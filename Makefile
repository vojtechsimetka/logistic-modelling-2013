##
# IMS project
#
# @author xsimet00 Vojtech Simetka
# @author xhonji01 Jiri Hon

CPP  = g++
CXXFLAGS=-std=c++98 -Wall -W -g -O3
CLINK=-lsimlib -lm

PROGRAM=model
ARCHIVE_ZIP=05_xsimet00_xhonji01.zip
README=Readme
DOC=dokumentace.pdf

$(PROGRAM): main.o facts.o packet.o model.o calendar.o office.o car.o param.o exception.o statistics.o
	$(CPP) main.o facts.o packet.o model.o calendar.o office.o car.o param.o exception.o statistics.o -o $(PROGRAM) $(CLINK)

# kompilace hlavniho souboru
main.o: main.cpp
	$(CPP) -c main.cpp -o main.o $(CXXFLAGS) $(CLINK)

# kompilace facts
facts.o: facts.cpp
	$(CPP) -c facts.cpp -o facts.o $(CXXFLAGS) $(CLINK)

# kompilace packet
packet.o: packet.cpp
	$(CPP) -c packet.cpp -o packet.o $(CXXFLAGS) $(CLINK)
	
# kompilace model
model.o: model.cpp
	$(CPP) -c model.cpp -o model.o $(CXXFLAGS) $(CLINK)
	
# kompilace calendar
calendar.o: calendar.cpp
	$(CPP) -c calendar.cpp -o calendar.o $(CXXFLAGS) $(CLINK)
	
# kompilace office
office.o: office.cpp
	$(CPP) -c office.cpp -o office.o $(CXXFLAGS) $(CLINK)
	
# kompilace car
car.o: car.cpp
	$(CPP) -c car.cpp -o car.o $(CXXFLAGS) $(CLINK)
	
# kompilace param
param.o: param.cpp
	$(CPP) -c param.cpp -o param.o $(CXXFLAGS) $(CLINK)
	
# kompilace exception
exception.o: exception.cpp
	$(CPP) -c exception.cpp -o exception.o $(CXXFLAGS) $(CLINK)
	
# kompilace statistics
statistics.o: statistics.cpp
	$(CPP) -c statistics.cpp -o statistics.o $(CXXFLAGS) $(CLINK)

# Pack final archive to zip
zip: *.cpp *.h
	@rm -f $(ARCHIVE_ZIP)
	zip $(ARCHIVE_ZIP) *.cpp *.h Makefile $(README) $(DOC)

# Runs project
run:
	./$(PROGRAM)
	
# Runs project with iteration over cars count
cars:
	./$(PROGRAM) -a n
	
# Runs project with iteration over cars capacity
capacity:
	./$(PROGRAM) -a k
	
# Runs project with iteration over package generation times
packages:
	./$(PROGRAM) -a p
	
# Runs project with iteration over offices central
offices:
	./$(PROGRAM) -a o

# Clean makefile products
clean:
	@rm -rf *.o $(PROGRAM) $(ARCHIVE_ZIP)

.PHONY: clean

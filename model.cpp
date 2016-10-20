/**
 * IMS12
 * Model describtion class
 *
 * @author  xhonji01 Jiri Hon
 * @author  xsimet00 Vojtech Simetka
 *
 * @date    2012/11/30
 * @version 1
 * @file    model.cpp
 */

#include "model.h"


/**
 * Model constructor
 */
Model::Model(Param param)
: parameters(param)
{
	// Resets central office cars visits (used for cars AI)
	central_car_visit = 0;
	
	// Creates calendar
	calendar = new Calendar(this);
	
	// Creates package generator
	packetgen = new PacketGen(this);
	
	// Creates offices
	createOffices();
	
	// Sets day
	workinghours = false;
	
	// Creates cars
	createCars();
	
	// Initializes statistics
	initStats();
	
	// Activates model entities
	Activate();
}

/**
 * Model destructor
 */
Model::~Model()
{	
	// Clears offices
	for (unsigned int i = 0; i < offices_count; i++)
		delete offices[i];
	
	// Clears cars
	for (unsigned int i = 0; i < my_cars.size(); i++)
		//my_cars.pop_back()->Cancel();
		my_cars.pop_back();
	
	// Stops calendar
	calendar->Cancel();
	
	// Stops calendar generator
	packetgen->Cancel();
}

/**
 * Creates offices for model
 */
void Model::createOffices()
{
	for (unsigned int i = 0; i < offices_count; i++)
	{
		// Creates office
		offices[i] = new Office((T_ofc)i, parameters.offices_workers_per_office);
		
		// Saves information about office in statistics
		model_statistics.addOffice(parameters.offices_workers_per_office);
	}
}

/**
 * Creates cars for model
 */
void Model::createCars()
{	
	for (cars_count = 0; cars_count < parameters.cars_count; cars_count++)
	{
		// Creates car
		my_cars.push_back(new Car(this, (T_ofc)(cars_count % offices_count)));
		
		// Saves information about car in statistics
		model_statistics.addCar(parameters.cars_capacity);
	}
}

/**
 * Initializes statistics for model
 */
void Model::initStats()
{
	// Resets cars statistics
	overall_car_stat.Clear();
	
	// Undelivered packages histogram
	undelivered_packages_hist.Init(1, 1, 20);
	undelivered_packages_hist.SetName("Undelivered packages before offices open");
	
	// Delivered packages histogram
	delivered_packages_delay.Init(0, 1, 5);
	delivered_packages_delay.SetName("Delivery time in days");
	
	// Overall model statistics
	model_statistics.setSimulationDuration(parameters.simulation_time);
	model_statistics.setMoneyPerPackage(parameters.package_price);
	model_statistics.setRent(parameters.money_rent_per_day);
	model_statistics.setCellary(parameters.money_worker_per_hour);
	model_statistics.setCarOutcome(parameters.money_car_per_km, parameters.money_car_per_hour);
	model_statistics.setCarCapacity(parameters.cars_capacity);
	model_statistics.setPackagesGenTime(parameters.package_gen_time);
	model_statistics.setMoneyPerCar(parameters.money_per_car);
	model_statistics.setMoneyPerCapacity(parameters.money_per_capacity);
	model_statistics.setCentral(parameters.offices_central);
}

/**
 * Print choosen statistics of the model
 */
void Model::Output()
{
	// Prints statistics about each car load
	if (parameters.statistics_car_load)
	{
		for (unsigned int i = 0; i < my_cars.size(); i++)
			(my_cars[i])->Output();
	}
	
	// Prints total statistics for cars
	if (parameters.statistics_car_load_total)
		overall_car_stat.Output();
	
	// Prints histogram of undelivered packages
	if (parameters.statistics_undelivered_packages_hist)
		undelivered_packages_hist.Output();
	
	// Prints histogram containing delivery time in days
	if (parameters.statistics_delivered_packages_delay)
		delivered_packages_delay.Output();
	
	
	// Saves cars total average load
	if (overall_car_stat.Number() != 0)
	{
		model_statistics.setAverageLoad(overall_car_stat.MeanValue());
		model_statistics.setMaxLoad(overall_car_stat.Max());
	}
	
	// Saves information about delivered packages
	if (delivered_packages_delay.stat.Number() != 0)
	{
		model_statistics.setAverageDeliveryTime(delivered_packages_delay.stat.MeanValue());
		model_statistics.setMaxDeliveryTime(delivered_packages_delay.stat.Max());
	}
	
	// Saves information about undelivered packages
	if (undelivered_packages_hist.stat.Number() != 0) {
		model_statistics.setAverageUndeliveredPackages(undelivered_packages_hist.stat.MeanValue());
		model_statistics.setMaxUndeliveredPackages(undelivered_packages_hist.stat.Max());
	}
	
	// Prints model statistics
	if (parameters.statistics_overall)
	{	
		// Prints statistics
		model_statistics.print();
	}
	
	// Prints statistics for experiments
	if (parameters.experiment_car_count)
		model_statistics.printExperimentCars();
		
	else if (parameters.experiment_car_capacity)
		model_statistics.printExperimentCapacity();
		
	else if (parameters.experiment_packages)
		model_statistics.printExperimentPackages();
	
	else if (parameters.experiment_central)
		model_statistics.printExperimentOffice();
}

/**
 * Returns time from one location to another. Also records it with distance traveled.
 * @param from statring position
 * @param to destination
 * @return time spent travelling
 */
double Model::travelTime(T_ofc from, T_ofc to)
{
	double travel_time = Facts::travelTime(from, to);
	double travel_distance = Facts::travelDistance(from,to);
	
	// Saves information about travelled distance and time
	model_statistics.addTravelInfo(travel_time, travel_distance);
	
	// Returns travel time
	return travel_time;
}

/**
 * Responds to day request
 * @return true if its day
 */
bool Model::isWorkinghours()
{
	return workinghours;
}

/**
 * Sets day or night and reactivates generators/cars
 * @param value New information about day
 */
void Model::setWorkinghours(bool value)
{
	workinghours = value;
	
	// Workinghours
	if (workinghours)
	{
		// Records undelivered packages
		recordLeftOvers();
	
		// Activates package generation
		packetgen->Activate(Time + 1);
	}
	
	// Offices closed
	else
	{
		// Activates cars
		ActivateCars();
	}
}

/**
 * Returns office for ID request
 * @param id Office descriptor
 * @return Requested office reference
 */
Office * Model::getOffice(T_ofc id){
	return offices[id];
}

/**
 * Activates model entities
 */
void Model::Activate(){
	// Activates package generation
	packetgen->Activate(Time + 1);
	
	// Activates day/night calendar
	calendar->Activate();
	
	// Activates cars
	ActivateCars();
}

/**
 * Activates model cars
 */
void Model::ActivateCars()
{	
	// Activates cars
	for (unsigned int i = 0; i < my_cars.size(); i++)
	{
		if (my_cars[i]->isPassive()) {
			my_cars[i]->Activate();
		}
	}
}

/**
 * Adds new package to adequate store
 * @param where package destination
 * @param packet reference to package
 */
void Model::addPackage(T_ofc from, T_ofc to, Packet * packet)
{
	// Adds packet
	offices[from]->addPackage(to, packet);
	
	// Saves statistics
	model_statistics.addPackage();
}

/**
 * Records packages that hadn't been delivered in time
 */
void Model::recordLeftOvers()
{
	// Delivers and counts undelivered packages within offices
	for (unsigned int i = 0; i < offices_count; i++)
	{
		// Deliver packages to customers
		deliverPackages((T_ofc)i);
	}
	
	// Notes total number of undelivered packages
	recordUndelivered();
}

/**
 * Records delay of delivered packages
 * @param day_count number of days
 */
void Model::recordDelivered(unsigned int day_count)
{
	delivered_packages_delay(day_count);
	model_statistics.addDeliveredPackage(day_count);
}

/**
 * Records number of undelivered packages within office
 * @param id ID of office for which we cound undelivered packages
 */
void Model::recordUndelivered()
{
	unsigned int undelivered_total = 0;
	
	// Counts undelivered packages in office
	for (unsigned int i = 0; i < offices_count; i++)
	{
		for (unsigned int j = 0; j < offices_count; j++)
		{
			// Deliver packages that are in queue for this office
			if (i == j)
				continue;
		
			// Note how many undelivered packages is there
			else
				undelivered_total += offices[j]->getQueue((T_ofc)j)->Length();
		}
	}
	
	// Counts undelivered packages in cars
	for (unsigned int i = 0; i < my_cars.size(); i++)
		undelivered_total += my_cars[i]->getLoad();
	
	// Records value
	undelivered_packages_hist(undelivered_total);
}

/**
 * Delivers all packages in office with id ID
 * @param id ID of office
 */
void Model::deliverPackages(T_ofc id)
{
	while (!offices[id]->getQueue(id)->Empty())
		offices[id]->getQueue(id)->GetFirst()->Activate();
}

/**
 * Gets office where the car should travel from offices central
 * @return Next cars destination
 */
T_ofc Model::getTravelOffice()
{
	// Cycles through offices
	for (unsigned int i = 0; i < offices_count; i++) {
		if (i == parameters.offices_central)
			continue;
		
		if (offices[i]->getNumberOfUndeliveredPackages() > getNumberOfCarsHeadingToOffice((T_ofc)i) * parameters.cars_capacity)
			return (T_ofc)i;
	}
	
	for (unsigned int i = 0; i < offices_count; i++)
	{
		if (i == parameters.offices_central)
			continue;
		
		if (!offices[parameters.offices_central]->getQueue((T_ofc)i)->Empty())
			return (T_ofc)i;
		
	}
	// This should never happen
	//throw Exception(E_dest);
	return parameters.offices_central;
}

/**
 * Adds load information about car to statistics about all car
 * @param value Load information to store
 */
void Model::addToOverallCarStat(unsigned int value)
{
	overall_car_stat(value);
}


/**
 * Returns true if all offices are empty
 * @return True if all offices are empty
 */
bool Model::officesEmpty()
{
	for (unsigned int i = 0; i < offices_count; i++)
	{
		if (!offices[i]->isEmpty())
			return false;
	}
	return true;
}

/**
 * Returns true if there is loaded car heading to central office
 * @return True if there is loaded car heading to central office
 */
bool Model::noLoadedCarHeadingToCentral()
{
	for (unsigned int i = 0; i < cars_count; i++)
	{
		if (my_cars[i]->getPosition() == parameters.offices_central)
		{
			if (!my_cars[i]->isEmpty())
				return false;
		}
	}
	return true;;
}

/**
 * Returns true if there are no packages to deliver in central office
 * @return True if there are no packages to deliver in central office
 */
bool Model::centralEmpty()
{
	return offices[parameters.offices_central]->isEmpty();
}

/**
 * Returns true if there is enough cars heading to branch offices to withdraw packages
 * @return True if there is enough cars heading to branch offices to withdraw packages
 */
bool Model::noUnhandledPacksInOffices()
{
	for (unsigned int i = 0; i < offices_count; i++)
	{
		if (offices[i]->getNumberOfUndeliveredPackages() > getNumberOfCarsHeadingToOffice((T_ofc)i) * parameters.cars_capacity)
			return false;
	}
		
	return true;
}

/**
 * Returns number of cars heading to office or being in office
 */
unsigned int Model::getNumberOfCarsHeadingToOffice(T_ofc office)
{
	unsigned int count = 0;
	
	for (unsigned int i = 0; i < cars_count; i++)
	{
		if (my_cars[i]->getPosition() == office)
			count++;
	}
	
	return count;
}

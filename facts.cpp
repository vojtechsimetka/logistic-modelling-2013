/**
 * IMS12
 * Model facts class
 *
 * @author  xhonji01 Jiri Hon
 * @author  xsimet00 Vojtech Simetka
 *
 * @date    2012/11/30
 * @version 1
 * @file    facts.cpp
 */

#include "facts.h"

// Average delay - used for calculating traveling time
const double Facts::average_travel_delay = 1.1;

// Offices names - uset by toString method
const char *Facts::off_names[] =
{
	"Praha 9",
	"Praha 4",
	"Brno",
	"Brno 2",
	"Ostrava",
	"Hradec Kralove",
	"Olomouc",
	"Plzen",
	"Bratislava",
};

// Time spent by traveling between two offices
const double Facts::travel_time_field[offices_count][offices_count] =
{//    P9   P4   Br  Br2   Os   HK   Ol   Pl   Ba
	{  0,  19, 129, 124, 209,  62, 162, 140, 192}, // Praha9
	{ 19,   0, 114, 119, 203,  74, 155, 129, 183}, // Praha4
	{129, 114,   0,   6,  99, 143,  51, 170,  82}, // Brno
	{124, 119,   6,   0, 100, 148,  52, 175,  85}, // Brno2
	{209, 203,  99, 100,   0, 181,  62, 255, 168}, // Ostrava
	{ 62,  74, 143, 148, 181,   0, 126, 130, 211}, // HradecKralove
	{162, 155,  51,  52,  62, 126,   0, 208, 120}, // Olomouc
	{140, 129, 170, 175, 255, 130, 208,   0, 238}, // Plzen
	{192, 183,  82,  85, 168, 211, 120, 238,   0}  // Bratislava
};

// Distance spent by traveling between two offices
const double Facts::travel_distance_field[offices_count][offices_count] =
{//     P9     P4     Br    Br2     Os     HK     Ol     Pl     Ba
	{  0  ,  10.8, 213  , 212  , 377  , 100  , 286  , 110  , 335  }, // Praha9
	{ 10.8,   0  , 204  , 205  , 370  , 112  , 279  ,  96.7, 327  }, // Praha4
	{213  , 204  ,   0  ,   2.6, 169  , 167  ,  77.9, 286  , 132  }, // Brno
	{212  , 205  ,  2.6 ,   0  , 170  , 143  ,  78.3, 297  , 132  }, // Brno2
	{377  , 370  , 169  , 170  ,   0  , 240  , 100  , 461  , 293  }, // Ostrava
	{100  , 112  , 167  , 143  , 240  ,   0  , 141  , 203  , 290  }, // HradecKralove
	{286  , 279  ,  77.9,  78.9, 100  , 141  ,   0  , 370  , 202  }, // Olomouc
	{110  ,  96.7, 286  , 297  , 461  , 203  , 370  ,   0  , 419  }, // Plzen
	{335  , 327  , 132  , 132  , 293  , 290  , 202  , 419  ,   0  }  // Bratislava
};

/**
 * Used for generating package address
 * @return Packets destination
 */
T_ofc Facts::officeGen()
{
	double office_gen = Uniform(0, 100);
	// Praha 9
	if (office_gen <= 12)
		return Praha9;
	// Praha 4
	else if (office_gen <= 24)
		return Praha4;
	// Brno
	else if (office_gen <= 33)
		return Brno;
	// Brno 2
	else if (office_gen <= 42)
		return Brno2;
	// Ostrava
	else if (office_gen <= 55)
		return Ostrava;
	// Hradec Kralove
	else if (office_gen <= 64)
		return HradecKralove;
	// Olomouc
	else if (office_gen <= 75)
		return Olomouc;
	// Plzen
	else if (office_gen <= 84)
		return Plzen;
	// Bratislava
	else
		return Bratislava;
}

/**
 * Converts office name to string
 * @param name Office enum
 * @return Name of office
 */
const char * Facts::toString(T_ofc name)
{
	return off_names[name];
}

/**
 * Calculates and returns distance between two offices
 * @param from Source office
 * @param to Destination office
 * @return Distance between offices
 */
double Facts::travelDistance(T_ofc from, T_ofc to)
{
	return travel_distance_field[from][to];
}

/**
 * Calculates and returns time spent by traveling between two offices
 * @param from Source office
 * @param to Destination office
 * @return Time spent by traveling between offices
 */
double Facts::travelTime(T_ofc from, T_ofc to)
{
	return travel_time_field[from][to] * average_travel_delay;
}

/**
 * Asks whether or not is one pair of offces closer then other
 * @param office Office B
 * @param position Office A
 * @param destination Office C
 * @param delay Time spent by loading packages
 * @return Time spent traveling A -> C + time spent loading packages is lesser then time spent traveling B -> C;
 */
bool Facts::isCloser(T_ofc office, T_ofc position, T_ofc destination, double delay)
{
	return (travel_time_field[office][destination] * average_travel_delay + delay) < (travel_time_field[position][destination] * average_travel_delay);
}

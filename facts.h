/**
 * IMS12
 * Model facts class header
 *
 * @author  xhonji01 Jiri Hon
 * @author  xsimet00 Vojtech Simetka
 *
 * @date    2012/11/30
 * @version 1
 * @file    facts.h
 */

#ifndef __IMS__facts__
#define __IMS__facts__

#include <iostream>
#include <map>
#ifdef __APPLE__
#include "../simlib.h"
#else
#include "simlib.h"
#endif

using namespace std;

typedef enum {
	Praha9 = 0,
	Praha4,
	Brno,
	Brno2,
	Ostrava,
	HradecKralove,
	Olomouc,
	Plzen,
	Bratislava,
}T_ofc;

const unsigned int offices_count = 9;

class Facts
{
public:
	static T_ofc officeGen();
	static const char * toString(T_ofc);
	static double travelDistance(T_ofc, T_ofc);
	static double travelTime(T_ofc, T_ofc);
	static bool isCloser(T_ofc, T_ofc, T_ofc, double);
	
private:
	static const char *off_names[];
	static const double travel_time_field[offices_count][offices_count];
	static const double travel_distance_field[offices_count][offices_count];
	static const double average_travel_delay;
};

#endif /* defined(__IMS__facts__) */

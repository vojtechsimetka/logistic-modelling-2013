/**
 * IMS12
 * Model and program parameters header
 *
 * @author  xhonji01 Jiri Hon
 * @author  xsimet00 Vojtech Simetka
 *
 * @date    2012/12/01
 * @version 1
 * @file    param.h
 */

#ifndef __IMS__param__
#define __IMS__param__

#include <iostream>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <iomanip>
#include "exception.h"
#include "facts.h"

using namespace std;

class Param
{
public:
	Param();
	Param(int argc, const char * argv[]);
	bool simulationEnd();
	
	// Simulation variables
	unsigned int cars_count;
	unsigned int cars_capacity;
	double cars_load_time;
	double cars_pause_time;
	
	double offices_workhours;
	T_ofc offices_central;
	unsigned int offices_workers_per_office;
	
	unsigned int simulation_time;
	bool simulation_debug;
	
	double package_gen_time;
	double package_price;
	double package_process_time;
	
	double money_rent_per_day;
	double money_worker_per_hour;
	double money_car_per_km;
	double money_car_per_hour;
	double money_per_car;
	double money_per_capacity;
	
	bool statistics_car_load;
	bool statistics_car_load_total;
	bool statistics_undelivered_packages_hist;
	bool statistics_delivered_packages_delay;
	bool statistics_overall;
	
	bool experiment_car_count;
	bool experiment_car_capacity;
	bool experiment_packages;
	bool experiment_central;
	
private:
	// Methods
	void setDefault();
	bool repeat();
	unsigned int stringToInt(string);
	void increment();
	
	// Variables
	unsigned int repeat_c;
	unsigned int experiment_repeat_count;
	unsigned int max;
	unsigned int min;
};

#endif /* defined(__IMS__param__) */

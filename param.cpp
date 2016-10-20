/**
 * IMS12
 * Model and program parameters
 *
 * @author  xhonji01 Jiri Hon
 * @author  xsimet00 Vojtech Simetka
 *
 * @date    2012/12/01
 * @version 1
 * @file    param.cpp
 */

#include "param.h"

/**
 * Param constructor, initializes values to default
 */
Param::Param()
{
	setDefault();
}

/**
 * Param constructor, allows setting various parameters from command line
 * @param argc Argument counter
 * @param argv Argument vector
 */
Param::Param(int argc, const char * argv[])
{
	setDefault();
	
	for (int i = 1; i < argc; i++)
	{
		// Sets number of cars in system
		if (!strcmp("-n", argv[i]))
		{
			if (argc > i)
				cars_count = stringToInt(argv[++i]);
		}
		// Sets cars capacity
		else if (!strcmp("-k", argv[i]))
		{
			if (argc > i)
				cars_capacity = stringToInt(argv[++i]);
		}
		// Sets simulation duration
		else if (!strcmp("-t", argv[i]))
		{
			if (argc > i)
				simulation_time = stringToInt(argv[++i]);
		}
		
		// Debuging mode
		else if (!strcmp("-d", argv[i]))
			simulation_debug = true;
		
		// Used for printing graphs, prints only outputs
		else if (!strcmp("-a", argv[i]))
		{
			if (argc > i)
			{
				i++;
				statistics_overall = false;
				repeat_c = 0;
				unsigned int width = 15;
				
				// Simulates number of cars
				if (!strcmp("n", argv[i]))
				{
					cout << left
					<< setw(width) << "Cars count"    << "\t"
					<< setw(width) << "Capacity"      << "\t"
					<< setw(width) << "Gen time"      << "\t"
					<< setw(width) << "Packages"      << "\t"
					<< setw(width) << "Average load"  << "\t"
					<< setw(width) << "Delivered"     << "\t"
					<< setw(width) << "In time"       << "\t"
					<< setw(width) << "Ratio"         << "\t"
					<< setw(width) << "Average delay" << "\t"
					<< setw(width) << "Max delay"     << "\t"
					<< setw(width) << "Budget"        << "\t" << endl;
					min = 1;
					max = 100;
					experiment_car_count = true;
					cars_count = 1;
				}
				
				// Simulates various capacity
				if (!strcmp("k", argv[i]))
				{
					cout << left
					<< setw(width) << "Cars count"    << "\t"
					<< setw(width) << "Capacity"      << "\t"
					<< setw(width) << "Gen time"      << "\t"
					<< setw(width) << "Packages"      << "\t"
					<< setw(width) << "Average load"  << "\t"
					<< setw(width) << "Delivered"     << "\t"
					<< setw(width) << "In time"       << "\t"
					<< setw(width) << "Ratio"         << "\t"
					<< setw(width) << "Average delay" << "\t"
					<< setw(width) << "Max delay"     << "\t"
					<< setw(width) << "Budget"        << "\t" << endl;
					min = 50;
					max = 200;
					experiment_car_capacity = true;
					cars_capacity = 50;
				}
				
				// Simulates packages distribution
				if (!strcmp("p", argv[i]))
				{
					cout << left
					<< setw(width) << "Cars count"    << "\t"
					<< setw(width) << "Capacity"      << "\t"
					<< setw(width) << "Gen time"      << "\t"
					<< setw(width) << "Packages"      << "\t"
					<< setw(width) << "Average load"  << "\t"
					<< setw(width) << "Delivered"     << "\t"
					<< setw(width) << "In time"       << "\t"
					<< setw(width) << "Ratio"         << "\t"
					<< setw(width) << "Average delay" << "\t"
					<< setw(width) << "Max delay"     << "\t"
					<< setw(width) << "Budget"        << "\t" << endl;
					min = 0.5;
					max = 2.5*10;
					experiment_packages = true;
					package_gen_time = 0.5;
				}
				
				// Simulates centrall position parameters
				if (!strcmp("o", argv[i]))
				{
					cout << left
					<< setw(width) << "Central Off."  << "\t"
					<< setw(width) << "Cars count"    << "\t"
					<< setw(width) << "Capacity"      << "\t"
					<< setw(width) << "Gen time"      << "\t"
					<< setw(width) << "Packages"      << "\t"
					<< setw(width) << "Average load"  << "\t"
					<< setw(width) << "Delivered"     << "\t"
					<< setw(width) << "In time"       << "\t"
					<< setw(width) << "Ratio"         << "\t"
					<< setw(width) << "Average delay" << "\t"
					<< setw(width) << "Max delay"     << "\t"
					<< setw(width) << "Budget"        << "\t" << endl;
					min = 1;
					max = offices_count;
					experiment_central = true;
					offices_central = Praha9;
				}
			}
		}
		
		// Prints statistics
		else if (!strcmp("-s", argv[i]))
		{
			if (argc > i)
			{
				i++;
				if (!strcmp("c", argv[i]))
					statistics_car_load = true;
				
				else if ((!strcmp("ct", argv[i])))
					statistics_car_load_total = true;
				
				else if ((!strcmp("puh", argv[i])))
					statistics_undelivered_packages_hist = true;
				
				else if ((!strcmp("dph", argv[i])))
					statistics_delivered_packages_delay = true;
			}
		}
	}
}

/**
 * Sets default values to parameters
 */
void Param::setDefault()
{
	cars_count = 9;
	cars_capacity= 150;
	cars_load_time = 1.5;
	cars_pause_time = 10;
	
	offices_workhours = 8;
	offices_central = Brno;
	offices_workers_per_office = 2;
	
	simulation_time = 2628000;
	simulation_debug = false;
	
	package_gen_time = 0.75;
	package_price = 35;
	package_process_time = 3;
	
	money_rent_per_day = 150;
	money_worker_per_hour = 80;
	money_car_per_km = 2.5;
	money_car_per_hour = 80;
	money_per_car = 200000;
	money_per_capacity = 0.02;
	
	statistics_car_load = false;
	statistics_car_load_total = false;
	statistics_undelivered_packages_hist = false;
	statistics_delivered_packages_delay = false;
	statistics_overall = true;
	
	experiment_car_count = false;
	experiment_car_capacity = false;
	experiment_packages = false;
	experiment_central = false;
	experiment_repeat_count = 30;
	
	repeat_c = experiment_repeat_count-1;
	min = 0;
	max = 0;
}

/**
 * Converts string to integer
 * @param stringNumber String we want to convert to number
 * @return Converted integer
 */
unsigned int Param::stringToInt(string stringNumber)
{
	unsigned int number = 0;
	
	// Converts string to integer
	for (unsigned int i = 0; i < stringNumber.length(); i++)
		// It is number
		if (isdigit(stringNumber[i]))
			number = number * 10 + (static_cast<int>(stringNumber[i])-'0');
	// Not a number, throws exception
		else
			throw Exception(E_param);
	
	// Returns converted number
	return number;
}

/**
 * Calculates number of repetion for each value
 * @return True if enought experiments with same value was alredy done
 */
bool Param::repeat()
{
	return ++repeat_c > experiment_repeat_count;
}

/**
 * Checks whether there was enough simulations of model behavior
 * @return True if there was enough simulations of model behavior
 */
bool Param::simulationEnd()
{
	if (repeat())
		increment();
	
	return min > max;
}

/**
 * Increments values for next experiment
 */
void Param::increment()
{
	if (experiment_car_count)
		cars_count++;
	
	else if (experiment_car_capacity)
		cars_capacity++;
	
	else if (experiment_packages)
		package_gen_time+=0.1;
	
	else if (experiment_central)
		offices_central=(T_ofc)(offices_central + 1);
	
	// Increments counter and resets number of tries
	min++;
	repeat_c = 1;
}

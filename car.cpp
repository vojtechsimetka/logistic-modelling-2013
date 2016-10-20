/**
 * IMS12
 * Model's Car class
 *
 * @author  xhonji01 Jiri Hon
 * @author  xsimet00 Vojtech Simetka
 *
 * @date    2012/11/30
 * @version 1
 * @file    car.cpp
 */

#include "car.h"

/**
 * Car constructor
 * @param pos starting position
 */
Car::Car(Model * mod, T_ofc pos)
{
	capacity = mod->parameters.cars_capacity;
	position = pos;
	model = mod;
	passive = true;
}

/**
 * Car destructor
 */
Car::~Car()
{
//	// Destroy all packets in cars trunk
//	for (unsigned int i = 0; i < offices_count; i++) {
//		while (!load[i].Empty()) {
//			load[i].GetFirst()->Cancel();
//		}
//	}
}

/**
 * Describes behavior of car
 */
void Car::Behavior()
{
	// Loops forever
	while (1)
	{
		// Sets car active
		passive = false;
		
		// Cars delivers only at night
		if (model->isWorkinghours())
		{
			Rest();
			continue;
		}
		
		// 
		if (position != model->parameters.offices_central &&
			model->officesEmpty() &&
			model->noLoadedCarHeadingToCentral())
		{
			Rest();
			continue;
		}
		
		if (position == model->parameters.offices_central &&
			model->centralEmpty() &&
			model->noUnhandledPacksInOffices())
		{
			Rest();
			continue;
		}
		
		// Chooses destination and loads packages
		loadPackages();
			
		// Saves cars load
		recordStats();
			
		// Unloads
		unloadPackages();
		
		// Pause
		Wait(model->parameters.cars_pause_time);
	}
}

/**
 *
 */
void Car::Rest()
{
	passive = true;
	Passivate();
}

/**
 * Returns how full the car is
 * @return number of packages in car
 */
unsigned int  Car::getLoad()
{
	return model->parameters.cars_capacity - capacity;
}

/**
 * Prints statistics of this car
 */
void Car::Output()
{
	my_stat.Output();
}

/**
 * Records car statistics
 */
void Car::recordStats()
{	
	my_stat(getLoad());
	model->addToOverallCarStat(getLoad());
}

///**
// * Loads packages into car
// * @return choosen destination of car
// */
//T_ofc Car::ownLoadPackages()
//{	
//	// Chooses which packages we will deliver
//	T_ofc destination = chooseDestination();
//	
//	// Cars travels through model
//	for (unsigned int j = Praha9; j < offices_count; j++) {
//		
//		double load_delay = 0;
//		if (model->parameters.simulation_own_assignment_count_delay)
//			load_delay = model->parameters.cars_load_time * model->getOffice(position)->getQueue((T_ofc)j)->Length() + model->parameters.cars_pause_time;
//		
//		if (Facts::isCloser((T_ofc)j, position, destination, load_delay))
//			// Loads packages
//			allocatePackages((T_ofc)j);
//	}
//	
//	// Moves packages to cars trunk
//	allocatePackages(destination);
//	
//	// Time spent by loading packages
//	Wait((model->parameters.cars_capacity - capacity) * model->parameters.cars_load_time);
//	
//	return destination;
//}

/**
 * Loads packages into car
 */
void Car::loadPackages()
{
	
	// Chooses which packages we will deliver
	T_ofc destination;
	
	// We are in centrall office, collect only packages for destination
	if (position == model->parameters.offices_central)
	{
		destination = model->getTravelOffice();
		
		allocatePackages(destination);
	}
	// We are heading to centrall office, collect all availiable packages
	else
	{
		destination = model->parameters.offices_central;
		
		for (unsigned int j = 0; j < offices_count; j++) {
			// Loads packages for every office excluding this one
			if (j != position) {
				// Loads packages
				allocatePackages((T_ofc)j);
			}
		}
	}
	
	double time_to_new_destination = model->travelTime(position, destination);
	
	// Set ready to drive to destination
	position = destination;
	
	// Time spent by loading packages
	Wait((model->parameters.cars_capacity - capacity) * model->parameters.cars_load_time);
	
	// Sleeps for time spent by traveling
	Wait(time_to_new_destination);
	
	// Reactivates all passive cars
	if (position == model->parameters.offices_central)
		model->ActivateCars();
}

/**
 * Allocates packages in office where the car is for choosen detination
 * @param destination ID of office for loading packages
 */
void Car::allocatePackages(T_ofc destination)
{
	Store * worker = model->getOffice(position)->getWorker();
	
	Enter(*worker, model->parameters.offices_workers_per_office);
	
	for (unsigned int i = 0;(!model->getOffice(position)->getQueue(destination)->Empty()) && (capacity > 0); i ++)
	{
		load[destination].Insert(model->getOffice(position)->getQueue(destination)->GetFirst());
		capacity--;
	}
	
	Leave(*worker, model->parameters.offices_workers_per_office);
}

/**
 * Choses destination of next travel
 * @return ID of office where the car will travel
 */
T_ofc Car::chooseDestination()
{
	if (position == model->parameters.offices_central)
		return model->getOffice(position)->getFullestQueue();
		
	else
		return model->parameters.offices_central;
	
}

/**
 * Unloads all packages into office where car currently is
 */
void Car::unloadPackages()
{
	unsigned int unload_time = model->parameters.cars_capacity - capacity;
	
	// Goes through every output queue
	for (unsigned int i = Praha9; i < offices_count; i++)
	{
		// Unloads every package
		while (!load[i].Empty())
		{
			model->getOffice(position)->getQueue((T_ofc)i)->Insert(load[i].GetFirst());
			capacity++;
		}
	}
	
	// Releases office
	
	// Time spent by unloading packages
	Wait(unload_time * model->parameters.cars_load_time);
}

/**
 * Gets cars position
 * @return Car position
 */
T_ofc Car::getPosition()
{
	return position;
}

/**
 * Returns true if car is empty
 * @return True if car is empty
 */
bool Car::isEmpty()
{
	return capacity==model->parameters.cars_capacity;
}

bool Car::isPassive()
{
	return passive;
}

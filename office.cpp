/**
 * IMS12
 * Model office class
 *
 * @author  xhonji01 Jiri Hon
 * @author  xsimet00 Vojtech Simetka
 *
 * @date    2012/11/30
 * @version 1
 * @file    office.cpp
 */

#include "office.h"

/**
 * Office constructor
 * @param name office's name
 */
Office::Office(T_ofc name, unsigned int worker_count)
{
	// Stores name
	my_name = name;
	
	// Creates workers name
	worker = new Store(Facts::toString(name), worker_count);
	
	// Sets queue names
	for (unsigned int i = 0; i < offices_count; i++)
		queue[i].SetName(Facts::toString((T_ofc)i));
}

/**
 * Office destructor
 */
Office::~Office()
{
	worker->Clear();
	
	delete worker;
	
	// Destroy all packets
	for (unsigned int i = 0; i < offices_count; i++) {
		while (!queue[i].Empty()) {
			queue[i].GetFirst()->Cancel();
		}
	}
}

/**
 * Gets worker reference for this office
 * @return Store reference
 */
Store * Office::getWorker()
{
	return worker;
}

/**
 * Adds new package to adequate store
 * @param where package destination
 * @param packet reference to package
 */
void Office::addPackage(T_ofc where, Packet * packet)
{
	queue[where].Insert(packet);
}

/**
 * Returns store that is fullest
 * @return fullest store reference
 */
T_ofc Office::getFullestQueue()
{
	T_ofc fullest = Praha9;
	
	if (fullest == my_name)
		fullest = Bratislava;
	
	// Loops over every queue
	for (unsigned int i = 0; i < offices_count; i++)
	{
		// Skipps queue for this office
		if (i == my_name)
			continue;
		
		// Found longer queue
		if (queue[i].Length() > queue[fullest].Length())
			fullest = (T_ofc)i;
	}
	
	return fullest;
}

/**
 * Gets queue reference
 * @param from queue idetification
 * @return queue reference
 */
Queue * Office::getQueue(T_ofc from)
{
	return queue[from];
}

/**
 * Returns true if there are no undelivered packages in this office
 * @return True if there are no undelivered packages in this office
 */
bool Office::isEmpty()
{
	for (unsigned int i = 0; i < offices_count; i++)
	{
		if (i == my_name)
			continue;
		
		if (!queue[i].Empty())
			return false;
	}
	return true;
}

unsigned int Office::getNumberOfUndeliveredPackages()
{
	unsigned int count = 0;
	
	for (unsigned int i = 0; i < offices_count; i++)
	{
		// Skipps queue for this office
		if (i == my_name)
			continue;
		
		count += queue[i].Length();
	}
	return count;
}

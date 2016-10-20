/**
 * IMS12
 * Model office class header
 *
 * @author  xhonji01 Jiri Hon
 * @author  xsimet00 Vojtech Simetka
 *
 * @date    2012/11/30
 * @version 1
 * @file    office.h
 */

#ifndef __IMS__office__
#define __IMS__office__

#include <iostream>
#ifdef __APPLE__
#include "../simlib.h"
#else
#include "simlib.h"
#endif
#include "facts.h"
#include "packet.h"

class Packet;

using namespace std;

class Office
{
public:
	Office(T_ofc, unsigned int);
	~Office();
	Store * getWorker();
	void addPackage(T_ofc, Packet *);
	T_ofc getFullestQueue();
	Queue * getQueue(T_ofc);
	bool isEmpty();
	unsigned int getNumberOfUndeliveredPackages();
	
private:
	T_ofc my_name;
	Store * worker;
	Queue queue[offices_count];
};

#endif /* defined(__IMS__office__) */

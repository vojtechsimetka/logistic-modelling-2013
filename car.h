/**
 * IMS12
 * Model's Car class header
 *
 * @author  xhonji01 Jiri Hon
 * @author  xsimet00 Vojtech Simetka
 *
 * @date    2012/11/30
 * @version 1
 * @file    car.h
 */

#ifndef __IMS__car__
#define __IMS__car__

#include <iostream>
#ifdef __APPLE__
#include "../simlib.h"
#else
#include "simlib.h"
#endif
#include "param.h"
#include "facts.h"
#include "model.h"
#include <iomanip>

class Model;

class Car : public Process
{
public:
	Car(Model *, T_ofc);
	~Car();
	void Behavior();
	void Output();
	unsigned int getLoad();
	T_ofc getPosition();
	bool isEmpty();
	bool isPassive();
	void Rest();
	
private:
	void recordStats();
	void loadPackages();
//	T_ofc ownLoadPackages();
	void unloadPackages();
	T_ofc chooseDestination();
	void allocatePackages(T_ofc);
	
	unsigned int capacity;
	Queue load[offices_count];
	T_ofc position;
	Stat my_stat;
	Model * model;
	bool passive;
};

#endif /* defined(__IMS__car__) */

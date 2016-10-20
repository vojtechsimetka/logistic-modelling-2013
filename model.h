/**
 * IMS12
 * Model describtion class header
 *
 * @author  xhonji01 Jiri Hon
 * @author  xsimet00 Vojtech Simetka
 *
 * @date    2012/11/30
 * @version 1
 * @file    model.h
 */

#ifndef __IMS__model__
#define __IMS__model__

#include <iostream>
#include <vector>

#ifdef __APPLE__
#include "../simlib.h"
#else
#include "simlib.h"
#endif
#include "facts.h"
#include "packet.h"
#include "office.h"
#include "car.h"
#include "calendar.h"
#include "statistics.h"

class Office;
class Car;
class Packet;
class PacketGen;
class Calendar;

class Model
{
public:
	Model(Param);
	~Model();
	void Output();
	double travelTime(T_ofc, T_ofc);
	bool isWorkinghours();
	void setWorkinghours(bool);
	Office * getOffice(T_ofc);
	void Activate();
	void ActivateCars();
	void recordLeftOvers();
	void recordDelivered(unsigned int);
	void addPackage(T_ofc, T_ofc, Packet *);
	T_ofc getTravelOffice();
	void addToOverallCarStat(unsigned int);
	
	bool officesEmpty();
	bool noLoadedCarHeadingToCentral();
	bool centralEmpty();
	bool noUnhandledPacksInOffices();
	
	// Model parameters
	const Param parameters;

private:
	// Methods
	void deliverPackages(T_ofc);
	void createOffices();
	void createCars();
	void initStats();
	void recordUndelivered();
	unsigned int getNumberOfCarsHeadingToOffice(T_ofc);
	
	// Variables
	Office * offices[offices_count];
	bool workinghours;
	vector<Car *> my_cars;
	unsigned int central_car_visit;
	Calendar * calendar;
	PacketGen * packetgen;
	Stat overall_car_stat;
	unsigned int cars_count;
	
	// Statistics
	Histogram undelivered_packages_hist;
	Histogram delivered_packages_delay;
	Statistics model_statistics;
};

#endif /* defined(__IMS__model__) */

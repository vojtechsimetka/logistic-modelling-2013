/**
 * IMS12
 * Model statistics class header
 *
 * @author  xhonji01 Jiri Hon
 * @author  xsimet00 Vojtech Simetka
 *
 * @date    2012/12/3
 * @version 1
 * @file    statistic.h
 */

#ifndef __IMS__statistics__
#define __IMS__statistics__

#include <iostream>
#include <iomanip>
#include <stdio.h>
#include "facts.h"

using namespace std;

class Statistics
{
public:
	Statistics();
	
	void setSimulationDuration(unsigned int);
	void addOffice(unsigned int);
	void addCar(unsigned int);
	void addTravelInfo(unsigned int, unsigned int);
	void addPackage();
	void addDeliveredPackage(unsigned int);
	void setAverageDeliveryTime(double);
	void setMaxDeliveryTime(unsigned int);
	void setMoneyPerPackage(unsigned int);
	void setAverageLoad(double);
	void setMaxLoad(unsigned int);
	void setRent(double);
	void setCellary(double);
	void setCarOutcome(double, double);
	void setAverageUndeliveredPackages(double);
	void setMaxUndeliveredPackages(unsigned int);
	void setCarCapacity(unsigned int);
	void setPackagesGenTime(double);
	void setMoneyPerCar(double);
	void setMoneyPerCapacity(double);
	void setCentral(T_ofc);
	
	
	void print();
	void printExperimentCars();
	void printExperimentCapacity();
	void printExperimentPackages();
	void printExperimentOffice();
	void printExperimentAll();
	
private:
	// Methods
	void printRow(string);
	void printHeadRow();
	double totalMoneyCar();
	double totalMoneyWorker();
	double totalMoneyRent();
	double totalOutcome();
	double totalIncome();
	double budgetChange();
	double deliveredInTimeRatio();
	
	// Variables
	unsigned int simulation_time;
	
	unsigned int offices_count;
	unsigned int offices_workers;
	T_ofc offices_central;
	
	unsigned int cars_count;
	unsigned int cars_capacity;
	unsigned int cars_total_cap;
	unsigned int cars_travel_distance;
	unsigned int cars_travel_time;
	double cars_average_load;
	unsigned int cars_max_load;
	
	unsigned int packages_created;
	unsigned int packages_delivered;
	unsigned int packages_delivered_in_time;
	double packages_average_delivery_time;
	unsigned int packages_max_delivery_time;
	double packages_average_undelivered;
	unsigned int packages_max_undelivered;
	double packages_gen_time;
	
	double money_per_package;
	double money_rent_per_day;
	double money_worker_per_hour;
	double money_car_per_km;
	double money_car_per_hour;
	double money_per_car;
	double money_per_capacity;
};

#endif /* defined(__IMS__statistics__) */

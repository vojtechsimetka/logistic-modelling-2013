/**
 * IMS12
 * Model statistics class
 *
 * @author  xhonji01 Jiri Hon
 * @author  xsimet00 Vojtech Simetka
 *
 * @date    2012/12/3
 * @version 1
 * @file    statistic.cpp
 */

#include "statistics.h"

/**
 * Statistics constructor
 */
Statistics::Statistics()
{
	simulation_time=0;
	offices_count=0;
	offices_workers=0;
	cars_count=0;
	cars_total_cap=0;
	cars_travel_distance=0;
	cars_travel_time=0;
	cars_average_load=0;
	packages_created=0;
	packages_delivered=0;
	packages_delivered_in_time=0;
	packages_average_delivery_time=0;
	packages_max_delivery_time=0;
	packages_average_undelivered=0;
	packages_max_undelivered=0;
	money_per_package=0;
	money_rent_per_day=0;
	money_worker_per_hour=0;
	money_car_per_km=0;
	money_car_per_hour=0;
	money_per_car=0;
	money_per_capacity=0;
}

/**
 * Prints statistics
 */
void Statistics::print()
{
	// Prints head
	printHeadRow();
	printRow(" Model overall statistics");
	printHeadRow();
	
	// Prints Simulation time
	char buffer [80];
	sprintf(buffer, "Simulation time: %dy %dd %dh %dm", simulation_time /  525600, simulation_time % 525600 / 1440, (simulation_time % 1440) / 60, ((simulation_time % 1440) % 60));
	printRow(buffer);
	printRow(" ");
	
	// Number of offices
	sprintf(buffer, "Number of offices: %d", offices_count);
	printRow(buffer);
	
	// Nimber of workers
	sprintf(buffer, "Number of workers: %d", offices_workers);
	printRow(buffer);
	printRow(" ");
	
	// Number of cars
	sprintf(buffer, "Number of cars: %d", cars_count);
	printRow(buffer);
	
	// Prints total traveled distance
	sprintf(buffer, "Total traveled distance: %dkm", cars_travel_distance);
	printRow(buffer);
	
	// Prints total traveled time
	sprintf(buffer, "Total traveled time: %dm", cars_travel_time);
	printRow(buffer);
	
	// Prints average load
	sprintf(buffer, "Average load: %.2f", cars_average_load);
	printRow(buffer);
	
	// Prints max load
	sprintf(buffer, "Maximal load: %d", cars_max_load);
	printRow(buffer);
	printRow(" ");
	
	sprintf(buffer, "Number of packages: %d", packages_created);
	printRow(buffer);
	
	sprintf(buffer, "Number of delivered packages: %d", packages_delivered);
	printRow(buffer);
	
	sprintf(buffer, "Packages delivered within next work day: %d", packages_delivered_in_time);
	printRow(buffer);
	
	sprintf(buffer, "Packages delivered within next work day ratio: %.2f%%", deliveredInTimeRatio());
	printRow(buffer);
	
	sprintf(buffer, "Packages delivered average delay: %.2fd", packages_average_delivery_time);
	printRow(buffer);
	
	sprintf(buffer, "Packages delivered maximal delay: %dd", packages_max_delivery_time);
	printRow(buffer);
	
	sprintf(buffer, "Packages maximal undelivered within day: %d", packages_max_undelivered);
	printRow(buffer);
	
	sprintf(buffer, "Packages average undelivered within day: %.2f", packages_average_undelivered);
	printRow(buffer);
	printRow(" ");
	
	sprintf(buffer, "Package price: %.2f", money_per_package);
	printRow(buffer);
	
	sprintf(buffer, "Total income: %.2fKc", money_per_package*packages_created);
	printRow(buffer);
	
	sprintf(buffer, "Total outcome: %.2fKc", totalOutcome());
	printRow(buffer);
	
	sprintf(buffer, "Outcome cars: %.2fKc", totalMoneyCar());
	printRow(buffer);
	
	sprintf(buffer, "Outcome workers & drivers: %.2fKc", totalMoneyWorker());
	printRow(buffer);
	
	sprintf(buffer, "Outcome rent: %.2fKc", totalMoneyRent());
	printRow(buffer);
	printRow(" ");
	
	if (deliveredInTimeRatio() > 95)
		printRow("Assignment fullfilled: True");
	else
		printRow("Assignment fullfilled: False");
	
	// Prints budget
	sprintf(buffer, "BUDGET CHANGE: %.2fKc", budgetChange());
	printRow(buffer);
	
	printHeadRow();
}

/**
 * Prints row with speified text
 */
void Statistics::printRow(string text)
{	cout << "|" <<  setw(58) << setfill(' ') << left << text << "|" << endl;
}

/**
 * Prints header
 */
void Statistics::printHeadRow()
{
	cout << "+" << setw(59) << right << setfill('-') << "+" << endl;
}

/**
 * Sets simulation duration
 * @param sim_duration Duration of simulation
 */
void Statistics::setSimulationDuration(unsigned int sim_duration)
{
	simulation_time = sim_duration;
}

/**
 * Adds office to statistics
 * @param workers Number of workers in office
 */
void Statistics::addOffice(unsigned int workers)
{
	offices_count ++;
	offices_workers += workers;
}

/**
 * Adds car to statistics
 * @param capacity Cars capacity
 */
void Statistics::addCar(unsigned int capacity)
{
	cars_count++;
	cars_total_cap += capacity;
}

/**
 * Adds information about car travels
 * @param dist Traveled distance
 * @param time Time spent traveling
 */
void Statistics::addTravelInfo(unsigned int dist, unsigned int time)
{
	cars_travel_distance+=dist;
	cars_travel_time+=time;
}

/**
 * Adds information about newly created package to statistics
 */
void Statistics::addPackage()
{
	packages_created++;
}

/**
 * Adds informaton about delivered package
 * @param delay Time spent in system in days
 */
void Statistics::addDeliveredPackage(unsigned int delay)
{
	packages_delivered++;
	
	if (delay == 0)
		packages_delivered_in_time++;
}

/**
 * Sets price of package
 * @param packet_price Price of package
 */
void Statistics::setMoneyPerPackage(unsigned int package_price)
{
	money_per_package = package_price;
}

/**
 * Sets information about average cars load
 * @param av_load Average cars load
 */
void Statistics::setAverageLoad(double av_load)
{
	cars_average_load = av_load;
}

/**
 * Sets rent
 * @param rent Rent per day
 */
void Statistics::setRent(double rent)
{
	money_rent_per_day = rent;
}

/**
 * Sets cellary
 * @param cellary Workers cellary per hour
 */
void Statistics::setCellary(double cellary)
{
	money_worker_per_hour = cellary;
}

/**
 * Sets outcome for travelled kilometr and drivers cellary per hour
 * @param per_km Outcome for travelled kilometr
 * @param per_hour Driver's cellary per hour
 */
void Statistics::setCarOutcome(double per_km, double per_hour)
{
	money_car_per_km = per_km;
	money_car_per_hour = per_hour;
}

/**
 * Sets information about average delivery time
 * @param delay Average delivery time in days
 */
void Statistics::setAverageDeliveryTime(double delay)
{
	packages_average_delivery_time = delay;
}

/**
 * Sets maximal delivery time
 * @param value Maximal delivery time in days
 */
void Statistics::setMaxDeliveryTime(unsigned int value)
{
	packages_max_delivery_time = value;
}

/**
 * Sets maximal load of all cars
 * @param value Maximal load of all cars
 */
void Statistics::setMaxLoad(unsigned int value)
{
	cars_max_load = value;
}

/**
 * Sets average undelivered packages per day
 * @param value Average undelivered packages per day
 */
void Statistics::setAverageUndeliveredPackages(double value)
{
	packages_average_undelivered = value;
}

/**
 * Sets maximal undelivered packages per day
 * @param value Maximal undelivered packages per day
 */
void Statistics::setMaxUndeliveredPackages(unsigned int value)
{
	packages_max_undelivered = value;
}

/**
 * Prints output for parameter -a n (cars count)
 */
void Statistics::printExperimentCars()
{
	unsigned int width = 15;
	
	cout << left
	<< setw(width) << cars_count                     << "\t"
	<< setw(width) << cars_capacity                  << "\t"
	<< setw(width) << packages_gen_time              << "\t"
	<< setw(width) << packages_created               << "\t"
	<< setw(width) << cars_average_load              << "\t"
	<< setw(width) << packages_delivered             << "\t"
	<< setw(width) << packages_delivered_in_time     << "\t"
	<< setw(width) << deliveredInTimeRatio()         << "\t"
	<< setw(width) << packages_average_delivery_time << "\t"
	<< setw(width) << packages_max_delivery_time     << "\t"
	<< setw(width) << budgetChange() << endl;
}

/**
 * Prints output for parameter -a k (cars capacity)
 */
void Statistics::printExperimentCapacity()
{
	unsigned int width = 15;
	
	cout << left
	<< setw(width) << cars_count                     << "\t"
	<< setw(width) << cars_capacity                  << "\t"
	<< setw(width) << packages_gen_time              << "\t"
	<< setw(width) << packages_created               << "\t"
	<< setw(width) << cars_average_load              << "\t"
	<< setw(width) << packages_delivered             << "\t"
	<< setw(width) << packages_delivered_in_time     << "\t"
	<< setw(width) << deliveredInTimeRatio()         << "\t"
	<< setw(width) << packages_average_delivery_time << "\t"
	<< setw(width) << packages_max_delivery_time     << "\t"
	<< setw(width) << budgetChange() << endl;
}

/**
 * Prints output for parameter -a p (packages generation time)
 */
void Statistics::printExperimentPackages()
{
	unsigned int width = 15;
	
	cout << left
	<< setw(width) << cars_count                     << "\t"
	<< setw(width) << cars_capacity                  << "\t"
	<< setw(width) << packages_gen_time              << "\t"
	<< setw(width) << packages_created               << "\t"
	<< setw(width) << cars_average_load              << "\t"
	<< setw(width) << packages_delivered             << "\t"
	<< setw(width) << packages_delivered_in_time     << "\t"
	<< setw(width) << deliveredInTimeRatio()         << "\t"
	<< setw(width) << packages_average_delivery_time << "\t"
	<< setw(width) << packages_max_delivery_time     << "\t"
	<< setw(width) << budgetChange() << endl;
}

/**
 * Prints output for parameter -a a
 */
void Statistics::printExperimentAll()
{
	unsigned int width = 15;
	
	cout << left
	<< setw(width) << cars_count                     << "\t"
	<< setw(width) << cars_capacity                  << "\t"
	<< setw(width) << packages_gen_time              << "\t"
	<< setw(width) << packages_created               << "\t"
	<< setw(width) << cars_average_load              << "\t"
	<< setw(width) << packages_delivered             << "\t"
	<< setw(width) << packages_delivered_in_time     << "\t"
	<< setw(width) << deliveredInTimeRatio()         << "\t"
	<< setw(width) << packages_average_delivery_time << "\t"
	<< setw(width) << packages_max_delivery_time     << "\t"
	<< setw(width) << budgetChange() << endl;
}

/**
 * Prints output for parameter -a o
 */
void Statistics::printExperimentOffice()
{
	unsigned int width = 15;
	
	cout << left
	<< setw(width) << Facts::toString(offices_central)<< "\t"
	<< setw(width) << cars_count                     << "\t"
	<< setw(width) << cars_capacity                  << "\t"
	<< setw(width) << packages_gen_time              << "\t"
	<< setw(width) << packages_created               << "\t"
	<< setw(width) << cars_average_load              << "\t"
	<< setw(width) << packages_delivered             << "\t"
	<< setw(width) << packages_delivered_in_time     << "\t"
	<< setw(width) << deliveredInTimeRatio()         << "\t"
	<< setw(width) << packages_average_delivery_time << "\t"
	<< setw(width) << packages_max_delivery_time     << "\t"
	<< setw(width) << budgetChange() << endl;
}

/**
 * Calculates and returns total money for cars
 * @return Outcome money from cars
 */
double Statistics::totalMoneyCar(){
	return money_car_per_km * cars_travel_distance+ cars_count * money_per_car + cars_travel_distance * money_per_capacity;
}

/**
 * Calculates and returns total money for workers
 * @return Outcome money from cellary
 */
double Statistics::totalMoneyWorker(){
	return money_worker_per_hour * (simulation_time / 1440) * 8 + money_car_per_hour * cars_travel_time / 60;
}

/**
 * Calculates and returns total money per car
 * @return Outcome money from cars
 */
double Statistics::totalMoneyRent()
{
	return money_rent_per_day * (simulation_time / 1440);
}

/**
 * Calculates and returns total outcome
 * @return Total system outcome
 */
double Statistics::totalOutcome()
{
	return totalMoneyCar() + totalMoneyWorker() + totalMoneyRent();
}

/**
 * Calculates and returns total income
 * @return Total system income
 */
double Statistics::totalIncome()
{
	return money_per_package*packages_created;
}

/**
 * Calculates and returns budget change
 * @return Budget change
 */
double Statistics::budgetChange()
{
	return totalIncome() - totalOutcome();
}

/**
 * Calculates and returns ratio of how many delivered packages were delivered in time
 * @return Ratio of in time delivered packages
 */
double Statistics::deliveredInTimeRatio()
{
	return packages_delivered == 0 ? 0 : ((double)packages_delivered_in_time/packages_delivered*100);
}

/**
 * Sets car capacity
 * @param value Car capacity
 */
void Statistics::setCarCapacity(unsigned int value)
{
	cars_capacity = value;
}

/**
 * Sets packages generation time
 * @param value Time between generating two packages
 */
void Statistics::setPackagesGenTime(double value)
{
	packages_gen_time = value;
}

/**
 * Sets money per car capacity
 * @param value Money per car capacity
 */
void Statistics::setMoneyPerCapacity(double value)
{
	money_per_capacity = value;
}

/**
 * Sets money per car
 * @param value Money per car
 */
void Statistics::setMoneyPerCar(double value)
{
	money_per_car = value;
}

/**
 * Sets offices central
 * @param value Offices central
 */
void Statistics::setCentral(T_ofc value)
{
	offices_central = value;
}

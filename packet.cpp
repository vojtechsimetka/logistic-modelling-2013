/**
 * IMS12
 * Model's Packet and PacketGen class
 *
 * @author  xhonji01 Jiri Hon
 * @author  xsimet00 Vojtech Simetka
 *
 * @date    2012/11/30
 * @version 1
 * @file    packet.cpp
 */

#include "packet.h"

/**
 * PacketGen constructor
 * @param mode model reference
 */
PacketGen::PacketGen(Model* mod)
{
	model = mod;
}


/**
 * Bahavior of package generator, generates packets
 */
void PacketGen::Behavior()
{
	// Offices are open
	if (model->isWorkinghours())
	{
		(new Packet(model))->Activate();
		
		// Plans next activation
		Activate(Time + Exponential(model->parameters.package_gen_time));
	}
}

/**
 * Packet constructor
 * @param mod model reference
 */
Packet::Packet(Model * mod)
{
	creation_time = Time;
	model = mod;
}

/**
 * Packet behavior
 */
void Packet::Behavior()
{
	// Generates office where new package should go
	T_ofc choose_ofc = Facts::officeGen();
	
	Store * worker = model->getOffice(choose_ofc)->getWorker();
	
	// Seizes worker
	Enter(*worker);
	
	// Service
	Wait(model->parameters.package_process_time);
	
	// Adds new package to store
	model->addPackage(choose_ofc, Facts::officeGen(), this);
	
	// Releases worker for office
	Leave(*worker);
	
	// Waiting for withdrawal
	Passivate();
	
	// Records when the package was delivered 
	model->recordDelivered(floor((Time - creation_time) / 1440));
}

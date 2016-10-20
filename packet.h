/**
 * IMS12
 * Model's Packet and PacketGen class header
 *
 * @author  xhonji01 Jiri Hon
 * @author  xsimet00 Vojtech Simetka
 *
 * @date    2012/11/30
 * @version 1
 * @file    packet.h
 */

#ifndef __IMS__packet__
#define __IMS__packet__

#include <iostream>
#include <math.h>
#ifdef __APPLE__
#include "../simlib.h"
#else
#include "simlib.h"
#endif
#include "param.h"
#include "facts.h"
#include "model.h"

class Model;

class PacketGen : public Event
{
public:
	PacketGen(Model *);
	void Behavior();
private:
	Model * model;
};

class Packet : public Process
{
public:
	Packet(Model *);
	void Behavior();
	void setModel(Model *);
	
private:
	Model * model;
	double creation_time;
};


#endif /* defined(__IMS__packet__) */

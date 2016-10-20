/**
 * IMS12
 * Models calendar class header
 *
 * @author  xhonji01 Jiri Hon
 * @author  xsimet00 Vojtech Simetka
 *
 * @date    2012/11/30
 * @version 1
 * @file    calendar.h
 */

#ifndef __IMS__callendar__
#define __IMS__callendar__

#include <iostream>
#ifdef __APPLE__
#include "../simlib.h"
#else
#include "simlib.h"
#endif
#include "model.h"

class Model;

class Calendar : public Event
{
public:
	Calendar(Model *);
	void Behavior();
	
private:
	Model *model;
};

#endif /* defined(__IMS__callendar__) */

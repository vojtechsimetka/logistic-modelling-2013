/**
 * IMS12
 * Models calendar class
 *
 * @author  xhonji01 Jiri Hon
 * @author  xsimet00 Vojtech Simetka
 *
 * @date    2012/11/30
 * @version 1
 * @file    calendar.cpp
 */

#include "calendar.h"

/**
 * Calendar constructor
 * @param mod Model reference
 */
Calendar::Calendar(Model * mod)
{
	model = mod;
}


/**
 * Calendar behavior process
 */
void Calendar::Behavior()
{
	// Offices closes, activate cars
	if (model->isWorkinghours()) {
		
		// Sets night
		model->setWorkinghours(false);
		
		// Plans next activation
		Activate(Time + (24 - model->parameters.offices_workhours) * 60);
	}
	
	// Offices opens
	else
	{
		// Sets day
		model->setWorkinghours(true);
		
		// Plans next activation
		Activate(Time + model->parameters.offices_workhours * 60);
	}
}
 
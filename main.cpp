/**
 * IMS12
 * Model main file
 *
 * @author  xhonji01 Jiri Hon
 * @author  xsimet00 Vojtech Simetka
 *
 * @date    2012/11/28
 * @version 1
 * @file    main.cpp
 */

#include "main.h"

Store * store;

int main(int argc, const char * argv[])
{
	try {
		// Parses parameters
		Param simulation_param(argc, argv);
		
		// Switches on debug mode
		if (simulation_param.simulation_debug)
			DebugON();
		
		// Randomize Exponential and Uniform generators
		RandomSeed(time(NULL));
		
		// Models cycle
		while (!simulation_param.simulationEnd())
		{
			// Initializes simulation
			Init(0, simulation_param.simulation_time);
			
			// Creates model
			Model model(simulation_param);
			
			// Runs simulation
			Run();
			
			// Prints outputs
			model.Output();
		}
		
		return EXIT_SUCCESS;
	}
	catch(...)
	{
		return EXIT_FAILURE;
	}
}

/**
 * IMS12
 * Programs exception class
 *
 * @author  xhonji01 Jiri Hon
 * @author  xsimet00 Vojtech Simetka
 *
 * @date    2012/12/01
 * @version 1
 * @file    exception.cpp
 */

#include "exception.h"

Exception::Exception(T_exc code){
	// Exceptions
	const char *EXC[] =
	{
		"Incorrect number format",
		"Multiple model definition",
		"Error finding path"
	};
	
	cerr << EXC[code] << endl;
}
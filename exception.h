/**
 * IMS12
 * Programs exception class header
 *
 * @author  xhonji01 Jiri Hon
 * @author  xsimet00 Vojtech Simetka
 *
 * @date    2012/12/01
 * @version 1
 * @file    exception.h
 */

#ifndef __IMS__exception__
#define __IMS__exception__

#include <iostream>
using namespace std;

// Enums
typedef enum {
	E_param,
	E_model,
	E_dest
}T_exc;

class Exception {
public:
	Exception(T_exc code);
};

#endif /* defined(__IMS__exception__) */

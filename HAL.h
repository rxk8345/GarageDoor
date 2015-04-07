/*
 * MotorController.h
 *
 *  Created on: Mar 17, 2015
 *      Author: rdl8212
 */

#ifndef MOTORCONTROLLER_H_
#define MOTORCONTROLLER_H_

#include "common.h"

void motorUp();
void motorDown();
void motorStop();
void turnIROn();
void turnIROff();
void setUpHardware();
event pollInputs();

#endif /* MOTORCONTROLLER_H_ */

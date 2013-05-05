/*
 * Softpot routine for device
 *
 * Author Suguru Oho
 * Since 2013/05/06
 * 
 * This file is Softpot routines of firmware for my HMD device.
 * 
 */

#include "Arduino.h"
#include "SoftpotLib.h"

SoftpotLib::SoftpotLib()
{
}

int SoftpotLib::read()
{
  return analogRead(SENSORPIN);
}


#ifndef __PHOTO_DIODE_H__
#define __PHOTO_DIODE_H__

#include <Arduino.h>

#include "DataSource.h"

typedef struct {
    float l = 0; // are we calibrating now?
} diode_state;

/*
 * ZStateEstimator class keeps track of the robot's depth state,
 * incorperating measurements of the system outputs from the Pressure
 * Sensor, as well as the control inputs to the system
 */
class PhotoDiode : public DataSource
{
public:
  PhotoDiode(void);

  // init
  void init(void);

  // State Access
  diode_state state;

  void updateState(int diode_signal);
  void updateState2(int diode_signal2);
  String printState(void);

  // from DataSource
  size_t writeDataBytes(unsigned char * buffer, size_t idx);

  int lastExecutionTime = -1;

private:
  // set pressure sensor calibration slope and incercept below
  // const float diodeCal_slope = -1.577;
  // const float diodeCal_intercept = 4.6802;

};

#endif
#ifndef __HALL_EFFECT_H__
#define __HALL_EFFECT_H__

#include <Arduino.h>

#include "DataSource.h"

typedef struct {
    float h = 0; // state of the hall effect sensor
} h_state;

/*
 * ZStateEstimator class keeps track of the robot's depth state,
 * incorperating measurements of the system outputs from the Pressure
 * Sensor, as well as the control inputs to the system
 */
class HallEffect : public DataSource
{
public:
  HallEffect(void);

  // init
  void init(void);

  // State Access
  h_state state;

  void updateState(int hallEffect_signal);
  String printState(void);

  // from DataSource
  size_t writeDataBytes(unsigned char * buffer, size_t idx);

  int lastExecutionTime = -1;

private:
    // 
};

#endif

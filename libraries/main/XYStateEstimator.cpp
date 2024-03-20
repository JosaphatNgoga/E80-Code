#include "XYStateEstimator.h"
#include <math.h>
#include "Printer.h"
extern Printer printer;

inline float angleDiff(float a) {
  while (a<-PI) a += 2*PI;
  while (a> PI) a -= 2*PI;
  return a;
}

XYStateEstimator::XYStateEstimator(void)
  : DataSource("x,y","float,float") // from DataSource
{}

void XYStateEstimator::init(void) {
 	state.x = 0;
  state.y = 0;
  state.yaw = 0;
}

void XYStateEstimator::updateState(imu_state_t * imu_state_p, gps_state_t * gps_state_p) {
  if (gps_state_p->num_sat >= N_SATS_THRESHOLD){
    gpsAcquired = 1;

    // set the values of state.x, state.y, and state.yaw
    // It can make use of the constants RADIUS_OF_EARTH, origin_lat, origin_lon (see XYStateEstimator.h)
    // You can access the current GPS latitude and longitude readings with gps_state_p->lat and gps_state_p->lon
    // You can access the current imu heading with imu_state_p->heading
    // Also note that math.h is already included so you have access to trig functions [rad]

    ///////////////// YAW, X and Y CALCULATIONS /////////////////
    float origin_lat_radians = origin_lat * PI / 180.0; //Convert to rad
    state.x = 2 * PI * RADIUS_OF_EARTH_M * cos(origin_lat_radians) * (gps_state_p->lon - origin_lon)/360;

    state.y = 2 * PI * RADIUS_OF_EARTH_M * (gps_state_p->lat - origin_lat)/360;

    float offset_angle = 0; 
    state.yaw = (PI/2) - imu_state_p->heading + offset_angle;
    // Adjust yaw to be in the range [-PI, PI]
    if (state.yaw < -PI) {
        state.yaw += (2 * PI); 
    } 
    else if (state.yaw > PI) {
        state.yaw -= (2 * PI);
    }

  }
  else{
    gpsAcquired = 0;
  }
}

String XYStateEstimator::printState(void) {
  String currentState = "";
  int decimals = 2;
  if (!gpsAcquired){
    currentState += "XY_State: Waiting to acquire more satellites...";
  }
  else{
    currentState += "XY_State: x: ";
    currentState += String(state.x,decimals);
    currentState += "[m], ";
    currentState += "y: ";
    currentState += String(state.y,decimals);
    currentState += "[m], ";
    currentState += "yaw: ";
    currentState += String(state.yaw,decimals);
    currentState += "[rad]; ";
  }
  return currentState;
}

size_t XYStateEstimator::writeDataBytes(unsigned char * buffer, size_t idx) {
  float * data_slot = (float *) &buffer[idx];
  data_slot[0] = state.x;
  data_slot[1] = state.y;
  return idx + 2*sizeof(float);
}

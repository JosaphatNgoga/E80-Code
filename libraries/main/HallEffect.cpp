#include "HallEffect.h"
#include <math.h>
#include "Printer.h"
extern Printer printer;

HallEffect::HallEffect(void)
  : DataSource("h","float") // from DataSource
{}

void HallEffect::init(void) {
  state.h = 0;
}

void HallEffect::updateState(int hallEffect_signal) {
  // get z (depth)
  float hallEffect_voltage = (double)hallEffect_signal;
  hallEffect_voltage *= (3.3/1023);  // convert from Teensy units to Volts
  // state.z = depthCal_slope * pressure_voltage + depthCal_intercept; // convert from Volts to depth [m]

  // uncomment the following print statement to calibrate your pressure sensor with the Teensy using the Serial Monitor
  String hallEffectMessage = "Hall Effect Voltage: " + String(hallEffect_voltage);
  printer.printMessage(hallEffectMessage,20);
}


String HallEffect::printState(void) {
  String currentState = "";
  int decimals = 2;
  currentState += "Hall effect state: ";
  currentState += String(state.h,decimals);
  currentState += "[V]";
  return currentState;
}

size_t HallEffect::writeDataBytes(unsigned char * buffer, size_t idx) {
    float * data_slot = (float *) &buffer[idx];
    data_slot[0] = state.h;
    return idx + sizeof(float);
}

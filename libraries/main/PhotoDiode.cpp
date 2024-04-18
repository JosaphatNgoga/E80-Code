#include "PhotoDiode.h"
#include <math.h>
#include "Printer.h"
extern Printer printer;

PhotoDiode::PhotoDiode(void)
  : DataSource("l","float") // from DataSource
{}

void PhotoDiode::init(void) {
  state.l = 0;
}

void PhotoDiode::updateState(int diode_signal) {
  float diode_voltage = (double)diode_signal;
  diode_voltage *= (3.3/1023);  // convert from Teensy units to Volts
  // state.z = depthCal_slope * pressure_voltage + depthCal_intercept; // convert from Volts to depth [m]

  // uncomment the following print statement to calibrate your pressure sensor with the Teensy using the Serial Monitor
  String diodeMessage = "Photodiode Voltage: " + String(diode_voltage);
  printer.printMessage(diodeMessage,20);
}


void PhotoDiode::updateState2(int diode_signal2) {
  float diode_voltage2 = (double)diode_signal2;
  diode_voltage2 *= (3.3/1023);  // convert from Teensy units to Volts

  String diodeMessage2 = "Photodiode Voltage 2: " + String(diode_voltage2);
  printer.printMessage(diodeMessage2,20);
}

String PhotoDiode::printState(void) {
  String currentState = "";
  int decimals = 2;
  currentState += "Photodiode state: ";
  currentState += String(state.l,decimals);
  currentState += "[V]";
  return currentState;
}

size_t PhotoDiode::writeDataBytes(unsigned char * buffer, size_t idx) {
    float * data_slot = (float *) &buffer[idx];
    data_slot[0] = state.l;
    return idx + sizeof(float);
}

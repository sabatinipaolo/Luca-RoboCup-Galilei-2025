#include <Arduino.h>
#include "../include/utility/utility.h"

double toGrad(double radianti) {
  double gradi;
  gradi = (180.0 * radianti) / PI;
  return gradi;
}

double toRad(double gradi) {
  double radianti;
  radianti = (PI * gradi) / 180.0;
  return radianti;
}

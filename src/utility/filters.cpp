#include <Arduino.h>
#include "utility/filters.h"
#include "utility/transformations.h"

int filter(float valA, float valP, float k) { //0<k<1
	int val0 = (k * valA) + ((1 - k) * valP);
	return val0;
}

int filter_angle(float angleA, float angleP, float k) { //0<k<1
	float angle_cos = (k * cos(toRad(angleA))) + ((1 - k) * cos(toRad(angleP)));
	float angle_sin = (k * sin(toRad(angleA))) + ((1 - k) * sin(toRad(angleP)));
	int val0 = toGrad(atan2(angle_sin, angle_cos));
	if (val0 < 0) val0 += 360;
	return val0;
}

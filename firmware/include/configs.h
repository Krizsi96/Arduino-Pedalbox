#pragma once

#define BRAKE_PEDAL_OFFSET 1000
#define BRAKE_PEDAL_FILTER_TYPE LOWPASS
#define BRAKE_PEDAL_FILTER_FREQUENCY 4
#define BRAKE_PEDAL_INITIAL_VALUE 0

#define THROTTLE_PEDAL_OFFSET -150
#define THROTTLE_PEDAL_FILTER_TYPE LOWPASS
#define THROTTLE_PEDAL_FILTER_FREQUENCY 10
#define THROTTLE_PEDAL_INITIAL_VALUE 0

#define CLUTCH_PEDAL_OFFSET -400
#define CLUTCH_PEDAL_FILTER_TYPE LOWPASS
#define CLUTCH_PEDAL_FILTER_FREQUENCY 10
#define CLUTCH_PEDAL_INITIAL_VALUE 0

#define THROTTLE_RANGE_MIN 0
#define THROTTLE_RANGE_MAX 600
#define BRAKE_RANGE_MIN 0
#define BRAKE_RANGE_MAX 180000
#define CLUTCH_RANGE_MIN 0
#define CLUTCH_RANGE_MAX 1023
/*
  AverageFilter.h - library for a mean-based filter
  Created by Ben Morris, March 19, 2021
*/

#ifndef AverageFilter_h
#define AverageFilter_h

#include "Arduino.h"

class AverageFilter
{
  public:
    AverageFilter(int pin, int length, double threshold, boolean reversed);
    AverageFilter(int pin, int length, double threshold);
    void update();
    boolean output();
    boolean lastOutput();
    boolean newly();
    boolean oldly();
  private:
    int _pin;
    int _length;
    double _threshold;
    long _startTime;
    boolean _output;
    boolean _lastOutput;
    double _sum;
    int _readings;
    boolean _reversed;
};

#endif
/*
  AverageFilter.cpp - library for a mean-based filter
  Created by Ben Morris, March 19, 2021
*/

#include "Arduino.h"
#include "AverageFilter.h"

AverageFilter::AverageFilter(int pin, int length, double threshold, boolean reversed)
{
  pinMode(pin, INPUT);
  _pin = pin;
  _length = length;
  _threshold = threshold;
  _startTime = -1;
  _output = false;
  _lastOutput = false;
  _sum = 0;
  _readings = 0;
  _reversed = reversed;
}
AverageFilter::AverageFilter(int pin, int length, double threshold)
{
  pinMode(pin, INPUT);
  _pin = pin;
  _length = length;
  _threshold = threshold;
  _startTime = -1;
  _output = false;
  _lastOutput = false;
  _sum = 0;
  _readings = 0;
  _reversed = false;
}

void AverageFilter::update()
{
  _lastOutput = _output;
  _sum += digitalRead(_pin);
  _readings++;
  
  long currentTime = millis();
  int elapsed = currentTime - _startTime;
  if (elapsed > _length) {
    double average = _sum / _readings;
    _output = _reversed ? average > _threshold : average < _threshold;
    
    _startTime = currentTime;
    _sum = 0;
    _readings = 0;
  }
}

boolean AverageFilter::output()
{
  return _output;
}

boolean AverageFilter::lastOutput()
{
  return _lastOutput;
}

boolean AverageFilter::newly()
{
  return output() && !lastOutput();
}

boolean AverageFilter::oldly()
{
  return !output() && lastOutput();
}
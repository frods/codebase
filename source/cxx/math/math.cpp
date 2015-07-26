#import "math.h"
#import <float.h>

float abs(float val)
{
  if(val >= 0.0f)
    return val;
  return -val;
}

float sqrt(float val)
{
  // Calculate square root using the babiloninan method
  return babilonian(val);
}

float babilonian(float val)
{
  // Make an initial quess of the quare root and
  // calculate the average of that and the quotient
  // repeat until desired accuracy has been reached

  float guess = 2.0;
  float delta = FLT_MAX;
  float accuracy = 0.00001;

  while(abs(delta) > accuracy)
  {
    float quotient = val/guess;
    float average = (guess + quotient)/2.0;
    delta = average - guess;
    guess = average;
  }
  return guess;
}

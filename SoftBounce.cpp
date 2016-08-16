#include <Arduino.h>
#include "SoftBounce.h"

#define DEBOUNCED_STATE 0
#define UNSTABLE_STATE  1
#define STATE_CHANGED   3

SoftBounce::SoftBounce()
    : previous_millis(0)
    , interval_millis(10)
    , state(0)
{

}

void SoftBounce::interval(uint16_t interval_millis)
{
    this->interval_millis = interval_millis;
}

bool SoftBounce::update(bool currentState)
{
  state &= ~_BV(STATE_CHANGED);

  // If the reading is different from last reading, reset the debounce counter
  if ( currentState != (bool)(state & _BV(UNSTABLE_STATE)) ) {
      previous_millis = millis();
      state ^= _BV(UNSTABLE_STATE);
  } else
      if ( millis() - previous_millis >= interval_millis ) {
          // We have passed the threshold time, so the input is now stable
          // If it is different from last state, set the STATE_CHANGED flag
          if ((bool)(state & _BV(DEBOUNCED_STATE)) != currentState) {
              previous_millis = millis();
              state ^= _BV(DEBOUNCED_STATE);
              state |= _BV(STATE_CHANGED);
          }
      }

  return state & _BV(STATE_CHANGED);
}

bool SoftBounce::high()
{
    return state & _BV(DEBOUNCED_STATE);
}

bool SoftBounce::rose()
{
    return ( state & _BV(DEBOUNCED_STATE) ) && ( state & _BV(STATE_CHANGED));
}

bool SoftBounce::fell()
{
    return !( state & _BV(DEBOUNCED_STATE) ) && ( state & _BV(STATE_CHANGED));
}

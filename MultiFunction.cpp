#include <Arduino.h>
#include "MultiFunction.h"

MultiFunction::MultiFunction()
{

}

void MultiFunction::changeFunction() {
  if (++currentFunction >= nrOfFunctions) {
    currentFunction = 0;
  }
}

void MultiFunction::doFunction() {
  if (nrOfFunctions > 0) {
    callbacks[currentFunction]();
  }
}

void MultiFunction::setFunctions( ptr_func _callbacks[], uint8_t _nrOfFunctions ) {
  callbacks = _callbacks;
  nrOfFunctions = _nrOfFunctions;
}

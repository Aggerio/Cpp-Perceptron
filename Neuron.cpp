#include "Neuron.hpp"

#include "main.hpp"

void Neuron::evaluate_val()
{
  float temp = 0.0f;
  for (int i = 0; i < INPUTS; ++i) {
    temp += inputs[i] * weights[i];
  }
  value = temp;
}

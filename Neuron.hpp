#include "main.hpp"

class Neuron {
  public:
  float value = 0.0f;
  std::vector<float> inputs;
  std::vector<float> weights;
  bool active = 0;
  float bias = 0.0f;

  Neuron()
  {
    inputs.resize(NEURON_PER_LAYER);
    weights.resize(NEURON_PER_LAYER);
  }

  // void activation_func();
  void evaluate_val();
};

#include "main.hpp"

#include "Neuron.hpp"
#include "Read_Data.hpp"
#include "Useful_Functions.hpp"

std::vector<float> MLP(std::vector<float> inputs,
                       std::vector<std::vector<std::vector<float>>> weights)
{
  std::vector<float> outp_vector;
  std::vector<std::vector<Neuron>> layers;
  for (int i = 0; i < HIDDEN_LAYERS + 1; ++i) {
    std::vector<Neuron> temp_Neuron_layer;
    for (int j = 0; j < weights[i].size(); ++j) {
      Neuron temp_Neuron;
      for (int k = 0; k < weights[i][j].size(); ++k) {
        if (i == 0) {
          temp_Neuron.value += inputs[k] * weights[i][j][k];
        }
        else {
          temp_Neuron.value += (ACTIVATION_FUNCTION(layers[i - 1][j].value) +
                                layers[i - 1][j].bias) *
                               weights[i][j][k];
        }
      }
      temp_Neuron_layer.push_back(temp_Neuron);
    }
    layers.push_back(temp_Neuron_layer);
  }
  // Getting the output of the last layer of Neurons
  for (int i = 0; i < layers[HIDDEN_LAYERS].size(); ++i) {
    // std::cout << "Neuron " << i + 1 << ": "
    // << (ACTIVATION_FUNCTION(layers[HIDDEN_LAYERS][i].value) +
    // layers[HIDDEN_LAYERS][i].bias)
    // << "\n";
    outp_vector.push_back((ACTIVATION_FUNCTION(layers[HIDDEN_LAYERS][i].value) +
                           layers[HIDDEN_LAYERS][i].bias));
  }
  return outp_vector;
}

int main()
{
  std::vector<std::vector<std::vector<float>>> weights;

  // Initializing the correct size of weights
  // Input --> 784
  // HIDDEN_LAYERS --> 2
  // Output --> 10
  // Therefore the vector size would be something like
  init_vec(weights, HIDDEN_LAYERS + 1, NEURON_PER_LAYER, NEURON_PER_LAYER);
  // for the input incase of mismatch in the no. of inputs and no. of neuron per
  // layer
  init_vec(weights[0], NEURON_PER_LAYER, INPUTS);
  // for the output incase of mismatch in the no. of outputs and no. of neuron
  // per layer
  init_vec(weights[HIDDEN_LAYERS], OUTPUTS, NEURON_PER_LAYER);

  // Initializing random weights
  random_weights(weights);

  std::vector<float> inputs = {0.3245, 0.213};
  std::vector<float> output = MLP(inputs, weights);

  for (int i = 0; i < OUTPUTS; ++i) {
    std::cout << "Neuron " << i + 1 << ": " << output[i] << "\n";
  }
  return 0;
}

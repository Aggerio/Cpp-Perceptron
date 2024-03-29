#include "main.hpp"

#include "Neuron.hpp"
#include "Read_Data.hpp"
#include "Useful_Functions.hpp"

std::vector<float> MLP(std::vector<float> inputs,
                       std::vector<std::vector<std::vector<float>>> weights,
                       std::vector<std::vector<Neuron>> &layers) {
  std::vector<float> outp_vector;
  for (int i = 0; i < HIDDEN_LAYERS + 1; ++i) {
    std::vector<Neuron> temp_Neuron_layer;
    for (int j = 0; j < weights[i].size(); ++j) {
      Neuron temp_Neuron;
      for (int k = 0; k < weights[i][j].size(); ++k) {
        if (i == 0) {
          temp_Neuron.value += inputs[k] * weights[i][j][k];
        } else {
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

void backpropagation(std::vector<float> &inputs,
                     std::vector<std::vector<std::vector<float>>> &weights,
                     const std::vector<float> targets, float learning_rate) {
  assert(targets.size() == OUTPUTS);
  std::vector<std::vector<Neuron>> layers;
  // Perform forward pass
  std::vector<float> outputs = MLP(inputs, weights, layers);

  // Compute output layer error
  std::vector<float> output_errors;
  for (int i = 0; i < OUTPUTS; ++i) {
    float error = std::pow(targets[i] - outputs[i], 2);
    output_errors.push_back(error * DERIVATIVE_ACTIVATION_FUNCTION(outputs[i]));
  }

  // Update output layer weights
  for (int i = 0; i < weights[HIDDEN_LAYERS].size(); ++i) {
    for (int j = 0; j < weights[HIDDEN_LAYERS][i].size(); ++j) {
      weights[HIDDEN_LAYERS][i][j] +=
          learning_rate * output_errors[i] * layers[HIDDEN_LAYERS][i].value;
    }
    layers[HIDDEN_LAYERS][i].bias += learning_rate * output_errors[i];
  }

  // Compute hidden layer errors and update weights
  for (int i = HIDDEN_LAYERS - 1; i >= 0; --i) {
    std::vector<float> hidden_errors;
    for (int j = 0; j < weights[i].size(); ++j) {
      float error = 0.0;
      for (int k = 0; k < weights[i + 1].size(); ++k) {
        error += output_errors[k] * weights[i + 1][k][j];
      }
      hidden_errors.push_back(
          error * DERIVATIVE_ACTIVATION_FUNCTION(layers[i][j].value));
    }

    for (int j = 0; j < weights[i].size(); ++j) {
      for (int k = 0; k < weights[i][j].size(); ++k) {
        if (i == 0) {
          weights[i][j][k] += learning_rate * hidden_errors[j] * inputs[k];
        } else {
          weights[i][j][k] +=
              learning_rate * hidden_errors[j] * layers[i - 1][k].value;
        }
      }
      layers[i][j].bias += learning_rate * hidden_errors[j];
    }
  }
}
int main() {
  std::vector<std::vector<std::vector<float>>> weights;

  // Initializing the correct size of weights
  // Input --> 784
  // HIDDEN_LAYERS --> 2
  // Output --> 10
  // Therefore the vector size would be something like
  init_vec(weights, HIDDEN_LAYERS + 1, NEURON_PER_LAYER, NEURON_PER_LAYER);
  // for the input incase of mismatch in the no. of inputs and no. of
  // neuron per layer
  init_vec(weights[0], NEURON_PER_LAYER, INPUTS);
  // for the output incase of mismatch in the no. of outputs and no. of
  // neuron per layer
  init_vec(weights[HIDDEN_LAYERS], OUTPUTS, NEURON_PER_LAYER);

  // Initializing random weights
  random_weights(weights);
  std::vector<std::vector<Neuron>> layers;

  std::vector<float> inputs = {0.3245, 0.213};
  std::vector<float> output = MLP(inputs, weights, layers);
  print_weights(weights);
  std::vector<float> targets = {1, 0, 0};
  backpropagation(inputs, weights, targets, 0.4);
  print_weights(weights);

  for (int i = 0; i < OUTPUTS; ++i) {
    std::cout << "Neuron " << i + 1 << ": " << output[i] << "\n";
  }
  return 0;
}

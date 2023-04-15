#pragma once

#include <assert.h>

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
// #define INPUTS 784
#define INPUTS 2
// #define OUTPUTS 10
#define OUTPUTS 3
// #define NEURON_PER_LAYER 784
#define NEURON_PER_LAYER 3
#define HIDDEN_LAYERS 2
#define ACTIVATION_FUNCTION sigmoid_activation_function
#define DERIVATIVE_ACTIVATION_FUNCTION derivative_sigmoid


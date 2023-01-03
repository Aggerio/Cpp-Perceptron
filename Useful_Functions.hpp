#include "main.hpp"

float dot_prod(std::vector<float> inp, std::vector<float> weights);

float relu_activation_function(float inp);
float sigmoid_activation_function(float inp);

void init_vec(std::vector<std::vector<float>> &vec, int n1, int n2);
void init_vec(std::vector<std::vector<std::vector<float>>> &vec, int n1, int n2,
              int n3);

float random_float();

void random_weights(std::vector<std::vector<std::vector<float>>> &vec);

std::vector<std::vector<float>> generate_output(std::vector<float> vec);

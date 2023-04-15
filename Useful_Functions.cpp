#include "Useful_Functions.hpp"

float dot_prod(std::vector<float> inp, std::vector<float> weights)
{
  float sum = 0;
  for (int i = 0; i < inp.size(); ++i) {
    sum += inp[i] * weights[i];
  }
  return sum;
}

float relu_activation_function(float inp) { return (inp > 0) ? inp : 0; }

float sigmoid_activation_function(float inp)
{
  return (1 / (1 + std::exp(-1 * inp)));
}

void init_vec(std::vector<std::vector<float>> &vec, int n1, int n2)
{
  vec.clear();
  for (int i = 0; i < n1; ++i) {
    std::vector<float> temp;
    for (int j = 0; j < n2; ++j) {
      float x = 0.0f;
      temp.push_back(x);
    }
    vec.push_back(temp);
  }
}

void init_vec(std::vector<std::vector<std::vector<float>>> &vec, int n1, int n2,
	      int n3)
{
  vec.clear();
  for (int i = 0; i < n1; ++i) {
    std::vector<std::vector<float>> temp1;
    for (int j = 0; j < n2; ++j) {
      std::vector<float> t;
      for (int k = 0; k < n3; ++k) {
	float x = 0.0f;
	t.push_back(x);
      }
      temp1.push_back(t);
    }
    vec.push_back(temp1);
  }
}

float random_float()
{
  return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}

void random_weights(std::vector<std::vector<std::vector<float>>> &vec)
{
  for (int i = 0; i < vec.size(); ++i) {
    for (int j = 0; j < vec[i].size(); ++j) {
      for (int k = 0; k < vec[i][j].size(); ++k) {
	vec[i][j][k] = random_float();
      }
    }
  }
}

std::vector<std::vector<float>> generate_output(std::vector<float> vec)
{
  std::vector<std::vector<float>> outp;
  for (int i = 0; i < vec.size(); ++i) {
    std::vector<float> temp(OUTPUTS);
    temp[vec[i]] = vec[i];
    outp.push_back(temp);
  }
  return outp;
}

float derivative_sigmoid(float inp)
{
  return sigmoid_activation_function(inp) *
	 (1 - sigmoid_activation_function(inp));
}

#include "Read_Data.hpp"

std::vector<std::string> load_file(std::string filename)
{
  std::ifstream f(filename, std::ios_base::in);
  std::string temp;
  std::vector<std::string> data;

  while (std::getline(f, temp)) {
    data.push_back(temp);
  }
  f.close();
  return data;
}

void get_pixel_data(std::vector<std::string> data, std::vector<int> &result,
                    std::vector<std::vector<int>> &pixel_data)
{
  // 1st line is useless
  data.erase(data.begin());
  result.clear();
  pixel_data.clear();
  // Now we split the lines at ',' position
  for (std::string a : data) {
    std::string temp = "";
    std::vector<int> pixel;
    for (char s : a) {
      if (s == ',') {
        pixel.push_back(stoi(temp));
        temp = "";
      }
      else {
        temp += s;
      }
    }

    pixel.push_back(std::stoi(temp));
    result.push_back(pixel[0]);
    pixel.erase(pixel.begin());
    pixel_data.push_back(pixel);
  }
}

// int main()
// {
// load_file("Dataset/train.csv");
// get_pixel_data();
// std::cout << pixel_data[0].size() << "\n";
// std::cout << result.size() << "\n";
// }

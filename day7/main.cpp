#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <bitset>
#include <cmath>

void convert_int_to_ternary(int input, std::string &result)
{
  if (input == 0)
  {
    if (result.empty())
      result += "0";
    return;
  }
  int x = input % 3;
  input /= 3;
  result.insert(0, std::to_string(x));
  convert_int_to_ternary(input, result);
}

bool is_valid(long int result, std::vector<int> input)
{
  int bitmask_size = input.size() - 1;
  int max = pow(3, bitmask_size);
  for (int i = 0; i < max; i++)
  {
    std::string ternary;
    convert_int_to_ternary(i, ternary);
    int num_zeros = bitmask_size - ternary.size();
    if (num_zeros > 0)
    {
      ternary.insert(0, num_zeros, '0');
    }
    long int tmp_result = input[0];
    for (int j = 0; j < ternary.size(); j++)
    {
      if (ternary[j] == '2')
      {
        tmp_result = std::stol(std::to_string(tmp_result) + std::to_string(input[j + 1]));
      }
      else if (ternary[j] == '1')
      {
        tmp_result = tmp_result * input[j + 1];
      }
      else
      {
        tmp_result += input [j + 1];
      }
    }
    if (tmp_result == result)
    {
      return true;
    }
  }
  return false;
}

int main() {

  long int result = 0;
  std::ifstream inputFile("input.txt");

  if (!inputFile.is_open())
  {
    std::cerr << "Error opening file!" << std::endl;
    return 1;
  }

  std::string line;

  while (std::getline(inputFile, line))
  {
    std::istringstream iss{line};
    std::string test_output_str;
    std::getline(iss, test_output_str, ':');
    long int test_output = std::stol(test_output_str);
    std::vector<int> test_input;
    std::string tmp;
    while(iss >> tmp)
    {
      test_input.push_back(std::stoi(tmp));
    }

    if(is_valid(test_output, test_input))
    {
      result += test_output;
    }
  }

  inputFile.close();

  std::cout << "Answer: " << result << std::endl;
  return 0;
}

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <queue>
#include <map>
#include <cmath>

int main() {
  std::ifstream inputFile("input.txt");

  if (!inputFile.is_open())
  {
    std::cerr << "Error opening file!" << std::endl;
    return 1;
  }

  std::string line;
  int num_safe = 0;

  while (std::getline(inputFile, line))
  {
    std::istringstream iss(line);
    std::vector<int> elements(std::istream_iterator<int>{iss}, {});
    bool increasing = false, decreasing = false, unsafe = false;

    for (int i = 0; i < elements.size() - 1; i++)
    {
      // Need to determine gradient of list
      if (!increasing || !decreasing)
      {
        if (elements[i] < elements[i + 1])
        {
          increasing = true;
        }
        if (elements[i] > elements[i + 1])
        {
          decreasing = true;
        }
      }
      // Make sure to break if equal
      if (elements[i] == elements[i + 1])
      {
        unsafe = true;
        break;
      }
      if (abs(elements[i] - elements[i + 1]) > 3)
      {
        unsafe = true;
        break;
      }

      // We already have gradient
      if (increasing && elements[i] > elements[i + 1])
      {
        unsafe = true;
        break;
      }
      else if (decreasing && elements[i] < elements[i + 1])
      {
        unsafe = true;
        break;
      }
    }

    if (!unsafe)
      num_safe++;
  }

  inputFile.close();

  std::cout << "Answer: " << num_safe << std::endl;
  return 0;
}

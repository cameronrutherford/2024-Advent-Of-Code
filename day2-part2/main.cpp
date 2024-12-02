#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <queue>
#include <map>
#include <cmath>

bool check_safety(const std::vector<int> &elements, bool recursive = false)
{
    bool increasing = false, decreasing = false, safe = true;

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
        safe = false;
        break;
      }
      if (abs(elements[i] - elements[i + 1]) > 3)
      {
        safe = false;
        break;
      }

      // We already have gradient
      if (increasing && elements[i] > elements[i + 1])
      {
        safe = false;
        break;
      }
      else if (decreasing && elements[i] < elements[i + 1])
      {
        safe = false;
        break;
      }
    }
    // Only want to try removing 1 element...
    // If we have recursively called this once, return true result
    if (!safe && !recursive)
    {
      // Otherwise, try removing each element to see if that makes it safe
      for (int i = 0; i < elements.size(); i++)
      {
        std::vector<int> new_elements;
        for (int j = 0; j < elements.size(); j++)
        {
          if (j != i)
          {
            new_elements.push_back(elements[j]);
          }
        }
        if (check_safety(new_elements, true))
        {
          return true;
        }
      }
    }
    return safe;
}

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
    if (check_safety(elements))
    {

      num_safe++;
    }
  }

  inputFile.close();

  std::cout << "Answer: " << num_safe << std::endl;
  return 0;
}

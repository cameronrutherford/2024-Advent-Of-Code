#include <iostream>
#include <format>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cassert>
#include <limits.h>

int main() {

  long int result = 0;
  std::ifstream inputFile("input.txt");

  if (!inputFile.is_open())
  {
    std::cerr << "Error opening file!" << std::endl;
    return 1;
  }

  std::string line;

  std::getline(inputFile, line);

  std::vector<char> data(line.begin(), line.end());

  std::vector<int> filesystem;

  bool file = true;
  int id = 0;

  for (auto c : data)
  {
    int curr_file;
    if (file)
    {
      curr_file = id;
      id++;
    }
    else
    {
      curr_file = -1;
    }
    for(int i = 0; i < c - '0'; i++)
    {
      filesystem.push_back(curr_file);
    }
    file = !file;
  }

  int curr_min = INT_MAX;

  for (int i = filesystem.size() - 1; i >= 0; i--)
  {
    if (filesystem[i] == -1)
      continue;

    // Get the length of the current file
    int curr = filesystem[i];
    if (curr < curr_min)
    {
      std::cout << std::format("curr = {}, curr_min = {}\n", curr, curr_min);
      curr_min = curr;
    }
    else
    {
      continue;
    }
    int len = 0;
    for (int j = i; j >= 0; j--)
    {
      if (filesystem[j] == curr)
      {
        len++;
      }
      else
      {
        break;
      }
    }
    // Try each new free space, through to the current file
    for (int j = 0; j <= i - 2 * len; j++)
    {
      if (filesystem[j] == -1)
      {
        bool flg = true;
        for (int k = j; k < j + len; k++)
        {
          if (filesystem[k] != -1)
          {
            flg = false;
            break;
          }
        }
        if(flg)
        {
          std::swap_ranges(filesystem.begin() + i - len + 1, filesystem.begin() + i + 1, filesystem.begin() + j);
          break;
        }
      }
    }
    // Move past the current file block since that failed
    i -= len - 1;
  }


  for (int i = 0; i < filesystem.size(); i++)
  {
    if (filesystem[i] == -1)
    {
      continue;
    }
    result += i * filesystem[i];
  }
  for (auto i : filesystem)
  {
    std::string to_print = (i == -1) ? "." : std::to_string(i);
    std::cout << to_print;
  }

  inputFile.close();

  std::cout << "\nAnswer: " << result << std::endl;
  return 0;
}

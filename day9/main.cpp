#include <iostream>
#include <format>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iterator>
#include <ranges>
#include <cassert>
#include <limits.h>

int main() {

  long int result = 0;
  std::ifstream inputFile("input-test.txt");

  if (!inputFile.is_open())
  {
    std::cerr << "Error opening file!" << std::endl;
    return 1;
  }

  std::string line;

  std::getline(inputFile, line);

  std::vector<char> data(line.begin(), line.end());

  // TODO: consider reformatting to use std:pair<int, int>
  // That way we track the file
  std::vector<std::pair<int, int>> filesystem;
  bool file = true;
  int id = 0;

  // Populating the filesystem with either the fileID or -1 for .
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
    filesystem.push_back(std::make_pair(curr_file, c - '0'));
    file = !file;
  }

  for (auto i : filesystem)
  {
    std::string to_print = (i.first == -1) ? "." : std::to_string(i.first);
    for (const int _ : std::views::iota(0,i.second))
    {
      std::cout << to_print;
    }
  }
  std::cout << std::endl;

  // Loop over all files in reverse
  for (auto const [x_idx, x] : filesystem | std::views::enumerate |
      std::views::filter([](auto pair) -> bool { return std::get<1>(pair).first != -1; }) | std::views::reverse)
  {
    // Iterate over the gaps in the system incrementally
    for(auto const [y_idx, y] : filesystem |
        std::views::enumerate |
        // Only if the gap is earlier in the filesystem than the file
        std::views::filter([&](auto&& pair)
          {
            auto ele = std::get<1>(pair);
            if (ele.first != -1)
            {
              return false;
            }
            for (auto test : filesystem)
            {
              if(test == ele)
                return true;
              if(test == x)
                return false;
            }
            return false;
          })
      )
    {
      // If the gap is big enough, move the chunk
      if (x.second < y.second)
      {
        std::cout << std::format("Trying to swap {} and {}\n", x.first, y.first);
        int size_remaining_after_move = y.second - x.second;

        y.second -= size_remaining_after_move + 1;

        auto x_val = x.first;

        // Fill the swapped file with -1s and clear
        filesystem[x_idx].first = -1;
        x.first = -1;

        filesystem.insert(filesystem.begin() + y_idx, std::make_pair(x_val, x.second));

        // "Compress" the empty spaces
        bool remove_prior = false;
        bool remove_next = false;
        if (filesystem[x_idx - 1].first == -1)
        {
          x.second += filesystem[x_idx - 1].second;
          remove_prior = true;
        }
        if (x_idx + 1 < filesystem.size() && filesystem[x_idx + 1].first == -1)
        {
          x.second += filesystem[x_idx + 1].second;
          remove_next = true;
        }
        if(remove_next)
        {
          filesystem.erase(filesystem.begin() + x_idx + 1);
        }
        if(remove_prior)
        {
          filesystem.erase(filesystem.begin() + x_idx - 1);
        }
        break;
      }
      // If the gap is precise, just swap
      else if (x.second == y.second)
      {
        std::cout << std::format("Trying to swap {} and {}\n", x.first, y.first);
        // Maybe this doesn't work
        auto tmp = x.first;
        x.first = y.first;
        y.first = std::move(tmp);
        break;
      }

    }
    // DEBUGGING
    for (auto i : filesystem)
    {
      std::string to_print = (i.first == -1) ? "." : std::to_string(i.first);
      for (const int _ : std::views::iota(0,i.second))
      {
        std::cout << to_print;
      }
    }
    std::cout << std::endl;
  }

  int index_counter = 0;
  for (auto x : filesystem)
  {
    if (x.first == -1)
    {
      index_counter += x.second;
      continue;
    }
    for (int i = 0; i < x.second; i++)
    {
      result += index_counter * x.first;
      index_counter++;
    }
  }
  for (auto i : filesystem)
  {
    std::string to_print = (i.first == -1) ? "." : std::to_string(i.first);
    for (const int _ : std::views::iota(0,i.second))
    {
      std::cout << to_print;
    }
  }

  inputFile.close();

  std::cout << "\nAnswer: " << result << std::endl;
  return 0;
}

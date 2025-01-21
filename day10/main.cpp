#include <iostream>
#include <format>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iterator>
#include <ranges>
#include <algorithm>
#include <cassert>
#include <limits.h>
#include <set>

std::set<std::pair<int,int>> num_reachable_nines(const std::vector<std::vector<int>>& map, std::pair<int, int> coords, int curr_val = 0)
{
  if(curr_val == 9)
    return {coords};

  std::set<std::pair<int,int>> reachable_nines = {};

  if(coords.first + 1 < map.size() && map[coords.first + 1][coords.second] == curr_val + 1)
  {
    auto extra_nines = num_reachable_nines(map, std::make_pair(coords.first + 1, coords.second), curr_val + 1);
    for (auto nine : extra_nines)
    {
      if(!reachable_nines.contains(nine))
      {
        reachable_nines.insert(nine);
      }
    }
  }
  if(coords.first - 1 >= 0 && map[coords.first - 1][coords.second] == curr_val + 1)
  {
    auto extra_nines = num_reachable_nines(map, std::make_pair(coords.first - 1, coords.second), curr_val + 1);
    for (auto nine : extra_nines)
    {
      if(!reachable_nines.contains(nine))
      {
        reachable_nines.insert(nine);
      }
    }
  }
  if(coords.second + 1 < map[0].size() && map[coords.first][coords.second + 1] == curr_val + 1)
  {
    auto extra_nines = num_reachable_nines(map, std::make_pair(coords.first, coords.second + 1), curr_val + 1);
    for (auto nine : extra_nines)
    {
      if(!reachable_nines.contains(nine))
      {
        reachable_nines.insert(nine);
      }
    }
  }
  if(coords.second - 1 >= 0 && map[coords.first][coords.second - 1] == curr_val + 1)
  {
    auto extra_nines = num_reachable_nines(map, std::make_pair(coords.first, coords.second - 1), curr_val + 1);
    for (auto nine : extra_nines)
    {
      if(!reachable_nines.contains(nine))
      {
        reachable_nines.insert(nine);
      }
    }
  }

  return reachable_nines;
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
  std::vector<std::vector<int>> map;

  while(std::getline(inputFile, line))
  {
    std::vector<char> data(line.begin(), line.end());
    map.push_back({});
    std::transform(data.begin(), data.end(), std::back_inserter(map.back()), [](char a) {return (int)a - '0';});
  }

  for (auto const& [row_idx, row] : map | std::views::enumerate)
  {
    for (auto const& [col_idx, ele]: row | std::views::enumerate)
    {
      if(ele == 0)
      {
        auto reachable_nines = num_reachable_nines(map, std::make_pair(row_idx,col_idx));
        std::cout << std::format("Trailhead at ({},{}) has a score of {}\n", row_idx, col_idx, reachable_nines.size());
        result += reachable_nines.size();
      }
    }
  }

  inputFile.close();

  std::cout << "\nAnswer: " << result << std::endl;
  return 0;
}

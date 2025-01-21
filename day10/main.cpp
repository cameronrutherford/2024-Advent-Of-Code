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

int num_paths_to_nine(const std::vector<std::vector<int>>& map, std::pair<int, int> coords, int curr_val = 0)
{
  if(curr_val == 9)
    return 1;

  int ret_val = 0;

  if(coords.first + 1 < map.size() && map[coords.first + 1][coords.second] == curr_val + 1)
    ret_val += num_paths_to_nine(map, std::make_pair(coords.first + 1, coords.second), curr_val + 1);
  if(coords.first - 1 >= 0 && map[coords.first - 1][coords.second] == curr_val + 1)
    ret_val += num_paths_to_nine(map, std::make_pair(coords.first - 1, coords.second), curr_val + 1);
  if(coords.second + 1 < map[0].size() && map[coords.first][coords.second + 1] == curr_val + 1)
    ret_val += num_paths_to_nine(map, std::make_pair(coords.first, coords.second + 1), curr_val + 1);
  if(coords.second - 1 >= 0 && map[coords.first][coords.second - 1] == curr_val + 1)
    ret_val += num_paths_to_nine(map, std::make_pair(coords.first, coords.second - 1), curr_val + 1);

  return ret_val;
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
        int score_of_trailhead = num_paths_to_nine(map, std::make_pair(row_idx,col_idx));
        std::cout << std::format("Trailhead at ({},{}) has a score of {}\n", row_idx, col_idx, score_of_trailhead);
        result += score_of_trailhead;
      }
    }
  }

  inputFile.close();

  std::cout << "\nAnswer: " << result << std::endl;
  return 0;
}

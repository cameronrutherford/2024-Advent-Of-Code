#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <utility>

int main() {

  long int result = 0;
  std::ifstream inputFile("input-test.txt");

  std::vector<std::vector<std::pair<char, bool>>> map;

  std::map<char, std::vector<std::pair<int,int>>> towers;

  if (!inputFile.is_open())
  {
    std::cerr << "Error opening file!" << std::endl;
    return 1;
  }

  std::string line;
  int y = 0;

  while (std::getline(inputFile, line))
  {
    map.push_back(std::vector<std::pair<char, bool>>());
    int x = 0;
    for (char c : line)
    {
      // Add character to map, default to no anode
      map.back().push_back(std::make_pair(c, false));
      // If tower key not in map, add to map with x,y coord
      if (c != '.')
      {
        towers.try_emplace(c, std::vector<std::pair<int,int>>());
        towers[c].push_back(std::make_pair(x,y));
      }
      x++;
    }
    y++;
  }

  // For each unique tower key
  for (const auto& [tower_char, locations] : towers)
  {
    // For each unique pair of coordinates
    for (int i = 0; i < locations.size(); i++)
    {
      for (int j = i + 1; j < locations.size(); j++)
      {
        // Generate anode pair
        // If anode is valid map coordinate
        // Set to true in map if not already true
        int x_dist = locations[i].first - locations[j].first;
        int y_dist = locations[i].second - locations[j].second;

        std::vector<std::pair<int,int>> anodes;
        int x1 = locations[i].first + x_dist;
        int y1 = locations[i].second + y_dist;
        anodes.push_back(std::make_pair(x1, y1));

        int x2 = locations[j].first - x_dist;
        int y2 = locations[j].second - y_dist;
        anodes.push_back(std::make_pair(x2, y2));

        for (auto anode : anodes)
        {
          if (anode.first >= 0 && anode.first < map[0].size() && anode.second >= 0 && anode.second < map.size())
          {
            if (!map[anode.second][anode.first].second)
            {
              map[anode.second][anode.first].second = true;
              result++;
            }
          }
        }
      }
    }
  }

  // Count true nodes in map

  inputFile.close();

  std::cout << "Answer: " << result << std::endl;
  return 0;
}
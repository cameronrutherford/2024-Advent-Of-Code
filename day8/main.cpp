#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <utility>

int main() {

  long int result = 0;
  std::ifstream inputFile("input.txt");

  // Stores all the grid squares to track existing anode squares
  std::vector<std::vector<std::pair<char, bool>>> map;

  // Stores a map from each tower char to the list of grid squares
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

  std::vector<std::pair<int,int>> anode_locations;
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

        int x1 = locations[i].first;
        int y1 = locations[i].second;
        int x2 = locations[j].first;
        int y2 = locations[j].second;

        while((x1 >= 0 && x1 < map[0].size() && y1 >= 0 && y1 < map.size())) 
        {
          anodes.push_back(std::make_pair(x1, y1));
          x1 += x_dist;
          y1 += y_dist;
        }
        while (x2 >= 0 && x2 < map[0].size() && y2 >= 0 && y2 < map.size())
        {
          anodes.push_back(std::make_pair(x2, y2));
          x2 -= x_dist;
          y2 -= y_dist;
        }

        for (auto anode : anodes)
        {
          if (!map[anode.second][anode.first].second)
          {
            map[anode.second][anode.first].second = true;
            anode_locations.push_back(std::make_pair(anode.first, anode.second));
            result++;
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

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <utility>
#include <set>

void rotate_90(std::pair<int, int> &direction)
{
  std::vector<std::pair<int, int>> rotation = {
    std::make_pair(0, -1),
    std::make_pair(1, 0),
    std::make_pair(0, 1),
    std::make_pair(-1, 0),
    std::make_pair(0,-1)
  };
  for (int i = 0; i < rotation.size(); i++)
  {
    if (rotation[i] == direction)
    {
      direction = rotation[i + 1];
      break;
    }
  }
}

bool make_move(int &result, std::pair<int ,int> &location, std::vector<std::vector<std::pair<char, bool>>> &map, std::pair<int, int> &direction)
{
  auto new_location = std::make_pair(location.first + direction.first, location.second + direction.second);

  if (new_location.first < 0 || new_location.first >= map[0].size())
  {
    return false;
  }
  if (new_location.second < 0 || new_location.second >= map.size())
  {
    return false;
  }

  if (map[new_location.second][new_location.first].first == '#')
  {
    rotate_90(direction);
    return make_move(result, location, map, direction);
  }
  else 
  {
    location = new_location;
    if (map[location.second][location.first].second == false)
    {
      result++;
      map[location.second][location.first].second = true;
    }
  }
  return true;
}

int main() {

  int result = 1;
  int real_result = 0;
  std::ifstream inputFile("input.txt");

  if (!inputFile.is_open())
  {
    std::cerr << "Error opening file!" << std::endl;
    return 1;
  }

  std::string line;
  int y_count = 0, x_pos, y_pos;
  std::vector<std::vector<std::pair<char, bool>>> map;

  while (std::getline(inputFile, line))
  {
    map.push_back({});
    int x_count = 0;
    for (auto c : line)
    {
      if (c == '^')
      {
        x_pos = x_count;
        y_pos = y_count;
        map[map.size() - 1].push_back(std::make_pair(c, true));
      }
      else
      {
        map[map.size() - 1].push_back(std::make_pair(c, false));
      }
      x_count++;
    }
    y_count++;
  }

  std::pair<int, int> direction = {0, -1};
  std::pair<int, int> position = {x_pos, y_pos};

  // Don't want to accidentally check the same element in the path twice
  std::set<std::pair<int,int>> path;

  while (true)
  {
    if(make_move(result, position, map, direction))
    {
      path.insert(position);
    }
    else
    {
      break;
    }
  }


  for (auto square : path)
  {
    direction = {0, -1};
    position = {x_pos, y_pos};
    auto tmp = map;
    tmp[square.second][square.first] = std::make_pair('#', false);
    bool loop = true;
    int length = 0;
    while (length <= tmp.size() * tmp[0].size())
    {
      if(make_move(result, position, tmp, direction))
      {
        length++;
      }
      else
      {
        loop = false;
        break;
      }
    }
    if (loop)
    {
      real_result++;
    }

  }

  inputFile.close();

  std::cout << "Answer: " << real_result << std::endl;
  return 0;
}

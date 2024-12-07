#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iterator>
#include <vector>
#include <ranges>
#include <map>
#include <set>

int main() {

  int result = 0;
  std::ifstream inputFile("input.txt");

  if (!inputFile.is_open())
  {
    std::cerr << "Error opening file!" << std::endl;
    return 1;
  }

  bool reading_rules = true;
  std::string line;
  std::map<int, std::vector<int>> rules;
  std::vector<std::vector<int>> updates;

  while (std::getline(inputFile, line))
  {
    std::istringstream iss{line};
    if (reading_rules)
    {
      if (line.empty())
      {
        reading_rules = false;
      }
      else
      {
        // Read into rules
        std::string key, value;
        std::getline(iss, key, '|');
        iss >> value;
        if (rules.contains(std::stoi(key)))
        {
          rules[std::stoi(key)].push_back(std::stoi(value));
        }
        else
        {
          rules[std::stoi(key)] = { std::stoi(value) };
        }
      }
    }
    else
    {
      // Read in potential updates
      std::vector<int> single_update;
      std::string ele;
      while (std::getline(iss, ele, ','))
      {
        single_update.push_back(std::stoi(ele));
      }
      updates.push_back(single_update);
    }
  }

  for (auto update : updates)
  {
    bool valid = true;
    for (int i = update.size() - 1; i >= 0; i--)
    {
      std::set<int> potential_conflicts(rules[update[i]].begin(), rules[update[i]].end());
      for (int j = i - 1; j >= 0; j--)
      {
        if (potential_conflicts.contains(update[j]))
        {
          valid = false;
          break;
        }
      }
      if (!valid)
      {
        break;
      }
    }
    if (valid)
    {
      result += *(update.begin() + update.size() / 2);
    }
  }
  // For update in updates
  //    if update is valid given rules
  //        result += middle of update

  inputFile.close();

  std::cout << "Answer: " << result << std::endl;
  return 0;
}

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iterator>
#include <vector>
#include <queue>
#include <ranges>
#include <algorithm>
#include <map>
#include <set>

bool is_valid(std::vector<int> update, std::map<int, std::vector<int>>& rules)
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
    return valid;
}

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
  std::vector<std::vector<int>> invalid_updates;

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
    if (!is_valid(update, rules))
    {
      invalid_updates.push_back(update);
    }
  }

  for (auto update : invalid_updates)
  {
    auto cmp = [&rules](int left, int right)
    { 
      if (std::find(rules[left].begin(), rules[left].end(), right) != rules[left].end())
      {
        return true;
      }
      else if (std::find(rules[right].begin(), rules[right].end(), left) != rules[right].end())
      {
        return false;
      }
      else
        return left < right;
    };
    std::priority_queue<
      int, 
      std::vector<int>, 
      decltype(cmp)
      >
    sorted_updates(cmp);
    for (auto ele : update)
      sorted_updates.push(ele);

    std::vector<int> sorted_vector_update;
    while (!sorted_updates.empty())
    {
      sorted_vector_update.push_back(sorted_updates.top());
      sorted_updates.pop();
    }
    result += *(sorted_vector_update.begin() + sorted_vector_update.size() / 2);
  }
  // For update in invalid_updates
  //    if update is valid given rules
  //        result += middle of update

  inputFile.close();

  std::cout << "Answer: " << result << std::endl;
  return 0;
}

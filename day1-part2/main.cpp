#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <queue>
#include <map>
#include <cmath>

int main() {
  std::ifstream inputFile("input.txt");

  if (!inputFile.is_open())
  {
    std::cerr << "Error opening file!" << std::endl;
    return 1;
  }

  std::string line;

  // Since we are maintaining a sorted structure here
  // Why not use a priority queue?
 
  std::priority_queue<int> left_list;
  std::map<int, int> right_list;

  // Everything in the input file is 2 space separated...
  while (std::getline(inputFile, line))
  {
    std::stringstream ss(line);
    int left_ele, right_ele;
    ss >> left_ele >> right_ele;
    left_list.push(left_ele);
    auto result_pair = right_list.insert( { right_ele, 1} );
    if (!result_pair.second)
    {
      result_pair.first->second++;
    }
  }

  int ret_val = 0;

  // Both lists have same number of elements, so just check left_list
  for(; !left_list.empty(); left_list.pop())
  {
    auto right_ele = right_list.find(left_list.top());
    if (right_ele == right_list.end())
    {
      continue;
    }
    ret_val += left_list.top() * right_ele->second;
  }

  inputFile.close();

  std::cout << "Answer: " << ret_val << std::endl;
  return 0;
}

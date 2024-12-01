#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <queue>
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
  
  std::priority_queue<int> left_list, right_list;

  // Everything in the input file is 2 space separated...
  while (std::getline(inputFile, line))
  {
    std::stringstream ss(line);
    int left_ele, right_ele;
    ss >> left_ele >> right_ele;
    left_list.push(left_ele);
    right_list.push(right_ele);
  }

  int ret_val = 0;

  // Both lists have same number of elements, so just check left_list
  for(; !left_list.empty(); left_list.pop(), right_list.pop())
  {
    ret_val += abs(left_list.top() - right_list.top());
  }

  inputFile.close();

  std::cout << "Answer: " << ret_val << std::endl;
  return 0;
}

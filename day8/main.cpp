#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

int main() {

  long int result = 0;
  std::ifstream inputFile("input.txt");

  if (!inputFile.is_open())
  {
    std::cerr << "Error opening file!" << std::endl;
    return 1;
  }

  std::string line;

  while (std::getline(inputFile, line))
  {
  }

  inputFile.close();

  std::cout << "Answer: " << result << std::endl;
  return 0;
}

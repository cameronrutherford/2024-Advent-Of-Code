#include <iostream>
#include <fstream>
#include <string>
#include <regex>

int main() {
  std::ifstream inputFile("input.txt");

  if (!inputFile.is_open())
  {
    std::cerr << "Error opening file!" << std::endl;
    return 1;
  }

  std::string line;
  int result = 0;

  while (std::getline(inputFile, line))
  {
    std::smatch res;
    std::regex rx("mul\\([0-9]+,[0-9]+\\)");
    std::string::const_iterator start = line.cbegin();
    while(std::regex_search(start, line.cend(), res, rx))
    {
      result += std::stoi(res[0].str().substr(4, res[0].str().find(',') - 4)) * std::stoi(res[0].str().substr(res[0].str().find(',') + 1, res[0].str().size() - res[0].str().find(',') - 2));
      start = res.suffix().first;
    }
  }

  inputFile.close();

  std::cout << "Answer: " << result << std::endl;
  return 0;
}

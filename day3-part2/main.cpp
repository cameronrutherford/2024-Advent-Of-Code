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
  bool do_set = true;

  while (std::getline(inputFile, line))
  {
    std::smatch res;
    std::regex rx("mul\\([0-9]+,[0-9]+\\)");
    std::regex do_rx("do\\(\\)");
    std::regex dont_rx("don't\\(\\)");
    std::string::const_iterator start = line.cbegin();
    // If dont() matches before the mul(), skip to next do()
    // Does this track across lines? - yes
    while(std::regex_search(start, line.cend(), res, rx))
    {
      if (do_set)
      {
        std::smatch temp;
        if(std::regex_search(start, line.cend(), temp, dont_rx) && 
            temp.suffix().first < res.suffix().first)
        {
          do_set = false;
          start = temp.suffix().first;
          continue;
        }
      }
      else if (!do_set)
      {
        std::smatch temp;
        if(std::regex_search(start, line.cend(), temp, do_rx))
        {
          do_set = true;
          start = temp.suffix().first;
          continue;
        }
        else
        {
          // No do remaining in this line
          break;
        }

      }
      std::string result_str = res[0].str();
      int comm_idx = result_str.find(',');
      int num1 = std::stoi(result_str.substr(4, comm_idx - 4));
      int num2 = std::stoi(result_str.substr(comm_idx + 1, result_str.size() - comm_idx - 2));
      result += num1 * num2;
      start = res.suffix().first;
    }
  }

  inputFile.close();

  std::cout << "Answer: " << result << std::endl;
  return 0;
}

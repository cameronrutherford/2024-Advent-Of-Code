#include <iostream>
#include <format>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ranges>
#include <algorithm>

void blink(std::vector<long>& stones)
{
  for (auto const& [stone_idx, stone] : stones | std::views::enumerate | std::views::reverse)
  {
    std::string stone_string = std::to_string(stones[stone_idx]);
    int stone_length = stone_string.length();
    if(stones[stone_idx] == 0)
    {
      stones[stone_idx] = 1;
    }
    else if(stone_length % 2 == 0)
    {
      std::string substr1 = stone_string.substr(0, stone_length / 2);
      stones[stone_idx] = std::stol(substr1);
      std::string substr2 = stone_string.substr(substr1.length());
      stones.insert(stones.begin() + stone_idx + 1, std::stol(substr2));
    }
    else
    {
      stones[stone_idx] = 2024 * stones[stone_idx];
    }
  }
}

int main() {
  std::ifstream inputFile("input.txt");

  if (!inputFile.is_open())
  {
    std::cerr << "Error opening file!" << std::endl;
    return 1;
  }

  std::string line;
  std::getline(inputFile, line);
  std::istringstream iss{line};
  std::string tmp;
  std::vector<long> stones({});
  while(iss >> tmp)
  {
    stones.push_back(std::stol(tmp));
  }

  for (auto const& [stone_idx, stone] : stones | std::views::enumerate)
  {
    std::cout << std::format("{} ", stone);
  }
  std::cout << std::endl;

  for (auto i : std::views::iota(0, 25))
    blink(stones);

  std::cout << "After 25 blinks\n";

  for (auto const& [stone_idx, stone] : stones | std::views::enumerate)
  {
    std::cout << std::format("{} ", stone);
  }
  std::cout << std::endl;

  inputFile.close();

  std::cout << "\nAnswer: " << stones.size() << std::endl;
  return 0;
}

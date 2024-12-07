#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector<std::pair<char, std::pair<int,int>>> get_neighbors(int x, int y, std::vector<std::vector<char>> rows)
{
  std::vector<std::pair<char, std::pair<int,int>>> result;
  // x + 1
  if (x + 1 < rows[0].size())
  {
    if (y + 1 < rows.size())
    {
      result.push_back(std::make_pair(rows[y + 1][x + 1], std::make_pair(x + 1, y + 1)));
    }
    result.push_back(std::make_pair(rows[y][x + 1], std::make_pair(x + 1, y)));
    if (y - 1 >= 0)
    {
      result.push_back(std::make_pair(rows[y - 1][x + 1], std::make_pair(x + 1, y - 1)));
    }
  }
  // x

  if (y + 1 < rows.size())
  {
    result.push_back(std::make_pair(rows[y + 1][x], std::make_pair(x, y + 1)));
  }
  if (y - 1 >= 0)
  {
    result.push_back(std::make_pair(rows[y - 1][x], std::make_pair(x, y - 1)));
  }


  // x - 1
  if (x - 1 >= 0)
  {
    if (y + 1 < rows.size())
    {
      result.push_back(std::make_pair(rows[y + 1][x - 1], std::make_pair(x - 1, y + 1)));
    }
    result.push_back(std::make_pair(rows[y][x - 1], std::make_pair(x - 1, y)));
    if (y - 1 >= 0)
    {
      result.push_back(std::make_pair(rows[y - 1][x - 1], std::make_pair(x - 1, y - 1)));
    }
  }
  return result;
}

int main() {

  int result = 0;
  std::ifstream inputFile("input-test.txt");

  if (!inputFile.is_open())
  {
    std::cerr << "Error opening file!" << std::endl;
    return 1;
  }

  std::vector<std::vector<char>> rows;
  std::string line;

  while (std::getline(inputFile, line))
  {
    rows.push_back(std::vector<char>());
    for (const char c : line)
      rows[rows.size() - 1].push_back(c);
  }
  int y = 0;

  for (auto const &row : rows)
  {
    int x = 0;
    for (auto c : row)
    {
      if (c == 'X')
      {
        auto c_neighbors = get_neighbors(x, y, rows);
        std::cout << "c : " << c << std::endl;
        for (auto c2 : c_neighbors)
        {
          if (c2.first == 'M')
          {
            std::cout << "c2 : " << c2.first << std::endl;
            auto c2_neighbors = get_neighbors(c2.second.first, c2.second.second, rows);
            for (auto c3 : c2_neighbors)
            {
              if (c3.first == 'A')
              {
                std::cout << "c3 : " << c3.first << std::endl;
                auto c3_neighbors = get_neighbors(c3.second.first, c3.second.second, rows);
                for (auto c4 : c3_neighbors)
                {
                  if (c4.first == 'S')
                  {
                    std::cout << "c4 : " << c4.first << std::endl;
                    result++;
                  }
                }
              }
            }
          }
        }
      }
      std::cout << "Found " << result << " matches as of row " << x + 1 << std::endl;
      x++;
    }
    std::cout << "Found " << result << " matches as of col " << y + 1 << std::endl;
    y++;
  }
  inputFile.close();

  std::cout << "Answer: " << result << std::endl;
  return 0;
}

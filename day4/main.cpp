#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector<char> get_x_neighbors(int x, int y, std::vector<std::vector<char>> rows)
{
  std::vector<char> result;
  // x - 1
  result.push_back(rows[y + 1][x - 1]);
  result.push_back(rows[y - 1][x - 1]);

  // x + 1
  result.push_back(rows[y + 1][x + 1]);
  result.push_back(rows[y - 1][x + 1]);

  return result;
}


int main() {

  int result = 0;
  std::ifstream inputFile("input.txt");

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
    if (y == 0 || y == rows.size() - 1)
    {
      y++;
      continue;
    }
    for (auto c : row)
    {
      if (x == 0 || x == row.size() - 1)
      {
        x++;
        continue;
      }
      if (c == 'A')
      {
        auto neighbors = get_x_neighbors(x, y, rows);
        if (neighbors[0] == 'M')
        {
          if (neighbors[1] == 'M' && neighbors[2] == 'S' && neighbors[2] == neighbors[3])
          {
            result++;
          }
          else if (neighbors[2] == 'M' && neighbors[1] == 'S' && neighbors[1] == neighbors[3])
          {
            result++;
          }

        }
        if(neighbors[0] == 'S')
        {
          if (neighbors[1] == 'S' && neighbors[2] == 'M' && neighbors[2] == neighbors[3])
          {
            result++;
          }
          else if (neighbors[2] == 'S' && neighbors[1] == 'M' && neighbors[1] == neighbors[3])
          {
            result++;
          }
        }
      }
      x++;
    }
    y++;
  }
  inputFile.close();

  std::cout << "Answer: " << result << std::endl;
  return 0;
}

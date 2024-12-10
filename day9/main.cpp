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

  std::getline(inputFile, line);

  std::vector<char> data(line.begin(), line.end());

  std::vector<int> filesystem;

  bool file = true;
  int id = 0;

  for (auto c : data)
  {
    int curr_file;
    if (file)
    {
      curr_file = id;
      id++;
    }
    else
    {
      curr_file = -1;
    }
    for(int i = 0; i < c - '0'; i++)
    {
      filesystem.push_back(curr_file);
    }
    file = !file;
  }

  int last_free_space = 0;
  for (int i = filesystem.size() - 1; i >= 0; i--)
  {
    if (filesystem[i] == -1)
      continue;

    // Get the next free space, and swap from the end
    for (;;)
    {
      if(filesystem[last_free_space] == -1)
      {
        break;
      }
      last_free_space++;
    }

    if (last_free_space > i)
    {
      break;
    }

    std::swap(filesystem[i], filesystem[last_free_space]);
    last_free_space++;

  }


  for (int i = 0; i < filesystem.size(); i++)
  {
    if (filesystem[i] == -1)
    {
      break;
    }
    result += i * filesystem[i];
  }
  for (auto i : filesystem)
  {
    std::string to_print = (i == -1) ? "." : std::to_string(i);
    std::cout << to_print;
  }

  inputFile.close();

  std::cout << "\nAnswer: " << result << std::endl;
  return 0;
}

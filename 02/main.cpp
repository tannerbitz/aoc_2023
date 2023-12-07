#include <fstream>
#include <iostream>
#include <string>
#include <vector>


int main()
{

  const auto fname = "inputs.txt";
  auto fs = std::fstream{};
  fs.open(fname);

  if (!fs.is_open()) {
    std::cout << "Failed to open inputs file.\n";
    exit(1);
  }

  std::vector<std::string> games;
  std::string tmp;
  while (!fs.eof())
  {
    std::getline(fs, tmp, '\n');
    games.push_back(tmp);
  }


}

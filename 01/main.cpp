#include <algorithm>
#include <fstream>
#include <iterator>
#include <string>
#include <cctype>
#include <iostream>
#include <optional>
#include <map>
#include <vector>

bool is_digit(char ch)
{
  return std::isdigit(static_cast<unsigned char>(ch));
}

struct ParsedVal
{
  int val;
  size_t idx;
};

bool index_less_than(const ParsedVal& lhs, const ParsedVal& rhs)
{
  return lhs.idx < rhs.idx;
}

auto first_digit(const std::string& line) -> ParsedVal
{
  const auto it = std::find_if(line.begin(), line.end(), &isdigit);
  ParsedVal val;
  val.val = std::stoi(std::string(1,*it));
  val.idx = std::distance(line.begin(), it);
  return val;
}

auto last_digit(const std::string& line) -> ParsedVal
{
  const auto it = std::find_if(line.rbegin(), line.rend(), &isdigit);
  ParsedVal val;
  val.val = std::stoi(std::string(1,*it));
  val.idx = line.size() - std::distance(line.rbegin(), it);
  return val;
}

auto first_spelled_digit(const std::string& line) -> std::optional<ParsedVal>
{
  static const std::map<std::string, int> spelled_digits = {
    { "one",    1   },
    { "two",    2   },
    { "three",  3   },
    { "four",   4   },
    { "five",   5   },
    { "six",    6   },
    { "seven",  7   },
    { "eight",  8   },
    { "nine",   9   },
    { "ten",    10  }
  };

  std::optional<ParsedVal> ret;
  for (const auto& [spelled_digit, val] : spelled_digits)
  {
    const auto idx = line.find(spelled_digit);
    if (idx != std::string::npos)
    {
      if (!ret.has_value())
      {
        ret = ParsedVal{val, idx};
      }
      else 
      {
        if (idx < ret->idx)
        {
          ret = ParsedVal{val, idx};
        }
      }
    }
  }

  return ret;
}

auto last_spelled_digit(const std::string& line) -> std::optional<ParsedVal>
{
  static const std::map<std::string, int> spelled_digits = {
    { "one",    1   },
    { "two",    2   },
    { "three",  3   },
    { "four",   4   },
    { "five",   5   },
    { "six",    6   },
    { "seven",  7   },
    { "eight",  8   },
    { "nine",   9   },
    { "ten",    10  }
  };

  std::optional<ParsedVal> ret;
  for (const auto& [spelled_digit, val] : spelled_digits)
  {
    const auto idx = line.rfind(spelled_digit);
    if (idx != std::string::npos)
    {
      if (!ret.has_value())
      {
        ret = ParsedVal{val, idx};
      }
      else 
      {
        if (idx > ret->idx)
        {
          ret = ParsedVal{val, idx};
        }
      }
    }
  }

  return ret;
}


int main()
{
  const std::string fname = "inputs.txt";  
  auto file = std::fstream();
  file.open(fname);

  if (!file.is_open())
  {
    std::cout << "Unable to open inputs file: " << fname << "\n";
    exit(1);
  }

  int val = 0;
  std::string line;
  while (std::getline(file, line, '\n')) {
    std::vector<ParsedVal> parsed_vals;
    parsed_vals.push_back(first_digit(line));
    parsed_vals.push_back(last_digit(line));
    
    const auto maybe_first_spelled_digit = first_spelled_digit(line);
    const auto maybe_last_spelled_digit  = last_spelled_digit(line);
    if (maybe_first_spelled_digit.has_value()) { parsed_vals.push_back(maybe_first_spelled_digit.value()); }
    if (maybe_last_spelled_digit.has_value())  { parsed_vals.push_back(maybe_last_spelled_digit.value()); }

    std::sort(parsed_vals.begin(), parsed_vals.end(), index_less_than);

    const int tens = parsed_vals.front().val;
    const int ones = parsed_vals.back().val;
    const int line_val = tens * 10 + ones;
    val += line_val;
  }

  std::cout << "The calibration value is: " << val << "\n"; 



}

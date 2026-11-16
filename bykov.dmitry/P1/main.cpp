#include <cctype>
#include <exception>
#include <iostream>
#include <stdexcept>
#include "sequence.hpp"

namespace bykov
{
  static int readInteger(std::istream& input)
  {
    int value = 0;
    if (!(input >> value))
    {
      throw std::invalid_argument("Input is not a sequence terminated by zero");
    }
    const int separator = input.peek();
    if (input.bad() || (!input.eof() && !std::isspace(static_cast< unsigned char >(separator))))
    {
      throw std::invalid_argument("Sequence elements must be integers separated by whitespace");
    }
    return value;
  }
}

int main()
{
  const int input_error = 1;
  const int calculation_error = 2;
  bykov::IncreasingRunCounter increasing;
  bykov::SignChangeCounter sign_changes;
  bool increasing_failed = false;
  bool signs_failed = false;
  try
  {
    int current = bykov::readInteger(std::cin);
    while (current != 0)
    {
      if (!increasing_failed)
      {
        try
        {
          increasing(current);
        }
        catch (const std::overflow_error& e)
        {
          increasing_failed = true;
          std::cerr << e.what() << "\n";
        }
      }
      if (!signs_failed)
      {
        try
        {
          sign_changes(current);
        }
        catch (const std::overflow_error& e)
        {
          signs_failed = true;
          std::cerr << e.what() << "\n";
        }
      }
      current = bykov::readInteger(std::cin);
    }
  }
  catch (const std::invalid_argument& e)
  {
    std::cerr << "Error: " << e.what() << "\n";
    return input_error;
  }
  catch (const std::exception& e)
  {
    std::cerr << "Error: " << e.what() << "\n";
    return calculation_error;
  }
  if (!increasing_failed)
  {
    std::cout << increasing() << "\n";
  }
  if (!signs_failed)
  {
    std::cout << sign_changes() << "\n";
  }
  if (!std::cout)
  {
    std::cerr << "Error: cannot write the results\n";
    return calculation_error;
  }
  return (increasing_failed || signs_failed) ? calculation_error : 0;
}

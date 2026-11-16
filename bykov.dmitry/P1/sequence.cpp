#include "sequence.hpp"
#include <cstddef>
#include <limits>
#include <stdexcept>

bykov::IncreasingRunCounter::IncreasingRunCounter():
  previous_(0),
  has_previous_(false),
  length_(0),
  maximum_(0)
{}

void bykov::IncreasingRunCounter::operator()(int next)
{
  if (next == 0)
  {
    throw std::invalid_argument("Zero is not a sequence element");
  }
  if (has_previous_ && next >= previous_)
  {
    if (length_ == std::numeric_limits< std::size_t >::max())
    {
      throw std::overflow_error("MON-INC: counter overflow");
    }
    ++length_;
  }
  else
  {
    length_ = 1;
  }
  if (length_ > maximum_)
  {
    maximum_ = length_;
  }
  previous_ = next;
  has_previous_ = true;
}

std::size_t bykov::IncreasingRunCounter::operator()() const
{
  return maximum_;
}

bykov::SignChangeCounter::SignChangeCounter():
  previous_(0),
  has_previous_(false),
  changes_(0)
{}

void bykov::SignChangeCounter::operator()(int next)
{
  if (next == 0)
  {
    throw std::invalid_argument("Zero is not a sequence element");
  }
  if (has_previous_ && ((next < 0) != (previous_ < 0)))
  {
    if (changes_ == std::numeric_limits< std::size_t >::max())
    {
      throw std::overflow_error("SGN-CHG: counter overflow");
    }
    ++changes_;
  }
  previous_ = next;
  has_previous_ = true;
}

std::size_t bykov::SignChangeCounter::operator()() const
{
  return changes_;
}

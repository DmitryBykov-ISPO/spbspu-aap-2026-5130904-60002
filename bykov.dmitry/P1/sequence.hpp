#ifndef SEQUENCE_HPP
#define SEQUENCE_HPP
#include <cstddef>

namespace bykov
{
  class IncreasingRunCounter
  {
  public:
    IncreasingRunCounter();
    void operator()(int next);
    std::size_t operator()() const;

  private:
    int previous_;
    bool has_previous_;
    std::size_t length_;
    std::size_t maximum_;
  };

  class SignChangeCounter
  {
  public:
    SignChangeCounter();
    void operator()(int next);
    std::size_t operator()() const;

  private:
    int previous_;
    bool has_previous_;
    std::size_t changes_;
  };
}

#endif

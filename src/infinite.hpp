#pragma once
#include <iterator>
#include <limits>

namespace gen {

template <class _Out, class _Gen> class infinite
{
  typedef infinite<_Out,_Gen> generator_type;
  _Gen _generator;
  _Out gen(std::size_t idx) const { return _generator(idx); }

public:
  infinite() : _generator() {}
  infinite(_Gen&& generator) : _generator(std::move(generator)) {}
  infinite(_Gen const& generator) : _generator(generator) {}

  infinite(generator_type&& other) : _generator(std::move(other._generator)) {}
  infinite(generator_type const& other) : _generator(other._generator) {}
  
  generator_type& operator=(generator_type&& other) { _generator = std::move(other._generator); return *this; }
  generator_type& operator=(generator_type const& other) { _generator = other._generator; return *this; }

  class const_iterator : public std::iterator<std::forward_iterator_tag, const _Out>
  {
    friend infinite<_Out, _Gen>;
    infinite<_Out, _Gen> const& container;
    std::size_t idx;
    explicit const_iterator(infinite<_Out, _Gen> const& container, std::size_t idx = std::numeric_limits<std::size_t>()) : container(container), idx(idx) {}
  
  public:
    const_iterator& operator++()
    {
      ++idx;
      return *this;
    }
    const_iterator operator++(int)
    {
      const_iterator ret = *this;
      ++(*this);
      return ret;
    }
    bool operator==(const_iterator other) const { return &container == &(other.container) && idx == other.idx; }
    bool operator!=(const_iterator other) const { return !(*this == other); }
    _Out operator*() const { return container.gen(idx); }
  };

  const_iterator begin() const { return const_iterator(*this, 0); }
  const_iterator end() const { return const_iterator(*this); }
};

template <class _Gen> decltype(auto) make_infinite(_Gen&& generator)
{
  return infinite<decltype(generator(std::size_t {})), _Gen>(std::forward<_Gen>(generator));
}

}


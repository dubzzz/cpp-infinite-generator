#include "gtest/gtest.h"
#include "../src/infinite.hpp"

#include <algorithm>
#include <vector>

TEST(Infinite, FromBeginning)
{
  auto infinite_stream = gen::make_infinite([](std::size_t i){ return i % 2; });
  std::size_t expected[] { 0, 1, 0, 1, 0, 1 };
  ASSERT_EQ(std::end(expected), std::mismatch(std::begin(expected), std::end(expected), infinite_stream.begin()).first);
}

TEST(Infinite, WithOffset)
{
  auto infinite_stream = gen::make_infinite([](std::size_t i){ return i % 3; });
  std::size_t expected[] { 2, 0, 1, 2, 0, 1 };
  ASSERT_EQ(std::end(expected), std::mismatch(std::begin(expected), std::end(expected), std::next(infinite_stream.begin(),2)).first);
}

TEST(Infinite, ReplayWithPureGenerator)
{
  auto infinite_stream = gen::make_infinite([](std::size_t i){ return i % 3; });
  std::size_t expected[] { 2, 0, 1, 2 };
  ASSERT_EQ(std::end(expected), std::mismatch(std::begin(expected), std::end(expected), std::next(infinite_stream.begin(),2)).first);
  ASSERT_EQ(std::end(expected), std::mismatch(std::begin(expected), std::end(expected), std::next(infinite_stream.begin(),2)).first);
}

struct PrimeGenerator
{
  static std::vector<unsigned long long> computed;
  unsigned long long operator()(std::size_t idx) const
  {
    while (computed.size() <= idx)
    {
      unsigned long long current = computed.empty() ? 2 : (computed.back() +1);
      while (std::find_if(computed.begin(), computed.end(), [current](unsigned long long prime){ return current % prime == 0; /*divisible by prime*/ }) != computed.end()) { ++current; }
      computed.push_back(current);
    }
    return computed[idx];
  }
};
std::vector<unsigned long long> PrimeGenerator::computed = {};

TEST(Infinite, PrimeGenerator)
{
  auto infinite_stream = gen::make_infinite<PrimeGenerator>();
  unsigned long long expected[] { 2, 3, 5, 7, 11, 13, 17 };
  ASSERT_EQ(std::end(expected), std::mismatch(std::begin(expected), std::end(expected), infinite_stream.begin()).first);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret { RUN_ALL_TESTS() };
  return ret;
}


#include "gtest/gtest.h"
#include "../src/infinite.hpp"

#include <algorithm>

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

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret { RUN_ALL_TESTS() };
  return ret;
}


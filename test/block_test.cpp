#include <blox/block.h>
#include <gtest/gtest.h>

namespace test {

TEST(block, equal) {
  auto a = blox::block("some data");
  auto b = blox::block("some other data");
  EXPECT_NE(a, b);
  b = blox::block(a.key(), b.data());  // make keys match
  EXPECT_EQ(a, b);
  b = blox::block(a.key());  // no data in block b
  EXPECT_EQ(a, b);
  auto a_copy = a;
  EXPECT_EQ(a_copy.key(), a.key());
  EXPECT_EQ(a_copy.data(), a.data());
  EXPECT_EQ(a, b);
  EXPECT_EQ(a, a);
  blox::block c{b};
  EXPECT_EQ(b, c);
  auto a_move = std::move(a);
  EXPECT_EQ(a_move, a_copy);
  std::ostringstream os;
  std::string_view a_key = static_cast<std::string_view>(a_move.key());
  for (uint8_t i : a_key) {
    os << std::hex << std::setfill('0') << std::setw(2);
    os << static_cast<int>(i);
  }
  EXPECT_EQ(
      "12201307990e6ba5ca145eb35e99182a9bec46531bc54ddf656a602c780fa0240dee",
      os.str());
}

TEST(block, empty) {
  auto block = blox::block("non-empty block");
  EXPECT_FALSE(block.empty());
}

TEST(block, set) {
  auto block_set = std::set<blox::block>{blox::block("a"), blox::block("b"),
                                         blox::block("c"), blox::block("d"),
                                         blox::block("a"), blox::block("b")};
  EXPECT_EQ(4u, block_set.size());
}

TEST(block, store) {
  auto map = std::map<std::string_view, std::string_view>{};
  auto block = blox::block("some data");
  auto inserted = map.insert(block);
  EXPECT_TRUE(inserted.second);
  EXPECT_NE(map.end(), inserted.first);
  auto it = map.find(block.key());
  EXPECT_NE(map.end(), it);
  EXPECT_EQ(block, *it);
}

}  // namespace test
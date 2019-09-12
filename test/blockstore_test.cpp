#include <blox/block.h>
#include <gtest/gtest.h>
#include <map>

namespace test {

struct blockstore : public testing::Test {
  std::map<std::string_view, std::string_view> datastore;
};

TEST_F(blockstore, insert) {
  auto block = blox::block("my data");
  datastore.insert(block);
  EXPECT_EQ(1, datastore.size());
  EXPECT_FALSE(datastore.empty());
  EXPECT_NE(datastore.end(), datastore.find(block.key()));
  EXPECT_EQ(1, datastore.erase(block.key()));
  EXPECT_EQ(datastore.end(), datastore.find(block.key()));
  EXPECT_TRUE(datastore.empty());
  EXPECT_EQ(0, datastore.size());
}

TEST_F(blockstore, iteration) {
  auto input = std::set<blox::block>{blox::block{"a"}, blox::block{"b"},
                                     blox::block{"c"}};
  std::copy(input.begin(), input.end(),
            std::inserter(datastore, datastore.end()));
  EXPECT_EQ(input.size(), datastore.size());
  EXPECT_TRUE(std::equal(input.begin(), input.end(), datastore.begin(),
                         datastore.end()));
}

}  // namespace test
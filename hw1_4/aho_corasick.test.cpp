#include <gtest/gtest.h>

#include "aho_corasick.cpp"

using namespace AC;

// TEST(ExampleTests, DemonstrateGTestMacros) {

//     AhoCorasick ac;
//     EXPECT_EQ(ac.add(2,2),4);
// }

TEST(AhoCorasickTests, TestConstructor){
    Node n;
    EXPECT_FALSE(n.getParent());
}

// TEST(AhoCorasickTests, TestRoot){
//     AhoCorasickTri ac;
//     EXPECT_EQ(ac.getRoot()->getLeftChild(), 'A');
// }
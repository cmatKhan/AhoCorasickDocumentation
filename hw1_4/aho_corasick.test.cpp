#include <gtest/gtest.h>
// #include <gmock/gmock.h>

#include "aho_corasick.cpp"
// #include "aho_corasick.h"

using namespace AC;

// mocks


//NODE TESTS

//constructor

TEST(NodeTests, testConstructorDefault){
    // Node n1, n2, n3, n4, n5, n6, n7, n8, n9, n10;

    // Edge n1e

    // n1e.insert( )
    Node n;

    // EXPECT_FALSE(n.outLink());
    // EXPECT_EQ(n.patternIndicator(), 0);
    // EXPECT_EQ(n.distFromRoot(), 0);
    EXPECT_FALSE(n.failureLink());
}

//EDGE TESTS

//constructor

//constructor

//insert

//updateFinalPtr

//search

//AHO CORASICK TRIE

//constructor

//getRoot

//insert

//findNv

//search

// TEST(ExampleTests, DemonstrateGTestMacros) {

//     AhoCorasick ac;
//     EXPECT_EQ(ac.add(2,2),4);
// }

// TEST(AhoCorasickTests, TestConstructor){
    // Node n;
    // EXPECT_FALSE(n.getParent());
// }

// TEST(AhoCorasickTests, TestRoot){
    // AhoCorasickTri ac;
    // EXPECT_EQ(ac.getRoot()->getLeftChild(), 'A');
// }
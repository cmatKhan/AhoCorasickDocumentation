#include <gtest/gtest.h>
// #include <gmock/gmock.h>

#include "aho_corasick.h"
// #include "aho_corasick.h"

using namespace AC;

// mocks


//NODE TESTS

//constructor

TEST(NodeTests, testConstructorDefault){
    Edge e{};
    Node n{&e};

    Node* o = n.outLink();
    int p = n.patternIndicator();
    int x = n.distFromRoot();
    Node* f = n.failureLink();

    EXPECT_FALSE(o);
    EXPECT_EQ(p, -1);
    EXPECT_EQ(x, -1);
    EXPECT_FALSE(f);
}

// failureLink()

TEST(NodeTests, failureLink){
    Edge edge_head1{}, edge_head2{}, edge_head3{}, eh4{};
    Node test_node{&edge_head1}, n1{&edge_head2}, n2{&edge_head3};
    
    Edge e1{nullptr, 'a', &n1}, e2{nullptr, 'b', &n2};

    test_node.insertEdge(&e1);
    test_node.insertEdge(&e2);

    Node* f = test_node.failureLink();
    // the failure link should be nullptr at this point
    EXPECT_FALSE(f);

    // set the failure link and see if the right pointer comes out
    Node fl{&eh4};
    test_node.setFailureLink(&fl);
    EXPECT_EQ(test_node.failureLink(), &fl);



}

TEST(NodeTest, edgeSearch){

    Edge edge_head1{}, edge_head2{}, edge_head3{};
    Node test_node{&edge_head1}, n1{&edge_head2}, n2{&edge_head3};
    
    Edge e1{nullptr, 'a', &n1}, e2{nullptr, 'b', &n2};

    test_node.insertEdge(&e1);
    test_node.insertEdge(&e2);

    Node* search_out1 = test_node.edgeSearch('b');

    Node* search_out2 = test_node.edgeSearch('z');

    // test that the right tri_node is returned with a char matches
    EXPECT_EQ(search_out1, &n2);
    // test that nullptr is returned when no match
    EXPECT_FALSE(search_out2);

}

// dist_from_root

TEST(NodeTests, distFromRoot){
    Edge edge_head{};
    Node n{&edge_head};
    n.setDistFromRoot(3);

    EXPECT_EQ(n.distFromRoot(), 3);
    
}

// pattern indicator
TEST(NodeTest, patternIndicator){

    Edge edge_head1{}, edge_head2{}, edge_head3{};
    Node test_node{&edge_head1}, n1{&edge_head2}, n2{&edge_head3};
    
    n2.setPatternIndicator(3);
    test_node.setPatternIndicator(1);

    Edge e1{nullptr, 'a', &n1}, e2{nullptr, 'b', &n2};

    test_node.insertEdge(&e1);
    test_node.insertEdge(&e2);

    int pattern1 = test_node.edgeSearch('b')->patternIndicator();

    int pattern2 = test_node.edgeSearch('a')->patternIndicator();

    EXPECT_EQ(pattern1, 3);

    EXPECT_EQ(pattern2, -1);

    EXPECT_EQ(test_node.patternIndicator(), 1);
}

// out link

TEST(NodeTest, outLink){

    Edge edge_head1{}, edge_head2{}, edge_head3{}, eh4{};
    Node test_node{&edge_head1}, n1{&edge_head2}, n2{&edge_head3}, n3{&eh4};
    
    n2.setPatternIndicator(3);
    test_node.setPatternIndicator(1);

    Edge e1{nullptr, 'a', &n1}, e2{nullptr, 'b', &n2};

    test_node.insertEdge(&e1);
    test_node.insertEdge(&e2);

    EXPECT_FALSE(test_node.outLink());

    test_node.setOutLink(&n3);

    EXPECT_EQ(test_node.outLink(), &n3);

}

//EDGE TESTS

//constructor
TEST(EdgeTests, testEdgeConstructorNull){
    
    Edge e{};
    
    Edge* ne = e.nextEdge();
    Node* tn = e.trieNode();
    char l = e.label();
    
    EXPECT_FALSE(ne);
    EXPECT_FALSE(tn);
    EXPECT_EQ(l, '\0');
    
}

//constructor
TEST(EdgeTests, testEdgeConstructorFull){

    Edge edge_head{};
    Node n{&edge_head};
    n.setDistFromRoot(3);
    Edge e2;

    Edge e(&e2,'a',&n);
    
    Edge* ne = e.nextEdge();
    Node* tn = e.trieNode();
    char l = e.label();
    
    EXPECT_EQ(ne, &e2);
    EXPECT_EQ(tn, &n);
    EXPECT_EQ(l, 'a');

}
// next edge
TEST(EdgeTest, nextEdge){
    Edge e1{}, e2{};
    e1.setNextEdge(&e2);

    EXPECT_EQ(e1.nextEdge(), &e2);
}

// edge label
TEST(EdgeTest, label){
    Edge e1{};
    e1.setEdgeLabel('a');
    EXPECT_EQ(e1.label(), 'a');
}

// trie node
TEST(EdgeTest, trieNode){
    Edge e1{}, e2{};
    Node n1{&e1};

    e1.setTrieNode(&n1);

    EXPECT_EQ(e1.trieNode(), &n1);
}

//AHO CORASICK TRIE

//constructor

//constructor

//getRoot

//insert

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
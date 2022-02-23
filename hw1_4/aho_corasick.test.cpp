#include <gtest/gtest.h>
// #include <gmock/gmock.h>

#include "aho_corasick.cpp"
#include "aho_corasick.h"

using namespace AC;

// mocks

// NODE TESTS

TEST(NodeTests, edgeSearch)
{

    ACTrie a {};

    char p1[] = "test";
    int p1_label = 1;

    char p2[] = "temp";
    int p2_label = 2;

    a.insert(p1, p1_label,2);
    a.insert(p2, p2_label,2);

    Node* e_node
        = a.getRoot()->edgeSearch('t')->trieNode()->edgeSearch('e')->trieNode();

    char m_edge_label = e_node->edgeHead()->label();
    char s_edge_label = e_node->edgeHead()->nextEdge()->label();

    Node* m_edge_node = e_node->edgeHead()->trieNode();
    Node* s_edge_node = e_node->edgeHead()->nextEdge()->trieNode();

    Node* m_edgeSearch_result = e_node->edgeSearch('m')->trieNode();
    Node* s_edgeSearch_result = e_node->edgeSearch('s')->trieNode();

    EXPECT_EQ(m_edge_label, 'm');
    EXPECT_EQ(s_edge_label, 's');
    EXPECT_EQ(m_edge_node, m_edgeSearch_result);
    EXPECT_EQ(s_edge_node, s_edgeSearch_result);
}

// test failure link node function
TEST(NodeTests, failureLink)
{

    ACTrie a {};

    char p1[] = "test";
    int p1_label = 1;

    char p2[] = "temp";
    int p2_label = 2;

    char p5[] = "mp";
    int p5_label = 5;

    a.insert(p1, p1_label,2);

    a.insert(p2, p2_label,2);

    a.insert(p5, p5_label,2);

    Node* first_m_node = a.getRoot()->edgeSearch('m')->trieNode();

    Node* p_node = a.getRoot()
                       ->edgeSearch('t')
                       ->trieNode()
                       ->edgeSearch('e')
                       ->trieNode()
                       ->edgeSearch('m')
                       ->trieNode()
                       ->edgeSearch('p')
                       ->trieNode();

    Node* fl_before = p_node->edgeSearch('i')->trieNode();

    // before setting the final link, the trie node attribute should be nullptr
    EXPECT_FALSE(fl_before);

    p_node->setFailureLink(&first_m_node);

    Node* p_after = a.getRoot()
                        ->edgeSearch('t')
                        ->trieNode()
                        ->edgeSearch('e')
                        ->trieNode()
                        ->edgeSearch('m')
                        ->trieNode()
                        ->edgeSearch('p')
                        ->trieNode()
                        ->edgeSearch('i')
                        ->trieNode();

    // after setting the failure link, the trie node pointer should go where
    // expected
    EXPECT_EQ(first_m_node, p_after);
}

// dist_from_root
TEST(NodeTests, distFromRoot)
{
    ACTrie a {};

    char p1[] = "test";
    int p1_label = 1;

    char p2[] = "temp";
    int p2_label = 2;

    char p5[] = "mp";
    int p5_label = 5;

    a.insert(p1, p1_label,2);

    a.insert(p2, p2_label,2);

    a.insert(p5, p5_label,2);

    int p1_t_node_dist = a.getRoot()
                             ->edgeSearch('t')
                             ->trieNode()
                             ->edgeSearch('e')
                             ->trieNode()
                             ->edgeSearch('s')
                             ->trieNode()
                             ->edgeSearch('t')
                             ->trieNode()
                             ->distFromRoot();

    int te_e_node_dist = a.getRoot()
                             ->edgeSearch('t')
                             ->trieNode()
                             ->edgeSearch('e')
                             ->trieNode()
                             ->distFromRoot();

    int p5_p_node_dist = a.getRoot()
                             ->edgeSearch('m')
                             ->trieNode()
                             ->edgeSearch('p')
                             ->trieNode()
                             ->distFromRoot();

    EXPECT_EQ(p1_t_node_dist, 4);
    EXPECT_EQ(te_e_node_dist, 2);
    EXPECT_EQ(p5_p_node_dist, 2);
}

TEST(ACTrieTests, constructor)
{
    ACTrie a {};

    EXPECT_FALSE(a.getRoot()->edgeHead()->nextEdge());
}

TEST(ACTrieTests, insert)
{
    ACTrie a {};

    char p1[] = "test";
    int p1_label = 1;

    char p2[] = "temp";
    int p2_label = 2;

    char p3[] = "te";
    int p3_label = 3;

    char p4[] = "em";
    int p4_label = 4;

    char p5[] = "mp";
    int p5_label = 5;

    a.insert(p1, p1_label,2);

    int pattern_indicator_check1 = a.getRoot()
                                       ->edgeSearch('t')
                                       ->trieNode()
                                       ->edgeSearch('e')
                                       ->trieNode()
                                       ->edgeSearch('s')
                                       ->trieNode()
                                       ->edgeSearch('t')
                                       ->trieNode()
                                       ->patternIndicator();

    a.insert(p2, p2_label,2);

    // TODO: ERROR HANDLING ON SEARCHING FOR A PATTERN THAT DNE
    int pattern_indicator_check2 = a.getRoot()
                                       ->edgeSearch('t')
                                       ->trieNode()
                                       ->edgeSearch('e')
                                       ->trieNode()
                                       ->edgeSearch('m')
                                       ->trieNode()
                                       ->edgeSearch('p')
                                       ->trieNode()
                                       ->patternIndicator();

    a.insert(p3, p3_label,2);

    a.insert(p3, p3_label,2);
    int pattern_indicator_check3 = a.getRoot()
                                       ->edgeSearch('t')
                                       ->trieNode()
                                       ->edgeSearch('e')
                                       ->trieNode()
                                       ->patternIndicator();

    a.insert(p4, p4_label,2);

    int pattern_indicator_check4 = a.getRoot()
                                       ->edgeSearch('e')
                                       ->trieNode()
                                       ->edgeSearch('m')
                                       ->trieNode()
                                       ->patternIndicator();

    a.insert(p5, p5_label,2);

    int pattern_indicator_check5 = a.getRoot()
                                       ->edgeSearch('m')
                                       ->trieNode()
                                       ->edgeSearch('p')
                                       ->trieNode()
                                       ->patternIndicator();

    EXPECT_EQ(pattern_indicator_check1, p1_label);
    EXPECT_EQ(pattern_indicator_check2, p2_label);
    EXPECT_EQ(pattern_indicator_check3, p3_label);
    EXPECT_EQ(pattern_indicator_check4, p4_label);
    EXPECT_EQ(pattern_indicator_check5, p5_label);
}

// cite: https://stackoverflow.com/a/58369622/9708266
class SearchStreamTest : public ::testing::Test {
protected:
    SearchStreamTest()
        : sbuf { nullptr }
    {
        // intentionally empty
    }

    ~SearchStreamTest() override = default;

    // Called before each unit test
    void SetUp() override
    {
        // Save cout's buffer...
        sbuf = std::cout.rdbuf();
        // Redirect cout to our stringstream buffer or any other ostream
        std::cout.rdbuf(buffer.rdbuf());
    }

    // Called after each unit test
    void TearDown() override
    {
        // When done redirect cout to its old self
        std::cout.rdbuf(sbuf);
        sbuf = nullptr;
    }

    // The following objects can be reused in each unit test

    // This can be an ofstream as well or any other ostream
    std::stringstream buffer {};
    // Save cout's buffer here
    std::streambuf* sbuf;
};

TEST(ACTrie, findNv)
{
    ACTrie a {};

    char p1[] = "potato";
    int p1_label = 1;

    char p2[] = "tatter";
    int p2_label = 2;

    char p3[] = "at";
    int p3_label = 3;

    a.insert(p1, p1_label,2);
    a.insert(p2, p2_label,2);
    a.insert(p3, p3_label,2);

    a.findNv();

    Node* potat_node_fl = a.getRoot()
                              ->edgeSearch('p')
                              ->trieNode()
                              ->edgeSearch('o')
                              ->trieNode()
                              ->edgeSearch('t')
                              ->trieNode()
                              ->edgeSearch('a')
                              ->trieNode()
                              ->edgeSearch('t')
                              ->trieNode()
                              ->failureLink();

    Node* tat_node = a.getRoot()
                         ->edgeSearch('t')
                         ->trieNode()
                         ->edgeSearch('a')
                         ->trieNode()
                         ->edgeSearch('t')
                         ->trieNode();

    Node* tat_node_fl = tat_node->failureLink();

    Node* at_node
        = a.getRoot()->edgeSearch('a')->trieNode()->edgeSearch('t')->trieNode();

    EXPECT_EQ(potat_node_fl, tat_node);
    EXPECT_EQ(tat_node_fl, at_node);
}

TEST(ACTrie, outLink1)
{

    ACTrie a{};

    char p1[] = "potato";
    int p1_label = 1;

    char p2[] = "tatter";
    int p2_label = 2;

    char p3[] = "at";
    int p3_label = 3;

    a.insert(p1, p1_label,2);
    a.insert(p2, p2_label,2);
    a.insert(p3, p3_label,2);

    a.findNv();

    Node* potat_outlink = a.getRoot()
                              ->edgeSearch('p')
                              ->trieNode()
                              ->edgeSearch('o')
                              ->trieNode()
                              ->edgeSearch('t')
                              ->trieNode()
                              ->edgeSearch('a')
                              ->trieNode()
                              ->edgeSearch('t')
                              ->trieNode()
                              ->outLink();

    Node* at_node
        = a.getRoot()->edgeSearch('a')->trieNode()->edgeSearch('t')->trieNode();

    EXPECT_EQ(potat_outlink, at_node);
}

TEST(ACTrieTest, outlink2)
{
    ACTrie a{};

    char p1[] = "test";
    int p1_label = 1;

    char p2[] = "temp";
    int p2_label = 2;

    char p3[] = "te";
    int p3_label = 3;

    char p4[] = "em";
    int p4_label = 4;

    char p5[] = "mp";
    int p5_label = 5;

    a.insert(p1, p1_label,2);
    a.insert(p2, p2_label,2);
    a.insert(p3, p3_label,2);
    a.insert(p4, p4_label,2);
    a.insert(p5, p5_label,2);

    // set failure links
    a.findNv();

    Node* temp_outlink = a.getRoot()
                             ->edgeSearch('t')
                             ->trieNode()
                             ->edgeSearch('e')
                             ->trieNode()
                             ->edgeSearch('m')
                             ->trieNode()
                             ->edgeSearch('p')
                             ->trieNode()
                             ->outLink();

    Node* mp_node
        = a.getRoot()->edgeSearch('m')->trieNode()->edgeSearch('p')->trieNode();

    EXPECT_EQ(temp_outlink, mp_node);
    EXPECT_EQ(temp_outlink->patternIndicator(), 5);
}

TEST(ACTrieTest, testpatternindicator)
{
    ACTrie a{};

    char p1[] = "test";
    int p1_label = 1;

    char p2[] = "temp";
    int p2_label = 2;

    char p3[] = "te";
    int p3_label = 3;

    char p4[] = "em";
    int p4_label = 4;

    char p5[] = "mp";
    int p5_label = 5;

    a.insert(p1, p1_label,2);
    a.insert(p2, p2_label,2);
    a.insert(p3, p3_label,2);
    a.insert(p4, p4_label,2);
    a.insert(p5, p5_label,2);

    // set failure links
    a.findNv();

    int mp_pi = a.getRoot()
                    ->edgeSearch('m')
                    ->trieNode()
                    ->edgeSearch('p')
                    ->trieNode()
                    ->patternIndicator();

    EXPECT_EQ(mp_pi, 5);
}

TEST_F(SearchStreamTest, searchWithFile)
{
    ACTrie a{};

    char p1[] = "test";
    int p1_label = 1;

    char p2[] = "temp";
    int p2_label = 2;

    char p3[] = "te";
    int p3_label = 3;

    char p4[] = "em";
    int p4_label = 4;

    char p5[] = "mp";
    int p5_label = 5;

    a.insert(p1, p1_label,1);
    a.insert(p2, p2_label,1);
    a.insert(p3, p3_label,1);
    a.insert(p4, p4_label,1);
    a.insert(p5, p5_label,1);

    a.findNv();
    a.search("/home/oguzkhan/class/bioseq/assignments/hw1/homework-1-problem-4-cmatKhan/data/test3.fa");

    std::string actual { buffer.str() };
    std::string expected {
        "1,5,1\n5,3,1\n5,1,1\n11,5,1\n15,3,1\n16,4,1\n15,2,1\n17,5,1\n"
    };
    

    EXPECT_EQ(expected, actual);
}
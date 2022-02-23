#include "aho_corasick.h"
#include <algorithm>
#include <cassert>
#include <cctype>
#include <filesystem>
#include <forward_list>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <stdio.h>
#include <stdlib.h>

using std::cerr;
using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::vector;

using namespace AC;
/**
 * @brief implement the AhoCorasick Trie interface
 *
 */
class ACTrie : public AhoCorasickTrie {

    /**
     * @brief pointer to a Node obj; the root of the Trie
     *
     */
    Node* root;

public:
    /**
     * @brief Construct a new ACTrie object. There is a Edge object instantiated
     *   and set such that root has an attribute pointer edge_head that points
     * to it.
     *
     */
    ACTrie()
    { // instantiate new edge object
        Edge* new_edge = new Edge {};
        // instantiate node with edge_head pointing to edge obj
        Node* n1 = new Node { &new_edge };
        // set root to point at node obj
        root = n1;
    }

    Node* getRoot() override { return (root); }

    void insert(string pattern, int label, int strand) override
    {
        // TODO check uniqueness of pattern (I guess search trie for the
        // pattern)
        //  first?

        // set pointer to walk around the trie
        Node* curr_node = root;
        // instantiate int to walk along pattern
        int i = 0;
        // walk along the pattern
        while (pattern[i] != NULL) {
            // while there are edges out of curr_node with the appropriate char
            // go to that node
            Edge* curr_edge = curr_node->edgeSearch(pattern[i]);
            if (curr_edge->label() == pattern[i]) {
                curr_node = curr_edge->trieNode();
                // else, start adding nodes and edges
            } else {
                Edge* new_edge = new Edge {};
                Node* n = new Node { &new_edge };

                curr_node = curr_node->insertEdge(&n, pattern[i]);
                curr_node->setDistFromRoot(i + 1);
            }
            // iterate to the next char in pattern
            i++;
        }
        // at the final char of pattern, set the curr_node pattern indicator
        // to the pattern's label
        curr_node->setPatternIndicator(label);
        curr_node->setStrand(strand);
    }

    void findNv() override
    {
        // instantiate pointers l1 and l2 to forward_list which will store
        // TrieNode pointers
        std::forward_list<Node*>* l1 = new std::forward_list<Node*>;
        std::forward_list<Node*>* l2 = new std::forward_list<Node*>;

        // instantiate pointers to use to walk along the Trie
        Node* parent;
        Edge* current_edge;
        Node* child;
        char current_edge_label;
        // pointer to a failure link
        Node* fl;
        // pointer to an out_link
        Node* out_link;

        // set root failure link to itself
        root->setFailureLink(&root);
        // push root onto l1
        l1->push_front({ root });

        // the main algorithm starts at level 2
        // while l1 is not empty
        while (!l1->empty()) {
            // iterate over l1
            for (; !l1->empty(); l1->pop_front()) {
                // pop the front node and set parent to point at it
                parent = l1->front();
                current_edge = parent->edgeHead();
                // iterate over the children while they exist
                while (current_edge->nextEdge()) {
                    // parent's failure link
                    fl = parent->failureLink();
                    // set x to char on edge
                    current_edge_label = current_edge->label();
                    // get the child along along a given labelled path
                    child = current_edge->trieNode();
                    // while fl doesn't have an edge with char x and
                    // fl isn't the root, walk back up the tree via failure
                    // links
                    while (
                        !fl->edgeSearchBool(current_edge_label) && fl != root) {
                        fl = fl->failureLink();
                    }
                    // fl can't be equal to the parent -- this should only be
                    // the case for level 2. TODO check this
                    if (fl->edgeSearchBool(current_edge_label)
                        && fl != parent) {
                        // if the failure link found above has an edge labelled
                        // x, then set the corresponding node to the failure
                        // link
                        fl = fl->edgeSearch(current_edge_label)->trieNode();
                        // set the child's failure link to the fl described
                        // above
                        child->setFailureLink(&fl);
                    } else {
                        child->setFailureLink(&root);
                    }
                    // if the failure link is a node with a pattern,
                    // set it as the out_link of the node in question
                    if (child->failureLink()->patternIndicator() != -1) {
                        out_link = child->failureLink();
                        child->setOutLink(&out_link);
                    } else {
                        // else set the current node out_link to the
                        // outlink of the failure link, which is either
                        // nullptr or a pointer to another node which is
                        // labelled with a pattern
                        out_link = child->failureLink()->outLink();
                        child->setOutLink(&out_link);
                    }

                    // add the child to l2
                    // if (edge_list->trieNode()) {
                    l2->push_front({ child });
                    // }
                    // move onto parent's next edge (which is the 'next edge'
                    // of the child edge obj)
                    current_edge = current_edge->nextEdge();
                }
            }
            // set l1 to point to l2
            l1 = l2;
            // set l2 to point at a new forward linked list
            l2 = new std::forward_list<Node*>;
        }
    }

    void search(string target_filepath) override
    {
        vector<char> bytes;

        FILE* input_file = fopen(target_filepath.c_str(), "r");
        if (input_file == nullptr) {
            cout << 'target_filepath DNE' << std::endl;
            exit(EXIT_FAILURE);
        }

        unsigned char t_c = getc(input_file);
        // set t_c to lower
        t_c = tolower(t_c);

        // instantiate an int to store the number of bases that may be
        // skipped when a mismatch or a leaf node is reached
        int l = 0;
        // instantiate an int to track movement along the target sequence
        int c = 0;
        // instantiate a node pointer to be used to move around the Trie
        Node* w = root;
        // instantiate node pointer to be used to follow out_links
        Node* out_link;
        // search the target for exact matches to strings in the Trie
        do {

            // while there is an edge (w,w') labelled t_c
            while (w->edgeSearch(t_c)->label() == t_c && t_c != NULL) {
                // if w' is numbered by a pattern
                if (w->edgeSearch(t_c)->trieNode()->patternIndicator() != -1) {
                    std::cout
                        << (c + 1)
                            - (w->edgeSearch(t_c)->trieNode()->distFromRoot()
                                - 1)
                        << ","
                        << w->edgeSearch(t_c)->trieNode()->patternIndicator()
                        << ',' << w->edgeSearch(t_c)->trieNode()->strand()
                        << std::endl;
                }
                // report also if there is a directed path of failure links
                // from w' to a numbered node
                out_link = w->edgeSearch(t_c)->trieNode()->outLink();
                while (out_link) {
                    std::cout << (c + 1) - (out_link->distFromRoot() - 1) << ","
                              << out_link->patternIndicator() << ','
                              << out_link->strand() << std::endl;
                    out_link = out_link->outLink();
                }

                // the final edge in the edge list for each node has a
                // pointer to which trie node at which the search for
                // matches should resume
                w = w->edgeSearch(t_c)->trieNode();
                // increment the counter to the next char
                c++;
                t_c = getc(input_file);
            }
            w = w->failureLink();
            // if t_c does not have a edge out of root, go to the next char
            if (w == root && !w->edgeSearchBool(t_c)) {
                c++;
                t_c = getc(input_file);
            }
            // continue until the target string is exhausted
        } while (!feof(input_file));
    }
    // std::cout << my_character;
    // if (my_character == '\n') {
    //     ++number_of_lines;
    // }
};

// copied from https://stackoverflow.com/a/33075573/9708266
char complement(char n)
{
    switch (n) {
    case 'A':
        return 't';
    case 'T':
        return 'a';
    case 'G':
        return 'c';
    case 'C':
        return 'g';
    case 'a':
        return 't';
    case 't':
        return 'a';
    case 'g':
        return 'c';
    case 'c':
        return 'g';
    }
    assert(false);
    return ' ';
}

int main(int argc, char* argv[])
{

    // path to target
    std::string pattern_file(argv[1]);
    // path to patterns
    std::string target_file(argv[2]);

    // didn't know how else to check that file exists
    FILE* input_file1 = fopen(pattern_file.c_str(), "r");
    if (input_file1 == nullptr) {
        cout << "pattern file does not exist at that path";
        exit(EXIT_FAILURE);
    }
    fclose(input_file1);

    FILE* input_file2 = fopen(target_file.c_str(), "r");
    if (input_file2 == nullptr) {
        cout << "target file does not exist at that path";
        exit(EXIT_FAILURE);
    }
    fclose(input_file2);

    cout << "creating Trie..." << std::endl;
    ACTrie a {};

    std::fstream newfile;
    newfile.open(pattern_file, std::ios::in);
    if (newfile.is_open()) {
        string pattern;
        int i = 1;
        while (std::getline(newfile, pattern)) {
            cout << "inserting pattern: " << pattern << std::endl;
            a.insert(pattern, i, 1);
            // reverse the string
            reverse(pattern.begin(), pattern.end());
            // get the complement
            transform(begin(pattern), end(pattern), begin(pattern), complement);
            cout << "and its reverse complement: " << pattern << std::endl;
            a.insert(pattern, i, 2);
            i++;
        }
        newfile.close();
    }
    // find the failure links and out links
    cout << "Setting failure links and out links..." << std::endl;
    a.findNv();
    cout << "Searching the target for pattern matches..." << std::endl;
    // search the file
    cout << "target_location, pattern, strand" << std::endl;
    a.search(target_file);
}

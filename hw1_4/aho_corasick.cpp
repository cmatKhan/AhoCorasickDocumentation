#include "aho_corasick.h"
#include <iostream>

using namespace AC;

class ACTrie : public AhoCorasickTrie {

    Node* root;

public:
    ACTrie()
    {
        Edge* new_edge = new Edge {};
        Edge* new_edge2 = new Edge {};
        Edge* new_edge3 = new Edge {};

        Node* n1 = new Node { &new_edge };

        root = n1;
    }

    Node* getRoot() override { return (root); }

    void insert(char pattern[], int label) override
    {

        Node* curr_node = root;
        int i = 0;

        while (pattern[i] != NULL) {
            Edge* curr_edge = curr_node->edgeSearch(pattern[i]);
            if (curr_edge->label() == pattern[i]) {
                curr_node = curr_edge->trieNode();
            } else {
                Edge* new_edge = new Edge {};
                Node* n = new Node { &new_edge };

                curr_node = curr_node->insertEdge(&n, pattern[i]);
                curr_node->setDistFromRoot(i + 1);
            }

            i++;
        }

        curr_node->setPatternIndicator(label);

        int t = 0;
    }

    void updateFinalTrieNode(Node** n) override { }

    void findNv() override { }

    void search(char t[]) override
    {
        int l = 0;
        int c = 0;
        Node* w = root;
        do {
            while (w->edgeSearch(t[c])->label() == t[c] && t[c] != NULL) {
                if (w->edgeSearch(t[c])->trieNode()->patternIndicator() != -1) {
                    std::cout
                        << (c+1) - (w->edgeSearch(t[c])->trieNode()->distFromRoot()-1)
                        << ","
                        << w->edgeSearch(t[c])->trieNode()->patternIndicator()
                        << ',' << 1 << std::endl;
                }
                // to go next node
                w = w->edgeSearch(t[c])->trieNode();
                c++;
            }
            w = root;
            if (w == root && !w->edgeSearch(t[c])->trieNode()) {
                c++;
            }
            l = c;

        } while (t[c] != NULL);
    }
};

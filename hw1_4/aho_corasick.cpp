#include "aho_corasick.h"

using namespace AC;

/**
 * @brief Construct a new Edge:: Edge object with a label.
 * 
 * @param c 
 */
Edge::Edge(char c){
    this->next = nullptr;
    this->label = c;
}

void Edge::insertAfter(Edge* new_edge){
    new_edge->next = this->next;
    this->next = new_edge;
}


Node::Node() {
    this->parent = nullptr;
};

Node *Node::getParent(){
    return(this->parent);
}

AhoCorasickTri::AhoCorasickTri(){
    Node n;
    this->root = &n;
}

Node *AhoCorasickTri::getRoot(){
    return(this->root);
}
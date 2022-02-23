#ifndef ac_h
#define ac_h

#include <string>
using std::string;

/** Namespace of Aho Corasick implementation for HW1_4.
 *  This contains the class aho_corasick, an implementation of
 *  the Aho Corasick algorithm described in Dan Gusfield's
 *  "Algorithms on Strings, Trees and Sequences". This note serves as a
 *  general citation: a good deal of the code in this project is copied
 *  from Gusfield.
 *
 */
namespace AC {
// forward declare classes in namespace
class Node;
class Edge;

/**
 * @brief list of edge_head out of a trie node. A forward linked list
 * which will store edge_head out of a given trie node.
 *
 * cite: c++ crash course by Josh Lospinoso
 */
class Edge {
    /**
     * @brief pointer to next edge in list.
     * Default constructor should initialize this to nullptr.
     *
     */
    Edge* next_edge;

    /**
     * @brief pointer to a TrieNode
     *
     */
    Node* trie_node;

    /**
     * @brief label of the edge between parent and next node.
     *
     */
    char edge_label;

public:
    /**
     * @brief Construct a new Edge object.
     * next_edge and trie_node are set to nullptr. label is set to '\0',
     * a character not intended to match anything in string
     */
    Edge()
    {
        next_edge = nullptr;
        trie_node = nullptr;
        edge_label = '\0';
    }

    /**
     * @brief Construct a new Edge object.
     * next_edge and trie_node are set to nullptr. label is set to '\0',
     * a character not intended to match anything in string
     *
     * @param n a double ptr to a node obj.
     */
    Edge(Node** n)
    {
        next_edge = nullptr;
        trie_node = *n;
        edge_label = '\0';
    }

    /**
     * @brief Construct a new Edge object with attributes filled.
     *
     * @param e pointer to an Edge object.
     * @param l a char label for the edge.
     * @param n pointer to a Node object.
     */
    Edge(Edge* e, char l, Node* n)
    {
        // set attributes
        next_edge = e;
        trie_node = n;
        edge_label = l;
    }

    /**
     * @brief Set the next_edge attribute.
     *
     * @param e a pointer to an Edge object.
     */
    void setNextEdge(Edge* e) { next_edge = e; }

    /**
     * @brief Get the pointer stored in attribute next_edge.
     *
     * @return the Edge pointer stored in this->next_edge.
     */
    Edge* nextEdge() { return (next_edge); }

    /**
     * @brief Set the the label attribute
     *
     * @param l a char representing the edge label
     */
    void setEdgeLabel(char l) { edge_label = l; }

    /**
     * @brief get the label attribute.
     *
     * @return the char in the label attribute.
     */
    char label() { return (edge_label); }

    /**
     * @brief Set the trie_node attribute
     *
     * @param tn a double pointer to a trie node
     */
    void setTrieNode(Node** tn) { trie_node = *tn; }
    /**
     * @brief getter for the trie_node attribute.
     *
     * @return a Node pointer.
     */
    Node* trieNode() { return (trie_node); }
};

/** A Tri Node. This is intended to be used in the
 *  AhoCorasick Tri structure.
 *
 */
class Node {
    /**
     * @brief pointer to the node reachable by the fewest failure links, if
     *   one exists. Default constructor should set this to nullptr.
     */
    Node* out_link;
    /**
     * @brief pointer to first edge object. Edge objects may be used to
     * construct a forward linked list. Each edge object has an attribute
     * label which stores the char representing the labe from the current
     * node to the next node.
     *
     */
    Edge* edge_head;
    /**
     * @brief an int representing one of the input patterns in the Trie.
     * Default constructor should set this to zero, indicating a given Node
     * does not represent an input pattern.
     *
     */
    int pattern;
    /**
     * @brief strand of the pattern match. strand is 1 for forward and 2 for
     *   reverse
     *
     */
    int pattern_strand;
    /**
     * @brief distance from the root node.
     * This will be used as the value by which the aho corasick search
     * algorithm may 'skip' the pattern forward.
     *
     */
    int dist_from_root;

    /**
     * @brief iterate over edge list to find final edge. Use public
     *   functions failureLink() and setFailureLink() to set the trie_node
     *   attribute of the final edge
     *
     * @return a pointer to the final edge
     */
    Edge* finalEdge()
    {
        Edge* e = edge_head;
        while (e->nextEdge()) {
            // update e
            e = e->nextEdge();
        }
        return (e);
    }

public:
    /**
     * @brief Construct a new Node object
     *
     * @param e a double pointer to an Edge obj
     */
    Node(Edge** e)
    {
        out_link = nullptr;
        edge_head = *e;
        pattern = -1;
        dist_from_root = -1;
    }

    /**
     * @brief get the first edge in the edge list
     *
     * @return pointer to an edge obj
     */
    Edge* edgeHead() { return (edge_head); }

    /**
     * @brief add new edge to the beginning of the list
     *
     * @param trie_node a double ptr to a new Node object. This will be
     *   used to set the trie_node pointer attribute in the new edge.
     * @param l a character with which to label the new edge.
     *
     * @return a pointer to the trie_node of the new edge
     */
    Node* insertEdge(Node** trie_node, char l)
    {
        // I had such a hard time figuring this out. The solution to this
        // mess of a namespace was to use double pointers
        // from
        // https://www.geeksforgeeks.org/linked-list-set-2-inserting-a-node/
        // push()
        Edge* new_edge = new Edge {};

        new_edge->setTrieNode(trie_node);

        new_edge->setNextEdge(edge_head);

        new_edge->setEdgeLabel(l);

        edge_head = new_edge;

        return (new_edge->trieNode());
    }

    /**
     * @brief get pointer to node at which search() should resume at
     *   mismatch.
     * The final edge object in edge_head will point to the node at which
     * search() should resume. The default value of next is nullptr, which
     * should be used to signify search() should resume at root.
     *
     * @return The Node pointer found in the final edge object in edge_head
     */
    Node* failureLink()
    {
        Edge* e = finalEdge();
        return (e->trieNode());
    }

    /**
     * @brief Set the the failure link. The final edge in the edge_list
     *   stores either trie_node nullptr or a pointer to the node where a
     *   search of the Trie should resume.
     *
     * @param tn a Node pointer.
     */
    void setFailureLink(Node** tn)
    {
        Edge* e = finalEdge();
        e->setTrieNode(tn);
    }

    /**
     * @brief Search the edge list for a given character.
     * If an edge with a given char label exists, return the pointer
     * to that node in the Trie. NOTE: a reference will always be returned.
     * Make sure the final edge in the Edgelist stores the trie_node
     * reference to the 'failure link'.
     *
     * @param c a character with which to search the labels of the edge
     * list
     *
     * @return a reference to a Node. NOTE: a reference to a Node will
     * always be returned. Make sure the last node in the edge list points
     * to the 'failure link'.
     */
    Edge* edgeSearch(char c)
    {
        Edge* e = edge_head;
        while (e->nextEdge() && c != e->label()) {
            e = e->nextEdge();
        }

        return (e);
    }
    /**
     * @brief search the edge list for a char, return boolean.
     *
     * @param c a character with which to search the edge list
     * @return a boolean. true if an edge matching the input character is found,
     *   false otherwise
     */
    bool edgeSearchBool(char c)
    {
        if (!this) {
            return false;
        } else {
            bool found = false;
            Edge* e = edge_head;
            if (e) {
                while (e->nextEdge()) {
                    if (e->label() == c & !found) {
                        found = true;
                    }
                    e = e->nextEdge();
                }
            }

            return (found);
        }
    }

    /**
     * @brief Set the Dist From Root object
     *
     * @param d an integer representing the number of nodes from root.
     *
     */
    void setDistFromRoot(int d) { dist_from_root = d; }

    /**
     * @brief getter for dist_from_root.
     *
     * @return an integer representing the number of nodes from root.
     */
    int distFromRoot() { return (dist_from_root); }

    /**
     * @brief Set the pattern_indicator attribute.
     * pattern_indicator is default 0, indicating no pattern.
     *
     * @param p the integer used to refer to a given pattern
     */
    void setPatternIndicator(int p) { pattern = p; }

    /**
     * @brief Get the pattern_indicator attribute
     *
     * @return an int signifying the index of the pattern
     */
    int patternIndicator() { return (pattern); }

    /**
     * @brief Set the strand of the pattern
     *
     * @param s an int. 1 for forward (or same direction as input), 2 for
     *   reverse
     */
    void setStrand(int s) { pattern_strand = s; }

    /**
     * @brief return the strand of the pattern
     *
     * @return int
     */
    int strand()
    {
        // TODO: NEED ERROR CHECKING. SHOULDN'T REPORT STRAND IF NO PATTERN
        return (pattern_strand);
    }

    /**
     * @brief Set the out_link attribute
     *
     * @param n a pointer to a Node
     */
    void setOutLink(Node** n) { out_link = *n; }

    /**
     * @brief get attribute out_link
     *
     * @return pointer to the out_link node
     */
    Node* outLink() { return (out_link); }
};

/**
 * @brief AhoCorasick Trie algorithm implementation.
 *
 */
class AhoCorasickTrie {

public:
    virtual ~AhoCorasickTrie() = default;

    /**
     * @brief Get the reference to the root node of the Trie.
     *
     * @return Node* reference to root node
     */
    virtual Node* getRoot() = 0;

    /**
     * @brief Insert a pattern into the tri.
     * This function inserts both the input pattern as well as its reverse
     * complement.
     *
     * @param pattern a string to enter into the trie.
     * @param pattern_index the pattern identifier. This is what will be
     *   emitted when match is found.
     * @param strand 1 for forward (or the same direction as in the pattern file
     *  and 2 for reverse complement)
     */
    virtual void insert(string pattern, int pattern_index, int strand) = 0;

    /**
     * @brief Set the failure_links and output_links.
     *
     * Conduct a breadth first traversal over the nodes in the Trie. The
     * final node in the edge list will hold the pointer to the node which
     * the search() algorithm moves to when no match is found. nullptr
     * signifies that search() should resume at root. Otherwise, update the
     * final node.next to point to the appropriate node in the trie.
     *
     */
    virtual void findNv() = 0;

    /**
     * @brief Using the tri, search a target.
     *
     * @param target_filepath a path to a file containing a string
     */
    virtual void search(string target_filepath) = 0;
};

}

#endif /* ac_h */
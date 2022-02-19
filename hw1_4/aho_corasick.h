#ifndef ac_h
#define ac_h

/** Namespace of Aho Corasick implementation for HW1_4. 
 *  This contains the class aho_corasick, an implementation of 
 *  the Aho Corasick algorithm described in Dan Gusfield's 
 *  "Algorithms on Strings, Trees and Sequences". This note serves as a 
 *  general citation: a good deal of the code in this project is copied 
 *  from Gusfield.
 * 
 */
namespace AC
{
    // forward declare classes in namespace
    class Node;
    class EdgeList;
    class AhoCorasick;

    /** A Tri Node. This is intended to be used in the 
     *  AhoCorasick Tri structure.
     *  
     * 
     */
    class Node
    {

        Node* parent;
        Node* failure_link;
        Node* out_link;
        Node* left_node;
        Node* right_node;
        Edge* edges;
        int pattern_indicator, dist_from_root;

        public:
          /**
           * @brief Construct a new Node object
           * 
           */
          Node();
          /**
           * @brief Get the Parent object
           * 
           * @return Node* reference to parent
           */
          Node *getParent();
          /**
           * @brief Get the Left Child object
           * 
           * @return the character on (this, left_node) edge
           */
          char getLeftChild();
          /**
           * @brief Set the Left Child object
           * 
           * @param c a character to set on the edge between (this, left_node) 
           */
          void setLeftChild(char c);
    };

    /**
     * @brief list of edges out of a trie node. A forward linked list 
     * which will store edges out of a given trie node. 
     * 
     * cite: c++ crash course by Josh Lospinoso 
     */
    class Edge
    {
        Edge* next;
        char label;
        public:
          /**
           * @brief Construct a new Edge List object without a label.
           * 
           */
          Edge();
          /**
           * @brief Construct a new Edge object with a label
           * 
           * @param c a character with which to label the edge 
           */
          Edge(char c);
          /**
           * @brief Insert another Edge in the forward linked list.
           * 
           * @param new_edge an Edge object 
           */
          void insertAfter(Edge* new_edge);
          /**
           * @brief search the edge list for a given character.
           * 
           * @param c a character with which to search the edge list
           * 
           * @return a reference to a node with the appropriate label, or 
           *   nullptr if none found
           */
          void findEdge(char c);
    };

    /** test docs for my_class. extended docs for my_class
     * 
     *  
     * 
     */
    class AhoCorasickTri
    {
        Node* root;

    public:
        /**
         * @brief Construct a new Aho Corasick object
         * 
         */
        AhoCorasickTri();
        /**
         * @brief Get the Root object
         * 
         * @return Node* reference to root node
         */
        Node *getRoot();
        /**
         * @brief Insert a pattern into the tri 
         * 
         * @param pattern a string to enter into the tri
         */
        void insert(char pattern[]);
        /**
         * @brief Update the failure links in the tri 
         * 
         * @param n a node for which to calculate failure links 
         */
        void findNv(Node n);
        /**
         * @brief Using the tri, search a target. Search will be done both 
         * forward and reverse complement.
         *  
         * 
         * @param target a target string to search 
         */
        void search(char target[]);
    };

}

#endif /* ac_h */
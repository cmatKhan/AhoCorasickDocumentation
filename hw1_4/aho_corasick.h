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
    class Edge;

    /**
     * @brief list of edges out of a trie node. A forward linked list 
     * which will store edges out of a given trie node. 
     * 
     * cite: c++ crash course by Josh Lospinoso 
     */
    class Edge
    {
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
          Edge(){
              next_edge = nullptr;
              trie_node = nullptr;
              edge_label = '\0';
          }

          /**
           * @brief Construct a new Edge object with attributes filled.
           * 
           * @param e pointer to an Edge object.
           * @param l a char label for the edge.
           * @param n pointer to a Node object.
           */
        //   Edge(Edge* e, char l, Node* n){
        //       // set attributes
        //       next_edge = e;
        //       trie_node = n;
        //       edge_label = l;
              
        //   }

          /**
           * @brief Set the next_edge attribute.
           * 
           * @param e a pointer to an Edge object. 
           */
          void setNextEdge(Edge* e){
              next_edge = e;
          }

          /**
           * @brief Get the pointer stored in attribute next_edge.
           * 
           * @return the Edge pointer stored in this->next_edge. 
           */
          Edge* nextEdge(){
              return(next_edge); 
          }

          /**
           * @brief Set the the label attribute
           * 
           * @param l a char representing the edge label 
           */
          void setEdgeLabel(char l){
              edge_label = l;
          }

          /**
           * @brief get the label attribute. 
           * 
           * @return the char in the label attribute. 
           */
          char label(){
              return(edge_label);
          }

          /**
           * @brief Set the trie_node attribute
           * 
           * @param tn a pointer to a trie node  
           */
          void setTrieNode(Node* tn){
              trie_node = tn;
          }

          Node* trieNode(){
              return(this->trie_node);
          }

          /**
           * @brief Insert another Edge in the forward linked list.
           * 
           * @param l insert a new node into the edge list with label char c.
           */
        //   void insert(char l, Node* n){
            //   Edge e(nextEdge(), l, n);
              // set the current edge to point to the new edge
            //   setNextEdge(&e);
        //   }

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
          Node* search(char c){
              Edge* e = this;
              while (e->nextEdge() && c != e->label())
              {
                  e = e->nextEdge();
              }
              
              return(e->trieNode());
              
          }
    };

    /** A Tri Node. This is intended to be used in the 
     *  AhoCorasick Tri structure.
     *  
     */
    class Node
    {
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
        Edge* edges;
        /**
         * @brief an int representing one of the input patterns in the Trie. 
         * Default constructor should set this to zero, indicating a given Node 
         * does not represent an input pattern. 
         * 
         */
        int pattern;
        /**
         * @brief distance from the root node. 
         * This will be used as the value by which the aho corasick search 
         * algorithm may 'skip' the pattern forward. 
         * 
         */
        int dist_from_root;

        public:
          /**
           * @brief Construct a new null Node object.
           * pattern and dist_from_root are initialized to 0.
           * 
           */
          Node(){
              Edge e;
              out_link = nullptr;
              edges = &e;
              pattern = 0;
              dist_from_root = 0;
          }
          /**
           * @brief Construct a new Node with pattern and dist_from_root set.
           * 
           * @param p an int, numeric pattern identifier
           * @param d an int, the number of nodes from root.
           */
          Node(int p, int d){
              Edge e;
              out_link = nullptr;
              edges = &e;
              pattern = p;
              dist_from_root = d;
          }
          
          /**
           * @brief get pointer to node at which search() should resume at 
           *   mismatch. 
           * The final edge object in edges will point to the node at which 
           * search() should resume. The default value of next is nullptr, which 
           * should be used to signify search() should resume at root.
           * 
           * @return The Node pointer found in the final edge object in edges
           */
          Node* failureLink(){
              // pointer to first edge node
              Edge e = *edges;
              // while e.next is not nullptr
              while (e.nextEdge()){
                  // update e
                  e = *e.nextEdge();
              }
              return(e.trieNode());
          }
          
          /**
           * @brief Set the Dist From Root object
           * 
           * @param d an integer representing the number of nodes from root.
           * 
           */
          void setDistFromRoot(int d){
              dist_from_root = d;
          }

          /**
           * @brief getter for dist_from_root. 
           * 
           * @return an integer representing the number of nodes from root. 
           */
          int distFromRoot(){
              return(dist_from_root);
          }

          /**
           * @brief Set the pattern_indicator attribute.
           * pattern_indicator is default 0, indicating no pattern.
           * 
           * @param p the integer used to refer to a given pattern
           */
          void setPatternIndicator(int p){
              pattern = p;
          }

          /**
           * @brief Get the pattern_indicator attribute
           * 
           * @return an int signifying the index of the pattern
           */
          int patternIndicator(){
              return(pattern);
          }
          
          /**
           * @brief Set the out_link attribute
           * 
           * @param n a pointer to a Node
           */
          void setOutLink(Node* n){
              out_link = n;
          }
          
          /**
           * @brief get attribute out_link
           * 
           * @return pointer to the out_link node 
           */
          Node* outLink(){
              return(out_link);
          }
    };


    /**
     * @brief AhoCorasick Trie algorithm implementation. 
     * 
     */
    class AhoCorasickTrie
    {
        /**
         * @brief pointer to a Node object to use as the root of the Trie. 
         * 
         */
        Node* root;

    public:
        /**
         * @brief Construct a new AhoCorasickTrie object. 
         * Initiate the ACT with a root node.
         * 
         */
        AhoCorasickTrie();

        /**
         * @brief Get the reference to the root node of the Trie.
         * 
         * @return Node* reference to root node
         */
        Node *getRoot();

        /**
         * @brief Insert a pattern into the tri. 
         * This function inserts both the input pattern as well as its reverse 
         * complement.
         * 
         * @param pattern a string to enter into the trie.
         * @param pattern_index the pattern identifier. This is what will be 
         *   emitted when match is found.
         */
        void insert(char pattern[], int pattern_index);

        /**
         * @brief Update the final edge's next attribute. 
         * This is intended to be used to update the final node.next to point 
         * to the node in the Trie where the search algorithm should resume
         * 
         * @param nv a pointer to another node in the Trie  
         * 
         */
        void updateFinalTrieNode(Node *nv);

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
        void findNv();

        /**
         * @brief Using the tri, search a target. 
         *  
         * @param target a target string to search 
         */
        void search(char target[]);
    };

}

#endif /* ac_h */
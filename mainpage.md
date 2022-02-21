# Introduction

I made a somewhat large blunder. This is the first time I have programmed 
in c++, and it went __very__ __very__ badly. I had working Node and Edge 
objects early on. With those, I had expected the Aho Corasick Trie 
functions to be somewhat straight forward to implement. However, in 
doing so, I ran into issues with pointers that I wasn't able to resolve.  

For what it is worth, learning how to write __formal__ tests, and create 
__formal__ documentation is important to me. I have not written a single line 
of c++ prior to this assignment, and have not used googletests (the test 
suite) or Doxygen (the documentation generator) before, either. What the 
formality is telling me right now is that I have an enormous misunderstanding 
of namespace and object life cycle that I need to resolve quite quickly.  

# How to use this site

At the top, you'll notice a navigator bar. More or less, clicking any of the 
drop downs will bring you to an interface where you can view the objects 
and their documentation.  

The header file implements the Node and Edge objects, and describes an 
interface for the Aho Corasick Trie. The .cpp file implements the interface, 
and this is where my attempts at the Trie algorithms are. As of this writing, 
those algorithms aren't working due to pointer/object life cycles.  

If possible, I'd appreciate some more time to try to get this right. I want to 
learn how to do this in C++, and I'd like to learn how to do it well.
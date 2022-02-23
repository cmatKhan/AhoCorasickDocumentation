# Introduction

It works! This is the first time I have coded in c++, or used pointers directly.
I am still learning about how to to deal with autoconf and whatnot. This compiles
on my computer, running ubuntu 20.04 and g++ version 9.3.0.

There is a test suite which is implemented with googletests. The code is
100% covered by the tests. Documentation is created from appropriately formatted
comments by Doxygen.

## How to use this site

At the top, you'll notice a navigator bar. More or less, clicking any of the
drop downs will bring you to a page where you can navigate to the object
definitions. But, the most interesting is Classes->Class List. Click on
ACTrie, which is my implementation of Aho Corasick. The code for the functions
ACTrie::insert(), ACTrie::findNv() and ACTrie::search() is included in the
documentation, in addition to a description of the input/output.

aho_corasick.h implements the Node and Edge objects, and describes an
interface for the Aho Corasick Trie. The aho_corasick.cpp file implements the
interface and includes the main method. aho_corasick.test.cpp is the test
suite (note that I comment out the main method of the .cpp file to run this.
Not great, but I'm still learning how to deal with the compiling, etc.)

Once compiled, run the code like this:

```{bash}
./aho_corasick pattern_file.txt target.fa
```

Output will look like this (__NOTE__ this is not the output of the assignment
files, only a short test):

```{bash}
> ./aho_corasick data/pattern_test4.txt data/test4.fa 
creating Trie...
inserting pattern: cag
and its reverse complement: ctg
inserting pattern: ag
and its reverse complement: ct
inserting pattern: gca
and its reverse complement: tgc
inserting pattern: ca
and its reverse complement: tg
Setting failure links and out links...
Searching the target for pattern matches...
target_location, pattern, strand
1,2,1
4,2,2
7,4,1
7,1,1
8,2,1
16,3,1
17,4,1
19,4,2
19,3,2
20,3,1
21,4,1
```

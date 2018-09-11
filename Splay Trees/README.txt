The included program creates a binary search tree (BST) and a splay tree and
analyses the performance of each.

In order to run the program the following fields must be updated in the main.cpp file:

  1) int treeSize; // Default is 20,000 elements
  2) int querySize; // Default is 10,000 queries
  3) string filenameSplay = "output file destination for splay tree heights";
  4) string filenameBST = "output file destination for BST tree heights";
  5) string filenameSplaySearch = "output file destination for splay tree search unbiased results";
  6) string filenameBSTSearch = "output file destination for BST tree unbiased height";
  7) string filenameSplaySearchBias = "output file destination for splay tree biased height";
  8) string filenameBSTSearchBias = "output file destination for BST tree biased height";

After the fields have been set, simply run main.cpp from any IDE or the command line.

The program will output the 6 files mentioned above:

filenameSplay - File with the height of the splay tree after each insertion of
a single element. Each height is output to a new line on the file.

filenameBST - File with the height of the BST after each insertion of
a single element. Each height is output to a new line on the file.

filenameSplaySearch - the number of nodes visited during a single search with
unbiased results. Each result is output to a new line on the file.

filenameBSTSearch - the number of nodes visited during a single search of the
BST with unbiased results. Each result is output to a new line on the file.

filenameSplaySearchBias - the number of nodes visited during a single search with
biased results. Each result is output to a new line on the file.

filenameBSTSearchBias - the number of nodes visited during a single search of the
BST with biased results. Each result is output to a new line on the file.

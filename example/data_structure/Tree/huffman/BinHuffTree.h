// Written by Todd Yilk using Microsoft Visual C++ v6.0
// Wriiten for CS328 - Professor Dale and TA Ramadass Nagarjan
// Prolog: This program generates Huffman codes for a user specified
// input file. Class CreateHuffTree contains a function which reads the
// file and stores the character frequencies in an array. Function
// CreateHuffTree creates the encoding tree by:
//		1. Generate the forest of nodes: the forest is implemented
//			as an array of BinaryHuffTrees, binary trees with each
//			node storing the element and an integer for the tree's
//			priority.
//			The forest is initialized with each element containing
//			a one node BinaryHuffTree with the element value set to
//			the character integer value and the priority set to the
//			character frequency.
//		2. The forest is sorted in ascending order by priority
//		3. The forest is iterated over from the first to the last
//		   element. At each iteration:
//			1. The two trees of smallest priority are combined into
//				a new tree with element -1 and priority equal to the
//				sum of the 2 tree priorities. The smaller (by priority)
//				of the 2 trees becomes the left node in the new tree
//				and the larger becomes the right node.
//			2. The new tree is inserted back into the forest array
//			   and moved to preserve the array's order by priority. The
//			   new tree is moved past trees of equal priority.
//		4. After this iteration, the tree with greatest priority in the
//		   forest is the final Huffman code tree; it is returned by the
//		   function.
//
//
 
#include<string>

using namespace std;
void error(const string & errorMessage);

class BinaryHuffTree;
class BinaryNode
{
	int element;
	BinaryNode *leftNode;
	BinaryNode *rightNode;

	BinaryNode(const int & theElement,BinaryNode *lt,BinaryNode *rt)
		: element(theElement), leftNode(lt), rightNode(rt) {}

	friend class BinaryHuffTree;
};


class BinaryHuffTree
{
	public:
		
// function: class constructor
//		     O(1)
// precondition: none
// postcondtion: tree is initialized
		BinaryHuffTree();

// function:  class copy constructor
//		     O(n) n: number of tree nodes
// precondition: trees initialized
// postcondtion: this = right hand side
		BinaryHuffTree( const BinaryHuffTree & rhs);

// function: class destructor, calls makeEmpty()
//		     O(n) n: number of tree nodes
// precondition: tree initialized
// postcondtion: tree deleted
		~BinaryHuffTree();

// function: class assignment operator; does deep copy on every node
//			 calls private recursive function clone
//		     O(n) n: number of tree nodes
// precondition: trees initialized
// postcondtion: A = B for HuffTrees A,B
		const BinaryHuffTree & operator=( const BinaryHuffTree & rhs);

// function: removes every tree element; calls private recursive
//			 form of makeEmpty()
//		     O(n) n: number of tree nodes
// precondition: tree initialized
// postcondtion: tree has zero nodes
		void makeEmpty();

//  function: creates a new tree with priority equal to the sum of
//            the priorities of the 2 arguments; the new tree has
//			  root with element = -1, left pointer to the first argument
//			  and right pointer to the second argument.
//			  O(n) n: number of nodes in the 2 arguments
//  precondition: all trees initialized
//  postcondition: function caller tree set as described
		const BinaryHuffTree & combine( const BinaryHuffTree & tree1,
			                            const BinaryHuffTree & tree2);

//  function: inserts an element into a binary tree of integers; inserted in
//            binary tree order
//			  O(log n) n: number of nodes in the tree
//  precondition: tree initialized
//  postcondition: element is guaranteed to exist in the tree
		void insert( const int & x);

//  function: accessor function to return the priority of a tree
//		      O(1);
//  precondition: tree initialized
//  postcondition: returns tree priority
		int getPriority() const;

//  function: accessor function to set the priority of a tree
//		      O(1);
//  precondition: tree initialized
//  postcondition: tree priority set to x
		void setPriority(const int & x);

// function: use a binaryHuffTree to encode a file, saving the code
//			 with the file. O(n) n:size of the file in bytes.
// precondition: Huff tree created with CreateHuffTree::createTree()
// postcondtion: encoded file is saved or an error message is printed
		void encodeFile(const string & textFileName,
						const string & codeFileName);

// function: use a binaryHuffTree to decode a file.
//			 O(n) n:size of the file in bytes.
// precondition: codeFileName is a file created with encode file
// postcondtion: file is decoded to textFileName or an error message is printed
		void decodeFile(const string & codeFileName,
						const string & textFileName);

	
	private:
		BinaryNode *root;
		int priority;

// function: private helper function for copying a tree
//		     O(n) n: number of nodes copied
// precondition: tree node exists
// postcondtion: tree node is duplicated
		BinaryNode * clone(BinaryNode *t) const;

// function: private helper function to remove every node from a tree
//		     O(n) n: number of tree nodes
// precondition: tree exists
// postcondtion: node is empty
		void makeEmpty(BinaryNode* & t) const;

// function: private function which recursively inserts an element into
//		     a binary tree of integers; inserted in binary tree order
//			 O(log n) n: number of nodes in the tree
//  precondition: tree initialized 
//  postcondition: element is guaranteed to exist in the tree
		void insert( const int & x, BinaryNode* & t) const;

// function: converts the binary tree representation of Huffman codes
//			 into an array representation
//			 O(n): n number of nodes in the tree
// precondition: the Huffman codes have been created with CreateHuffTree::createTree()
// postcondition: codeArray is an array of strings representing the Huffman codes
		void createCodeArray(BinaryNode *t,string s,
										 string* & codeArray) const;

// function: used by decodeFile to change the Huffman codes read from a
//           file into a binary tree representation.
//			 O(n) n: number of bits in the Huffman codes
// precondition: none/ checking in decode
// postcondition: the Huffman codes have been read from a file and
//                placed into a binary tree
		void putIntoTree(const int & charValue, 
						 string & charCode,BinaryNode* & t);

// function: used by decodeFile to read the stream of binary data from an
//			 encoded file, decode the characters using the tree
//           generated by putIntoTree, and write the results to a file
//			 O(n) n: size of the file decoded
// precondition: function putIntoTree sucessfully run
// postcondition: The decoded characters are placed in textFile
		void BinaryHuffTree::emitDecodedFile(BinaryNode*& t, ifstream & codeFile,
												ofstream & textFile);

// function: helper function used by emitDecodedFile to convert a 
//           stream of bits into a stream of characters
//            O(1)
// precondition: called from emitDecodedFile
// postcondition: returns character '1','0', or 'e' for end of file
		char getBit(ifstream& inFile);


};

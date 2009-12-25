// Written by Todd Yilk using Microsoft Visual C++ v6.0
// Wriiten for CS328 - Professor Dale and TA Ramadass Nagarjan


class BinaryNode;
class BinaryHuffTree;

class CreateHuffTree
{
	public:
// function: class constructor O(n) n: size of character set
// precondition: none
// postcondition: frequency table created and initialized to 0.
		CreateHuffTree(const int & charSetSize);

// function: class destructor. O(n) n: size of character set.
// precondition: class initialized
// postcondition: class deleted
		~CreateHuffTree();

// function: reads characters from a user specified file, counting
//           the number of times each character is read.
//           O(n) n: file size
// precondition: class initialized
// postcondition: the frequency table stores the number of occurences
//                of each character
//		                 or
//		          an error message is printed if file cannot be opened
		void getData(const string & inFileName);

// function: prints the frequency table to file HufFreq.txt
//           O(n) n: size of frequency table = character set size
// precondition: class has been initialized
// postcondition: table printed to file
		void printTable() const;

// function: creates the binary tree for Huffman
//			 encoding the character set.
//           O(n^2) n: size of character set
// precondition: frequency table has been generated
// postcondition: returns a binary tree encoding the character set
		BinaryHuffTree createTree();

	private:
		int* freqTable;
		BinaryHuffTree* forest;
		int alphabetSize;

};



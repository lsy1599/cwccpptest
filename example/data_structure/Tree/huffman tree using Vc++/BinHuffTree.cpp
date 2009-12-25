// Written by Todd Yilk using Microsoft Visual C++ v6.0
// Wriiten for CS328 - Professor Dale and TA Ramadass Nagarjan

#include<iostream>
#include<fstream>
#include<string>
#include<cmath>
#include"BinHuffTree.h"

using namespace std;

BinaryHuffTree::BinaryHuffTree()
{
	root = NULL;
	priority = 0;
}


BinaryHuffTree::BinaryHuffTree(const BinaryHuffTree & rhs)
{
	root = NULL;
	*this = rhs;
}



BinaryHuffTree::~BinaryHuffTree()
{
	makeEmpty();
}



const BinaryHuffTree &
BinaryHuffTree::operator=(const BinaryHuffTree & rhs)
{
	if( this != &rhs)
	{
		makeEmpty();
		root = clone(rhs.root);
		priority = rhs.priority;
	}
	return *this;
}


BinaryNode * BinaryHuffTree::clone(BinaryNode *t) const
{
	if(t==NULL)
		return NULL;
	else
		return new BinaryNode(t->element, clone(t->leftNode),
												  clone(t->rightNode));
}


void BinaryHuffTree::makeEmpty()
{
	makeEmpty(root);
}


void BinaryHuffTree::makeEmpty(BinaryNode * & t) const
{
	if ( t != NULL)
	{
		makeEmpty(t->leftNode);
		makeEmpty(t->rightNode);
		delete t;
	}
	t = NULL;
}


int BinaryHuffTree::getPriority() const
{
	return priority;
}


void BinaryHuffTree::setPriority(const int & x)
{
	priority = x;
}


// function: creates a new tree with priority equal to the sum of
//           the priorities of the 2 arguments; the new tree has
//			 root with element = -1, left pointer to the first argument
//			 and right pointer to the second argument
const BinaryHuffTree & BinaryHuffTree::combine(const BinaryHuffTree & tree1,
												const BinaryHuffTree & tree2)
{	
	BinaryHuffTree tempTree;

	(*this).setPriority(tree1.getPriority() + tree2.getPriority());
	(*this).root = new BinaryNode(-1,clone(tree1.root),
										clone(tree2.root));
	return *this;

}


void BinaryHuffTree::insert(const int & x)
{
	insert(x, root);
}


// Inserts element into a tree in binary search tree order.
void BinaryHuffTree::
insert(const int & x, BinaryNode * & t) const
{
	if (t== NULL )
		t= new BinaryNode(x, NULL, NULL);
	else if( x < t->element)
		insert(x, t->leftNode);
	else if( t->element < x)
		insert(x, t->rightNode);
	else
		return;
}



void BinaryHuffTree::createCodeArray(BinaryNode *t,string s,
										 string* & codeArray) const
{
	if (t->leftNode == NULL && t->rightNode == NULL)
		codeArray[t->element] = s;

	if ( t->rightNode != NULL)			// append 1 for right
		createCodeArray(t->rightNode,s+"1",codeArray);

	if ( t->leftNode != NULL)			// append 0 for left
		createCodeArray(t->leftNode,s+"0",codeArray);	

}


void BinaryHuffTree::encodeFile(const string & textFileName,
								const string & codeFileName)
{
	ofstream outFile; ifstream inFile;
	char inChar;
	unsigned char storeChar, bitField=0; char bitFieldPosition=7;
	string code;
	
	string* codeArray;
	codeArray = new string[256];

	cout << "Writing encoded file . . ." << endl;

	outFile.open(codeFileName.data(),ios::out+ios::binary);
	if (!outFile.is_open())
	error("\n*** Fatal error encoding file: Unable to open coded file ");
		
	//Convert binary tree representation of the Huff codes
	//into an array form
	createCodeArray(root, "", codeArray);

	//first write the codes using format:
	//C <integer> e <string><newline>
	for( int i=0; i<=255; i++)
		if (codeArray[i] != "")
		outFile << "C " << i
				<< "e " << codeArray[i] << "\n";

	outFile << "Character# -1encoded_by NULL\n"; //Terminator for codes
												  //section of the file
	
	//next read in characters of inFile one at a time, emitting
	//appropriate Huffman codes.
	inFile.open(textFileName.data(),ios::binary);
	for(;;)
	{
		inFile.get(inChar);	   // get returns a signed char value
		if (inFile.eof()) break; 
		storeChar = inChar;    // Convert to unsigned for compatabilty
		                       // with ascII values > 127
		code = codeArray[int(storeChar)];
		for(int i=0; i < code.length(); i++)  //Loop converts a string
		{									 // of 1's and 0's into a 
			if (code[i] == '1')				// stream of bits
				bitField += int(pow(2,bitFieldPosition));
			bitFieldPosition--;	

			if (bitFieldPosition == -1)	// Write out the character buffer
			{							// and reset it every 8 bits
				outFile << bitField;
				bitField = 0;
				bitFieldPosition =7;
			}

		}
	}
	
	// In this enoding, the second to last character of the file will
	// contain meaningful data while the last character of the file
	// tells us how many bits from that byte are meaningful.
	// The second to last character of the file will always contain
	// n = 0 to 7 significant bits of data, never exactly 8. The last
	// character contains the character code equal to n.
	outFile << bitField;								
	outFile << (char(7 - bitFieldPosition));

	inFile.close();
	outFile.close();

	delete[] codeArray;
	codeArray = NULL;
}


// This function helps decode a file
// Takes a Huffman code represented as a string of 1's and 0's and
// parses it into a BinaryHuffTree
void BinaryHuffTree::putIntoTree(const int & charValue, 
								 string & charCode, BinaryNode* & t)
{
	if (charCode[0] == '1')
	{	
		charCode.erase(0,1);
		if (t->rightNode == NULL)
			if(charCode.empty())
			{
				t->rightNode = new BinaryNode(charValue,NULL,NULL);
				return;
			}
			else
			{
				t->rightNode = new BinaryNode(-1,NULL,NULL);
				putIntoTree(charValue,charCode,t->rightNode);
				return;
			}
		else
			if (charCode.empty())
			{
				error("*** Internal error in Huffman decoding: duplicate code found");
			}
			else
			{
				putIntoTree(charValue,charCode,t->rightNode);
				return;
			}
	}
	else
	if (charCode[0] = '0')
	{	
		charCode.erase(0,1);
		if (t->leftNode == NULL)
			if(charCode.empty())
			{
				t->leftNode = new BinaryNode(charValue,NULL,NULL);
				return;
			}
			else
			{
				t->leftNode = new BinaryNode(-1,NULL,NULL);
				putIntoTree(charValue,charCode,t->leftNode);
				return;
			}
		else
			if (charCode.empty())
			{
				error("*** Internal error in Huffman decoding: duplicate code found");
			}
			else
			{
				putIntoTree(charValue,charCode,t->leftNode);
				return;
			}
	}

	error("*** Internal Error in Huffman decoding: Invalid character in code");
}


// *************************************************************************
//
// An undiscovered bug still lurks in this method. Meant to correctly
// decode the trailing bits of a file, where the number of significant
// bits is not an even multiple of 8, the two characters lastSigBits and
// numSigBits are inexplicably given values of 0x11111111 some of the time.
// Other times, the method runs correctly. The source of this problem
// remains undiscovered at this time. Decoded files are thus correct
// only through the last character, which did not make any of the binary
// files in the test plan unreadable.

//DEL void BinaryHuffTree::emitLastBits(BinaryNode*& t, ifstream & codeFile,
//DEL 												ofstream & textFile)
//DEL {
//DEL 	char readChar;
//DEL 	static unsigned char lastSigBits = codeFile.get();
//DEL 	static char numSigBits = codeFile.get();
//DEL 	static int mask = 256;
//DEL 
//DEL   	while(numSigBits > 0)
//DEL 	{
//DEL 		mask /= 2;
//DEL 		if( lastSigBits & mask )
//DEL 			readChar = '1';
//DEL 		else
//DEL 			readChar = '0';
//DEL 		numSigBits--;
//DEL 
//DEL 		if(readChar == '1')
//DEL 		{
//DEL 			if( t->rightNode->element != -1)
//DEL 			{
//DEL 				textFile << char(t->rightNode->element);
//DEL 				return;
//DEL 			}
//DEL 			else
//DEL 				emitLastBits(t->rightNode,codeFile,textFile);
//DEL 		}
//DEL 		else
//DEL 		if(readChar == '0')
//DEL 		{
//DEL 			if( t->leftNode->element != -1)
//DEL 			{
//DEL 				textFile << char(t->leftNode->element);
//DEL 				return;
//DEL 			}
//DEL 			else
//DEL 				emitLastBits(t->leftNode,codeFile,textFile);
//DEL 		}
//DEL 	}
//DEL }


char BinaryHuffTree::getBit(ifstream& inFile)
{
	static const unsigned char bufferMasks[8] = {1,2,4,8,16,32,64,128};
	static int bufferPosition = -1;
	static char buffer;
//	char buffer2;
//	int buffer3;

	if(bufferPosition == -1)
	{
		buffer = inFile.get();
	//	buffer2 = inFile.get();
	//	buffer3 = inFile.peek();

		if (inFile.eof()) // if(buffer3 == EOF)
		{
	//		inFile.putback(buffer2);
	//		inFile.putback(buffer);
			return 'e';
		}

	//	inFile.putback(buffer2);
		bufferPosition = 7;
	}

	if (buffer & bufferMasks[bufferPosition--]) //use old buffer position
		return '1';								//then move position right
	else
		return '0';
}


void BinaryHuffTree::emitDecodedFile(BinaryNode*& t, ifstream & codeFile,
												ofstream & textFile)
{
	char readChar;

	readChar = getBit(codeFile);

	if (readChar == 'e')
	{
	//	emitLastBits(t,codeFile,textFile);
		return;
	}
	else
	{
		if(readChar == '1')
		{
			if( t->rightNode->element != -1)
			{
				textFile << char(t->rightNode->element);
				return;
			}
			else
				emitDecodedFile(t->rightNode,codeFile,textFile);
		}
		else
		if(readChar == '0')
		{
			if( t->leftNode->element != -1)
			{
				textFile << char(t->leftNode->element);
				return;
			}
			else
				emitDecodedFile(t->leftNode,codeFile,textFile);
		}
	}
}


void BinaryHuffTree::decodeFile(const string & codeFileName,
								const string & textFileName)
{
	ifstream codeFile; ofstream textFile;
	int charValue; string charCode;
	char readChar;

	cout << "Writing decoded file . . ." << endl;

	codeFile.open(codeFileName.data(),ios::in+ios::binary);
	if (!codeFile.is_open())
		error("\n*** Fatal error encoding file: Unable to open coded file ");

	//read in codes and construct the Huffman tree
	makeEmpty();
	root = new BinaryNode(-1,NULL,NULL);
	priority =0;
	
	getline(codeFile,charCode,' '); // skip "C "
	codeFile >> charValue;			// get ascII value
	getline(codeFile,charCode,' '); // skip "e"
	getline(codeFile,charCode,'\n'); // character code string
	while (charValue != -1)
	{
		putIntoTree(charValue,charCode,root);

		getline(codeFile,charCode,' '); // skip "C"
		codeFile >> charValue;			// get ascII value
		getline(codeFile,charCode,' '); // skip "e "
		getline(codeFile,charCode,'\n'); // character code string
	}

	//open output stream and emit decoded characters
	textFile.open(textFileName.data(),ios::out+ios::binary);
	if (!textFile.is_open())
		error("\n*** Fatal error decoding file: Unable to open decoding target file.");
	
	for(;;)
	{
		readChar = codeFile.get();
		if (codeFile.eof())
			break;
		else
		{
			codeFile.putback(readChar);
			emitDecodedFile(root,codeFile,textFile);
		}
	}
	
	codeFile.close();
	textFile.close();
}
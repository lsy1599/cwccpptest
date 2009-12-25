// Written by Todd Yilk using Microsoft Visual C++ v6.0
// Wriiten for CS328 - Professor Dale and TA Ramadass Nagarjan

#include<string>
#include<iostream>
#include<iomanip>

#include"BinHuffTree.h"
#include"MakeHuffCode.h"

using namespace std;

// Helper function used to dump error messages
void error(const string & errorMessage)
{
	string bye;

	cerr << errorMessage << endl;
	cout << endl <<"   Press return to exit the program" << endl;
	getline(cin,bye,'\n');
	exit(1);
}


// Driver to create Huffman codes
void main()
{	
	const int possibleChars = 256;
	BinaryHuffTree HuffTree;

	CreateHuffTree A(possibleChars);
	string textFileName,codeFileName,newTextFileName,bye;

	cout << "This driver tests the Huffman encoding functions.\n"
		 << "You will be prompted for a total of three file names,\n"
		 << " the original document, the coded document, and the\n"
		 << " decoded coded document. Upon program completion, the\n"
		 << " first and third files should be duplicates\n" << endl;
	cout << "Enter the file name to encode: ";
	cin >> textFileName;
	cout << setw(31) << "encode to file: ";
	cin >> codeFileName;
	cout << endl;

	A.getData(textFileName);
	A.printTable();
	HuffTree = A.createTree();

	HuffTree.encodeFile(textFileName, codeFileName);

	cout << "\nEnter the file name to decode " << codeFileName
		 << " to: ";
	cin >> newTextFileName;

	HuffTree.decodeFile(codeFileName, newTextFileName);

	cout << endl <<"   Press return to exit the program" << endl;
	getline(cin,bye,'\n');

}

// Written by Todd Yilk using Microsoft Visual C++ v6.0
// Wriiten for CS328 - Professor Dale and TA Ramadass Nagarjan

#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>

#include"BinHuffTree.h"
#include"MakeHuffCode.h"

using namespace std;

CreateHuffTree::CreateHuffTree(const int & charSetSize)
{
	alphabetSize = charSetSize;

	freqTable = new int[charSetSize];  // Freq table is created
	for(int i=0; i<=charSetSize; i++)  // and initialized
		freqTable[i]=0;
}


CreateHuffTree::~CreateHuffTree()
{

	delete[] freqTable;
	freqTable = NULL;
}


void CreateHuffTree::getData(const string & inFileName)
{
	ifstream inFile;
	char inChar;
	unsigned char storeChar;

	inFile.open(inFileName.data(),ios::binary);
									// "binary" allows proper reading
	if (!inFile.is_open())		    // of any file.
		error("\n*** Fatal Error: Unable to open file source file.");

	cout << "\nReading characters from file " << inFileName
		 << " . . ." << endl;
	for(;;)
	{
		inFile.get(inChar);	   // get returns a signed char value
		if (inFile.eof()) break; 
		storeChar = inChar;    // Convert to unsigned for compatabilty
		                       // with ascII values > 127
		freqTable[int(storeChar)]++;
	}

	inFile.close();
}


void CreateHuffTree::printTable() const
{
	ofstream outFile("HufFreq.txt");

	cout << "Writing character frequency table to HufFreq.txt . . ."
		 << endl;

	outFile << "Character ASCII values (Val)"
		    << " and frequency of occurence (Freq)\n";
	for(int i=1;i<=8;i++)
		outFile << "Val  Freq   ";
	outFile << "\n";

	for(i=0; i<=31; i++)	// Prints 32 rows of 8 columns
	{							// incrementing down columns    
		for(int j=0; j<=7; j++) 
			outFile << setw(3) << i+j*32 
			        << " "
					<< setw(5) << freqTable[i+j*32]
					<< "   ";
		outFile << "\n";
	}
	
	outFile.close();
}


BinaryHuffTree CreateHuffTree::createTree()
{

	int j,firstNonZero=0;
	BinaryHuffTree tempTree,combinedTrees;
	forest = new BinaryHuffTree[alphabetSize];
	
	cout << "Creating the Huffman tree . . ." << endl;

	// Create the forest of nodes
	for(int i=0; i < alphabetSize; i++)
	{
		forest[i].setPriority(freqTable[i]);
		forest[i].insert(i);
	}

	// Sort the forest by increasing priority using Shellsort
	for( int gap = alphabetSize/2; gap>0; gap/=2 )
		for ( i=gap; i < alphabetSize; i++ )
		{
			tempTree = forest[i];
			for( j=i;
			     (j>=gap) && (tempTree.getPriority() < forest[j-gap].getPriority());
				 j -= gap)
				forest[j] = forest[j-gap];
			forest[j] = tempTree;
		}

	// Skip all of the characters with zero occurence
	while(forest[firstNonZero].getPriority() == 0)
		firstNonZero++;
	
	// Create the Huffman tree
	for( i=firstNonZero; i < alphabetSize - 1; i++)
	{
		// combine the two lowest priorities
		combinedTrees.combine(forest[i],forest[i+1]);

		// reinsert into the forest
		forest[i+1] = combinedTrees;

		// place in priority order
		for( j=i+1; j < alphabetSize-1; j++)
			if( forest[j].getPriority() >= forest[j+1].getPriority())
			{
				tempTree=forest[j];
				forest[j]=forest[j+1];
				forest[j+1]=tempTree;
			}
			else
				break;
	}

	tempTree = forest[alphabetSize-1]; // is now the completed Huffcode tree
	
	delete[] forest;
	forest = NULL;

	return tempTree;

}
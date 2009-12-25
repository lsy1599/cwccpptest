/*
 * Huffman Coding
 *
 * This program reads a text file named on the command line, then
 * compresses it using Huffman coding.  The file is read twice,
 * once to determine the frequencies of the characters, and again
 * to do the actual compression.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <iostream.h>
/* there are 256 possible characters */

#define NUM_CHARS	256

/* tree node, heap node */

typedef struct _treenode treenode;
struct _treenode {
	int		freq;	      // 存放在優先佇列中的頻率
	unsigned char	ch;	// 字元
	treenode	*left,	   // left child of Huffman tree (not heap!)
			*right;	      // right child of Huffman tree
};

/* 優先佇列使用二元累堆來製作 */
typedef struct _pq
{
	int		heap_size;
	treenode	*A[NUM_CHARS];
} PQ;

/* 建立空佇列 */
void create_pq (PQ *p)
{
	p->heap_size = 0;
}//end create_pq

/* 計算節點父親的位址 */
int parent (int i)
{
	return (i-1) / 2;
}//end parent

/* 計算左邊節點位址 */
int left (int i)
{
	return i * 2 + 1;
}//end left

/* 計算右邊節點位址 */
int right (int i)
{
	return i * 2 + 2;
}//end right

/* makes the subheap with root i into a heap , assuming left(i) and
 * right(i) are heaps
 */
void heapify (PQ *p, int i) {
	int		l, r, smallest;
	treenode	*t;

	l = left (i);
	r = right (i);

	/* find the smallest of parent, left, and right */

	if (l < p->heap_size && p->A[l]->freq < p->A[i]->freq)
		smallest = l;
	else
		smallest = i;
	if (r < p->heap_size && p->A[r]->freq < p->A[smallest]->freq)
		smallest = r;

	/* swap the parent with the smallest, if needed. */

	if (smallest != i) {
		t = p->A[i];
		p->A[i] = p->A[smallest];
		p->A[smallest] = t;
		heapify (p, smallest);
	}
}

/* 插入元素到頻率優先佇列中 */
void insert_pq (PQ *p, treenode *r)
{
	int		i;

	p->heap_size++;
	i = p->heap_size - 1;

	/* we would like to place r at the end of the array,
	 * but this might violate the heap property.  we'll start
	 * at the end and work our way up
	 */
	while ((i > 0) && (p->A[parent(i)]->freq > r->freq))
   {
		p->A[i] = p->A[parent(i)];
		i = parent (i);
	}
	p->A[i] = r;
}//end insert_pq

/* remove the element at head of the queue (i.e., with minimum frequency) */
treenode *extract_min_pq (PQ *p)
{
	treenode	*r;

	if (p->heap_size == 0) {
		printf ("heap underflow!\n");
		exit (1);
	}

	/* get return value out of the root */

	r = p->A[0];

	/* take the last and stick it in the root (just like heapsort) */

	p->A[0] = p->A[p->heap_size-1];

	/* one less thing in queue */

	p->heap_size--;

	/* left and right are a heap, make the root a heap */

	heapify (p, 0);
	return r;
}

/* read the file, computing the frequencies for each character
 * and placing them in v[]
 */
unsigned int get_frequencies (FILE *f, unsigned int v[])
{
	int	r, n;

	/* n will count characters */
	for (n=0;;n++)
   {
		/* fgetc() gets an unsigned char, converts to int */
		r = fgetc (f);

		/* no more?  get out of loop */
		if (feof (f)) break;

		/* one more of this character */
		v[r]++;
	}
	return n;
}

/* make the huffman tree from frequencies in freq[] (Huffman's Algorithm) */
treenode *build_huffman (unsigned int freqs[])
{
	int		i, n;
	treenode	*x, *y, *z;
	PQ		p;

	/* 建立一個新的佇列 */
	create_pq (&p);

	/* 針對每一個字元，建立一個包含數值和頻率的累堆/數節點 */
	for (i=0; i<NUM_CHARS; i++)
   {
		x = (treenode*)malloc (sizeof (treenode));

		/* Huffman tree 葉節點設定*/
		x->left = NULL;
		x->right = NULL;
		x->freq = freqs[i];
		x->ch = (char) i;

		/* 將資料放到累堆中 */
		insert_pq (&p, x);
	}//next i

	/* at this point, the heap is a "forest" of singleton trees */
	n = p.heap_size-1; /* heap_size isn't loop invariant! */

	/* if we insert two things and remove one each time,
	 * at the end of heap_size-1 iterations, there will be
	 * one tree left in the heap
	 */
	for (i=0; i<n; i++)
   {
		/* make a new node z from the two least frequent
		 * nodes x and y
		 */
		z =(treenode*) malloc (sizeof (treenode));
		x = extract_min_pq (&p);
		y = extract_min_pq (&p);
		z->left = x;
		z->right = y;

		/* z's frequency is the sum of x and y */
		z->freq = x->freq + y->freq;

		/* put this back in the queue */
		insert_pq (&p, z);
	}

	/* return the only thing left in the queue, the whole Huffman tree */
	return extract_min_pq (&p);
}

/* traverse the Huffman tree, building up the codes in codes[] */
void traverse (treenode *r, 	/* root of this (sub)tree */
		int level, 	/* current level in Huffman tree */
		char code_so_far[], /* code string up to this point in tree */
		char *codes[]) {/* array of codes */

	/* if we're at a leaf node, */

	if ((r->left == NULL) && (r->right == NULL)) {

		/* put in a null terminator */

		code_so_far[level] = 0;

		/* make a copy of the code and put it in the array */

		codes[r->ch] = strdup (code_so_far);
	} else {

		/* not at a leaf node.  go left with bit 0 */

		code_so_far[level] = '0';
		traverse (r->left, level+1, code_so_far, codes);

		/* go right with bit 1 */

		code_so_far[level] = '1';
		traverse (r->right, level+1, code_so_far, codes);
	}
}

/* global variables, a necessary evil */

int nbits, current_byte, nbytes;

/* output a single bit to an open file */

void bitout (FILE *f, char b) {

	/* shift current byte left one */

	current_byte <<= 1;

	/* put a one on the end of this byte if b is '1' */

	if (b == '1') current_byte |= 1;

	/* one more bit */

	nbits++;

	/* enough bits?  write out the byte */

	if (nbits == 8) {
		fputc (current_byte, f);
		nbytes++;
		nbits = 0;
		current_byte = 0;
	}
}

/* using the codes in codes[], encode the file in infile, writing
 * the result on outfile
 */
void encode_file (FILE *infile, FILE *outfile, char *codes[]) {
	unsigned char ch;
	char	*s;

	/* initialize globals for bitout() */

	current_byte = 0;
	nbits = 0;
	nbytes = 0;

	/* continue until end of file */

	for (;;) {

		/* get a char */

		ch = fgetc (infile);
		if (feof (infile)) break;

		/* put the corresponding bitstring on outfile */

		for (s=codes[ch]; *s; s++) bitout (outfile, *s);
	}

	/* finish off the last byte */

	while (nbits) bitout (outfile, '0');
}

/* main program */

int main (int argc, char *argv[]) {
	FILE		*f, *g;
	treenode	*r;		   /* Huffman tree 的根節點 */
	unsigned int	n,    /* 檔案總 bytes 數(字元數) */
			         freqs[NUM_CHARS];  /* 每個字元出現頻率 */
	char		*codes[NUM_CHARS], /* array of codes, 1 per char */
			   code[NUM_CHARS],   /* a place to hold one code */
			   fname[100];	   /* what to call output file */

	/* hassle user */
   char *file="c:\\arick.txt";
/*
	if (argc != 2) {
		fprintf (stderr, "Usage: %s <filename>\n", argv[0]);
		exit (1);
	}
*/
	/* 初始化字元出現頻率為零 */
	memset (freqs, 0, sizeof (freqs));

	/* 開啟命令列參數中的檔案 */
//	f = fopen (argv[1], "r");
   f = fopen(file,"r");
	if (!f) {
		perror (argv[1]);
		exit (1);
	}

	/* 計算檔案中字母的出現頻率 */
	n = get_frequencies (f, freqs);
	fclose (f);

	/* 建立 huffman tree */
	r = build_huffman (freqs);

	/* traverse the tree, filling codes[] with the codes */
   /* 走訪 Huffman tree, 建立編碼原則*/
	traverse (r, 0, code, codes);

	/* 開啟儲存編碼後的文件的檔案 *.huf */
//	sprintf (fname, "%s.huf", argv[1]);
	sprintf (fname, "%s.huf", file);
	g = fopen (fname, "w");
	if (!g) {
		perror (fname);
		exit (1);
	}

	/* 字元頻率寫至目的檔案，以便解碼用 */
	fwrite (freqs, NUM_CHARS, sizeof (int), g);

	/* write number of characters to file as binary int */
	fwrite (&n, 1, sizeof (int), g);

	/* open input file again */
	f = fopen (argv[1], "r");
	if (!f) {
		perror (argv[1]);
		exit (1);
	}

	/* encode f to g with codes[] */
	encode_file (f, g, codes);
	fclose (f);
	fclose (g);
	/* brag */
	printf ("%s is %0.2f%% of %s\n",
		fname, (float) nbytes / (float) n, argv[1]);
	exit (0);
}











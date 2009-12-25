#include <stdio.h>
#include <alloc.h>
typedef struct treenode
{
  struct treenode *left;
  struct treenode *right;
  int  data;
}NODE ;

void print_perf_tree(NODE *p,int h);
NODE *create_perf_tree(int n,int *kptr);
FILE *fout;
void main ()
{
  NODE *root;
  int n,k;
  fout=fopen("c:\perftree.txt","w");
  for (n=2;n<=6;n++)
  {
    k=1;
    root=create_perf_tree(n,&k);
    fprintf(fout,"        tree for %d nodes\n",n);
    print_perf_tree(root,1);
    fprintf(fout,"\n\n");
  }
  fclose(fout);
}

NODE *create_perf_tree(int n,int *kptr)
{
  int nl,nr;
  NODE *p;
  if (n==0)
    return NULL;
  else
  {
    nl=n/2;
    nr=n-nl-1;
//    p=malloc(sizeof(NODE));
    p->data=(*kptr)++;
    p->left=create_perf_tree(nl,kptr);
    p->right=create_perf_tree(nr,kptr);
    return p;
  }
}

void print_perf_tree(NODE *p,int h)
{
  int i;
  if (p!=NULL)
  {
    print_perf_tree(p->right,h+1);
    for(i=0;i<=h;i++)
      fprintf(fout,"    ");
    fprintf(fout,"%d\n",p->data);
    print_perf_tree(p->left,h+1);
  }
}
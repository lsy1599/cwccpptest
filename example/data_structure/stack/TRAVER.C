#include <stdio.h>
#include <alloc.h>
typedef struct treenode
{
  struct treenode *left;
  struct treenode *right;
  int  data;
}NODE ;

void preOrder(NODE *p);
void inOrder(NODE *p);
void postOrder(NODE *p);
NODE *create_bin_tree();

int data;
FILE *fin,*fout;
void main ()
{
  NODE *root;
  int n,k;
  fin=fopen("c:\perftree.in","r");
  fout=fopen("c:\perftree.out","w");
  root=create_bin_tree();
  fprintf(fout,"    == preorder  traversal ==\n");
  preOrder(root);
  fprintf(fout,"\n\n    == inorder  traversal ==\n");
  inOrder(root);
  fprintf(fout,"\n\n    == postorder  traversal ==\n");
  postOrder(root);

  fprintf(fout,"\n\n");
  fclose(fin);
  fclose(fout);
}

NODE *create_bin_tree()
{
  NODE *p;
  fscanf(fin,"%d",&data);
  if (data==0)
    return NULL;
  else
  {
    p=malloc(sizeof(NODE));
    p->data=data;
    p->left=create_bin_tree();
    p->right=create_bin_tree();
    return p;
  }
}

void preOrder(NODE *p)
{
  static int i=0;
  if (p!=NULL)
  {
    fprintf(fout,"%6d%c",p->data,(i++%10==9)?'\n':' ');
    preOrder(p->left);
    preOrder(p->right);
  }
}
void inOrder(NODE *p)
{
  static int i=0;
  if (p!=NULL)
  {
    inOrder(p->left);
    fprintf(fout,"%6d%c",p->data,(i++%10==9)?'\n':' ');
    inOrder(p->right);
  }
}

void postOrder(NODE *p)
{
  static int i=0;
  if (p!=NULL)
  {
    postOrder(p->left);
    postOrder(p->right);
    fprintf(fout,"%6d%c",p->data,(i++%10==9)?'\n':' ');
  }
}


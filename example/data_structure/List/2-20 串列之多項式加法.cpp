/******************************************************************/
/******************** �{���W�� : 2-20.c ***************************/
/******************** ��C���h�����[�k ****************************/

 Pnode *Addnode(Pnode *rear,float cof,int ex)  /* �{�����q */
 {				/* cof���h�����Y��,ex���h�������� */
   Pnode *node;
   node=malloc(sizeof(Pnode));
   node->coef=cof;
   node->exp=ex;
   node->link=NULL;
   rear->link=node;
   rear=node;
   return(rear);
 }

 Pnode *polyadd(Pnode *pa,Pnode *pb)
 {
   Pnode *c,*crear;
   c=malloc(sizeof(Pnode));
   crear=c;
   pa=pa->link;
   pb=pb->link;
   while (pa && pb)
   {
    if (pa->exp > pb->exp)
    {
      crear=Addnode(crear,pa->coef,pa->exp);
      pa=pa->link;
    }
    else if (pa->exp < pb->exp)
    {
      crear=Addnode(crear,pb->coef,pb->exp);
      pb=pb->link;
    }
    else
    if ((pa->coef+pb->coef) !=0 )
    {
      crear=Addnode(crear,pa->coef+pb->coef,pa->exp);
      pa=pa->link;
      pb=pb->link;
    }
   }
   while (pa)
   {
     crear=Addnode(crear,pa->coef,pa->exp);
     pa=pa->link;
   }
   while (pb)
   {
     crear=Addnode(crear,pb->coef,pb-exp);
     pb=pb->link;
   }
   return(c);
 }
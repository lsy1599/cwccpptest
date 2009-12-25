 /*******************************************************************/
 /******************* �{���W�� : 7-3.c ******************************/
 /******************* �{���\�� : �O��j�M�k *************************/
 /*******************************************************************/

 # include <stdio.h>
 # define N 12
 # define TRUE 1

 int fib_search(int key,int x[],int low,int high,int index[]) ;
 int fibonacci(int k) ;

 main()				       /* �D�{�� : �O��j�M�k */
 {
   static int data[N] = {25,13,625,131,65,33,27,87,71,22,138,241} ;
   int i,key,count,index[N] ;
   clrscr() ;		               /* �N��l�}�C���e�C�L�X�� */
   while (TRUE)
   {
     for (i = 0 ; i < N ; i++)
     {
       printf("data[%2d]=%3d  ",i,data[i]) ;
       if ((i+1) % 4 == 0)
	  printf("\n");
     }
     printf("\n�п�J�j�M���(^Break : ����) : ") ;
     scanf("%d",&key) ;
     count=fib_search(key,data,0,N-1,index) ;    /* �I�s�O��j�M��� */
     printf("===================================\n") ;
     if (count > 0)
	for(i = 0 ;i < count ; i++)
	printf("���%3d ���F ! �O�bdata[%d] ��m\n",key,index[i]) ;
     else
	printf("���%3d �䤣��!\n",key) ;
	printf("===================================\n");    /*�䤣�����*/
     printf("�A �� �� !!!\n");
    }
 }


 int fib_search(key,x,low,high,index)	     /* ����O��j�M�ʧ@ */
 int key,x[],low,high,index[] ;
 {
    int i,j,n1,n2,n3,m,n,mid,count;
    count = -1 ;
    n = high-low+1;
    for (i = 0; fibonacci(i) < n +1 ; i++) ; /* �H�O��żƨӷ��j����檺�P�_���� */
    i -- ;;
    m = n + 1 - fibonacci(i) ;
    n1 = fibonacci(i-1);
    n2 = fibonacci(i-2);
    n3 = fibonacci(i-3);
    if (key > x[n1])
       n1 =n1 + m ;
    while (n1 >= low)
    {
      if (key < x[n1])
      {			       /* �Ykey < x[n1]�A�h��Ȧb���b�q */
	if (n3 == 0)
	   n1 = 0 ;
	else
	{
	  n1 = n1 - n3 ;
	  j =n2 ;
	  n2 = n3 ;
	  n3 = j- n3 ;
	}
      }
      else if (key > x[n1])
      { 		       /* �Ykey>x[n1]�A�h��Ȧb�k�b�q */
	if (n2 == 1)
	   n1 = 0 ;
	else
	{
	  n1 = n1 + n3 ;
	  n2 = n2 - n3 ;
	  n3 = n3 - n2 ;
	}
      }
      else
      {	     /* �Y�Hkey=x[n1],�N�������,�åHindex �}�C���x�s����Ȫ���m */
	index[++count] = n1  ;
	mid = n1 ;
	n1 = mid - 1 ;
	while (key == x[n1])
	     index[++count] = n1 -- ;
	n1 = mid + 1 ;
	while (key == x[n1])
	     index[++count] = n1 ++ ;
	return(count + 1) ;
      }
    }
    return(-1) ;
 }


 int fibonacci(k)	       /* �إ߶O��ż� */
 int k ;
 {
    if (k == 0)  return(0) ;
    else if (k == 1) return(1) ;
    else return(fibonacci (k-1) + fibonacci (k-2)) ;
 }

 /********************************************************************/
 /*********************** �{���W�� : 7-4.c ***************************/
 /*********************** �{���\�� : ���ɷj�M�k **********************/
 /********************************************************************/

 # include <stdio.h>
 # define N 12
 # define TRUE 1

 int intp_search(int key,int x[],int low,int high,int index[]) ;

 main()
 {
    static int data[N] = {11,23,33,46,54,62,78,89,124,235,341,456} ;
    int i,key,count,index[N] ;
    clrscr();
    while (TRUE)
    {     			       /* �N��l��ƦC�L�X�� */
    for (i = 0; i< N ; i++)
    {
      printf("data[%2d]=%3d  ",i,data[i]) ;
      if ((i+1) %4 == 0)  printf("\n") ;
    }
    printf("\n�п�J�j�M���(^Break : ����) : "); /* ��J���j�M����� */
    scanf("%d",&key) ;
    count=intp_search(key,data,0,N-1,index) ;     /* �I�s���ɷj�M��� */
    printf("=====================================\n") ;
    if (count > 0)
       for(i =0 ; i< count ; i++)
       printf("��� %3d ���F ! �O�bdata[%d] ��m\n",key,index[i]) ;
    else
       printf("��� %3d �䤣�� ! \n",key) ;
       printf("==================================\n") ;  /*�䤣�����*/
       printf("�A �� �� !!! \n");
    }
 }


 int intp_search(key,x,low,high,index)       /* �i�洡�ɷj�M���ʧ@ */
 int key,x[],low,high,index[] ;
 {
    int i,mid,count;
    count = -1 ;
    mid= -100 ;
    while (low <= high)
    {
      mid=low + (key-x[low]) * (high-low) / (x[high]-x[low]);/* �]�w�έp��ץ��q */
      if (key < x[mid])
      { 		        /* ��key<x[mid]�A����high���Ш�mid-1 ��m */
	if (high != mid -1)
	   high = mid-1;
	else  return(-1) ;
      }
      else if (key > x[mid])
      {
	if (low != mid +1)     /* ��key>x[mid]�A����low���Ш�mid+1����m */
	   low = mid +1 ;
	else  return(-1) ;
      }
      else
      {
	index[++count] = mid ;
	/* ��key=x[mid]�A�N������ȡA�åHindex�}�C������Ȫ���m*/
	i = mid -1 ;
	while (key == x[i])
	     index[++count] = i -- ;
	i = mid + 1 ;
	while (key ==x[i])
	     index[++count] = i ++ ;
	return(count + 1) ;
      }
    }
    return(-1) ;
 }



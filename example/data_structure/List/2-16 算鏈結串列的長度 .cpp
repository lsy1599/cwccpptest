 /*******************************************************/
 /*************** 程式名稱 : 2-16.c *********************/
 /*************** 計算鏈結串列的長度 ********************/
 Procedure Length(node_ptr L)             /*  程式片段 */
 {
  int num=0;
  node_ptr p=L;
  while(!p)
  {
    num++;
    p==p->Link;
  }
  return(num);
 }

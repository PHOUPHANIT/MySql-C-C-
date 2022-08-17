#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<mysql.h>
#include"NFA.h"
#include"DFA.h"
#include"Table.h"


using namespace std;

char table[50][50];
char s[50];
char query[100];
int succ = 0;
void check()
{
    int snum;
    int synum;
    int fsnum;
    char sstate;
    char fstate[20];
    char state[20];
    char sym[20];
    char *t[20][20];

    printf("Enter the number of state: "); scanf("%d",&snum);

    for (int i=0;i<snum;i++)
    {
        printf("Enter state %d : ",i+1);
        scanf("%s",&state[i]);
        s[i]=state[i];
    }
    printf("Enter the number of symbol: "); scanf("%d",&synum);

    for (int j=0;j<synum;j++)
    {
        printf("Enter symbol %d : ",j+1);
        scanf("%s",&sym[j]);
    }

    printf("Enter start state: "); scanf("%s",&sstate);
    printf("Enter number of final state: "); scanf("%d",&fsnum);

    for (int k=0;k<fsnum;k++)
    {
        printf("Enter final state %d : ",k+1);
         scanf("%s",&fstate[k]);
    }
    printf("Enter the transaction: \n");

    for(int p=0;p<strlen(state);p++)
    {
        for(int q=0;q<strlen(sym);q++)
        {
            printf("Enter the transaction of %c through %c : ",state[p],sym[q]); scanf("%s",&t[p][q]);
        }
    }
    system("pause");
    system("cls");
    printf("\n\t\tState: ");
    for(int i=0;i<snum;i++)
    {
        printf("%c, ",state[i]);
    }
    printf("\n\t\tSymbol: ");
    for(int i=0;i<synum;i++)
    {
        printf("%c, ",sym[i]);
    }
    printf("\n\t\tStart state: %c",sstate);
    printf("\n\t\tFinal state: ");
    for(int i=0;i<sizeof(fstate);i++)
    {
        printf("%c",fstate[i]);
    }

    printf("\n\n\n\tTransaction table: \n\n");
    cout<<"\t\t\tState/Symbol|";
    for(int i=0;i<synum;i++)
    {
        printf("\t%c   |",sym[i]);
    }
    cout<<endl;
    for(int p=0;p<strlen(state);p++)
    {
        if(state[p]==sstate)
        {
            printf("\t\t\t\t->%c |\t",state[p]);
        }
        else if(state[p]==fstate[p])
        {
            printf("\t\t\t\t*%c  |\t",state[p]);
        }
        else{
            printf("\t\t\t\t %c  |\t",state[p]);
        }

        for(int h=0;h<strlen(sym);h++)
        {
            printf("%s   |\t",&t[p][h]);

        }
        cout<<endl;
    }
    cout<<endl;
    int flag;
    for(int i=0;i<snum;i++)
    {
        for(int j=0;j<synum;j++)
        {
            if(t[i][j]=="-"||sym[j]=='e')
            {
                flag=0;

            }
            else
            {
                flag=1;
            }
        }
    }
    if(flag==0)
    {
        cout<<"\t\tThis is NFA"<<endl;
    }
    else if(flag==1)
    {
        cout<<"\t\tThis is DFA"<<endl;
    }
    //choice for inserting into database and test string and exit
//    printf("\n\n\t\t\t\t1.Save\t\t2.Test string\t\t3.Exit");
//    int k;
//    printf("\n\t\tOption: "); scanf("%d",&k);


    system("pause");
}
void finish_with_error(MYSQL *conn)
{
  fprintf(stderr, "%s\n", mysql_error(conn));
  mysql_close(conn);
  exit(1);
}
void NFAinput(List *L,List2 *l)
{

    int snum;
    int synum;
    int fsnum;
    char sstate[10];
    char fstate[20];
    char state[20];
    char sym[20];
    char *t[20][20];
    int id,tid,sid;

    MYSQL *conn;

    printf("Enter the number of state: "); scanf("%d",&snum);

    for (int i=0;i<snum;i++)
    {
        printf("Enter state %d : ",i+1);
        scanf("%s",&state[i]);
        s[i]=state[i];
    }
    printf("Enter the number of symbol: "); scanf("%d",&synum);

    for (int j=0;j<synum;j++)
    {
        printf("Enter symbol %d : ",j+1);
        scanf("%s",&sym[j]);
    }

    printf("Enter the transaction: \n");
    printf("Enter start state: "); scanf("%s",&sstate);
    printf("Enter number of final state: "); scanf("%d",&fsnum);

    for (int k=0;k<fsnum;k++)
    {
        printf("Enter final state %d : ",k+1);
         scanf("%s",&fstate[k]);
    }

    for(int p=0;p<strlen(state);p++)
    {
        for(int q=0;q<strlen(sym);q++)
        {
            printf("Enter the transaction of %c through %c : ",state[p],sym[q]); scanf("%s",&t[p][q]);
        }
    }


    printf("\n\t\tEnter IDFA: ");   scanf("%d",&id);
    printf("\t\tEnter TID: ");   scanf("%d",&tid);
    printf("\t\tEnter SID: ");   scanf("%d",&sid);

    conn = mysql_init(0);
    conn = mysql_real_connect(conn,"localhost","root","","automata",0,NULL,0);
        sprintf(query,"INSERT INTO finite_automata_t VALUES(%d,'NFA','%s','%s')",id,sstate,fstate);
       //printf("%s\n",query);
        succ = mysql_query(conn,query);
        sprintf(query,"INSERT INTO transaction_t VALUES(%d,%d,'%s','%s','%s')",tid,id,state,sym,t);
        succ = mysql_query(conn,query);
        sprintf(query,"INSERT INTO state_t VALUES(%d,%d,'%s','%s')",sid,id,state,sym);
        succ = mysql_query(conn,query);

    if(succ==0){
        printf("\n\t\tInsert successful\n\n");
    }else{
        printf("\n\t\tInsert Error\n\n");
    }

    system("pause");
    system("cls");

    printf("\n\t\tState: ");
    for(int i=0;i<snum;i++)
    {
        printf("%c, ",state[i]);
    }
    printf("\n\t\tSymbol: ");
    for(int i=0;i<synum;i++)
    {
        printf("%c, ",sym[i]);
    }
    printf("\n\t\tStart state: %s",sstate);
    printf("\n\t\tFinal state: ");
    for(int i=0;i<fsnum;i++)
    {
        printf("%c ",fstate[i]);
    }

    printf("\n\n\n\tTransaction table: \n\n");
    cout<<"\t\t\tState/Symbol|";
    for(int i=0;i<synum;i++)
    {
        printf("\t%c   |",sym[i]);
    }
    cout<<endl;
    for(int p=0;p<strlen(state);p++)
    {
        if(state[p]==sstate[p])
        {
            printf("\t\t\t\t->%c |\t",state[p]);
        }
        else if(state[p]==fstate[p])
        {
            printf("\t\t\t\t*%c  |\t",state[p]);
        }
        else{
            printf("\t\t\t\t %c  |\t",state[p]);
        }

        for(int h=0;h<strlen(sym);h++)
        {
            printf("%s   |\t",&t[p][h]);

        }
        cout<<endl;
    }

    ElementInsert(L,snum,synum,state,sym,fstate,sstate);
    ElementDisplay(L);
    mysql_close(conn);
}
void DFAinput(List1 *L, List2 *l2)
{

    int snum;
    int synum;
    int fsnum;
    char sstate[10];
    char fstate[20];
    char state[20];
    char sym[20];
    char t[20][20];
    int id,tid,sid;

    MYSQL *conn;

    printf("Enter the number of state: "); scanf("%d",&snum);

    for (int i=0;i<snum;i++)
    {
        printf("Enter state %d : ",i+1);
        scanf("%s",&state[i]);
    }
    printf("Enter the number of symbol: "); scanf("%d",&synum);

    for (int j=0;j<synum;j++)
    {
        printf("Enter symbol %d : ",j+1);
        scanf("%s",&sym[j]);
    }

    printf("Enter start state: "); scanf("%s",&sstate);
    printf("Enter number of final state: "); scanf("%d",&fsnum);

    for (int k=0;k<fsnum;k++)
    {
        printf("Enter final state %d : ",k+1);
         scanf("%s",&fstate[k]);
    }
//  sprintf(query,"INSERT INTO finite_automata_t VALUES(1,'NFA','%s','%s')",sstate,fstate);
//
//    printf("%s\n",query);
    printf("Enter the transaction: \n");

    for(int p=0;p<strlen(state);p++)
    {
        for(int q=0;q<strlen(sym);q++)
        {
            printf("Enter the transaction of %c through %c : ",state[p],sym[q]); scanf("%s",&t[p][q]);
        }
    }


    printf("\n\t\tEnter ID: "); scanf("%d",&id);
    printf("\t\tEnter TID: ");  scanf("%d",&tid);
    printf("\t\tEnter SID: ");  scanf("%d",&sid);

    conn = mysql_init(0);
    conn = mysql_real_connect(conn,"localhost","root","","automata",0,NULL,0);

        sprintf(query,"INSERT INTO finite_automata_t VALUES(%d,'DFA','%s','%s')",id,sstate,fstate);
        succ = mysql_query(conn,query);
        sprintf(query,"INSERT INTO transaction_t VALUES(%d,%d,'%s','%s','%s')",tid,id,state,sym,t);
        succ= mysql_query(conn,query);
        sprintf(query,"INSERT INTO state_t VALUES(%d,%d,'%s','%s')",sid,id,state,sym);
        succ = mysql_query(conn,query);

        if(succ==0){
            printf("\n\t\t Insert successful!\n\n");
        }else{
            finish_with_error(conn);
            printf("\n\t\tNo insert!\n\n");
        }

    system("pause");
    system("cls");

    printf("\n\t\tState: ");
    for(int i=0;i<snum;i++)
    {
        printf("%c, ",state[i]);
    }
    printf("\n\t\tSymbol: ");
    for(int i=0;i<synum;i++)
    {
        printf("%c, ",sym[i]);
    }
    printf("\n\t\tStart state: %s",sstate);
    printf("\n\t\tFinal state: ");
    for(int i=0;i<fsnum;i++)
    {
        printf("%c, ",fstate[i]);
    }

    printf("\n\n\n\tTransaction table: \n\n");
    cout<<"\t\t\tState/Symbol|";
    for(int i=0;i<synum;i++)
    {
        printf("\t%c   |",sym[i]);
    }
    cout<<endl;
    for(int p=0;p<strlen(state);p++)
    {
        if(state[p]==sstate[p])
        {
            printf("\t\t\t\t->%c |\t",state[p]);
        }
        else if(state[p]==fstate[p])
        {
            printf("\t\t\t\t*%c  |\t",state[p]);
        }
        else{
            printf("\t\t\t\t %c  |\t",state[p]);
        }

        for(int h=0;h<strlen(sym);h++)
        {
            printf("%c   |\t",t[p][h]);

        }
        cout<<endl;
    }
    cout<<endl;

    //1.Save    2.Test string   3.Exit to menu
//    printf("\n\n\t\t\t\t1.Save\t\t2.Test string\t\t3.Exit");
//    int k;
//    printf("\n\t\tOption: "); scanf("%d",&k);
    for(int i=0,k=0;i<snum&&k<sizeof(fstate);i++,k++)
    {
        for(int j=0;j<synum;j++)
        {
            TableInsert(l2,snum,fstate[k],state[i],sym[j],t[i][j]);
        }
    }



    ElementInsert1(L,snum,synum,state,sym,fstate,sstate);
    //displayTable(l2);
    //ElementDisplay1(L);
    mysql_close(conn);
    system("pause");
}
void deleteData(){


      MYSQL *conn;
      conn = mysql_init(0);
      conn = mysql_real_connect(conn,"localhost","root","","automata",0,NULL,0);

      int id;

      printf("\n\t\t\tEnter IDFA to delete: "); scanf("%d",&id);
      sprintf(query,"DELETE FROM  finite_automata_t WHERE id = %d",id);
      succ = mysql_query(conn,query);
      sprintf(query,"DELETE FROM  transaction_t WHERE id = %d",id);
      succ = mysql_query(conn,query);
      sprintf(query,"DELETE FROM  state_t WHERE id = %d",id);
      succ = mysql_query(conn,query);
      printf("%s\n",query);

      if(succ==0){
         cout<< "\n\t\tDelete successfully\n";
      }
  mysql_close(conn);
}
void displayFromDatabase(){

      MYSQL *conn;

      conn = mysql_init(0);
      conn = mysql_real_connect(conn,"localhost","root","","automata",0,NULL,0);

            mysql_query(conn,"SELECT *FROM finite_automata_t");

            MYSQL_RES *result = mysql_store_result(conn);

            int num_fields = mysql_num_fields(result);

            MYSQL_ROW row;
           cout<< "\n\t\t\t-------------------------";
           cout<< "\n\t\t\t| FINITE_AUTOMATA_TABLE |\t";
           cout<< "\n\t\t\t-------------------------\n\n";
           cout<< "\n\tID\t\tType\t\tStart_state\tFinal_state\n";
           cout<< "\t___________________________________________________________"<<endl;
           while((row=mysql_fetch_row(result))){
                  printf("\n");
                  for(int i = 0; i < mysql_num_fields(result); i++){
                      printf("\t%s\t", row[i] ? row[i] : "NULL");

                  }
           cout<< "\n\t___________________________________________________________";
               printf("\n");
           }




           mysql_query(conn,"SELECT *FROM state_t");

           MYSQL_RES *result1 = mysql_store_result(conn);
           int num_fields1 = mysql_num_fields(result1);
           MYSQL_ROW row1;
           cout<< "\n\n\n\n\t\t\t-------------------------";
           cout<< "\n\t\t\t|      STATE_TABLE      |\t";
           cout<< "\n\t\t\t-------------------------\n\n";
           cout<< "\n\tSID\t\tID\t\tState\t\tAlphabet\n";
           cout<< "\t___________________________________________________________"<<endl;
           while((row1=mysql_fetch_row(result1))){
                  printf("\n");
                  for(int i = 0; i < mysql_num_fields(result1); i++){
                      printf("\t%s\t", row1[i] ? row1[i] : "NULL");

                  }
           cout<< "\n\t___________________________________________________________";
               printf("\n");
           }


           mysql_query(conn,"SELECT *FROM transaction_t");

           MYSQL_RES *result2 = mysql_store_result(conn);
           int num_fields2 = mysql_num_fields(result2);
           MYSQL_ROW row2;
           cout<< "\n\n\n\n\t\t\t-------------------------------";
           cout<< "\n\t\t\t|      TRANSACTION_TABLE      |\t";
           cout<< "\n\t\t\t-------------------------------\n\n";
           cout<< "\n\tTID\t\tID\t\tState\t\tAlphabet\tToState\n";
           cout<< "\t______________________________________________________________________"<<endl;
           while((row2=mysql_fetch_row(result2))){
                  printf("\n");
                  for(int i = 0; i < mysql_num_fields(result2); i++){
                      printf("\t%s\t", row2[i] ? row2[i] : "NULL");

                  }
           cout<< "\n\t______________________________________________________________________";
               printf("\n");
           }



  mysql_free_result(result);
  mysql_close(conn);

}
int main()
{
    NFAelement *e;
    List *L;
    L=createList();

    Table *t;
    List2 *l2;
    l2=createlist2();

    DFAelement *d;
    List1 *L1;
    L1=createList1();


    int a;
    cout<<"\n\n\n\n\t\t\t\t\t\t1.FA test\n\n\t\t\t\t\t\t2.Create NFA\n\n\t\t\t\t\t\t3.Create DFA\n\n\t\t\t\t\t\t4.Display FA\n\n\t\t\t\t\t\t5.Delete FA\n\n\t\t\t\t\t\t6.Exit"<<endl;
    cout<<"\n\n\t\t\tSelect option: "; cin>>a;
    system("cls");
    if(a==1)
    {
        check();

    }

    else if(a==2)
    {
        NFAinput(L,l2);
        //closure(l2,L);
    }
    else if (a==3)
    {
        DFAinput(L1,l2);
    }
    else if (a==4)
    {
      displayFromDatabase();
    }
    else if(a==5)
    {
      deleteData();
    }
    else if(a==6)
    {

    }

}

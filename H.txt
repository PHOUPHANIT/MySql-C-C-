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
void NFAinput(List *L,List2 *l)
{

    int snum;
    int synum;
    int fsnum;
    char sstate[20];
    char fstate[20];
    char state[20];
    char sym[20];
    char t[20][20];


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
    int id,tid,sid;

    printf("\n\t\tEnter ID: "); scanf("%d",&id);
    printf("\n\t\tEnter TID: "); scanf("%d",&tid);
    printf("\n\t\tEnter SID: "); scanf("%d",&sid);

    conn = mysql_init(0);
    conn = mysql_real_connect(conn,"localhost","root","","automata",0,NULL,0);

        sprintf(query,"INSERT INTO finite_automata_t VALUES(%d,'NFA','%s','%s')",id,sstate,fstate);
        mysql_query(conn,query);
        sprintf(query,"INSERT INTO transaction_t VALUES(%d,%d,'%s','%s','%s')",tid,id,state,sym,t);
        mysql_query(conn,query);
        sprintf(query,"INSERT INTO state_t VALUES(%d,%d,'%s','%s')",sid,id,state,sym);
        mysql_query(conn,query);
        if(conn){
            printf("\n\t\t Insert successful!\n");
        }else{
            printf("\n\t\tNo insert!\n");
        }


    cout<<endl;
    cout<<"State/Symbol";
    for(int i=0;i<synum;i++)
    {
        printf("\t%c",sym[i]);
    }
    cout<<endl;
    for(int p=0;p<strlen(state);p++)
    {
        if(state[p]==sstate[p])
        {
            printf("\t->%c\t",state[p]);
        }
        else if(state[p]==fstate[p])
        {
            printf("\t*%c\t",state[p]);
        }
        else{
            printf("\t %c\t",state[p]);
        }

        for(int h=0;h<strlen(sym);h++)
        {
            printf("%c \t",t[p][h]);
            table[p][h]=t[p][h];
        }
        cout<<endl;
    }
    cout<<endl;
    char ta[50];

    //1.Save    2.Test string   3.Exit to menu  4.Convert to DFA




    ElementInsert(L,snum,synum,state,sym,fstate,sstate);

    for(int i=0;i<snum;i++)
    {
        for(int j=0,k=1;j<synum&&k<=snum*synum;j++,k++)
        {
            TableInsert(l,k,snum,state[i],sym[j],t[i][j]);
            //root=Insert(root,snum,synum,state[i],sym[j],t[i][j]);
        }


    }


    //ElementDisplay(L);
    //displayTable(l);


}
void closure(List2 *l2,List *L)
{
    Table *t;
    t=l2->Front;

    NFAelement *e;
    e=L->Front;



    char ta[50][50];

    for(int i=0;i<e->synum-1;i++)
    {
        cout<<"\t"<<e->symbol[i];
    }
    cout<<endl;
    for(int i=0;i<e->snum;i++)
    {
        cout<<e->state[i]<<"\t";

        for(int j=0;j<e->synum-1;j++)
        {
            cout<<table[i][j]<<"\t";
            ta[i][j]=table[i][j];

        }
        cout<<endl;
    }
    cout<<endl;

    char b[50];
    for(int i=0;i<e->synum-1;i++)
    {
        cout<<"\t"<<e->symbol[i];
    }
    cout<<endl;
   while(l2->n!=NULL)
    {
        for(int i=0,j=0;i<t->snum&&j<e->synum;i++,j++)
        {
           if(t->state==s[i]&&t->sym=='e')
            {
                if(t->tran=='-')
                {
                    cout<<ta[i][j]<<endl;
                }
                else
                {
                    cout<<ta[i][j]<<t->tran<<endl;
                }
            }
        }
        t=t->next;
   }



    //displayTable(l2);

}
void DFAinput(List1 *L)
{

    int snum;
    int synum;
    int fsnum;
    char sstate[20];
    char fstate[20];
    char state[20];
    char sym[20];
    char t[20][20];

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

    printf("Enter the transaction: \n");

    for(int p=0;p<strlen(state);p++)
    {
        for(int q=0;q<strlen(sym);q++)
        {
            printf("Enter the transaction of %c through %c : ",state[p],sym[q]); scanf("%s",&t[p][q]);
        }
    }

    int id,tid,sid;

    printf("\n\t\tEnter ID: "); scanf("%d",&id);
    printf("\n\t\tEnter TID: "); scanf("%d",&tid);
    printf("\n\t\tEnter SID: "); scanf("%d",&sid);

    conn = mysql_init(0);
    conn = mysql_real_connect(conn,"localhost","root","","automata",0,NULL,0);

        sprintf(query,"INSERT INTO finite_automata_t VALUES(%d,'DFA','%s','%s')",id,sstate,fstate);
        mysql_query(conn,query);
        sprintf(query,"INSERT INTO transaction_t VALUES(%d,%d,'%s','%s','%s')",tid,id,state,sym,t);
        mysql_query(conn,query);
        sprintf(query,"INSERT INTO state_t VALUES(%d,%d,'%s','%s')",sid,id,state,sym);
        mysql_query(conn,query);
        if(conn){
            printf("\n\t\t Insert successful!\n");
        }else{
            printf("\n\t\tNo insert!\n");
        }

    cout<<endl;
    cout<<"State/Symbol";
    for(int i=0;i<synum;i++)
    {
        printf("\t%c",sym[i]);
    }
    cout<<endl;
    for(int p=0;p<strlen(state);p++)
    {
        if(state[p]==sstate[p])
        {
            printf("\t->%c\t",state[p]);
        }
        else if(state[p]==fstate[p])
        {
            printf("\t*%c\t",state[p]);
        }
        else{
            printf("\t %c\t",state[p]);
        }

        for(int h=0;h<strlen(sym);h++)
        {
            printf("%c \t",t[p][h]);
        }
        cout<<endl;
    }
    cout<<endl;

    //1.Save    2.Test string   3.Exit to menu
    ElementInsert1(L,snum,synum,state,sym,fstate,sstate);
    //ElementDisplay1(L);
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
    cin>>a;
    if(a==1)
    {
        NFAinput(L,l2);
        closure(l2,L);
    }

    else if(a==2)
        DFAinput(L1);


}


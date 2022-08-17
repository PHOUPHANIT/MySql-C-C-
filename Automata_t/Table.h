#include<iostream>
using namespace std;

struct Table
{
    int snum,id;
    char state;
    char sym;
    char tran;

    Table *next;
};
struct List2
{
    int n;
    Table *Front;
    Table *Rear;
};
List2 *createlist2()
{
    List2 *ls;
    ls = new List2();
    ls->n=0;
    ls->Front=NULL;
    ls->Rear=NULL;
}
void TableInsert(List2 *ls,int ID, int sn, char s,char sy,char t)
{
    Table *e;
    e = new Table();
    e->snum=sn;
    e->id=ID;
    e->state=s;
    e->sym=sy;
    e->tran=t;
    e->next=NULL;

    if(ls->n==0)
    {
        ls->Front=e;
        ls->Rear=e;
    }
    if(ls->n!=0)
    {
        ls->Rear->next=e;
        ls->Rear=e;
    }
    ls->n=ls->n+1;
}
void displayTable(List2 *ls)
{
    Table *tmp;
    tmp=ls->Front;
    while(ls->n!=NULL)
    {

        cout<<tmp->id<<endl;
        cout<<"\t"<<tmp->state<<"\t"<<tmp->sym<<"\t"<<tmp->tran<<endl;


        tmp=tmp->next;
    }
    cout<<endl;
}

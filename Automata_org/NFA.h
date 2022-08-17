#include<iostream>
using namespace std;

struct NFAelement
{
    int snum;
    int synum;
    string state;
   string symbol;
    string Fstate;
    string Sstate;

    NFAelement *next;
};
struct List
{
    int n;
    NFAelement *Front;
    NFAelement *Rear;
};
List* createList()
{
    List *ls;
    ls = new List();
    ls->n =0;
    ls->Front = NULL;
    ls->Rear = NULL;
}

void ElementInsert(List *ls,int sn,int syn,string s, string sym, string f, string ss)
{
    NFAelement *e;
    e=new NFAelement();
    e->snum=sn;
    e->synum=syn;
    e->state=s;
    e->symbol=sym;
    e->Fstate=f;
    e->Sstate=ss;
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


void ElementDisplay(List *ls)
{
    NFAelement *tmp;
    tmp=ls->Front;
    while(ls->n!=NULL)
    {
        for( int i=0;i<tmp->synum;i++)
        {
            cout<<"\t"<<tmp->symbol[i];
        }
        cout<<endl;
        for(int i=0;i<tmp->snum;i++)
        {
            cout<<tmp->state[i]<<endl;
        }

        tmp=tmp->next;
    }
    cout<<endl;
}

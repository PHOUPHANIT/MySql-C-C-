#include<iostream>
using namespace std;

struct DFAelement
{
    int snum;
    int synum;
    string state;
    string symbol;
    string Fstate;
    char Sstate;

    DFAelement *next;
};
struct List1
{
    int n;
    DFAelement *Front;
    DFAelement *Rear;
};
List1* createList1()
{
    List1 *ls;
    ls = new List1();
    ls->n =0;
    ls->Front = NULL;
    ls->Rear = NULL;
}

void ElementInsert1(List1 *ls,int sn,int syn,string s, string sym, string f, char ss)
{
    DFAelement *e;
    e=new DFAelement();
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
void ElementDisplay1(List1 *ls)
{
    DFAelement *tmp;
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

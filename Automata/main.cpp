#include<iostream>
#include<vector>
#include<bits/stdc++.h>
#include<string.h>
#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
const int M=100;
const int N=100;
string dfa[M][N];
string nfa[M][N];
string query;
vector<string> Nstate;
vector<string> Nalpha;
vector<string> Dstate;
vector<string> Dalpha;
vector<string> fdstate;
vector<string> fnstate;
//vector<string> nfa;

struct NFA
{
    int nstate;
    int nalpha;
    string NSstate;
    NFA *next;
};
struct DFA
{
    int n_state;
    int n_alpha;
    string DSstate;
    //string _state;
    //string _alpha;

    DFA *next;
};
struct dList
{
    int a;
    DFA *Front;
    DFA *Rear;
};
dList *createList1()
{
    dList *ls;
    ls = new dList();
    ls->a=0;
    ls->Front=NULL;
    ls->Rear=NULL;
}
struct List
{
    int n;
    NFA *Front;
    NFA *Rear;
};
List *createList()
{
    List *ls;
    ls = new List();
    ls->n=0;
    ls->Front=NULL;
    ls->Rear=NULL;
}

void EnqueueNFA(List *ls,int ns,int na,string NS )
{
    NFA *e;
    e = new NFA();
    e->nstate=ns;
    e->nalpha=na;
    e->NSstate=NS;


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
void displayD(dList *ls)
{
    DFA *tmp;
    tmp=ls->Front;
    while(ls->a!=NULL)
    {
        cout<<tmp->n_state<<" "<<tmp->n_alpha<<" "<<tmp->DSstate;
        tmp=tmp->next;
    }
    cout<<endl;
}
void displayN(List *ls)
{
    NFA *tmp;
    tmp=ls->Front;
    while(ls->n!=NULL)
    {
        cout<<tmp->nstate<<" "<<tmp->nalpha<<" "<<tmp->NSstate;
        tmp=tmp->next;
    }
    cout<<endl;
}

void EnqueueDFA(dList *l,int ns,int na,string NA)
{
    DFA *d;
    d = new DFA();
    d->n_state=ns;
    d->n_alpha=na;
    d->DSstate=NA;
    d->next=NULL;

    if(l->a==0)
    {
        l->Front=d;
        l->Rear=d;
    }
    if(l->a!=0)
    {
        l->Rear->next=d;
        l->Rear=d;
    }
    l->a=l->a+1;
}

void NFAinput(List *ls)
{
    MYSQL* conn;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn,"localhost","root","","automata",0,NULL,0);
    int ns,na;
    string state,alpha;

    cout<<"Enter number of state: "; cin>>ns;
    cout<<"Enter state: ";
    cin>>state;

    //vector<int> state_;
    stringstream s1(state);
    while (s1.good()) {
        string substr;
        getline(s1, substr, ',');
        Nstate.push_back(substr);
    }
    cout<<"Enter number of alphabet: "; cin>>na;
    cout<<"Enter alphabet: ";
     cin>>alpha;

    //vector<int> alpha_;
    stringstream s2(alpha);
    while (s2.good()) {
        string substr;
        getline(s2, substr, ',');
        Nalpha.push_back(substr);
    }
    string snstate,fstate;
    cout<<"Enter start state: "; cin>>snstate;
    cout<<"Enter the final state: "; cin>>fstate;

    stringstream F(fstate);
    while(F.good())
    {
        string substr;
        getline(F,substr,',');
        fnstate.push_back(substr);
    }
    EnqueueNFA(ls,ns,na,snstate);//state_,alpha_);

    //string nfa[Nstate.size()][Nalpha.size()];
//transaction part
    for(size_t i=0;i<Nstate.size();i++)
    {
        cout<<"Enter the transaction of "<<Nstate[i];
        for(size_t j=0;j<Nalpha.size();j++)
        {
            cout<<" through "<<Nalpha[j]<<endl;
            cin>> nfa[i][j];
        }
    }
//print transaction in 2d array form
    //cout<<Nstate[0]<<Nalpha[0];
    cout<<"State/Alphabet";
    for (size_t i = 0; i < Nalpha.size(); i++)
        {
            cout <<"\t"<< Nalpha[i] << " ";
        }
        cout<<endl;
     for (size_t i = 0; i < Nstate.size(); i++)
        {
            if (Nstate[i]==snstate)
                {cout <<"\t->"<<Nstate[i];}
            else if (Nstate[i]!=snstate)
                {cout<<"\t  "<<Nstate[i];}
            for(size_t j=0;j<Nalpha.size();j++)
            {

                cout <<"\t"<<nfa[i][j] ;

            }
            cout<<endl;
        }
//        string str = "INSERT INTO finite_automata_t VALUES";
//        for (size_t i = 0; i < Nstate.size(); i++){
//            mysql_query(conn,query);
//        }

//insert into FA table: id,type,snstate,fnstate[i]
//insert into transaction table: tid,id,Nstate[i],Nalpha[j],nfa[i][j]
}
void DFAinput(dList*l)
{
    MYSQL* conn;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn,"localhost","root","","automata",0,NULL,0);
    int dns,dna;
    if(conn){
        cout<< "Connected.\n";
    }
    string dstate,dalpha;

    cout<<"Enter the number of state: "; cin>>dns;
    cout<<"Enter state: "; cin>>dstate;
    stringstream sds(dstate);
    while(sds.good())
    {
        string substr;
        getline(sds,substr,',');
        Dstate.push_back(substr);
    }

    cout<<"Enter the number of alphabet: "; cin>>dna;
    cout<<"Enter the alphabet: "; cin>>dalpha;
    stringstream sda(dalpha);
    while(sda.good())
    {
        string substr;
        getline(sda,substr,',');
        Dalpha.push_back(substr);
    }

    string sdstate,fstate;
    cout<<"Enter start state: "; cin>>sdstate;
    cout<<"Enter the final state: "; cin>>fstate;

    for (size_t i=100;i<Dstate.size();i++){

            mysql_query(conn,"INSERT INTO finite_automata_t VALUES(100,'DFA',"+"'"+sdstate+"'"+","+"'"+fnstate[i]+"'"+");");


    }



    stringstream Fs(fstate);
    while(Fs.good())
    {
        string substr;
        getline(Fs,substr,',');
        fdstate.push_back(substr);
    }

    string dfa[Dstate.size()][Dalpha.size()];

    for(size_t i=0;i<Dstate.size();i++)
    {
        cout<<"Enter the transaction of "<<Dstate[i];
        for(size_t j=0;j<Dalpha.size();j++)
        {
            cout<<" through "<<Dalpha[j]<<endl;
            cin>> dfa[i][j];
        }
    }
    //cout<<Nstate[0]<<Nalpha[0];
    cout<<"State/Alphabet";
    for (size_t i = 0; i < Dalpha.size(); i++)
        {
            cout <<"\t"<< Dalpha[i] << " ";
        }
        cout<<endl;
        size_t k;
     for (size_t i = 0; i < Dstate.size(); i++)
        {

            if(Dstate[i]==sdstate)
            {
                cout <<"\t->"<<Dstate[i];
            }
            else if(Dstate[i]!=sdstate)
            {
                cout<<"\t  "<<Dstate[i];
            }
//            else if(Dstate[i]==fdstate[k])
//            {
//                cout<<"\t* "<<Dstate[i];
//            }
//            else if(Dstate[i]!=fdstate[k])
//            {
//                cout<<"\t  "<<Dstate[i];
//            }


            for(size_t j=0;j<Dalpha.size();j++)
            {

                cout <<"\t"<<dfa[i][j] ;

            }
            cout<<endl;
        }
    EnqueueDFA(l,dns,dna,sdstate);

//insert into FA table: id,type,sdstate,fdstate[i]
//insert into transaction table: tid,id,Dstate[i],Dalpha[j],dfa[i][j]

}

int main()
{
    dList*l;
    DFA *d;
    l=createList1();

    List *L;
    NFA *e;
    L=createList();

    int n;
    cout<<"1.NFA\n2.DFA"<<endl;
    cout<<"Enter option: "; cin>>n;

    if(n==1)
    {
        NFAinput(L);
        //displayN(L);
        //closure(L);
    }

    else if(n==2)
       {
            DFAinput(l);
            //displayD(l);
       }

}

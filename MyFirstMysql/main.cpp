#include <iostream>
#include <Windows.h>
#include <mysql.h>
#include <iomanip>
#include <stdlib.h>
#include <sstream>
#include <stdio.h>
using namespace std;

int main()
{
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES * res;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn,"localhost","root","","test",0,NULL,0);
    if(conn){
        cout<< "Connection";
    }else{
        cout<< "Unconnection";
    }
}

#include <iostream>
#include<mysql.h>

using namespace std;

int main()
{
    MYSQL *conn;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn,"localhost","root","","test",0,NULL,0);

    if(conn){
        cout<< "Connection";
    }else{
        cout<< "Fail";
    }
}

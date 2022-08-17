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


    int qstate;

    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "localhost", "root", "", "test", 0, NULL, 0);

    if(conn)
    {
        cout <<" Connection to database successful:"<<endl;

        string f_name, l_name, username, password;

        cout <<" Enter your first name"<<endl;
        cin >> f_name;

        cout <<" Enter last name"<<endl;
        cin >> l_name;

        cout <<" Enter username"<<endl;
        cin >> username;

        cout<<" Enter password:"<<endl;
        cin>> password;


        stringstream ss;

        ss << " INSERT INTO registration (First_Name, Last_Name, Username, Password) values ('" << f_name<<"','" << l_name<<" ','" <<username<<" ','" <<password <<"')";

        string query = ss.str ();
        const char * q = query.c_str();
        qstate = mysql_query(conn, q);

        if (qstate == 0)
        {

            cout <<" Record inserted successfully ..."<<endl;
        }
        else
        {
            cout <<" Error, data not inserted..."<<endl;
        }
    }

    if (conn)
    {
        qstate = mysql_query(conn, "SELECT * FROM registration");

        if (!qstate)
        {
            res = mysql_store_result(conn);


            while (row = mysql_fetch_row (res))
            {



                cout<<" ID : "<< row [0]<<endl;
                cout <<" First name: "<<row [1]<<endl;
                cout <<" Last name: "<< row [2]<<endl;
                cout <<" Username: " <<row [3] <<endl;
            }
        }
    }

    else
    {
        cout <<" Connection failure"<<endl;
    }

    return 0;
}

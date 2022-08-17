#include<iostream>
#include<math.h>
#include<string.h>
#include<mysql.h>
#include<stdio.h>
using namespace std;

int BinToDec(int bin){
    int dec=0,rem,b=1;
    while (bin>0){
        rem = bin%10;
        dec = dec + rem*b;
        b= b*2;
        bin = bin /10;
    }
    return dec;
   // cout<<dec<<endl;
}
void DecToOcta(int bin){

    int dec=0,rem,b=1;
    while (bin>0){
        rem = bin%10;
        dec = dec + rem*b;
        b= b*2;
        bin = bin /10;
    }
    int Dec=dec;
    int octa[100],i=0;
    while (Dec!=0){
        octa[i] = Dec%8;
        Dec=Dec/8;
        i++;
    }
    for(int j=i-1;j>=0;j--){

       cout<<octa[j];
    }
}

int convertBinarytoOctal(long long binaryNumber){
    int octalNumber = 0, decimalNumber = 0, i = 0;

    while(binaryNumber != 0){
        decimalNumber += (binaryNumber%10) * pow(2,i);
        ++i;
        binaryNumber/=10;
    }

    i = 1;

    while (decimalNumber != 0){
        octalNumber += (decimalNumber % 8) * i;
        decimalNumber /= 8;
        i *= 10;
    }

    return octalNumber;
}
int main()
{

    MYSQL *conn;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn,"localhost","root","","BaseConversion",0,NULL,0);

    char query[100];
    int num;
    int n;


while(1){
    int option;
    cout<< "\n\t\t1. Convert Binary to Decimal and octal";
    cout<< "\n\t\t2. Display History";
    cout<< "\n\n\t\tEnter the option: ";cin>>option;
    if(option==1){
            printf("\n\n\t\t\t\tEnter binary number: "); scanf("%d",&num);
            int Dec;
            //cout<<num<<" convert into decimal number: ";
            n=BinToDec(num);
            cout<<"\n\t\t"<<num<<"\tConvert into decimal number: "<<n<<endl;
            cout<<"\t\t"<<num<<"\tConvert into octal number: ";
            DecToOcta(num);
            cout<<endl;
            cout<<endl;
            cout<<endl;

          int oc;
          oc = convertBinarytoOctal(num);
          sprintf(query,"INSERT INTO Base VALUES(%d,%d,%d)",num,n,oc);
          mysql_query(conn,query);

    }
    if(option==2){

            int state;
            state = mysql_query(conn,"SELECT *FROM Base");
            if (state !=0){
               cout <<mysql_error(conn);
               return 1;
            }

            MYSQL_RES *result = mysql_store_result(conn);

            int num_fields = mysql_num_fields(result);

            MYSQL_ROW row;

           //cout<< "\n\tBinary\t\tDecimal\t\tOctal\n";
           while((row=mysql_fetch_row(result))){
                  printf("\n");
                  for(int i = 0; i < mysql_num_fields(result); i++){
                      printf("\t%s\t", row[i] ? row[i] : "NULL");
                  }

               printf("\n");
           }

    }if(option!=1 && option!=2){
        cout<< "\n\t\tInvariable input!\n";

    }
}

     mysql_free_result(result);
     mysql_close(conn);

     return 0;
}


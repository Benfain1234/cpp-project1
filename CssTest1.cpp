
#include "CssProject1.h"
using namespace std;



int main(){
// Account class tests

    Account A1(0,657483,5000);  //Account constructor test
    if (A1.GetBalance()!=5000)                       //Account.GetBalance test
        cout << "GetBalance failed"<<endl;

    if (A1.GetAccountNumber()!=657483)               //Account.GetAccountNumber test
        cout <<"GetAccountNumber failed"<<endl;

    A1.SetNumberOfTransaction(5);               //Account.set/get Number of transactions test
    if (A1.GetNumOfTransactions()!=5)
        cout <<"GetNumOfTransactions failed";



    // Person class tests
    Person P1("Ben",206844375,A1);         //Person constructor test
    if (strcmp(P1.GetName(),"Ben")!=0)
        cout<<"P1.GetName failed"<<endl;

     P1.Deposit(5000);                          //Person.Deposit test
    if (P1.GetBalance()!=10000||P1.GetMonthlyBalance()!=5000)
      cout <<"P1.Deposit failed" <<endl;


    P1.Withdrew(5000);                           //Person.Withdrew test
    if(P1.GetBalance()!=5000||P1.GetMonthlyBalance()!=0)
        cout <<"P1.Withdrew failed"<< endl;

 // Banker class tests
 Account A2(0,768594,10000);
 Account A3(0,865432,13754);
 Person P2("Dave",207754382,A2);
 Person P3("Ron",203659750,A3);
 Banker B1(11,P1);

 B1.AddPerson(P2);
 B1.AddPerson(P3);
    if (B1.GetPerson("Ron").GetId()!=203659750)         //Banker.AddPerson test
        cout<<"B1.GetPerson failed"<<endl;

 if (B1.GetBalance("Dave")!=10000)                     //Banker.GetBalance test
        cout<<"B1.GetBalance failed"<<endl;

    B1.BankerDeposit(5000,P3);                      //Banker.Deposit test
    if (B1.GetBalance("Ron")!=18754)
        cout<<"B1.BankerDeposit failed"<<endl;

    B1.BankerWithdrew(3000,P1);                    //Banker.Withdrew test
    if (B1.GetBalance("Ben")!=2000)
        cout<<"B1.BankerWithdrew failed"<<endl;

    B1.BankerDeposit(3000,P2);                     //Banker.BalanceStatus& Banker.PositiveStatus test
    if (B1.BalanceStatus(B1.GetPerson("Dave"))!=1||B1.PositiveStatus()!=2)
        cout<<"B1.BankerDeposit failed"<<endl;

    //Manager class tests
    Manager M1(B1);
    if (M1.NumberOfBankers()!=1)                   //Manager constructor test
        cout<< "M1 constructor failed"<<endl;
    Account A4(0,765843,6854);
    Account A5(0,986432,19085);
    Person P4("Liran",286543219,A4);
    Person P5("Elad",201754396,A5);
    Banker B2(13,P4);
    B2.AddPerson(P5);
    M1.AddBanker(B2);

    if (M1.NumberOfBankers()!=2)          //Manager.AddBanker test
        cout<<"M1.AddBanker failed"<<endl;

    Banker B3(M1.GetBanker(13));    //Manager.GetBanker test
    if (B3.GetEmployeeNumber()!=13)
        cout<<"M1.GetBanker failed"<<endl;

    return 0;
}
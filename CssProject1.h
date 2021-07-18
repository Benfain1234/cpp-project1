#include <__bit_reference>

#ifndef PERSON_H
#define PERSON_H
using namespace std;
#include <string.h>
#include <iostream>

class Account
{
private:

    int				m_numberOfTransaction;
    int				m_accountNumber;
    double			m_balance;
public:
    Account(){                     //default constructor
        m_numberOfTransaction=0;
        m_accountNumber=0;
        m_balance=0;
    }
    Account( int Trans, int Anum, double balance ){   //constructor
        m_balance=balance;
        m_accountNumber=Anum;
        m_numberOfTransaction=Trans;
    }
    Account( const Account& other ){    //copy constructor
        m_numberOfTransaction=other.m_numberOfTransaction;
        m_accountNumber=other.m_accountNumber;
        m_balance=other.m_balance;
    }


public:
   void SetNumberOfTransaction(int num){
        m_numberOfTransaction=num;
    }

     void			SetAccountNumber( int number ){
        m_accountNumber=number;
    }
    void			SetBalance( double balance ){
        m_balance=balance;
    }
    int				GetNumOfTransactions(){
        return m_numberOfTransaction;
    }
    int				GetAccountNumber() const{
        return m_accountNumber;
    }
    double			GetBalance() const{
        return m_balance;
    }





};

class Person
{
public:
   friend class Banker;
    Person(){       //default constructor
        m_MonthlyBalance=0;
        m_maxTransMonth=20;
        m_name= nullptr;
        m_id=0;
        m_a=nullptr;
    }
    Person(const char* name, int id , const Account &A){    //constructor
       m_MonthlyBalance=0;
        m_maxTransMonth=20;
        m_name=new char[strlen(name)+1];
        strcpy(m_name,name);
        m_id=id;
        m_a= new Account(A);
    }
    Person(const Person& other ){    //copy constructor
       m_MonthlyBalance=other.m_MonthlyBalance;
        m_id=other.m_id;
        m_name=new char [strlen(other.m_name)+1];
        strcpy(m_name,other.m_name);
        m_a= new Account(*other.m_a);
      m_maxTransMonth=20;
    }
    ~Person(){   //destructor
        delete m_name;
    }

public:
   void Deposit(double cash){        //Deposits money in the account
       if(m_a->GetNumOfTransactions()>=m_maxTransMonth)
           return;
        m_a->SetBalance(m_a->GetBalance()+cash);
        m_a->SetNumberOfTransaction(m_a->GetNumOfTransactions()+1);
       m_MonthlyBalance=m_MonthlyBalance+cash;
    }
    void Withdrew(double cash){    //Withdraws money from the account
        if (cash>m_a->GetBalance()||m_a->GetNumOfTransactions()>=m_maxTransMonth)
            return;
        m_a->SetBalance(m_a->GetBalance()-cash);
        m_a->SetNumberOfTransaction(m_a->GetNumOfTransactions()+1);
        m_MonthlyBalance=m_MonthlyBalance-cash;
    }
    void	SetName( const char* newName ){
        delete this->m_name;
        m_name=new char[strlen(newName)+1];
        strcpy(m_name,newName);
    }
    void	SetId( int newId ){
        m_id=newId;
    }
    char*	GetName() const{
        return this->m_name;
    }
    int		GetId() const{
        return m_id;
    };
   double GetBalance(){
       return m_a->GetBalance();
   }
    double GetMonthlyBalance(){ return m_MonthlyBalance;}
private:
   double m_MonthlyBalance;
    int m_maxTransMonth;
    Account*  m_a;
    char*	m_name;
    int		m_id;
};

class Banker{
private:
    int EmployeeNumber;
    int arrsize;
    Person** arr;
public:
    Banker(){      //default constructor
    EmployeeNumber=0;
    arrsize=0;
    arr= nullptr;
}

Banker(int Enum, const Person& p){       //constructor
        EmployeeNumber=Enum;
        arr= new Person*[1];
        arr[0]=new Person(p);
        arrsize=1;
    }
Banker(const Banker& b){          //copy constructor
        this->EmployeeNumber=b.EmployeeNumber;
        this->arrsize=b.arrsize;
        this->arr= new Person*[b.arrsize];
        for(int i=0;i<arrsize;i++)
        arr[i]=new Person(*b.arr[i]);
    }
    ~Banker(){                   //destructor
        int i;
        for(i=0;i<arrsize;i++)
            delete arr[i];
    }
    int GetEmployeeNumber(){return EmployeeNumber;}
    void EndofMonth() {   //resets the data at the end of the month
    int i;
    for (i = 0; i < arrsize; i++) {
        arr[i]->m_a->SetNumberOfTransaction(0);
        arr[i]->m_MonthlyBalance = 0;
    }
}
       int BalanceStatus(const Person& p){   //return 1 if the balance is positive and -1 if negative
           if (p.m_MonthlyBalance>0)
               return 1;
           if (p.m_MonthlyBalance==0)
               return 0;
           return -1;
       }
int PositiveStatus(){  //return the number of persons with positive balance
       int count=0;
        int i;
        for(i=0;i<arrsize;i++)
            if (this->BalanceStatus(*arr[i])==1)
                count++;
    return count;
    }
    int NegativeStatus(){ //return the number of persons with negative balance
        int count=0;
        int i;
        for(i=0;i<arrsize;i++)
            if (this->BalanceStatus(*arr[i])==-1)
                count++;
        return count;
    }

    void AddPerson(const Person& p){      //add person to the arr
        Person**  temparr=new Person*[arrsize + 1];
        for (int i=0;i<arrsize;i++)
            temparr[i]=new Person(*arr[i]);
        for(int i=0;i<arrsize;i++)
            delete arr[i];
        arr=temparr;
        arrsize++;
        arr[arrsize-1]=new Person(p);

    }
  const Person& GetPerson(const char * c){          //return the person that match the name
        for(int i=0;i<arrsize;i++){
            if (strcmp(arr[i]->m_name,c)==0)
                return *arr[i];
        }
    }
   double GetBalance(const char* c){              //return the balance of the person that match the name
        for(int i=0;i< this->arrsize;i++) {
            if (strcmp(arr[i]->m_name, c) == 0)
                return arr[i]->GetBalance();
        }
        cout <<"Not found in database"<< endl;
    }
void BankerDeposit(double cash,const Person& p){     //Deposit the cash in the Account of the Person that match the p

    for (int j = 0; j < this->arrsize; ++j) {
        if (this->arr[j]->m_id==p.m_id) {
            this->arr[j]->Deposit(cash);
            return;
        }
        }
   cout <<"  this person does not exist in the database"<<endl ;
    return;
    }

    void BankerWithdrew(double cash,const Person& p){      //withdrew the cash in the Account of the Person that match the p

        for (int j = 0; j < this->arrsize; ++j) {
            if (this->arr[j]->m_id==p.m_id) {
                this->arr[j]->Withdrew(cash);
                return;
            }
        }
        cout <<"  this person does not exist in the database"<<endl ;
        return;
    }
};



class Manager: public Banker{
private:
    Banker** Barr;
    int Barrsize;
public:


Manager(const Banker& banker):Banker(banker){      //constructor
         Barr= new Banker*[1];
         Barr[0]=new Banker(banker);
         Barrsize=1;
     }
void AddBanker(const Banker& b){              //Add banker to the arr
        int i;
         Banker** temp=new Banker*[Barrsize+1];
         for( i=0;i<Barrsize;i++)
             temp[i]=new Banker(*Barr[i]);
         for(i=0;i<Barrsize;i++)
             delete Barr[i];
         Barr=temp;
         Barr[Barrsize]=new Banker(b);
         Barrsize++;
     }
const Banker& GetBanker(int Enum){               //return the banker that match the EmployeeNumber
    for(int i=0;i<Barrsize;i++)
        if (Barr[i]->GetEmployeeNumber()==Enum)
            return *Barr[i];
        cout<<"Banker not found in database"<<endl;
}
int NumberOfBankers(){
    return Barrsize;
}

~Manager(){                        //destructor
    for(int i=0;i<Barrsize;i++)
        delete Barr[i];
}
};
#endif // !PERSON_H
#include<iostream>
#include<iomanip>
#include<fstream>
#include<cctype>
using namespace std;
class Bank_account{
    int account_number;
    char name[50];
    char type;
    int Money_deposit;
    public:
    void modify();
    void report() const;
    int retacno() const{
        return account_number;
    }
    void dep(int x){
        Money_deposit+=x;
    }
    void draw(int x){
        Money_deposit-=x;
    }
    int retdeposit()const{
        return Money_deposit;
    }
    void create_account();
    void Display_account();
};
void Bank_account::modify(){
    cout<<"\t Account Number: "<<account_number<<endl;
    cout<<"\t Modify Account Holder Name: ";
    cin.ignore();
    cin.getline(name,50);
    cout<<"\t Modify Type of Account:";
    cin>>type;
    type=toupper(type);
    cout<<"\t Modify Balance amount:";
    cin>>Money_deposit;
}
void Bank_account::report()const{
    cout<<account_number<<setw(10)<<" "<<name<<setw(10)<<" "<<type<<setw(6)<<Money_deposit<<endl;
}
void write_account();
void delete_account(int);
void display_details(int);
void display_all();
void Money_deposit_withdraw(int,int);
void Updation_bank_account(int);
void Bank_account :: create_account(){
    system("cls");
    cout<<"\t Enter the account number :-";
    cin>>account_number;
    cout<<"\t Enter the name of the account holder :";
    cin.ignore();
    cin.getline(name,50);
    cout<<"\t Enter the type of the account (c/s) :-";
    cin>>type;
    type=toupper(type);
    cout<<"\t Enter the initial amount (>=500 for saving and >=1000 for current) :-";
    cin>>Money_deposit;
    cout<<endl;
    cout<<"\t Account created....";
}
void Bank_account::Display_account()
{
    cout<<"\t Bank Account Number :"<<account_number<<endl;
    cout<<"\t Account Holder Name :"<<name<<endl;
    cout<<"\t Type of Account :"<<type<<endl;
    cout<<"\t Balance Amount :"<<Money_deposit<<endl;
}
int main(){
    char ch;
    int num;
    cout<<"\t\t ------------------------------------------"<<endl;
    cout<<"\t\t | Welcome to the Bank Management System  |"<<endl;
    cout<<"\t\t ------------------------------------------"<<endl;
    cout<<endl;
    do{
    cout<<"\t --- Main Menu ---"<<endl;
    cout<<"\t 1. Create Account"<<endl;
    cout<<"\t 2. Deposit Money"<<endl;
    cout<<"\t 3. Withdraw Money"<<endl;
    cout<<"\t 4. Balance Enquiry"<<endl;
    cout<<"\t 5. All Account Holder List"<<endl;
    cout<<"\t 6. Close an Account "<<endl;
    cout<<"\t 7. Modify an Account"<<endl;
    cout<<"\t 8. Exit"<<endl;
    cout<<endl;
    cout<<"\t Enter your choice (1-8)";
    cin>>ch;
    switch (ch)
    {
    case '1':
        write_account();
        break;
    case '2':
          system("cls");
          cout<<"\t Enter the account number: ";
          cin>>num;
          Money_deposit_withdraw(num,1);        
          break;
    case '3':
          system("cls");
          cout<<"\t Enter the account number: ";
          cin>>num;
          Money_deposit_withdraw(num,2);
          break;
    case '4':
          system("cls");
          cout<<"\t Enter the account number: ";
          cin>>num;
          display_details(num);
          break;
    case '5':
          display_all();
          break;
    case '6':
         system("cls");
         cout<<"\t Enter the account number: ";
         cin>>num;
         delete_account(num);
          break;
    case '7':
         system("cls");
         cout<<"\t Enter the account number: ";
         cin>>num;
         Updation_bank_account(num);
         break;
    case '8':
          system("cls");
          cout<<"\t Thanks for using the Bank Management System"<<endl;
          break;

    
    }
    // Bank_account B;
    // B.create_account();
    // cout<<endl;
    // B.Display_account();
    cin.ignore();
    cin.get();
    system("cls");
    }while(ch!='8');
    return 0;
}
void write_account(){
    Bank_account ac;
    ofstream outFile;
    outFile.open("account.dat",ios::binary|ios::app);
    ac.create_account();
    outFile.write(reinterpret_cast<char *>(&ac),sizeof(Bank_account));
    outFile.close();
}
void delete_account(int n)
{
    Bank_account ac;
    ifstream inFile;
    ofstream outFile;
    inFile.open("account.dat",ios::binary);
    if(!inFile){
        cout<<"File could not be open !! lpress any key....";
        return ;
    }
    outFile.open("Temp.dat",ios::binary);
    inFile.seekg(0,ios::beg);
    while(inFile.read(reinterpret_cast<char *>(&ac),sizeof(Bank_account)))
    { if(ac.retacno()!=n){
         outFile.write(reinterpret_cast<char *>(&ac),sizeof(Bank_account));
    }

    }
    inFile.close();
    outFile.close();
    remove("Bank_account.dat");
    rename("Temp.dat","Bank_Account.dat");
    cout<<"\t Record Deleted..."<<endl;

}
void display_details(int n){
    Bank_account ac;
    bool flag= false;
    ifstream inFile;
    inFile.open("account.dat",ios::binary);
    if(!inFile){
        cout<<"File could not be open !! press any other key...";
        return ;
    }
    cout<<"\t Bank Account Details "<<endl;
    while(inFile.read(reinterpret_cast<char *>(&ac),sizeof(Bank_account))){
        if(ac.retacno()==n){
            ac.Display_account();
            flag=true;
        }
    }
    inFile.close();
    if(flag==false)
    {
        cout<<"\t Account number does not exist"<<endl;
    }
    
}
void display_all(){
    system("cls");
    Bank_account ac;
    ifstream inFile;
    inFile.open("account.dat",ios::binary);
    if(!inFile)
    {
        cout<<"File could not be open !! Press any key...";
        return ;
    }
    cout<<"\t Bank Account Holder List"<<endl;
    cout<<"=================================================="<<endl;
    cout<<"A/c no.      Name           Type           BALANCE"<<endl; 
    cout<<"=================================================="<<endl;
    while(inFile.read(reinterpret_cast<char *>(&ac),sizeof(Bank_account)))
    {
        ac.report();
    }
    inFile.close();
}
void Money_deposit_withdraw(int n,int option){
    int amt;
    bool found =false;
    Bank_account ac;
    fstream File;
    File.open("account.dat",ios::binary|ios::in|ios::out);
    if(!File){
        cout<<"File could not be open !! Press any key...";
        return ;
    }
    while(!File.eof() && found == false){
        File.read(reinterpret_cast<char *>(&ac),sizeof(Bank_account));
        if(ac.retacno()==n){
            ac.Display_account();
            if(option==1)
            {
                cout<<"\t Enter the amount to be deposited: ";
                cin>>amt;
                ac.dep(amt);
            }
            if(option==2){
                cout<<"\t Enter the amount to be withdraw";
                cin>>amt;
                int balance =ac.retdeposit()-amt;
                if(balance ==2){
                    cout<<"\t Insufficient balance"<<endl;
                }
                else{
                    ac.draw(amt);
                }
            }
            int pos=(-1)*static_cast<int>(sizeof(Bank_account));
            File.seekp(pos,ios::cur);
            File.write(reinterpret_cast<char *>(&ac),sizeof(Bank_account));
            cout<<"\t Record updated"<<endl;
            found=true;
        }
    }
    File.close();
    if(found == false){
        cout<<"\t Record Not Found"<<endl;
  }
}
void Updation_bank_account(int n){
    bool found =false;
    Bank_account ac;
    fstream File;
    File.open("account.dat",ios::binary|ios::in|ios::out);
    if(!File){
    cout<<"Fild could not be open !! press any key...";
    return ;
    }
    while(!File.eof() && found ==false){
    File.read(reinterpret_cast<char *>(&ac),sizeof(Bank_account));
    if(ac.retacno()==n){
        ac.Display_account();
        cout<<"\t Enter the new details of the account"<<endl;
        ac.modify();
        int pos=(-1)*static_cast<int>(sizeof(Bank_account));
        File.seekp(pos,ios::cur);
        File.write(reinterpret_cast<char *>(&ac),sizeof(Bank_account));
        cout<<"\t Record Updated"<<endl;
        found=true;
     }
}
File.close();
if(found== false){
    cout<<"\t Record Not Found"<<endl;
}
}

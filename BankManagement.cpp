#include<bits/stdc++.h>
using namespace std;

class Bank{
    //Attributes
    string name,pin,account_type;
    int account_number;
    double balance;

public:

 Bank(string n, string p, string acc_type, int account_num, double bal){
    name = n;
    pin = p;
    account_type = acc_type;  
    account_number = account_num;
    balance = bal;
    }

    string getName(){ return name;}
    string getPin(){ return pin;}
    string getAccountType(){ return account_type;}
    int getAccountNumber(){ return account_number;}
    double getBalance(){ return balance;}

    void display(){ 
        cout<<"Name: "<<name<<endl;
        cout<<"Account Number: "<<account_number<<endl;
        cout<<"Account Type: "<<account_type<<endl;
        cout<<"PIN (Password): "<<pin<<endl;
        cout<<"Current Balance: "<<balance<<" PKR"<<endl;
        cout<<"\t--------\n";
        }
     

    void deposit(double inputAmount){
        cout<<"Current Amount = "<<balance<<endl;
        if(inputAmount>0){
            balance+=inputAmount;
        cout<<"Deposit Succesful. New Balance Is: "<<balance<<" PKR"<<endl;
        }
        else cout<<"Invalid Deposit Input!"<<endl;
    }
    void withdraw(double withdrawAmount){
        if(withdrawAmount>0 && withdrawAmount<=balance){
            balance-=withdrawAmount;
        cout<<"Withdraw Succesful. New Balance Is: "<<balance<<" PKR"<<endl;
        }
        else cout<<"Invalid Withdraw Input!"<<endl;
    }
        
};

int generateAccountNum(){
    srand(time(0));
    return rand();
}

void createAccount(vector<Bank> &v){
    string n,p,acc_type;
    int account_num;
    double bal;
    cout<<"Enter Account Holder Name: "; getline(cin,n);
    cout<<"Enter Account Type[Saving/Current]: "; getline(cin,acc_type);
    cout<<"Enter PIN (4 Digits): "; getline(cin,p);
    account_num = generateAccountNum();
    bal = 0;
    for(auto i: v){
    if(account_num == i.getAccountNumber() && p==i.getPin()){
        cout<<"Account Alraedy Exist. Please Log In"<<endl;
        return;
        }
    }
    v.push_back(Bank(n,p,acc_type,account_num,bal));
    system("cls");
    cout<<"Welcome! Note The Details.\n"<<endl;
    cout<<"Account Holder Name: "<<n<<endl;
    cout<<"Account Number: "<<account_num<<endl;
    cout<<"Account Type: "<<acc_type<<endl;
    cout<<"PIN (Password): "<<p<<endl;
    cout<<"Current Balance: "<<bal<<" PKR ";
    cin.get();
}

void displayAllAccount(vector<Bank> &v){
    for(auto &i: v){
    i.display();}
}

void searchAccount(vector<Bank> &v){
    string p;
    int account_num;
    cout<<"Enter Account Number: "; cin>>account_num; cin.ignore();
    cout<<"Enter PIN (4 Digits): "; getline(cin,p);
    for(auto i: v){
    if(account_num == i.getAccountNumber() && p==i.getPin()){
        i.display();
        return; 
        }
    }
    cout<<"Account Not Found"<<endl;
}

void deleteAccount(vector<Bank> &v){
    string p;
    int account_num;
    cout<<"Enter Account Number: "; cin>>account_num; cin.ignore();
    cout<<"Enter PIN (4 Digits): "; getline(cin,p);
    for(int i = 0; i<v.size(); i++){
    if(account_num == v[i].getAccountNumber() && p==v[i].getPin()){
        v.erase(v.begin()+i); 
        cout<<"Account Deletion Succesful!"<<endl;
        }
    }
     cout<<"Account Not Found"<<endl;
}

void loginAccount(vector<Bank> &v){
    string p;
    int account_num,found = 0,index = 0;
    cout<<"Enter Account Number: "; cin>>account_num; cin.ignore();
    cout<<"Enter PIN (4 Digits): "; getline(cin,p);
    for(int i = 0; i<v.size(); i++){
    if(account_num == v[i].getAccountNumber() && p==v[i].getPin()){
        found = 1;
        index = i;
        }
    else if(account_num == v[i].getAccountNumber() && p!=v[i].getPin()) found = 2;
    else if(account_num != v[i].getAccountNumber() && p==v[i].getPin()) found = 3;
    }
    if(found==2) cout<<"Incorrect PIN!"<<endl;
    if(found==3) cout<<"Incorrect Account Number!"<<endl;
    if(found==0) cout<<"Incorrect Credentials!"<<endl;
 if(found==1){
       int choice;  
    while(1){ system("cls");
    cout<<"xxxxxx Login Menu xxxxxx"<<endl;
    cout<<" 1.View Account Details"<<endl;
    cout<<" 2.Deposit Amount"<<endl;
    cout<<" 3.Withdraw Amount"<<endl;
    cout<<" 4.Current Amount"<<endl;
    cout<<" 5.Delete Account"<<endl;
    cout<<" 0.Log OUT!"<<endl;
    cout<<" Enter Choice: "; cin>>choice; cin.ignore();

        
    switch(choice){ 
        case 1:
        system("cls");
        v[index].display();
        cin.get();
        break;

        case 2:
        system("cls");
        double depositAmount; 
        cout<<"Enter Deposit Ammount: "; cin>>depositAmount; cin.ignore();
        v[index].deposit(depositAmount);
        cin.get();
        break;

        case 3:
        system("cls");
        double withdrawAmount; 
        cout<<"Enter Deposit Ammount: "; cin>>withdrawAmount; cin.ignore();
        v[index].withdraw(withdrawAmount);
        cin.get();
        break;

        case 4:
        system("cls");
        cout<<"Current Amount Is: "<<v[index].getBalance()<<" PKR ";
        cin.get();
        break;

        case 5:
        system("cls");
        v.erase(v.begin()+index);
        cout<<"Account Deletion Complete! ";
        cin.get();
        return;

        case 0:
        return;

        default:
        cout<<"Invalid Input! ";
        cin.get();
        } 
    }
  }
}

void writeFile(vector<Bank> &v){
        fstream file;
        file.open("accounts.txt",ios::out);
        if(!file){
            cerr<<"File Opening Error"<<endl;
            return;
        }
        else{
            for(auto i: v){
            file<<i.getName()<<", "<<i.getAccountType()<<", "<<
            i.getPin()<<", "<<i.getAccountNumber()<<" "<<i.getBalance()<<endl;
            }
        }
        cout<<"Accounts SAve To File Succesfully! "; cin.get();
}

void readFile(vector<Bank> &v){
         string n,p,acc_type;
         int account_num;
         double bal;
        fstream file;
        file.open("accounts.txt",ios::in);
        if(!file){
             file.open("accounts.txt",ios::out);  
            cout<<"No Existing Data File Found. Create Account 1st."<<endl; cin.get();
            file.close();
            return;
        }
        else{
            v.clear();
            while(getline(file,n,',')){
            getline(file,acc_type,',');
            file>>ws;
            getline(file,p,',');
            file>>ws;
            file>>account_num;
            file>>bal; file.ignore();
            v.push_back(Bank(n,p,acc_type,account_num,bal));
            }
        }
        file.close();
}

void adminfeature(vector<Bank> &v){
    string email,password;
    cout<<"Enter Admin Email: "; getline(cin,email);
    cout<<"Enter Admin Password: "; getline(cin,password);
    if(email=="ijazalim608" || email=="ijazalim608@gmail.com"  && password=="90900"){
    system("cls");
    int choice;
    while(1){
    cout<<"\txxxxxx ADMIN FEATURES xxxxxx"<<endl;
    cout<<"\t   1.View All Account"<<endl;
    cout<<"\t   2.Search Account"<<endl;
    cout<<"\t   3.Delete Account!"<<endl;
    cout<<"\t   4.Return Main Menu"<<endl;
    cout<<"\tEnter Choice: "; cin>>choice; cin.ignore();

    if(choice==1){
        displayAllAccount(v);
    }
    else if(choice==2){
        searchAccount(v);
    }
    else if(choice==3){
        deleteAccount(v);
    }
    else if(choice==4) return;

    else cout<<"invalid Input!"<<endl;

    }
    }
    else {
        cout<<"Excess Denied!"<<endl;
        return;
    }
}

int main(){
    vector<Bank> accounts;
    readFile(accounts); // load all accounts to vector of objects.
    int c;
    while(1){ system("cls");
    cout<<" xxxxxx BANK MANAGEMENT SYSTEM xxxxxx\n"<<endl;
    cout<<"\t 1.Login Account"<<endl;
    cout<<"\t 2.Register Now"<<endl;
    cout<<"\t 3.Admin Features"<<endl;
    cout<<"\t 0.Exit Program!"<<endl;
    cout<<"\t Enter Choice: "; cin>>c; cin.ignore();

    switch(c) { 
        case 1:
        system("cls");
        loginAccount(accounts);
        break;

        case 2:
        system("cls");
        createAccount(accounts);
        break;
    
        case 3:
        system("cls");
        adminfeature(accounts);
        break;

        case 0:
         writeFile(accounts);
         return 0;

        default:
        cout<<"invalid Input!"<<endl;
    }
    }

    writeFile(accounts);
    return 0;
    
}

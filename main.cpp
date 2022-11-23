//
// Created by khine on 11/7/2022.
//

#include "iostream"
#include "fstream"
#include "ctime"
#include "vector"
using namespace std;

class Bank{
private:
    int adminLocate = 1;
    int adminCurrentId = 0;
    string adminUname[10]={"khine"};
    string adminUpass[10]={"123"};
public:
    string transitionData[100];
    int currentID=0;
    int currentUserAmount=0;
    int locate=0;
    string username[100];
    string upassword[100];
    int amount[100];

    Bank(){
        cout<<"Welcome to our Bank!"<<endl;
    }
    int setter(string adminUsername,string adminUserpass){
        adminUname[adminLocate] = adminUsername;
        adminUpass[adminLocate] = adminUserpass;
        adminLocate++;
    }
    int getter(){

    }

    int reGister();
    int login();
    int mainMenu();
    int allInfo();
    int exchange();
    int toTransfer(int currentID,int receiverID,int toTransferAmount);
    int toCheckUserName(string toTransferName);
    int toWithDraw(int currentId , int withdrawamount);
    int updateAmount(int toupdateAmount ,int updateOption);
    int changeAccocuntInfo();
    int changeAccountUsername();
    int changeAccountPassword();
    int adminView();
    int transitionDetails();
    int adminAllinfo();
};
int Bank::adminView() {
    int adminPress = 0;
    cout<<"Admin View"<<endl;
    cout<<"**********"<<endl;
    cout<<"Press 1 to view transition details\nPress 2 to view all info of users\nPress 3 to quit"<<endl;
    cin>>adminPress;
    if(adminPress == 1){
        transitionDetails();
    }else if(adminPress == 2){
        adminAllinfo();
    }else if(adminPress == 3){
        login();
    }else{
        cout<<"Wrong Pressed! Try again"<<endl;
        adminView();
    }
}
int Bank::transitionDetails() {
    cout<<"This is from transition details form"<<endl;
    ifstream fin("admin.txt");
    string num;
    vector<string>vec;
    while(fin>>num){
        vec.push_back(num);
    }
    for(int i=0;i<=vec.size()-1;i++){
        if(vec[i] == "$"){
            cout<<endl;
        }
        cout<<vec[i];
    }
}
int Bank::adminAllinfo() {
    allInfo();
}
int Bank::reGister() {
    string name;
    string password;
    string password2;
    int money;
    cout<<"This is from registration"<<endl;
    cout<<"Enter your name to register:";
    cin>>name;
    for(int i=0;i<=adminLocate;i++){
        if(name == adminUname[i]){
            cout<<"Your name is already registered in adminSide,Plz Try again!!"<<endl;
            mainMenu();
            break;
        }
    }
    int status = toCheckUserName(name);

    if(status == 1111){
        cout<<"Enter your password to register:";
        cin>>password;
        cout<<"Confirm password to register:";
        cin>>password2;
        if(password == password2){
            cout<<"Enter amount:";
            cin>>money;
            username[locate] = name ;
            upassword[locate] = password;
            amount[locate] = money;
            cout<<"Registration Success!"<<endl;
            locate++;
            allInfo();
        }else{
            cout<<"Passwords are not equal!"<<endl;
            reGister();
        }
    } else{
        cout<<"#####Username Already Registered#####"<<endl;
        reGister();
    }
}
int Bank::login() {
    string lusername;
    string lpassword;
    cout<<"This is from Login"<<endl;
    cout<<"Enter username to login:";
    cin>>lusername;
    cout<<"Enter pass to login for"<<lusername;
    cin>>lpassword;

    for(int a = 0;a<=adminLocate;a++)
    {
        if(lusername == adminUname[a] && lpassword == adminUpass[a]){
            adminCurrentId = a;
            cout<<"Hello Admin Level: "<<a<<" "<<lusername;
            adminView();


        }
    }
    for(int i=0; i<=locate ; i++){
        if(lusername == username[i] && lpassword== upassword[i]){
            currentID = i;
            currentUserAmount = amount[i];
            cout<<"Login Success"<<endl;
            exchange();

        }
    }
    return 100;
}
int Bank::exchange(){
    string toTransferName;
    int toTransferAmount;
    int userAmount=0;

    int exchangeOption=0;
    cout<<"Press 1 to Transfer:"<<endl;
    cout<<"Press 2 to Withdraw:"<<endl;
    cout<<"Press 3 to Update Amount:"<<endl;
    cout<<"Press 4 to Quit:"<<endl;
    cout<<"Press 5 to change account Information!"<<endl;

    cin>>exchangeOption;
    if(exchangeOption==1){
        cout<<"Enter name to transfer:";
        cin>>toTransferName;
        int receiverID = toCheckUserName(toTransferName);

        if(receiverID >= 0 ){
            while (receiverID >=0 ){

                cout<<"Enter amount to Transfer:";
                cin>>toTransferAmount;
                if(toTransferAmount>=currentUserAmount){
                    cout<<"Invalid amount:"<<endl;
                    continue;
                } else{

                    toTransfer(currentID,receiverID,toTransferAmount);
                    allInfo();
                    exchange();
                }
            }

        } else{
            cout<<"Name is not exit in our DB:"<<endl;
            exchange();
        }

    } else if(exchangeOption==2){
        int withdrawamount=0;
        cout<<"To Withdraw Option:"<<endl;
        cout<<"Enter amount to Withdraw:";
        cin>>withdrawamount;

        if(amount[currentID]-100 > withdrawamount){
            toWithDraw(currentID , withdrawamount);
            exchange();
        } else{
            cout<<"Invalid amount to withdraw : "<<withdrawamount;
            exchange();
        }

    } else if(exchangeOption==3){
        int toupdateAmount=0;
        int updateOption=0;
        cout<<"This is Update Option"<<endl;
        cout<<"Press 1 To add amount for Update\nPress 2 to sub amount for Update!:";
        cin>>updateOption;

        if(updateOption==1){
            cout<<"Enter amount to add for  Update :"<<username[currentID];
            cin>>toupdateAmount;
            updateAmount(toupdateAmount , updateOption);
            allInfo();
            exchange();
        } else{
            cout<<"Enter amount to sub for Update :"<<username[currentID];
            cin>>toupdateAmount;
            updateAmount(toupdateAmount , updateOption);
            allInfo();
            exchange();
        }

    } else if(exchangeOption==4){
        //Quit Option
        login();

    } else if( exchangeOption == 5){

        changeAccocuntInfo();

    }else{
        cout<<"Invalid Option"<<endl;
        exchange();
    }
}
int Bank::updateAmount(int toupdateAmount , int updateOption){

    if( updateOption == 1){
        amount[currentID] = amount[currentID] + toupdateAmount;

    } else{

        amount[currentID] = amount[currentID] - toupdateAmount;
    }

}

int Bank::toTransfer(int currentID,int receiverID,int toTransferAmount){
    amount[currentID]=amount[currentID]-toTransferAmount;
    amount[receiverID]=amount[receiverID] + toTransferAmount;
    cout<<"Money Successfully Transferred to : "<<username[receiverID]<<endl;
    cout<<"Transferred Amount: "<<toTransferAmount<<endl;
    //we must log here transition information
    string fileName = username[currentID]+".dat";
    string admin = "admin.txt";

    ofstream  outfile2;
    ofstream outfile;
    outfile.open(fileName,ios::app);
    outfile2.open(admin,ios::app);
    if(!outfile.is_open()){
        cout<<"Unable to record data in file!"<<endl;
        //to do something
    }
    if(!outfile2.is_open()){
        cout<<"Unable to record data for admin!"<<endl;
        //do something here
    }
    std::time_t myTime= std::time(nullptr);
    string time = std::asctime(std::localtime(&myTime));
    string toRecord = "From: "+username[currentID]+" To->"+username[receiverID]+" transfered"+ to_string(toTransferAmount)+" amount"+time+"$"+"\n";
    outfile<<toRecord;
    outfile2<<toRecord;
    outfile.close();
    outfile2.close();
}

int Bank::toWithDraw(int currentId , int withdrawamount){
    amount[currentId]=amount[currentId] - withdrawamount;
    cout<<username[currentId]<<" : amount = "<<amount[currentId]<<endl;
}

int Bank::toCheckUserName(string toTransferName){

    for(int i =0 ; i<=locate ; i++){
        if(toTransferName == username[i]){
            return i;
        }
    }
    return 1111;//error code for checking username;
}

int Bank::mainMenu(){
    int option=10;
    while (true){
        cout<<"Press 1 to Register;"<<endl;
        cout<<"Press 2 to Login"<<endl;
        cout<<"Press 3 to Quit"<<endl;
        cin>>option;
        if(option == 1){
            //registration
            reGister();
        } else if(option == 2){
            //login
            int status=login();
            if(status == 100){
                cout<<"Try again"<<endl;
            }
        } else{
            cout<<"bye bye"<<endl;
            return 0;
        }
    }
}

int Bank::allInfo() {
    cout<<"Username"<<endl;
    for(int i=0; i<=locate ; i++){
        cout<<"   "<<username[i]<<endl;
    }

    cout<<"Password"<<endl;
    for(int i=0; i<=locate ; i++){
        cout<<"   "<<upassword[i]<<endl;
    }

    cout<<"Amount"<<endl;
    for(int i=0; i<locate ; i++){
        cout<<"   "<<amount[i]<<endl;
    }
}


int Bank::changeAccocuntInfo(){
    int optionForchange=0;

    cout<<"Press 1 to Change Username:\nPress 2 to Change Password:"<<endl;
    cin>>optionForchange;

    if(optionForchange == 1){

        changeAccountUsername();
    }else if(optionForchange == 2){
        changeAccountPassword();
    }

}

int Bank::changeAccountUsername() {
    string newUsername;
    cout<<"This is your current Username: "<<username[currentID]<<endl;
    cout<<"Enter your new Username: ";
    cin>>newUsername;
    int status = toCheckUserName(newUsername);//not include 1111
    if(status == 1111){
        cout<<"Updating your New Username:..."<<endl;
        username[currentID]=newUsername;
        if(username[currentID] == newUsername){
            cout<<"Changing Success!"<<endl;
            cout<<"This is your New Username:"<<username[currentID]<<endl;
            mainMenu();
        }
    } else{
        cout<<"New username Already Registered!"<<endl;
        changeAccountUsername();
    }
}

int Bank::changeAccountPassword() {

    string newPassword;
    string currentPassword;
    cout<<"Enter your current password!:";
    cin>>currentPassword;

    if( upassword[currentID] == currentPassword){
        cout<<"Enter your new password:";
        cin>>newPassword;

        if(newPassword == currentPassword){
            cout<<"Password are same with old one:"<<endl;
            changeAccountPassword();
        } else{

            upassword[currentID] = newPassword;
            cout<<"Password changed successfully!"<<endl;
            mainMenu();
        }
    } else{
        cout<<"Wrong Password !"<<endl;
        exchange();
    }

}

int main(){

    Bank _obj;
    int ex=_obj.mainMenu();
    if(ex == 0){
        exit(1);
    }
}


// Problems
// transition record codes များအား သီးသန့်ခွဲထားရန်

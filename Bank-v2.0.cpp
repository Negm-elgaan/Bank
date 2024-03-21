#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

const string ClientsFileName = "File of Negm.txt" ;
const string UsersFileName = "Negm.txt" ;
enum MainMenu {ShowClientList = 1 , AddnewClient = 2 , DeleteClient = 3 , UpdateClient = 4 , FindClient = 5 , Transaction = 6 , ManageUsers = 7 , Logout = 8 , Exit = 9};
enum UsersMainMenu {ListUsers = 1 , AddNewUser = 2 , DeleteUser = 3 , UpdateUser = 4 , FindUser = 5 , MainMenuee = 6};
enum TranscationMainMenu {Deposit = 1 , Withdraw = 2 , Transfer = 3 , TotalBalance = 4 , MainMenue = 5 };
struct sUser
{
    string UserName;
    string Password;
    int AcessLevel;
    bool MarkForDelete = false ;
    bool MarkForUpdate = false ;
};
struct Permission
{
    bool ClientList ;
    bool AddClientt ;
    bool deleteclient ;
    bool updateclient ;
    bool findclient ;
    bool transcation ;
    bool manageusers ;
};
struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false ;
    bool MarkForUpdate = false ;
};
vector <string> splitstring(string S1,string Delim)
{
    vector <string> vString ;
    string sWord = "" ;
    short pos = 0 ;
    while ((pos = S1.find(Delim)) != std :: string :: npos)
    {
        sWord =S1.substr(0, pos); // store the word
        if (sWord !="")
        {
            vString.push_back(sWord);
        }
        S1.erase(0, pos + Delim.length());  /* erase() until positon and move to next word. */
    }
    if (S1!="")
    {
        vString.push_back(S1); // it adds last word of the string.
    }
    return vString;
}
sClient ConvertLinetoRecord(string line)
{
    vector <string> Vstring = splitstring(line,"#//#");
    sClient Client ;
    Client.AccountNumber = Vstring[0];
    Client.PinCode = Vstring[1];
    Client.Name = Vstring[2];
    Client.Phone = Vstring[3];
    try
    {
        Client.AccountBalance = stod(Vstring[4]);
    }
    catch(...)
    {
        cout << "hi";
    }
    return Client;
}
string ConvertRecordToLine(sClient Client, string Seperator = "#//#")
{
    string stClientRecord = "";
    stClientRecord += Client.AccountNumber + Seperator;
    stClientRecord += Client.PinCode + Seperator;
    stClientRecord += Client.Name + Seperator;
    stClientRecord += Client.Phone + Seperator;
    stClientRecord += to_string(Client.AccountBalance);
    return stClientRecord;
}
void AddDataLineToFile(string FileName, string stDataLine)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);
    if (MyFile.is_open())
    {
        MyFile << stDataLine << endl;
        MyFile.close();
    }
}
vector <sClient> LoadClientsFromFiletoVector(string filename)
{
    fstream NewFile ;
    sClient client ;
    vector <sClient> VsClients;
    NewFile.open(filename, ios::in );
    if (NewFile.is_open())
    {
        string line ;
        while(getline(NewFile , line))
        {
            client = ConvertLinetoRecord(line);
            VsClients.push_back(client);
        }
        NewFile.close();
    }
    return VsClients;
}
sClient ReadNewClient()
{
    vector <sClient> Vclients = LoadClientsFromFiletoVector(ClientsFileName);
    sClient client ;
    cout << "Adding new client:\n\n";
    cout << "Enter account number?";
    getline(cin >> ws,client.AccountNumber);
    short i = 0 ;
    if (Vclients.size() != 0)
    {
        while (i < Vclients.size())
        {
            if (Vclients[i].AccountNumber == client.AccountNumber)
            {
                cout << "Client with  [" << client.AccountNumber << "] already exists , Enter another account number ?";
                getline(cin,client.AccountNumber) ;
            }
            else
                i++;
        }
    }
    cout << "Enter pincode?";
    getline(cin,client.PinCode);
    cout << "Enter Name?";
    getline(cin,client.Name) ;
    cout << "Enter phone?";
    getline(cin,client.Phone) ;
    cout << "Enter account balance?";
    cin >> client.AccountBalance ;
    return client;
}
void AddClient()
{
    sClient client = ReadNewClient();
    AddDataLineToFile(ClientsFileName,ConvertRecordToLine(client));
}
bool isfound(string Accountnumber ,sClient s)
{
    return (Accountnumber == s.AccountNumber);
}
void displayclient(sClient s)
{
    cout << "The following is the extracted client record:\n\n";
    cout << "Account number" << ": " << s.AccountNumber << endl;
    cout << "Pin Code: " << s.PinCode << endl;
    cout << "Name: " << s.Name << endl;
    cout << "Phone: " << s.Phone << endl;
    cout << "Account balance: " << s.AccountBalance << endl;
}
void checkClient(string Accountnumber , vector <sClient> VsClients)
{
    for (short i = 0 ; i < VsClients.size() ; i++)
    {
        if (isfound(Accountnumber,VsClients[i]))
        {
            displayclient(VsClients[i]) ;
            return ;
        }
    }
}
vector <sClient> DeleteRecordbyAccountnumber(string AccountNumber , vector <sClient> Vclients)
{
    bool found = 0 ;
    vector <sClient> VClient;
    for (short i = 0 ; i < Vclients.size() ; i++)
    {
        if(isfound(AccountNumber , Vclients[i]))
        {
            found = 1 ;
            displayclient(Vclients[i]);
            char f = NULL;
            cout << "Are you sure you want to delete this client ?y/n? ";
            cin >> f ;
            if (toupper(f) != 'Y')
                VClient.push_back(Vclients[i]);
        }
        else
            VClient.push_back(Vclients[i]);
    }
    if(!found)
        cout << "Client with account number (" << AccountNumber << ") not found!";
    return VClient;
}
void AddnewDataLineToFile(string FileName, vector <sClient> Vsclient)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);
    if (MyFile.is_open())
    {
        for (int i = 0 ; i < Vsclient.size() ; i++)
        {
            AddDataLineToFile(FileName,ConvertRecordToLine(Vsclient[i],"#//#"));
        }
        //MyFile.close();
    }
}
bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{
    for (sClient& C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            C.MarkForDelete = true;
            return true;
        }
    }
    return false;
}
vector <sClient> SaveCleintsDataToFile(string FileName, vector<sClient> & vClients)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);//overwrite
    string DataLine;
    if (MyFile.is_open())
    {
        for (sClient C : vClients)
        {
            if (C.MarkForDelete == false)
            {
                    //we only write records that are not marked for delete.
                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;
            }
            else if (C.MarkForUpdate == true)
            {
                DataLine = ConvertRecordToLine(ReadNewClient());
                MyFile << DataLine << endl;
            }
        }
        MyFile.close();
    }
    return vClients;
}
string ReadUserName()
{
    string Username ;
    cout << "Enter Username?";
    getline(cin >> ws , Username);
    cout << endl;
    return Username;
}
string ReadUserPassword()
{
    string Password ;
    cout << "Enter Password?";
    getline(cin >> ws , Password);
    cout << endl;
    return Password;
}
sUser ConvertLinetoRecord2(string line)
{
    vector <string> Vstring = splitstring(line,"#//#");
    sUser User ;
    User.UserName = Vstring[0];
    User.Password = Vstring[1];
    User.AcessLevel = stoi(Vstring[2]);
    return User;
}
string ConvertRecordToLine2(sUser User, string Seperator = "#//#")
{
    string stUserRecord = "";
    stUserRecord += User.UserName + Seperator;
    stUserRecord += User.Password + Seperator;
    stUserRecord += to_string(User.AcessLevel);
    return stUserRecord;
}
vector <sUser> LoadUsersFromFiletoVector(string filename)
{
    fstream NewFile ;
    sUser User ;
    vector <sUser> VsUsers;
    NewFile.open(filename, ios::in );
    if (NewFile.is_open())
    {
        string line ;
        while(getline(NewFile , line))
        {
            User = ConvertLinetoRecord2(line);
            VsUsers.push_back(User);
        }
        NewFile.close();
    }
    return VsUsers;
}
bool isUsernameExist(string UserName ,sUser s)
{
    return (UserName == s.UserName);
}
short ReadAcessLevel()
{
    short AccessLevel = 0 ;
    cout << "Grant full access?y/n?" ;
    char c = NULL ;
    cin >> c ;
    if(toupper(c) == 'Y')
        return AccessLevel = -1 ;
    else
    {
        cout << endl << endl ;
        cout << "Show client list?y/n";
        cin >> c ;
        if(toupper(c) == 'Y')
            AccessLevel++;
        cout << endl << endl ;
        cout << "Add new client?y/n";
        cin >> c ;
        if(toupper(c) == 'Y')
            AccessLevel += 2;
        cout << endl << endl ;
        cout << "Delete client?y/n";
        cin >> c ;
        if(toupper(c) == 'Y')
            AccessLevel += 4;
        cout << endl << endl ;
        cout << "Update client?y/n";
        cin >> c ;
        if(toupper(c) == 'Y')
            AccessLevel += 8;
        cout << endl << endl ;
        cout << "Find client?y/n";
        cin >> c ;
        if(toupper(c) == 'Y')
            AccessLevel += 16;
        cout << endl << endl ;
        cout << "Transaction client?y/n";
        cin >> c ;
        if(toupper(c) == 'Y')
            AccessLevel += 32;
        cout << endl << endl ;
        cout << "Manage users?y/n";
        cin >> c ;
        if(toupper(c) == 'Y')
            AccessLevel += 64;
    }
    if (AccessLevel == 127)
        AccessLevel = -1 ;
    return AccessLevel ;
}
sUser ReadUser(string message)
{
    vector <sUser> vUsers = LoadUsersFromFiletoVector(UsersFileName);
    sUser User ;
    User.UserName = ReadUserName();
    for (short i = 0 ; i < vUsers.size() ; i++)
    {
        while(isUsernameExist(User.UserName,vUsers[i]))
        {
            cout << message << endl;
            User.UserName = ReadUserName();
        }
    }
    User.Password = ReadUserPassword();
    User.AcessLevel = ReadAcessLevel();
    return User ;
}
void AddnewDataLineToFile2(string FileName, vector <sUser> VsUser)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);
    if (MyFile.is_open())
    {
        for (int i = 0 ; i < VsUser.size() ; i++)
        {
            AddDataLineToFile(FileName,ConvertRecordToLine2(VsUser[i],"#//#"));
        }
        //MyFile.close();
    }
}
vector <sUser> SaveUsersDataToFile(string FileName, vector<sUser> & vUsers)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);//overwrite
    string DataLine;
    if (MyFile.is_open())
    {
        for (sUser C : vUsers)
        {
            if (C.MarkForDelete == false)
            {
                    //we only write records that are not marked for delete.
                DataLine = ConvertRecordToLine2(C);
                MyFile << DataLine << endl;
            }
            else if (C.MarkForUpdate == true)
            {
                DataLine = ConvertRecordToLine2(ReadUser("Username already exists!\n"));
                MyFile << DataLine << endl;
            }
        }
        MyFile.close();
    }
    return vUsers;
}
bool FindClientByAccountNumber(string AccountNumber , vector <sClient> vClients , sClient & Client )
{
    for (sClient C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }
    }
    return false;
}
bool DeleteClientByAccountNumber(string AccountNumber, vector<sClient> & vClients)
{
    sClient Client;
    char Answer = 'n';
    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        displayclient(Client);
        cout << "\n\nAre you sure you want delete this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
            SaveCleintsDataToFile(ClientsFileName, vClients); //Refresh Clients
            vClients = LoadClientsFromFiletoVector(ClientsFileName);
            cout << "\n\nClient Deleted Successfully.";
            return true;
        }
    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber<< ") is Not Found!";
        return false;
    }
}
bool MarkClientForUpdateByAccountNumber(string AccountNumber , vector <sClient> & s)
{
    for (sClient & c : s)
    {
        if (c.AccountNumber == AccountNumber)
        {
            c.MarkForUpdate = true ;
            return true ;
        }
    }
    return false ;
}
sClient ChangeClientRecord(string AccountNumber)
{
    sClient Client;
    Client.AccountNumber = AccountNumber;
    cout << "\n\nEnter PinCode? ";
    getline(cin >> ws, Client.PinCode);
    cout << "Enter Name? ";
    getline(cin, Client.Name);
    cout << "Enter Phone? ";
    getline(cin, Client.Phone);
    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;
    return Client;
}
bool UpdateClientByAccountNumber(string AccountNumber, vector<sClient> &vClients)
{
    sClient Client;
    char Answer = 'n';
    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        displayclient(Client);
        cout << "\n\nAre you sure you want update this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            for (sClient & C : vClients)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    C = ChangeClientRecord(AccountNumber);
                    break;
                }
            }
            SaveCleintsDataToFile(ClientsFileName, vClients);
            cout << "\n\nClient Updated Successfully.";
            return true;
        }
    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber<< ") is Not Found!\n\n";
        return false;
    }
}
bool MarkUserForDeleteByUsername(string Username , vector <sUser>& vUsers)
{
    for (sUser& C : vUsers)
    {
        if (C.UserName == Username)
        {
            C.MarkForDelete = true;
            return true;
        }
    }
    return false;
}
bool FindUserByUsernameAndPassword(string username , string password , vector <sUser> vUsers , sUser &user)
{
    for (sUser &c : vUsers)
    {
        if (c.UserName == username && c.Password == password)
        {
            user = c ;
            return true ;
        }
    }
    return false ;
}
void PrintUserRecord(sUser User)
{
    cout << "| " << setw(15) << left << User.UserName;
    cout << "| " << setw(10) << left << User.Password;
    cout << "| " << setw(40) << left << User.AcessLevel;
}
bool DeleteUserByUsernameAndPassword(string Username , string Password , vector <sUser> & vUsers)
{
    sUser User;
    char Answer = 'n';
    if (FindUserByUsernameAndPassword(Username ,Password, vUsers, User))
    {
        PrintUserRecord(User);
        cout << "\n\nAre you sure you want delete this user? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            MarkUserForDeleteByUsername(Username , vUsers);
            SaveUsersDataToFile(UsersFileName, vUsers); //Refresh Clients
            vUsers = LoadUsersFromFiletoVector(UsersFileName);
            cout << "\n\nUser Deleted Successfully.";
            return true;
        }
    }
    else
    {
        cout << "\nUser is Not Found!";
        return false;
    }
}
bool MarkUserForUpdateByUsernameAndPassword(string username , string password , vector <sUser> & s)
{
    for (sUser & c : s)
    {
        if (c.UserName == username)
        {
            c.MarkForUpdate = true ;
            return true ;
        }
    }
    return false ;
}
sUser ChangeUserRecord()
{
    sUser User;
    cout << "\n\nEnter username?" ;
    getline(cin >> ws , User.UserName) ;
    cout << "\n\nEnter password? ";
    getline(cin >> ws, User.Password);
    User.AcessLevel = ReadAcessLevel();
    return User;
}
bool UpdateUserByAccountNumberAndPassword(string username , string password, vector<sUser> &vUsers)
{
    sUser User;
    char Answer = 'n';
    if (FindUserByUsernameAndPassword(username , password , vUsers , User))
    {
        PrintUserRecord(User);
        cout << "\n\nAre you sure you want update this User? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            for (sUser & C : vUsers)
            {
                if (C.UserName == username)
                {
                    C = ChangeUserRecord();
                    break;
                }
            }
            SaveUsersDataToFile(UsersFileName, vUsers);
            cout << "\n\nUser Updated Successfully.";
            return true;
        }
    }
    else
    {
        cout << "\nUser with username (" << username << ") is Not Found!\n\n";
        return false;
    }
}
void PrintClientRecord(sClient Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.AccountBalance;
}
void PrintAllClientsData(vector <sClient> vClients)
{
    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    for (sClient Client : vClients)
    {
        PrintClientRecord(Client);
        cout << endl;
    }
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}
string ReadClientAccountNumber()
{
    string AccountNumber = "";
    cout << "\nPlease enter AccountNumber? ";
    cin >> AccountNumber;
    return AccountNumber;
}
void ShowAddClientScreen()
{
    cout << "--------------------------------------\n";
    cout << setw(30) << right << "Add client screen\n";
    cout << "--------------------------------------\n";
}
void Addclients()
{
    char d = 'y' ;
    while (d == 'y' || d == 'Y')
    {
        AddClient();
        cout << "Do you want to add more clients?y/n?";
        cin >> d ;
    }
}
MainMenu ShowMainMenu()
{
    short Choice ;
    cout << "===============================================\n";
    cout << setw (35) << right << "Main menu screen\n";
    cout << "===============================================\n";
    cout << setw(30) << right << "[1] Show client list.\n";
    cout << setw(28) << right << "[2] Add new client.\n";
    cout << setw(27) << right << "[3] Delete client.\n";
    cout << setw(32) << right << "[4] Update client info.\n";
    cout << setw(24) << right << "[5] Find client\n";
    cout << setw(24) << right << "[6] Transaction\n";
    cout << setw(25) << right << "[7] Manage Users\n";
    cout << setw(19) << right << "[8] Logout\n";
    cout << setw(17) << right << "[9] Exit\n";
    cout << "===============================================\n";
    cout << "Choose what you want to do [1 to 9]?";
    cin >> Choice ;
    while ((Choice > 9 && Choice >= 1) || (Choice <= 9 && Choice < 1))
    {
        cout << "\nInvalid choice!\n" << "Choose What you want to do [1 to 9]?";
        cin >> Choice;
    }
    switch (Choice)
    {
        case 1:
            return MainMenu :: ShowClientList ;
        case 2:
            return MainMenu :: AddnewClient ;
        case 3:
            return MainMenu :: DeleteClient ;
        case 4:
            return MainMenu :: UpdateClient ;
        case 5:
            return MainMenu :: FindClient ;
        case 6:
            return MainMenu :: Transaction ;
        case 7:
            return MainMenu :: ManageUsers ;
        case 8:
            return MainMenu :: Logout ;
        case 9:
            return MainMenu ::Exit ;
    }
}
void ShowDeleteClientScreen()
{
    cout << "--------------------------------------\n";
    cout << setw(30) << right << "Delete Client screen\n";
    cout << "--------------------------------------\n";
}
void ShowUpdateClientInfoScreen()
{
    cout << "--------------------------------------\n";
    cout << setw(30) << right << "Update Client Info Screen\n";
    cout << "--------------------------------------\n";
}
void ShowFindClientScreen()
{
    system("cls");
    cout << "--------------------------------------\n";
    cout << setw(30) << right << "Find Client Screen\n";
    cout << "--------------------------------------\n";
}
void ShowDeleteUserScreen()
{
    cout << "--------------------------------------\n";
    cout << setw(28) << right << "Delete User screen\n";
    cout << "--------------------------------------\n";
}
void ShowAddUserScreen()
{
    cout << "--------------------------------------\n";
    cout << setw(28) << right << "Add User screen\n";
    cout << "--------------------------------------\n";
}
void ShowUpdateUserInfoScreen()
{
    cout << "--------------------------------------\n";
    cout << setw(28) << right << "Update User Info Screen\n";
    cout << "--------------------------------------\n";
}
void ShowFindUserScreen()
{
    system("cls");
    cout << "--------------------------------------\n";
    cout << setw(28) << right << "Find User Screen\n";
    cout << "--------------------------------------\n";
}
void ShowExitScreen()
{
    system("cls");
    cout << "--------------------------------------\n";
    cout << setw(30) << right << "Program ends :-)\n";
    cout << "--------------------------------------\n";
}
void ShowTransactionScreen()
{
    cout << "======================================\n";
    cout << setw(30) << right << "Transaction Menu Screen\n";
    cout << "======================================\n";
    cout << setw(21) << right << "[1] Deposit.\n";
    cout << setw(22) << right << "[2] Withdraw.\n";
    cout << setw(22) << right << "[3] Transfer.\n";
    cout << setw(27) << right << "[4] Total Balance.\n";
    cout << setw(23) << right << "[5] Main Menu.\n";
    cout << "======================================\n";
}
void ShowDepositScreen()
{
    system("cls");
    cout << "--------------------------------------\n";
    cout << setw(30) << right << "Deposit Screen\n";
    cout << "--------------------------------------\n";
}
void ShowWithdrawScreen()
{
    system("cls");
    cout << "--------------------------------------\n";
    cout << setw(30) << right << "Withdraw Screen\n";
    cout << "--------------------------------------\n";
}
void ShowTransferScreen()
{
    system("cls");
    cout << "--------------------------------------\n";
    cout << setw(30) << right << "Transfer Screen\n";
    cout << "--------------------------------------\n";
}
void ShowManageUsersScreen()
{
    system("cls");
    cout << "======================================\n";
    cout << setw(34) << right << "Manage Users Screen\n";
    cout << "======================================\n";
    cout << setw(24) << right << "[1] List users.\n";
    cout << setw(26) << right << "[2] Add new user.\n";
    cout << setw(25) << right << "[3] Delete user.\n";
    cout << setw(25) << right << "[4] Update user.\n";
    cout << setw(23) << right << "[5] Find user.\n";
    cout << setw(23) << right << "[6] Main menu.\n";
    cout << "======================================\n";
}
void ShowTotalBalanceScreen()
{
    vector <sClient> vClients = LoadClientsFromFiletoVector(ClientsFileName);
    cout << "\n\t\t\t\t\tBalance List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    for (sClient Client : vClients)
    {
        PrintClientRecord(Client);
        cout << endl;
    }
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}
double CalculateTotalBalance()
{
    vector <sClient> Vclient = LoadClientsFromFiletoVector(ClientsFileName);
    double TotalBalance = 0 ;
    for (short i = 0 ; i < Vclient.size() ; i++)
        TotalBalance += Vclient[i].AccountBalance;
    return TotalBalance;
}
void ShowTotalBalance()
{
    double totalbalnce = CalculateTotalBalance();
    cout << "Total Balance = " << totalbalnce << endl;
}
bool isThereEnough(double MoneyTowithdraw , sClient client)
{
    return client.AccountBalance >= MoneyTowithdraw ;
}
double ReadmoneytoWithdraw()
{
    double money = 0 ;
    cin >> money ;
    return money ;
}
void DoWithdraw()
{
    ShowWithdrawScreen();
    double money = 0 ;
    vector <sClient> Vclients = LoadClientsFromFiletoVector(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    sClient Client ;
    if (FindClientByAccountNumber(AccountNumber , Vclients , Client))
    {
        char d = 'd';
        displayclient(Client);
        cout << "Enter money you want to withdraw?\n";
        money = ReadmoneytoWithdraw();
        cout << "Are you sure you want to do this transaction?y/n?";
        cin >> d ;
        if (d == 'y' || d == 'Y')
        {
            while (isThereEnough(money,Client) != true)
                {
                    cout << "Amount Exceeds the balance, you can withdraw up to :" << Client.AccountBalance << endl;
                    cout << "Please enter another amount? " ;
                    money = ReadmoneytoWithdraw();
                    cout << "Are you sure you want to do this transaction?y/n?";
                    cin >> d ;
                    if (toupper(d) != 'Y')
                        return ;
                }
            Client.AccountBalance -= money;
            for (short i = 0 ; i < Vclients.size() ; i++)
                if (Client.AccountNumber == Vclients[i].AccountNumber)
                        Vclients[i].AccountBalance = Client.AccountBalance;
            SaveCleintsDataToFile(ClientsFileName,Vclients);
        }
    }
    else
        cout << "Client with account number [" << AccountNumber << "] not found!\n";
}
double MoneyToDeposit()
{
    double Money = 0 ;
    cout << "Enter money to deposit\n";
    cin >> Money;
    return Money;
}
void DoDeposit()
{
    vector <sClient> Vclients = LoadClientsFromFiletoVector(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    sClient Client ;
    double Money = MoneyToDeposit();
        if(FindClientByAccountNumber(AccountNumber , Vclients , Client))
        {
            displayclient(Client);
            cout << "Are sure you want to do this transaction?y/n?";
            char h ;
            cin >> h ;
            if (h == 'y' || h == 'Y')
            {
                Client.AccountBalance += Money;
                for (short i = 0 ; i < Vclients.size() ; i++)
                    if (Client.AccountNumber == Vclients[i].AccountNumber)
                        Vclients[i].AccountBalance = Client.AccountBalance;
                SaveCleintsDataToFile(ClientsFileName,Vclients);
            }
        }
        else
        {
            cout << "Client with account number [" << AccountNumber << "] not found!\n";
        }
    return ;
}
void DoTransfer()
{
    vector <sClient> Vclients = LoadClientsFromFiletoVector(ClientsFileName);
    string AccountNumberToTransferFrom = ReadClientAccountNumber();
    sClient Client1 ;
    if(FindClientByAccountNumber(AccountNumberToTransferFrom , Vclients , Client1))
    {
        displayclient(Client1);
        string AccountNumberToTransferTo = ReadClientAccountNumber();
        sClient Client2;
        if(FindClientByAccountNumber(AccountNumberToTransferTo , Vclients , Client2))
        {
            displayclient(Client2);
            double Money = MoneyToDeposit();
            cout << "Are sure you want to Transfer " << Money << "From Client with account number [" << AccountNumberToTransferFrom << "] to Client with account number [" << AccountNumberToTransferTo << "]?y/n?";
            char h ;
            cin >> h ;
            if (h == 'y' || h == 'Y')
            {
                if(isThereEnough(Money,Client1))
                {
                    Client1.AccountBalance -= Money ;
                    Client2.AccountBalance += Money ;
                    for (short i = 0 ; i < Vclients.size() ; i++)
                    {
                        if (Client1.AccountNumber == Vclients[i].AccountNumber)
                            Vclients[i].AccountBalance = Client1.AccountBalance;
                        SaveCleintsDataToFile(ClientsFileName,Vclients);
                        if (Client2.AccountNumber == Vclients[i].AccountNumber)
                            Vclients[i].AccountBalance = Client2.AccountBalance;
                        SaveCleintsDataToFile(ClientsFileName,Vclients);
                    }
                }
                else
                    cout << "Insufficient Balance\n";
            }
        }
        else
            cout << "Client with account number [" << AccountNumberToTransferTo << "] not found!\n";
    }
    else
        cout << "Client with account number [" << AccountNumberToTransferFrom << "] not found!\n";
    return ;
}
short GetClientChoice()
{
    short Choice = 0 ;
    cout << "Choose what you want to do [1 to 5]?";
    cin >> Choice ;
    while ((Choice > 5 && Choice >= 1) || (Choice <= 5 && Choice < 1))
    {
        cout << "\nInvalid choice!\n" << "Choose What you want to do [1 to 5]?";
        cin >> Choice;
    }
    return Choice;
}
void PerformTranactionMenuOption(TranscationMainMenu Choice)
{
    while(Choice != MainMenue)
    {
        system("cls");
        switch (Choice)
        {
            case Deposit :
                ShowDepositScreen();
                DoDeposit();
                break;
            case Withdraw :
                ShowWithdrawScreen();
                DoWithdraw();
                break;
            case Transfer :
                ShowTransferScreen();
                DoTransfer();
                break ;
            case TotalBalance :
                ShowTotalBalanceScreen();
                ShowTotalBalance();
        }
        cout << "Press any key to go back to transaction menu";
        system("pause>0");
        system("cls");
        ShowTransactionScreen();
        Choice = ((TranscationMainMenu)GetClientChoice());
    }
    return ;
}
void PrintAllUsersData(vector <sUser> vUsers)
{
    cout << "\n\t\t\t\t\tUser List (" << vUsers.size() << ") User(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(10) << "Username";
    cout << "| " << left << setw(10) << "Password";
    cout << "| " << left << setw(40) << "Access Level";
    //cout << "| " << left << setw(12) << "Phone";
    //cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    for (sUser &User : vUsers)
    {
        PrintUserRecord(User);
        cout << endl;
    }
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}
vector <bool> CheckPermission(short acesslevel)
{
    vector <bool> vPermission ;
    if (acesslevel == -1)
    {
        vPermission.push_back(1);
        vPermission.push_back(1);
        vPermission.push_back(1);
        vPermission.push_back(1);
        vPermission.push_back(1);
        vPermission.push_back(1);
        vPermission.push_back(1);
        return vPermission ;
    }
    while(acesslevel != 0)
    {
        if (acesslevel % 2 > 0)
        {
            vPermission.push_back(1);
        }
        else
            vPermission.push_back(0);
        acesslevel /= 2 ;
    }
    while(vPermission.size() < 7)
        vPermission.push_back(0);
    return vPermission ;
}
Permission GetPermission(short acessLevel)
{
    vector <bool> vPermission = CheckPermission(acessLevel);
    Permission p1;
    p1.ClientList = vPermission[0];
    p1.AddClientt = vPermission[1];
    p1.deleteclient = vPermission[2];
    p1.updateclient = vPermission[3];
    p1.findclient = vPermission[4];
    p1.transcation = vPermission[5];
    p1.manageusers = vPermission[6];
    return p1 ;
}
void ShowLoginScreen()
{
    cout << "--------------------------------------\n";
    cout << setw(25) << right << "Login Screen\n";
    cout << "--------------------------------------\n";
}
void AddUser()
{
    sUser User = ReadUser("User already exists\n") ;
    AddDataLineToFile(UsersFileName,ConvertRecordToLine2(User));
}
void AddUsers()
{
    char d = 'y' ;
    while (d == 'y' || d == 'Y')
    {
        AddUser();
        cout << "Do you want to add more users?y/n?";
        cin >> d ;
    }
    return ;
}
short GetUserChoice()
{
    short Choice = 0 ;
    cout << "Choose what you want to do [1 to 6]?";
    cin >> Choice ;
    while ((Choice > 6 && Choice >= 1) || (Choice <= 6 && Choice < 1))
    {
        cout << "\nInvalid choice!\n" << "Choose What you want to do [1 to 6]?";
        cin >> Choice;
    }
    return Choice;
}
void PerformUserMenuOption(UsersMainMenu Choice)
{
    vector <sUser> vUsers = LoadUsersFromFiletoVector(UsersFileName);
    vector <sUser> vNewUsers ;
    while(Choice != MainMenuee)
    {
        system("cls");
        switch (Choice)
        {
            case ListUsers:
                vUsers = LoadUsersFromFiletoVector(UsersFileName);
                PrintAllUsersData(vUsers);
                break;
            case AddNewUser:
                ShowAddUserScreen();
                AddUsers();
                vUsers = LoadUsersFromFiletoVector(UsersFileName);
                break;
            case DeleteUser :
                system("cls");
                ShowDeleteUserScreen();
                DeleteUserByUsernameAndPassword(ReadUserName(),ReadUserPassword(),vUsers);
                SaveUsersDataToFile(UsersFileName,vUsers);
                vUsers = LoadUsersFromFiletoVector(UsersFileName);
                break ;
            case UpdateUser:
                ShowUpdateUserInfoScreen();
                UpdateUserByAccountNumberAndPassword(ReadUserName(),ReadUserPassword(),vUsers);
                vUsers = LoadUsersFromFiletoVector(UsersFileName);
                break;
            case FindUser:
                sUser user;
                ShowFindUserScreen();
                if (FindUserByUsernameAndPassword(ReadUserName(),ReadUserPassword(),vUsers,user))
                    PrintUserRecord(user);
                else
                    cout << "User with username [" << user.UserName << "] not found !\n";
        }
        cout << "Press any key to go back to main menu";
        system("pause>0");
        system("cls");
        ShowManageUsersScreen();
        Choice = ((UsersMainMenu)GetUserChoice());
    }
    return ;
}
bool StartBanking(bool c , sUser user)
{
    vector <sClient> Vclients = LoadClientsFromFiletoVector(ClientsFileName);
    vector <sClient> newvclient ;
    Permission p1 = GetPermission(user.AcessLevel) ;
    MainMenu s = ShowMainMenu();
    system("cls");
    sClient client;
    while(s != Exit && s != Logout)
    {
        switch (s)
        {
            case ShowClientList:
                if(p1.ClientList == true)
                {
                    Vclients = LoadClientsFromFiletoVector(ClientsFileName);
                    PrintAllClientsData(Vclients);
                }
                else
                {
                    system("cls");
                    cout << "Access denied!\n";
                }
                break;
            case AddnewClient:
                if(p1.AddClientt == true)
                {
                    system("cls");
                    ShowAddClientScreen();
                    Addclients();
                    Vclients = LoadClientsFromFiletoVector(ClientsFileName);
                }
                else
                {
                    system("cls");
                    cout << "Access denied!\n";
                }
                break;
            case DeleteClient:
                if (p1.deleteclient == true)
                {
                    system("cls");
                    ShowDeleteClientScreen();
                    newvclient = DeleteRecordbyAccountnumber(ReadClientAccountNumber(),Vclients);
                    SaveCleintsDataToFile(ClientsFileName,newvclient);
                    Vclients = LoadClientsFromFiletoVector(ClientsFileName);
                }
                else
                {
                    system("cls");
                    cout << "Access denied!\n";
                }
                break;
            case UpdateClient:
                if (p1.updateclient == true)
                {
                    system("cls");
                    ShowUpdateClientInfoScreen();
                    UpdateClientByAccountNumber(ReadClientAccountNumber(),Vclients);
                    Vclients = LoadClientsFromFiletoVector(ClientsFileName);
                }
                else
                {
                    system("cls");
                    cout << "Access denied!\n";
                }
                break;
            case FindClient:
                {
                    if (p1.findclient == true)
                    {
                        system("cls");
                        ShowFindClientScreen();
                        string AccountNumber = ReadClientAccountNumber();
                        if(FindClientByAccountNumber(AccountNumber,Vclients,client))
                            displayclient(client);
                        else
                            cout << "Client with account number [" << AccountNumber << "] not found !\n";
                    }
                    else
                    {
                        system("cls");
                        cout << "Access denied!\n";
                    }
                    break;
                }
            case Transaction:
                if (p1.transcation)
                {
                    system("cls");
                    ShowTransactionScreen();
                    PerformTranactionMenuOption((TranscationMainMenu)GetClientChoice());
                }
                else
                {
                    system("cls");
                    cout << "Access denied!\n";
                }
                break;
            case ManageUsers:
                if(p1.manageusers)
                {
                    ShowManageUsersScreen();
                    PerformUserMenuOption((UsersMainMenu)GetUserChoice());
                }
                else
                {
                    system("cls");
                    cout << "Access denied!\n";
                }
        }
        cout << "Press any key to go back to main menu";
        system("pause>0");
        system("cls");
        s = ShowMainMenu();
    }
    if (s == Logout)
        return c;
    return c = false ;
}
void ShowRegisterScreen()
{
    cout << "--------------------------------------\n";
    cout << setw(28) << right << "Register Screen\n";
    cout << "--------------------------------------\n";
    cout << "Setup your user account:\n\n";
}
void Login()
{
    bool c = true;
    while (c == true)
    {
        system("Color FC");
        sUser User ;
        system("cls");
        vector <sUser> vUsers = LoadUsersFromFiletoVector(UsersFileName);
        if (vUsers.empty())
        {
            ShowRegisterScreen();
            AddUsers();
            vUsers = LoadUsersFromFiletoVector(UsersFileName);
            User = vUsers[0];
        }
        else
        {
            ShowLoginScreen();
            string UserName = ReadUserName();
            string Password = ReadUserPassword();
            while (!FindUserByUsernameAndPassword(UserName,Password,vUsers,User))
            {
                system("cls");
                ShowLoginScreen();
                cout << "Invalid username/password!\n";
                UserName = ReadUserName();
                Password = ReadUserPassword();
            }
        }
        system("cls");
        c = StartBanking(c,User);
    }
    ShowExitScreen();
    system("pause");
    return ;
}
int main()
{
    Login();
    system("pause>0");
    return 0;
}


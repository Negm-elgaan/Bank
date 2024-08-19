#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

const string ClientsFileName = "File of Negm.txt" ;
enum enAtmMainMenu {QuickWithdraw = 1 , NormalWithdraw = 2 , Deposit = 3 , CheckBalance = 4 , Logout = 5};
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
sClient client;
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
void AddnewDataLineToFile(string FileName, vector <sClient> Vsclient)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);
    if (MyFile.is_open())
    {
        for (int i = 0 ; i < Vsclient.size() ; i++)
        {
[O            AddDataLineToFile(FileName,ConvertRecordToLine(Vsclient[i],"#//#"));
        }
    }
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
bool FindClientByAccountNumberAndPincode(string AccountNumber  , string pincode , vector <sClient> vClients)
{
    for (sClient &C : vClients)
    {
        if (C.AccountNumber == AccountNumber && C.PinCode == pincode)
        {
            client = C;
            return true;
        }
    }
    return false;
}
string ReadClientAccountNumber()
{
    string AccountNumber = "";
    cout << "\nPlease enter AccountNumber? ";
    cin >> AccountNumber;
    return AccountNumber;
}
int ReadmoneytoWithdraw()
{
    int money = 0 ;
    do
    {
        cout << "Enter an amount multiple of 5 ' s ? ";
        cin >> money ;
        cout << endl << endl;
    }
    while (money % 5 != 0);
    return money ;
}
enAtmMainMenu ShowMainMenu()
{
    short Choice ;
    cout << "===============================================\n";
    cout << setw (35) << right << "Main menu screen\n";
    cout << "===============================================\n";
    cout << setw(28) << right << "[1] Quick withdraw.\n";
    cout << setw(29) << right << "[2] Normal withdraw.\n";
    cout << setw(21) << right << "[3] Deposit.\n";
    cout << setw(27) << right << "[4] Total balance.\n";
    cout << setw(19) << right << "[5] Logout\n";
    cout << "===============================================\n";
    cout << "Choose what you want to do [1 to 5]?";
    cin >> Choice ;
    while ((Choice > 5 && Choice >= 1) || (Choice <= 5 && Choice < 1))
    {
        cout << "\nInvalid choice!\n" << "Choose What you want to do [1 to 5]?";
        cin >> Choice;
    }
    switch (Choice)
    {
        case 1:
            return enAtmMainMenu :: QuickWithdraw ;
        case 2:
            return enAtmMainMenu :: NormalWithdraw ;
        case 3:
            return enAtmMainMenu :: Deposit ;
        case 4:
            return enAtmMainMenu :: CheckBalance ;
        case 5:
            return enAtmMainMenu :: Logout ;
    }
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
void ShowQuickWithdrawScreen()
{
    system("cls");
    cout << "===============================================\n";
    cout << setw(36) << right << "Quick Withdraw Screen\n";
    cout << "===============================================\n";
}
void ShowCheckBalanceScreen()
{
    system("cls");
    cout << "===============================================\n";
    cout << setw(36) << right << "Check balance Screen\n";
    cout << "===============================================\n";
}
bool isThereEnough(double MoneyTowithdraw , sClient client)
{
    return client.AccountBalance >= MoneyTowithdraw ;
}
short GetClientChoice2()
{
    short Choice = 0 ;
    cout << "Choose what you want to do [1 to 9]?";
    cin >> Choice ;
    while ((Choice > 9 && Choice >= 1) || (Choice <= 9 && Choice < 1))
    {
        cout << "\nInvalid choice!\n" << "Choose What you want to do [1 to 9]?";
        cin >> Choice;
    }
    return Choice;
}
void DoQuickWithdraw()
{
    vector <sClient> Vclients = LoadClientsFromFiletoVector(ClientsFileName);
    cout << "[1] 20" << setw(10) << right << "[2] 50\n" ;
    cout << "[3] 100" << setw(10) << right << "[4] 200\n" ;
    cout << "[5] 400" << setw(10) << right << "[6] 600\n" ;
    cout << "[7] 800" << setw(11) << right << "[8] 1000\n" ;
    cout << "[9] Exit\n";
    cout << "===============================================\n";
    cout << "Your balance is : " << client.AccountBalance << endl;
    short s = GetClientChoice2();
    switch (s)
    {
        case 1:
            if (isThereEnough(20,client))
                client.AccountBalance -= 20 ;
            else
                cout << "Amount Exceeds the balance, you can withdraw up to :" << client.AccountBalance << endl;
            break ;
        case 2:
            if (isThereEnough(50,client))
                client.AccountBalance -= 50 ;
            else
                cout << "Amount Exceeds the balance, you can withdraw up to :" << client.AccountBalance << endl;
            break ;
        case 3:
            if (isThereEnough(100,client))
                client.AccountBalance -= 100 ;
            else
                cout << "Amount Exceeds the balance, you can withdraw up to :" << client.AccountBalance << endl;
            break ;
        case 4:
            if (isThereEnough(200,client))
                client.AccountBalance -= 200 ;
            else
                cout << "Amount Exceeds the balance, you can withdraw up to :" << client.AccountBalance << endl;
            break ;
        case 5:
            if (isThereEnough(400,client))
                client.AccountBalance -= 400 ;
            else
                cout << "Amount Exceeds the balance, you can withdraw up to :" << client.AccountBalance << endl;
            break ;
        case 6:
            if (isThereEnough(600,client))
                client.AccountBalance -= 600 ;
            else
                cout << "Amount Exceeds the balance, you can withdraw up to :" << client.AccountBalance << endl;
            break ;
        case 7:
            if (isThereEnough(800,client))
                client.AccountBalance -= 800 ;
            else
                cout << "Amount Exceeds the balance, you can withdraw up to :" << client.AccountBalance << endl;
            break ;
        case 8:
            if (isThereEnough(1000,client))
                client.AccountBalance -= 1000 ;
            else
                cout << "Amount Exceeds the balance, you can withdraw up to :" << client.AccountBalance << endl;
            break ;
        case 9:
            return ;
    }
    for (short i = 0 ; i < Vclients.size() ; i++)
            if (client.AccountNumber == Vclients[i].AccountNumber)
                Vclients[i].AccountBalance = client.AccountBalance;
    SaveCleintsDataToFile(ClientsFileName,Vclients);
}
void DoWithdraw()
{
    ShowWithdrawScreen();
    int money = 0 ;
    vector <sClient> Vclients = LoadClientsFromFiletoVector(ClientsFileName);
    char d = 'd';
    money = ReadmoneytoWithdraw();
    cout << "Are you sure you want to do this transaction?y/n?";
    cin >> d ;
    if (d == 'y' || d == 'Y')
    {
        if (client.AccountBalance == 0)
        {
            cout << "You currently don't have any money to withdraw\n";
            return ;
        }
        while (isThereEnough(money,client) != true)
        {
            cout << "Amount Exceeds the balance, you can withdraw up to :" << client.AccountBalance << endl;
            cout << "Please enter another amount? " ;
            money = ReadmoneytoWithdraw();
            cout << "\nAre you sure you want to do this transaction?y/n?";
            cin >> d ;
            if (toupper(d) != 'Y')
[I                return ;
        }
        client.AccountBalance -= money;
        for (short i = 0 ; i < Vclients.size() ; i++)
            if (client.AccountNumber == Vclients[i].AccountNumber)
                Vclients[i].AccountBalance = client.AccountBalance;
        SaveCleintsDataToFile(ClientsFileName,Vclients);
        cout << "\nDone successfully new balance is : " << client.AccountBalance << endl;
    }
}
string ReadClientPincode()
{
    string pincode ;
    cout << "Enter pincode? ";
    cin >> pincode ;
    return pincode ;
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
    double Money = MoneyToDeposit();
    cout << "Are you want to do this transaction?y/n?";
    char h ;
    cin >> h ;
    if (h == 'y' || h == 'Y')
    {
        client.AccountBalance += Money;
        for (short i = 0 ; i < Vclients.size() ; i++)
            if (client.AccountNumber == Vclients[i].AccountNumber)
                Vclients[i].AccountBalance = client.AccountBalance;
        SaveCleintsDataToFile(ClientsFileName,Vclients);
    }
}
short GetClientChoice()
{
    short Choice = 0 ;
    cout << "Choose what you want to do [1 to 4]?";
    cin >> Choice ;
    while ((Choice > 4 && Choice >= 1) || (Choice <= 4 && Choice < 1))
    {
        cout << "\nInvalid choice!\n" << "Choose What you want to do [1 to 4]?";
        cin >> Choice;
    }
    return Choice;
}
void StartAtming()
{
    system("cls");
    enAtmMainMenu s = ShowMainMenu();
    while(s != Logout)
    {
        switch (s)
        {
            case QuickWithdraw:
                ShowQuickWithdrawScreen();
                DoQuickWithdraw();
                break;
            case NormalWithdraw:
                ShowWithdrawScreen();
                DoWithdraw();
                break;
            case Deposit:
                ShowDepositScreen();
                DoDeposit();
                break;
            case CheckBalance:
                ShowCheckBalanceScreen();
                cout << "Your total balance is : " << client.AccountBalance << endl;
        }
        cout << "Press any key to go back to main menu";
        system("pause>0");
        system("cls");
        s = ShowMainMenu();
    }
    system("pause");
    return ;
}
void ShowLoginScreen()
{
    cout << "--------------------------------------\n";
    cout << setw(25) << right << "Login Screen\n";
    cout << "--------------------------------------\n";
}
void Login()
{
    vector <sClient> vClients = LoadClientsFromFiletoVector(ClientsFileName);
    string accountnum , pincode ;
    bool c = true;
    while (c == true)
    {
            ShowLoginScreen();
            accountnum = ReadClientAccountNumber();
            pincode = ReadClientPincode();
            while (!FindClientByAccountNumberAndPincode(accountnum , pincode ,vClients))
            {
                system("cls");
                ShowLoginScreen();
                cout << "Invalid account number/password!\n";
                accountnum = ReadClientAccountNumber();
                pincode = ReadClientPincode();
            }
            StartAtming();
            system("cls");
    }
}
int main()
{
    Login();
    return 0;
}


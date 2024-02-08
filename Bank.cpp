#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

const string ClientsFileName = "neweeFile of Negm.txt" ;
enum MainMenu {ShowClientList = 1 , AddnewClient = 2 , DeleteClient = 3 , UpdateClient = 4 , FindClient = 5 , Transaction = 6 ,Exit = 7};
enum TranscationMainMenu {Deposit = 1 , Withdraw = 2 , TotalBalance = 3 , MainMenue = 4 };
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
    cout << setw(17) << right << "[7] Exit\n";
    cout << "===============================================\n";
    cout << "Choose what you want to do [1 to 7]?";
    cin >> Choice ;
    while ((Choice > 7 && Choice >= 1) || (Choice <= 7 && Choice < 1))
    {
        cout << "\nInvalid choice!\n" << "Choose What you want to do [1 to 7]?";
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
            return MainMenu :: Exit ;
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
    cout << setw(27) << right << "[3] Total Balance.\n";
    cout << setw(23) << right << "[4] Main Menu.\n";
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
            cout << "Are you want to do this transaction?y/n?";
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
void StartBanking()
{
    vector <sClient> Vclients = LoadClientsFromFiletoVector(ClientsFileName);
    vector <sClient> newvclient ;
    MainMenu s = ShowMainMenu();
    system("cls");
    sClient client;
    while(s != Exit)
    {
        switch (s)
        {
            case ShowClientList:
                Vclients = LoadClientsFromFiletoVector(ClientsFileName);
                PrintAllClientsData(Vclients);
                break;
            case AddnewClient:
                ShowAddClientScreen();
                Addclients();
                Vclients = LoadClientsFromFiletoVector(ClientsFileName);
                break;
            case DeleteClient:
                ShowDeleteClientScreen();
                newvclient = DeleteRecordbyAccountnumber(ReadClientAccountNumber(),Vclients);
                SaveCleintsDataToFile(ClientsFileName,newvclient);
                Vclients = LoadClientsFromFiletoVector(ClientsFileName);
                break;
            case UpdateClient:
                ShowUpdateClientInfoScreen();
                UpdateClientByAccountNumber(ReadClientAccountNumber(),Vclients);
                Vclients = LoadClientsFromFiletoVector(ClientsFileName);
                break;
            case FindClient:
                {
                    ShowFindClientScreen();
                    string AccountNumber = ReadClientAccountNumber();
                    if(FindClientByAccountNumber(AccountNumber,Vclients,client))
                        displayclient(client);
                    else
                        cout << "Client with account number [" << AccountNumber << "] not found !\n";
                    break;
                }
            case Transaction:
                ShowTransactionScreen();
                PerformTranactionMenuOption((TranscationMainMenu)GetClientChoice());
                break;
        }
        cout << "Press any key to go back to main menu";
        system("pause>0");
        system("cls");
        s = ShowMainMenu();
    }
    ShowExitScreen();
    system("pause");
    return ;
}
int main()
{
    StartBanking();
    return 0;
}


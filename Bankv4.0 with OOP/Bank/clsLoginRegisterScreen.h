#pragma once

#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsUser.h"

class clsLoginRegisterScreen : protected clsScreen
{
    private:
        static void PrintLoginRegisterRecord  (clsUser::stLoginRegisterRecord LRR)
        {
            cout << setw(16) << left << "" << "| " << setw(25) << left << LRR.Date;
            cout << "| " << setw(30) << left << LRR.UserName;
            cout << "| " << setw(12) << left << LRR.Password;
            cout << "| " << setw(12) << left << LRR.permission;
        }
    public:
        static void ShowLoginRegister()
        {
            if (!CheckAccessRights(clsUser::enPermissions::pManageUsers))
            {
                return;// this will exit the function and it will not continue
            }
            vector <clsUser::stLoginRegisterRecord> vLRR = clsUser::GetLoginRegisterList();
            string Title = "\t  Login Register list Screen";
            string SubTitle = "\t    (" + to_string(vLRR.size()) + ") Record(s).";
            _DrawScreenHeader(Title, SubTitle);
            //_DrawUserScreen();
            //_DrawDateScreen();
            cout << setw(25) << left << "" << "\n\t\t____________________________________________________________________";
            cout << "__________________________\n" << endl;

            cout << setw(16) << left << "" << "| " << left << setw(25) << "Date";
            cout << "| " << left << setw(30) << "UserName";
            cout << "| " << left << setw(12) << "Password";
            cout << "| " << left << setw(12) << "permission";
            cout << setw(25) << left << "" << "\n\t\t____________________________________________________________________";
            cout << "__________________________\n" << endl;
            
            if (vLRR.size() == 0)
                cout << "\t\t\t\tNo Login Registers Available In the System!";
            else

                for (clsUser::stLoginRegisterRecord LRR : vLRR)
                {
                    PrintLoginRegisterRecord(LRR);
                    cout << endl;
                }

            cout << setw(25) << left << "" << "\n\t\t____________________________________________________________________";
            cout << "__________________________\n" << endl;
        }
};
/*
* ABU HADHOUD CLASS
* class clsLoginRegisterScreen :protected clsScreen
{

private:
    
    static void PrintLoginRegisterRecordLine(clsUser::stLoginRegisterRecord LoginRegisterRecord)
    {

        cout << setw(8) << left << "" << "| " << setw(35) << left << LoginRegisterRecord.DateTime;
        cout << "| " << setw(20) << left << LoginRegisterRecord.UserName;
        cout << "| " << setw(20) << left << LoginRegisterRecord.Password;
        cout << "| " << setw(10) << left << LoginRegisterRecord.Permissions;
    }

public:
  
    static void ShowLoginRegisterScreen()
    {

        vector <clsUser::stLoginRegisterRecord> vLoginRegisterRecord = clsUser::GetLoginRegisterList();
  
        string Title = "\tLogin Register List Screen";
        string SubTitle =  "\t\t(" + to_string(vLoginRegisterRecord.size()) + ") Record(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(35) << "Date/Time";
        cout << "| " << left << setw(20) << "UserName";
        cout << "| " << left << setw(20) << "Password";
        cout << "| " << left << setw(10) << "Permissions";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vLoginRegisterRecord.size() == 0)
            cout << "\t\t\t\tNo Logins Available In the System!";
        else

            for (clsUser::stLoginRegisterRecord Record : vLoginRegisterRecord)
            {

                PrintLoginRegisterRecordLine(Record);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

    }

};


*/

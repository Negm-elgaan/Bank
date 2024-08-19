#pragma once
#include <iostream>
#include "Global.h"
#include "clsdate.h"

using namespace std;

class clsScreen
{
protected:
    static void _DrawScreenHeader(string Title, string SubTitle = "")
    {
        cout << "\t\t\t\t\t______________________________________";
        cout << "\n\n\t\t\t\t\t  " << Title;
        if (SubTitle != "")
        {
            cout << "\n\t\t\t\t\t  " << SubTitle;
        }
        cout << "\n\t\t\t\t\t______________________________________\n\n";
        cout << "\n\t\t\t\t\tUser: " << CurrentUser.UserName << "\n";
        cout << "\t\t\t\t\tDate: " << clsDate::DateToString(clsDate())
            << "\n\n";

    }

    static void _DrawDateScreen()
    {
        clsDate Date = clsDate::GetSystemDate();
        cout << "\t\t\t\t\tDate:" << Date.GetDay() << "/" << Date.GetMonth() << "/" << Date.GetYear();
    }

    static void _DrawUserScreen()
    {
        cout << "\n\t\t\t\t\tUser:" << CurrentUser.GetUserName() << "\n";
    }

    static bool CheckAccessRights(clsUser::enPermissions Permission)
    {

        if (!CurrentUser.CheckAccessPermission(Permission))
        {
            cout << "\t\t\t\t\t______________________________________";
            cout << "\n\n\t\t\t\t\t  Access Denied! Contact your Admin.";
            cout << "\n\t\t\t\t\t______________________________________\n\n";
            return false;
        }
        else
        {
            return true;
        }

    }

};


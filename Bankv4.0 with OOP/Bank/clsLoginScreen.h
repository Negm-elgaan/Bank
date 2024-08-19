#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsPerson.h"
#include <vector>   
#include <fstream>
#include <iomanip>
#include "clsMainScreen.h"
#include "Global.h"

class clsLoginScreen :protected clsScreen
{

private:

    static  void _Login()
    {
        bool LoginFaild = false;
        short LoginCounter = 3;
        string Username, Password;
        do
        {

            if (LoginFaild)
            {
                cout << "\nInvlaid Username/Password!\n\n";
                LoginCounter--;
                if (LoginCounter == 0)
                {
                    cout << "You are locked out after 3 failed trails\n\n";
                    Exit = true;
                    return;
                }
                cout << "You have " << LoginCounter << " Trials to login";
            }

            cout << "Enter Username? ";
            cin >> Username;

            cout << "Enter Password? ";
            cin >> Password;

            CurrentUser = clsUser::Find(Username, Password);

            LoginFaild = CurrentUser.IsEmpty();

        } while (LoginFaild);
        /*fstream MyFile;
        MyFile.open("LoginRegister.txt", ios::out | ios::app);
        time_t t = time(0);
        tm* now = localtime(&t);
        if (MyFile.is_open())
        {
            string Line = clsDate::DateToString(clsDate()) + " - " + to_string(now->tm_hour) + ":" + to_string(now->tm_min) + ":" + to_string(now->tm_sec) + "#//#" + CurrentUser.UserName + "#//#" + CurrentUser.Password + "#//#" + to_string(CurrentUser.Permissions);
            MyFile << Line << endl;
            MyFile.close();
        }*/
        CurrentUser.RegisterLogIn();
        clsMainScreen::ShowMainMenue();

    }

public:


    static void ShowLoginScreen()
    {
        system("cls");
        _DrawScreenHeader("\t  Login Screen");
        //_DrawDateScreen();
        //_DrawUserScreen();
        _Login();

    }

};


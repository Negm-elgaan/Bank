#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsString.h"
#include <vector>
#include <fstream>

class clsTransferScreen : protected clsScreen
{
	private:

		static void _PrintClient(clsBankClient Client)
		{
			cout << "\nClient Card:";
			cout << "\n___________________";
			cout << "\nFirstName   : " << Client.FirstName;
			cout << "\nLastName    : " << Client.LastName;
			cout << "\nFull Name   : " << Client.FullName();
			cout << "\nEmail       : " << Client.Email;
			cout << "\nPhone       : " << Client.Phone;
			cout << "\nAcc. Number : " << Client.AccountNumber();
			cout << "\nPassword    : " << Client.PinCode;
			cout << "\nBalance     : " << Client.AccountBalance;
			cout << "\n___________________\n";

		}

		static string _ReadAccountNumber(string message)
		{
			string AccountNumber = "";
			cout << message;
			cin >> AccountNumber;
			return AccountNumber;
		}
		
	public:

		static struct stTransferLogRecord
		{
			string Date;
			string SenderAccountNumber;
			string ReceiverAccountNumber;
			double TransferAmount;
			double SenderBalance;
			double ReceiverBalance;
			string UserName;
		};
		
		static string _PrepareTransferLogRecord(stTransferLogRecord TLR, string Seperator = "#//#")
		{
			string TransferLogRecord = "";
			TransferLogRecord += TLR.Date + Seperator;
			TransferLogRecord += TLR.SenderAccountNumber + Seperator;
			TransferLogRecord += TLR.ReceiverAccountNumber + Seperator;
			TransferLogRecord += to_string(TLR.TransferAmount) + Seperator;
			TransferLogRecord += to_string(TLR.SenderBalance) + Seperator;
			TransferLogRecord += to_string(TLR.ReceiverBalance) + Seperator;
			TransferLogRecord += CurrentUser.UserName + Seperator;
			return TransferLogRecord;
		}

		static void SaveToTransferLogFile(stTransferLogRecord TLR)
		{
			string stDataLine = _PrepareTransferLogRecord(TLR);

			fstream MyFile;
			MyFile.open("Transfer Log.txt", ios::out | ios::app);

			if (MyFile.is_open())
			{

				MyFile << stDataLine << endl;

				MyFile.close();
			}
		}

		static stTransferLogRecord _ConvertLinetoTransferLogStructure(string Line, string Seperator = "#//#")
		{
			stTransferLogRecord TLR;
			vector <string> TLRData = clsString::Split(Line, Seperator);
			TLR.Date = TLRData[0];
			TLR.SenderAccountNumber = TLRData[1];
			TLR.ReceiverAccountNumber = TLRData[2];
			TLR.TransferAmount = stoi(TLRData[3]);
			TLR.SenderBalance = stoi(TLRData[4]);
			TLR.ReceiverBalance = stoi(TLRData[5]);
			TLR.UserName = TLRData[6];
			return TLR;
		}

		static vector <stTransferLogRecord> GetTransferLogRecord()
		{
			vector <stTransferLogRecord> TLRS;
			fstream MyFile;
			MyFile.open("Transfer Log.txt", ios::in);//read Mode

			if (MyFile.is_open())
			{

				string Line;

				while (getline(MyFile, Line))
				{

					stTransferLogRecord TLR = _ConvertLinetoTransferLogStructure(Line);

					TLRS.push_back(TLR);
				}

				MyFile.close();

			}

			return TLRS;
		}

		static void ShowTransferScreen()
		{
			_DrawScreenHeader("\t   Transfer Screen");
			//_DrawDateScreen();
			//_DrawUserScreen();
			stTransferLogRecord TLR;
			string AccountNumber = _ReadAccountNumber("\nPlease enter AccountNumber to transfer from? ");


			while (!clsBankClient::IsClientExist(AccountNumber))
			{
				cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
				AccountNumber = _ReadAccountNumber("\nPlease enter AccountNumber to transfer from ? ");
			}
			TLR.SenderAccountNumber = AccountNumber;
			clsBankClient Client1 = clsBankClient::Find(AccountNumber);
			_PrintClient(Client1);

			AccountNumber = _ReadAccountNumber("\nPlease enter AccountNumber to transfer to? ");

			while (!clsBankClient::IsClientExist(AccountNumber))
			{
				cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
				AccountNumber = _ReadAccountNumber("\nPlease enter AccountNumber to transfer to? ");
			}
			TLR.ReceiverAccountNumber = AccountNumber;
			clsBankClient Client2 = clsBankClient::Find(AccountNumber);
			_PrintClient(Client2);

			double Amount = 0;
			cout << "\nPlease enter Transfer amount? ";
			Amount = clsInputValidate::ReadDblNumber();
			TLR.TransferAmount = Amount;
			cout << "\nAre you sure you want to perform this transaction? ";
			char Answer = 'n';
			cin >> Answer;

			if (Answer == 'Y' || Answer == 'y')
			{
				if (Client1.Withdraw(Amount))
				{
					cout << "\nAmount Transfered Successfully.\n";
					cout << "\nNew Balance of " << Client1.AccountNumber() << " is: " << Client1.AccountBalance;
					Client2.Deposit(Amount);
					cout << "\nNew Balance of " << Client2.AccountNumber() << " is: " << Client2.AccountBalance;
					TLR.Date = clsDate::GetSystemDateTimeString();
					TLR.SenderBalance = Client1.AccountBalance;
					TLR.ReceiverBalance = Client2.AccountBalance;
					TLR.UserName = CurrentUser.UserName;
					SaveToTransferLogFile(TLR);

				}
				else
				{
					cout << "\nCannot transfer, Insuffecient Balance!\n";
					cout << "\nAmonut to transfer is: " << Amount;
					cout << "\nYour Balance is: " << Client1.AccountBalance;

				}
			}
			else
			{
				cout << "\nOperation was cancelled.\n";
			}
		}
};

/*
* ABU HADHOUD CLASS
* #pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsTransferScreen :protected clsScreen
{

private:
    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________\n";
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nAcc. Number : " << Client.AccountNumber();
        cout << "\nBalance     : " << Client.AccountBalance;
        cout << "\n___________________\n";

    }

   static string _ReadAccountNumber()
    {
        string AccountNumber;
        cout << "\nPlease Enter Account Number to Transfer From: ";
        AccountNumber = clsInputValidate::ReadString();
        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }
        return AccountNumber;
    }

   static float ReadAmount(clsBankClient SourceClient)
   {
       float Amount;

       cout << "\nEnter Transfer Amount? ";

       Amount = clsInputValidate::ReadFloatNumber();

       while (Amount > SourceClient.AccountBalance)
       {
           cout << "\nAmount Exceeds the available Balance, Enter another Amount ? ";
           Amount = clsInputValidate::ReadDblNumber();
       }
       return Amount;
   }

public:

    static void ShowTransferScreen()
    {
      
        _DrawScreenHeader("\tTransfer Screen");

        clsBankClient SourceClient = clsBankClient::Find(_ReadAccountNumber());

        _PrintClient(SourceClient);

        clsBankClient DestinationClient = clsBankClient::Find(_ReadAccountNumber());

        _PrintClient(DestinationClient);

        float Amount = ReadAmount(SourceClient);

        
        cout << "\nAre you sure you want to perform this operation? y/n? ";
        char Answer = 'n';
        cin >> Answer;
        if (Answer == 'Y' || Answer == 'y')
        {
            if (SourceClient.Transfer(Amount, DestinationClient,CurrentUser.UserName))
            {
                cout << "\nTransfer done successfully\n";
            }
            else
            {
                cout << "\nTransfer Faild \n";
            }
        }

        _PrintClient(SourceClient);
        _PrintClient(DestinationClient);


    }

};




*/
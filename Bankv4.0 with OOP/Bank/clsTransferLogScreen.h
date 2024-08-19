#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsTransferScreen.h"

class clsTransferLogScreen : protected clsScreen
{
private:

    static void PrintTransferLogRecord(clsTransferScreen::stTransferLogRecord LRR)
    {
        cout << setw(16) << left << "" << "| " << setw(25) << left << LRR.Date;
        cout << "| " << setw(10) << left << LRR.SenderAccountNumber;
        cout << "| " << setw(10) << left << LRR.ReceiverAccountNumber;
        cout << "| " << setw(10) << left << LRR.TransferAmount;
        cout << "| " << setw(10) << left << LRR.SenderBalance;
        cout << "| " << setw(10) << left << LRR.ReceiverBalance;
        cout << "| " << setw(10) << left << LRR.UserName;
    }
public:

    static void ShowTransferLogRecord()
    {

        vector <clsTransferScreen::stTransferLogRecord> vTLR = clsTransferScreen::GetTransferLogRecord();
        string Title = "\t  Transfer Log list Screen";
        string SubTitle = "\t    (" + to_string(vTLR.size()) + ") Record(s).";
        _DrawScreenHeader(Title, SubTitle);
        cout << setw(25) << left << "" << "\n\t\t____________________________________________________________________";
        cout << "__________________________\n" << endl;

        cout << setw(16) << left << "" << "| " << left << setw(25) << "Date/Time";
        cout << "| " << left << setw(10) << "S.Acct";
        cout << "| " << left << setw(10) << "R.Acct";
        cout << "| " << left << setw(10) << "Amount";
        cout << "| " << left << setw(10) << "S.Balance";
        cout << "| " << left << setw(10) << "R.Balance";
        cout << "| " << left << setw(10) << "User";
        cout << setw(25) << left << "" << "\n\t\t____________________________________________________________________";
        cout << "__________________________\n" << endl;

        if (vTLR.size() == 0)
            cout << "\t\t\t\tNo Login Registers Available In the System!";
        else

            for (clsTransferScreen::stTransferLogRecord TLR : vTLR)
            {
                PrintTransferLogRecord(TLR);
                cout << endl;
            }

        cout << setw(25) << left << "" << "\n\t\t____________________________________________________________________";
        cout << "__________________________\n" << endl;
    }
};

/*
* #pragma once

#include <iostream>
#include "clsScreen.h"
#include <iomanip>
#include <fstream>
#include "clsBankClient.h"


class clsTransferLogScreen :protected clsScreen
{

private:

    static void PrintTransferLogRecordLine(clsBankClient::stTrnsferLogRecord TransferLogRecord)
    {

        cout << setw(8) << left << "" << "| " << setw(23) << left << TransferLogRecord.DateTime;
        cout << "| " << setw(8) << left << TransferLogRecord.SourceAccountNumber;
        cout << "| " << setw(8) << left << TransferLogRecord.DestinationAccountNumber;
        cout << "| " << setw(8) << left << TransferLogRecord.Amount;
        cout << "| " << setw(10) << left << TransferLogRecord.srcBalanceAfter;
        cout << "| " << setw(10) << left << TransferLogRecord.destBalanceAfter;
        cout << "| " << setw(8) << left << TransferLogRecord.UserName;

      
    }

public:

    static void ShowTransferLogScreen()
    {


        vector <clsBankClient::stTrnsferLogRecord> vTransferLogRecord = clsBankClient::GetTransfersLogList();

        string Title = "\tTransfer Log List Screen";
        string SubTitle = "\t    (" + to_string(vTransferLogRecord.size()) + ") Record(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(23) << "Date/Time";
        cout << "| " << left << setw(8) << "s.Acct";
        cout << "| " << left << setw(8) << "d.Acct";
        cout << "| " << left << setw(8) << "Amount";
        cout << "| " << left << setw(10) << "s.Balance";
        cout << "| " << left << setw(10) << "d.Balance";
        cout << "| " << left << setw(8) << "User";

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vTransferLogRecord.size() == 0)
            cout << "\t\t\t\tNo Transfers Available In the System!";
        else

            for (clsBankClient::stTrnsferLogRecord Record : vTransferLogRecord)
            {

                PrintTransferLogRecordLine(Record);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

    }

};

*/
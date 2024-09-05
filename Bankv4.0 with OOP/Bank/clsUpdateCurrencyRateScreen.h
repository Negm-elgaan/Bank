#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsUser.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

class clsUpdateCurrencyRateScreen:protected clsScreen
{
    static void _printCurrency(clsCurrency Currency)
    {
        cout << "\nCurrency Card:";
        cout << "\n___________________";
        cout << "\nCountry   : " << Currency.Country();
        cout << "\nCode    : " << Currency.CurrencyCode();
        cout << "\nName   : " << Currency.CurrencyName();
        cout << "\nRate(1$)   : " << Currency.Rate();
    }
    static void _UpdateCurrencyRate(clsCurrency &Currency)
    {
        float NewRate = 0;
        cout << "Enter new Rate: ";
        cin >> NewRate;
        Currency.UpdateRate(NewRate);
    }
	public:
        static void ShowUpdateCurrencyRateScreen()
        {

            _DrawScreenHeader("\tUpdate Currency Screen");
            //_DrawDateScreen();
            //_DrawUserScreen();

            string Code = "";

            cout << "\nPlease Enter Currency Code?: ";
            Code = clsInputValidate::ReadString();

            while (!clsCurrency::IsCurrencyExist(Code))
            {
                cout << "\nCurrency is not found, choose another one: ";
                Code = clsInputValidate::ReadString();
            }

            clsCurrency Currency = clsCurrency::FindByCode(Code);

            _printCurrency(Currency);

            cout << "\nAre you sure you want to update rate of this currency y/n? ";

            char Answer = 'n';
            cin >> Answer;

            if (Answer == 'y' || Answer == 'Y')
            {

                cout << "\n\nUpdate Currency Rate:";
                cout << "\n____________________\n";


                _UpdateCurrencyRate(Currency);
                cout << "\nCurrency Updated Successfully :-)\n";
                _printCurrency(Currency);

            }

        }
};

/*#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

class clsUpdateCurrencyRateScreen :protected clsScreen

{
private:

    static float _ReadRate()
    {
        cout << "\nEnter New Rate: ";
        float NewRate = 0;

        NewRate = clsInputValidate::ReadFloatNumber();
        return NewRate;
    }

    static void _PrintCurrency(clsCurrency Currency)
    {
        cout << "\nCurrency Card:\n";
        cout << "_____________________________\n";
        cout << "\nCountry    : " << Currency.Country();
        cout << "\nCode       : " << Currency.CurrencyCode();
        cout << "\nName       : " << Currency.CurrencyName();
        cout << "\nRate(1$) = : " << Currency.Rate();

        cout << "\n_____________________________\n";

    }

public:

    static void ShowUpdateCurrencyRateScreen()
    {

        _DrawScreenHeader("\tUpdate Currency Screen");

        string CurrencyCode = "";

        cout << "\nPlease Enter Currency Code: ";
        CurrencyCode = clsInputValidate::ReadString();

        while (!clsCurrency::IsCurrencyExist(CurrencyCode))
        {
            cout << "\nCurrency is not found, choose another one: ";
            CurrencyCode = clsInputValidate::ReadString();
        }

        clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
        _PrintCurrency(Currency);

        cout << "\nAre you sure you want to update the rate of this Currency y/n? ";

        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {

            cout << "\n\nUpdate Currency Rate:";
            cout << "\n____________________\n";

            Currency.UpdateRate( _ReadRate());

            cout << "\nCurrency Rate Updated Successfully :-)\n";
            _PrintCurrency(Currency);
          

        }

    }
};


*/

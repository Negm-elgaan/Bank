#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsUser.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"
class clsCurrencyCalculatorScreen : protected clsScreen
{
    static void _printCurrency(clsCurrency Currency)
    {
        //cout << "\nCurrency Card:";
        cout << "\n___________________";
        cout << "\nCountry   : " << Currency.Country();
        cout << "\nCode    : " << Currency.CurrencyCode();
        cout << "\nName   : " << Currency.CurrencyName();
        cout << "\nRate(1$)   : " << Currency.Rate();
        cout << "\n___________________\n\n";
    }  

    static float _ReadAmount()
    {
        float Amount = 0;
        cout << "Enter Amount to exchange: ";
        Amount = clsInputValidate::ReadFloatNumber();
    }

    public:
        static void ShowCurrencyExchangeCalculator()
        {
            char Choice = ' ';
            do
            {
                system("cls");
                _DrawScreenHeader("Currency Calculator Screen");
                cout << "Please enter currency1 code: ";
                string code1 = clsInputValidate::ReadString();

                cout << "\n\nPlease Enter Currency2 code: ";
                string code2 = clsInputValidate::ReadString();

                if (clsCurrency::IsCurrencyExist(code1) && clsCurrency::IsCurrencyExist(code2))
                {
                    cout << "\n\nEnter Amount to exchange: ";
                    float Amount = clsInputValidate::ReadFloatNumber();
                    cout << "\n\nConvert From:\n\n";

                    clsCurrency Currency1 = clsCurrency::FindByCode(code1);
                    _printCurrency(Currency1);

                    float Exchange = Amount / Currency1.Rate();
                    cout << Amount << " " << Currency1.CurrencyCode() << " = " << Exchange << " USD\n\n";

                    clsCurrency Currency2 = clsCurrency::FindByCode(code2);
                    if (Currency2.CurrencyCode() != "USD")
                    {
                        cout << "Converting from USD\n\n" << "To\n\n";
                        _printCurrency(Currency2);

                        Exchange *= Currency2.Rate();
                        cout << Amount << " " << Currency1.CurrencyCode() << " = " << Exchange << " " << Currency2.CurrencyCode();
                    }
                }

                else
                {
                    cout << "Invalid Currency Code\n";
                }

                cout << "\nDo you want to perform another calculation ? y/n ?";
                cin >> Choice;

            } while (Choice == 'y' || Choice == 'Y');
        }
};
/*#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

class clsCurrencyCalculatorScreen :protected clsScreen

{
private:

    static float _ReadAmount()
    {
        cout << "\nEnter Amount to Exchange: ";
        float Amount = 0;

        Amount = clsInputValidate::ReadFloatNumber();
        return Amount;
    }

    static clsCurrency _GetCurrency(string Message)
    {

        string CurrencyCode;
        cout << Message << endl;

        CurrencyCode = clsInputValidate::ReadString();

        while (!clsCurrency::IsCurrencyExist(CurrencyCode))
        {
            cout << "\nCurrency is not found, choose another one: ";
            CurrencyCode = clsInputValidate::ReadString();
        }

        clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
        return Currency;

    }


    static  void _PrintCurrencyCard(clsCurrency Currency, string Title = "Currency Card:")
    {

        cout << "\n" << Title << "\n";
        cout << "_____________________________\n";
        cout << "\nCountry       : " << Currency.Country();
        cout << "\nCode          : " << Currency.CurrencyCode();
        cout << "\nName          : " << Currency.CurrencyName();
        cout << "\nRate(1$) =    : " << Currency.Rate();
        cout << "\n_____________________________\n\n";

    }
   
    static void _PrintCalculationsResults(float Amount, clsCurrency Currency1, clsCurrency Currency2)
    {

        _PrintCurrencyCard(Currency1, "Convert From:");

        float AmountInUSD = Currency1.ConvertToUSD(Amount);

        cout << Amount << " " << Currency1.CurrencyCode()
            << " = " << AmountInUSD << " USD\n";

        if (Currency2.CurrencyCode() == "USD")
        {
            return;
        }

        cout << "\nConverting from USD to:\n";

        _PrintCurrencyCard(Currency2, "To:");

        float AmountInCurrrency2 = Currency1.ConvertToOtherCurrency(Amount, Currency2);

        cout << Amount << " " << Currency1.CurrencyCode()
            << " = " << AmountInCurrrency2 << " " << Currency2.CurrencyCode();

    }


public:

    static void ShowCurrencyCalculatorScreen()
    {
        char Continue = 'y';

        while (Continue == 'y' || Continue == 'Y')
        {
            system("cls");

            _DrawScreenHeader("\tUpdate Currency Screen");

            clsCurrency CurrencyFrom = _GetCurrency("\nPlease Enter Currency1 Code: ");
            clsCurrency CurrencyTo = _GetCurrency("\nPlease Enter Currency2 Code: ");
            float Amount = _ReadAmount();

            _PrintCalculationsResults(Amount, CurrencyFrom, CurrencyTo);

            cout << "\n\nDo you want to perform another calculation? y/n ? ";
            cin >> Continue;

        }


    }
};

*/
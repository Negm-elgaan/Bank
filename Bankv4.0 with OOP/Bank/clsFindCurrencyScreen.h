#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsUser.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

class clsFindCurrencyScreen : protected clsScreen
{
	enum enCodeOrCountry {enCode = 1 , enCountry = 2};

	static void _printCurrency(clsCurrency Currency)
	{
		cout << "\nCurrency Card:";
		cout << "\n___________________";
		cout << "\nCountry   : " << Currency.Country();
		cout << "\nCode    : " << Currency.CurrencyCode();
		cout << "\nName   : " << Currency.CurrencyName();
		cout << "\nRate(1$)   : " << Currency.Rate();
	}

	static void _FindCurrencyByCode(string code)
	{
		clsCurrency Currency = clsCurrency::FindByCode(code);

		if (!Currency.IsEmpty())
		{
			cout << "\nCurrency Found :-)\n";
		}
		else
		{
			cout << "\nCurrency Was not Found :-(\n";
		}

		_printCurrency(Currency);
	}

	static void _FindCurrencyByCountry(string Country)
	{
		clsCurrency Currency = clsCurrency::FindByCountry(Country);

		if (!Currency.IsEmpty())
		{
			cout << "\nCurrency Found :-)\n";
		}
		else
		{
			cout << "\nCurrency Was not Found :-(\n";
		}

		_printCurrency(Currency);

	}

	static short _ReadCurrencySearchOption()
	{
		cout << "Find By : [1]Code or [2]Country ? ";
		short Choice = clsInputValidate::ReadShortNumberBetween(1, 2);
		return Choice;
	}

	static void _PerformCuurencySearchOption(enCodeOrCountry Option)
	{
		string code;
		string country;
		switch (Option)
		{
			case enCode:
				code = clsInputValidate::ReadString();
				while (!clsCurrency::IsCurrencyExist(code))
				{
					cout << "\nCurrency is not found, choose another one: ";
					code = clsInputValidate::ReadString();
				}
				_FindCurrencyByCode(code);
				break;
			case enCountry:
				country = clsInputValidate::ReadString();
				while (!clsCurrency::IsCurrencyExist2(country))
				{
					cout << "\nCurrency is not found, choose another one: ";
					country = clsInputValidate::ReadString();
				}
				_FindCurrencyByCountry(country);
				break;
		}
	}
	public:
		static void ShowFindCurrencyScreen()
		{
			_DrawScreenHeader("\t  Find Currency Screen");
			_PerformCuurencySearchOption((enCodeOrCountry)_ReadCurrencySearchOption());
		}
};

/*
* Abu Hadhoud Class
* #pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

class clsFindCurrencyScreen :protected clsScreen
{

private:
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

   static void _ShowResults(clsCurrency Currency)
    {
        if (!Currency.IsEmpty())
        {
            cout << "\nCurrency Found :-)\n";
            _PrintCurrency(Currency);
        }
        else
        {
            cout << "\nCurrency Was not Found :-(\n";
        }
    }

public:

    static void ShowFindCurrencyScreen()
    {

        _DrawScreenHeader("\t  Find Currency Screen");

        cout << "\nFind By: [1] Code or [2] Country ? ";
        short Answer = 1;

        cin >> Answer;
       
        if (Answer == 1)
        {
            string CurrencyCode;
            cout << "\nPlease Enter CurrencyCode: ";
            CurrencyCode = clsInputValidate::ReadString();
            clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
            _ShowResults(Currency);
        }
        else
        {
            string Country;
            cout << "\nPlease Enter Country Name: ";
            Country = clsInputValidate::ReadString();
            clsCurrency Currency = clsCurrency::FindByCountry(Country);
            _ShowResults(Currency);
        }
        

      

       

    }

};

*/
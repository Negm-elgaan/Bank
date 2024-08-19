#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsAddNewUserScreen.h"
#include "Global.h"
#include "clsLoginScreen.h"

class clsRegisterScreen:protected clsScreen
{
	private:

		static void _Register()
		{
			clsAddNewUserScreen::ShowAddNewUserScreen(true);
		}

	public:
		static void ShowRegisterScreen()
		{
			vector <clsUser> vUsers = clsUser::GetUsersList();

			if (vUsers.size() == 0)
			{
				_DrawScreenHeader("\t  Register Screen");
				//_DrawDateScreen();
				//_DrawUserScreen();
				_Register();
			}
			while (Exit == false)
			{
				clsLoginScreen::ShowLoginScreen();
			}
		}
};


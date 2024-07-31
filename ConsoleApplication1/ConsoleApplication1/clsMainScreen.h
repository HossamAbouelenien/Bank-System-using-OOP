#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include "clsUtil.h"
#include "clsScreen.h"
#include "clsClientListScreen.h"
#include "clsAddingNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdatingCLientsScreen.h"
#include "clsFindClientScreen.h"
#include "clsShowTransactionsMenueScreen.h"
#include "clsManageUserScreen.h"
#include "global.h"

using namespace std;

class clsMainScreen : protected clsScreen
{
private:
    enum enMainMenueOptions {
        eListClients = 1, eAddNewClient = 2, eDeleteClient = 3,
        eUpdateClient = 4, eFindClient = 5, eShowTransactionsMenue = 6,
        eManageUsers = 7,  eExit = 8
    };

    static short _ReadMainMenueOption() {
        cout << setw(30) << left << "" << "Choose What do you want [1 - 8] ? ";
        int choice = clsInputValidate::ReadIntNumberBetween(1, 8, "Enter again [1 - 8] ");
        return choice;
    }

    static  void _GoBackToMainMenue()
    {
        cout << "\n\tPress any key to go back to Main Menue...\n";
        system("pause > 0");
        ShowMainMenue();
    }

    static void _ShowAllClientsScreen()
    {
        clsClientListScreen::ShowCLientsList();


    }

    static void _ShowAddNewClientsScreen()
    {
        clsAddingNewClientScreen::AddNewClient();

    }

    static void _ShowDeleteClientScreen()
    {
        clsDeleteClientScreen::DeleteClients();

    }

    static void _ShowUpdateClientScreen()
    {
        clsUpdatingCLientsScreen::UpdateClients();

    }

    static void _ShowFindClientScreen()
    {
        clsFindClientScreen::FindClient();

    }

    static void _ShowTransactionsMenue()
    {
        clsShowTransactionsMenueScreen::ShowTransactionsMenue();

    }

    static void _ShowManageUsersMenue()
    {
        clsManageUserScreen::ShowManageUsersMenue();

    }


    static void _Logout() {

        CurrentUser = clsUser::Find("", "");

    }

    static void _PerfromMainMenueOption(enMainMenueOptions MainMenueOption) {
        switch (MainMenueOption) {
        case enMainMenueOptions::eListClients: {
            system("cls");
            _ShowAllClientsScreen();
            _GoBackToMainMenue();
            break;
        }
        case enMainMenueOptions::eAddNewClient: {
            system("cls");
            _ShowAddNewClientsScreen();
            _GoBackToMainMenue();
            break;
        }
        case enMainMenueOptions::eDeleteClient: {
            system("cls");
            _ShowDeleteClientScreen();
            _GoBackToMainMenue();
            break;
        }
        case enMainMenueOptions::eUpdateClient: {
            system("cls");
            _ShowUpdateClientScreen();
            _GoBackToMainMenue();
            break;
        }
        case enMainMenueOptions::eFindClient: {
            system("cls");
            _ShowFindClientScreen();
            _GoBackToMainMenue();
            break;
        }
        case enMainMenueOptions::eShowTransactionsMenue: {
            system("cls");
            _ShowTransactionsMenue();
            _GoBackToMainMenue();
            break;
        }
        case enMainMenueOptions::eManageUsers: {
            system("cls");
            _ShowManageUsersMenue();
            _GoBackToMainMenue(); 
            break;
        }
      
        case enMainMenueOptions::eExit: {
            system("cls");
            _Logout();
            break;

        }
        }
    }

public:

	static void ShowMainMenue() {
        
        system("cls");
		_DrawScreenHeader("\t\t\tMain Screen");

        cout << setw(30) << left << "" << "===========================================\n";
        cout << setw(30) << left << "" << "\t\t\tMain Menue\n";
        cout << setw(30) << left << "" << "===========================================\n";
        cout << setw(30) << left << "" << "\t[1] Show Client List.\n";
        cout << setw(30) << left << "" << "\t[2] Add New Client.\n";
        cout << setw(30) << left << "" << "\t[3] Delete Client.\n";
        cout << setw(30) << left << "" << "\t[4] Update Client Info.\n";
        cout << setw(30) << left << "" << "\t[5] Find Client.\n";
        cout << setw(30) << left << "" << "\t[6] Transactions.\n";
        cout << setw(30) << left << "" << "\t[7] Manage Users.\n";
        cout << setw(30) << left << "" << "\t[8] Logout.\n";
        cout << setw(30) << left << "" << "===========================================\n";


    _PerfromMainMenueOption((enMainMenueOptions)_ReadMainMenueOption());

	}





};


#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsDepositeScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"

class clsShowTransactionsMenueScreen : protected clsScreen
{
private:
    enum enTransactionsMenueOptions {
        eDeposit = 1, eWithdraw = 2,
        eShowTotalBalance = 3, eShowMainMenue = 4
    };

    static short ReadTransactionsMenueOption()
    {
        cout << setw(30) << left << "" << "Choose what do you want to do? [1 to 4]? ";
        short Choice = clsInputValidate::ReadIntNumberBetween(1, 4, "Enter Number between 1 to 4? ");
        return Choice;
    }

    static void _GoBackToTransactionsMenue()
    {
        cout << "\n\nPress any key to go back to Transactions Menue...";
        system("pause>0");
        ShowTransactionsMenue();

    }


    static void _ShowDepositScreen()
    {
        clsDepositeScreen::ShowDepositeScreen();
    }

    static void _ShowWithdrawScreen()
    {
        clsWithdrawScreen::ShowWithdrawScreen();
    }

    static void _ShowTotalBalancesScreen()
    {
        clsTotalBalancesScreen::ShowTotalBalances();
    }


    static void _PerformTransactionsMenueOption(enTransactionsMenueOptions TransactionsMenueOption)
    {
        switch (TransactionsMenueOption)
        {
        case enTransactionsMenueOptions::eDeposit:
        {
            system("cls");
            _ShowDepositScreen();
            _GoBackToTransactionsMenue();
            break;
        }

        case enTransactionsMenueOptions::eWithdraw:
        {
            system("cls");
            _ShowWithdrawScreen();
            _GoBackToTransactionsMenue();
            break;
        }

        case enTransactionsMenueOptions::eShowTotalBalance:
        {
            system("cls");
            _ShowTotalBalancesScreen();
            _GoBackToTransactionsMenue();
            break;
        }


        case enTransactionsMenueOptions::eShowMainMenue:
        {
            //do nothing here the main screen will handle it :-) ;
        }
        }


    }

public:


    static void ShowTransactionsMenue()
    {
        if (!CheckPermissionRights(clsUser::enPermissions::pTranactions)) {
            return;
        }

        system("cls");
        _DrawScreenHeader("\t\tTransactions Screen");

        cout << setw(30) << left << "" << "===========================================\n";
        cout << setw(30) << left << "" << "\t\tTransactions Menue\n";
        cout << setw(30) << left << "" << "===========================================\n";
        cout << setw(30) << left << "" << "\t[1] Deposit.\n";
        cout << setw(30) << left << "" << "\t[2] Withdraw.\n";
        cout << setw(30) << left << "" << "\t[3] Total Balances.\n";
        cout << setw(30) << left << "" << "\t[4] Main Menue.\n";
        cout << setw(30) << left << "" << "===========================================\n";

        _PerformTransactionsMenueOption((enTransactionsMenueOptions)ReadTransactionsMenueOption());
    }

};


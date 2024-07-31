#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsBankClient.h"

class clsTotalBalancesScreen : protected clsScreen
{
private:
    static void printBalanceInfo(clsBankClient client) {
        cout << "| " << setw(30) << left << client.getAccountNumber();
        cout << " | " << setw(30) << left << client.getFullName();
        cout << " | " << setw(30) << left << client.getAccountBalance();
        cout << endl;
    }

public:
   static void ShowTotalBalances() {

        vector<clsBankClient> vClientsObj = clsBankClient::getCLientsObj();

       string title = "\t\tTotal Balances Screen";
       string subtitle = "(" + to_string(vClientsObj.size()) + ") Client(s)";

       _DrawScreenHeader(title, subtitle);

        cout << "-----------------------------------------------------------------------------------------------\n";
        cout << "| " << setw(30) << left << "Account Number";
        cout << " | " << setw(30) << left << "Client Names";
        cout << " | " << setw(30) << left << "Balance ";
        cout << "\n-----------------------------------------------------------------------------------------------\n";

        if (vClientsObj.size() == 0) {
            cout << "\n\t\tThere is No Balances To Show . \n";
        }
        else {
            for (clsBankClient& c : vClientsObj) {
                printBalanceInfo(c);
            }
        }

        cout << "\n-----------------------------------------------------------------------------------------------\n";

        double TotalBalances = clsBankClient::totalBalances();

        cout << "\n\t\t\t\tTotal Balances = " << TotalBalances << endl;
        cout << "\n\t\t\t\t( " << clsString::TrimRight(clsUtil::NumberToText(TotalBalances)) << " ) \n";


    }
};


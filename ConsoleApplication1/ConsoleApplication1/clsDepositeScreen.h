#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsBankClient.h"


class clsDepositeScreen : protected clsScreen
{
private:

    static void Print(clsBankClient client) {
        cout << "\nClient Card : ";
        cout << "\n------------------------------";
        cout << "\nFirstName       : " << client.getFirstName();
        cout << "\nLastName        : " << client.getLastName();
        cout << "\nFullName        : " << client.getFirstName() + " " + client.getLastName();
        cout << "\nEmail           : " << client.email;
        cout << "\nPhone           : " << client.phone;
        cout << "\nAccountNumber   : " << client.getAccountNumber();
        cout << "\nPinCode         : " << client.pincode;
        cout << "\nAccountBalance  : " << client.accountBalance;
        cout << "\n------------------------------\n";
    }

    static string _ReadAccountNumber() {
        string accountNumber = "";
        cout << "\nEnter the accountNumber of client : ";
        accountNumber = clsInputValidate::ReadString();
        return accountNumber;
    }


public:


    static void ShowDepositeScreen() {

        _DrawScreenHeader("\t\tDeposite Screen");
    
        string AccountNumber = _ReadAccountNumber();

        while (!clsBankClient::IsClientExist(AccountNumber)) {
            cout << "\nClient With [" << AccountNumber << "] Is Not Founded , Enter another one : ";
            AccountNumber = _ReadAccountNumber();

        }

        clsBankClient client = clsBankClient::Find(AccountNumber);
        Print(client);

        cout << "\nPlease Enter deposite amount ?  ";
        double amount = clsInputValidate::ReadDblNumber();

        char answer;
        cout << "Are you sure you want to perfrom this transaction ? y/n  ";
        cin >> answer;
        if (answer == 'y' || answer == 'Y') {

            client.Deposite(amount);
            cout << "\nOperation Successfully ! \n";
            cout << "\nNew Balance Is : " << client.accountBalance << endl;

        }
        else {
            cout << "\nOperation was cancelled. \n";
        }



    }

};


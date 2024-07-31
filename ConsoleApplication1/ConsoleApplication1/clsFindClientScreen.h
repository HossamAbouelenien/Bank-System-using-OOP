#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsBankClient.h"

class clsFindClientScreen : protected clsScreen
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
public:

    static void FindClient() {


        if (!CheckPermissionRights(clsUser::enPermissions::pFindClient)) {
            return;
        }

        _DrawScreenHeader("\t\tFinding Clients Screen");

        string accountNumber = "";
        cout << "\nEnter the accountNumber of client : ";
        accountNumber = clsInputValidate::ReadString();
        while (!clsBankClient::IsClientExist(accountNumber)) {
            cout << "\nclient don't exist, Please Enter the accountNumber of client : ";
            accountNumber = clsInputValidate::ReadString();
        }
        clsBankClient client = clsBankClient::Find(accountNumber);

        if (!client.IsEmpty()) {
            cout << "The Client Has been Founded (^_^)" << endl;
        }
        else {
            cout << "The Client Has NOt been Founded (*_*)" << endl;
        }


        Print(client);

       

    }


};


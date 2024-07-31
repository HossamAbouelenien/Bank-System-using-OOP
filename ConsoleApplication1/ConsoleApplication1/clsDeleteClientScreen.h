#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsBankClient.h"

class clsDeleteClientScreen : protected clsScreen
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

  static  void DeleteClients() {

      if (!CheckPermissionRights(clsUser::enPermissions::pDeleteClient)) {
          return;
      }

      clsScreen::_DrawScreenHeader("\t\tDeleting CLients Screen");

        string accountNumber = "";
        cout << "\nEnter the account Number : \n";
        accountNumber = clsInputValidate::ReadString();
        while (!clsBankClient::IsClientExist(accountNumber)) {
            cout << "\naccount Number not exist , enter another one : \n";
            accountNumber = clsInputValidate::ReadString();
        }
        clsBankClient client = clsBankClient::Find(accountNumber);
        Print(client);

        cout << "Are you sure ? you want to delete this ? y / n : ";
        char answer;
        cin >> answer;
        if (answer == 'y' || answer == 'Y') {
            if (client.delet()) {
                cout << "Deleted Done Successfully ! \n";
                Print(client);
            }
            else {
                cout << "you cannot delete this \n";
            }
        }


    }

};


#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsBankClient.h"

class clsUpdatingCLientsScreen : protected clsScreen
{
private:

    static void ReadClientInfo(clsBankClient& client) {
        cout << "\nEnter First Name     : \n";
        client.firstName = clsInputValidate::ReadString();
        cout << "\nEnter Last Name      : \n";
        client.lastName = clsInputValidate::ReadString();
        cout << "\nEnter Your Email     : \n";
        client.email = clsInputValidate::ReadString();
        cout << "\nEnter Your Phone     : \n";
        client.phone = clsInputValidate::ReadString();
        cout << "\nEnter Pin Code       : \n";
        client.pincode = clsInputValidate::ReadString();
        cout << "\nEnter Acc.Balance    : \n";
        client.accountBalance = clsInputValidate::ReadDblNumber();

    }

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


  static void UpdateClients() {


      if (!CheckPermissionRights(clsUser::enPermissions::pUpdateClients)) {
          return;
      }

      _DrawScreenHeader("\t\tUpdating Clients Screen");

        string accountNumber = "";
        cout << "\nEnter the accountNumber of client : ";
        accountNumber = clsInputValidate::ReadString();
        while (!clsBankClient::IsClientExist(accountNumber)) {
            cout << "\nclient don't exist, Please Enter the accountNumber of client : ";
            accountNumber = clsInputValidate::ReadString();
        }
        clsBankClient client = clsBankClient::Find(accountNumber);
        Print(client);

        cout << "\nUpdate client info : \n";
        cout << "\n---------------------\n";

        ReadClientInfo(client);

        clsBankClient::enSaveResults save;
        save = client.save();

        switch (save) {
        case clsBankClient::enSaveResults::svSuccessed: {
            cout << "\nUpdated Done Successfully !\n";
            Print(client);
            break;
        }
        case clsBankClient::enSaveResults::svFailedEmptyObject: {
            cout << "\nError ! , Account was not save because it is empty\n";

            break;
        }
        }


    }

};


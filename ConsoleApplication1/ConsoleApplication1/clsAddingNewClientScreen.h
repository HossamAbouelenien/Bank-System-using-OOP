#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsBankClient.h"

class clsAddingNewClientScreen : protected clsScreen
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

   static void AddNewClient() {

       if (!CheckPermissionRights(clsUser::enPermissions::pAddNewClient)) {
           return;
       }
       string title = "\t\tAdding New Client Screen";
      
       clsScreen::_DrawScreenHeader(title);

        string accountNumber = "";
        cout << "\nEnter the accountNumber of client : ";
        accountNumber = clsInputValidate::ReadString();
        while (clsBankClient::IsClientExist(accountNumber)) {
            cout << "\nAlready Existed , Enter the accountNumber of client : ";
            accountNumber = clsInputValidate::ReadString();
        }

        clsBankClient NewClient = clsBankClient::GetAddNewClientObj(accountNumber);
        ReadClientInfo(NewClient);

        clsBankClient::enSaveResults save;
        save = NewClient.save();

        switch (save) {
        case clsBankClient::enSaveResults::svSuccessed: {
            cout << "\nAdding New Client Successfully !\n";
            Print(NewClient);
            break;
        }
        case clsBankClient::enSaveResults::svFailedEmptyObject: {
            cout << "\nError ! , Account was not added because it is empty\n";

            break;
        }
        case clsBankClient::enSaveResults::svFailedAccountNumberExist: {
            cout << "\nError ! , Account was not added because it is already exist\n";

            break;
        }
        }

    }




};


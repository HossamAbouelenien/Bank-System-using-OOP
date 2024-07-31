#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsBankClient.h"

using namespace std;

class clsClientListScreen : protected clsScreen
{

private:

   static void PrintOneClient(clsBankClient client) {
        cout << "| " << setw(15) << left << client.getAccountNumber();
        cout << " | " << setw(15) << left << client.getFirstName();
        cout << " | " << setw(13) << left << client.getPhone();
        cout << " | " << setw(13) << left << client.getEmail();
        cout << " | " << setw(10) << left << client.getPinCode();
        cout << " | " << setw(10) << left << client.getAccountBalance();
        cout << endl;
    }

public:


    static void ShowCLientsList() {

        if (!CheckPermissionRights(clsUser::enPermissions::pListClients)) {
            return;
        }

        vector<clsBankClient> vClientsObj = clsBankClient::getCLientsObj();
        
        string title = "\t\tClient List Screen";
        string subTitle = "(" + to_string(vClientsObj.size()) + ") Clients(s)";
        clsScreen::_DrawScreenHeader(title, subTitle);

        cout << "\n\t\t\t\t\tCLient List (" << vClientsObj.size() << ") CLient(s)\n";
        cout << "-----------------------------------------------------------------------------------------------\n";
        cout << "| " << setw(15) << left << "Account Number";
        cout << " | " << setw(15) << left << "Client Names";
        cout << " | " << setw(13) << left << "Phones";
        cout << " | " << setw(13) << left << "Email";
        cout << " | " << setw(10) << left << "Pin Code";
        cout << " | " << setw(10) << left << "Balance ";
        cout << "\n-----------------------------------------------------------------------------------------------\n";

        if (vClientsObj.size() == 0) {
            cout << "\n\t\tThere is No CLients To Show . \n";
        }
        else {
            for (clsBankClient& c : vClientsObj) {
                PrintOneClient(c);
            }
        }

        cout << "\n-----------------------------------------------------------------------------------------------\n";

    }



};


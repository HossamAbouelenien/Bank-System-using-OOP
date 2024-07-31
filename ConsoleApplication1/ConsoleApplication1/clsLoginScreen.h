#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsMainScreen.h"
#include "global.h"
#include <fstream>

class clsLoginScreen : protected clsScreen
{

private:
	static bool _Login() {
		bool loginFailed = false;
		short counter = 3;
		string userName, password;
		do {
			if (loginFailed) {
				cout << "\nInvlaid Username/Password!\n";
				counter--;
				cout << "You have " << counter << " Trials to login.\n" << endl;
				if (counter == 0) {
					cout << "You are locked after 3 failed trails." << endl;
					return false;
				}
			}
			cout << "Enter Username? ";
			cin >> userName;

			cout << "Enter Password? ";
			cin >> password;

			CurrentUser = clsUser::Find(userName, password);
			loginFailed = CurrentUser.IsEmpty();

		} while (loginFailed);
		_SaveDataRejesterToFile();
		clsMainScreen::ShowMainMenue();
		return true;
	}

	static string _ConvertObjDataToLine( string delimiter = "#//#") {
		string line = "";
		line += clsDate::GetSystemDateTimeString() + delimiter;
		line += CurrentUser.GetUserName() + delimiter;
		line += CurrentUser.GetPassword() + delimiter;
		line += to_string(CurrentUser.GetPermissions());
		return line;
	}

	static void _SaveDataRejesterToFile() {

		fstream file;

		string line;

		line = _ConvertObjDataToLine();

		file.open("LoginRejester.txt", ios::out | ios::app);
		if (file.is_open()) {

			file << line << endl;
			file.close();

		}
	 }



public:

	static bool ShowLoginScreen() {
		system("cls");
		_DrawScreenHeader("\t\t\tLogin Screen");
		cout << "\n\n";
		return _Login();
	}




};


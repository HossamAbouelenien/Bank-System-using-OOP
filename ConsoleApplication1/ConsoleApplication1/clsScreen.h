#pragma once
#include <iostream>
#include <iomanip>
#include "clsUser.h"
#include "global.h"
#include "clsDate.h"

using namespace std;

class clsScreen
{
protected:
	static void _DrawScreenHeader(string title , string subTitle = "") {
		
		cout <<  setw(30) << left << "" << "--------------------------------------------" << endl;
		cout << "\t\t\t" << title << endl;
		if (subTitle != "") {
			cout << "\t\t\t\t\t" << subTitle << endl;
		}
		cout << setw(30) << left << "" << "--------------------------------------------" << endl;
		cout << setw(30) << left << "" << "User: " << CurrentUser.GetUserName() << endl;
		cout << setw(30) << left << "" << "Date: " << clsDate::DateToString(clsDate()) << endl;
		cout << setw(30) << left << "" << "--------------------------------------------" << endl;

	}


	static bool CheckPermissionRights(clsUser::enPermissions Permission) {

		if (CurrentUser.CheckAccessPermission(Permission)) {
			return true;
		}
		else {
			_DrawScreenHeader("\t\tAccess Denied! Contact your Admin.");
			return false;
		}

	}


};


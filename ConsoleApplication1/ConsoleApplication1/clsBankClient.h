#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>
#include "clsPerson.h"
#include "clsString.h"
#include "clsInputValidate.h"


using namespace std;

class clsBankClient : public clsPerson
{
private:

	enum enMode { EmptyMode = 0, UpdateMode = 1 , AddNewMode = 2};
	enMode _mode;

	string _AccountNumber;
	string _PinCode;
	double _AccountBalance = 0;
	bool _MarkToDeleted = false;


	static clsBankClient _ConvertLineToClientObject(string line, string delimiter = "#//#") {
		vector<string> vClient;
		vClient = clsString::Split(line, delimiter);

		return clsBankClient(enMode::UpdateMode, vClient[0], vClient[1], vClient[2], vClient[3], vClient[4], vClient[5], stod(vClient[6]));

	}

	static clsBankClient _GetEmptyObject() {
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	string _ConvertObjToLine(clsBankClient client , string delimiter = "#//#") {
		string line = "";
		line += client.firstName + delimiter;
		line += client.lastName + delimiter;
		line += client.email + delimiter;
		line += client.phone + delimiter;
		line += client.getAccountNumber() + delimiter;
		line += client.pincode + delimiter;
		line += to_string(client.accountBalance);

		return line;

	}

	void _SaveClientsObjToFile(vector<clsBankClient> vClientsObj) {
		fstream file;
		file.open("ClientsFile.txt", ios::out);
		if (file.is_open()) {
			string line;
			for (clsBankClient c : vClientsObj) {
				if (c.getMarkToDelet() == false) {
					line = _ConvertObjToLine(c);
					file << line << endl;
				}
			}
			file.close();
		}
	}

	static vector<clsBankClient> _LoadObjFromFile() {
		vector<clsBankClient>vClientsObj;
		fstream file;
		file.open("ClientsFile.txt", ios::in);
		if (file.is_open()) {
			string line;
			while (getline(file, line)) {
				clsBankClient client = _ConvertLineToClientObject(line);
				vClientsObj.push_back(client);
			}
			file.close();

		}
		return vClientsObj;
	}


	void _Update() {
		vector<clsBankClient>vClientsObj;
		vClientsObj = _LoadObjFromFile();
		for (clsBankClient& c : vClientsObj) {
			if (c.getAccountNumber() == this->getAccountNumber()) {
				c = *this;
				break;
			}
		}
		_SaveClientsObjToFile(vClientsObj);
	}

	void _AddNewObjToFile(string line) {
		fstream file;
		file.open("ClientsFile.txt", ios::out | ios::app);
		if (file.is_open()) {
			file << line << endl;
			file.close();
		}
	}

	void _AddNew() {
		_AddNewObjToFile(_ConvertObjToLine(*this));
	}

public:

	clsBankClient(enMode mode, string firstName, string lastName, string email, string phone, string accountNumber, string pincode, double accountBalance)
		:clsPerson(firstName, lastName, email, phone) {

		_mode = mode;
		_AccountNumber = accountNumber;
		_PinCode = pincode;
		_AccountBalance = accountBalance;

	}

	bool IsEmpty() {
		return (_mode == enMode::EmptyMode);
	}

	//


	string getAccountNumber() {
		return _AccountNumber;
	}


	//
	void setPinCode(string pincode) {
		_PinCode = pincode;
	}

	string getPinCode() {
		return _PinCode;
	}

	__declspec(property(get = getPinCode, put = setPinCode))string pincode;

	//
	void setAccountBalance(double accountBalance) {
		_AccountBalance = accountBalance;
	}

	double getAccountBalance() {
		return _AccountBalance;
	}

	__declspec(property(get = getAccountBalance, put = setAccountBalance))double accountBalance;

	bool getMarkToDelet() {
		return _MarkToDeleted;
	}

	/*
	void Print() {

		cout << "\n------------------------------";
		cout << "\nFirstName       : " << getFirstName();
		cout << "\nLastName        : " << getLastName();
		cout << "\nFullName        : " << getFirstName() + " " + getLastName();
		cout << "\nEmail           : " << email;
		cout << "\nPhone           : " << phone;
		cout << "\nAccountNumber   : " << getAccountNumber();
		cout << "\nPinCode         : " << pincode;
		cout << "\nAccountBalance  : " << accountBalance;
		cout << "\n------------------------------\n";
	}*/



	static clsBankClient Find(string accountNumber) {

		fstream file;
		file.open("ClientsFile.txt", ios::in);
		if (file.is_open()) {
			string line;
			while (getline(file, line)) {
				clsBankClient client = _ConvertLineToClientObject(line);
				if (client.getAccountNumber() == accountNumber) {
					file.close();
					return client;
				}
			}
			file.close();
		}

		return _GetEmptyObject();

	}



	static clsBankClient Find(string accountNumber, string pinCode) {

		fstream file;
		file.open("ClientsFile.txt", ios::in);
		if (file.is_open()) {
			string line;
			while (getline(file, line)) {
				clsBankClient client = _ConvertLineToClientObject(line);
				if (client.getAccountNumber() == accountNumber && client.pincode == pinCode) {
					file.close();
					return client;
				}
			}
			file.close();
		}

		return _GetEmptyObject();

	}


	static bool IsClientExist(string accountNumber) {
		clsBankClient client = clsBankClient::Find(accountNumber);
		return !(client.IsEmpty());
	}


	enum enSaveResults {svFailedEmptyObject = 0 , svSuccessed = 1 , svFailedAccountNumberExist = 2};

	enSaveResults save() {
		switch (_mode) {

		case enMode::EmptyMode: {
			return enSaveResults::svFailedEmptyObject;
		}
		case enMode::UpdateMode: {
			_Update();
			return enSaveResults::svSuccessed;
		}
		case enMode::AddNewMode: {
			if (clsBankClient::IsClientExist(this->_AccountNumber)) {
				return enSaveResults::svFailedAccountNumberExist;
			}
			else {
				_AddNew();
				this->_mode = enMode::UpdateMode;
				return enSaveResults::svSuccessed;
			}
		}


		}
	}

	 

	static clsBankClient GetAddNewClientObj(string accountNumber) {

		return clsBankClient(enMode::AddNewMode, "", "", "", "", accountNumber, "", 0);


	}

	bool delet() {
		vector<clsBankClient>vClientsObj;
		vClientsObj = _LoadObjFromFile();
		for (clsBankClient& c : vClientsObj) {
			if (c.getAccountNumber() == this->getAccountNumber()) {
				c._MarkToDeleted = true;
				break;
			}
		}
		_SaveClientsObjToFile(vClientsObj);
		*this = _GetEmptyObject();
		return true;

	}

	static	vector <clsBankClient> getCLientsObj() {
		return _LoadObjFromFile();
	}

	static double totalBalances() {
		vector<clsBankClient> vClientsObj;
		vClientsObj = _LoadObjFromFile();
		double totalBalances = 0;
		for (clsBankClient c : vClientsObj) {
			totalBalances += c.getAccountBalance();
		}
		return totalBalances;
	}

	void Deposite(double amount) {
		this->_AccountBalance = _AccountBalance + amount;
		save();
	}
	bool Withdraw(double amount) {
		if (amount > this->_AccountBalance) {
			return false;
		}
		else {
			this->_AccountBalance = _AccountBalance - amount;
			save();
		}
	}


};


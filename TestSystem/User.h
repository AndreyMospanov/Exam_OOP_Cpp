#pragma once
#include<iostream>
#include<string>
#include<vector>

using namespace std;
class User
{
private:
	string login;
	string name[3];
	string password;
	string address;
	string phone;
	vector<string> myResults;
	bool admin;
	string code(string data);
	string decode(string data);	
	void codeUser();	
	void decodeUser();	
	
public:
	User(string loginP, string nameP[3], string passwordP, string adressP, string phoneP, bool adminP = 0) :login{ loginP }, password { passwordP }, address{ adressP }, phone{ phoneP }, admin{adminP}
	{
		for (size_t i = 0; i < 3; i++)
		{
			name[i] = nameP[i];
		}
		//if (!adminP) admin = false;
	}

	User() :User("nologin", new string[3]{"nodata", "nodata", "nodata"}, "password", "noaddress", "nophone") {}
	
	string Login()
	{
		return login;
	}

	string Login(string newLogin)
	{
		login = newLogin;
	}

	string Name()
	{
		return name[0] + " " + name[1] + " " + name[2];
	}

	bool Admin()
	{
		return admin;
	}

	void Modify(bool create);
	void SetPassword(bool create);
	bool CheckPassword(string input);
	void ShowResults();
	void SaveResults();
	void AddResults(string data);

	friend ostream& operator << (ostream& out, User& user)
	{
		user.codeUser();
		out << user.login << endl;
		for (size_t i = 0; i < 3; i++)
		{
			out << user.name[i] << endl;
		}
		out << user.password << endl;
		out << user.address << endl;
		out << user.phone << endl;
		out << (int)user.admin<< endl;
		out << user.myResults.size() << endl;
		for (size_t i = 0; i < user.myResults.size(); i++)
		{
			out << user.myResults[i] << endl;
		}
		return out;
	}

	friend istream& operator >> (istream& in, User& user)
	{	
		string temp = "0";
		int length;
		getline(in, user.login);
		for (size_t i = 0; i < 3; i++)
		{
			getline(in, user.name[i]);			 
		}
		getline(in, user.password);		 
		getline(in, user.address);		 
		getline(in, user.phone);
		getline(in, temp);
		user.admin = (bool)(stoi(temp));		
		getline(in, temp);
		length = stoi(temp);
		for (size_t i = 0; i < length; i++)
		{
			getline(in, temp);
			user.myResults.push_back(temp);
		}
		user.decodeUser();
		return in;
	}
};


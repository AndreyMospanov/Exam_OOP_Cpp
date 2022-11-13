#include "User.h"
#include <fstream>

string User::code(string data)
{
	int* code = new int[data.size()];
	string result;
	for (size_t i = 0; i < data.size(); i++)
	{
		char c = data[i];
		code[i] = c;
	}
	for (size_t i = 0; i < data.size(); i++)
	{
		result += to_string(code[i]) + " ";
		
	}	
	return result;
}

string User::decode(string data)
{
	string temp;
	string decode;
	for (size_t i = 0; i < data.size(); i++)
	{
		if (data[i] != ' ')
		{
			temp += data[i];
		}
		else
		{
			decode += (char)(stoi(temp));
			temp = "";
		}
	}
	return decode;
}

void User::codeUser()
{	
	login = code(login);
	for (size_t i = 0; i < 3; i++)
	{
		name[i] = code(name[i]);
	}
	
	password = code(password);
	address = code(address);
	phone = code(phone);
}

void User::decodeUser()
{
	login = decode(login);
	for (size_t i = 0; i < 3; i++)
	{
		name[i] = decode(name[i]);
	}

	password = decode(password);
	address = decode(address);
	phone = decode(phone);
}

void User::SetPassword(bool create)
{
	try
	{
		string temp;
		string newpass;
		if (create)
		{
			cout << "¬ведите пароль\n";
			cin >> temp;
		}
		else
		{
			cout << "—мена парол€. ¬ведите старый пароль:\n";
			cin >> temp;
			if (temp == password)
			{
				cout << "¬ведите новый пароль\n";
				cin >> temp;				
			}
			else
			{
				throw "пароль неверный!\n";
			}				
		}
		cout << "ѕовторите пароль\n";
		cin >> newpass;
		if (temp != newpass)
		{
			throw "ѕароли не совпадают!\n";
		}			
		else
		{
			password = newpass;
			cout << "пароль изменЄн\n";
		}
	}
	catch (const char* msg)
	{	
		cout << "ќшибка: ";
		cerr << msg << " попробуйте заново\n";
		SetPassword(create);
	}
}

bool User::CheckPassword(string input)
{
	if (input == password)
	{
		return true;
	}
	else
		return false;
}

void User::ShowResults()
{
	for (size_t i = 0; i < myResults.size(); i++)
	{
		cout << myResults[i] << endl;
	}
	system("pause");
	system("cls");
}

void User::SaveResults()
{
	ofstream out;
	string fileName;
	cout << "¬ведите им€ файла куда сохранить результаты\n";
	cin >> fileName;
	out.open(fileName);
	if (out.is_open())
	{
		for (size_t i = 0; i < myResults.size(); i++)
		{
			out << myResults[i] << endl;
		}
	}
	out.close();
}

void User::AddResults(string data)
{
	myResults.push_back(data);
}

void User::Modify(bool create)//create = true - заводим нового пользовател€. false - измен€ем существующего 
{
	string temp;
	if (create)
	{
		cout << "¬ведите логин\n";
		cin >> login;
	}	
	SetPassword(create);
	cout << "¬ведите фамилию: ";
	cin >> name[0];
	cout << "¬ведите им€: ";
	cin >> name[1];
	cout << "¬ведите отчество: ";
	cin >> name[2];
	cout << "¬ведите адрес: ";
	cin >> address;
	cout << "¬ведите телефон: ";
	cin >> phone;	
}


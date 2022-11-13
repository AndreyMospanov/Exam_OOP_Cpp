/*Создать систему управления персональными финансами*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <Windows.h>
#include "Expence.h"
#include "Wallet.h"
using namespace std;

static struct categories
{
    int size = 9;
    string list[9]{ "Продукты", "Платежи, комиссии", "Одежда, техника", "Развлечения", "Кафе", "Кредит", "Проезд", "Зарплата", "Корректировка" };
};

string mainFile = "main.txt";

Wallet LoadWallet(string path)//загрузка отдельной карты с отдельного файла
{    
    ifstream in;
    in.open(path);
    Expence temp;
    Wallet tempW(categories().size, categories().list);
    if (in.is_open())
    {           
        while (in >> temp)
        { 
            tempW.Add(temp);            
        }
    }
    in.close();
    return tempW;
}

void Load(vector<Wallet>& myWallets, string mainFile)//загрузка всех кошельков при помощи главного файла
{    
    ifstream input;
    ofstream out;
    string path;
    string name;
    string currency;
    
    input.open(mainFile);
    //проверка файла на существование. Если есть, то считывание названий кошелька из файла
    if (input.bad() == true)
    {
        out.open(mainFile);
        out.close();
        return;
    }
    else
    {
        while (getline(input, name))
        { 
            path = name + ".txt";
            getline(input, currency);
            myWallets.push_back(LoadWallet(path));//метод загрузки трат в кошелёк
            myWallets[myWallets.size() - 1].Name(name);
            myWallets[myWallets.size() - 1].Currency(currency);
        }
        input.close();
    }
}

void Save(vector<Wallet>& myWallets)//сохранение данных в файлы
{
    ofstream mainOut;
    ofstream out;    
    string path;
    mainOut.open(mainFile);
    for (int i = 0; i < myWallets.size(); i++)
    {
        path = myWallets[i].Name() + ".txt";

        if (mainOut.is_open())
        {
            mainOut << myWallets[i].Name() << endl << myWallets[i].Currency() << endl;
        }        
        out.open(path);

        if (out.is_open())
        {
            for (int j = 0; j < myWallets[i].Count(); j++)
            {
                out << myWallets[i][j];
            }
        }
        out.close();
    }
    mainOut.close();
}

void PrintMenu()
{
    cout << "Выберите пункт меню из списка:\n1. Создать кошелёк (карту)\n2. Удалить кошелёк\n3. Добавить доход\n4. Добавить расход\n5. Удалить транзакцию \n6. Показать расходы\n7. Сохранить\n0. Сохранить и выйти\n";
}

void PrintWallets(vector<Wallet>& myWallets)
{
    for (int i = 0; i < myWallets.size(); i++)
    {
        cout << i + 1 << ". " << myWallets[i].Name() << endl << endl;
    }
}

int GetInt(int left, int right)//метод для корректного ввода целых чисел
{
    int result;
    string input;
    try
    {
        cout << "введите значение:\n";
        
        cin >> input;
        for (size_t i = 0; i < input.size(); i++)
        {
            int temp = (int)(input[i]);
            if (temp < 48 || temp >57)
                throw input;
        }
        result = stoi(input);
        if (result < left || result > right)
            throw result;
        return result;
    }    
    catch (int)
    {
        cerr << "Ошибка. Число за пределами допустимых значений! ";        
        GetInt(left, right);
    }
    catch (string)
    {
        cerr << "Ошибка. Значение не является числом! ";
        GetInt(left, right);
    }
}

Expence newExp(bool income)//создание новой транзакции
{
    string name;
    float value;
    int catNum;
    int choice;
    int date[3];    
    int catSize = 9;
    SYSTEMTIME today;

    cin.ignore(1024, '\n');
    cout << "Введите название транзакции\n";
    getline(cin, name);

    cout << "Введите номер категории\n";
    for (int i = 0; i < categories().size; i++)
    {
        cout << i + 1 << ". " << categories().list[i] << endl;
    }
    catNum = GetInt(1, catSize);
    catNum--;

    cout << "Введите сумму транзакции\n";
     value = GetInt(0, 2147483647);

     if (!income)
         value *= -1;

    cout << "Введите дату\n";
    cout << "1. Сегодня \n2. Другая\n";
    choice = GetInt(1, 2);
    GetLocalTime(&today);
    //задаём дату
    switch (choice)
    {
    case 1:
    {       
        date[0] = today.wYear;
        date[1] = today.wMonth;
        date[2] = today.wDay;        
        break;
    }    
    case 2:
    {
        int year;
        int month;
        int day;
        cout << "Введите год: \n";
        year = GetInt(1900, 2100);
        cout << "Введите месяц: \n";
        month = GetInt(1, 12);
        cout << "Введите число: \n";
        day = GetInt(1, 31);
        date[0] = year;
        date[1] = month;
        date[2] = day;
        break;
    }
    default:
        break;
    }

    return Expence(name, value, categories().list[catNum], date);
}

void ShowExpTime(int index, int monYear, vector<Wallet>& myWallets)
{
    map <string, float> exp;
    map <string, float>::iterator it;
    for (size_t i = 0; i < categories().size; i++)
    {
        exp.insert(make_pair(categories().list[i], 0.0f));
    }
    for (size_t i = 0; i < myWallets.size(); i++)
    {
        for (size_t j = 0; j < myWallets[i].Count(); j++)
        {
            if (myWallets[i][j].date(monYear) == index)
            {
                exp[myWallets[i][j].category()] += myWallets[i][j].value();
            }
        }
    }

    for (it = exp.begin(); it != exp.end(); it++)
    {
        cout << it->first << ": " << it->second << endl;
    }
} 

void Show(int choice, vector<Wallet>& myWallets)
{
    switch (choice)
    {
    case 1:
    {
        for (int i = 0; i < myWallets.size(); i++)
        {
            cout << "Кошелёк " << myWallets[i].Name() << ". Доступные средства: " << myWallets[i].Value() << myWallets[i].Currency() << endl;
            myWallets[i].ShowExpences();
            cout << endl;
        }
        break;
    }
    case 2:
    {
        int wallet;
        cout << "Выберите кошелёк: \n";
        PrintWallets(myWallets);
        wallet = GetInt(1, myWallets.size());
        wallet--;
        cout << "Кошелёк " << myWallets[wallet].Name() << ". Доступные средства: " << myWallets[wallet].Value() << myWallets[wallet].Currency() << endl;
        myWallets[wallet].ShowExpences();
        cout << endl;
        break;
    }
    case 3:
    {        
        for (size_t k = 0; k < myWallets.size(); k++)
        {
            cout << myWallets[k].Name() << endl;
            for (size_t i = 0; i < categories().size; i++)
            {
                cout << categories().list[i] << ": " << myWallets[k].CatValues(i) << myWallets[k].Currency() << endl;
            }
            cout << endl << endl;
        }
        break;
    }
    case 4:
    {
        int choose;
        int month;
        int year;
        cout << "Выберите отрезок времени, по которому будут сгруппированы траты:\n";
        cout << "1. Месяц\n2. Год\n";
        choose = GetInt(1, 2);
        if (choose == 1)
        {
            cout << "Введите число месяца\n";
            month = GetInt(1, 12);
            cout << "Введите год\n";
            year = GetInt(1900, 2100);
            for (size_t i = 0; i < myWallets.size(); i++)
            {
                cout << "Кошелёк " << myWallets[i].Name() << endl; 
                myWallets[i].ShowExpences(month, year, 1);
                cout << endl;
            }            
        }
        else
        {
            cout << "Введите год\n";
            year = GetInt(1900, 2100);
            for (size_t i = 0; i < myWallets.size(); i++)
            {
                cout << "Кошелёк " << myWallets[i].Name() << endl;
                myWallets[i].ShowExpences(year, year, 0);
                cout << endl;
            }            
        }
    }
    default:
        break;
    }
}

void Action(vector<Wallet>& myWallets, int choice)
{
    int wallet;
    string name;
    string currency;
    
    switch (choice)
    {
    case 0:
    {
        break;
    }
    case 1:
    {
        // Создать кошелёк (карту)
        cout << "Создание кошелька\n";
        cin.ignore(1024, '\n');        
        cout << "Введите название карты (кошелька)\n";
        getline(cin, name);
        cout << "Введите валюту\n";
        cin >> currency;
        myWallets.push_back(Wallet(name, currency, categories().size, categories().list));
        cout << "Кошелёк " << name << " создан\n";        
        break;
    }
    case 2:
    {
        //  Удалить кошелёк
        cout << "Удалить кошелёк\nНажмите 0 для отмены.\n";
        cout << "Выберите кошелёк: \n";
        PrintWallets(myWallets);
        wallet = GetInt(1, myWallets.size());
        if (wallet == 0)
            break;
        wallet--;
        name = myWallets[wallet].Name();
        myWallets.erase(myWallets.begin() + wallet);
        cout << "Кошелёк " << name << " удалён.\n";
        break;
    }
    case 3:
    {
        //  Добавить доход
        cout << "Доход\nНажмите 0 для отмены.\n";
        cout << "Выберите кошелёк: \n";
        PrintWallets(myWallets);
        wallet = GetInt(0, myWallets.size());
        if (wallet == 0)
            break;
        wallet--;
        myWallets[wallet].Add(newExp(true));        
        break;
    }
    case 4:
    {
        // Добавить расход        
        cout << "Расход\nНажмите 0 для отмены.\n";
        cout << "Выберите кошелёк: \n";
        PrintWallets(myWallets);
        wallet = GetInt(1, myWallets.size());
        if (wallet == 0)
            break;
        wallet--;
        myWallets[wallet].Add(newExp(false));
        break;
    }
    case 5:
    {
        //Удалить транзакцию  
        int wChoice;
        cout << "Удаление транзакции\nНажмите 0 для отмены.\nВыберите кошелёк: \n";
        PrintWallets(myWallets);
        wallet = GetInt(0, myWallets.size());
        if (wallet == 0)
            break;
        wallet--;        
        myWallets[wallet].ShowExpences();
        cout << "Выберите трату. Введите её номер\n";
        wChoice = GetInt(1, myWallets[wallet].Count());        
        wChoice = myWallets[wallet].Count() - wChoice;//это действие производим потому что отображение трат на экране происходит в обратном порядке
        myWallets[wallet].Delete(wChoice);
        cout << "успешное удаление\n";
        myWallets[wallet].ShowExpences();
        break;
    }
    case 6:
    {
        int choiceS;
        cout << "1. Показать все \n2. Показать по отдельному кошельку\n3. Показать по категориям\n4. Показать за определённое время\n";
        choiceS = GetInt(1, 4);
        Show(choiceS, myWallets);
        break;
    }
    case 7:
    {
        Save(myWallets);
        cout << "сохранено\n";
        break;
    }
    default:
        break;
    }
}

int main()
{
    setlocale(0, "");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);    
    vector<Wallet> myWallets;
    int choice = 0;
    int menuCount = 7;// количество пунктов меню    

    Load(myWallets, mainFile);
    //меню    
    do
    {
        PrintMenu();
        choice = GetInt(0, menuCount);
        system("cls");
        Action(myWallets, choice);
        system("pause");
        system("cls");
    } while (choice != 0);
    Save(myWallets);
    cout << "Программа завершена\n";
}

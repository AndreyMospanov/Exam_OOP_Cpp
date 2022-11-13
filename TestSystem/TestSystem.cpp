#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <Windows.h>
#include "User.h"
#include "Test.h"
#include "TestBlock.h"

using namespace std;

static struct dat
{  
    string dir = "TestSystem_data\\";
    string usersPath = "users.txt";
    string testPath = "tests.txt";
};

void Save(vector<TestBlock>& tests)
{
    ofstream out;    
    out.open(dat().testPath);
    if (out.is_open())
    {
        for (size_t i = 0; i < tests.size(); i++)
        {
            out << tests[i];
        }
    }
    out.close();
}

void Save(vector<User>& users)
{
    ofstream out;
    out.open(dat().usersPath);
    if (out.is_open())
    {
        for (size_t i = 0; i < users.size(); i++)
        {
            out << users[i];
        }
    }
    out.close();    
}

void Load(vector<TestBlock>& tests)
{
    ifstream in;
    TestBlock tempTest;
    in.open(dat().testPath);
    if (!in.bad())
    {
        while (in >> tempTest)
        {
            tests.push_back(tempTest);
        }
    }
    in.close();
}

void Load(vector<User>& users)
{    
    ifstream in;
    User temp;
    in.open(dat().usersPath);
    if (!in.bad())
    {
        if (in.is_open())
        {
            while (in >> temp)
            {
                users.push_back(temp);
            }
        }
    }
    in.close();      
}

void CreateUser(vector<User>& users, bool admin)
{    
    if (admin)
    {
        User user("", new string[3]{ "", "", "" }, "", "", "", true);
        cout << "Создание учётной записи администратора\n";
        user.Modify(true);
        users.push_back(user);
    }
    else
    {
        User user("", new string[3]{ "", "", "" }, "", "", "", false);
        cout << "Создание учётной записи\n";
        user.Modify(true);
        users.push_back(user);
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

int SignIn(vector<User>& users)
{
    string userLogin;
    string userPassword;
    int choice;
    bool loginExist = false;
    bool passwordCorrect = false;
    try
    {
        cout << "Введите логин\n";
        cin >> userLogin;

        for (size_t i = 0; i < users.size(); i++)
        {
            if (userLogin == users[i].Login())
            {
                loginExist = true;
                cout << "Введите пароль\n";
                cin >> userPassword;
                passwordCorrect = users[i].CheckPassword(userPassword);
                if (!passwordCorrect)
                {
                    throw "Неверный пароль!\n";
                }                    
                else
                {
                    system("cls");
                    return i;
                }                    
            }
        }
        if (!loginExist)
            throw "Логин не существует!\n";
    }
    catch (const char* msg) 
    {
        cerr << "Ошибка: " << msg << endl;
        cout << "Попробовать ещё раз?\n1. Да\n2. Нет\n";        
        choice = GetInt(1, 2);
        if (choice == 1)
        {
            system("cls");
            return SignIn(users);
        }                   
        else
        {
            return -1;
        }                
    }    
}

int Authorize(vector<User>& users)//возвращает номер пользователя в базе
{
    int choice;
    cout << "1. Создать новую учётную запись\n2. Авторизоваться\n";
    choice = GetInt(1, 2);
    if (choice == 1)
    {
        CreateUser(users, false);
        system("cls");
        cout << "Вы авторизовались как " << users[users.size() - 1].Name() << endl;
        return users.size() - 1;
    }
    return SignIn(users);
}

void SubMenu(vector<User>& users, int actor, int choiceAction)//управление пользователями
{
    int userChoice;
    if (choiceAction > 1)
    {
        cout << "Выберите пользователя из списка : \n";
        for (size_t i = 0; i < users.size(); i++)
        {
            cout << i + 1 << "). " << users[i].Login() << endl;
        }
    }
    
    userChoice = GetInt(0, users.size());
    userChoice--;
    switch (choiceAction)
    {
    case 0:
    {
        break;
    }
    case 1:
    {
        CreateUser(users, false);
        break;
    }
    case 2:
    {
        users[userChoice].Modify(true);
        break;
    }
    case 3:
    {
        cout << users[userChoice].Login() << " удалён\n";
        users.erase(users.begin() + userChoice);
        break;
    }
    case 4:
    {
        users[userChoice].ShowResults();
        break;
    }
    default:
        break;
    }
    system("pause");
    system("cls");
}

void SubMenu(vector<TestBlock>& tests, int choiceAction)//управление тестами
{
    switch (choiceAction)
    {  
    case 0:
    {
        break;
    }
    case 1://Создать новое тестирование
    {
        TestBlock temp;
        temp.CreateTestBlock();
        tests.push_back(temp);
        break;
    }
    case 2://добавить вопросы в существующий тест
    {
        int choice;
        cout << "Выберите тест для добавления вопросов\n";
        for (size_t i = 0; i < tests.size(); i++)
        {
            cout << i + 1 << " " << tests[i].Name();
        }
        choice = GetInt(1, tests.size());
        choice--;
        tests[choice].CreateTestBlock(false);
        break;
    }
    case 3://Удалить тестирование
    {
        int choice;
        cout << "Выберите тест для удаления\n";
        for (size_t i = 0; i < tests.size(); i++)
        {
            cout << i + 1 << " " << tests[i].Name();
        }
        choice = GetInt(1, tests.size());
        choice--;
        tests.erase(tests.begin() + choice);
        cout << "Тест удалён\n";
        break;
    }
    case 4:
    {
        int choice;
        cout << "Выберите тест, для просмотра результатов\n";
        for (size_t i = 0; i < tests.size(); i++)
        {
            cout << i + 1 << " " << tests[i].Name();
        }
        choice = GetInt(1, tests.size());
        choice--;
        tests[choice].GetScore();
        break;
    }
    default:
        break;
    }
    system("pause");
    system("cls");
}

void RunTest(vector<User>& users, int actor, vector<TestBlock>& tests)
{
    int choice;
    cout << "Выберите тест из списка:\n";
    for (size_t i = 0; i < tests.size(); i++)
    {
        cout << i + 1 << "). " << tests[i].Name() << endl;
    }
    choice = GetInt(1, tests.size());
    choice--;
    users[actor].AddResults(tests[choice].RunTestBlock(users[actor].Name()));
}

void ShowMenu(vector<User>& users, int actor)
{
    cout << "Выберите пункт меню\n0. Выйти\n1. Изменить профиль\n2. Пройти тест\n3. Просмотреть результаты тестов\n4. Сохранить результаты в файл\n";
    if (users[actor].Admin())
    {
        cout << "5. Управление пользователями\n6. Управление тестами\n";
    }
}

void RunMenu(vector<User>& users, int actor, int choice, vector<TestBlock>& tests)//механизм навигации по пунктам меню
{
    switch (choice)
    {
    case 0://выход
    {
        break;
    }
    case 1://Изменить профиль
    {
        users[actor].Modify(false);
        break;
    }
    case 2://пройти тест
    {
        RunTest(users, actor, tests);
        break;
    }
    case 3://Посмотреть результаты тестов
    {
        users[actor].ShowResults();
        break;
    }
    case 4://Сохранить результаты тестов
    {
        users[actor].SaveResults();
        break;
    }
    case 5://Управление пользователями
    {        
        int choiceAction;
        do
        {
            cout << "0. Выход\n1. Создать пользователя\n2. Изменить данные пользователя\n3. Удалить пользователя\n4. Просмотреть результаты тестов пользователя\n";
            choiceAction = GetInt(0, 4);
            SubMenu(users, actor, choiceAction);
        } while (choiceAction != 0);
        break;
    }
    case 6://Управление тестами
    {
        int choiceAction;
        do
        {
            cout << "0. Выход\n1. Создать новое тестирование\n2. Добавить вопросы в существующий тест\n3. Удалить тестирование\n4. Просмотреть результаты теста\n";
            choiceAction = GetInt(0, 4);
            SubMenu(tests, choiceAction);
        } while (choiceAction != 0);
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
    vector<User> users;
    vector<TestBlock> tests;
    int actor;//индекс активного пользователя в юзерс 
    int choice = 0;
    Load(users);
    Load(tests);
    if (users.size() == 0)
    {
        CreateUser(users, true);
    }
    actor = Authorize(users);
    if (actor == -1)
    {
        cout << "Авторизация не произведена. Выход из приложения\n";
        exit(0);
    }        
    do
    {
        ShowMenu(users, actor);
        choice = GetInt(0, 6);
        system("cls");
        RunMenu(users, actor, choice, tests);
        system("cls");
    } while (choice != 0);
    
    Save(tests);
    Save(users);
}
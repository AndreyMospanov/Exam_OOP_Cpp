#include "Test.h"

int Test::GetInt(int left, int right)//метод для корректного ввода целых чисел
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

void Test::CreateTest()
{    
    cin.ignore(1024, '\n');
	cout << "Запишите вопрос\n";    
	getline(cin, question);
	for (size_t i = 0; i < 4; i++)
	{
		cout << "Запишите вариант ответа №" << i + 1 << endl;
		getline(cin, variants[i]);
	}
	cout << "Запишите номер правильного ответа\n";
    rightAnsw = GetInt(1, 4);
	cout << "Запишите стоимость ответа в баллах\n";
	cost = GetInt(0,100);
}

int Test::RunTest()//возвращает количество баллов за правильный ответ или 0
{
    int studAnswer;
    cout << "Вопрос:\n" << question << endl;
    cout << "Варианты:\n";
    for (size_t i = 0; i < 4; i++)
    {
        cout << i + 1 << "). " << variants[i] << endl;
    }
    cout << "Ваш ответ. ";
    studAnswer = GetInt(1, 4);

    if (studAnswer == rightAnsw)
        return cost;
    else
        return 0;
}
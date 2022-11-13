#include "Wallet.h"

void Wallet::Add(Expence exp)
{
	expences.insert(make_pair(exp.id(), exp));
	value += exp.value();

	for (int i = 0; i < 9; i++)
	{
		if (exp.category() == categories[i])
		{
			catValues[i] += exp.value();
			break;
		}
	}
}

void Wallet::Delete(int index)
{
	multimap <int, Expence>::iterator it = expences.begin();
	advance(it, index);// присваиваем итератору нужный индекс
	value -= it->second.value(); //убираем расход из общей суммы
	expences.erase(it);
}

void Wallet::ShowExpences()
{
	multimap<int, Expence> ::iterator it;
	int index = 1;
	if (expences.size() > 0)
	{
		for (it = --expences.end(); it != --expences.begin(); it--)
		{
			cout << index++ << ". ";
			it->second.Print();
		}
	}
	else
		cout << "ѕусто\n";
}

void Wallet::ShowExpences(int index, int year, int selector) //selector = 1 - показываем мес€ц, 0 - год
{
	map <string, float> exp;
	map <string, float>::iterator it;
	multimap <int, Expence>::iterator itExp;
	for (size_t i = 0; i < categories.size(); i++)
	{
		exp.insert(make_pair(categories[i], 0.0f));
	}

	for (itExp = expences.begin(); itExp != expences.end(); itExp++)
	{
		if (itExp->second.date(0) == year)
		{
			if (itExp->second.date(selector) == index)
			{
				exp[itExp->second.category()] += itExp->second.value();
			}
		}
	}

	for (it = exp.begin(); it != exp.end(); it++)
	{
		cout << it->first << ": " << it->second << " " << currency << endl;
	}
}
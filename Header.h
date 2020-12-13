#pragma once

#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
#include <string>


enum types { intNumber = 0, string, floatNumber };

class column
{
private:
	char* columnName;
	int length;
	int* intValues = nullptr;
	char** charValues = nullptr;
	float* floatValues = nullptr;
	types type;

public:
	column()
	{
		columnName = nullptr;
		length = 0;
	}
	column(char* columnName)
	{
		this->columnName = new char[strlen(columnName) + 1];
		strcpy_s(this->columnName, strlen(columnName) + 1, columnName);
		length = 0;
	}
	column(char* columnName, types type, int length, int value) :column(columnName)
	{
		this->type = type;
		this->length = length;
		setValue(value);
	}
	column(char* columnName, types type, int length, float value) :column(columnName)
	{
		this->type = type;
		this->length = length;
		setValue(value);
	}
	column(char* columnName, types type, int length, char* value) :column(columnName)
	{
		this->type = type;
		this->length = length;
		setValue(value);
	}

	column(const column& c)
	{
		if (type == 0)
			column(c.columnName, c.type, c.length, 0);
		if (type == 1)
		{
			char* x = nullptr;
			column(c.columnName, c.type, c.length, x);
		}
		if (type == 2)
			column(c.columnName, c.type, c.length, float(0));
	}

	void setValue(int value)
	{
		intValues = new int[length];
		for (int i = 0; i < length; i++)
		{
			intValues[i] = value;
		}
	}
	void setValue(float value)
	{
		floatValues = new float[length];
		for (int i = 0; i < length; i++)
		{
			floatValues[i] = value;
		}
	}
	void setValue(char* value)
	{
		charValues = new char* [length];
		for (int i = 0; i < length; i++)
		{
			charValues[i] = new char(strlen(value) + 1);
			strcpy_s(charValues[i], strlen(value) + 1, value);
		}
	}
	int getInt(int index)
	{
		return intValues[index];
	}
	char* getString(int index)
	{
		return charValues[index];
	}
	float getFloat(int index)
	{
		return floatValues[index];
	}
	int getLength()
	{
		return length;
	}
	char* getColumnName()
	{
		return columnName;
	}
	types getType()
	{
		return type;
	}

	column operator=(column c)
	{
		length = c.length;
		columnName = new char[strlen(c.columnName) + 1];
		strcpy_s(columnName, strlen(c.columnName) + 1, c.columnName);
		if (intValues != nullptr)
		{
			intValues = new int[c.length];
			for (int i = 0; i < c.length; i++)
			{
				intValues[i] = c.intValues[i];
			}
		}
		if (floatValues != nullptr)
		{
			floatValues = new float[c.length];
			for (int i = 0; i < length; i++)
			{
				floatValues[i] = c.floatValues[i];
			}
		}
		if (charValues != nullptr)
		{
			charValues = new char* [length];
			for (int i = 0; i < length; i++)
			{
				charValues[i] = new char(strlen(c.charValues[i]) + 1);
				strcpy_s(charValues[i], strlen(c.charValues[i]) + 1, c.charValues[i]);
			}
		}
		return*this;
	}
};


class table
{
private:
	char* tableName;
	int nbOfColumns;
	column* columns;
public:
	table() :nbOfColumns(0)
	{
		tableName = nullptr;
		columns = nullptr;
	}
	table(char* tableName) :nbOfColumns(0)
	{
		this->tableName = new char[strlen(tableName) + 1];
		strcpy_s(this->tableName, strlen(tableName) + 1, tableName);
	}
	table(char* tableName, int nbOfColumns, char** columnNames)
	{}

	void addColumn(char* columnName, types type)
	{
		nbOfColumns++;
		column* c = columns;
		columns = new column[nbOfColumns];
		for (int i = 0; i < nbOfColumns - 1; i++)
		{
			columns[i] = c[i];
		}
		if (type == 0)
			columns[nbOfColumns - 1] = column(columnName, type, 5, 1);
		else if (type == 1)
		{
			char* x = nullptr;
			columns[nbOfColumns - 1] = column(columnName, type, 5, x);
		}
		else if (type == 2)
		{
			columns[nbOfColumns - 1] = column(columnName, type, 5, float(2));
		}
	}

	friend istream& operator>>(istream& in, table& t);
	friend ostream& operator<<(ostream& out, table t);
};

int lungimeComanda(char* s)
{
	int counter = 0;
	for (int i = 0; i < strlen(s); i++)
	{
		if (s[i] == ' ')
		{
			counter++;
		}
		if (counter == 2)
		{
			return i - 1;
		}
	}
}

bool compara(char* s1, const char* s2)
{
	for (int i = 0; i < strlen(s1) + 1; i++)
	{
		if (s1[i] != s2[i])
			return false;
	}
	return true;
}

//CREATE TABLE angajat (
int numeTabel(char* s, int index)
{
	for (int i = index; i < strlen(s); i++)
	{
		if (s[i] == ' ')
			return i;
	}
}

bool valideaza(char* comanda)
{
	int l = lungimeComanda(comanda);
	char* c = new char[100];
	char* copie = new char[strlen(comanda) + 1];
	strcpy_s(copie, strlen(comanda) + 1, comanda);
	copie[l + 1] = '\0';

	strcpy_s(c, strlen("CREATE TABLE") + 1, "CREATE TABLE\0");

	if (strcmp(copie, c) == 0)
	{
		strcpy_s(copie, strlen(comanda) + 1, comanda);
		copie[strlen(comanda) + 2] = '\0';
		int index = numeTabel(copie, strlen("CREATE TABLE") + 2);
		copie[index] = '\0';
		copie = copie + strlen("CREATE TABLE") + 1;
		if (comanda[strlen("CREATE TABLE") + strlen(copie) + 2] != '(')
		{
			cout << "Eroare";
			return false;
		}
		else
		{
			//cout << 5;
			table t(copie);
			cin >> t;
			cout << endl;
			cout << endl;
			cout << endl;
			cout << t;
		}
		return true;
	}

	strcpy_s(c, strlen("DROP TABLE") + 1, "DROP TABLE\0");

	if (strcmp(copie, c) == 0)
	{
		strcpy_s(copie, strlen(comanda) + 1, comanda);
		copie[strlen(comanda) + 2] = '\0';
		int index = numeTabel(copie, strlen("DROP TABLE") + 2);
		copie[index] = '\0';
		copie = copie + strlen("DROP TABLE") + 1;
		cout << copie;
		if (comanda[strlen("DROP TABLE") + strlen(copie) + 1] != ';')
		{
			cout << "Eroare";
			return false;
		}
		return true;
	}

	strcpy_s(c, strlen("DISPLAY TABLE") + 1, "DISPLAY TABLE\0");

	if (strcmp(copie, c) == 0)
	{
		strcpy_s(copie, strlen(comanda) + 1, comanda);
		copie[strlen(comanda) + 2] = '\0';
		int index = numeTabel(copie, strlen("DISPLAY TABLE") + 2);
		copie[index] = '\0';
		copie = copie + strlen("DISPLAY TABLE") + 1;
		cout << copie;
		if (comanda[strlen("DISPLAY TABLE") + strlen(copie) + 1] != ';')
		{
			cout << "Eroare";
			return false;
		}

		return true;
	}

	strcpy_s(c, strlen("CREATE INDEX") + 1, "CREATE INDEX\0");

	if (strcmp(copie, c) == 0)
	{
		cout << "create index";
		return true;
	}

	strcpy_s(c, strlen("DROP INDEX") + 1, "DROP INDEX\0");

	if (strcmp(copie, c) == 0)
	{
		cout << "drop index";
		return true;
	}

	return false;
}

//template <typename t>



types getType(char* s)
{
	if (strcmp(s, "int") == 0) return types(0);
	if (strcmp(s, "string") == 0) return types(1);
	if (strcmp(s, "float") == 0) return types(2);
}

types getType(std::string s)
{
	if (s == "int") return types(0);
	if (s == "string") return types(1);
	if (s == "float") return types(2);
}

void test()
{
	char* sir = new char[100];
	char* coloana = new char[100];
	char* valoare = new char[100];
	//strcpy_s(sir, strlen("int") + 1, "int\0");
	strcpy_s(sir, strlen("string") + 1, "string\0");
	//strcpy_s(sir, strlen("float") + 1, "float\0");
	strcpy_s(coloana, strlen("coloana1") + 1, "coloana1\0");
	strcpy_s(valoare, strlen("valoare") + 1, "valoare\0");

	//cout<<getType(sir);
	column c(coloana, getType(sir), 10, valoare);

	///c = coloana;

	for (int i = 0; i < c.getLength(); i++)
	{
		cout << c.getString(i) << endl;
	}

}




istream& operator>>(istream& in, table& t)
{
	std::string line;
	std::vector<std::string> nameList;
	std::vector<std::string> typeList;
	while (getline(in, line))
	{
		if (line == ");") break;
		else if (line[line.length() - 1] != ',')
		{
			cout << "eroare";
			break;
		}
		else
		{
			std::string name = line.substr(0, line.find(' '));
			char* tableName = new char[name.length() + 1];
			strcpy_s(tableName, name.length() + 1, name.c_str());
			//cout << tableName;
			std::string type = line.substr(line.find(' ') + 1, line.find(','));
			if (type.find(' ') < type.length() + 1)
			{
				type = type.substr(0, type.find(' '));
			}
			else
			{
				type = type.substr(0, type.find(','));
			}
			//nameList.push_back(tableName);
			//typeList.push_back(type);
			t.addColumn(tableName, getType(type));
		}
	}
	//cout << endl << "rezultat:" << endl;
	/*for (int i = 0; i < nameList.size(); i++)
	{
		int lungime = nameList[i].length();
		char* name = new char[nameList[i].length() + 1];
		strcpy_s(name, nameList[i].length(), nameList[i].c_str());
		char* type = new char[typeList[i].length() + 1];
		strcpy_s(type, typeList[i].length() + 1, typeList[i].c_str());
		t.addColumn(name, getType(type));
	} */
	return in;
}

ostream& operator<<(ostream& out, table t)
{
	cout << t.tableName << endl;
	for (int i = 0; i < t.nbOfColumns; i++)
	{
		cout << t.columns[i].getColumnName() << ' ';
	}
	cout << endl;
	for (int i = 0; i < t.columns[0].getLength(); i++)
		for (int j = 0; j < t.nbOfColumns; j++)
		{
			if (t.columns[j].getType() == 0)
			{
				cout << t.columns[j].getInt(i) << ' ';
			}
			if (t.columns[j].getType() == 1)
			{
				cout << t.columns[j].getString(i) << ' ';
			}
			if (t.columns[j].getType() == 2)
			{
				cout << t.columns[j].getFloat(i) << ' ';
			}
		}
	return out;
}

/*
CREATE TABLE a (
comanda1 int,
comanda2 float,
);
*/

class createTable
{
private:

public:

};




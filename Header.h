#pragma once

#include <cstring>
#include <iostream>
using namespace std;

class createTable
{
private:

public:

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

//CREATE TABLE table_name (

bool valideaza(char* comanda)
{
	int l = lungimeComanda(comanda);
	char* c = new char[100];
	char* copie = new char[strlen(comanda) + 1];
	strcpy_s(copie, strlen(comanda) + 1, comanda);
	copie[l + 1] = '\0';

	strcpy_s(c, strlen("CREATE TABLE") + 1, "CREATE TABLE\0");

	if (strcmp(copie,c) == 0)
	{
		cout << "create";
		return true;
	}

	strcpy_s(c, strlen("DROP TABLE") + 1, "DROP TABLE\0");

	if (strcmp(copie,c) == 0)
	{
		cout << "drop";
		return true;
	}

	strcpy_s(c, strlen("DISPLAY TABLE") + 1, "DISPLAY TABLE\0");

	if (strcmp(copie, c) == 0)
	{
		cout << "display";
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
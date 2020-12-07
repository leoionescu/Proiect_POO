#include <iostream>
#include <cstring>
using namespace std;
#include "Header.h"

int main()
{
    char* sir = new char[100];
    strcpy_s(sir, strlen("CREATE TABLE a") + 1, "CREATE TABLE a\0");
    //strcpy_s(sir, strlen("DROP TABLE a") + 1, "DROP TABLE a\0");
    //strcpy_s(sir, strlen("DISPLAY TABLE a") + 1, "DISPLAY TABLE a\0");
    //strcpy_s(sir, strlen("CREATE INDEX a") + 1, "CREATE INDEX a\0");
    //strcpy_s(sir, strlen("DROP INDEX a") + 1, "DROP INDEX a\0");
    cout << valideaza(sir);
}
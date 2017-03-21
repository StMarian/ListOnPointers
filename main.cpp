#include <stdio.h>
#include <iostream>
#include "ListImpl.h"
using namespace std;

int main()
{
	char** list = 0;
	ListInit(&list);

	cout << "Press\n1 to list your array\n2 to enter and add string to an array\n3 to enter and remove string from array\n4 to get the numbers of strings in array\n5 to enter a string and find index of it in array\nq to quit\n";
	char choise = '0';

	while ((choise = getchar()) != 'q')
	{
		if (choise == '\n')
			continue;

		char* temp_str = (char*)malloc(sizeof(char) * 50);

		switch (choise)
		{
		case '1':
			cout << "listing array:" << endl;
			PrintList(list);
			break;
		case '2':
			cout << "Enter string to be added: ";
			cin >> temp_str;
			break;
		case '3':
			cout << "Enter string to be removed: ";
			cin >> temp_str;
			break;
		case '4':
			cout << "Numbers in string: " << endl;
			break;
		case '5':
			cout << "Enter string to find it's index: ";
			cin >> temp_str;
			break;
		default:
			cout << "Bad input!" << endl;
			break;
		}
	}

	system("pause");
	return 0;
}
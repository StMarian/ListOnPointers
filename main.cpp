#include <stdio.h>
#include "ListImpl.h"

int main()
{
	char** list;
	//ListInit(&list);	 -- someone, explain me why it doesn't work

	int init_size;
	cout << "Enter initial size of a list: ";
	cin >> init_size;
	
	system("cls");

	// ---- allocate memory -----	
	list = reinterpret_cast<char**>(calloc(init_size + 2, sizeof(char*)));
	
	// capacity
	list[0] = reinterpret_cast<char*>(calloc(1, sizeof(int)));
	list[0][0] = init_size;
	
	// size
	list[1] = reinterpret_cast<char*>(calloc(1, sizeof(int)));
	list[1][0] = 0;				

	if (!list == NULL)
	{
		for (int i = 2; i < init_size + 2; i++)
		{
			list[i] = reinterpret_cast<char*>(calloc(32, sizeof(char)));
		}
	}
	else // problem with allocation
	{
		cout << "Memory trouble!\n";
		system("pause");
		exit(-1);
	}
	// ----- end allocate memory -----

	cout << "Press\n1 to list your array\n2 to enter and add string to an array\n3 to enter and remove string from array\n4 to get the numbers of strings in array\n5 to get the capacity of the list\n6 to enter a string and find index of it in array\nq to quit\n";
	
	char choise = '0';
	char* temp_str = (char*)malloc(sizeof(char) * 50);

	while ((choise = getchar()) != 'q')
	{
		if (choise == '\n')
			continue;

		switch (choise)
		{
		case '1':
			cout << "listing array:" << endl;
			PrintList(list);
			break;
		case '2':
			cout << "Enter string to be added: ";
			cin >> temp_str;
			ListAdd(list, temp_str);
			break;
		case '3':
			cout << "Enter string to be removed: ";
			cin >> temp_str;
			ListRemove(list, temp_str);
			break;
		case '4':
			cout << "Number of strings in list: ";
			cout << ListSize(list) << endl;
			break;
		case '5':
			cout << "Capacity of a list: ";
			cout << ListCapacity(list) << endl;
			break;
		case '6':
			cout << "Enter a string to find: ";
			cin >> temp_str;
			cout << "Index: " << ListIndexOf(list, temp_str) << endl;
			break;
		default:
			cout << "Bad input!" << endl;
			break;
		}
	}

	ListDestroy(&list);
	free(temp_str);

	system("pause");
	return 0;
}
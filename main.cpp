#include "ListImpl.h"

void testcase1()
{
	char** list = nullptr;
	ListInitialize(&list);

	for (int i = 0; i < 1024; ++i)
	{
		char buff[8];
		ListAdd(&list, itoa(i, buff, 10));
	}

	PrintList(list);
	ListDestroy(&list);
	system("cls");
}
void testcase2()
{
 	system("pause");
	for (int i = 0; i < 32000; i++)
	{
		// Note: user HAVE TO to set initial value to newly definited object (Scott Meyers, "Effective C++: 55..", part 4)!
		char** list = nullptr;				
		ListInitialize(&list, 256);
		ListInitialize(&list, 256);

		ListDestroy(&list);
	}
}
void SaveStringListToFile(/*const*/ char*** stringList) {}

int main()
{
//	testcase1();
//	testcase2();

	int init_size;
	cout << "Enter initial size of a list: ";
	cin >> init_size;
	system("cls");

	char** list = nullptr;
	ListInitialize(&list, init_size);

	cout << "Press\n1 to list your array\n2 to enter and add string to an array\n3 to enter and remove string from array"
		"\n4 to get the numbers of strings in array\n5 to get the capacity of the list\n6 to enter a string and find index of it in array"
		"\n7 to sort list\n8 to remove duplicates\n9 to enter \"before\" and \"after\" string, and replace all \"before\" by \"after\"\nq to quit\n";
	
	char choise = '0';
	char* temp_str = (char*)malloc(sizeof(char) * 50);

	while ((choise = getchar()) != 'q')
	{
		if (choise == '\n')
			continue;

		switch (choise)
		{
		case '1':
			PrintList(list);	
			break;
		case '2':
			cout << "Enter string to be added:\n";
			cin >> temp_str;		
			ListAdd(&list, temp_str);
			break;
		case '3':
			cout << "Enter string to be removed: ";
			cin >> temp_str;
			ListRemove(list, temp_str);
			break;
		case '4':
			cout << "Number of strings in list: ";
			cout << get_ListSize(list) << endl;
			break;
		case '5':
			cout << "Capacity of a list: ";
			cout << get_ListCapacity(list) << endl;
			break;
		case '6':
			cout << "Enter a string to find: ";
			cin >> temp_str;
			cout << "Index: " << ListIndexOf(list, temp_str) << endl;
			break;
		case '7':
			ListSort(list);
			cout << "Sorted\n";
			break;
		case '8':
			ListRemoveDuplicates(list);
			cout << "Duplicates removed\n";
			break;
		case '9':
		{
			char* temp_after = (char*)malloc(sizeof(char) * 50);

			cout << "Enter a \"before\" string: ";
			cin >> temp_str;
			cout << "Enter a \"after\" string: ";
			cin >> temp_after;

			ListReplaceInStrings(list, temp_str, temp_after);
			cout << "Replaced\n";

			free(temp_after);
			break;
		}
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
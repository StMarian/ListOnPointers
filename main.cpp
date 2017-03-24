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
	ListInitialize(nullptr, -1);
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

int main()
{
	char** test_list = nullptr;
	ListInitialize(&test_list);

//	testcase1();
//	testcase2();

	int init_size;
	std::cout << "Enter initial size of a list: ";
	std::cin >> init_size;
	system("cls");

	char** list = nullptr;
	ListInitialize(&list, init_size);

	std::cout << "Press\n1 to list your array\n2 to enter and add string to an array\n3 to enter and remove string from array"
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
			std::cout << "Enter string to be added:\n";
			std::cin >> temp_str;
			ListAdd(&list, temp_str);
			break;
		case '3':
			std::cout << "Enter string to be removed: ";
			std::cin >> temp_str;
			ListRemove(list, temp_str);
			break;
		case '4':
			std::cout << "Number of strings in list: ";
			std::cout << get_ListSize(list) << std::endl;
			break;
		case '5':
			std::cout << "Capacity of a list: ";
			std::cout << get_ListCapacity(list) << std::endl;
			break;
		case '6':
			std::cout << "Enter a string to find: ";
			std::cin >> temp_str;
			std::cout << "Index: " << ListIndexOf(list, temp_str) << std::endl;
			break;
		case '7':
			ListSort(list);
			std::cout << "Sorted\n";
			break;
		case '8':
			ListRemoveDuplicates(list);
			std::cout << "Duplicates removed\n";
			break;
		case '9':
		{
			char* temp_after = (char*)malloc(sizeof(char) * 50);

			std::cout << "Enter a \"before\" string: ";
			std::cin >> temp_str;
			std::cout << "Enter a \"after\" string: ";
			std::cin >> temp_after;

			ListReplaceInStrings(list, temp_str, temp_after);
			std::cout << "Replaced\n";

			free(temp_after);
			break;
		}
		default:
			Info("Invalid input");
			break;
		}
	}

	ListDestroy(&list);
	free(temp_str);

	system("pause");
	return 0;
}
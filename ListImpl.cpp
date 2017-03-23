#include "ListImpl.h"

#include <stdio.h> // fot printf

/*  TODO - problem
	calls form this:
	char** list;
	ListInit(&list);
*/
void ListInit(char*** list, int length)
{
	// first 2 entries would be capacity and actual size of a list
	*list = reinterpret_cast<char**>(calloc(length + 2, sizeof(char*)));

	*(list)[0] = reinterpret_cast<char*>(calloc(1, sizeof(char)));
	*(list)[1] = reinterpret_cast<char*>(calloc(1, sizeof(char)));	// trouble here
	
	for (int i = 2; i < length + 2; i++)
	{
		*(list)[i] = reinterpret_cast<char*>(calloc(32, sizeof(char)));
	}
}

void ListDestroy(char*** list)
{
	for (int i = 0; i < ListCapacity(*list); i++)
		free(*list[i]);

	free(*list);
	list = nullptr;
}

void PrintList(char** list)
{
	if (ListSize(list) == 0)
	{
		cout << "List is empty!" << endl;
		return;
	}

	cout << "Capacity of a list: " << ListCapacity(list) << "| strings in list: " << ListSize(list) << endl;

	for (int i = 2; i < ListSize(list) + 2; i++)
		printf("String #%d(length: %lu): %s\n", i - 2, strlen(list[i]), list[i]);
} 

// TODO reset capacity
void ReallocateList(char*** list, size_t oldsize, size_t newsize)
{
	*list = reinterpret_cast<char**>(realloc(*list, newsize * sizeof(char**)));
	
	//memset(*list + oldsize, '\0', (oldsize - newsize) * sizeof(char*));

	for (int i = oldsize; i < newsize; i++)
	{
		*list[i] = nullptr;
	}

	if (list == NULL)
	{
		cout << "Memory trouble!\n";
		system("pause");
		exit(-1);
	}
}

// TODO - solve problem
void ListAdd(char** list, char* str)
{
//	if (ListSize(*list) == ListCapacity(*list))
//		ReallocateList(list, ListCapacity(*list), ListCapacity(*list) * 3 / 2 + 1);
	
	// size increased
	list[1][0]++;

	int index = 1 + ListSize(list);

	//memcpy(&list[1 + ListSize(list)], &str, sizeof(str));
	strcpy(list[index], str);
//	char* tmp = "0";
//	char* pmt = "1";
//	memcpy(tmp, pmt, sizeof(pmt));
//	strcpy_s(list[index], sizeof(list[index]), str);

	PrintList(list);
}

// removes first same string from end of the list
void ListRemove(char** list, char* str)
{
	char c_str[100];
	strcpy(c_str, str);

	bool removed = false;

	for (int i = ListSize(list) + 1; i > 1; i--)	
	{
		if (removed)
			break;

		if (!strcmp(list[i], c_str))	// strcmp returns 0 when strings are equal
		{
			list[1][0]--;
			removed = true;

			// left shift by 1 pos. right part of an array
			for (int j = i; j < ListSize(list) + 2; j++)
				strcpy(list[j], list[j + 1]);
		}
	}
}

inline int ListCapacity(char** list)
{
	return list[0][0];
}

inline int ListSize(char** list)
{
	return list[1][0];
}

// counts index exluding first two places in a list
int ListIndexOf(char** list, char* str)
{
	for (int i = 2; i < ListSize(list) + 2; i++)
		if (!strcmp(list[i], str))
			return i - 2;
	
	// if not found
	return -1;
}

void ListRemoveDuplicates(char ** list)
{
	for (int i = 2; i < ListSize(list) + 2; i++)
	{
		for (int j = i + 1; j < ListSize(list) + 2; j++)
		{
			if (!strcmp(list[i], list[j]))
			{
				ListRemove(list, list[j]);
				j--;		// prevents from losing data comparation (it is possible bcs we shift array when deleting)
			}
		}
	}
}

void Swap(char** s1, char** s2)
{
	char* temp = *s1;
	*s1 = *s2;
	*s2 = temp;
}

// Selection sort
void ListSort(char ** list)
{
	int temp_min_index;
	for (int i = 2; i < ListSize(list) + 2; i++)
	{	
		temp_min_index = i;
		for (int j = i + 1; j < ListSize(list) + 2; j++)
		{
			if (strcmp(list[j], list[temp_min_index]) < 0) // the first character that does not match has a lower value in list[i] than in list[j]
			{
				temp_min_index = j;
			}
		}

		// swaps min value and first unsorted value in list
		Swap(&list[i], &list[temp_min_index]);
	}
}

void ListReplaceInStrings(char ** list, char * before, char * after)
{
	for (int i = 2; i < ListSize(list) + 2; i++)
	{
		if (!strcmp(list[i], before))
		{
			strcpy(list[i], after);
		}
	}
}

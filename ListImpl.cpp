#include "ListImpl.h"

#include <stdio.h> // fot printf

void ListInit(char*** list, int length)
{
	// first 2 entries would be capacity and actual size of a list
	*list = reinterpret_cast<char**>(calloc(length + 2, sizeof(char*)));

	// feature
	// actually, it would be better to give list[0] two memory cells, and store 
	// capacity and size in list[0][0] and list[0][1]
	
	// capacity
	(*list)[0] = reinterpret_cast<char*>(calloc(1, sizeof(int)));
	(*list)[0][0] = length;

	// size
	(*list)[1] = reinterpret_cast<char*>(calloc(1, sizeof(int)));
	(*list)[1][0] = 0;
	
	if (!(*list) == NULL)
		for (int i = 2; i < length + 2; i++)
			(*list)[i] = reinterpret_cast<char*>(calloc(STR_MAX_LEN, sizeof(char)));
	else
		MemFailed();
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

void ReallocateList(char*** list, size_t old_cap, size_t new_cap)
{
	int i;
	char** safe;
	safe = reinterpret_cast<char**>(realloc(*list, new_cap * sizeof(char*)));
	if (safe == NULL)
		MemFailed();
	else
		*list = safe;

	for (i = old_cap; i < new_cap; i++)
		(*list)[i] = NULL;
	
	for (i = 0; i < new_cap; i++)
	{
		char* new_ptr = reinterpret_cast<char*>(realloc((*list)[i], new_cap * sizeof(char)));
		
		if (new_ptr == NULL)
			MemFailed();
		else
			(*list)[i] = new_ptr;
	}
	// set up new capacity
	(*list)[0][0] = new_cap;
}

void ListAdd(char*** list, char* str)
{
	if (ListSize(*list) == ListCapacity(*list))
		// each capacity increased by 2 to fit real capacity
		// (Capacity * 3 / 2 + 1) - formula for new capacity value
		ReallocateList(list, ListCapacity(*list) + 2, ListCapacity(*list) * 3 / 2 + 1 + 2);
	
	// size increased
	(*list)[1][0]++;

	int index = 1 + ListSize(*list);
	strcpy((*list)[index], str);
}

// removes first same string from End of the list
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
		if (!strcmp(list[i], before))
			strcpy(list[i], after);
}

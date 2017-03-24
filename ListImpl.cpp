#include "ListImpl.h"

void ListInitialize(char*** list, unsigned int length)
{
	if (*list == nullptr)
	{
		unsigned int memory_block_size = 2 * sizeof(unsigned int) + length * sizeof(char*);

		void* memory = malloc(memory_block_size);

		if (memory == nullptr)
			MemFailed();

		memset(memory, 0, memory_block_size);

		int* capacity = (int*)(memory);
		*capacity = length;

		int* size = (int*)(capacity + 1);
		*size = 0;

		*list = (char**)(capacity + 2);
	}
}

void ListDestroy(char*** list)
{
	if (*list != nullptr)
	{
		void* mem_to_delete = ((unsigned*)(*list)) - 2;
	
		for (int i = 0; i < get_ListSize(*list); i++)
		{
			free(*((*list) + i));
			(*((*list) + i)) = nullptr;
		}

		free(mem_to_delete);

		*list = nullptr;
	}
}

void PrintList(char** const list)
{
	unsigned int size = get_ListSize(list);

	if (size == 0)
	{
		cout << "List is empty!" << endl;
		return;
	}

	cout << "Capacity of a list: " << get_ListCapacity(list) << "| strings in list: " << size << endl;

	for (int i = 0; i < size; i++)
		printf("String #%d(length: %lu): %s\n", i, strlen(list[i]), i[list]);
} 

inline void set_ListCapacity(char*** const list, unsigned int const cap)
{
	unsigned int* cap_ptr = (unsigned*)((*list) - 2);
	*cap_ptr = cap;
}

void ListAdd(char*** list, const char* const str)
{
	if (get_ListSize(*list) == get_ListCapacity(*list))
	{
		// (Capacity * 3 / 2 + 1) - formula for new capacity value
		unsigned int old_capacity = get_ListCapacity(*list);
		unsigned int new_capacity = old_capacity * 3 / 2 + 1;

		void* new_mem_block = (*list) - 2;
		new_mem_block = realloc(new_mem_block, new_capacity * sizeof(char**) + 2 * sizeof(unsigned));

		if (new_mem_block == nullptr)
		{
			MemFailed();
		}
		else
		{
			*list = reinterpret_cast<char**>( ( (unsigned*)(new_mem_block) ) + 2 );			
			memset((*list) + old_capacity, 0, (new_capacity - old_capacity) * sizeof(char*));			
			set_ListCapacity(list, new_capacity);
		}
	}

	// allocate memory for a new string
	(*list)[get_ListSize(*list)] = reinterpret_cast<char*>(malloc(strlen(str) + 1));
	strcpy((*list)[get_ListSize(*list)], str);
	
	// increments size
	++(*((*list) - 1));

}

void ListRemove(char** const list, char* const str)
{
	bool removed = false;

	for (int i = get_ListSize(list) - 1; i >= 0; i--)	
	{
		if (removed)
			break;

		if (!strcmp(list[i], str))	// strcmp returns 0 when strings are equal
		{
			// decrements size
			--(*(list - 1));
			removed = true;

			// left shift by 1 pos. right part of an array
			for (int j = i; j < get_ListSize(list); j++)
				strcpy(list[j], list[j + 1]);
		}
	}
}

inline int get_ListCapacity(char** const list)
{
	return (int)(*(list - 2));
}

inline int get_ListSize(char** const list)
{
	return (int)(*(list - 1));
}

int ListIndexOf(char** const list, char* const str)
{
	for (int i = 0; i < get_ListSize(list); i++)
		if (!strcmp(list[i], str))
			return i;
	
	// if not found
	return -1;
}

void ListRemoveDuplicates(char** const list)
{
	for (int i = 0; i < get_ListSize(list) - 1; i++)
	{
		for (int j = i + 1; j < get_ListSize(list); j++)
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
void ListSort(char** const list)
{
	int temp_min_index;
	for (int i = 0; i < get_ListSize(list); i++)
	{	
		temp_min_index = i;
		for (int j = i + 1; j < get_ListSize(list); j++)
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

void ListReplaceInStrings(char** const list, const char* const before, const char* const after)
{
	for (int i = 0; i < get_ListSize(list); i++)
		if (!strcmp(list[i], before))
			strcpy(list[i], after);
}

#include "MyLibrary.h"

#include <iostream>

bool isUnsignedInteger(string str)
{
	size_t length = str.length();
	for (size_t i = 0; i < length; i++)
	{
		if (!isdigit(str[i]))
			return false;
		else
		{
			if (i == length - 1)
				return true;
		}
	}
	return false;
}

void printArray(unsigned int array[], unsigned int array_size) {
	for (unsigned int i = 0; i < array_size; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;
}

bool YNQuestion() {
	string temp = "";
	while (true)
	{
		cout << "Lua chon cua ban: ";
		getline(cin, temp);
		if (temp.length() == 1)
		{
			switch (temp[0])
			{
			case 'y':
			case 'Y':
				return true;
			case 'n':
			case 'N':
				return false;
			}
		}
		cout << "Lua chon khong hop le: ";
	}
}

void selectionSort(unsigned int* a, unsigned int arr_size)
{
	size_t i_min;
	for (size_t i = 0; i < arr_size - 1; i++)
	{
		i_min = i;
		for (size_t j = i + 1; j < arr_size; j++)
		{
			if (a[j] < a[i_min])
				i_min = j;
		}
		if (i_min != i)
			swap(a[i_min], a[i]);
	}
}

void bubbleSort(unsigned int* a, unsigned int arr_size)
{
	bool have_swap;
	for (size_t i = 0; i < arr_size - 1; i++)
	{
		have_swap = false;
		for (size_t j = 0; j < arr_size - i - 1; j++)
		{
			if (a[j] > a[j + 1])
			{
				swap(a[j], a[j + 1]);
				have_swap = true;
			}
		}
		if (!have_swap)
			break;
	}
}

void swap(unsigned int& a, unsigned int& b) {
	int temp = a;
	a = b;
	b = temp;
}

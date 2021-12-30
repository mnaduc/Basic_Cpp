#ifndef MY_LIBRARY_H_
#define MY_LIBRARY_H_

#include <string>
using namespace std;

/*
	Kiểm tra số nguyên dương và 0
	@param str chuỗi cần kiểm tra
*/
bool isUnsignedInteger(string str);

void printArray(unsigned int[], unsigned int array_size);

/*
	Xử lý lựa chọn yes/no
	@return true(y/Y) or false(n/N)
*/
bool YNQuestion();

void selectionSort(unsigned int* arr, unsigned int arr_size);

void bubbleSort(unsigned int* arr, unsigned int arr_size);

void swap(unsigned int&, unsigned int&);

#endif // !MY_LIBRARY_H_


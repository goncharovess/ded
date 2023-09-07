#include <stdio.h>
#include <stdlib.h>

void PrintData1 (const int data[], size_t sizeX, size_t sizeY){ //первая реализация ф-ии, которая печатает одномерный массив как двумерный с размерами sizeX и sizeY
	for (size_t i = 0; i < sizeX; i++){
		for (size_t j = 0; j < sizeY; j++){
			printf("%d ", *(data + i * sizeY + j));
		}
		printf("\n");
	}
}

const int* newData (const int data[], size_t sizeX, size_t sizeY){ //получаю массив, первые два элемента которого - размеры двумерного массива
	int* data1 = calloc(sizeX * sizeY + 2, sizeof(int)); //предполагаю, что гарантируется, что data представим в виде матрицы, т.е. имеет длину sizeX * sizeY
	*data1 = sizeX;
	*(data1 + 1) = sizeY;
	for (size_t i = 2; i < sizeX * sizeY + 2; i++)
	{
		*(data1 + i) = data[i - 2];
	}
	return data1;
}

const int* element (const int* data, size_t i, size_t j){ //вычисление адреса [i][j] элемента, используя массив, полученный из newData
	size_t Y = *(data + 1);
	return data + i * Y + j + 2;
}

void PrintData2 (const int* data){ //вторая реализация ф-ии, размеры двумерного массива записаны в первые две ячейки одномерного массива data
	size_t X = (size_t) *data;
	size_t Y = (size_t) *(data + 1);
	for (size_t i = 0; i < X; i++){
		for (size_t j = 0; j < Y; j++){
			printf("%d ", *(element(data, i, j)));
		}
		printf("\n");
	}
}

void PrintDataTriangle (const int* data, size_t length){ //печать треугольного массива
	const int* end = data + length;
	for (size_t i = 0; i < length; i++){
		for (size_t j = 0; j < i + 1; j++){
			if (data + j < end){
				printf("%d ", *(data + j));
			}
			else{
				exit(0);
			}
		}
		data += i + 1;
		printf("\n");
	}
}

int get_element (const int* data, size_t i, size_t j){ //возвращает элемент матрицы, размеры которой заданы в первых двух ячейках одномерного массива data
	return *(element(data, i, j));	
}

/*int set_element (int* data, size_t i, size_t j, int new_element){ //присваивает новое значение элементу матрицы и возвращает старое
	int previous_element = get_element(data, i, j);
	*(element(data, i, j)) = new_element;
	return previous_element;
}*/

int main(){
	const int data[15] = {10, 20, 30, 40, 50,
			      11, 21, 31, 41, 51,
			      12, 22, 32, 42, 52};
	size_t X = 3, Y = 5;
	//PrintData1(data, X, Y);
	
	const int* data1 = malloc(17 * sizeof(int));
	data1 = newData(data, X, Y);
	//PrintData2(data1);
	
	free((void*) data1);
	
	/*const int data2[15] = {0, 
			       2, 3, 
			       4, 5, 6,
			       7, 8, 9, 4,
			       1, 0, 2, 1, 5};*/

	//size_t lengthData2 = 15;
	//PrintDataTriangle(data2, lengthData2); 
	
	size_t i = 2;
	size_t j = 2;

	//int a = get_element(data1, i, j);
	//printf("%d\n", a);
	
	//int b = set_element(data1, i, j, 5);
	//printf("%d\n", b);

	//PrintData2(data1);

}





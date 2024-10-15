#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <limits.h>
#include <locale.h>
#include <time.h>
#include <random>
#include <string.h>
#include <search.h>
#include <Windows.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
//размер графа = кол-во ребер
int main(){
	int m = 5;
	int Gsize = 0;
	int** G;
	int* deg;
	srand(time(NULL));
	setlocale(LC_ALL, "");
	

	printf("1 задание:\n");//1. Сгенерируйте матрицу смежности для неориентированного графа G.Выведите матрицу на экран.
	
	//выделение памяти для матрицы смежности
	G = (int**)malloc(m*sizeof(int*));
	for (int i = 0; i < m; i++){
		G[i]= (int*)malloc(m*sizeof(int));
	}

	//заполнение графа 1-ми (кроме главной диагонали)
	for (int i = 0; i < m; i++){
		for (int j = 0; j < m; j++) {
			G[i][j] = rand()%2; // 0 или 1
			G[i][i] = 0;
			G[j][j] = 0;
			G[j][i] = G[i][j];
			printf("%d ", G[i][j]);
		}
		printf("\n");
	}


	printf("\nЗадание 2"); //Определите размер графа G, используя матрицу смежности графа.
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			if (G[i][j] == 1) {
				Gsize++;
			}
		}
	}
	printf("\nРазмер графа = %d", Gsize / 2);
	

	printf("\nЗадание 3\n");// поиск изолированных, концевых и доминирующи вершин.

	deg = (int*)malloc(m * sizeof(int)); // 
	for (int i = 0; i < m; i++) {
		deg[i] = 0;
	}
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			if (G[i][j] == 1) {
				deg[i]++;
			}
		}
		printf("Степень вершины %d = %d \n", i+1, deg[i]);
	}

	for (int i = 0; i < m; i++) {
		if (deg[i] == 0) printf("\n Вершина %d изолированная", i);
		if (deg[i] == 1) printf("\nВершина %d концевая", i);
		if (deg[i] == m-1) printf("\nВершина %d доминирующая", i);
	}
	
	return 0;
}
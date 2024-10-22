#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <locale.h>
#include <time.h>
#include <random>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
//размер графа = кол-во ребер
int main() {
	int m = 5;
	int Gsize = 0;
	int** N;
	int** G;
	int* deg;
	srand(time(NULL));
	setlocale(LC_ALL, "");


	printf("\n1 задание:\n");//1. Сгенерируйте матрицу смежности для неориентированного графа G.Выведите матрицу на экран.
	printf("Матрица смежности\n");
	//выделение памяти для матрицы смежности
	G = (int**)malloc(m * sizeof(int*));
	for (int i = 0; i < m; i++) {
		G[i] = (int*)malloc(m * sizeof(int));
	}

	//заполнение графа 1-ми (кроме главной диагонали)
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			G[i][j] = rand() % 2; // 0 или 1
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


	printf("\n \nЗадание 3\n");// поиск изолированных, концевых и доминирующих вершин.

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
		printf("Степень вершины %d = %d \n", i + 1, deg[i]);
	}

	for (int i = 0; i < m; i++) {
		if (deg[i] == 0) printf("\n Вершина %d изолированная", i);
		if (deg[i] == 1) printf("\nВершина %d концевая", i);
		if (deg[i] == m - 1) printf("\nВершина %d доминирующая", i);
	}


	printf("\n\nЗадание 4\n");//Матрица инцидентности графа

	//выделение памяти и заполнение 0-ми
	N = (int**)malloc(m * sizeof(int*));
	for (int i = 0; i < m; i++) {
		N[i] = (int*)malloc(Gsize / 2 * sizeof(int));
		for (int j = 0; j < Gsize / 2; j++) {
			N[i][j] = 0;
		}
	}

	//построение матрицы инцидентности
	int k = 0;
	for (int i = 0; i < m; i++) {
		for (int j = i; j < m; j++) {
			if (G[i][j] == 1) {
				N[i][k] = 1;
				N[j][k] = 1;
				k++;
			}
		}
	}

	//вывод матрицы инцидентности
	printf("\nМатрица Инцидентности:\n");
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < Gsize / 2; j++) {
			printf("%d ", N[i][j]);
		}
		printf("\n");
	}

	printf("\nЗадание 5\n");//Определение размера графа G, используя матрицу инцидентности графа.

	int Nsize = 0;
	for (int j = 0; j < Gsize; j++) {
		int count = 0;
		for (int i = 0; i < m; i++) {
			if (N[i][j] == 1) {
				count++;
			}
		}
		if (count == 2) {
			Nsize++;
		}
	}

	printf("Размер графа(с помощью матрицы смежности:) = %d\n", Nsize);

	printf("\nЗадание 6");//Изолированные, концевые и доминирующие вершины графа G

	int inc = 0;
	for (int i = 0; i < m; i++) {
		int count = 0;
		for (int j = 0; j < Gsize / 2; j++) {
			inc += N[i][j];
		}

		if (inc == 0) printf("\n Вершина %d изолированная", i+1);
		if (inc == 1) printf("\nВершина %d концевая", i+1);
		if (inc == Nsize) printf("\nВершина %d доминирующая", i+1);
	}

	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void shell(int* items, int count)
{
	int i, j, gap, k;
	int x, a[5];
	a[0] = 9; a[1] = 5; a[2] = 3; a[3] = 2; a[4] = 1;
	for (k = 0; k < 5; k++) {
		gap = a[k];
		for (i = gap; i < count; ++i) {
			x = items[i];
			for (j = i - gap; (x < items[j]) && (j >= 0); j = j - gap)
				items[j + gap] = items[j];
			items[j + gap] = x;
		}
	}
}

void qs(int* items, int left, int right) //вызов функции: qs(items, 0, count- 1);
{
	int i, j;
	int x, y;

	i = left; j = right;
	/* выбор компаранда */
	x = items[(left + right) / 2];
	do {
		while ((items[i] < x) && (i < right)) i++;
		while ((x < items[j]) && (j > left)) j--;
		if (i <= j) {
			y = items[i];
			items[i] = items[j];
			items[j] = y;
			i++; j--;
		}
	} while (i <= j);
	if (left < j) qs(items, left, j);
	if (i < right) qs(items, i, right);
}

int funcmp(const void* v1, const void*v2) {
	return(*(int*)v1 - *(int*)v2);
}

int main(void)
{
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);
	srand(time(NULL)); // инициализируем параметры генератора случайных чисел
	clock_t start, end, difference; // объявляем переменные для определения времени выполнения
	int i = 0, j = 0, r, choose = 0, sort = 0, elem_c;
	int m = 0, n = 0;
	int half = m / 2;
	printf("Size of massive:  \n");
	printf("Rows:");
	scanf_s("%d", &m);
	printf("\n");
	////Задание 1
	/*int** a;
	a = (int**)malloc(m * sizeof(int*));
	printf("Columns:");
	scanf_s("%d", &n);
	for (int i = 0; i < m; i++) {
		a[i] = (int*)malloc(sizeof(int) * n);
	}
	for (int i = 0; i < m;i++ ) {
		for (int j = 0; j < n; j++) {
			a[i][j] = rand() % 1000;
		}
	}
	int** b;
	b = (int**)malloc(m * sizeof(int*));
	for (int i = 0; i < m; i++) {
		b[i] = (int*)malloc(sizeof(int) * n);
	}
	for (int i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			b[i][j] = rand() % 1000;
		}
	}
	int** c;
	c = (int**)malloc(m * sizeof(int*));
	for (int i = 0; i < m; i++) {
		c[i] = (int*)malloc(sizeof(int) * n);
	}
	start = clock();
	for (i = 0; i <m; i++)
	{
		for (j = 0; j < n; j++)
		{
			elem_c = 0;
			for (r = 0; r < n; r++)
			{
				elem_c = elem_c + a[i][r] * b[r][j];
				c[i][j] = elem_c;
			}
		}
	} 
	end = clock();
	free(a);
	free(b);
	free(c);*/

	//Задание 2
	int* mss;
	mss = (int*)malloc(m * sizeof(int));
	printf("Massive size = %d\n\n\n", m); //m - размер массива
	printf("Choose sort type(1 - shell sort     2 - quick sort 3 - library quicksort()):\n");
	printf("Your choose: ");
	scanf_s("%d", &sort);
	printf("\n\n\n");
	printf("Choose numbers type: \n");
	printf("1.Random numbers\n2.Increasing numbers\n3.Descending numbers \n4.Sawtooth subsequence\n");
	printf("Your choose: ");
	scanf_s("%d", &choose);
	printf("\n\n\n");
	switch (choose) {
	case 1:{
		//Случайные числа
	for (int i = 0; i < m; i++) {
		mss[i] = rand() % 1000;
		//printf("%d, ", mss[i]);
		break;
	}
		}
	case 2: {
		//Возрастающая последовательность
	for (int i = 0; i < m; i++) {
		mss[i] = i;
		//printf("%d, ", mss[i]);
	}
	printf("\n");
	break;
	}
	case 3: {
		//Убывающая последовательность
	for (int i = 0; i < m; i++) {
		mss[i] = m-i;
		//printf("%d, ", mss[i]);
	}
	printf("\n");
	break;
	}
	case 4: {
		//Пилообразная последовательность
	for (int i = 0; i < half; i++) {
		mss[i] = m - i;
		//printf("%d, ", mss[i]);
	}

	for (int i = 0; i < half; i++) {
		mss[half + i] = half - i;
		//printf("%d, ", mss[i]);
	}
	printf("\n");
	break;
	}
	}
	//printf("Massive before: \n");
	printf("\n\n\n");
	
	start = clock();
	switch (sort) {
	case 1:{
			shell(mss, m);
			break;
		}
	case 2:{
			qs(mss, 0, m - 1);
			break;
		}
	case 3: {
		qsort(mss,m, sizeof(int),funcmp);
		break;
	}
	}
	end = clock();
	//printf("Massive after: \n");
	printf("\n\n\n");
	for (int i = 0; i < m; i++) {
		//printf("%d, ",mss[i]);
	}
	printf("\n\n\n");
	free(mss);

	//вывод времени
	difference = (float(end) - float(start));
	printf("\nStart: %f \nEnd: %f\nDifference: %f", float(start) / float(CLOCKS_PER_SEC), float(end)/ float(CLOCKS_PER_SEC), float(difference)/ float(CLOCKS_PER_SEC));
	return 0;
}
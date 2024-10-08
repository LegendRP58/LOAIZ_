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

//Доп. Задание
    // в 5 добавить сортировку по курсу студента
    //ввод кол-ва элементов структуры с клавиатуры
    //в 4 номере добавлен вывод результата суммы строк/столбцов через массив

int main() {
    setlocale(LC_ALL, "RU");
    printf("----------------------Лабораторная работа 1---------------------- \n");
    printf("Выберите номер задания:");
    int choose;
    SetConsoleCP(1251); 
    SetConsoleOutputCP(1251);
    scanf_s("%d", &choose);
    printf("\nНомер задания: %d \n", choose);

    int stroka = 100, stolb = 100, i, j, a1, b1;
    int mass[10] = { 2,4,6,8,-10,34,64,64,5463,43 }, max = INT_MIN, min = INT_MAX;
    int** mass4 = (int**)calloc(stroka * stolb, sizeof(int*)); // память на массив массивов
    for (int i = 0; i < stroka; i++) {
        mass4[i] = (int*)calloc(stolb, sizeof(int)); // память на элементы массива
    }
   
    switch (choose) {
    case 1:
        for (int i = 0; i < 10; i++) {
            if (mass[i] > max) {
                max = mass[i];
            }
            if (mass[i] < min) {
                min = mass[i];
            }
        }
        printf(" Минимальное: %d \n Максимальное: %d \n Разность: %d", min, max, max - min);
        break;

    case 2:
        srand(time(NULL));
        int mass2[25], a, b;
        printf("Выберите нижнюю границу рандомных чисел: ");
        scanf_s("%d", &a);
        printf("Выберите верхнюю границу рандомных чисел: ");
        scanf_s("%d", &b);
        printf("Элементы массива: ");
        for (int i = 0; i < 25; i++) {
            mass2[i] = a + rand() % (b - a + 1);
            printf("%d, ", mass2[i]);
        }
        break;

    case 3:
        int* mass3;
        int n, a0, b0;
        printf("Выберите нижнюю границу рандомных чисел: ");
        scanf_s("%d", &a0);
        printf("Выберите верхнюю границу рандомных чисел: ");
        scanf_s("%d", &b0);
        printf("Введите размер массива: ");
        scanf_s("%d", &n);
        mass3 = (int*)malloc(n * sizeof(int));
        printf("Элементы массива: ");
        for (int i = 0; i < n; i++) {
            mass3[i] = a0 + rand() % (b0 - a0 + 1);
            printf("%d, ", mass3[i]);
        }
        free(mass3);
        break;

    case 4:
        printf("Кол-во строк массива: ");
        scanf_s("%d", &stroka);
        printf("Кол-во столбцов массива: ");
        scanf_s("%d", &stolb);

        printf("Массив:\n");
        for (int i = 0; i < stroka; i++) {
            for (j = 0; j < stolb; j++) {
                mass4[i][j] = rand() % 1000;
                printf("%d ", mass4[i][j]);
            }
            printf("\n");
        }

        for (int i = 0; i < stroka; i++) {
            int *sum_strok = (int*)calloc(stolb,sizeof(int)); //добавлен динамический массив
            for (j = 0; j < stolb; j++) {
                sum_strok[i] += mass4[i][j];
            }
            printf("Сумма строки %d: %d\n", i + 1, sum_strok[i]);// вывод рез-та суммы через динамический массив
        }
        for (int j = 0; j < stolb; j++) {
            int* sum_stolb = (int*)calloc(stolb, sizeof(int)); //добавлен динамический массив
            for (i = 0; i < stroka; i++) {
                sum_stolb[i] += mass4[i][j];// вывод рез-та суммы через динамический массив
            }
            printf("Сумма столбца %d: %d\n", j + 1, sum_stolb[i]);
        }
        for (int i = 0; i < stroka; i++) {
            free(mass4[i]);
        }
        free(mass4);
        break;

    case 5: {
        int sort, sort_choose = 0, search, action, stud_numbers;
        const int number = 100; 
        printf("Введите кол-во студентов: "); //добавлен ввод кол-ва студентов с клавиатуры
        scanf("%d", &stud_numbers);
        rewind(stdin);

        struct student {
            char name[50], surname[50], facult[30];
            int age, course;
        } students [number];

        //Ввод данных в структуру
        for (int i = 0; i < stud_numbers; i++) {
                printf("Введите имя студента: \n");
                scanf("%s", students[i].name);
                rewind(stdin);
                printf("Введите фамилию студента: \n");
                scanf("%s", students[i].surname);
                rewind(stdin);
                printf("Введите возраст студента: \n");
                scanf("%d", &students[i].age);
                rewind(stdin);
                printf("Введите факультет студента: \n");
                scanf("%s", students[i].facult);
                rewind(stdin);
                printf("Введите номер курса студента: \n");
                scanf("%d", &students[i].course);
                rewind(stdin);
        }
        
        //Сортировка по курсу студента//

        student tmp;
        for (int i = stud_numbers - 1; i >= 0; i--)
        {
            for (int j = 0; j < i; j++)
            {
                // сравниваем элементы массива по номеру курса
                if (students[j].course > students[j + 1].course){
                    tmp = students[j];
                    students[j] = students[j + 1];
                    students[j + 1] = tmp;
                }
            }
        }
       
        //Вывод структуры//

        printf("\n\n");
        printf("------------------------------Студенты------------------------------\n"); 
        for (int i = 0; i < stud_numbers; i++) {
            printf("%d.", i + 1);
            printf(" Имя:%s", students[i].name);
            printf(" Фамилия:%s", students[i].surname);
            printf(" Возраст:%d",students[i].age);
            printf(" Факультет:%s", students[i].facult);
            printf(" Курс:%d\n",students[i].course);
        }
             
             ///Поиск///

        printf("\nПоиск:\n1)Поиск по имени \n2)По фамилии \n3)По возрасту \n4)По факультету \n5)По номеру курса.\n");
        scanf("%d", &search);
        int result;
        bool out = false;
        switch (search) {
        case 1: {
            char name_student[100];
            int count_1 = 1;
            printf("\nВведите имя студента:");
            scanf("%s", &name_student);
            rewind(stdin);
            for (int i = 0; i < number; i++) {
                if ((strcmp(students[i].name, name_student)) == 0) {
                    printf("Студент найден. Номер студента %d", count_1);
                    out = true;
                    break;
                }
                count_1++;
            }
            if (!out) {
                printf("Студент не найден.");
            }
            break;
        }

        case 2: {
            char surname_student[100];
            int count_1 = 1;
            printf("\nВведите фамилию студента:");
            scanf("%s", &surname_student);
            rewind(stdin);
            for (int i = 0; i < number; i++) {
                if ((strcmp(students[i].surname, surname_student)) == 0) {
                    printf("Студент найден. Номер студента %d", count_1);
                    out = true;
                    break;
                }
                count_1++;
            }
            if (!out) {
                printf("Студент не найден.");
            }
            break;
        }

        case 3: {
            int age_student;
            int count_1 = 1;
            printf("\nВведите возраст студента:");
            scanf("%d", &age_student);
            rewind(stdin);
            for (int i = 0; i < number; i++) {
                if ((students[i].age == age_student)) {
                    printf("Студент найден. Номер студента %d", count_1);
                    out = true;
                    break;
                }
                count_1++;
            }
            if (!out) {
                printf("Студент не найден.");
            }
            break;
        }

        case 4: {
            char facult_student[100];
            int count_1 = 1;
            printf("\nВведите факультет студента:");
            scanf("%s", &facult_student);
            rewind(stdin);
            for (int i = 0; i < number; i++) {
                if ((strcmp(students[i].facult, facult_student)) == 0) {
                    printf("Студент найден. Номер студента %d", count_1);
                    out = true;
                    break;
                }
                count_1++;
            }
            if (!out) {
                printf("Студент не найден.");
            }
            break;
        }

        case 5: {
            int course_student;
            int count_1 = 1;
            printf("\nВведите номер курса студента:");
            scanf("%d", &course_student);
            rewind(stdin);
            for (int i = 0; i < number; i++) {
                if (students[i].course == course_student) {
                    printf("Студент найден. Номер студента %d", count_1);
                    out = true;
                    break;
                }
                count_1++;
            }

            if (!out) {
                printf("Студент не найден.");
            }
            break;
        }
    }
    }
    }
    return 0;
    }
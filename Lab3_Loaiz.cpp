#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<string.h>
#include<locale.h>
#include<stdio.h>

//удалить эл-ты с приоритетом >10;
//вывод приоритета /done


struct node
{
	char inf[256];  // полезная информация
	int prioryty;
	struct node* next; // ссылка на следующий элемент 
};

//Обращение к списку и его элементам осуществляется посредством указателей :

struct node* head = NULL, * last = NULL, * f = NULL; // указатели на первый и последний элементы списка
int dlinna = 0;

//Для списка реализованы функции создания, добавления, удаления элемента, просмотра списка, нахождения нужного элемента списка :

// Функции добавления элемента, просмотра списка
void spstore(void), review(void), del(char* name);

char find_el[256];
struct node* find(char* name); // функция нахождения элемента
struct node* get_struct(void); // функция создания элемента



struct node* get_struct(void)
{
	struct node* p = NULL;
	char s[256];
	int prior = 0;

	if ((p = (node*)malloc(sizeof(struct node))) == NULL)  // выделяем память под новый элемент списка
	{
		printf("Ошибка при распределении памяти\n");
		exit(1);
	}

	printf("Введите название объекта: \n");   // вводим данные
	scanf("%s", s);
	if (*s == 0)
	{
		printf("Запись не была произведена\n");
		return NULL;
	}
	printf("Укажите приоритет:\n");
	scanf("%d", &prior);
	strcpy(p->inf, s);
	p->prioryty = prior;
	p->next = NULL;

	return p;		// возвращаем указатель на созданный элемент
}

/* Последовательное добавление в список элемента (в конец)*/
void spstore(void)
{
	struct node* p = NULL;
	p = get_struct();
	if (head == NULL && p != NULL)	// если списка нет, то устанавливаем голову списка
	{
		head = p;
		last = p;
	}
	else if (head != NULL && p != NULL) // список уже есть, то вставляем в конец
	{
		last->next = p;
		last = p;
	}
	return;
}


/* Просмотр содержимого списка. */
void review(void)
{
	struct node* struc = head;
	if (head == NULL)
	{
		printf("Список пуст\n");
	}
	while (struc)
	{
		printf("Имя - %s Приоритет: %d \n", struc->inf, struc->prioryty);
		struc = struc->next;
	}
	return;
}


/* Поиск элемента по содержимому. */
struct node* find(char* name)
{
	struct node* struc = head;
	if (head == NULL)
	{
		printf("Список пуст\n");
	}
	while (struc)
	{
		if (strcmp(name, struc->inf) == 0)
		{
			return struc;
		}
		struc = struc->next;
	}
	printf("Элемент не найден\n");
	return NULL;
}

/* Удаление элемента по содержимому. */
void del(char* name) {
	struct node* struc = head;
	struct node* prev = NULL;
	int found = 0;
	
	if (head == NULL) {
		printf("Список пуст\n");
		return;
	}

	// Проход по списку для поиска и удаления всех совпадающих элементов
	while (struc) {
		if (strcmp(name, struc->inf) == 0) {
			found = 1;  // Элемент найден

			// Удаление первого элемента
			if (prev == NULL) {
				head = struc->next;
				free(struc);
				struc = head;  // обновляем текущий узел после удаления головы
			}
			else {  // Удаление элемента не в начале списка
				prev->next = struc->next;
				free(struc);
				struc = prev->next;  // обновляем текущий узел
			}
			printf("Элемент удален\n");
		}
		else {
			prev = struc;  // Обновляем предыдущий элемент
			struc = struc->next;  // Переходим к следующему элементу
		}
	}

	if (!found) {
		printf("Элемент не найден\n");
	}
}

/* Удаление элемента по приоритету. */
void del_prior(int prior_del) {
	struct node* struc = head;
	struct node* prev = NULL;

	int found = 0;
	int prior = 0;
	printf("Введите приоритет, выше которого все элементы будут удалены: ");
	scanf_s("%d", &prior_del);

	if (head == NULL) {
		printf("Список пуст\n");
		return;
	}

	// Проход по списку для поиска и удаления всех элементов с определенным приоритетом 
	while (struc) {
		if (struc->prioryty > prior_del) {
			found = 1;  // Элемент найден

			// Удаление головы списка
			if (prev == NULL) {
					head = struc->next;
					free(struc);
					struc = head;  // обновляем текущий узел после удаления головы
			}
			else {  // Удаление элемента не в начале списка
				prev->next = struc->next;
				free(struc);
				struc = prev->next;  // обновляем текущий узел
			}		
		}

		else {
			prev = struc;  // Обновляем предыдущий элемент
			struc = struc->next;  // Переходим к следующему элементу
		}
	}

	if (!found) {
		printf("Элемент не найден\n");
	}
}

int main() {
	setlocale(LC_ALL, "rus");
	printf("\n-------------Лабораторная работа 3-------------\n");
	char s[10];
	int c = 0;
	int prior_del = 0;
	struct node* vrem;
	do {
		printf("\n-----------------------------------------------\n");
		printf("1. Добавить элемент\n");
		printf("2. Просмотреть список\n");
		printf("3. Удалить элемент по содержанию\n");
		printf("4. Удалить элементы по приоритету\n");
		printf("5. Поиск элемента\n");
		printf("6. Выход\n");
		printf("Выберите один из пунктов: ");
		scanf_s("%d", &c);

		switch (c) {
		case 1:
			printf("\n");
			spstore();
			break;
		case 2:
			printf("\n\n  Список:\n");
			review();
			break;

		case 3:
			printf("Введите название объекта для удаления: ");
			scanf_s("%s", s, (unsigned)_countof(s));
			del(s);
			break;

		case 4: {
			del_prior(prior_del);
		break;
		}
		case 5:
			printf("Введите элемент для поиска: ");
			scanf_s("%s", s, (unsigned)_countof(s));
			vrem = find(s);
			if (vrem != NULL) {
				printf("Элемент  найден!\n"); // Вывести данные вне функции, сохранить указатель, вывести номер в структуре
				printf("Элемент: %s\n Приоритет элемента: %d", vrem->inf, vrem->prioryty);
			}
			break;

		case 6:
			printf("Выход...\n");
			break;
		default:
			printf("Ошибка. Попробуйте снова.\n");
			break;
		}
	} while (c != 5);

	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

//узел древа
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

//указатель на древо и его элементы
struct Node* root;

 //Создание древа и выделение памяти для его элементов 
struct Node* CreateTree(struct Node* root, struct Node* r, int data) {
    if (r == NULL) {
        r = (struct Node*)malloc(sizeof(struct Node));
        if (r == NULL) {
            printf("Ошибка выделения памяти");
            exit(0);
        }

        r->left = NULL;
        r->right = NULL;
        r->data = data;
        if (root == NULL) return r;

        if (data > root->data) root->left = r;
        else root->right = r;
        return r;
    }

    //Ислючение добавления одинаковых элементов
    if (data == r->data) {
        print("Введен дубликат числа %d \n", data);
            return root;
    }


    if (data > r->data)
        CreateTree(r, r->left, data);
    else
        CreateTree(r, r->right, data);

    return root;
}

//вывод перевернутого на 90 градусов дерева в консоль, где head слева
void print_tree(struct Node* r, int l) {
    if (r == NULL) {
        return;
    }

    print_tree(r->right, l + 1);
    for (int i = 0; i < l; i++) {
        printf(" ");
    }

    printf("%d\n", r->data);
    print_tree(r->left, l + 1);
}

// поиск числа в дереве
struct Node* search(struct Node *r,int data ) {
    if (r->data == data) return r;
    else if (r->data < data && r->left != NULL) {
        search(r->left, data);
    }

    else if (r->data > data && r->right != NULL) {
        search(r->right, data);
    }
    else {
        printf("Не найдено. ");
        return NULL;
    }
}

//подсчет количества элементов в дереве
int fcount(struct Node *r, int data) {
    if (r == NULL){
        return 0; 
    }

    int counter = (r->data == data);
    counter += fcount(r->left, data);
    counter += fcount(r->right, data);
    return counter;
}

int main() {
    setlocale(LC_ALL, "");
    int cou = 0;
    int D, start = 1;

    root = NULL;
    printf("Введите (-1) для окончания заполнения данных\n");
    while (start) {
        printf("Введите число: ");
        scanf_s("%d", &D);
        if (D == -1) {
            printf("Построение дерева окончено\n\n");
            start = 0;
        }
        else
            root = CreateTree(root, root, D);
    }

    print_tree(root, 0);
    printf("Введите число для поиска: ");
    scanf_s("%d", &D);
    struct Node *r = search(root, D);
    if (r != NULL) {
        printf("Число %d найдено в дереве.\n", r->data);
    }
    else {
        printf("Число %d не найдено в дереве.\n", D);
    }

    cou =fcount(root, D);
    printf("Количество = %d", cou);
    return 0;
}

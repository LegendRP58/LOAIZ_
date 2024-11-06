#include <iostream> 
#include <locale.h>
using namespace std;

//создание графа
int** createG(int size) {
    int** G;
    G = (int**)malloc(size * sizeof(int*));

    for (int i = 0; i < size; i++) {
        G[i] = (int*)malloc(size * sizeof(int));
    }

    for (int i = 0; i < size; i++) {
        G[i][i] = 0;
        for (int j = i + 1; j < size; j++) {

            G[i][j] = rand() % 2;
            G[j][i] = G[i][j];
        }
    }
    return G;
}

//вывод матрицы
void printG(int** G, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << " " << G[i][j];
        }
        cout << endl;
    }
}

//Удаление вершины
int** delV(int** G, int size, int v) {
    int** Gtemp = createG(size - 1);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i < v && j < v) Gtemp[i][j] = G[i][j];
            if (i > v && j > v) Gtemp[i - 1][j - 1] = G[i][j];
            if (i > v && j < v) Gtemp[i - 1][j] = G[i][j];
            if (i < v && j > v) Gtemp[i][j - 1] = G[i][j];
        }
    }
    for (int i = 0; i < size; i++) {
        free(G[i]);
    }
    free(G);
    G = NULL;
    return Gtemp;
}

//отождествление вершин
int** unionV(int** G, int size, int v1, int v2) {
    for (int i = 0; i < size; i++) {
        if (G[v2][i] == 1) {
            G[v1][i] = G[v2][i];
            G[i][v1] = G[i][v2];
        }
    }
    G = delV(G, size, v2);
    return G;
}

//стягивание ребра
int** contrE(int** G, int size, int v1, int v2) {
    G[v1][v2] = 0;
    G[v2][v1] = 0;

    for (int i = 0; i < size; i++) {
        if (G[v2][i] == 0) {
            G[v1][i] = G[v2][i];
            G[i][v1] = G[i][v2];
        }
    }

    G = delV(G, size, v2);
    return G;
}

//расщепление вершины
int** splitV(int** G, int size, int v) {
    int** Gtemp = createG(size + 1);

    for (int i = 0; i < size; i++) {
        Gtemp[i][size] = G[i][v];
        Gtemp[size][i] = G[v][i];
    }

    printG(Gtemp, size + 1);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            Gtemp[i][j] = G[i][j];
        }
    }
    Gtemp[v][v] = 0;
    Gtemp[size + 1][size + 1] = 0;

    for (int i = 0; i < size; i++) {
        free(G[i]);
    }
    free(G);
    G = NULL;
    return Gtemp;
}

//объединение графа
int** unionG(int** G1, int** G2, int size1, int size2) {
    int sizemax = (size1 > size2) ? size1 : size2;
    int sizemin = (size1 < size2) ? size1 : size2;

    int** Gmax = (size1 > size2) ? G1 : G2;
    int** Gmin = (size1 > size2) ? G1 : G2;

    int** Gtemp = createG(sizemax);

    for (int i = 0; i < sizemax; i++) {
        for (int j = 0; j < sizemax; j++) {
            Gtemp[i][j] = Gmax[i][j];
        }
    }

    for (int i = 0; i < sizemin; i++) {
        for (int j = 0; j < sizemin; j++) {
            if (Gmin[i][j] == 1) {
                Gtemp[i][j] = Gmin[i][j];
            }
        }
    }
    return Gtemp;
}

//пересечение графов
int** intersectG(int** G1, int** G2, int size1, int size2) {
    int sizemin = (size1 < size2) ? size1 : size2;

    int** Gtemp = createG(sizemin);

    for (int i = 0; i < sizemin; i++) {
        for (int j = 0; j < sizemin; j++) {
            Gtemp[i][j] = G1[i][j] & G2[i][j];
        }
    }
    return Gtemp;
}

//кольцевая сумма
int** xorG(int** G1, int** G2, int size1, int size2, int* nG5)
{
    int sizemax = (size1 > size2) ? size1 : size2;
    int sizemin = (size1 < size2) ? size1 : size2;
    int step = 0;

    int** Gmax = (size1 > size2) ? G1 : G2;
    int** Gmin = (size1 < size2) ? G1 : G2;

    int** Gnew = createG(sizemax);
    for (int i = 0; i < sizemin; i++)
    {
        for (int j = 0; j < sizemin; j++)
        {
            Gnew[i][j] = G1[i][j] ^ G2[i][j];
        }
    }

    for (int i = 0; i < sizemin; i++)
    {
        for (int j = sizemin; j < sizemax; j++)
        {
            Gnew[i][j] = Gmax[i][j];
        }
    }

    for (int i = sizemin; i < sizemax; i++)
    {
        for (int j = 0; j < sizemax; j++)
        {
            Gnew[i][j] = Gmax[i][j];
        }
    }

    for (int i = 0; i < sizemax; i++)
    {
        step = 0;
        for (int j = 0; j < sizemax; j++)
        {
            if (Gnew[i][j] == 1)
            {
                step++;
            }
        }
        if (step == 0) {
            Gnew = delV(Gnew, sizemax, i);
            sizemax--;
            i--;
        }
    }
    *nG5 = sizemax;
    return Gnew;
}

int main() {
    setlocale(LC_ALL, "");
    int nG1, nG2, v, v1, v2, choose, nG5, graph;
    cout << "Введите количество вершин  Граф1: ";
    cin >> nG1;
    cout << endl;
    cout << "Введите количество вершин  Граф2: ";
    cin >> nG2;

    int** G1 = createG(nG1);
    cout << endl << " Матрица 1" << endl << endl;
    printG(G1, nG1);
    int** G2 = createG(nG2);
    cout << endl << " Maтрица 2" << endl << endl;
    printG(G2, nG2);


    cout << "Выберите действие над графами: " << endl;
    cout << "1. Отождествление вершин" << endl << "2. Cтягивание ребра" << endl << "3. Объединение графов" << endl << "4. Пересечение графов" << endl << "5. Кольцевая сумма" << endl;
    cin >> choose;
    
   
    switch (choose) {
    case 1:
        cout << "Выберите граф для операции: " << endl;
        cin >> graph;
        cout << "Выберите вершины для отождествления: " << endl << "Вершина 1:" << endl;
        cin >> v1;
        cout << "Вершина 2:" << endl;
        cin >> v2;
        if (graph == 1) {
            int** G6 = unionV(G1, nG1, v1, v2);
            cout << "Отождествленнный граф:" << endl;
            printG(G6, nG1 - 1);
        }
        else {
            int** G6 = unionV(G2, nG2, v1, v2);
            cout << "Отождествленнный граф:" << endl;
            printG(G6, nG2 - 1);
        }
        break;

    case 2:
        cout << "Выберите граф для операции: " << endl;
        cin >> graph;
        cout << "Выберите вершины для cтягивания: " << endl << "Вершина 1:" << endl;
        cin >> v1;
        cout << "Вершина 2:" << endl;
        cin >> v2;
        if (graph == 1) {
            int** G6 = contrE(G1, nG1, v1, v2);
            cout << "Отождествленнный граф:" << endl;
            printG(G6, nG1 - 1);
        }
        else {
            int** G6 = contrE(G2, nG2, v1, v2);
            cout << "Отождествленнный граф:" << endl;
            printG(G6, nG2 - 1);
        }
        break;

    case 3: {
        //Объединение вершин
        int** G3 = unionG(G1, G2, nG1, nG2);
        int nG3 = (nG1 > nG2) ? nG1 : nG2;
        cout << endl << "Объединение графов" << endl << endl;
        printG(G3, nG3);
        break;
    }
    case 4: {
        //Пересечение графов
        int** G4 = intersectG(G1, G2, nG1, nG2);
        int nG4 = (nG1 < nG2) ? nG1 : nG2;
        cout << endl << "Пересечение графов" << endl << endl;
        printG(G4, nG4);
        break;
    }

    case 5: {
        //Кольцева сумма
        int** G5 = xorG(G1, G2, nG1, nG2, &nG5);
        cout << endl << "Кольцевая сумма" << endl << endl;
        printG(G5, nG5);
        break;

    }
    }
    return 0;
}
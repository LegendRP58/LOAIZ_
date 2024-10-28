#include <iostream> 
#include <locale.h>
using namespace std;

int** createGraph(int size) {
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

void printG(int** G, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << " " << G[i][j];
        }
        cout << endl;
    }
}

int **delV(int** G, int size, int v) {
    int** Gnew = createGraph(size - 1);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (j < v && i < v) Gnew[i][j] = G[i][j];
            if (j > v && i < v) Gnew[i][j - 1] = G[i][j];
            if (j < v && i > v) Gnew[i - 1][j] = G[i][j];
            if (j > v && i > v) Gnew[i - 1][j] = G[i][j];
        }
    }
    return Gnew;
}

int main() {
    setlocale(LC_ALL, "");
    int nG1, nG2, v, choose;

    cout << "Введите размер матрицы 1: ";
    cin >> nG1;
    cout << endl;

    cout << "Введите размер матрицы 2: ";
    cin >> nG2;
    

    int** G1 = createGraph(nG1);
    cout << endl << " Матрица1" << endl << endl;
    printG(G1, nG1);
    int** G2 = createGraph(nG2);
    cout << endl << " Maтрица2" << endl << endl;
    printG(G2, nG2);
    
    cout << endl << "Выберите матрицу: ";
    cin >> choose;
    cout << endl << "Введите вершину, которую нужно удалить: ";
    cin >> v;

    int** Del = delV(G1, nG1, v - 1);
    int** Del2 = delV(G2, nG2, v - 1);

    switch (choose) {
    case 1:
        printG(Del, nG1 - 1);
        break;
    case 2:
        printG(Del2 , nG2 - 1);
        break;
    }
    cout << endl;
    
    return 0;
}
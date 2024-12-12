#include <iostream>
#include <locale>

using namespace std;

int** createG(int size){
    int** G;
    G = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++)
    {
        G[i] = (int*)malloc(size * sizeof(int));
    }
    for (int i = 0; i < size; i++)
    {
        G[i][i] = 0;
        for (int j = i + 1; j < size; j++)
        {
            G[i][j] = rand() % 2;
            G[j][i] = G[i][j];
        }
    }
    return G;
}

void printG(int** G, int size){
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            cout << G[i][j] << " ";
        }
        cout << endl;
    }
}

//обход в глубину 
void DFS(int** G, int size, int start, int* vis) {
    vis[start] = 1;

    cout << start << endl;

    for (int i = 0; i < size; i++) {
        if (G[start][i] == 1 && vis[i] == 0)
            DFS(G, size, i, vis);
    }


}

int main() {
    setlocale(LC_ALL, "RUS");
    int** G = NULL;
    int nG, s;

    cout << "Введите размер матрицы смежности: ";
    cin >> nG;

    G = createG(nG);

    printG(G, nG);
    cout << endl;

    cout << "Введите начальную вершину обхода: ";
    cin >> s;
    cout << endl;

    int* vis = NULL;
    vis = (int*)malloc(nG * sizeof(int));

    for (int i = 0; i < nG; i++) {
        vis[i] = 0;
    }

    DFS(G, nG, s, vis);

    return 0;
}
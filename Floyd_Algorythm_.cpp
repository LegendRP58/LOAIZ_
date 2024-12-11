#include <iostream>
#include <locale>
#include <time.h>
#include <fstream>
#include <conio.h>
#include <string>

using namespace std;

int** AlgoritmFloyd(const int SIZE, int** graph) {
    //Алгоритм
    for (int k = 0; k < SIZE; k++)
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                if (graph[i][j] > graph[i][k] + graph[k][j])
                    graph[i][j] = graph[i][k] + graph[k][j];

    cout << endl << "Матрица кратчайших расстояний в графе" << endl;
    cout << endl << "   ";
    for (int i = 1; i < SIZE + 1; i++) {
        cout << i << "  ";
    }
    cout << endl << "  ";

    for (int i = 1; i < SIZE + 1; i++) {
        cout << "___";
    }
    cout << endl;
    for (int i = 0; i < SIZE; i++) {
        cout << i + 1 << "|";
        for (int j = 0; j < SIZE; j++) {
            cout << graph[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;
    return graph;
}

//Создание случайной матрицы 
int** Gen_matrix(const int SIZE)
{
    int** graph = new int* [SIZE];
    for (int i = 0; i < SIZE; i++) {
        graph[i] = new int[SIZE];
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (!(i == j)) {
                graph[i][j] = rand() % 100;
            }
            else {
                graph[i][j] = 0;
            }
        }
    }
    return graph;
}

//Ввод матрицы с клавиатуры
int** Write_matrix(const int SIZE) {

    int** a = new int* [SIZE];
    for (int i = 0; i < SIZE; i++) {
        a[i] = new int[SIZE];
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (!(i == j)) {
                cout << "Введите строку " << i + 1 << " столбец " << j + 1 << ": "; cin >> a[i][j];
            }
            else {
                a[i][j] = 0;
            }
        }
    }
    return a;
}

//вывод матрицы в консоль
void Output(const int SIZE, int** a) {
    cout << endl << "   ";
    for (int i = 1; i < SIZE + 1; i++) {
        cout << i << "  ";
    }
    cout << endl << "  ";

    for (int i = 1; i < SIZE + 1; i++) {
        cout << "___";
    }
    cout << endl;

    for (int i = 0; i < SIZE; i++) {
        cout << i + 1 << "| ";
        for (int j = 0; j < SIZE; j++) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void File_output(const int SIZE, int** a) {

    ofstream fileout;
    string filename;

    cout << "Введите имя файла (с расширением, например: file.txt): ";
    cin >> filename;
    fileout.open(filename);
    if (!fileout.is_open()) {
        cerr << "Ошибка открытия файла! " << endl;
    }

    if (fileout.is_open()) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                fileout << a[i][j] << " ";
            }
            fileout << "\n";
        }

    }
    fileout.close();
    cout << "Данные записаны." << endl << endl;
}

int main() {
    setlocale(LC_ALL, "rus");
    int SIZE, choose;
    int** matrix;
    int repeat = 1;
    string path = "C:\23VVV3\Logic\Floyd_Algorythm";

    while (repeat == 1) {
    cout << "----------Реализация Алгоритма Флойда----------" << endl << "1.| Записать через консоль " << endl << "2.| Сгенерировать случайно " << endl << "0.| Выход" << endl;
    choose = _getch();

    
        if (choose == '0') {
            exit(0);
        }

        if (choose == '1') {
            cout << "\n--->Введите кол-во вершин: "; cin >> SIZE; cout << endl;
            matrix = Write_matrix(SIZE);
            Output(SIZE, matrix);
            cout << "\n--->1.Найти кратчайшие пути: " << endl;
            choose = _getch();
            if (choose == '1') {
                AlgoritmFloyd(SIZE, matrix);
                cout << "---> Сохранить в файл? <---" << endl;
                cout << "--->1.Да" << endl;
                cout << "--->2.Нет" << endl;
                choose = _getch();
                if (choose == '1')
                {
                    File_output(SIZE, matrix);
                }
                if (choose = '2') {
                    
                }
            }
        }

        if (choose == '2') {
            cout << "\n--->Введите количество вершин: "; cin >> SIZE; cout << endl;
            matrix = Gen_matrix(SIZE);
            Output(SIZE, matrix);
            cout << "\n--->1.Найти кратчайшие пути " << endl;
            choose = _getch();
            if (choose == '1')
            {
                AlgoritmFloyd(SIZE, matrix);
                cout << "---> Сохранить в файл? <---" << endl;
                cout << "--->1.Да" << endl;
                cout << "--->2.Нет" << endl;
                choose = _getch();
                if (choose == '1')
                {
                    File_output(SIZE, matrix);
                }
                if (choose = '2') {
                    
                }
            }
            
        }
    }
    return 0;
}
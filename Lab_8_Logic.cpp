#include <iostream>
#include <locale>
#include <queue>

using namespace std;

queue <int> Q;

int** createG(int len) {
	int** G;
	srand(time(0));
	G = new int* [len];
	for (int i = 0; i < len; i++) {
		G[i] = new int[len];
	}
	for (int i = 0; i < len; i++) {
		for (int j = i; j < len; j++) {
			if (i == j) G[i][i] = 0;
			else {
				G[i][j] = rand() % 2;
				G[j][i] = G[i][j];
			}
		}
	}
	return G;
}

void printG(int** G, int len) {
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len; j++) {
			cout << G[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}

//Обход графа в ширину
//Q.push(i); // кладем в конец очереди
//s = Q.front(); // возвращение первого эл-та очереди
//Q.empty(); //проверка очередь на пусто
//Q.pop(); // удаление первого эл-та очереди без возвращения его значения

void BFS(int** G, int size, int s, int* vis) {

	Q.push(s);
	vis[s] = 1;
	cout << s << " ";

	while (Q.empty() ) {
		s = Q.front();
		Q.pop();
		for (int i = 0; i < size; i++) {
			if (G[s][i] != 0 && vis[i] == 0) {
				Q.push(i);
				vis[i] = 1;
				cout << i << " ";
			}
		}
	}
}

int main() {
	setlocale(LC_ALL, "");
	int** G, size;
	int s;
	cout << "Введите размер графа: ";
	cin >> size;
	cout << endl;
	cout << "Введите начальную вершину обхода: " << endl;
	cin >> s;

	int* vis = new int[size * sizeof(int)];
	for (int i = 0; i < size; i++) {
		vis[i] = 0;
	}

	G = createG(size);
	printG(G, size);
	cout << "\n";

	cout << "Обход вершины:" << s << endl;

	BFS(G, size, s, vis);

	return 0;
}
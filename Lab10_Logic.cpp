#include <iostream>
#include <locale>
#include <queue>
#include <limits>

using namespace std;

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
				G[i][j] = rand() % 10;
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

//обход в ширину + paccтояние
void BFSDD(int** G, int size, int s, int* dist) {

	queue <int> Q;
	Q.push(s);
	dist[s] = 0;

	while (!Q.empty()) {
		s = Q.front();
		Q.pop();
		for (int i = 0; i < size; i++) {
			if (G[s][i] != 0 && dist[i] + G[s][i] < dist[i]) {
				dist[i] = dist[s] + G[s][i];
				Q.push(i);
			}
		}
	}
}

int main() {
	setlocale(LC_ALL, "");
	int** G = NULL;
	int s, size;
	cout << "Введите размер графа: ";
	cin >> size;
	cout << endl;
	cout << "Введите начальную вершину обхода: " << endl;
	cin >> s;

	G = createG(size);
	printG(G, size);
	cout << "\n";

	int* dist = new int[size * sizeof(int)];
	for (int i = 0; i < size; i++) {
		dist[i] = INT_MAX;
	}

	cout << "Обход вершины:" << s << endl;

	BFSDD(G, size, s, dist);

	for (int i = 0; i < size; i++) {
		cout << dist[i] << " ";
	}

	return 0;
}


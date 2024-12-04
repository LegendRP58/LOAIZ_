#include <iostream>
#include <locale>
#include <queue>
#include <limits>

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


//обход в ширину + paccтояние
void BFSD(int** G, int size, int s, int* dist) {

	Q.push(s);
	dist[s] = 0;

	while (!Q.empty()) {
		s = Q.front();
		Q.pop();
		for (int i = 0; i < size; i++) {
			if (G[s][i] == 1 && dist[i] == INT_MAX) {
				Q.push(i);
				dist[i] = dist[s] + G[s][i];
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

	BFSD(G, size, s, dist);

	for (int i = 0; i < size; i++) {
		cout << dist[i] << " ";
	}


	return 0;
}

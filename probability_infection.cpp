#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;
typedef pair<int, float> valueAndWeight;
vector<valueAndWeight> terminal[100001];
vector<float> road(100001, INT_MAX);

void Dijkstra(int N, int start) {
    vector<bool> visited(N, false);
    road[start] = 0;

    priority_queue<pair<int, int>> queue;
    queue.push(pair<int, int>(0, start));

    while (!queue.empty()) {
        int v = queue.top().second;
        queue.pop();
        if (!visited[v]) {
            for (int i = 0; i < terminal[v].size(); i++) {
                if (road[v] + terminal[v][i].second < road[terminal[v][i].first]) {
                    road[terminal[v][i].first] = road[v] + terminal[v][i].second;
                    queue.push(pair<int, int>(-road[terminal[v][i].first], terminal[v][i].first));
                }
            }
            visited[v] = true;
        }
    }
}

int main() {
    ifstream fin;
    ofstream fout;
    fin.open("../input.txt");
    fout.open("../infection.txt");
    int N = 87, M, start=25,finish=41;
    fin >> M;
    int first, second;
    float weight;
    for (int i = 0; i < M; i++) {
        fin >> first >> second >> weight;
        terminal[first - 1].emplace_back(second - 1, weight);
    }
    Dijkstra(N, start - 1);

    fout<<road[finish-1];
}
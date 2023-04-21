#include <fstream>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

class Task {
public:
    void solve() {
        read_input();
        print_output(get_result());
    }

private:
    // numarul maxim de noduri
    static constexpr int NMAX = (int)1e5 + 5; // 10^5 + 5 = 100.005

    // n = numar de noduri, m = numar de muchii/arce
    int n, m;

    // adj[node] = lista de adiacenta a nodului node
    // exemplu: daca adj[node] = {..., neigh, ...} => exista arcul (node, neigh)
    vector<int> adj[NMAX];

    void read_input() {
        ifstream fin("dfs.in");
        fin >> n >> m;
        for (int i = 1, x, y; i <= m; i++) {
            fin >> x >> y; // arc (x, y)
            adj[x].push_back(y);
			adj[y].push_back(x);
        }
        fin.close();
    }

    void dfs_recursive(int source, vector<bool> &visited) {
        visited[source] = true;

        for (auto& neigh : adj[source]) {
            if (!visited[neigh]) {
                dfs_recursive(neigh, visited);
            }
        }
    }

    int get_result() {
        vector<bool> visited(n + 1, false);

		int counter = 0;
 
        for (int i = 1; i <= n; i++) {
            if (!visited[i]) {
                dfs_recursive(i, visited);
				counter++;
            }
        }

        return counter;
    }

    void print_output(int counter) {
        ofstream fout("dfs.out");
        fout << counter;
        fout << '\n';
        fout.close();
    }
};

// [ATENTIE] NU modifica functia main!
int main() {
    // * se aloca un obiect Task pe heap
    // (se presupune ca e prea mare pentru a fi alocat pe stiva)
    // * se apeleaza metoda solve()
    // (citire, rezolvare, printare)
    // * se distruge obiectul si se elibereaza memoria
    auto* task = new (nothrow) Task(); // hint: cppreference/nothrow
    if (!task) {
        cerr << "new failed: WTF are you doing? Throw your PC!\n";
        return -1;
    }
    task->solve();
    delete task;
    return 0;
}
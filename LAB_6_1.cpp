#include <fstream>
#include <vector>
#include <string>

using namespace std;

int HashFunc(int x) {
    return x = abs(x % 100001);
}

int exists(vector< vector<int> >& hash_tab, int a) {
    int hash = HashFunc(a);
    for (int i : hash_tab[hash]) {
        if (i == a)
            return 0;
    }
    return 1;
}

void insert(vector< vector<int> >& hash_tab, int a) {
    int hash = HashFunc(a);
    if (exists(hash_tab, a) == 1) {
        hash_tab[hash].push_back(a);
    }    
}

void deleted(vector< vector<int> >& hash_tab, int a) {
    int hash = HashFunc(a);
    for (int i = 0; i < hash_tab[hash].size(); i++)
    {
        if (hash_tab[hash][i] == a) {
            hash_tab[hash].erase(hash_tab[hash].begin() + i);
            break;                                        
        }
    }
}

int main() {
    ifstream fin("set.in");
    ofstream fout("set.out");
    int n = 100001;
    vector <vector<int>> hash_tab(n, vector<int>());
    string cmd;
    int x;
    while (fin) {
        fin >> cmd;
        if (!fin.eof()) {
            if (cmd == "insert") {
                fin >> x;
                insert(hash_tab, x);
            }
            else if (cmd == "delete") {
                fin >> x;
                deleted(hash_tab, x);
            }
            else {
                fin >> x;
                if (exists(hash_tab, x) == 0)
                    fout << "true\n";
                else
                    fout << "false\n";
            }
        }
    }
    return 0;
}

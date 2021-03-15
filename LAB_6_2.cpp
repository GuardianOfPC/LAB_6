#include <fstream>
#include <vector>

using namespace std;

ifstream fin("map.in");
ofstream fout("map.out");

struct key {
    string x;
    string y;
};

int HashFunc(const string& word) {
    int hash = 0;
    int k = 41;
    for (int i = 0; i < word.size(); i++) {
        int z = 0;
        if (word[i] - 'a' >= 0 && word[i] - 'a' <= 9)
            z = word[i] - 'a';
        else
            z = word[i] - 'A';
        hash = (hash + ((z + 1) * k) % 1000000) % 1000000;
        k = (k * 41) % 1000000;
    }
    return hash;
}

void put(vector<vector<key>>& hash_tab, const string& key, const string& word) {
    int hash = HashFunc(key);
    for (auto& i : hash_tab[hash]) {
        if (i.x == key) {
            i.y = word;
            return;
        }
    }
    hash_tab[hash].push_back({ key, word });
}

void get(vector<vector<key>>& hash_tab, const string& key) {
    int hash = HashFunc(key);
    for (auto& i : hash_tab[hash]) {
        if (i.x == key) {
            fout << i.y << endl;
            return;
        }
    }
    fout << "none" << endl;
}

void deleted(vector<vector<key>>& hash_tab, const string& key) {
    int hash = HashFunc(key);
    for (int i = 0; i < hash_tab[hash].size(); i++) {
        if (hash_tab[hash][i].x == key) {
            hash_tab[hash].erase(hash_tab[hash].begin() + i);
            return;
        }
    }
}

int main() {
    vector<vector<key>> hash_tab(10000001, vector<key>());
    string cmd;
    while (fin) {
        fin >> cmd;
        if (!fin.eof()) {
            if (cmd == "put") {
                string key, word;
                fin >> key >> word;
                put(hash_tab, key, word);
            }
            else if (cmd == "delete") {
                string key;
                fin >> key;
                deleted(hash_tab, key);
            }
            else if (cmd == "get") {
                string key;
                fin >> key;
                get(hash_tab, key);
            }
        }
    }
    return 0;
}
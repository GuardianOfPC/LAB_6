#include <fstream>
#include <vector>

using namespace std;

int MultimapSize = 10001;
int ValuesArrSize = 101;

struct ValuesArray {
    string K;
    vector <vector<string>> vec_val;
    ValuesArray() {
        vec_val.resize(ValuesArrSize);
    }
};
struct MultiMap {
    vector<vector<ValuesArray>> ValuesArr;
    MultiMap() {
        ValuesArr.resize(MultimapSize);
    }
};

MultiMap multimap;

int HashFunc(string K, int vector_size)
{
    const int z = 31;
    int hash_code = 0;
    for (int i = 0; i < K.length(); i++) {
        hash_code = hash_code * z % vector_size;
        hash_code += (K[i] - 'A' + 1);
        hash_code %= vector_size;
    }
    return hash_code;
}

void put(const string& K, const string& V) {
    int hash_key = HashFunc(K, MultimapSize);
    for (auto& i : multimap.ValuesArr[hash_key]) {
        if (i.K == K) {
            int hash_value = HashFunc(V, ValuesArrSize);
            for (const auto& j : i.vec_val[hash_value]) {
                if (j == V)						
                    return;
            }							
            i.vec_val[hash_value].push_back(V);
            return;
        }
    }
    ValuesArray* ValuesArray_new = new ValuesArray; 
    ValuesArray_new->K = K;
    ValuesArray_new->vec_val[HashFunc(V, ValuesArrSize)].push_back(V);
    multimap.ValuesArr[hash_key].push_back(*ValuesArray_new);
    delete ValuesArray_new;
}

void deleted(const string& K, const string& V) {
    int hash_key = HashFunc(K, MultimapSize);
    for (auto& i : multimap.ValuesArr[hash_key]) { 
        if (i.K == K) {                                                          
            int hash_value = HashFunc(V, ValuesArrSize);
            for (int j = 0; j < i.vec_val[hash_value].size(); j++) {                                                    
                if (i.vec_val[hash_value][j] == V) {
                    i.vec_val[hash_value].erase(i.vec_val[hash_value].begin() + j);
                    return;
                }
            }
        }
    }
}

void deleteAll(const string& K) {
    int hash_key = HashFunc(K, MultimapSize);
    for (auto& i : multimap.ValuesArr[hash_key]) {
        if (i.K == K) {
            for (auto& j : i.vec_val) {
                while (!j.empty())
                    j.pop_back();
            }
            return;
        }
    }
}

vector<string> get(const string& K) {
    vector<string> answer_arr;
    int hash_key = HashFunc(K, MultimapSize);
    for (auto& i : multimap.ValuesArr[hash_key]) {
        if (i.K == K) {
            for (auto& j : i.vec_val)
                for (const auto& k : j)
                    answer_arr.push_back(k);
            return answer_arr;
        }
    }
    return answer_arr;
}

int main() {
    ifstream fin("multimap.in");
    ofstream fout("multimap.out");
    string cmd;
    string K;
    string V;
    while (fin >> cmd) {
        if (cmd == "put") {
            fin >> K >> V;
            put(K, V);
        }
        else if (cmd == "delete") {
            fin >> K >> V;
            deleted(K, V);
        }
        else if (cmd == "deleteall") {
            fin >> K;
            deleteAll(K);
        }
        else if (cmd == "get") {
            fin >> K;
            vector<string> vec = get(K);
            fout << vec.size() << ' ';
            for (const string& i : vec)
                fout << i << ' ';
            fout << "\n";
        }
    }
    return 0;
}
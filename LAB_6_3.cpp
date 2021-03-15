#include <fstream>
#include <vector>

using namespace std;

struct Node {
	string K; // key
	string V; // value
	Node* next_queue;
	Node* next;
	Node* prev;
	
};

class LinkedMap {
private:
	Node* list;
public:
	LinkedMap() {
		list = new Node(); // создаём новый элемент
		list->V = list->K = ""; // записываем в ключ и в значение пустую строку
		list->next_queue = NULL; // адресу следующего элемента в цепочке ставим NULL
	}
	void Insert(string& K, string& V, Node* head) {
		Node* new_el = Search(K);
		if (Search(K) == NULL)  {
			new_el = new Node;
			new_el->K = K;
			new_el->V = V;
			new_el->next_queue = list->next_queue;
			list->next_queue = new_el;
			Node* tail = head->prev;
			tail->next = new_el;
			head->prev = new_el;
			new_el->next = head;
			new_el->prev = tail;
		}
		else
			new_el->V = V;
	}
	void Deleted(string K) {
		Node* current_el = list;
		while (current_el->next_queue != NULL) {
			if (current_el->next_queue->K == K) {
				Node* del = current_el->next_queue;
				current_el->next_queue = current_el->next_queue->next_queue;
				Node* prev_el = del->prev, * next_el = del->next;
				del->prev->next = next_el;
				del->next->prev = prev_el;
				delete del;
				break;
			}
			else
				current_el = current_el->next_queue;
		}
	}
	Node* Search(string& K) {
		Node* current_el = list; 
		while (current_el->next_queue != NULL) {
			if (current_el->next_queue->K == K)
				return current_el->next_queue;
			else
				current_el = current_el->next_queue;
		}
		return NULL;
	}
};

class UpgradeLinkedMap {
private:
	LinkedMap hash_tab[100001];
	Node* head;
public:
	UpgradeLinkedMap() {
		head = new Node;
		head->next = head->prev = head;
		head->V = head->K = "HEAD";
	}
	int HashFunc(string K) {
		int hash = 0;
		int degree = 1;
		int z = 31;
		for (int i = 0; i < K.length(); i++) {
			hash += (K[i] - 'A') * degree;
			degree *= z;
		}
		return abs(hash % 100001);
	}
	void put(string K, string V) {
		int hash = HashFunc(K);
		hash_tab[hash].Insert(K, V, head);
	}
	string get(string K) {
		int hash = HashFunc(K);
		Node* result = hash_tab[hash].Search(K);
		if (result == NULL)
			return "none";
		else
			return result->V;
	}
	void deleted(string key) {
		int hash = HashFunc(key);
		hash_tab[hash].Deleted(key);
	}
	string next(string key) {
		int hash = HashFunc(key);
		Node* result = hash_tab[hash].Search(key); 
		if (result == NULL || result->next == head) 
			return "none";
		else
			return result->next->V;
	}
	string prev(string key) {
		int hash = HashFunc(key);
		Node* result = hash_tab[hash].Search(key);
		if (result == NULL || result->prev == head)
			return "none";
		else
			return result->prev->V;
	}
};

int main() {
	ifstream fin("linkedmap.in");
	ofstream fout("linkedmap.out");
	string K;
	string V;
	string cmd;
	UpgradeLinkedMap u_map;
	while (fin >> cmd) {
		if (cmd == "put") {
			fin >> K >> V;
			u_map.put(K, V);
		}
		else if (cmd == "delete") {
			fin >> K;
			u_map.deleted(K);
		}
		else if (cmd == "get") {
			fin >> K;
			fout << u_map.get(K) << endl;
		}
		else if (cmd == "prev") {
			fin >> K;
			fout << u_map.prev(K) << endl;
		}
		else if (cmd == "next") {
			fin >> K;
			fout << u_map.next(K) << endl;
		}
	}
	return 0;
}
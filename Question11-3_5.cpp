/*
   3. Implement a function to delete a key K from a trie T. Assume that each of the branch nodes has a COUNT field which
   records the number of information nodes in the sub-trie for which it is the root.
   5. Execute a function to gather all the information node beginnig with a specific alphabet from a trie  representing
   alphabetical keys.
   */
#include<iostream>
#include<string>
#include<queue>
using std::string;
using std::cin;
using std::cout;
using std::queue;

class Trie {
	class Node {
	public:
		string key;
		Node* links[27]; // 26 for 'a'-'z' and 1 for special cases
		int count;
		bool isInfoNode;

		Node(string key) : key(key), count(0), isInfoNode(true) {
			for (int i = 0; i < 27; i++) links[i] = nullptr;
		}

		Node() : count(0), isInfoNode(false) {
			for (int i = 0; i < 27; i++) links[i] = nullptr;
		}
	};

	Node* root;

public:
	Trie() : root(nullptr) {}

	void insert(string data) {
		if (!root) root = new Node();
		Node* current = root;

		for (int i = 0; i < data.size(); i++) {
			int index = data[i] - 'a'; // Maps 'a' to 0, 'z' to 25
			if (current->links[index] == nullptr) {
				current->links[index] = new Node();
			}
			current = current->links[index];
			current->count++;
		}

		// Mark the last node as an information node and store the key
		if (!current->isInfoNode) {
			current->isInfoNode = true;
			current->key = data;
		}
	}

	void deleteKey(string data) {
		if (!root) return;

		if (!deleteHelper(root, data, 0)) {
			cout << "Key not found!\n";
		} else {
			cout << "Key deleted successfully.\n";
		}
	}

	bool deleteHelper(Node* node, string data, int depth) {
		if (!node) return false;

		if (depth == data.size()) {
			// We've reached the end of the key
			if (!node->isInfoNode) return false; // Key not found

			// Unmark this node as an information node
			node->isInfoNode = false;
			node->key = "";
			node->count--;
			return node->count == 0;
		}

		int index = data[depth] - 'a';
		if (deleteHelper(node->links[index], data, depth + 1)) {
			// Delete the child node if it has no more keys
			delete node->links[index];
			node->links[index] = nullptr;

			node->count--;
			return node->count == 0 && !node->isInfoNode;
		}

		return false;
	}

	void keysWithAlphabet(char alphabet) {
		if (!root) {
			cout << "Trie is empty\n";
			return;
		}

		int index = alphabet - 'a';
		Node* current = root->links[index];

		if (current == nullptr) {
			cout << "No keys for this alphabet\n";
			return;
		}

		queue<Node*> q;
		q.push(current);
		while (!q.empty()) {
			current = q.front();
			q.pop();

			if (current->isInfoNode) {
				cout << current->key << std::endl;
			}

			for (int i = 0; i < 26; i++) { // Loop through 'a'-'z'
				if (current->links[i] != nullptr) {
					q.push(current->links[i]);
				}
			}
		}
	}
};

int main() {
	Trie trie;
	bool quit = false;
	while (!quit) {
		cout << "Select one of the options:\n";
		cout << "1. Insert key\n";
		cout << "2. Delete key\n";
		cout << "3. Find all keys starting with alphabet\n";
		int opt, num;
		string data;
		char charData;
		cin >> opt;
		switch (opt) {
			case 1:
				cout << "How many inserts: ";
				cin >> num;
				for (int i = 0; i < num; i++) {
					cin >> data;
					trie.insert(data);
				}
				break;
			case 2:
				cout << "Insert key to delete\n";
				cin >> data;
				trie.deleteKey(data);
				break;
			case 3:
				cout << "Please enter the alphabet\n";
				cin >> charData;
				trie.keysWithAlphabet(charData);
				break;
			default:
				quit = true;
				break;
		}
	}
}

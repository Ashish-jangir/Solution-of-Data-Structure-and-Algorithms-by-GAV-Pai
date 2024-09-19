/*
1. Implement a menu-driven demostration of all the functions pertaining to insert, delete and
search operations of B trees of order m
4. Implement functions to traverse a B tree of order m by inorder, preorder and postorder traversals.
Note: Code is not totally accurate. After delete operation childPointers are not totally cleard. So search and delete operation does not work as expected.
*/
#include<iostream>
#include <vector>
#include <stack>
#include <queue>

using std::cin;
using std::cout;
using std::vector;
using std::pair;
using std::stack;
using std::queue;

template <typename T>
class bTree
{
	class Node
	{
		public:
			vector<T> keys;
			vector<Node *> childPointers;
			bool isLeaf;
			Node(T data, bool isLeaf) {
				keys.push_back(data);
				this->isLeaf = isLeaf;
			}
			Node(bool isLeaf) {
				this->isLeaf = isLeaf;
			}
	};
	int order;
	Node* root;

	pair<Node*, int> searchNode(T data) {
		if(root) {
			Node *current = root;
			while(current) {
				for (int i = 0; i < current->keys.size(); i++) {
					if(current->keys[i] == data) {
						return {current, i};
					}
					else if(current->keys[i] > data) {
						current = current->childPointers[i];
						break;
					}
				}
				if(current && current->keys.back() < data) {
					current = current->childPointers.back();
				}
				if(current == nullptr) {
					break;
				}
			}
		}
		return {nullptr, 0};
	}

	public:
	bTree(int order): order(order), root(nullptr) {}

	

	void splitChild(Node* parent, int i, Node* fullChild) {
		int median = (order - 1) / 2;

		Node* newChild = new Node(fullChild->isLeaf);
		for(int j = median + 1; j < fullChild->keys.size(); j++) {
			newChild->keys.push_back(fullChild->keys[j]);
		}
		if(!fullChild->isLeaf) {
			for(int j = median + 1; j <= fullChild->childPointers.size(); j++) {
				newChild->childPointers.push_back(fullChild->childPointers[j]);
			}
		}
		fullChild->keys.resize(median);
		fullChild->childPointers.resize(median + 1);

		parent->childPointers.insert(parent->childPointers.begin() + i + 1, newChild);
		parent->keys.insert(parent->keys.begin() + i, fullChild->keys[median]);
	}

	void insertNonFull(Node* node, T data) {
		int i = node->keys.size() - 1;
		if(node->isLeaf) {
			// Insert the new key into the correct position
			while(i >= 0 && node->keys[i] > data) {
				i--;
			}
			node->keys.insert(node->keys.begin() + i + 1, data);
		} else {
			// Find the correct child to descend
			while(i >= 0 && node->keys[i] > data) {
				i--;
			}
			i++;
			if(node->childPointers[i]->keys.size() == order - 1) {
				// If the child is full, split it
				splitChild(node, i, node->childPointers[i]);
				if(node->keys[i] < data) {
					i++;
				}
			}
			insertNonFull(node->childPointers[i], data);
		}
	}

	void insert(T data) {
		if(!root) {
			root = new Node(data, true); // Create root if it doesn't exist
		} else {
			if(root->keys.size() == order - 1) {
				// If root is full, split it
				Node* newRoot = new Node(false);
				newRoot->childPointers.push_back(root);
				splitChild(newRoot, 0, root);
				int i = (newRoot->keys[0] < data) ? 1 : 0;
				insertNonFull(newRoot->childPointers[i], data);
				root = newRoot;
			} else {
				insertNonFull(root, data);
			}
		}
	}

	void remove(T data) {
		pair<Node*, int> output = {nullptr, 0};
		stack<pair<Node*, int>> s;
		if(root) {
			Node *current = root, *pre = nullptr;
			int i;
			while(current) {
				pre = current;
                bool skip = false;
				for (i = 0; i < current->keys.size(); i++)
				{
					if(current->keys[i] == data) {
						output = {current, i};
						s.push(output);
						current = nullptr;
						break;
					}
					else if(current->keys[i] > data) {
						s.push({current, i});
						current = current->childPointers[i];
                        skip = true;
						break;
					}
				}
                if(skip) continue;
                if( current && i == current->keys.size()) {
                    s.push({current, i});
                    current = current->childPointers.back();
                }
			}
		}

		if(output.first) {
			//check if its children are null or not
			if(output.first->childPointers[output.second] == nullptr && output.first->childPointers[output.second + 1] == nullptr) {
				//both child are null
				output.first->keys.erase(output.first->keys.begin() + output.second);
				output.first->childPointers.erase(output.first->childPointers.begin() + output.second);
				if(output.first->keys.size() == 0) {
					delete(output.first);
					s.pop();
					s.top().first->childPointers[s.top().second] = nullptr;
				}
			}
			else if(output.first->childPointers[output.second] == nullptr && output.first->childPointers[output.second + 1] != nullptr) {
				//only left child is null
				Node *temp = output.first->childPointers[output.second + 1], *pre = nullptr;

				while(temp) {
					s.push({temp, 0});
					pre = temp;
					temp = temp->childPointers[0];
				}
				output.first->keys[output.second] = pre->keys[0];

				pre->keys.erase(pre->keys.begin());
				pre->childPointers.erase(pre->childPointers.begin());
				if(pre->keys.size() == 0) {
					delete(pre);
					s.pop();
					s.top().first->childPointers[s.top().second] = nullptr;
				}
			}
			else if(output.first->childPointers[output.second] != nullptr && output.first->childPointers[output.second + 1] == nullptr) {
				//only right child is null
				Node *temp = output.first->childPointers[output.second], *pre = nullptr;
				while(temp) {
					s.push({temp, temp->childPointers.size() - 1});
					pre = temp;
					temp = temp->childPointers.back();
				}
				output.first->keys[output.second] = pre->keys[0];

				pre->keys.pop_back();
				pre->childPointers.pop_back();
				if(pre->keys.size() == 0) {
					delete(pre);
					s.pop();
					s.top().first->childPointers[s.top().second] = nullptr;
				}
			}
			else {
				//both child are not null
				Node *temp = output.first->childPointers[output.second], *pre = nullptr;
				while(temp) {
					s.push({temp, temp->childPointers.size() - 1});
					pre = temp;
					temp = temp->childPointers.back();
				}
				output.first->keys[output.second] = pre->keys[0];
				pre->keys.erase(pre->keys.begin());
				pre->childPointers.erase(pre->childPointers.begin());
				if(pre->keys.size() == 0) {
					delete(pre);
					s.pop();
					s.top().first->childPointers[s.top().second] = nullptr;
				}
			}
			//now check if node's new size is less then order/2.
			//if yes then check if siblings have elements to spare (have more then order / 2). if yes then move biggest element from sibling to parent and move parent to our node.
			//if sibling don't have element to spare then remaining element from our node is moved to sibling node with intervenig parent
			while(!s.empty()) {	
				Node* top = s.top().first;
				s.pop();
				if(top->keys.size() < order/2) {
					Node *sibling = s.top().first->childPointers[s.top().second - 1 ];
					if(sibling->keys.size() > order/2) {
						int parentData = s.top().first->keys[s.top().second];
						s.top().first->keys[s.top().second] = sibling->keys.back();
						Node *movingChildPointer = sibling->childPointers.back();
						sibling->keys.pop_back();
						sibling->childPointers.pop_back();
						
						top->keys.insert(top->keys.begin(), parentData);
						top->childPointers.insert(top->childPointers.begin(), movingChildPointer);
					}
					else {
						sibling->keys.push_back(s.top().first->keys[s.top().second]);

						s.top().first->keys.erase(s.top().first->keys.begin() + s.top().second);
						s.top().first->childPointers.erase(s.top().first->childPointers.begin() + s.top().second);
						s.top().first->childPointers.erase(s.top().first->childPointers.begin() + s.top().second - 1);

						sibling->childPointers.push_back(top->childPointers[0]);
						top->childPointers.erase(top->childPointers.begin());
						while(top->keys.size() > 0) {
							sibling->keys.push_back(top->keys[0]);
							sibling->childPointers.push_back(top->childPointers[0]);
							top->keys.erase(top->keys.begin());
							top->childPointers.erase(top->childPointers.begin());
						}
						delete(top);
					}
				}
			}
		}
		else {
			cout << "Element is not found in tree!\n";
		}
	}
	
	void search(T data) {
		pair<Node*, int> output = searchNode(data);
		if(output.first) {
			cout << "Element found in the tree\n";
		}
		else {
			cout << "Element is not found in tree\n";
		}
	}
	void print() {
		queue<pair<Node*, int>>q;
		q.push({root, 1});
		while(!q.empty()) {
			Node* current = q.front().first;
			int level = q.front().second;
			q.pop();
			for(int key : current->keys) {
				cout << key << " ";
			}
			for(Node* nodeP : current->childPointers) {
				if(nodeP != nullptr)
					q.push({nodeP, level+1});
			}
			if(level == q.front().second)
				cout << "	||	";
			else
				cout << std::endl;
		}
	}
};

int main()
{
	cout << "Program to construct B tree\n";
	cout << "Please insert order of the B tree: ";
	int order, opt, num;
	int element;
	cin >> order;
	bTree<int> btree(order);
	bool quit = false;
	while(!quit) {
		cout << "Please select one of the below option\n";
		cout << "1. Insert new elements\n";
		cout << "2. Delete elements\n";
		cout << "3. Search element\n";
		cout << "4. Print elements of tree\n";
		cin >> opt;
		switch (opt)
		{
			case 1:
				cout << "How many inserts: ";
				cin >> num;
				cout << "Please insert " << num << " elements to insert in tree\n";
				for (size_t i = 0; i < num; i++)
				{
					cin >> element;
					btree.insert(element);
				}
				break;
			case 2:
				cout << "Please insert element of delete: ";
				cin >> element;
				btree.remove(element);
				break;
			case 3:
				cout << "Please insert element to search in tree: ";
				cin >> element;
				btree.search(element);
				break;
			case 4:
				btree.print();
				break;

			default:
				quit = true;
				break;
		}
	}

	return 0;
}

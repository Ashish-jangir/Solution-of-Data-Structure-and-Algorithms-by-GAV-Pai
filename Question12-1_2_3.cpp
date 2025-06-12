/*
1. Implement a function RB_IMBALANCE(T), which given a red-black tree T would test for the violation of red and black conditions.

2. Execute a menu driven program to insert keys into a initially empty red-black tree. Make use of function RB_IMBALANCE(T) developed in programming assignment 1 to test
for any imbalance. Display the tree after rebalancing it.

3. Implement a program to accept a non-empty red-black tree as input and delete all its leaf nodes. Rebalance the tree after every deletetion and display the rebalanced
tree on the screen.
*/
#include<iostream>
using namespace std;

enum Color { RED, BLACK };

class Node {
public:
    int key;
    Color color;
    Node *left, *right, *parent;

    Node(int key) : key(key), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree {
private:
    Node *root;

    void rotateLeft(Node*&);
    void rotateRight(Node*&);

    void fixInsert(Node*&);
    void fixDelete(Node*&);

    Node* minimum(Node*);
    void transplant(Node*, Node*);
    void deleteNode(Node*);

    void printTreeHelper(Node*, string, bool);

    Node* deleteLeafNodesHelper(Node* node);
public:
    RedBlackTree() : root(nullptr) {}

    void insert(int);
    void deleteLeafNodes();
    void rebalanceAndDisplay();

    bool RB_IMBALANCE();
    bool checkRedViolation(Node*);
    bool checkBlackHeight(Node*, int, int&);
};

// Rotate operations
void RedBlackTree::rotateLeft(Node *&ptr) {
    Node *rightChild = ptr->right;
    ptr->right = rightChild->left;
    if (ptr->right != nullptr)
        ptr->right->parent = ptr;

    rightChild->parent = ptr->parent;

    if (ptr->parent == nullptr)
        root = rightChild;
    else if (ptr == ptr->parent->left)
        ptr->parent->left = rightChild;
    else
        ptr->parent->right = rightChild;

    rightChild->left = ptr;
    ptr->parent = rightChild;
}

void RedBlackTree::rotateRight(Node *&ptr) {
    Node *leftChild = ptr->left;
    ptr->left = leftChild->right;
    if (ptr->left != nullptr)
        ptr->left->parent = ptr;

    leftChild->parent = ptr->parent;

    if (ptr->parent == nullptr)
        root = leftChild;
    else if (ptr == ptr->parent->left)
        ptr->parent->left = leftChild;
    else
        ptr->parent->right = leftChild;

    leftChild->right = ptr;
    ptr->parent = leftChild;
}

// Insertion and Fixing violations
void RedBlackTree::insert(int key) {
    Node *newNode = new Node(key);
    Node *parent = nullptr;
    Node *current = root;

    while (current != nullptr) {
        parent = current;
        if (newNode->key < current->key)
            current = current->left;
        else
            current = current->right;
    }

    newNode->parent = parent;
    if (parent == nullptr)
        root = newNode;
    else if (newNode->key < parent->key)
        parent->left = newNode;
    else
        parent->right = newNode;

    fixInsert(newNode);
}

void RedBlackTree::fixInsert(Node *&ptr) {
    Node *parent = nullptr;
    Node *grandparent = nullptr;

    while (ptr != root && ptr->color == RED && ptr->parent->color == RED) {
        parent = ptr->parent;
        grandparent = parent->parent;

        // Case 1: Parent is left child of grandparent
        if (parent == grandparent->left) {
            Node *uncle = grandparent->right;

            // Case 1.1: Uncle is RED, only recoloring needed
            if (uncle != nullptr && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                ptr = grandparent;
            } else {
                // Case 1.2: Uncle is BLACK, rotation needed
                if (ptr == parent->right) {
                    rotateLeft(parent);
                    ptr = parent;
                    parent = ptr->parent;
                }
                rotateRight(grandparent);
                swap(parent->color, grandparent->color);
                ptr = parent;
            }
        } else { // Case 2: Parent is right child of grandparent (mirror of case 1)
            Node *uncle = grandparent->left;

            // Case 2.1: Uncle is RED, only recoloring needed
            if (uncle != nullptr && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                ptr = grandparent;
            } else {
                // Case 2.2: Uncle is BLACK, rotation needed
                if (ptr == parent->left) {
                    rotateRight(parent);
                    ptr = parent;
                    parent = ptr->parent;
                }
                rotateLeft(grandparent);
                swap(parent->color, grandparent->color);
                ptr = parent;
            }
        }
    }
    root->color = BLACK; // Ensure root is always black
}

// Minimum element in subtree
Node* RedBlackTree::minimum(Node *ptr) {
    while (ptr->left != nullptr)
        ptr = ptr->left;
    return ptr;
}

// Transplanting nodes during deletion
void RedBlackTree::transplant(Node *u, Node *v) {
    if (u->parent == nullptr)
        root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    if (v != nullptr)
        v->parent = u->parent;
}

// Delete node and fix violations
void RedBlackTree::deleteNode(Node *ptr) {
    Node *child = nullptr;
    Node *parent = nullptr;
    Color originalColor = ptr->color;

    if (ptr->left == nullptr) {
        child = ptr->right;
        transplant(ptr, ptr->right);
    } else if (ptr->right == nullptr) {
        child = ptr->left;
        transplant(ptr, ptr->left);
    } else {
        Node *minNode = minimum(ptr->right);
        originalColor = minNode->color;
        child = minNode->right;

        if (minNode->parent == ptr)
            child->parent = minNode;
        else {
            transplant(minNode, minNode->right);
            minNode->right = ptr->right;
            minNode->right->parent = minNode;
        }
        transplant(ptr, minNode);
        minNode->left = ptr->left;
        minNode->left->parent = minNode;
        minNode->color = ptr->color;
    }

    delete ptr;

    if (originalColor == BLACK)
        fixDelete(child);
}

void RedBlackTree::fixDelete(Node *&ptr) {
    while (ptr != root && ptr != nullptr && ptr->color == BLACK) {
        if (ptr == ptr->parent->left) {
            Node *sibling = ptr->parent->right;

            if (sibling != nullptr && sibling->color == RED) {
                sibling->color = BLACK;
                ptr->parent->color = RED;
                rotateLeft(ptr->parent);
                sibling = ptr->parent->right;
            }

            if (sibling != nullptr && (sibling->left == nullptr || sibling->left->color == BLACK) &&
                (sibling->right == nullptr || sibling->right->color == BLACK)) {
                sibling->color = RED;
                ptr = ptr->parent;
            } else {
                if (sibling != nullptr && sibling->right == nullptr || sibling->right->color == BLACK) {
                    sibling->left->color = BLACK;
                    sibling->color = RED;
                    rotateRight(sibling);
                    sibling = ptr->parent->right;
                }
                sibling->color = ptr->parent->color;
                ptr->parent->color = BLACK;
                sibling->right->color = BLACK;
                rotateLeft(ptr->parent);
                ptr = root;
            }
        } else {
            Node *sibling = ptr->parent->left;

            if (sibling != nullptr && sibling->color == RED) {
                sibling->color = BLACK;
                ptr->parent->color = RED;
                rotateRight(ptr->parent);
                sibling = ptr->parent->left;
            }

            if (sibling != nullptr && (sibling->right == nullptr || sibling->right->color == BLACK) &&
                (sibling->left == nullptr || sibling->left->color == BLACK)) {
                sibling->color = RED;
                ptr = ptr->parent;
            } else {
                if (sibling != nullptr && sibling->left == nullptr || sibling->left->color == BLACK) {
                    sibling->right->color = BLACK;
                    sibling->color = RED;
                    rotateLeft(sibling);
                    sibling = ptr->parent->left;
                }
                sibling->color = ptr->parent->color;
                ptr->parent->color = BLACK;
                sibling->left->color = BLACK;
                rotateRight(ptr->parent);
                ptr = root;
            }
        }
    }
    if (ptr != nullptr)
        ptr->color = BLACK;
}

// Utility functions for RB Imbalance check and menu-driven program
bool RedBlackTree::RB_IMBALANCE() {
    if (root == nullptr || root->color == RED) {
        return false;  // An empty tree is balanced
    }

    // Check for Red condition violation: No two consecutive red nodes.
    if (!checkRedViolation(root)) {
        cout << "Red violation detected in the tree!\n";
        return true;  // Red condition violated
    }

    // Check for Black condition violation: Consistent black height.
    int blackHeight = -1;  // Initialize with an invalid value
    if (!checkBlackHeight(root, 0, blackHeight)) {
        cout << "Black height imbalance detected in the tree!\n";
        return true;  // Black condition violated
    }

    return false;  // No imbalance detected
}
bool RedBlackTree::checkRedViolation(Node* node) {
    if (node == nullptr) {
        return true;  // Null nodes are considered black
    }

    // If the current node is red, both children must not be red.
    if (node->color == RED) {
        if ((node->left != nullptr && node->left->color == RED) ||
            (node->right != nullptr && node->right->color == RED)) {
            return false;  // Red violation: two consecutive red nodes
        }
    }

    // Recursively check for red condition violations in the left and right subtrees.
    return checkRedViolation(node->left) && checkRedViolation(node->right);
}
bool RedBlackTree::checkBlackHeight(Node* node, int blackCount, int& blackHeight) {
    if (node == nullptr) {
        // We've reached a leaf node (null pointer), so return true if the current path's black count matches others.
        if (blackHeight == -1) {
            blackHeight = blackCount;  // Set the black height for the first time
        }
        return blackCount == blackHeight;  // Check if the black count matches the established black height
    }

    // Increment blackCount if the current node is black
    if (node->color == BLACK) {
        blackCount++;
    }

    // Check both left and right subtrees recursively
    bool leftCheck = checkBlackHeight(node->left, blackCount, blackHeight);
    bool rightCheck = checkBlackHeight(node->right, blackCount, blackHeight);

    return leftCheck && rightCheck;  // Both subtrees must have the same black height
}
void RedBlackTree::deleteLeafNodes() {
    if (root == nullptr) {
        cout << "Tree is empty, nothing to delete.\n";
        return;
    }
    
    // Call the recursive function to delete leaf nodes
    deleteLeafNodesHelper(root);

    // If the root becomes null after deleting leaf nodes
    if (root == nullptr) {
        cout << "All nodes deleted, tree is empty now.\n";
    } else {
        rebalanceAndDisplay();  // Rebalance and display the tree after deletion
    }
}
// Helper function to recursively delete all leaf nodes
Node* RedBlackTree::deleteLeafNodesHelper(Node* node) {
    if (node == nullptr) {
        return nullptr;
    }

    // If the node is a leaf node
    if (node->left == nullptr && node->right == nullptr) {
        cout << "Deleting leaf node: " << node->key << endl;
        delete node;  // Free the memory
        return nullptr;  // Return nullptr to the parent so it can update the pointer
    }

    // Recursively delete leaf nodes in the left and right subtrees
    node->left = deleteLeafNodesHelper(node->left);
    node->right = deleteLeafNodesHelper(node->right);

    return node;  // Return the current node (after deletion of its children)
}
// Function to display the rebalanced tree
void RedBlackTree::rebalanceAndDisplay() {
    if (root == nullptr) {
        cout << "Tree is empty.\n";
    } else {
        cout << "Current Red-Black Tree structure:\n";
        printTreeHelper(root, "", true);
    }
}
// Helper function to print the tree structure
void RedBlackTree::printTreeHelper(Node *root, string indent, bool last) {
    if (root != nullptr) {
        cout << indent;  // Print the indentation for current node

        if (last) {
            cout << "R----";  // If it's the right child, print this
            indent += "   ";
        } else {
            cout << "L----";  // If it's the left child, print this
            indent += "|  ";
        }

        // Print the current node's key and color (RED or BLACK)
        string color = (root->color == RED) ? "RED" : "BLACK";
        cout << root->key << "(" << color << ")" << endl;

        // Recursively print the left and right subtrees
        printTreeHelper(root->left, indent, false);
        printTreeHelper(root->right, indent, true);
    }
}
int main() {
    RedBlackTree tree;
    pair<bool, Node*> temp;
    int opt, data;
    bool quit = false;
    while(!quit) {
        cout << "Please select one option from below\n";
        cout << "1. Test with RB_IMBALANCE(T)\n";
        cout << "2. insert nodes in tree\n";
        cout << "3. Delete All leaf nodes\n";
        cout << "4. Display Rebalanced tree\n";
        cin >> opt;
        switch (opt)
        {
        case 1:
            tree.RB_IMBALANCE();
            break;
        case 2:
            cout << "How many inserts?\n";
            int n;
            cin >> n;
            cout << "Please insert Integer data to add in element: ";
            for (size_t i = 0; i < n; i++)
            {
                cin >> data;
                tree.insert(data);
            }
            break;
        case 3:
            tree.deleteLeafNodes();
            break;
        case 4:
            tree.rebalanceAndDisplay();
            break;
        default:
            quit = true;
            break;
        }
    }
    return 0;
}

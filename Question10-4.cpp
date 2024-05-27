/*
[Huffman Coding] D Huffman applied binary trees with minimal external
path length to obtain an optimal set of codes for messages 𝑀_j 0 ≤ 𝑗 ≤ 𝑛. Each
message is encoded using a binary string for transmission. At the receiving end,
the messages are decoded using a binary tree in which external nodes represent
messages and the external path to the node represents the binary string encoding of
the message. Thus, if 0 labels a left branch and 1 a right branch, then a sample
decode tree given below can decode messages 𝑀_0 , 𝑀_1 , 𝑀_2 , 𝑀_3 represented using
codes {0, 100, 101, 11}. These codes are called Huffman codes. The expected
decode time is given by ∑_(0 ≤ i ≤ 𝑛) 𝑞_i . 𝑑_i , where 𝑑_i is the distance of the external node
representing message 𝑀_i from the root node and 𝑞_i is the relative frequency with
which the message 𝑀_i is transmitted. It is obvious that the cost of decoding a
message is dependent on the number of bits in the binary code of the message and
hence on the external path to the node representing the message. Therefore, the
problem is to look for a decode tree with minimal weighted external path length to
speed up decoding.
(Refer the figure in book)

i) Investigate the algorithm given by D Huffman to obtain a decode tree with
minimal weighted external path length.
ii) Implement the algorithm given a sample set of weights 𝑞_i .

Note
Weighted external path length: It is the sum of the product of the weight and path length
of each external node in an extended binary tree. The path length is the distance from the
root of the tree to each node, and the weight is associated with each external node.

Tasks:

1. Investigate the algorithm proposed by D. Huffman to construct a decode tree with minimal weighted external path length. This involves
 understanding the steps of the algorithm and its theoretical underpinnings.
2. Implement the algorithm given a sample set of weights 𝑞_i, representing the relative frequencies of messages. The implementation should
 construct a decode tree that minimizes the weighted external path length.

solution 1:
The algorithm mentioned in the assignment is likely referring to the Huffman coding algorithm, which is used to construct a binary tree
 with minimal weighted external path length. Here's a simplified version of the algorithm:

1. Frequency Calculation:
Given a set of messages and their relative frequencies 𝑞_i, calculate the frequency of each message.

2. Priority Queue Initialization:
Create a priority queue (min-heap) of nodes, where each node represents a message and its frequency.
Initially, each node contains a single message and its frequency as weight.

3. Tree Construction:
While there is more than one node in the priority queue:
Remove the two nodes with the lowest frequencies from the priority queue. These nodes will become the left and right children of a new node.
Create a new node whose frequency is the sum of the frequencies of the two removed nodes.
Insert the new node back into the priority queue.

4. Tree Finalization:
The last remaining node in the priority queue is the root of the Huffman tree.

5. Code Assignment:
Traverse the Huffman tree to assign binary codes to each message.
Left branches represent 0 and right branches represent 1.
The binary code for each message is determined by the path from the root to the leaf node representing the message.

6. Decoding:
To decode a binary string, start from the root of the Huffman tree and follow the corresponding branches based on the bits in the string
 until reaching a leaf node, which represents a message.
This algorithm constructs a Huffman tree such that messages with higher frequencies have shorter binary codes, resulting in a minimal
 weighted external path length. This minimizes the overall transmission cost and speeds up decoding.

Solution 2:
*/
#include<iostream>
#include<vector>
#include<queue>
#include<map>
using std::cin;
using std::cout;
using std::string;
using std::vector;
using std::pair;
using std::queue;
using std::map;

template<typename U>
class PriorityQ {
    template <typename T>
    class Node {
        public:
        int priority;
        T data;
        Node* link;
        Node(T data, int priority): data(data), priority(priority), link(NULL) {}
        Node(): priority(0), link(NULL) {}
    };
    Node<U> *front = NULL, *rear = NULL;
    int size = 0;
    public:

    int getSize() {
        return size;
    }
    void enqueue(U data, int priority) {
        Node<U> *node = new Node<U>(data, priority);
        if(front == NULL && rear == NULL) {
            front = node;
            rear = node;
        }
        else {
            if(front == rear) {
                if(priority > front->priority){
                    front = node;
                    node->link = rear;
                }
                else {
                    rear->link = node;
                    rear = node;
                }
            }
            else {
                Node<U> *temp = front, *pre = front;
                while(temp && (priority <= temp->priority)) {
                    pre = temp;
                    temp = temp->link;
                }

                if(temp == front) {
                    front = node;
                }
                else {
                    pre->link = node;
                }
                node->link = temp;

                if(rear == pre) {
                    rear = node;
                }
            }

        }
        size++;
    }
    pair<U, int> dequeue() {
        if(front == NULL && rear == NULL) {
            cout << "Q is empty\n";
            return {NULL, 0};
        }
        else {
            Node<U> *temp = front;
            pair<U, int> data = { temp->data, temp->priority};
            if(front == rear) {
                front = NULL;
                rear = NULL;
            }
            else {
                front = front->link;
            }
            delete(temp);
            size--;
            return data;
        }
    }
};

template<typename N>
class Node {
    public:
    N data;
    bool isLeafNode;
    int freq;
    Node *rchild, *lchild;
    Node(N data, bool isLeaf, int freq): data(data), isLeafNode(isLeaf), freq(freq), rchild(NULL), lchild(NULL) {}
    Node(): rchild(NULL), lchild(NULL) {}
};

map<char, string> mappingTable(Node<char> *root) {
    map<char, string> output;
    queue<pair<Node<char>*, string>> q;
    string bitString = "";
    q.push({root, ""});
    while(!q.empty()) {
        Node<char>*front = q.front().first;
        string bits = q.front().second;
        q.pop();
        Node<char> *left = front->lchild;
        if(left->isLeafNode) {
            output[left->data] = bits + "0";
        }
        else {
            q.push({left, bits + "0"});
        }
        Node<char> *right = front->rchild;
        if(right->isLeafNode) {
            output[right->data] = bits + "1";
        }
        else {
            q.push({right, bits + "1"});
        }
    }
    return output;
}


int main() {
    cout << "Enter the complete Message String: ";
    //Ex. OISDHFUBIEWIUBKJSIHFIUBEBJSBDFUIBIUSDIIDSFUIBSDUFBIUFUISDBDFISDDBF
    string msg;
    cin >> msg;
    vector<char> input;
    for(char ch: msg) {
        input.push_back(ch);
    }
    vector<pair<char, int>> messageFrequncy;
    while(input.size() > 0) {
        char currentChar = input[0];
        pair<char, int> charFreq;
        charFreq.first = currentChar;
        charFreq.second = 1;
        for (size_t j = 1; j < input.size(); j++)
        {
            if(input[j] == currentChar) {
                input.erase(input.begin() + j);
                j--;
                charFreq.second++;
            }
        }
        messageFrequncy.push_back(charFreq);
        input.erase(input.begin());
    }

    PriorityQ<Node<char>*> priorityQ;
    for(pair<char, int> currFreq: messageFrequncy) {
        Node<char> *temp = new Node<char>(currFreq.first, true, currFreq.second);
        temp->isLeafNode = true;
        priorityQ.enqueue(temp, -currFreq.second);
    }

    Node<char> *root = NULL;
    while(priorityQ.getSize() > 1) {
        pair< Node<char>*, int> temp1 = priorityQ.dequeue();
        pair< Node<char>*, int> temp2 = priorityQ.dequeue();

        if(temp1.first == NULL || temp2.first == NULL)
            break;

        Node<char> *temp3 = new Node<char>();
        temp3->freq = temp1.first->freq + temp2.first->freq;
        temp3->lchild = temp1.first;
        temp3->rchild = temp2.first;
        temp3->isLeafNode = false;
        priorityQ.enqueue(temp3, -temp3->freq);
        root = temp3;
    }

    map<char, string> mapping = mappingTable(root);

    cout << "Bit string: ";
    string output = "";
    for(char ch: msg) {
        output += mapping[ch];
    }
    cout << output;

    cout << "\nOutput: ";
    Node<char> *control = root;
    for(char ch: output) {
        if(ch == '0') {
            control = control->lchild;
            if(control->isLeafNode) {
                cout << control->data;
                control = root;
            }
        }
        else {
            control = control->rchild;
            if(control->isLeafNode) {
                cout << control->data;
                control = root;
            }
        }   
    }

    return 0;
}

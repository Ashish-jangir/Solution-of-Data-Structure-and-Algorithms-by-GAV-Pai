//Develop a program to implement a Queue List (Refer Illustrative Problem 7.10) which is a
//list of linked queues stored according to an order of priority.
//Test for the insertion and deletion of the following jobs with their priorities listed within
//brackets, on a Queue List JOB_MANAGER with three queues A, B and C listed according
//to their order of priorities:
#include<iostream>

class QueueNode;
class LeadNode;

class QueueNode {
    public:
    QueueNode* link;
    char data;
    QueueNode() {
        link = NULL;
        data = '*';
    }
};

class LeadNode {
    public:
    QueueNode* down;
    char lead_data;
    LeadNode* follow;
    LeadNode() {
        down = NULL;
        lead_data = '*';
        follow = NULL;
    }
} headNode;


void insertJob(char job, char priority) {
    if(headNode.follow == NULL) {
        LeadNode* ln = new LeadNode();
        headNode.follow = ln;
        QueueNode* qn = new QueueNode();
        qn->data = job;
        ln->down = qn;
        ln->lead_data = priority;
    }
    else {
        LeadNode* temp = headNode.follow;
        bool foundPriority = false;
        LeadNode* rear;
        while(temp != NULL) {
            if(temp->lead_data == priority) {
                foundPriority = true;
                if(temp->down == NULL) {
                    QueueNode* qn = new QueueNode();
                    qn->data = job;
                    temp->down = qn;        
                }
                else {
                    QueueNode* qn = new QueueNode();
                    QueueNode* rear = temp->down;
                    while(rear->link != NULL) {
                        rear = rear->link;
                    }
                    qn->data =  job;
                    rear->link = qn;
                }
                break;
            }
            rear = temp;
            temp = temp->follow;
        }
        if(!foundPriority) {
            LeadNode* ln = new LeadNode();
            rear->follow = ln;
            QueueNode* qn = new QueueNode();
            qn->data = job;
            ln->down = qn;
            ln->lead_data = priority;
        }
    }
}

void deleteJob(char priority) {
    LeadNode* temp = headNode.follow;
    bool foundPriority = false;
    while(temp != NULL) {
        if(temp->lead_data == priority) {
            foundPriority = true;
            QueueNode* temp2 = temp->down;
            temp->down = temp->down->link;
            char job = temp2->data;
            delete(temp2);
            std::cout << "Job " << job << " have been deleted successfully." << std::endl;
        }
        temp = temp->follow;
    }
    if(!foundPriority) {
        std::cout << "There are no jobs exist with this priority" << std::endl;
    }
}

void displayQueueList() {
    if(headNode.follow == NULL) {
        std::cout << "The Queue list is empty!" << std::endl;
    } else {
        LeadNode* temp = headNode.follow;
        std::cout << "Queue List:" << std::endl;
        while(temp != NULL) {
            std::cout << temp->lead_data << "   |   ";
            QueueNode* temp2 = temp->down;
            while(temp2 != NULL) {
                std::cout << temp2->data << "   ";
                temp2 = temp2->link;
            }
            std::cout << std::endl;
            temp = temp->follow;
        }
    }
}

int main() {
    while(true) {
        char job, priority;
        char opt;
        std::cout << "Please select 1 to insert, 2 to delete a job from Queue list and Q/q to exit the program: ";
        std::cin >> opt;
        if(opt == '1') {
            std::cout << "Please enter no. of elements to insert: ";
            int num;
            std::cin >> num;
            std::cout<< "Please enter job character and job priority: ";
            for(int i = 0; i < num; i++) {
                std::cin >> job >> priority;
                insertJob(job, priority);
            }
        }
        else if(opt == '2') {
            std::cout << "Please enter the priority from which you want to delete the element: ";
            std::cin >> priority;
            deleteJob(priority);
        }
        else if( opt == 'q' || opt == 'Q') {
            break;
        }
    }
    displayQueueList();
    return 0;

}
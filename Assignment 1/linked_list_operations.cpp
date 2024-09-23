#include <iostream>
#include <string>


using namespace std;

struct Node {
    int task_id;
    string description;
    int priority;
    Node *next;

    Node(int tid, string description, int priority){
        this->task_id = tid;
        this->description = description;
        this->priority = priority;
        this->next = NULL;
    }
};


class TaskManagementSystem {
    public:
    Node *head = NULL;

    void insert_task(int tid, string description, int priority){
        if (task_exists(tid)) {
            cout << "Task already exists with ID: " << tid << endl;
            return;
        }

        Node *task = new Node(tid, description, priority);

        if (this->head == NULL){
            this->head = task;
            return;
        }

        if (this->head->priority < priority) {
            task->next = this->head;
            this->head = task;
            return;
        }

        Node *current = this->head;
        // loop as long as we have a high priority task.
        while (current->next != NULL && current->next->priority >= priority){
            current = current->next;
        }
        // Now we have a Node after which we have to insert a Node keeping rest of Task list intact
        task->next = current->next;
        current->next = task;
    }

    void print_tasks(){
        cout << "--------------------------------------" << endl;
        Node *current = this->head;
        while (current != NULL){
            cout << current->task_id << ": " << current->description << " - " << current->priority << endl;
            current = current->next;
        }
        cout << "--------------------------------------" << endl;
    }

    void delete_from_start(){
        if (this->head == NULL) {
            cout << "Empty task list" << endl;
            return;
        }
        Node *temp = this->head;
        this->head = temp->next;
        delete temp;
    }

    bool task_exists(int tid) {
        Node *current = this->head;
        while (current != NULL) {
            if (current->task_id == tid){
                return true;
            }
            current = current->next;
        }

        return false;
    }

    void delete_task_using_id(int tid){
        if (this->head == NULL) {
            cout << "Task list is empty. Nothing to delete." << endl;
            return;
        }

        if (this->head->task_id == tid) {
            Node *temp = this->head;
            this->head = temp->next;
            delete temp;
            return;
        }

        Node *current = this->head;
        // we will stop one node before target node
        while (current->next != NULL && current->next->task_id != tid) {
            current = current->next;
        }

        if (current->next != NULL) {
            Node *temp = current->next;
            current->next = temp->next;
            delete temp;
        } else {
            cout << "Task with ID " << tid << " not found." << endl;
        }
    }


};


int main()
{
    TaskManagementSystem tms;
    int choice;
    int tid, priority;
    string description;

    do {
        cout << "\nTask Management System Menu:\n";
        cout << "1. Add a new task\n";
        cout << "2. View all tasks\n";
        cout << "3. Remove the highest priority task\n";
        cout << "4. Remove a task by ID\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                cout << "Enter task ID: ";
                cin >> tid;
                cout << "Enter task description: ";
                cin.ignore();
                getline(cin, description);
                cout << "Enter task priority: ";
                cin >> priority;
                tms.insert_task(tid, description, priority);
                break;
            case 2:
                tms.print_tasks();
                break;
            case 3:
                tms.delete_from_start();
                break;
            case 4:
                int tidToDelete;
                cout << "Enter the task ID to delete: ";
                cin >> tidToDelete;
                tms.delete_task_using_id(tidToDelete);
                break;
            case 5:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

    } while (choice != 5);

    return 0;
}
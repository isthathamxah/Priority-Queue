#include <iostream>
#include <fstream>
#include<string>
using namespace std;


class Role 
{
private:
    string id;
    int priority;

public:
    Role(); 
    Role(string ID);  
    void setPriority();
    string getId();
    int getPriority();
};


Role::Role() {}

Role::Role(string ID)
{
    id = ID;
    setPriority();
}


void Role::setPriority()
{
    if (id[0] == 'P' || id[0] == 'p')
        priority = 1;  
    else if (id[0] == 'T' || id[0] == 't')
        priority = 2;  
    else
        priority = 3;  
}


string Role::getId() 
{
    return id;
}

int Role::getPriority()
{
    return priority;
}


class Queue {
private:
    int front, rear, size, maxSize;
    Role* queue;

public:
    Queue(int capacity);
    ~Queue();

    bool isEmpty();
    bool isFull();

    void enqueue(Role p);
    Role dequeue();
    void display();
};


Queue::Queue(int capacity) 
{
    maxSize = capacity;
    queue = new Role[maxSize];
    front = 0;
    rear = -1;
    size = 0;
}

Queue::~Queue()
{
    delete[] queue;
}

bool Queue::isEmpty()
{
    return size == 0;
}

bool Queue::isFull()
{
    return size == maxSize;
}

void Queue::enqueue(Role p)
{
    if (isFull()) {
        cout << "Queue is full!\n";
        return;
    }

    if (isEmpty())
    {
        front = rear = 0;
        queue[rear] = p;
    }
    else {
        int i = rear;

        while (i >= front && queue[i].getPriority() > p.getPriority())
        {
            queue[(i + 1) % maxSize] = queue[i];
            i = (i - 1 + maxSize) % maxSize;
        }

        queue[(i + 1) % maxSize] = p;
        rear = (rear + 1) % maxSize;
    }

    size++;
}


Role Queue::dequeue() 
{
    if (isEmpty())
    {
        cout << "Queue is empty!\n";
        return Role();
    }
    Role temp = queue[front];
    front = (front + 1) % maxSize;
    size--;
    return temp;
}

void Queue::display()
{
    if (isEmpty()) {
        cout << "Queue is empty!\n";
        return;
    }
    int i = front;
    while (true) {
        cout << queue[i].getId() << " ";
        if (i == rear) break;
        i = (i + 1) % maxSize;
    }
    cout << endl;
}


void readFile(string filename, Queue& q)
{
    ifstream file(filename);
    if (!file) {
        cout << "File not found!\n";
        return;
    }

    string id;
    while (file >> id) {
        q.enqueue(Role(id));
    }
    file.close();
}

int main()
 {
    Queue s(20);

    readFile("data.txt", s);

    cout << "Priority Queue Output:\n";
    s.display();

    return 0;
}

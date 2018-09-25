#include<iostream>
#include<string>

using namespace std;

struct Node {
	string name;
	int processTime;
	Node * next;
	bool bDelete;
};

void showElapsedTime(const int elapsedTime);
void burstNodeTime(Node * item, int & elapsedTime, const int queueTime);
void showQueueTime(int & time);
void pushBack(Node *& cabeza, Node *& item);
Node * createNode(const string name, const int processTime, int nodeNumber);
Node popFront(Node *& cabeza);

int main() 
{
	
	return 0;
}

void showElapsedTime(const int elapsedTime) 
{
	cout << "\nTiempo transcurrido: "<<elapsedTime<<" /s"; 
}

void burstNodeTime(Node * item, int & elapsedTime, const int queueTime) 
{
	if (queueTime >= item->processTime)
	{
		elapsedTime += item->processTime;
		item->bDelete = true;
	}
	else 
	{
		item->processTime -= queueTime;
		elapsedTime += queueTime;
	}
}

void showQueueTime(int & time) 
{
	cout << "\nTiempo Quantum: " << time << " /s";
}


void pushBack(Node *& cabeza, Node *& item) {
	if (!cabeza) 
		cabeza = item;
	else
	{
		Node * aux = cabeza;
		while (aux->next != cabeza) 
			aux = aux->next;
		aux->next = item;
	}
	item->next = cabeza;
}

Node popFront(Node *& cabeza) 
{
	Node * aux = cabeza;
	Node front = *cabeza;

	if (!cabeza) 
	{
		if (aux->next != cabeza)
		{
			cabeza = aux->next;
			while (aux->next != cabeza)
				aux = aux->next;
			aux->next = cabeza;
		}
		delete aux;
	}
	return front;
}

Node * createNode(const string name, const int processTime, int nodeNumber)
{
	Node * nuevo = (Node *)malloc(sizeof(Node));
	nuevo->bDelete = false;
	nuevo->next = NULL;
	nuevo->processTime = processTime;
	nuevo->name = "Process #" + nodeNumber;
	return nuevo;
}

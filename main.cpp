#include<iostream>
#include<string>

using namespace std;

struct Node {
	int id;
	string name;
	int processTime;
	Node * next;
	bool bDelete;
};

void showElapsedTime(const int elapsedTime);
void burstNodeTime(Node * item, int & elapsedTime, const int queueTime);
void showQueueTime(int & time);
void pushBack(Node *& lista);
Node * popFront(Node *& lista);

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

void showQueueTime(int & time) {
	cout << "\nTiempo Quantum: " << time << " /s";
}

void pushBack(Node *& lista) {
	//TODO
}

Node * popFront(Node *& lista) {
	//TODO
}
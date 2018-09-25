#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>

using namespace std;

struct Node {
	int processTime;
	int nodeArrival;
	Node * next;
	bool bDelete;
};

void showElapsedTime(const int elapsedTime);
void showList(Node * cabeza, Node * fin, bool useNames = false);
void burstNodeTime(Node * item, int & elapsedTime, const int queueTime);
void showQueueTime(int & time);
void initializeSimulation(Node *& cabeza, Node *& fin, const int quantumTime, int & elapsedTime, int & nNodos);
void pushBack(Node *& cabeza, Node *& fin , Node *& item);
Node * createNode(const int processTime, int nodeNumber);
Node * popFront(Node *& cabeza, Node *& fin);

int mainMenu()
{
	int temp = -1;
	printf("\n	PROGRAMA ROUND ROBIN\n	1. Ingresar Quantum	\n	2. Ingresar procesos	\n	3. Simular	\n	0. Salir\n	Seleccion: ");
	cin >> temp;
	if (cin.fail())
	{
		cin.clear();
		cin.ignore();
	}
	return temp;
}

bool seguirIngresando()
{
	char temp = '0';
	do {
		printf("\n	Desea seguir ingresando procesos (Y/N)?	");
		scanf(" %c", &temp);
		switch (temp)
		{
		case 'Y':
			return true;
		case 'N':
			return false;
		}
	} while (temp != 'Y' || temp != 'N');
}

int pedirNumero(int minNumero)
{
	int num = 0;
	do {
		cin.clear();
		cin.ignore(256,'\n');
		printf("\n	Ingrese numero: ");
		cin >> num;
	} while (cin.fail() || num < minNumero);
	return num;
}

int main() 
{
	Node * cabeza = NULL;
	Node * fin = NULL;
	int op = '0';
	int nNodos = 0;
	int elapsedTime = 0;
	int queueTime = 0;

	do {
		system("CLS");
		if (cabeza || queueTime > 0 || elapsedTime) {
			printf("\n	============ PARAMETROS LISTA ROUND ROBBIN ============	\n\n");
			if (queueTime > 0)
				showQueueTime(queueTime);			
			if (elapsedTime > 0)
				showElapsedTime(elapsedTime);
			if (cabeza)
			{
				cout << "\n	====== Lista de procesos ======\n\n";
				showList(cabeza, fin);
				cout << "\n\n	====== Fin Lista procesos ======\n\n";
			}
			printf("\n	============ FIN PARTAMETROS ROUND ROBIN ============	\n\n");
		}
		switch (op = mainMenu())
		{
		case 1:
			cout << "	Ingrese tiempo de procesamiento Quantum. ";
			queueTime = pedirNumero(1);
			break;
		case 2:
		{
			cout << "	Ingrese tiempo de nuevo proceso. ";
			Node * item = createNode(pedirNumero(1), ++nNodos);
			pushBack(cabeza, fin, item);
		}
			break;
		case 3:
			initializeSimulation(cabeza, fin, queueTime, elapsedTime, nNodos);
			break;
		}
		printf("\n");
		system("PAUSE");
	} while (op != 0);
	return 0;
}

void initializeSimulation(Node *& cabeza, Node *& fin, const int quantumTime, int & elapsedTime, int & nNodos) {
	
	if (quantumTime <= 0)
	{
		cout << "\n	Debe ingresar un timepo para procesar Quantum.\n	";
		return;
	}

	if (cabeza)
	{
		printf("\n	========================	\n");
		showList(cabeza, fin, true);
		printf("\n	========================	\n");
	}
	else {
		cout << "\n	No existen procesos a simular.\n";
	}
	while (nNodos > 0 && cabeza)
	{
		burstNodeTime(cabeza, elapsedTime, quantumTime);
		Node * front = popFront(cabeza, fin);
		if (front)
		{
			if (front->bDelete)
			{
				delete front;
				nNodos--;
			}
			else
				pushBack(cabeza, fin, front);
			if (cabeza)
			{
				printf("\n	========================	\n");
				showList(cabeza, fin, true);
				printf("\n	========================	\n");
			}
		}
	}
}

void showList(Node * cabeza, Node * fin, bool useNames) {
	Node * aux = cabeza;
	bool continuar = true;
	while (continuar && cabeza)
	{
		if (useNames)
			cout << "	" << "P" << aux->nodeArrival << "(";
		else
			cout << "	";
		cout << aux->processTime;
		if (useNames)
			cout << ")	";
		else
			cout << "	";
		if (aux == fin)
			continuar = false;
		aux = aux->next;
	}
}

void showElapsedTime(const int elapsedTime) 
{
	cout << "\n	Tiempo transcurrido (Ultima simulacion): "<<elapsedTime<<" /s\n"; 
}

void burstNodeTime(Node * item, int & elapsedTime, const int queueTime) 
{
	if (item)
		if (queueTime >= item->processTime)
		{
			elapsedTime += item->processTime;
			item->processTime = 0;
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
	cout << "\n	Tiempo Quantum: " << time << " /s\n";
}


void pushBack(Node *& cabeza, Node *& fin, Node *& item)
{
	if (!cabeza){
		cabeza = item;
		fin = item;
	}
	else
	{
		fin->next = item;
		fin = item;
	}
	item->next = cabeza;
}

Node * popFront(Node *& cabeza, Node *& fin)
{
	Node * aux = cabeza;

	if (cabeza) 
	{
		if (cabeza == fin)
		{
			cabeza = NULL;
			fin = NULL;
			return aux;
		}
		cabeza = aux->next;
		fin->next = cabeza;
	}

	return aux;
}

Node * createNode(const int processTime, int nodeNumber)
{
	Node * nuevo = (Node *)malloc(sizeof(Node));
	nuevo->bDelete = false;
	nuevo->next = NULL;
	nuevo->nodeArrival = nodeNumber;
	nuevo->processTime = processTime;
	return nuevo;
}

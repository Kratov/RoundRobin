#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>

using namespace std;

struct Node {
	int processTime;
	Node * next;
	bool bDelete;
};

void showElapsedTime(const int elapsedTime);
void showList(Node * cabeza, Node * fin);
void burstNodeTime(Node * item, int & elapsedTime, const int queueTime);
void showQueueTime(int & time);
void initializeSimulation(Node *& cabeza, Node *& fin, const int quantumTime, int & elapsedTime, int & nNodos);
void pushBack(Node *& cabeza, Node *& fin , Node *& item);
Node * createNode(const int processTime, int nodeNumber);
Node * popFront(Node *& cabeza, Node *& fin);

char mainMenu()
{
	char temp = '0';
	printf("\n	PROGRAMA ROUND ROBIN\n	1. Ingresar Quantum	\n	2. Ingresar procesos	\n	3. Simular	\n	0. Salir\n	Seleccion: ");
	scanf(" %c", &temp);
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

int pedirNumero()
{
	int num = 0;
	do {
		cin.clear();
		cin.ignore();
		printf("\n	Ingrese numero: ");
		cin >> num;
	} while (cin.fail() || num < 0);
	return num;
}

int main() 
{
	Node * cabeza = NULL;
	Node * fin = NULL;
	char op = '0';
	int nNodos = 0;
	int elapsedTime = 0;
	int queueTime = 0;

	do {
		system("CLS");
		if (cabeza) {
			printf("\n	============ PARAMETROS LISTA ROUND ROBBIN ============	\n\n");
			showQueueTime(queueTime);
			showElapsedTime(elapsedTime);
			cout << "\n	====== Lista ======\n\n";
			showList(cabeza, fin);
			cout << "\n\n	====== Fin Lista ======\n\n";
			printf("\n	============ FIN PARTAMETROS ROUND ROBIN ============	\n\n");
		}
		switch (op = mainMenu())
		{
		case '1':
			cout << "	Ingrese tiempo de procesamiento Quantum. ";
			queueTime = pedirNumero();
			break;
		case '2':
		{
			cout << "	Ingrese tiempo de nuevo proceso. ";
			Node * item = createNode(pedirNumero(), ++nNodos);
			pushBack(cabeza, fin, item);
		}
			break;
		case '3':
			initializeSimulation(cabeza, fin, queueTime, elapsedTime, nNodos);
			break;
		case '4':
			printf("\n	============ POSTORDER ============	\n\n");
			
			printf("\n\n	============ FIN POSTORDER ============	\n\n");
			break;
		}
		printf("\n");
		system("PAUSE");
	} while (op != '0');
	system("PAUSE");
	return 0;
}

void initializeSimulation(Node *& cabeza, Node *& fin, const int quantumTime, int & elapsedTime, int & nNodos) {
	printf("\n	========================	\n");
	showList(cabeza, fin);
	printf("\n	========================	\n");
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
				showList(cabeza, fin);
				printf("\n	========================	\n");
			}
		}
	}
}

void showList(Node * cabeza, Node * fin) {
	Node * aux = cabeza;
	bool continuar = true;
	while (continuar && cabeza)
	{
		cout <<"	" << aux->processTime << "	";
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
	nuevo->processTime = processTime;
	return nuevo;
}

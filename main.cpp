
#include<iostream>
#include<string>
#include<stdlib.h>
#include<windows.h>
using namespace std;

const int MIN_NUMBER = 1;

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
void copyList(Node *& cabezaOri, Node *& finOri, Node *& cabezaDest, Node *& finDest);
void freeList(Node *& cabeza, Node *& fin);
Node * createNode(const int processTime, int nodeNumber);
Node * popFront(Node *& cabeza, Node *& fin);

int mainMenu()
{
	int temp = -1;
	printf("\n	PROGRAMA ROUND ROBIN\n	1. Ingresar Quantum	\n	2. Ingresar procesos \n	3. Limpiar lista	\n	4. Simular	\n	0. Salir\n	Seleccion: ");
	cin >> temp;
	if (cin.fail())
	{
		cin.clear();
		cin.ignore();
	}
	return temp;
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
	Node * cabeza, *fin, *cabezaCopia, *finCopia;
	cabeza = fin = cabezaCopia = finCopia = NULL;
	int op, elapsedTime, nNodos, nNodosCopia, queueTime;
	elapsedTime = nNodos = nNodosCopia = queueTime = op = 0;

	do {
		system("CLS");
		if (cabeza || queueTime >= MIN_NUMBER || elapsedTime) {
			printf("\n	============ PARAMETROS LISTA ROUND ROBBIN ============	\n\n");
			if (queueTime >= MIN_NUMBER)
				showQueueTime(queueTime);			
			if (elapsedTime >= MIN_NUMBER)
				showElapsedTime(elapsedTime);
			if (cabeza)
			{
				cout << "\n	====== Lista de procesos ======\n\n";
				showList(cabeza, fin, true);
				cout << "\n\n	====== Fin Lista procesos ======\n\n";
			}
			printf("\n	============ FIN PARTAMETROS ROUND ROBIN ============	\n\n");
		}
		switch (op = mainMenu())
		{
		case 1:
			cout << "	Ingrese tiempo de procesamiento Quantum. ";
			queueTime = pedirNumero(MIN_NUMBER);
			break;
		case 2:
		{
			cout << "	Ingrese tiempo de nuevo proceso. ";
			Node * item = createNode(pedirNumero(MIN_NUMBER), ++nNodos);
			pushBack(cabeza, fin, item);
		}
			break;
		case 3:
			nNodos = 0;
			freeList(cabeza, fin);
			break;
		case 4:
			freeList(cabezaCopia, finCopia);
			copyList(cabeza, fin, cabezaCopia, finCopia);
			initializeSimulation(cabezaCopia, finCopia, queueTime, elapsedTime = 0, nNodosCopia = nNodos);
			break;
		}
		printf("\n");
		system("PAUSE");
	} while (op != 0);
	return 0;
}

void initializeSimulation(Node *& cabeza, Node *& fin, const int quantumTime, int & elapsedTime, int & nNodos) {
	system("cls");	
	if (quantumTime <= 0)
	{
		cout << "\n	Debe ingresar un tiempo para procesar Quantum.\n	";
		return;
	}

	if (cabeza)
	{
		cout << "Simulacion iniciada";
		printf("\n	====== Procesando elementos ======	\n");
		showList(cabeza, fin, true);					
		printf("\n	==================================	\n");
		Sleep(1500);
		system("cls");
	}
	else {
		cout << "\n	No existen procesos a simular.\n";
	}

	while (nNodos > 0 && cabeza)
	{
		burstNodeTime(cabeza, elapsedTime, quantumTime); //Restar cuantum a cabeza
		if (Node * front = popFront(cabeza, fin)) //Extraer el nodo de la cabeza
		{
			if (front->bDelete)   //Si el nodo bDelete = true elimino el nodo
			{
				delete front;
				nNodos--; //Redusco el contador de nodos
			}
			else
				pushBack(cabeza, fin, front);  //Si no es verdadero todo el nodo y lo ingreso a la cola
			if (cabeza)
			{
				cout << "Simulacion iniciada";
				printf("\n	====== Procesando elementos ======	\n");
				showList(cabeza, fin, true);			
		 		//Imprmimo lista despues de modificar
				printf("\n	==================================	\n");
				Sleep(1500);
				system("cls");
			}
		}
	}
	cout << "Simulacion terminada";
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

	if (cabeza == fin)
	{
		cabeza = NULL;
		fin = NULL;
	}

	if (cabeza) 
	{
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

void copyList(Node *& cabezaOri, Node *& finOri, Node *& cabezaDest, Node *& finDest) {
	Node * aux = cabezaOri;
	Node * nuevo = NULL;
	bool continuar = true;
	while (continuar && aux) {
		nuevo = createNode(aux->processTime, aux->nodeArrival);
		pushBack(cabezaDest, finDest, nuevo);
		if (aux == finOri)
			continuar = false;
		aux = aux->next;
	}
}

void freeList(Node *& cabeza, Node *& fin ) {
	while (cabeza) 
		delete popFront(cabeza, fin);
}

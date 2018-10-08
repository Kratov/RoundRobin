#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<iomanip>
#include<string>
#include<stdlib.h>
#include<stdio.h>
#include<windows.h>


using namespace std;

struct Node {
	int processTime;
	int nodeArrival;
	Node * next;
	bool bDelete;
};

void showElapsedTime(const int elapsedTime);
void showList(Node * cabeza, Node * fin, int startBorderOffset, const int itemSeparation, const int endBorderDifference, const bool useOffsetJump);
void burstNodeTime(Node * item, int & elapsedTime, const int queueTime);
void showQueueTime(const int time);
void initializeSimulation(Node *& cabeza, Node *& fin, const int quantumTime, int & elapsedTime, int & nNodos);
void pushBack(Node *& cabeza, Node *& fin, Node *& item);
void copyList(Node *& cabezaOri, Node *& finOri, Node *& cabezaDest, Node *& finDest);
void freeList(Node *& cabeza, Node *& fin);
void moveCursor(const int x, const int y);
void moveCursor(COORD pos);
void setWindowSize(int width, int height, int left, int top);
void setWindowSize(int width, int height);
void setWindowAttribute(int option);
void showSuccess(string message, COORD pos);
void showSuccess(string message, int x, int y);
void showInfo(string message, COORD pos);
void showInfo(string message, int x, int y);
void showError(string message, COORD pos);
void showError(string message, int x, int y);
COORD getConsoleCenter();
COORD getCursorPosition();
RECT getConsoleRect();
CONSOLE_SCREEN_BUFFER_INFO getConsoleBufferInfo();
Node * createNode(const int processTime, int nodeNumber);
Node * popFront(Node *& cabeza, Node *& fin);

const int MIN_NUMBER = 1;
const int MAX_NODES = 100;
const int MAX_RIGHT_BORDER = 170;
const int MIN_LEFT_BORDER = 40;
const int ITEM_SEPARATION = 10;
const int CONSOLE_BASE_ATTRIB = 10;
const int WIN_HEIGHT = GetSystemMetrics(SM_CYSCREEN);
const int WIN_WIDTH = GetSystemMetrics(SM_CXSCREEN);
const int SLEEP_ANIMATION = 1000;

int mainMenu(bool & error, int yAxisStart)
{
	int temp = -1;
	setWindowAttribute(CONSOLE_BASE_ATTRIB | FOREGROUND_INTENSITY);
	COORD center = getConsoleCenter();
	COORD cursorPos;
	center.X -= 10;
	moveCursor(center.X - 30, yAxisStart); printf("=================================================================================");
	moveCursor(center.X - 30, getCursorPosition().Y + 1); printf("  ______   _____  _     _ __   _ ______     ______   _____  ______  _____ __   _");
	moveCursor(center.X - 30, getCursorPosition().Y + 1); printf(" |_____/  |     | |     | | \\  | |     \\   |_____/  |     | |_____]   |   | \\  |");
	moveCursor(center.X - 30, getCursorPosition().Y + 1); printf(" |    \\_  |_____| |_____| |  \\_| |_____/   |    \\_  |_____| |_____] __|__ |  \\_|");
	moveCursor(center.X - 30, getCursorPosition().Y + 2); printf("=================================================================================");
	moveCursor(center.X - 23, getCursorPosition().Y + 2); printf("Authors: Jaime Enrique Zamora Munar, William Andres Garcia Robayo - V1.0");
	moveCursor(center.X, getCursorPosition().Y + 2); printf("Menu:");
	moveCursor(center.X, getCursorPosition().Y + 2); printf("1. Ingresar Quantum");
	moveCursor(center.X, getCursorPosition().Y + 2); printf("2. Ingresar procesos");
	moveCursor(center.X, getCursorPosition().Y + 2); printf("3. Limpiar lista");
	moveCursor(center.X, getCursorPosition().Y + 2); printf("4. Simular");
	moveCursor(center.X, getCursorPosition().Y + 2); printf("0. Salir");
	moveCursor(center.X, getCursorPosition().Y + 2); printf("Seleccion: ");
	cursorPos = getCursorPosition();
	moveCursor(cursorPos.X, getCursorPosition().Y); cin >> setw(1) >> temp;
	if (cin.fail())
	{
		cin.clear();
		cin.ignore(256, '\n');
		showError("Error de tipo de dato, ingrese de nuevo.", center.X - 10, getCursorPosition().Y + 2);
		error = true;
	}
	return temp;
}

bool pedirNumero(int minNumero, int & num)
{
	COORD center = getConsoleCenter();
	center.X -= 10;
	moveCursor(center.X, getCursorPosition().Y + 2); printf("Ingrese numero: ");
	cin >> num;
	if (cin.fail())
	{
		cin.clear();
		cin.ignore(256, '\n');
		showError("Tipo de dato erroneo - intentelo de nuevo.", center.X - 15, getCursorPosition().Y + 3);
		return false;
	}
	return true;
}

int main()
{
	bool inputFail = false;
	Node * cabeza, *fin, *cabezaCopia, *finCopia;
	cabeza = fin = cabezaCopia = finCopia = NULL;
	int op, elapsedTime, nNodos, nNodosCopia, queueTime, nAuxiliar;
	elapsedTime = nNodos = nNodosCopia = queueTime = op = nAuxiliar = 0;
	setWindowSize(WIN_WIDTH, WIN_HEIGHT, getConsoleBufferInfo().srWindow.Left, getConsoleBufferInfo().srWindow.Top);
	COORD center = getConsoleCenter();
	center.X -= 10;
	do {
		inputFail = false;
		system("CLS");
		if (cabeza || queueTime >= MIN_NUMBER || elapsedTime) {
			setWindowAttribute(14 | BACKGROUND_BLUE | FOREGROUND_INTENSITY);
			moveCursor(center.X - 35, getCursorPosition().Y + 2); printf("================================= PARAMETROS LISTA ROUND ROBBIN =================================");
			if (queueTime >= MIN_NUMBER)
				showQueueTime(queueTime);
			if (elapsedTime >= MIN_NUMBER)
				showElapsedTime(elapsedTime);
			if (cabeza)
			{
				moveCursor(center.X - 35, getCursorPosition().Y + 2); cout << "======================================= Lista de procesos =======================================";
				showList(cabeza, fin, MIN_LEFT_BORDER, ITEM_SEPARATION, MAX_RIGHT_BORDER, true);
				moveCursor(center.X - 35, getCursorPosition().Y + 2); cout << "======================================= Fin Lista procesos =======================================";
			}
			moveCursor(center.X - 35, getCursorPosition().Y + 2); printf("================================== FIN PARTAMETROS ROUND ROBIN ==================================");
			setWindowAttribute(CONSOLE_BASE_ATTRIB | FOREGROUND_INTENSITY);
		}
		switch (op = mainMenu(inputFail, getCursorPosition().Y + 2))
		{
		case 1:
		{
			COORD center = getConsoleCenter();
			center.X -= 10;
			moveCursor(center.X - 15, getCursorPosition().Y + 2); cout << "	========================================= ";
			moveCursor(center.X - 15, getCursorPosition().Y + 2); cout << "	Usted ingreso la opcion 1 (Ingreso Quantum):";
			moveCursor(center.X - 15, getCursorPosition().Y + 2); cout << "	========================================= ";
			moveCursor(center.X - 15, getCursorPosition().Y + 2); cout << "	Ingrese tiempo de procesamiento Quantum. ";
			pedirNumero(MIN_NUMBER, queueTime);
		}
		break;
		case 2:
		{
			COORD center = getConsoleCenter();
			center.X -= 10;
			if (nNodos >= MAX_NODES) {
				showError("No puede ingresar mas procesos.", getConsoleCenter().X - 20, getCursorPosition().Y + 2);
				cin.ignore();
				cin.get();
			}
			else
			{
				moveCursor(center.X - 15, getCursorPosition().Y + 2); cout << "	========================================= ";
				moveCursor(center.X - 15, getCursorPosition().Y + 2); cout << "	Usted ingreso la opcion 2 (Ingreso Proceso):";
				moveCursor(center.X - 15, getCursorPosition().Y + 2); cout << "	========================================= ";
				moveCursor(center.X - 15, getCursorPosition().Y + 2); cout << "	Ingrese tiempo de nuevo proceso. ";
				if (pedirNumero(MIN_NUMBER, nAuxiliar)) {
					Node * item = createNode(nAuxiliar, ++nNodos);
					pushBack(cabeza, fin, item);
				}
			}
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
		default:
			if (!inputFail && op != 0)
			{
				showError("Opcion no existe.", center.X - 10, getCursorPosition().Y + 2);
				cin.ignore();

			}
			break;
		}
		printf("\n");
		cin.get();
	} while (op != 0 || inputFail);
	return 0;
}

void initializeSimulation(Node *& cabeza, Node *& fin, const int quantumTime, int & elapsedTime, int & nNodos)
{
	COORD center = getConsoleCenter();
	center.X -= 10;
	system("cls");
	if (quantumTime <= 0)
	{
		showError("Debe ingresar un tiempo para procesar Quantum.", center.X - 15, getCursorPosition().Y + 2);
		cin.ignore();
		cin.get();
		return;
	}

	if (cabeza)
	{
		showInfo("Simulacion iniciada", center.X - 5, getCursorPosition().Y + 2);
		setWindowAttribute(14 | BACKGROUND_BLUE | FOREGROUND_INTENSITY);
		showQueueTime(quantumTime);
		setWindowAttribute(CONSOLE_BASE_ATTRIB | FOREGROUND_INTENSITY);
		moveCursor(center.X - 35, getCursorPosition().Y + 4); printf("======================================= Procesando elementos =======================================");
		showList(cabeza, fin, MIN_LEFT_BORDER, ITEM_SEPARATION, MAX_RIGHT_BORDER, true);
		moveCursor(center.X - 35, getCursorPosition().Y + 4); printf("====================================================================================================");
		Sleep(SLEEP_ANIMATION);
		system("cls");
	}
	else {
		showError("No existen procesos a simular.", center.X - 5, getCursorPosition().Y + 2);
		cin.ignore();
		cin.get();
		return;
	}

	while (nNodos > 0 && cabeza)
	{
		burstNodeTime(cabeza, elapsedTime, quantumTime);
		if (Node * front = popFront(cabeza, fin))
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

				showInfo("Simulacion iniciada", center.X - 5, getCursorPosition().Y + 2);
				setWindowAttribute(14 | BACKGROUND_BLUE | FOREGROUND_INTENSITY);
				showQueueTime(quantumTime);
				setWindowAttribute(CONSOLE_BASE_ATTRIB | FOREGROUND_INTENSITY);
				moveCursor(center.X - 35, getCursorPosition().Y + 4); printf("======================================= Procesando elementos =======================================");
				showList(cabeza, fin, MIN_LEFT_BORDER, ITEM_SEPARATION, MAX_RIGHT_BORDER, true);
				moveCursor(center.X - 35, getCursorPosition().Y + 4); printf("====================================================================================================");
				Sleep(SLEEP_ANIMATION);
				system("cls");
			}
		}
	}
	showSuccess("Simulacion terminada", center.X - 5, getCursorPosition().Y + 2);
	cin.ignore();
	cin.get();
}

void showList(Node * cabeza, Node * fin, int startBorderOffset, const int itemSeparation, const int endBorderDifference, const bool useOffsetJump)
{
	Node * aux = cabeza;
	bool continuar = true;
	COORD center = getConsoleCenter();
	center.X -= itemSeparation;
	moveCursor(center.X, getCursorPosition().Y + 2);
	int offset = startBorderOffset;
	while (continuar && cabeza)
	{
		if (useOffsetJump)
		{
			if (getCursorPosition().X >= endBorderDifference)
			{
				offset = startBorderOffset;
				moveCursor(center.X - offset, getCursorPosition().Y + 1);
			}
		}
		moveCursor(center.X - offset, getCursorPosition().Y); cout << "" << "P" << aux->nodeArrival << "(";
		cout << aux->processTime;
		cout << ")";
		if (aux == fin)
			continuar = false;
		aux = aux->next;
		offset -= itemSeparation;
	}
}

void showElapsedTime(const int elapsedTime)
{
	COORD center = getConsoleCenter();
	center.X -= 10;
	moveCursor(center.X - 15, getCursorPosition().Y + 1); cout << "Tiempo transcurrido (Ultima simulacion): " << elapsedTime << " /s";
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

void showQueueTime(const int time)
{
	COORD center = getConsoleCenter();
	center.X -= 10;
	moveCursor(center.X, getCursorPosition().Y + 2); cout << "Tiempo Quantum: " << time << " /s";
}


void pushBack(Node *& cabeza, Node *& fin, Node *& item)
{
	if (!cabeza) {
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

void copyList(Node *& cabezaOri, Node *& finOri, Node *& cabezaDest, Node *& finDest)
{
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

void freeList(Node *& cabeza, Node *& fin)
{
	while (cabeza)
		delete popFront(cabeza, fin);
}

void moveCursor(const int x, const int y)
{
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), dwPos);
}

void moveCursor(COORD pos) {
	moveCursor(pos.X, pos.Y);
}

COORD getConsoleCenter() {
	COORD dim = getConsoleBufferInfo().dwSize;
	dim.X = dim.X / 2;
	dim.Y = dim.Y / 2;
	return dim;
}

CONSOLE_SCREEN_BUFFER_INFO getConsoleBufferInfo() {
	CONSOLE_SCREEN_BUFFER_INFO  lpBufferInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &lpBufferInfo);
	return lpBufferInfo;
}

COORD getCursorPosition() {
	return getConsoleBufferInfo().dwCursorPosition;
}

void setWindowSize(int width, int height)
{
	RECT rWindow = getConsoleRect();
	MoveWindow(GetConsoleWindow(), rWindow.left, rWindow.top, width, height, true);
}

void setWindowSize(int width, int height, int left, int top)
{
	MoveWindow(GetConsoleWindow(), left, top, width, height, true);
}

RECT getConsoleRect()
{
	RECT rWindow;
	GetWindowRect(GetConsoleWindow(), &rWindow);
	return rWindow;
}

void setWindowAttribute(int option) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), option);
}

void showError(string message, int x, int y)
{
	setWindowAttribute(14 | BACKGROUND_RED | FOREGROUND_INTENSITY);
	moveCursor(x, y); cout << "Error: " << message << endl;
	setWindowAttribute(CONSOLE_BASE_ATTRIB | FOREGROUND_INTENSITY);
}

void showError(string message, COORD pos)
{
	showError(message, pos.X, pos.Y);
}

void showSuccess(string message, COORD pos)
{
	showSuccess(message, pos.X, pos.Y);
}

void showSuccess(string message, int x, int y)
{
	setWindowAttribute(9 | BACKGROUND_GREEN | FOREGROUND_INTENSITY);
	moveCursor(x, y); cout << "Exitoso: " << message << endl;
	setWindowAttribute(CONSOLE_BASE_ATTRIB | FOREGROUND_INTENSITY);
}

void showInfo(string message, COORD pos)
{
	showInfo(message, pos.X, pos.Y);
}

void showInfo(string message, int x, int y)
{
	setWindowAttribute(23 | BACKGROUND_BLUE | FOREGROUND_INTENSITY);
	moveCursor(x, y); cout << "Informacion: " << message << endl;
	setWindowAttribute(CONSOLE_BASE_ATTRIB | FOREGROUND_INTENSITY);
}
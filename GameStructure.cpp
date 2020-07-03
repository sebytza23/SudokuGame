#include "GameStructure.h"

//---------------------------------------------------DISCLAIMER---------------------------------------------
//Codul daca va fi rulat in felul acesta nu va functiona
//Codul din spate,care creeaza executabilul a fost ascuns
//Pentru a nu se frauda munca noastra
//Astfel ca aici se ragaseste doar codul functiilor ce fac aplicatia sa functioneze
//----------------------------------------------------------------------------------------------------------


void GameStructure::SetDigitToTextBox(HWND wnd, int x, std::string data)
{
	HWND textbox = GetDlgItem(wnd, x);	// preia valoarea de textbox pentru id-ul x
	if (textbox) //daca nu exista valori in textbox intra 
	{
		int index = GetWindowTextLength(textbox);	//index preia lungimea elementelor din textboxul respectiv
		if (index <= 0)
		{
			// append to textbox
			SetFocus(textbox);	//intra in focus respectivul textbox
			SendMessageA(textbox, WM_SETTEXT, 0, (LPARAM)data.c_str());	//modifica valoarea din textboxul liber
		}
	}
}

bool GameStructure::CheckNumberSafe(int matrix[9][9], int row, int column, int number)
{
	return !NumberInRow(matrix, row, number) && // daca numarul nu se afla pe randul respectiv
		!NumberInColumn(matrix, column, number) && // daca numarul nu se afla pe coloana respectiva
		!NumberInBox(matrix, row - row % 3, column - column % 3, number) && // daca numarul nu se afla in cutia respectiva
		matrix[row][column] == unassigned_number; // daca respectiva casuta este 0
}

bool GameStructure::CheckLocation(int matrix[9][9], int &row, int &column)
{
	int n = 3, m = 3, n1 = 0, n2 = 0;	//n reprezinta liniile maxime , m reprezinta coloanele maxime, n1 = pozitia de start linie, n2 = pozitie de start coloana
	while (n < 12 && m < 12) { // cand una din cele 2 va fi falsa se va iesi din structura si se va cunoaste faptul ca s-a terminat de umplut matricea
		for (row = n1; row < n; row++)
		{
			for (column = n2; column < m; column++)
			{
				if (matrix[row][column] == unassigned_number) //cauta o locatie valida de plasare
				{
					return true;	//daca o gaseste returneaza adevarat
				}
			}
		}
		if (m < 9) {
			n2 = m;//cand m este egal cu 9, pozitia de start la coloana ia valoarea lui m
			m += 3; // iar marimea maxima a cautarii pe coloana este de m+3
		}
		else {
			n1 = n; // daca m a depasit valoarea 9, linia porneste de la n 
			n += 3; // iar marimea maxima a cautarii pe linie este de n+3
			n2 = 0; // n2 se reseteaza inapoi la 0
			m = 3; // iar marimea maxima de cautare pe coloana se reseteaza cu 3
		}
	}
	return false;	//daca nu gaseste returneaza fals
}

bool GameStructure::NumberInRow(int matrix[9][9], int row, int number)
{
	for (int column = 0; column < 9; column++)
	{
		if (matrix[row][column] == number) //daca se regaseste numarul in rand
		{
			return true;	//returneaza adevarat
		}
	}
	return false;	//altfel returneaza fals
}

bool GameStructure::NumberInColumn(int matrix[9][9], int column, int number)
{
	for (int row = 0; row < 9; row++)
	{
		if (matrix[row][column] == number)	//daca se regaseste numarul in coloana
		{
			return true;	//returneaza adevarat
		}
	}
	return false;	//altfel returneaza fals
}

bool GameStructure::NumberInBox(int matrix[9][9], int start_row, int start_column, int number)
{
	for (int row = 0; row < 3; row++)
	{
		for (int column = 0; column < 3; column++)
		{
			if (matrix[row + start_row][column + start_column] == number) //cauta numarul in casuta respectiva
			{
				return true; // daca e gasit se returneaza true
			}
		}
	}
	return false;	// daca nu este gasit se returneaza false
}

bool GameStructure::SolveTheGame(int matrix[9][9])
{
	int row, column;
	if (!CheckLocation(matrix, row, column)) //daca celula respectiva este goala
	{
		//locatie valida
		return true;
	}
	for (int number = 1; number <= 9; number++) //genereaza numerele ce pot fi plasate
	{
		if (CheckNumberSafe(matrix, row, column, number))	//verificare daca se poate plasa pe celula respectiva
		{
			matrix[row][column] = number;
			if (SolveTheGame(matrix))
			{
				//locatie valida
				return true;
			}
			//incearca iar si ofera celulei respecive valoarea 0
			matrix[row][column] = unassigned_number;
		}
	}
	return false;	//in cazul in care nu s-a gasit o rezolvare se returneaza false pentru functia din care a fost apelata
}



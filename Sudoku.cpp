#include "GameStructure.h"

//---------------------------------------------------DISCLAIMER---------------------------------------------
//Codul daca va fi rulat in felul acesta nu va functiona
//Codul din spate,care creeaza executabilul a fost ascuns
//Pentru a nu se frauda munca noastra
//Astfel ca aici se ragaseste doar codul functiilor ce fac aplicatia sa functioneze
//----------------------------------------------------------------------------------------------------------

int game_type;	//mod de joc
HINSTANCE currentbase;	//instanta deschisa(teoretic fereastra aplicatiei deschise)
int m[9][9];

void write(int n, HWND window) {
	ifstream f("date2.txt");s
	for (int k = 1; k <= n; k++) {
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 9; j++)
				f >> m[i][j];	//citeste matricea
	}
	int j = 0, l = 0;
	for (int i = 0; i < 81; i++) //exista 81 de taguri pentru textboxuri
	{
		if (m[j][l] != 0)	//daca valoarea din matrice este 0
			GameStructure::SetDigitToTextBox(window, i, to_string(m[j][l++]));	//adauga in textbox valoarea de tip char regasita in matricea respectiva
		else {
			GameStructure::SetDigitToTextBox(window, i, "");	//altfel adauga in textbox valoarea NULL
			l++;
		}
		if (l == 9) {
			l = 0;
			j++;
		}
	}
}

int __stdcall gtype_handler(HWND window, UINT msg, WPARAM window_param, LPARAM long_param)
{
	switch (msg) //msj reprezinta mesajul primit de la mouse
	{
		case WM_COMMAND: //Actiunea mouse-ului
		{
			switch (LOWORD(window_param))	//window_param reprezinta parametrii paginii, in cazul de fata cele 3 butoane
			{
				case 10: // Buton Easy(10 reprezinta id-ul butonului)
				{
					game_type = GameStructure::GAME_EASY_MODE;
					//prin ajutorul acestei functii se inchide aplicatia 
					//si se activeaza modul de joc ales
					SendMessage(window, WM_CLOSE, 0, 0);	
					break;
				}
				case 11: // Buton Medium(11 reprezinta id-ul butonului)
				{
					game_type = GameStructure::GAME_MEDIUM_MODE;
					SendMessage(window, WM_CLOSE, 0, 0);
					break;
				}
				case 12: // Buton Hard(12 reprezinta id-ul butonului)
				{
					game_type = GameStructure::GAME_HARD_MODE;
					SendMessage(window, WM_CLOSE, 0, 0);
					break;
				}
			}
			break;
		}
		case WM_CLOSE:
		{
			DestroyWindow(window);	//inchirere aplicatie
			break;
		}
		default: return DefWindowProcA(window, msg, window_param, long_param);	//opreste fereastra din a se afisa multiplu
	}
	return 1;
}

int __stdcall game_handler(HWND window, UINT msg, WPARAM window_param, LPARAM long_param)
{
	switch (msg)
	{
		case WM_INITDIALOG:	//initializarea ferestrei in functie de modul de joc ales
		{	
			switch (game_type)	//tipul de joc ales
			{
				case GameStructure::GAME_EASY_MODE:
				{
					//Titlul Modului de Joc
					SetWindowText(window, "Sudoku - EASY");
					write(1, window); //umplere celule in functie de modul de joc ales
					break; 
				}
				case GameStructure::GAME_MEDIUM_MODE:
				{
					//Titlul Modului de Joc
					SetWindowText(window, "Sudoku - MEDIUM");
					write(2, window);
					break;
				}
				case GameStructure::GAME_HARD_MODE:
				{
					//Titlul Modului de Joc
					SetWindowText(window, "Sudoku - HARD");
					write(3, window);
					break;
				}
			}
			break;
		}
		case WM_COMMAND:
		{
			switch (LOWORD(window_param))	//daca s-a ales butonul de rezolvare
			{
				case 82: //buton rezolvare(82 reprezinta id-ul butonului)
				{
					if (GameStructure::SolveTheGame(m))//aici se apeleaza functia de rezolvare
					{
						//printeaza solutia
						int i = 0, j = 0;
						for (int x = 0; x <= 80; x++)
						{
							Sleep(80);
							GameStructure::SetDigitToTextBox(window, x, to_string(m[i][j++]));
							//functia de introducere solutii
							//pe tabla de rezolvare
							if (j == 9)
							{
								i++;
								j = 0;
							}
						}
					}
					else
					{
						DestroyWindow(window);	//iesire fortata din aplicatie
						MessageBox(NULL, "Nu exista solutii!", "Ne pare rau!", MB_OK);	//afisare messagebox pentru eroare
					}
					break;
				}
			}
			break;
		}
		case WM_CLOSE:	//actiune mouse buton iesire
		{
			DestroyWindow(window); //iesire fereastra
			break;
		}
		default: return DefWindowProcA(window, msg, window_param, long_param);//opreste fereastra din a se afisa multiplu
	}
	return 1;
}

int __stdcall WinMain(HINSTANCE current_base, HINSTANCE previous_base, char* args, int display)
{
	currentbase = current_base;	//instanta deschisa in momentul acela
	DialogBoxA(currentbase, MAKEINTRESOURCEA(IDD_GAMETYPE_FORM), 0, gtype_handler);//deschide fereastra de inceput

	if (game_type >= 0) // -1 reprezinta nivelul ferestrei principale care se deschide
	{
		DialogBoxA(currentbase, MAKEINTRESOURCEA(IDD_MAIN_FORM), 0, game_handler); // deschidere fereastra in functie de modul ales
	}
}
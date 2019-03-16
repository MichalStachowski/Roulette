//POP_2017_12_18_projekt_1_Stachowski_Michal_AIR_1_171570
//Korzystalem z Dev-C++ 5.11

//Zadanie projektowe to ruletka. Gra od 1 do 4 graczy. 
//Kazdy gracz dokonuje zakladow w tajemnicy przed innymi a jego wybor zostaje zaznaczony na planszy do gry.
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<iomanip>
#include<cstring>
#include<fstream>
using namespace std;

const int MAX_GRACZY=4;				//maksymalna ilosc graczy
const int MAX_NAZWA=10;				//maksymalna dlugosc nazwy gracza

struct Gracze
{
	char nazwa_gracza[MAX_NAZWA];
	int liczba_zetonow;
	int wybor_gracza;
	int postawionych_zetonow;
	char wybor_parz[2];
	char wybor_cz[2];
};

//----------Funkcje zabezpieczajace program przed bledami wynikacjacymi ze zlych typow wprowadzonych danych-----
void warunek_zla_dana_wejsciowa();
void warunek_zetony(int i, Gracze *tab);
//--------------------------------------------------------------------------------------------------------------

//----------Zaznaczenie wyboru gracza na stole do gry-------------------------------------------
void Rysuj_stol_do_gry();
void Stol_zaznaczenie_pojedynczego_wyboru (int wybor_gracza);
void Stol_zaznaczenie_dwa_pola(int wart_1[], int wart_2[], int k);
void Stol_zaznaczenie_4_pola (int wart_1[], int wart_2[], int wart_3[], int wart_4[], int k);
void Stol_tuziny (int a, int b);
void Stol_zaznaczenie_parzystych ();
void Stol_zaznaczenie_nieparzystych ();
void Stol_18 (int wybor_18);
void Stol_zaznaczenie_czerwonych ();
void Stol_zaznaczenie_czarnych ();
//----------------------------------------------------------------------------------------------

//----------Funkcje odpowiadajace za personalizacje graczy oraz wypisanie tabeli punktowej na koniec rundy----
void Ile_graczy (int & Liczba_graczy, Gracze *tab);
void Nazwanie_graczy(int Liczba_graczy, Gracze *tab);
void tabela_punktowa(int Liczba_graczy, Gracze *tab);
//------------------------------------------------------------------------------------------------------------

//----------Warunki okreslajace w zaleznosci od trybu rozgrywki wygrana lub przegrana gracza------------------------
void warunek_pojedyncze_losowanie(int los, Gracze *tab, int i);
void warunek_dwa_pola(int los, int k, Gracze *tab, int wart_1[], int wart_2[]);
void warunek_cztery_pola(int los, int k, Gracze *tab, int wart_1[], int wart_2[], int wart_3[], int wart_4[]);
void warunek_tuziny (int los, Gracze *tab, int i);
void warunek_parzyste_nieparzyste(int los, int i, Gracze *tab);
void warunek_18(int los, int i, Gracze *tab);
void warunek_czarne_czerwone(int los, int i, Gracze *tab);
//------------------------------------------------------------------------------------------------------------------

//----------Typy zakladow i ich przeprowadzanie---------------------------------------
void Losowanie_pojedyncze (int Liczba_graczy, Gracze *tab, int i, int los);
void Losowanie_dwa_pola (int Liczba_graczy, Gracze *tab, int k, int los);
void Losowanie_cztery_pola (int Liczba_graczy, Gracze *tab, int k, int los);
void Losowanie_tuziny (int Liczba_graczy, Gracze *tab, int i, int los);
void Losowanie_parzyste_nieparzyste (int Liczba_graczy, Gracze *tab, int i, int los);
void Losowanie_18 (int Liczba_graczy, Gracze *tab, int i, int los);
void Losowanie_czarne_czerwone (int Liczba_graczy, Gracze *tab, int i, int los);
//------------------------------------------------------------------------------------

//---------Mechanika rozgrywki-----------------------------------------------------
void Pisz_Menu ();
void wybor_trybu(int wybor, int Liczba_graczy, Gracze *tab, int i, int los);
void Dodatkowy_zaklad(int wybor, int Liczba_graczy, Gracze *tab, int i, int los);
void zmiana_gracza (int i, int Liczba_graczy);
void Kto_wygral (int Liczba_graczy, Gracze *tab);
void warunek_koniec(int Liczba_graczy, Gracze *tab);
void Wypis_dane();
void wyniki_losowania(int licznik_rund, int los, int Liczba_graczy, Gracze *tab);
//---------------------------------------------------------------------------------

//--------Inicjalizacja rozgrywki oraz jej zakonczenie po 10 rundach----
void Wpisanie_zetonow_poczatek(int Liczba_graczy, Gracze *tab);
void Poczatek_gry(int &Liczba_graczy, Gracze *tab);
void Koniec_gry(int Liczba_graczy, Gracze *tab);								
// ---------------------------------------------------------------------


int main()
{
	srand(time(NULL));
	int Liczba_graczy;

	Gracze *tab;
	tab = new Gracze[MAX_GRACZY];
	Poczatek_gry(Liczba_graczy, tab);

	int los;
	int wybor;
	do
	{	
		for (int licznik_rund=1; licznik_rund<=10; licznik_rund++)
		{
			los=rand()%37;
			for (int i=0; i<Liczba_graczy; i++)
			{
				wybor_trybu(wybor, Liczba_graczy, tab, i, los);
				zmiana_gracza(i, Liczba_graczy);
				Pisz_Menu();
			}			
			wyniki_losowania(licznik_rund, los, Liczba_graczy, tab);
		}
		Koniec_gry(Liczba_graczy, tab);		
		break;	
	}
	while (true);	
	
	return 0;
}
// ----------------------------------------------------------------------

void warunek_zla_dana_wejsciowa()
{
	if (!cin)
	{
		cin.clear();				//czyszczenie flagi bledu strumienia
		cin.sync();					//czysczenie bufora strumienia
	}
}


void warunek_zetony(int i, Gracze *tab)
{
	while ((*(tab+i)).postawionych_zetonow > (*(tab+i)).liczba_zetonow || (!cin) || (*(tab+i)).postawionych_zetonow<0)
	{
		if(!cin)
		{
			cout << "Ilosc zetonow nalezy podac w postaci liczby.\n\n";
			cin.clear();
			cin.sync();
			break;
		}
		else
		{
			cout << "Bledna ilosc postawionych zetonow! Masz " << (*(tab+i)).liczba_zetonow << " zetonow.\n\n";
			break;
		}
	}
}


void Rysuj_stol_do_gry()
{
	int Stol_do_gry[12][3];
	int licznik_stol=1;
	for (int i=0; i<12; i++)
	{
		for (int j=0; j<3; j++)
		{
			Stol_do_gry[i][j] = licznik_stol;
			cout << setw(3) << "[" << Stol_do_gry[i][j] << "]";
			if(licznik_stol < 10)
			{
				cout << " ";
			}
			licznik_stol++;
		}
		cout << endl;
	}
}


void Stol_zaznaczenie_pojedynczego_wyboru (int wybor_gracza)
{
	int Stol_do_gry[12][3];
	int licznik_stol=1;
	for (int i=0; i<12; i++)
	{
		for (int j=0; j<3; j++)
		{
			Stol_do_gry[i][j] = licznik_stol;
			
			if (Stol_do_gry[i][j] == wybor_gracza)
			{
				cout << setw(3) << "  [X] ";
			}
			else
			{
				cout << setw(3) << "[" << Stol_do_gry[i][j] << "]";				
				if(licznik_stol < 10)
				{
					cout << " ";
				}				
			}	
			licznik_stol++;								
		}
		cout << endl;
	}
}


void Stol_zaznaczenie_dwa_pola(int wart_1[], int wart_2[], int k)
{
	int Stol_do_gry[12][3];
	int licznik_stol=1;
	for (int i=0; i<12; i++)
	{
		for (int j=0; j<3; j++)
		{
			Stol_do_gry[i][j] = licznik_stol;
									
			if (Stol_do_gry[i][j] == wart_1[k] || Stol_do_gry[i][j] == wart_2[k])
			{
				cout << setw(3) << "  [X] ";
			}
			else
			{
				cout << setw(3) << "[" << Stol_do_gry[i][j] << "]";				
				if(licznik_stol < 10)
				{
					cout << " ";
				}					
			}	
			licznik_stol++;								
		}
		cout << endl;
	}
}


void Stol_zaznaczenie_4_pola (int wart_1[], int wart_2[], int wart_3[], int wart_4[], int k)
{
	int Stol_do_gry[12][3];
	int licznik_stol=1;
	for (int i=0; i<12; i++)
	{
		for (int j=0; j<3; j++)
		{
			Stol_do_gry[i][j] = licznik_stol;
									
			if (Stol_do_gry[i][j]==wart_1[k] || Stol_do_gry[i][j]==wart_2[k] || Stol_do_gry[i][j]==wart_3[k] || Stol_do_gry[i][j]==wart_4[k])
			{
				cout << setw(3) << "  [X] ";
			}
			else
			{
				cout << setw(3) << "[" << Stol_do_gry[i][j] << "]";				
				if(licznik_stol < 10)
				{
					cout << " ";
				}				
			}	
		licznik_stol++;								
	}
	cout << endl;
	}
}


void Stol_tuziny (int a, int b)
{
	int Stol_do_gry[12][3];
	int licznik_stol=1;
	for (int i=0; i<12; i++)
	{
		for (int j=0; j<3; j++)
		{
			Stol_do_gry[i][j] = licznik_stol;
			
			if (Stol_do_gry[i][j]>a && Stol_do_gry[i][j]<b)
			{
				cout << setw(3) << "  [X] ";
			}
			else
			{
				cout << setw(3) << "[" << Stol_do_gry[i][j] << "]";				
				if(licznik_stol < 10)
				{
					cout << " ";
				}				
			}	
			licznik_stol++;								
		}
		cout << endl;
	}	

}


void Stol_zaznaczenie_parzystych ()
{
	int Stol_do_gry[12][3];
	int licznik_stol=1;
	for (int i=0; i<12; i++)
	{
		for (int j=0; j<3; j++)
		{
			Stol_do_gry[i][j] = licznik_stol;
			
			if (Stol_do_gry[i][j]%2 == 0)
			{
				cout << setw(3) << "  [X] ";
			}
			else
			{
				cout << setw(3) << "[" << Stol_do_gry[i][j] << "]";				
				if(licznik_stol < 10)
				{
					cout << " ";
				}				
			}	
			licznik_stol++;								
		}
		cout << endl;
	}
}


void Stol_zaznaczenie_nieparzystych ()
{
	int Stol_do_gry[12][3];
	int licznik_stol=1;
	for (int i=0; i<12; i++)
	{
		for (int j=0; j<3; j++)
		{
			Stol_do_gry[i][j] = licznik_stol;
			
			if (Stol_do_gry[i][j]%2 != 0)
			{
				cout << setw(3) << "  [X] ";
			}
			else
			{
				cout << setw(3) << "[" << Stol_do_gry[i][j] << "]";				
				if(licznik_stol < 10)
				{
					cout << " ";
				}				
			}	
			licznik_stol++;								
		}
		cout << endl;
	}
}


void Stol_18 (int wybor_18)
{
	int Stol_do_gry[12][3];
	int licznik_stol=1;	
	if (wybor_18==1)
	{
		for (int i=0; i<12; i++)
		{
			for (int j=0; j<3; j++)
			{
				Stol_do_gry[i][j] = licznik_stol;
				
				if (Stol_do_gry[i][j] < 19)
				{
					cout << setw(3) << "  [X] ";
				}
				else
				{
					cout << setw(3) << "[" << Stol_do_gry[i][j] << "]";				
					if(licznik_stol < 10)
					{
						cout << " ";
					}				
				}	
				licznik_stol++;								
			}
			cout << endl;
		}
	}
	else if(wybor_18==2)
	{
		for (int i=0; i<12; i++)
		{
			for (int j=0; j<3; j++)
			{
				Stol_do_gry[i][j] = licznik_stol;				
					if (Stol_do_gry[i][j]>18)
					{
						cout << setw(3) << "  [X] ";
					}
					else
					{
						cout << setw(3) << "[" << Stol_do_gry[i][j] << "]";				
						if(licznik_stol < 10)
						{
							cout << " ";
						}				
					}	
					licznik_stol++;								
				}
				cout << endl;
		}
	}
	else cout << "Wybrano bledna opcje.";
}


void Stol_zaznaczenie_czerwonych ()
{
	int Stol_do_gry[12][3];
	int licznik_stol=1;
	for (int i=0; i<12; i++)
	{
		for (int j=0; j<3; j++)
		{
			Stol_do_gry[i][j] = licznik_stol;
			
			if (Stol_do_gry[i][j] == 1 || Stol_do_gry[i][j] == 3 || Stol_do_gry[i][j] == 5 || Stol_do_gry[i][j] == 7 || Stol_do_gry[i][j] == 9 || Stol_do_gry[i][j] == 12 || Stol_do_gry[i][j] == 14 || Stol_do_gry[i][j] == 16 || Stol_do_gry[i][j] == 18 || Stol_do_gry[i][j] == 19 || Stol_do_gry[i][j] == 21 || Stol_do_gry[i][j] == 23 || Stol_do_gry[i][j] == 25 || Stol_do_gry[i][j] == 27 || Stol_do_gry[i][j] == 30 || Stol_do_gry[i][j] == 32 || Stol_do_gry[i][j] == 34 || Stol_do_gry[i][j] == 36)
			{
				cout << setw(3) << "  [X] ";
			}
			else
			{
				cout << setw(3) << "[" << Stol_do_gry[i][j] << "]";				
				if(licznik_stol < 10)
				{
					cout << " ";
				}				
			}	
			licznik_stol++;								
		}
		cout << endl;
	}
}


void Stol_zaznaczenie_czarnych ()
{
	int Stol_do_gry[12][3];
	int licznik_stol=1;
	for (int i=0; i<12; i++)
	{
		for (int j=0; j<3; j++)
		{
			Stol_do_gry[i][j] = licznik_stol;
			if (Stol_do_gry[i][j] == 2 || Stol_do_gry[i][j] == 4 || Stol_do_gry[i][j] == 6 || Stol_do_gry[i][j] == 8 || Stol_do_gry[i][j] == 10 || Stol_do_gry[i][j] == 11 || Stol_do_gry[i][j] == 13 || Stol_do_gry[i][j] == 15 || Stol_do_gry[i][j] == 17 || Stol_do_gry[i][j] == 20 || Stol_do_gry[i][j] == 22 || Stol_do_gry[i][j] == 24 || Stol_do_gry[i][j] == 26 || Stol_do_gry[i][j] == 28 || Stol_do_gry[i][j] == 29 || Stol_do_gry[i][j] == 31 || Stol_do_gry[i][j] == 33 || Stol_do_gry[i][j] == 35)
			{
				cout << setw(3) << "  [X] ";
			}
			else
			{
				cout << setw(3) << "[" << Stol_do_gry[i][j] << "]";				
				if(licznik_stol < 10)
				{
					cout << " ";
				}				
			}	
			licznik_stol++;								
		}
		cout << endl;
	}
}


void Ile_graczy (int & Liczba_graczy, Gracze *tab)
{
	while (true)
	{
		cout << "Ile graczy bierze udzial w rozgrywce?: ";
		cin >> Liczba_graczy;
			
		if (Liczba_graczy>4 || Liczba_graczy<1 || (!cin))
		{
			while(Liczba_graczy>4 || Liczba_graczy<1 || (!cin))
			{
				cout << "Zla liczba graczy. Wprowadz ponownie liczbe graczy (od 1 do 4): \n" << endl;
				cin.clear();																				//Czyszczenie flagi bledu strumienia
				cin.sync();																					//Czyszczenie bufora strumienia
				break;
			}	
		}
		else 
		{
			Nazwanie_graczy(Liczba_graczy, tab);
			Wpisanie_zetonow_poczatek(Liczba_graczy, tab);
			tabela_punktowa(Liczba_graczy, tab);
			break;				
		}
	}
}


void Nazwanie_graczy(int Liczba_graczy, Gracze *tab)
{
	for (int i=0; i<Liczba_graczy; i++)
	{
		cout << "Podaj nazwe gracza " << i+1 << ": ";
		cin >> (*(tab+i)).nazwa_gracza;
	}
}


void tabela_punktowa(int Liczba_graczy, Gracze *tab)
{
	cout << endl;
  	cout << " nazwa gracza | liczba zetonow | liczba punktow" << endl;
  	cout << "-------------------------------------------------" << endl;
  	
	for (int i=0; i<Liczba_graczy; i++)
	{
		cout << setw(10) << (*(tab+i)).nazwa_gracza << setw(15) << (*(tab+i)).liczba_zetonow << setw(15) << (*(tab+i)).liczba_zetonow*10 << endl;
	}
	
	cout << "-------------------------------------------------" << endl;
}


void warunek_pojedyncze_losowanie(int los, Gracze *tab, int i)
{
	ofstream plik;
	plik.open("wypis.txt", ios::out|ios::app);		
	if (los==0)
	{
		plik << "Wylosowano 0. " << (*(tab+i)).nazwa_gracza << ", przegrany zaklad. Tracisz " << (*(tab+i)).postawionych_zetonow << " zetonow.\n";
		(*(tab+i)).liczba_zetonow = (*(tab+i)).liczba_zetonow-(*(tab+i)).postawionych_zetonow;
	}
	else if ((*(tab+i)).wybor_gracza != los)
	{
		plik << "Niestety " << (*(tab+i)).nazwa_gracza << ", przegrany zaklad Straight Up. Obstawione pole to " << (*(tab+i)).wybor_gracza << ". Tracisz " << (*(tab+i)).postawionych_zetonow << " zetonow.\n";
		(*(tab+i)).liczba_zetonow = (*(tab+i)).liczba_zetonow-(*(tab+i)).postawionych_zetonow;
	}
	else
	{
		plik << "Brawo " << (*(tab+i)).nazwa_gracza << ", wygrany zaklad Straight Up! Zdobywasz " << ((*(tab+i)).postawionych_zetonow*1) << " zetonow!\n";
		(*(tab+i)).liczba_zetonow = (*(tab+i)).liczba_zetonow + ((*(tab+i)).postawionych_zetonow*35);
	}
	plik.close();	
}


void warunek_dwa_pola(int los, int k, Gracze *tab, int wart_1[], int wart_2[])
{
	ofstream plik;
	plik.open("wypis.txt", ios::out|ios::app);		
	if (los==0)
	{
		plik << "Wylosowano 0. " << (*(tab+k)).nazwa_gracza << ", przegrany zaklad. Tracisz " << (*(tab+k)).postawionych_zetonow << " zetonow.\n";
		(*(tab+k)).liczba_zetonow = (*(tab+k)).liczba_zetonow-(*(tab+k)).postawionych_zetonow;
	}
	else if (wart_1[k]==los || wart_2[k]==los)
	{
		plik << "Brawo " << (*(tab+k)).nazwa_gracza << ", wygrany zaklad Split Bet! Zdobywasz " << ((*(tab+k)).postawionych_zetonow*17) << " zetonow!\n";
		(*(tab+k)).liczba_zetonow = (*(tab+k)).liczba_zetonow + ((*(tab+k)).postawionych_zetonow*17); 
	}
	else
	{
		plik << "Niestety " << (*(tab+k)).nazwa_gracza << ", przegrany zaklad Split Bet. Tracisz " << (*(tab+k)).postawionych_zetonow << " zetonow.\n";
		(*(tab+k)).liczba_zetonow = (*(tab+k)).liczba_zetonow-(*(tab+k)).postawionych_zetonow;				
	}
	plik.close();
}


void warunek_cztery_pola(int los, int k, Gracze *tab, int wart_1[], int wart_2[], int wart_3[], int wart_4[])
{
	ofstream plik;
	plik.open("wypis.txt", ios::out|ios::app);
	if (los==0)
	{
		plik << "Wylosowano 0. " << (*(tab+k)).nazwa_gracza << ", przegrany zaklad. Tracisz " << (*(tab+k)).postawionych_zetonow << " zetonow.\n";
		(*(tab+k)).liczba_zetonow = (*(tab+k)).liczba_zetonow-(*(tab+k)).postawionych_zetonow;
	}
	else if (wart_1[k]==los || wart_2[k]==los || wart_3[k]==los || wart_4[k]==los)
	{
		plik << "Brawo " << (*(tab+k)).nazwa_gracza << ", wygrany zaklad Corner Bet! Zdobywasz " << ((*(tab+k)).postawionych_zetonow*8) << " zetonow!\n";
		(*(tab+k)).liczba_zetonow = (*(tab+k)).liczba_zetonow + ((*(tab+k)).postawionych_zetonow*8); 
	}
	else
	{
		plik << "Niestety " << (*(tab+k)).nazwa_gracza << ", przegrany zaklad Corner Bet. Tracisz " << (*(tab+k)).postawionych_zetonow << " zetonow.\n";
		(*(tab+k)).liczba_zetonow = (*(tab+k)).liczba_zetonow-(*(tab+k)).postawionych_zetonow;				
	}
	plik.close();
}


void warunek_tuziny (int los, Gracze *tab, int i)
{
	ofstream plik;
	plik.open("wypis.txt", ios::out|ios::app);
	if (los==0)
	{
		plik << "Wylosowano 0. " << (*(tab+i)).nazwa_gracza << ", przegrany zaklad. Tracisz " << (*(tab+i)).postawionych_zetonow << " zetonow.\n";
		(*(tab+i)).liczba_zetonow = (*(tab+i)).liczba_zetonow-(*(tab+i)).postawionych_zetonow;
	}
	else if ((*(tab+i)).wybor_gracza == 1)
	{
		if (los>0 && los<13)
		{
			plik << "Brawo " << (*(tab+i)).nazwa_gracza << ", wygrany zaklad Dozen Bet (wybrano tuzin 1)! Zdobywasz " << ((*(tab+i)).postawionych_zetonow*2) << " zetonow!\n";
			(*(tab+i)).liczba_zetonow = (*(tab+i)).liczba_zetonow + ((*(tab+i)).postawionych_zetonow*2); 
		}
		else
		{
			plik << "Niestety " << (*(tab+i)).nazwa_gracza << ", przegrany zaklad Dozen Bet (wybrano tuzin 1). Tracisz " << (*(tab+i)).postawionych_zetonow << " zetonow.\n";
			(*(tab+i)).liczba_zetonow = (*(tab+i)).liczba_zetonow-(*(tab+i)).postawionych_zetonow;				
		}
	}
	else if ((*(tab+i)).wybor_gracza == 2)
	{
		if (los>12 && los<25)
		{
			plik << "Brawo " << (*(tab+i)).nazwa_gracza << ", wygrany zaklad Dozen Bet (wybrano tuzin 2)! Zdobywasz " << ((*(tab+i)).postawionych_zetonow*2) << " zetonow!\n";
			(*(tab+i)).liczba_zetonow = (*(tab+i)).liczba_zetonow + ((*(tab+i)).postawionych_zetonow*2); 
		}
		else
		{
			plik << "Niestety " << (*(tab+i)).nazwa_gracza << ", przegrany zaklad Dozen Bet (wybrano tuzin 2). Tracisz " << (*(tab+i)).postawionych_zetonow << " zetonow.\n";
					(*(tab+i)).liczba_zetonow = (*(tab+i)).liczba_zetonow-(*(tab+i)).postawionych_zetonow;				
		}
	}
	else
	{
		if (los>24 && los<37)
		{
			plik << "Brawo " << (*(tab+i)).nazwa_gracza << ", wygrany zaklad Dozen Bet (wybrano tuzin 3)! Zdobywasz " << ((*(tab+i)).postawionych_zetonow*2) << " zetonow!\n";
			(*(tab+i)).liczba_zetonow = (*(tab+i)).liczba_zetonow + ((*(tab+i)).postawionych_zetonow*2); 
		}
		else
		{
			plik << "Niestety " << (*(tab+i)).nazwa_gracza << ", przegrany zaklad Dozen Bet (wybrano tuzin 3). Tracisz " << (*(tab+i)).postawionych_zetonow << " zetonow.\n";
			(*(tab+i)).liczba_zetonow = (*(tab+i)).liczba_zetonow-(*(tab+i)).postawionych_zetonow;				
		}
	}
	plik.close();
}


void warunek_parzyste_nieparzyste(int los, int i, Gracze *tab)
{
	ofstream plik;
	plik.open("wypis.txt", ios::out|ios::app);
	if (los==0)
	{
		plik << "Wylosowano 0. " << (*(tab+i)).nazwa_gracza << ", przegrany zaklad. Tracisz " << (*(tab+i)).postawionych_zetonow << " zetonow.\n";
		(*(tab+i)).liczba_zetonow = (*(tab+i)).liczba_zetonow-(*(tab+i)).postawionych_zetonow;
	}
	else if (0 == los%2)
	{
		if (strcmp((*(tab+i)).wybor_parz, "P") == 0)
		{
			plik << "Brawo " << (*(tab+i)).nazwa_gracza << ", wygrany zaklad Even (parzyste)! Zdobywasz " << ((*(tab+i)).postawionych_zetonow*1) << " zetonow!\n";
			(*(tab+i)).liczba_zetonow = (*(tab+i)).liczba_zetonow + ((*(tab+i)).postawionych_zetonow*1);
		}
		else
		{
		plik << "Niestety " << (*(tab+i)).nazwa_gracza << ", przegrany zaklad Odd (nieparzyste). Tracisz " << (*(tab+i)).postawionych_zetonow << " zetonow.\n";
			(*(tab+i)).liczba_zetonow = (*(tab+i)).liczba_zetonow-(*(tab+i)).postawionych_zetonow;
		}
	}
	else
	if (strcmp((*(tab+i)).wybor_parz, "N") == 0)
	{
		plik << "Brawo " << (*(tab+i)).nazwa_gracza << ", wygrany zaklad Odd (nieparzyste)! Zdobywasz " << ((*(tab+i)).postawionych_zetonow*1) << " zetonow!\n";
		(*(tab+i)).liczba_zetonow = (*(tab+i)).liczba_zetonow + ((*(tab+i)).postawionych_zetonow*1);
	}
	else
	{
		plik << "Niestety " << (*(tab+i)).nazwa_gracza << ", przegrany zaklad Even (parzyste). Tracisz " << (*(tab+i)).postawionych_zetonow << " zetonow.\n";
		(*(tab+i)).liczba_zetonow = (*(tab+i)).liczba_zetonow-(*(tab+i)).postawionych_zetonow;
	}
	plik.close();
}


void warunek_18(int los, int i, Gracze *tab)
{
	ofstream plik;
		plik.open("wypis.txt", ios::out|ios::app);	
		if (los==0)
		{
			plik << "Wylosowano 0. " << (*(tab+i)).nazwa_gracza << ", przegrany zaklad. Tracisz " << (*(tab+i)).postawionych_zetonow << " zetonow.\n";
			(*(tab+i)).liczba_zetonow = (*(tab+i)).liczba_zetonow-(*(tab+i)).postawionych_zetonow;
		}
		else if ((*(tab+i)).wybor_gracza == 1)
		{
			if (los>0 && los<19)
			{
				plik << "Brawo " << (*(tab+i)).nazwa_gracza << ", wygrany zaklad 1st 18! Zdobywasz " << ((*(tab+i)).postawionych_zetonow*1) << " zetonow!\n";
				(*(tab+i)).liczba_zetonow = (*(tab+i)).liczba_zetonow + ((*(tab+i)).postawionych_zetonow*1); 
			}
			else
			{
				plik << "Niestety " << (*(tab+i)).nazwa_gracza << ", przegrany zaklad 1st 18. Tracisz " << (*(tab+i)).postawionych_zetonow << " zetonow.\n";
				(*(tab+i)).liczba_zetonow = (*(tab+i)).liczba_zetonow-(*(tab+i)).postawionych_zetonow;				
			}
		}
		else if ((*(tab+i)).wybor_gracza == 2)
		{
			if (los>18 && los<37)
			{
				plik << "Brawo " << (*(tab+i)).nazwa_gracza << ", wygrany zaklad 2nd 18! Zdobywasz " << ((*(tab+i)).postawionych_zetonow*1) << " zetonow!\n";
				(*(tab+i)).liczba_zetonow = (*(tab+i)).liczba_zetonow + ((*(tab+i)).postawionych_zetonow*1); 
			}
			else
			{
				plik << "Niestety " << (*(tab+i)).nazwa_gracza << ", przegrany zaklad 2nd 18. Tracisz " << (*(tab+i)).postawionych_zetonow << " zetonow.\n";
				(*(tab+i)).liczba_zetonow = (*(tab+i)).liczba_zetonow-(*(tab+i)).postawionych_zetonow;				
			}
		}
		plik.close();
}


void warunek_czarne_czerwone(int los, int i, Gracze *tab)
{
	ofstream plik;
	plik.open("wypis.txt", ios::out|ios::app);			
	if (los==0)
	{
		plik << "Wylosowano 0. " << (*(tab+i)).nazwa_gracza << ", przegrany zaklad. Tracisz " << (*(tab+i)).postawionych_zetonow << " zetonow.\n";
		(*(tab+i)).liczba_zetonow = (*(tab+i)).liczba_zetonow-(*(tab+i)).postawionych_zetonow;
	}
	else if (los == 1 || los == 3 || los == 5 || los == 7 || los == 9 || los == 12 || los == 14 || los == 16 || los == 18 || los == 19 || los == 21 || los == 23 || los == 25 || los == 27 || los == 30 || los == 32 || los == 34 || los == 36)
	{
		if (strcmp((*(tab+i)).wybor_cz, "R") == 0)
		{
			plik << "Brawo " << (*(tab+i)).nazwa_gracza << ", wygrany zaklad Red! Zdobywasz " << ((*(tab+i)).postawionych_zetonow*1) << " zetonow!\n";
			(*(tab+i)).liczba_zetonow = (*(tab+i)).liczba_zetonow + ((*(tab+i)).postawionych_zetonow*1);
		}
		else
		{
			plik << "Niestety " << (*(tab+i)).nazwa_gracza << ", przegrany zaklad Black. Tracisz " << (*(tab+i)).postawionych_zetonow << " zetonow.\n";
			(*(tab+i)).liczba_zetonow = (*(tab+i)).liczba_zetonow-(*(tab+i)).postawionych_zetonow;
		}
	}
	else
	{
		if (strcmp((*(tab+i)).wybor_cz, "B") == 0)
		{
			plik << "Brawo " << (*(tab+i)).nazwa_gracza << ", wygrany zaklad Black! Zdobywasz " << ((*(tab+i)).postawionych_zetonow*1) << " zetonow!\n";
			(*(tab+i)).liczba_zetonow = (*(tab+i)).liczba_zetonow + ((*(tab+i)).postawionych_zetonow*1);
		}
		else
		{
			plik << "Niestety " << (*(tab+i)).nazwa_gracza << ", przegrany zaklad Red. Tracisz " << (*(tab+i)).postawionych_zetonow << " zetonow.\n";
			(*(tab+i)).liczba_zetonow = (*(tab+i)).liczba_zetonow-(*(tab+i)).postawionych_zetonow;
		}
	}
	plik.close();	
}


void Losowanie_pojedyncze (int Liczba_graczy, Gracze *tab, int i, int los)
{

		while (true)
		{
			cout << (*(tab+i)).nazwa_gracza << ", ile zetonow chcesz postawic?: ";
			cin >> (*(tab+i)).postawionych_zetonow;
		
			if ((*(tab+i)).postawionych_zetonow > (*(tab+i)).liczba_zetonow || (!cin) || (*(tab+i)).postawionych_zetonow<0)
			{
				warunek_zetony(i, tab);		
			}
			else
			{
				while(true)
				{
					cout << (*(tab+i)).nazwa_gracza <<", ktore pole obstawiasz?: ";
					cin >> (*(tab+i)).wybor_gracza;
					if ((*(tab+i)).wybor_gracza>36 || (*(tab+i)).wybor_gracza<=0 || (!cin))
					{
						while((*(tab+i)).wybor_gracza>36 || (*(tab+i)).wybor_gracza<=0 || (!cin))
						{
							{
								cout << "Nie mozna wybrac takiego pola! Mozna wybrac pole od 0 do 36.\n\n";
								warunek_zla_dana_wejsciowa();
								break;
							}						
						}
					}
					else
					{
						Stol_zaznaczenie_pojedynczego_wyboru ((*(tab+i)).wybor_gracza);	
						break;
					}
				}				
			break;
			}
		}
		warunek_pojedyncze_losowanie(los, tab, i);	
}


void Losowanie_dwa_pola (int Liczba_graczy, Gracze *tab, int k, int los)
{
	int wart_1[5];
	int wart_2[5];

	while (true)
	{
		cout << (*(tab+k)).nazwa_gracza << ", ile zetonow chcesz postawic?: ";
		cin >> (*(tab+k)).postawionych_zetonow;	
		
		if ((*(tab+k)).postawionych_zetonow > (*(tab+k)).liczba_zetonow || (!cin) || (*(tab+k)).postawionych_zetonow<0)
		{
			warunek_zetony(k, tab);		
		}
		else
		{
			cout << "Plansza ukazana w celu pomocy jaki wybor moze zostac dokonany. Wybrane pola musza stykac sie bokami.\n\n";
			Rysuj_stol_do_gry();
			while(true)
			{
				cout << (*(tab+k)).nazwa_gracza << ", podaj pierwsze pole: ";
				cin >> wart_1[k];
				cout << (*(tab+k)).nazwa_gracza << ", podaj drugie pole: ";
				cin >> wart_2[k];
				
				if ((wart_1[k]%3==0 && wart_2[k]%3==1) || (wart_1[k]%3==1 && wart_2[k]%3==0) || ((abs(wart_2[k]-wart_1[k]))==2) || ((abs(wart_2[k]-wart_1[k]))>3) || (!cin) || (wart_2[k]*wart_1[k])==0 || (wart_2[k]+wart_1[k])>71 || (wart_2[k]+wart_1[k])<3)
				{
					while((wart_1[k]%3==0 && wart_2[k]%3==1) || (wart_1[k]%3==1 && wart_2[k]%3==0) || ((abs(wart_2[k]-wart_1[k]))==2) || ((abs(wart_2[k]-wart_1[k]))>3) || (!cin) || (wart_2[k]*wart_1[k])==0 || (wart_2[k]+wart_1[k])>71 || (wart_2[k]+wart_1[k])<3)
					{							
						cout << "\nZaznaczono blednie pola. Zaznaczone pola musza znajdowac sie na planszy musza stykac sie bokami.\n\n";
						warunek_zla_dana_wejsciowa();
						break;							
					}					
				}
				else
				{
					Stol_zaznaczenie_dwa_pola(wart_1, wart_2, k);						
					break;													
				}						
			}
		break;	
		}		
	}
	warunek_dwa_pola(los, k, tab, wart_1, wart_2);
}


void Losowanie_cztery_pola (int Liczba_graczy, Gracze *tab, int k, int los)
{
	int wart_1[5];
	int wart_2[5];
	int wart_3[5];
	int wart_4[5];
	
		while (true)
		{
			cout << (*(tab+k)).nazwa_gracza << ", ile zetonow chcesz postawic?: ";
			cin >> (*(tab+k)).postawionych_zetonow;
			
			if ((*(tab+k)).postawionych_zetonow > (*(tab+k)).liczba_zetonow || (!cin) || (*(tab+k)).postawionych_zetonow<0)
			{
				warunek_zetony(k, tab);	
			}
			else
			{
				cout << "Plansza ukazana w celu pomocy jaki wybor moze zostac dokonany. Wybrane pola musza stykac sie bokami.\n\n";
				Rysuj_stol_do_gry();
				while(true)
				{
					cout << (*(tab+k)).nazwa_gracza << ", podaj pierwsze pole: ";
					cin >> wart_1[k];
					cout << (*(tab+k)).nazwa_gracza << ", podaj drugie pole: ";
					cin >> wart_2[k];
					cout << (*(tab+k)).nazwa_gracza << ", podaj trzecie pole: ";
					cin >> wart_3[k];
					cout << (*(tab+k)).nazwa_gracza << ", podaj czwarte pole: ";
					cin >> wart_4[k];
					
					int Tab[4];
					Tab[0]=wart_1[k];
					Tab[1]=wart_2[k];
					Tab[2]=wart_3[k];
					Tab[3]=wart_4[k];
					
					int max=0;
					for (int i=0; i<4; i++)
					{
						if (Tab[i]>max)
						{
							max=Tab[i];
						}
					}
					
					int min=37;
					for (int i=0; i<4; i++)
					{
						if (Tab[i]<min)
						{
							min=Tab[i];
						}
					}
					
					int suma;
					int iloczyn;
					suma=wart_1[k]+wart_2[k]+wart_3[k]+wart_4[k];
					iloczyn=wart_1[k]*wart_2[k]*wart_3[k]*wart_4[k];
					if ((suma)%4>0 || (max-min)!=4 || (!cin) || ((iloczyn)==0) || (suma)>136 || suma<12)
					{
						while ((suma)%4>0 || (max-min)!=4 || (!cin) || ((iloczyn)==0) || (suma)>136 || suma<12)
						{
							cout << "\nZaznaczono bledne pola. Wybrane 4 pola musza sasiadowac ze soba.\n\n";
							warunek_zla_dana_wejsciowa();
							break;
						}
					}
					else
					{
						Stol_zaznaczenie_4_pola (wart_1, wart_2, wart_3, wart_4, k);
						break;
					}					
				}
			break;	
			}
		}			
		warunek_cztery_pola(los, k, tab, wart_1, wart_2, wart_3, wart_4);
}


void Losowanie_tuziny (int Liczba_graczy, Gracze *tab, int i, int los)
{

		while (true)
		{
			cout << (*(tab+i)).nazwa_gracza << ", ile zetonow chcesz postawic?: ";
			cin >> (*(tab+i)).postawionych_zetonow;
			if ((*(tab+i)).postawionych_zetonow > (*(tab+i)).liczba_zetonow || (!cin) || (*(tab+i)).postawionych_zetonow<0)
			{
				warunek_zetony(i, tab);		
			}
			else
			{
				while (true)
				{
					cout << (*(tab+i)).nazwa_gracza <<", ktory tuzin wybierasz? (Numery 1-12 = 1, Numery 12-24 = 2, Numery 25-36=3): ";
					cin >> (*(tab+i)).wybor_gracza;
					
					if ((*(tab+i)).wybor_gracza>3 || (*(tab+i)).wybor_gracza<=0 || (!cin))
					{
						while((*(tab+i)).wybor_gracza>3 || (*(tab+i)).wybor_gracza<=0 || (!cin))
						{
							cout << "Nie mozna wybrac takiego tuzina!\n\n";
							warunek_zla_dana_wejsciowa();
							break;
						}
					}
					else if ((*(tab+i)).wybor_gracza==1)
					{
						Stol_tuziny(0, 13);
						break;
					}
					else if ((*(tab+i)).wybor_gracza==2)
					{
						Stol_tuziny(12, 25);
						break;
					}
					else if ((*(tab+i)).wybor_gracza==3)
					{
						Stol_tuziny(24, 37);
						break;
					}
				}
			break;	
			}
		}
		warunek_tuziny(los, tab, i);					
}


void Losowanie_parzyste_nieparzyste (int Liczba_graczy, Gracze *tab, int i, int los)
{
		while (true)
		{
			cout << (*(tab+i)).nazwa_gracza << ", ile zetonow chcesz postawic?: ";
			cin >> (*(tab+i)).postawionych_zetonow;
		
			if ((*(tab+i)).postawionych_zetonow > (*(tab+i)).liczba_zetonow || (!cin) || (*(tab+i)).postawionych_zetonow<0)
			{
				warunek_zetony(i, tab);		
			}
			else
			{
				while(true)
				{
					cout << (*(tab+i)).nazwa_gracza <<", parzyste, czy nieparzyste?: ";
					cin >> (*(tab+i)).wybor_parz;
					
					if (strcmp((*(tab+i)).wybor_parz, "P")!=0 && strcmp((*(tab+i)).wybor_parz, "N")!=0)
					{
						while(strcmp((*(tab+i)).wybor_parz, "P")!=0 && strcmp((*(tab+i)).wybor_parz, "N")!=0)
						{
							cout << "Wprowadzono nieprawidlowy wybor! (P-parzyste, N-nieparzyste)\n\n";
							break;
						}
					}
					else if (strcmp((*(tab+i)).wybor_parz, "P") == 0)
					{
						Stol_zaznaczenie_parzystych ();
						break;
					}
					else if (strcmp((*(tab+i)).wybor_parz, "N") == 0)
					{
						Stol_zaznaczenie_nieparzystych ();
						break;
					}
				}			
			break;	
			}
		}
		warunek_parzyste_nieparzyste(los, i, tab);		
}


void Losowanie_18 (int Liczba_graczy, Gracze *tab, int i, int los)
{

		while (true)
		{
			cout << (*(tab+i)).nazwa_gracza << ", ile zetonow chcesz postawic?: ";
			cin >> (*(tab+i)).postawionych_zetonow;
			if ((*(tab+i)).postawionych_zetonow > (*(tab+i)).liczba_zetonow || (!cin) || (*(tab+i)).postawionych_zetonow<0)
			{
				warunek_zetony(i, tab);	
			}
			else
			{
				while (true)
				{
					cout << (*(tab+i)).nazwa_gracza <<", ktory zetaw wybierasz? (Numery 1-18 = 1, Numery 19-36 = 2): ";
					cin >> (*(tab+i)).wybor_gracza;
					
					if ((*(tab+i)).wybor_gracza!=1 && (*(tab+i)).wybor_gracza!=2 || (!cin))
					{
						while((*(tab+i)).wybor_gracza!=1 && (*(tab+i)).wybor_gracza!=2 || (!cin))
						{
							warunek_zla_dana_wejsciowa();
							cout << "\nNie mozna wybrac takiej opcji.\n\n";
							break;
						}
					}
					else
					{
						Stol_18((*(tab+i)).wybor_gracza);
						break;
					}
				}

			break;	
			}
		}	
		warunek_18(los, i, tab);		
}


void Losowanie_czarne_czerwone (int Liczba_graczy, Gracze *tab, int i, int los)
{

		while (true)
		{
			cout << (*(tab+i)).nazwa_gracza << ", ile zetonow chcesz postawic?: ";
			cin >> (*(tab+i)).postawionych_zetonow;
		
			if ((*(tab+i)).postawionych_zetonow > (*(tab+i)).liczba_zetonow || (!cin) || (*(tab+i)).postawionych_zetonow<0)
			{
				warunek_zetony(i, tab);		
			}
			else
			{
				while(true)
				{
					cout << (*(tab+i)).nazwa_gracza <<", czarne czy czerwone (R-czerwone , B-czarne)?: ";
					cin >> (*(tab+i)).wybor_cz;
					
					if (strcmp((*(tab+i)).wybor_cz, "R") != 0 && strcmp((*(tab+i)).wybor_cz, "B") != 0)
					{
						while(strcmp((*(tab+i)).wybor_cz, "R") != 0 && strcmp((*(tab+i)).wybor_cz, "B") != 0)
						{
							cout << "Wprowadzono nieprawidlowy wybor! (R-czerwone, B-czarne)\n\n";
							break;
						} 
					}
					else if (strcmp((*(tab+i)).wybor_cz, "R") == 0)
					{
						Stol_zaznaczenie_czerwonych ();
						break;
					}
					else if (strcmp((*(tab+i)).wybor_cz, "B") == 0)
					{
						Stol_zaznaczenie_czarnych ();
						break;
					}
				}
			break;	
			}
		
		}
		warunek_czarne_czerwone(los, i, tab);			
}


void Pisz_Menu ()
{
	cout << "-------------------MENU GLOWNE-------------------" << endl;
	cout << "1 - Straight Up, numer pojedynczy" << endl;
	cout << "2 - Split Bet, dwa numery obok siebie na stole" << endl;
	cout << "3 - Corner Bet, cztery numery obok siebie na stole" << endl;
	cout << "4 - Dozen Bet, tuziny: 1-12, 13-24, 25-36" << endl;
	cout << "5 - Even, Odd, parzyste, nieparzyste" << endl;
	cout << "6 - 1st 18, 2nd 18, numery 1-18 i 19-36" << endl;
	cout << "7 - Red, Black - czerwone, czarne" << endl;
	cout << "8 - Spasowanie rundy" << endl;
	cout << "-------------------------------------------------\n\n"	<<endl;
}


void wybor_trybu(int wybor, int Liczba_graczy, Gracze *tab, int i, int los)
{

	while(true)
	{
		cout << (*(tab+i)).nazwa_gracza << ", ktora opcje wybierasz?: ";
		cin >> wybor;	
		
		if (abs(wybor)>8 || wybor==0 || (!cin))
		{
			while (abs(wybor)>8 || wybor==0 || (!cin))
			{
				cout << "Podano nieprawidlowa opcje. Wybierz ponownie (od 1 do 7).\n\n";
				warunek_zla_dana_wejsciowa();
				break;
			}
		}
		else
		{	
			switch(wybor)
			{		
				case 1: 
				{			
					Losowanie_pojedyncze (Liczba_graczy, tab, i, los);
					Dodatkowy_zaklad(wybor, Liczba_graczy, tab, i, los);	
					break;	
				}
							
				case 2: 
				{
					Losowanie_dwa_pola (Liczba_graczy, tab, i, los);			
					Dodatkowy_zaklad(wybor, Liczba_graczy, tab, i, los);
					break;
				}
							
				case 3: 
				{
					Losowanie_cztery_pola (Liczba_graczy, tab, i, los);			
					Dodatkowy_zaklad(wybor, Liczba_graczy, tab, i, los);			
					break;
				}
							
				case 4: 
				{
					Losowanie_tuziny (Liczba_graczy, tab, i, los);			
					Dodatkowy_zaklad(wybor, Liczba_graczy, tab, i, los);			
					break;
				}
							
				case 5: 
				{
					Losowanie_parzyste_nieparzyste (Liczba_graczy, tab, i, los);			
					Dodatkowy_zaklad(wybor, Liczba_graczy, tab, i, los);			
					break;
				}
							
				case 6: 
				{
					Losowanie_18 (Liczba_graczy, tab, i, los);			
					Dodatkowy_zaklad(wybor, Liczba_graczy, tab, i, los);			
					break;
				}
							
				case 7: 
				{
					Losowanie_czarne_czerwone (Liczba_graczy, tab, i, los);
					Dodatkowy_zaklad(wybor, Liczba_graczy, tab, i, los);			
					break;
				}
				
				case 8: 
				{			
					break;
				}
							
				default:
				{
					cout << "Podales niewlasciwa opcje.";
					system("CLS");			
					Pisz_Menu ();
				}
			}						
		break;
		}				
	}		
}


void Dodatkowy_zaklad(int wybor, int Liczba_graczy, Gracze *tab, int i, int los)
{
	char czy_dalej[2];
	while(true)
	{
		cout << "Czy chcesz obstawic jeszcze jeden zaklad (T-Tak, N-Nie)?: ";
		cin >> czy_dalej;
		if (strcmp(czy_dalej, "T")!=0 && strcmp(czy_dalej, "N")!=0)
		{
			while(strcmp(czy_dalej, "T")!=0 && strcmp(czy_dalej, "N")!=0)
			{
				cout << "Wprowadzono nieprawidlowy wybor! (T-Tak, N-Nie)\n\n";
				break;
			}
		}
		else if (strcmp(czy_dalej, "T")==0)
		{
			system("cls");
			cout << "Dodatkowy zaklad\n";
			Pisz_Menu ();
			wybor_trybu(wybor, Liczba_graczy, tab, i, los);
			break;			
		}
		else if (strcmp(czy_dalej, "N")==0)
		{
			break;
		}
	}	
}


void zmiana_gracza (int i, int Liczba_graczy)
{
	cout << "Koniec zakladow gracza " << i+1 << "\n\n";
	system("pause");
	system("cls");
	if (i<Liczba_graczy-1)
	{
		cout << "Zmiana gracza." << endl;
		system("pause");
	}
	else system("pause");
	system("cls");
}


void Kto_wygral (int Liczba_graczy, Gracze *tab)
{
	int k=0;
	int max=0;
	int zwyciezcy=0;
	for (int i=0; i<Liczba_graczy; i++)
	{
		if((*(tab+i)).liczba_zetonow>max)
		{
			max=(*(tab+i)).liczba_zetonow;
			k=i;
		}
	}
	
	for (int i=0; i<Liczba_graczy; i++)
	{
		if((*(tab+i)).liczba_zetonow==max)
		{
			zwyciezcy++;
		}
	}
	
	if (zwyciezcy>1)
	{
		cout << "Mamy " << zwyciezcy << " zwyciezcow!\n Zdobyliscie " << (*(tab+k)).liczba_zetonow*10 << " punktow! Gratulacje\n";
	}	
	else cout << "Zwyciezca rozgrywki jest " << (*(tab+k)).nazwa_gracza << "!!! Gracz zakonczyl rozgrywke majac " << (*(tab+k)).liczba_zetonow*10 << " punktow!\n";
}


void warunek_koniec(int Liczba_graczy, Gracze *tab)
{
	for (int i=0; i<Liczba_graczy; i++)
	{
		if ((*(tab+i)).liczba_zetonow==0)
		{
			cout << "Jeden z graczy nie ma juz zetonow! Koniec Gry!\n\n";
			cout << "Oto Koncowa Tabela punktowa wszystkich graczy.\n";
			tabela_punktowa(Liczba_graczy, tab);
			Kto_wygral(Liczba_graczy, tab);
			system("pause");
			exit(0);
		}
	}
}


void Wypis_dane()
{
	string dane;
	ifstream plik;
	plik.open("wypis.txt", ios::in);
	while (getline(plik, dane))
	{
		cout << dane << endl;
	}
	plik.close();
	system("del wypis.txt");
}


void wyniki_losowania(int licznik_rund, int los, int Liczba_graczy, Gracze *tab)
{
	system("cls");
	cout << "Koniec rundy nr " << licznik_rund << endl;
	cout << "Wylosowano liczbe " << los << endl;
	Stol_zaznaczenie_pojedynczego_wyboru(los);
	cout << "\n";
	Wypis_dane();
								
	cout << "\nWyniki: \n";
	warunek_koniec(Liczba_graczy, tab);
	tabela_punktowa(Liczba_graczy, tab);
	
	system("pause");
	system("cls");
	Pisz_Menu();
}


void Wpisanie_zetonow_poczatek(int Liczba_graczy, Gracze *tab)
{
	for (int i=0; i<Liczba_graczy; i++)
	{
		(*(tab+i)).liczba_zetonow=100;
	}
}


void Poczatek_gry(int &Liczba_graczy, Gracze *tab)
{
	cout << "\n  ***** WITAMY W GRZE RULETKA *****\n\n";	
	Ile_graczy (Liczba_graczy, tab);	
	cout << "Powodzenia!\n" << endl;;	
	system("PAUSE");	
	system("cls");
	Pisz_Menu ();
}


void Koniec_gry(int Liczba_graczy, Gracze *tab)
{				
	system("cls");
	cout << "Koniec Gry! Dziekujemy za wspolnie spedzony czas.";
	tabela_punktowa(Liczba_graczy, tab);
	cout << endl;
	Kto_wygral (Liczba_graczy, tab);
	cout << "Aby zakonczyc wcisnij Enter.";
	system("Pause");
}

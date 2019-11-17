#include <iostream>
#include <cstring>
using namespace std;

void wyswietl_p01(string *plansza01)
{
  string alfabet = "ABCDEFGHIJ";
  cout << "  ";

  for (int k = 0; k <= 10; k++)
    if (k != 0)
      cout << k << " ";
  cout << endl;
  cout << alfabet[0] << " ";
  for (int i = 1; i < 11; i++)
  {
    for (int j = 1; j < 11; j++)
    {
      cout << *(plansza01 + i * 12 + j) << " "; // plansza[a][b] == *(plansza + i * size <tu: 12> + j)
    }
    cout << endl;
    if (alfabet[i] != 'K')
      cout << alfabet[i] << " ";
  }
    cout<<endl;
}

void wyswietl_p1(string *plansza1)
{
  string alfabet = "ABCDEFGHIJKLMN";

  cout << "  ";
  for (int k = 0; k <= 10; k++)
    if (k != 0)
      cout << k << " ";
  cout << endl;
  cout << alfabet[0] << " ";
  for (int i = 1; i < 11; i++)
  {
    for (int j = 1; j < 11; j++)
    {
      cout << *(plansza1 + 12 * i + j) << " ";
    }
    cout << endl;
    if (alfabet[i] != 'K')
      cout << alfabet[i] << " ";
  }
    cout<<endl;
}

void wyswietl_p2(string *plansza2)
{
  string alfabet = "ABCDEFGHIJ";
  cout << "  ";
  for (int k = 0; k <= 10; k++)
    if (k != 0)
      cout << k << " ";
  cout << endl;
  cout << alfabet[0] << " ";
  for (int i = 1; i < 11; i++)
  {
    for (int j = 1; j < 11; j++)
    {
 cout << *(plansza2 + i * 12 + j) << " ";
    }
    cout << endl;
    if (alfabet[i] != 'K')
      cout << alfabet[i] << " ";
  }
    cout<<endl;
}

void wyswietl_p02(string *plansza02)
{
  string alfabet = "ABCDEFGHIJ";
  cout << "  ";
  for (int k = 0; k <= 10; k++)
    if (k != 0)
      cout << k << " ";
  cout << endl;
  cout << alfabet[0] << " ";
  for (int i = 1; i < 11; i++)
  {
    for (int j = 1; j < 11; j++)
    {
 cout << *(plansza02 + i * 12 + j) << " ";
    }
    cout << endl;
    if (alfabet[i] != 'K')
      cout << alfabet[i] << " ";
  }
  cout<<endl;
}

int main()
{
  char a, b;
  string plansza1[12][12]; //plansza gracza 1 rzeczywista
  string plansza2[12][12];
  string plansza01[12][12]; //plansza gracza nr 1 wyswietlana graczowi drugiemu
  string plansza02[12][12];
  for (int i = 0; i < 12; i++)
  {
    for (int j = 0; j < 12; j++)
      plansza1[j][i] = '-';
  }
  for (int i = 0; i < 12; i++)
  {
    for (int j = 0; j < 12; j++)
      plansza2[j][i] = '-';
  }
  for (int i = 0; i < 12; i++)
  {
    for (int j = 0; j < 12; j++)
      plansza01[j][i] = '-';
  }
  for (int i = 0; i < 12; i++)
  {
    for (int j = 0; j < 12; j++)
      plansza02[j][i] = '-';
  }
  int jedno, dwu, trzy, cztero, piecio;
  plansza02[5][5]=="X";
 wyswietl_p02((string *)plansza02);

  cout << "Niech jeden z graczy wpisze ilosc poszczegolnych statkow." << endl
       << endl;

  cout << "Podaj ilosc jednomasztowcow:";
  cin >> jedno;
  cout << "Podaj ilosc dwumasztowcow:";
  cin >> dwu;
  cout << "Podaj ilosc trzymasztowcow:";
  cin >> trzy;
  cout << "Podaj ilosc czteromasztowcow:";
  cin >> cztero;
  cout << "Podaj ilosc pieciomasztowcow:";
  cin >> piecio;
  int hp1=jedno +(2*dwu)+(3*trzy)+(4*cztero)+(5*piecio);
  int hp2=jedno +(2*dwu)+(3*trzy)+(4*cztero)+(5*piecio);
  cout<<"Teraz gracz nr1 bedzie rozmieszczal swoje statki. Graczu nr2 - nie podgladaj!"<<endl
  <<endl;


  for (int a = 0; a < jedno; a++)
  {
    cout << "Podaj koordynaty jednomasztowca(np.B5). Pamietaj, ze rozne statki nie moga sie stykac burtami:" << endl
         << endl;
    string kord;
    cin >> kord;
    bool mozliwosc_rozstawienia = true;
    int rzad, kolumna;
    if (kord.size() == 2)
    {
      kolumna = kord[0] - 'A' + 1;
      rzad = kord[1] - '0';
    }
    else
    {
      rzad = 10;                  //cyferki(gora)
      kolumna = kord[0] - 65 + 1; //literki(bok)
    }
    if (plansza1[kolumna][rzad] == "-" && plansza1[kolumna-1][rzad-1] == "-" && plansza1[kolumna-1][rzad] == "-" && plansza1[kolumna-1][rzad+1] == "-" && plansza1[kolumna][rzad-1] == "-" && plansza1[kolumna][rzad+1] == "-" && plansza1[kolumna+1][rzad-1] == "-" && plansza1[kolumna+1][rzad] == "-" && plansza1[kolumna+1][rzad+1] == "-")
    {
      plansza1[kolumna][rzad] = "S"; // SWAP kolumna <> rzad
      wyswietl_p1((string *)plansza1);
    }
    else
    {
              cout << "Nie mozesz umiescic 2 statkow w tym samym miejscu. Nie moga sie tez stykac burtami. Sprobuj ustawic statek jeszcze raz" << endl<<endl;
      a--;
    }
  }////////////////////////*rozstawianie dwumasztowcow*///////////////////
for (int a = 0; a < dwu; a++)
  {
    cout << "Teraz podaj koordynaty dzioba DWUMASZTOWCA i (po spacji)kierunek, w ktorym ma byc zwrocony(lewo,prawo,gora,dol)(np.B5 gora - umieszczasz statek na B5 i A5). Pamietaj, ze rozne statki nie moga sie stykac burtami:" << endl
         << endl;
    string kord, kierunek;
    cin >> kord>>kierunek;
    bool mozliwosc_rozstawienia = true;
    int rzad, kolumna;
    if (kord.size() == 2)
    {
      kolumna = kord[0] - 'A' + 1;
      rzad = kord[1] - '0';
    }
    else
    {
      rzad = 10;                  //cyferki(gora)
      kolumna = kord[0] - 65 + 1; //literki(bok)
    }
        if (kierunek[0]=='g'){
        if (kolumna!=1&&plansza1[kolumna][rzad] == "-" && plansza1[kolumna-1][rzad-1] == "-" && plansza1[kolumna-1][rzad] == "-" && plansza1[kolumna-1][rzad+1] == "-" && plansza1[kolumna][rzad-1] == "-" && plansza1[kolumna][rzad+1] == "-" && plansza1[kolumna+1][rzad-1] == "-" && plansza1[kolumna+1][rzad] == "-" && plansza1[kolumna+1][rzad+1] == "-"&&plansza1[kolumna-2][rzad-1] == "-" &&plansza1[kolumna-2][rzad] == "-" &&plansza1[kolumna-2][rzad+1] == "-")
    {
      plansza1[kolumna][rzad] = "S";
      plansza1[kolumna-1][rzad] = "S";
      wyswietl_p1((string *)plansza1);
    }
    else {
                cout << "Nie mozesz umiescic 2 statkow w tym samym miejscu. Nie moga sie tez stykac burtami, oraz wychodzic poza plansze. Sprobuj ustawic statek jeszcze raz." << endl<<endl;
      a--;
    }}
    else if (kierunek[0]=='d'){
        if (kolumna!=10&&plansza1[kolumna][rzad] == "-" && plansza1[kolumna-1][rzad-1] == "-" && plansza1[kolumna-1][rzad] == "-" && plansza1[kolumna-1][rzad+1] == "-" && plansza1[kolumna][rzad-1] == "-" && plansza1[kolumna][rzad+1] == "-" && plansza1[kolumna+1][rzad-1] == "-" && plansza1[kolumna+1][rzad] == "-" && plansza1[kolumna+1][rzad+1] == "-"&&plansza1[kolumna+2][rzad-1] == "-" &&plansza1[kolumna+2][rzad] == "-" &&plansza1[kolumna+2][rzad+1] == "-")
    {
      plansza1[kolumna][rzad] = "S";
      plansza1[kolumna+1][rzad] = "S";
      wyswietl_p1((string *)plansza1);
    }
    else {
                cout << "Nie mozesz umiescic 2 statkow w tym samym miejscu. Nie moga sie tez stykac burtami, oraz wychodzic poza plansze. Sprobuj ustawic statek jeszcze raz." << endl<<endl;
      a--;
    }}
    else if (kierunek[0]=='l'){
        if (rzad!=1&&plansza1[kolumna][rzad] == "-" && plansza1[kolumna-1][rzad-1] == "-" && plansza1[kolumna-1][rzad] == "-" && plansza1[kolumna-1][rzad+1] == "-" && plansza1[kolumna][rzad-1] == "-" && plansza1[kolumna][rzad+1] == "-" && plansza1[kolumna+1][rzad-1] == "-" && plansza1[kolumna+1][rzad] == "-" && plansza1[kolumna+1][rzad+1] == "-"&& plansza1[kolumna-1][rzad-2] == "-"&& plansza1[kolumna][rzad-2] == "-"&& plansza1[kolumna+1][rzad-2] == "-")
    {
      plansza1[kolumna][rzad] = "S";
      plansza1[kolumna][rzad-1] = "S";
      wyswietl_p1((string *)plansza1);
    }
    else {
                cout << "Nie mozesz umiescic 2 statkow w tym samym miejscu. Nie moga sie tez stykac burtami, oraz wychodzic poza plansze. Sprobuj ustawic statek jeszcze raz." << endl<<endl;
      a--;
    }}
    else if (kierunek[0]=='p'){
        if (rzad!=10&&plansza1[kolumna][rzad] == "-" && plansza1[kolumna-1][rzad-1] == "-" && plansza1[kolumna-1][rzad] == "-" && plansza1[kolumna-1][rzad+1] == "-" && plansza1[kolumna][rzad-1] == "-" && plansza1[kolumna][rzad+1] == "-" && plansza1[kolumna+1][rzad-1] == "-" && plansza1[kolumna+1][rzad] == "-" && plansza1[kolumna+1][rzad+1] == "-"&& plansza1[kolumna-1][rzad+2] == "-"&& plansza1[kolumna][rzad+2] == "-"&& plansza1[kolumna+1][rzad+2] == "-")
    {
      plansza1[kolumna][rzad] = "S";
      plansza1[kolumna][rzad+1] = "S";
      wyswietl_p1((string *)plansza1);
    }
    else {
                cout << "Nie mozesz umiescic 2 statkow w tym samym miejscu. Nie moga sie tez stykac burtami, oraz wychodzic poza plansze. Sprobuj ustawic statek jeszcze raz." << endl<<endl;
      a--;
    }
    }

    }///////////////////////////////////////*rozmieszczanie trzymasztowcow*////////////////////////////////////////
for (int a = 0; a < trzy; a++)
  {
    cout << "Teraz podaj koordynaty dzioba TRZYMASZTOWCA i (po spacji)kierunek, w ktorym ma byc zwrocony(lewo,prawo,gora,dol)(np.B5 dol - umieszczasz statek na B5 i C5 i D5). Pamietaj, ze rozne statki nie moga sie stykac burtami:" << endl
         << endl;
    string kord, kierunek;
    cin >> kord>>kierunek;
    bool mozliwosc_rozstawienia = true;
    int rzad, kolumna;
    if (kord.size() == 2)
    {
      kolumna = kord[0] - 'A' + 1;
      rzad = kord[1] - '0';
    }
    else
    {
      rzad = 10;                  //cyferki(gora)
      kolumna = kord[0] - 65 + 1; //literki(bok)
    }
        if (kierunek[0]=='g'){
        if (kolumna!=1&&kolumna!=2&&plansza1[kolumna][rzad] == "-" && plansza1[kolumna-1][rzad-1] == "-" && plansza1[kolumna-1][rzad] == "-" && plansza1[kolumna-1][rzad+1] == "-" && plansza1[kolumna][rzad-1] == "-" && plansza1[kolumna][rzad+1] == "-" && plansza1[kolumna+1][rzad-1] == "-" && plansza1[kolumna+1][rzad] == "-" && plansza1[kolumna+1][rzad+1] == "-"&&plansza1[kolumna-2][rzad-1] == "-" &&plansza1[kolumna-2][rzad] == "-" &&plansza1[kolumna-2][rzad+1] == "-"&&plansza1[kolumna-3][rzad-1] == "-"&&plansza1[kolumna-3][rzad] == "-"&&plansza1[kolumna-3][rzad+1] == "-")
    {
      plansza1[kolumna][rzad] = "S";
      plansza1[kolumna-1][rzad] = "S";
      plansza1[kolumna-2][rzad] = "S";
      wyswietl_p1((string *)plansza1);
    }
    else {
                cout << "Nie mozesz umiescic 2 statkow w tym samym miejscu. Nie moga sie tez stykac burtami, oraz wychodzic poza plansze. Sprobuj ustawic statek jeszcze raz." << endl<<endl;
      a--;
    }}
    else if (kierunek[0]=='d'){
        if (kolumna!=10&&kolumna!=9&&plansza1[kolumna][rzad] == "-" && plansza1[kolumna-1][rzad-1] == "-" && plansza1[kolumna-1][rzad] == "-" && plansza1[kolumna-1][rzad+1] == "-" && plansza1[kolumna][rzad-1] == "-" && plansza1[kolumna][rzad+1] == "-" && plansza1[kolumna+1][rzad-1] == "-" && plansza1[kolumna+1][rzad] == "-" && plansza1[kolumna+1][rzad+1] == "-"&&plansza1[kolumna+2][rzad-1] == "-" &&plansza1[kolumna+2][rzad] == "-" &&plansza1[kolumna+2][rzad+1] == "-"&&plansza1[kolumna+3][rzad+1] == "-"&&plansza1[kolumna+3][rzad] == "-"&&plansza1[kolumna+3][rzad-1] == "-")
    {
      plansza1[kolumna][rzad] = "S";
      plansza1[kolumna+1][rzad] = "S";
      plansza1[kolumna+2][rzad] = "S";
      wyswietl_p1((string *)plansza1);
    }
    else {
                cout << "Nie mozesz umiescic 2 statkow w tym samym miejscu. Nie moga sie tez stykac burtami, oraz wychodzic poza plansze. Sprobuj ustawic statek jeszcze raz." << endl<<endl;
      a--;
    }}
    else if (kierunek[0]=='l'){
        if (rzad!=1&&rzad!=2&&plansza1[kolumna][rzad] == "-" && plansza1[kolumna-1][rzad-1] == "-" && plansza1[kolumna-1][rzad] == "-" && plansza1[kolumna-1][rzad+1] == "-" && plansza1[kolumna][rzad-1] == "-" && plansza1[kolumna][rzad+1] == "-" && plansza1[kolumna+1][rzad-1] == "-" && plansza1[kolumna+1][rzad] == "-" && plansza1[kolumna+1][rzad+1] == "-"&&plansza1[kolumna-1][rzad-2] == "-" &&plansza1[kolumna][rzad-2] == "-" &&plansza1[kolumna+1][rzad-2] == "-"&& plansza1[kolumna-1][rzad-3] == "-"&& plansza1[kolumna][rzad-3] == "-"&& plansza1[kolumna+1][rzad-3] == "-")
    {
      plansza1[kolumna][rzad] = "S";
      plansza1[kolumna][rzad-1] = "S";
      plansza1[kolumna][rzad-2] = "S";
      wyswietl_p1((string *)plansza1);
    }
    else {
                cout << "Nie mozesz umiescic 2 statkow w tym samym miejscu. Nie moga sie tez stykac burtami, oraz wychodzic poza plansze. Sprobuj ustawic statek jeszcze raz." << endl<<endl;
      a--;
    }}
    else if (kierunek[0]=='p'){
        if (rzad!=10&&rzad!=9&&plansza1[kolumna][rzad] == "-" && plansza1[kolumna-1][rzad-1] == "-" && plansza1[kolumna-1][rzad] == "-" && plansza1[kolumna-1][rzad+1] == "-" && plansza1[kolumna][rzad-1] == "-" && plansza1[kolumna][rzad+1] == "-" && plansza1[kolumna+1][rzad-1] == "-" && plansza1[kolumna+1][rzad] == "-" && plansza1[kolumna+1][rzad+1] == "-"&&plansza1[kolumna-1][rzad+2] == "-" &&plansza1[kolumna][rzad+2] == "-" &&plansza1[kolumna+1][rzad+2] == "-"&& plansza1[kolumna-1][rzad+3] == "-"&& plansza1[kolumna][rzad+3] == "-"&& plansza1[kolumna+1][rzad+3] == "-")
    {
      plansza1[kolumna][rzad] = "S";
      plansza1[kolumna][rzad+1] = "S";
      plansza1[kolumna][rzad+2] = "S";
      wyswietl_p1((string *)plansza1);
    }
    else {
                cout << "Nie mozesz umiescic 2 statkow w tym samym miejscu. Nie moga sie tez stykac burtami, oraz wychodzic poza plansze. Sprobuj ustawic statek jeszcze raz." << endl<<endl;
      a--;
    }}
  }
for (int a = 0; a < cztero; a++)
  {
    cout << "Teraz podaj koordynaty dzioba CZTEROMASZTOWCA i (po spacji)kierunek, w ktorym ma byc zwrocony(lewo,prawo,gora,dol). Pamietaj, ze rozne statki nie moga sie stykac burtami:" << endl
         << endl;
    string kord, kierunek;
    cin >> kord>>kierunek;
    bool mozliwosc_rozstawienia = true;
    int rzad, kolumna;
    if (kord.size() == 2)
    {
      kolumna = kord[0] - 'A' + 1;
      rzad = kord[1] - '0';
    }
    else
    {
      rzad = 10;                  //cyferki(gora)
      kolumna = kord[0] - 65 + 1; //literki(bok)
    }
        if (kierunek[0]=='g'){
        if (kolumna!=1&&kolumna!=2&&kolumna!=3&&plansza1[kolumna][rzad] == "-" && plansza1[kolumna-1][rzad-1] == "-" && plansza1[kolumna-1][rzad] == "-" && plansza1[kolumna-1][rzad+1] == "-" && plansza1[kolumna][rzad-1] == "-" && plansza1[kolumna][rzad+1] == "-" && plansza1[kolumna+1][rzad-1] == "-" && plansza1[kolumna+1][rzad] == "-" && plansza1[kolumna+1][rzad+1] == "-"&&plansza1[kolumna-2][rzad-1] == "-" &&plansza1[kolumna-2][rzad] == "-" &&plansza1[kolumna-2][rzad+1] == "-"&&plansza1[kolumna-3][rzad-1] == "-"&&plansza1[kolumna-3][rzad] == "-"&&plansza1[kolumna-3][rzad+1] == "-"&&plansza1[kolumna-4][rzad+1] == "-"&&plansza1[kolumna-4][rzad] == "-"&&plansza1[kolumna-4][rzad-1] == "-")
    {
      plansza1[kolumna][rzad] = "S";
      plansza1[kolumna-1][rzad] = "S";
      plansza1[kolumna-2][rzad] = "S";
      plansza1[kolumna-3][rzad] = "S";
      wyswietl_p1((string *)plansza1);
    }
    else {
                cout << "Nie mozesz umiescic 2 statkow w tym samym miejscu. Nie moga sie tez stykac burtami, oraz wychodzic poza plansze. Sprobuj ustawic statek jeszcze raz." << endl<<endl;
      a--;
    }}
    else if (kierunek[0]=='d'){
        if (kolumna!=10&&kolumna!=9&&kolumna!=8&&plansza1[kolumna][rzad] == "-" && plansza1[kolumna-1][rzad-1] == "-" && plansza1[kolumna-1][rzad] == "-" && plansza1[kolumna-1][rzad+1] == "-" && plansza1[kolumna][rzad-1] == "-" && plansza1[kolumna][rzad+1] == "-" && plansza1[kolumna+1][rzad-1] == "-" && plansza1[kolumna+1][rzad] == "-" && plansza1[kolumna+1][rzad+1] == "-"&&plansza1[kolumna+2][rzad-1] == "-" &&plansza1[kolumna+2][rzad] == "-" &&plansza1[kolumna+2][rzad+1] == "-"&&plansza1[kolumna+3][rzad+1] == "-"&&plansza1[kolumna+3][rzad] == "-"&&plansza1[kolumna+3][rzad-1] == "-"&&plansza1[kolumna+4][rzad-1] == "-"&&plansza1[kolumna+4][rzad] == "-"&&plansza1[kolumna+4][rzad+1] == "-")
    {
      plansza1[kolumna][rzad] = "S";
      plansza1[kolumna+1][rzad] = "S";
      plansza1[kolumna+2][rzad] = "S";
      plansza1[kolumna+3][rzad] = "S";
      wyswietl_p1((string *)plansza1);
    }
    else {
                cout << "Nie mozesz umiescic 2 statkow w tym samym miejscu. Nie moga sie tez stykac burtami, oraz wychodzic poza plansze. Sprobuj ustawic statek jeszcze raz." << endl<<endl;
      a--;
    }}
    else if (kierunek[0]=='l'){
        if (rzad!=1&&rzad!=2&&rzad!=3&&plansza1[kolumna][rzad] == "-" && plansza1[kolumna-1][rzad-1] == "-" && plansza1[kolumna-1][rzad] == "-" && plansza1[kolumna-1][rzad+1] == "-" && plansza1[kolumna][rzad-1] == "-" && plansza1[kolumna][rzad+1] == "-" && plansza1[kolumna+1][rzad-1] == "-" && plansza1[kolumna+1][rzad] == "-" && plansza1[kolumna+1][rzad+1] == "-"&&plansza1[kolumna-1][rzad-2] == "-" &&plansza1[kolumna][rzad-2] == "-" &&plansza1[kolumna+1][rzad-2] == "-"&& plansza1[kolumna-1][rzad-3] == "-"&& plansza1[kolumna][rzad-3] == "-"&& plansza1[kolumna+1][rzad-3] == "-"&& plansza1[kolumna+1][rzad-4] == "-"&& plansza1[kolumna-1][rzad-4] == "-"&& plansza1[kolumna][rzad-4] == "-")
    {
      plansza1[kolumna][rzad] = "S";
      plansza1[kolumna][rzad-1] = "S";
      plansza1[kolumna][rzad-2] = "S";
      plansza1[kolumna][rzad-3] = "S";
      wyswietl_p1((string *)plansza1);
    }
    else {
                cout << "Nie mozesz umiescic 2 statkow w tym samym miejscu. Nie moga sie tez stykac burtami, oraz wychodzic poza plansze. Sprobuj ustawic statek jeszcze raz." << endl<<endl;
      a--;
    }}
    else if (kierunek[0]=='p'){
        if (rzad!=10&&rzad!=9&&rzad!=8&&plansza1[kolumna][rzad] == "-" && plansza1[kolumna-1][rzad-1] == "-" && plansza1[kolumna-1][rzad] == "-" && plansza1[kolumna-1][rzad+1] == "-" && plansza1[kolumna][rzad-1] == "-" && plansza1[kolumna][rzad+1] == "-" && plansza1[kolumna+1][rzad-1] == "-" && plansza1[kolumna+1][rzad] == "-" && plansza1[kolumna+1][rzad+1] == "-"&&plansza1[kolumna-1][rzad+2] == "-" &&plansza1[kolumna][rzad+2] == "-" &&plansza1[kolumna+1][rzad+2] == "-"&& plansza1[kolumna-1][rzad+3] == "-"&& plansza1[kolumna][rzad+3] == "-"&& plansza1[kolumna+1][rzad+3] == "-"&& plansza1[kolumna-1][rzad+4] == "-"&& plansza1[kolumna][rzad+4] == "-"&& plansza1[kolumna+1][rzad+4] == "-")
    {
      plansza1[kolumna][rzad] = "S";
      plansza1[kolumna][rzad+1] = "S";
      plansza1[kolumna][rzad+2] = "S";
      plansza1[kolumna][rzad+3] = "S";
      wyswietl_p1((string *)plansza1);
    }
    else {
                cout << "Nie mozesz umiescic 2 statkow w tym samym miejscu. Nie moga sie tez stykac burtami, oraz wychodzic poza plansze. Sprobuj ustawic statek jeszcze raz." << endl<<endl;
      a--;
    }}
  }
  for (int a = 0; a < piecio; a++)
  {
    cout << "Teraz podaj koordynaty dzioba PIECIOMASZTOWCA i (po spacji)kierunek, w ktorym ma byc zwrocony(lewo,prawo,gora,dol)(np.B5 dol). Pamietaj, ze rozne statki nie moga sie stykac burtami:" << endl
         << endl;
    string kord, kierunek;
    cin >> kord>>kierunek;
    bool mozliwosc_rozstawienia = true;
    int rzad, kolumna;
    if (kord.size() == 2)
    {
      kolumna = kord[0] - 'A' + 1;
      rzad = kord[1] - '0';
    }
    else
    {
      rzad = 10;                  //cyferki(gora)
      kolumna = kord[0] - 65 + 1; //literki(bok)
    }
        if (kierunek[0]=='g'){
        if (kolumna!=1&&kolumna!=2&&kolumna!=3&&kolumna!=4&&plansza1[kolumna][rzad] == "-" && plansza1[kolumna-1][rzad-1] == "-" && plansza1[kolumna-1][rzad] == "-" && plansza1[kolumna-1][rzad+1] == "-" && plansza1[kolumna][rzad-1] == "-" && plansza1[kolumna][rzad+1] == "-" && plansza1[kolumna+1][rzad-1] == "-" && plansza1[kolumna+1][rzad] == "-" && plansza1[kolumna+1][rzad+1] == "-"&&plansza1[kolumna-2][rzad-1] == "-" &&plansza1[kolumna-2][rzad] == "-" &&plansza1[kolumna-2][rzad+1] == "-"&&plansza1[kolumna-3][rzad-1] == "-"&&plansza1[kolumna-3][rzad] == "-"&&plansza1[kolumna-3][rzad+1] == "-"&&plansza1[kolumna-4][rzad+1] == "-"&&plansza1[kolumna-4][rzad] == "-"&&plansza1[kolumna-4][rzad-1] == "-"&&plansza1[kolumna-5][rzad+1] == "-"&&plansza1[kolumna-5][rzad] == "-"&&plansza1[kolumna-5][rzad-1] == "-")
    {
      plansza1[kolumna][rzad] = "S";
      plansza1[kolumna-1][rzad] = "S";
      plansza1[kolumna-2][rzad] = "S";
      plansza1[kolumna-3][rzad] = "S";
      plansza1[kolumna-4][rzad] = "S";
      wyswietl_p1((string *)plansza1);
    }
    else {
                cout << "Nie mozesz umiescic 2 statkow w tym samym miejscu. Nie moga sie tez stykac burtami, oraz wychodzic poza plansze. Sprobuj ustawic statek jeszcze raz." << endl<<endl;
      a--;
    }}
    else if (kierunek[0]=='d'){
        if (kolumna!=10&&kolumna!=9&&kolumna!=8&&kolumna!=7&&plansza1[kolumna][rzad] == "-" && plansza1[kolumna-1][rzad-1] == "-" && plansza1[kolumna-1][rzad] == "-" && plansza1[kolumna-1][rzad+1] == "-" && plansza1[kolumna][rzad-1] == "-" && plansza1[kolumna][rzad+1] == "-" && plansza1[kolumna+1][rzad-1] == "-" && plansza1[kolumna+1][rzad] == "-" && plansza1[kolumna+1][rzad+1] == "-"&&plansza1[kolumna+2][rzad-1] == "-" &&plansza1[kolumna+2][rzad] == "-" &&plansza1[kolumna+2][rzad+1] == "-"&&plansza1[kolumna+3][rzad+1] == "-"&&plansza1[kolumna+3][rzad] == "-"&&plansza1[kolumna+3][rzad-1] == "-"&&plansza1[kolumna+4][rzad-1] == "-"&&plansza1[kolumna+4][rzad] == "-"&&plansza1[kolumna+4][rzad+1] == "-"&&plansza1[kolumna+5][rzad+1] == "-"&&plansza1[kolumna+5][rzad] == "-"&&plansza1[kolumna+5][rzad-1] == "-")
    {
      plansza1[kolumna][rzad] = "S";
      plansza1[kolumna+1][rzad] = "S";
      plansza1[kolumna+2][rzad] = "S";
      plansza1[kolumna+3][rzad] = "S";
      plansza1[kolumna+4][rzad] = "S";
      wyswietl_p1((string *)plansza1);
    }
    else {
                cout << "Nie mozesz umiescic 2 statkow w tym samym miejscu. Nie moga sie tez stykac burtami, oraz wychodzic poza plansze. Sprobuj ustawic statek jeszcze raz." << endl<<endl;
      a--;
    }}
    else if (kierunek[0]=='l'){
        if (rzad!=1&&rzad!=2&&rzad!=3&&rzad!=4&&plansza1[kolumna][rzad] == "-" && plansza1[kolumna-1][rzad-1] == "-" && plansza1[kolumna-1][rzad] == "-" && plansza1[kolumna-1][rzad+1] == "-" && plansza1[kolumna][rzad-1] == "-" && plansza1[kolumna][rzad+1] == "-" && plansza1[kolumna+1][rzad-1] == "-" && plansza1[kolumna+1][rzad] == "-" && plansza1[kolumna+1][rzad+1] == "-"&&plansza1[kolumna-1][rzad-2] == "-" &&plansza1[kolumna][rzad-2] == "-" &&plansza1[kolumna+1][rzad-2] == "-"&& plansza1[kolumna-1][rzad-3] == "-"&& plansza1[kolumna][rzad-3] == "-"&& plansza1[kolumna+1][rzad-3] == "-"&& plansza1[kolumna+1][rzad-4] == "-"&& plansza1[kolumna-1][rzad-4] == "-"&& plansza1[kolumna][rzad-4] == "-"&& plansza1[kolumna-1][rzad-5] == "-"&& plansza1[kolumna][rzad-5] == "-"&& plansza1[kolumna+1][rzad-5] == "-")
    {
      plansza1[kolumna][rzad] = "S";
      plansza1[kolumna][rzad-1] = "S";
      plansza1[kolumna][rzad-2] = "S";
      plansza1[kolumna][rzad-3] = "S";
      plansza1[kolumna][rzad-4] = "S";
      wyswietl_p1((string *)plansza1);
    }
    else {
                cout << "Nie mozesz umiescic 2 statkow w tym samym miejscu. Nie moga sie tez stykac burtami, oraz wychodzic poza plansze. Sprobuj ustawic statek jeszcze raz." << endl<<endl;
      a--;
    }}
    else if (kierunek[0]=='p'){
        if (rzad!=10&&rzad!=9&&rzad!=8&&rzad!=7&&plansza1[kolumna][rzad] == "-" && plansza1[kolumna-1][rzad-1] == "-" && plansza1[kolumna-1][rzad] == "-" && plansza1[kolumna-1][rzad+1] == "-" && plansza1[kolumna][rzad-1] == "-" && plansza1[kolumna][rzad+1] == "-" && plansza1[kolumna+1][rzad-1] == "-" && plansza1[kolumna+1][rzad] == "-" && plansza1[kolumna+1][rzad+1] == "-"&&plansza1[kolumna-1][rzad+2] == "-" &&plansza1[kolumna][rzad+2] == "-" &&plansza1[kolumna+1][rzad+2] == "-"&& plansza1[kolumna-1][rzad+3] == "-"&& plansza1[kolumna][rzad+3] == "-"&& plansza1[kolumna+1][rzad+3] == "-"&& plansza1[kolumna-1][rzad+4] == "-"&& plansza1[kolumna][rzad+4] == "-"&& plansza1[kolumna+1][rzad+4] == "-"&& plansza1[kolumna-1][rzad+5] == "-"&& plansza1[kolumna][rzad+5] == "-"&& plansza1[kolumna+1][rzad+5] == "-")
    {
      plansza1[kolumna][rzad] = "S";
      plansza1[kolumna][rzad+1] = "S";
      plansza1[kolumna][rzad+2] = "S";
      plansza1[kolumna][rzad+3] = "S";
      plansza1[kolumna][rzad+4] = "S";
      wyswietl_p1((string *)plansza1);
    }
    else {
                cout << "Nie mozesz umiescic 2 statkow w tym samym miejscu. Nie moga sie tez stykac burtami, oraz wychodzic poza plansze. Sprobuj ustawic statek jeszcze raz." << endl<<endl;
      a--;
    }}
  }
  ////////////////////////////////////**************************************************************************************************************////////////////////////////////////////////////////////
  cout<<"Teraz gracz nr2 bedzie rozmieszczal swoje statki. Graczu nr1 - nie podgladaj!"<<endl
  <<endl;
  for (int a = 0; a < jedno; a++)
  {
    cout << "Podaj koordynaty jednomasztowca(np.B5). Pamietaj, ze rozne statki nie moga sie stykac burtami:" << endl
         << endl;
    string kord;
    cin >> kord;
    bool mozliwosc_rozstawienia = true;
    int rzad, kolumna;
    if (kord.size() == 2)
    {
      kolumna = kord[0] - 'A' + 1;
      rzad = kord[1] - '0';
    }
    else
    {
      rzad = 10;                  //cyferki(gora)
      kolumna = kord[0] - 65 + 1; //literki(bok)
    }
    if (plansza2[kolumna][rzad] == "-" && plansza2[kolumna-1][rzad-1] == "-" && plansza2[kolumna-1][rzad] == "-" && plansza2[kolumna-1][rzad+1] == "-" && plansza2[kolumna][rzad-1] == "-" && plansza2[kolumna][rzad+1] == "-" && plansza2[kolumna+1][rzad-1] == "-" && plansza2[kolumna+1][rzad] == "-" && plansza2[kolumna+1][rzad+1] == "-")
    {
      plansza2[kolumna][rzad] = "S"; // SWAP kolumna <> rzad
      wyswietl_p2((string *)plansza2);
    }
    else
    {
              cout << "Nie mozesz umiescic 2 statkow w tym samym miejscu. Nie moga sie tez stykac burtami. Sprobuj ustawic statek jeszcze raz" << endl<<endl;
      a--;
    }
  }////////////////////////*rozstawianie dwumasztowcow*///////////////////
for (int a = 0; a < dwu; a++)
  {
    cout << "Teraz podaj koordynaty dzioba DWUMASZTOWCA i (po spacji)kierunek, w ktorym ma byc zwrocony(lewo,prawo,gora,dol)(np.B5 gora - umieszczasz statek na B5 i A5). Pamietaj, ze rozne statki nie moga sie stykac burtami:" << endl
         << endl;
    string kord, kierunek;
    cin >> kord>>kierunek;
    bool mozliwosc_rozstawienia = true;
    int rzad, kolumna;
    if (kord.size() == 2)
    {
      kolumna = kord[0] - 'A' + 1;
      rzad = kord[1] - '0';
    }
    else
    {
      rzad = 10;                  //cyferki(gora)
      kolumna = kord[0] - 65 + 1; //literki(bok)
    }
        if (kierunek[0]=='g'){
        if (kolumna!=1&&plansza2[kolumna][rzad] == "-" && plansza2[kolumna-1][rzad-1] == "-" && plansza2[kolumna-1][rzad] == "-" && plansza2[kolumna-1][rzad+1] == "-" && plansza2[kolumna][rzad-1] == "-" && plansza2[kolumna][rzad+1] == "-" && plansza2[kolumna+1][rzad-1] == "-" && plansza2[kolumna+1][rzad] == "-" && plansza2[kolumna+1][rzad+1] == "-"&&plansza2[kolumna-2][rzad-1] == "-" &&plansza2[kolumna-2][rzad] == "-" &&plansza2[kolumna-2][rzad+1] == "-")
    {
      plansza2[kolumna][rzad] = "S";
      plansza2[kolumna-1][rzad] = "S";
      wyswietl_p2((string *)plansza2);
    }
    else {
                cout << "Nie mozesz umiescic 2 statkow w tym samym miejscu. Nie moga sie tez stykac burtami, oraz wychodzic poza plansze. Sprobuj ustawic statek jeszcze raz." << endl<<endl;
      a--;
    }}
    else if (kierunek[0]=='d'){
        if (kolumna!=10&&plansza2[kolumna][rzad] == "-" && plansza2[kolumna-1][rzad-1] == "-" && plansza2[kolumna-1][rzad] == "-" && plansza2[kolumna-1][rzad+1] == "-" && plansza2[kolumna][rzad-1] == "-" && plansza2[kolumna][rzad+1] == "-" && plansza2[kolumna+1][rzad-1] == "-" && plansza2[kolumna+1][rzad] == "-" && plansza2[kolumna+1][rzad+1] == "-"&&plansza2[kolumna+2][rzad-1] == "-" &&plansza2[kolumna+2][rzad] == "-" &&plansza2[kolumna+2][rzad+1] == "-")
    {
      plansza2[kolumna][rzad] = "S";
      plansza2[kolumna+1][rzad] = "S";
      wyswietl_p2((string *)plansza2);
    }
    else {
                cout << "Nie mozesz umiescic 2 statkow w tym samym miejscu. Nie moga sie tez stykac burtami, oraz wychodzic poza plansze. Sprobuj ustawic statek jeszcze raz." << endl<<endl;
      a--;
    }}
    else if (kierunek[0]=='l'){
        if (rzad!=1&&plansza2[kolumna][rzad] == "-" && plansza2[kolumna-1][rzad-1] == "-" && plansza2[kolumna-1][rzad] == "-" && plansza2[kolumna-1][rzad+1] == "-" && plansza2[kolumna][rzad-1] == "-" && plansza2[kolumna][rzad+1] == "-" && plansza2[kolumna+1][rzad-1] == "-" && plansza2[kolumna+1][rzad] == "-" && plansza2[kolumna+1][rzad+1] == "-"&& plansza2[kolumna-1][rzad-2] == "-"&& plansza2[kolumna][rzad-2] == "-"&& plansza2[kolumna+1][rzad-2] == "-")
    {
      plansza2[kolumna][rzad] = "S";
      plansza2[kolumna][rzad-1] = "S";
      wyswietl_p2((string *)plansza2);
    }
    else {
                cout << "Nie mozesz umiescic 2 statkow w tym samym miejscu. Nie moga sie tez stykac burtami, oraz wychodzic poza plansze. Sprobuj ustawic statek jeszcze raz." << endl<<endl;
      a--;
    }}
    else if (kierunek[0]=='p'){
        if (rzad!=10&&plansza2[kolumna][rzad] == "-" && plansza2[kolumna-1][rzad-1] == "-" && plansza2[kolumna-1][rzad] == "-" && plansza2[kolumna-1][rzad+1] == "-" && plansza2[kolumna][rzad-1] == "-" && plansza2[kolumna][rzad+1] == "-" && plansza2[kolumna+1][rzad-1] == "-" && plansza2[kolumna+1][rzad] == "-" && plansza2[kolumna+1][rzad+1] == "-"&& plansza2[kolumna-1][rzad+2] == "-"&& plansza2[kolumna][rzad+2] == "-"&& plansza2[kolumna+1][rzad+2] == "-")
    {
      plansza2[kolumna][rzad] = "S";
      plansza2[kolumna][rzad+1] = "S";
      wyswietl_p2((string *)plansza2);
    }
    else {
                cout << "Nie mozesz umiescic 2 statkow w tym samym miejscu. Nie moga sie tez stykac burtami, oraz wychodzic poza plansze. Sprobuj ustawic statek jeszcze raz." << endl<<endl;
      a--;
    }
    }

    }///////////////////////////////////////*rozmieszczanie trzymasztowcow*////////////////////////////////////////
for (int a = 0; a < trzy; a++)
  {
    cout << "Teraz podaj koordynaty dzioba TRZYMASZTOWCA i (po spacji)kierunek, w ktorym ma byc zwrocony(lewo,prawo,gora,dol)(np.B5 dol - umieszczasz statek na B5 i C5 i D5). Pamietaj, ze rozne statki nie moga sie stykac burtami:" << endl
         << endl;
    string kord, kierunek;
    cin >> kord>>kierunek;
    bool mozliwosc_rozstawienia = true;
    int rzad, kolumna;
    if (kord.size() == 2)
    {
      kolumna = kord[0] - 'A' + 1;
      rzad = kord[1] - '0';
    }
    else
    {
      rzad = 10;                  //cyferki(gora)
      kolumna = kord[0] - 65 + 1; //literki(bok)
    }
        if (kierunek[0]=='g'){
        if (kolumna!=1&&kolumna!=2&&plansza2[kolumna][rzad] == "-" && plansza2[kolumna-1][rzad-1] == "-" && plansza2[kolumna-1][rzad] == "-" && plansza2[kolumna-1][rzad+1] == "-" && plansza2[kolumna][rzad-1] == "-" && plansza2[kolumna][rzad+1] == "-" && plansza2[kolumna+1][rzad-1] == "-" && plansza2[kolumna+1][rzad] == "-" && plansza2[kolumna+1][rzad+1] == "-"&&plansza2[kolumna-2][rzad-1] == "-" &&plansza2[kolumna-2][rzad] == "-" &&plansza2[kolumna-2][rzad+1] == "-"&&plansza2[kolumna-3][rzad-1] == "-"&&plansza2[kolumna-3][rzad] == "-"&&plansza2[kolumna-3][rzad+1] == "-")
    {
      plansza2[kolumna][rzad] = "S";
      plansza2[kolumna-1][rzad] = "S";
      plansza2[kolumna-2][rzad] = "S";
      wyswietl_p2((string *)plansza2);
    }
    else {
                cout << "Nie mozesz umiescic 2 statkow w tym samym miejscu. Nie moga sie tez stykac burtami, oraz wychodzic poza plansze. Sprobuj ustawic statek jeszcze raz." << endl<<endl;
      a--;
    }}
    else if (kierunek[0]=='d'){
        if (kolumna!=10&&kolumna!=9&&plansza2[kolumna][rzad] == "-" && plansza2[kolumna-1][rzad-1] == "-" && plansza2[kolumna-1][rzad] == "-" && plansza2[kolumna-1][rzad+1] == "-" && plansza2[kolumna][rzad-1] == "-" && plansza2[kolumna][rzad+1] == "-" && plansza2[kolumna+1][rzad-1] == "-" && plansza2[kolumna+1][rzad] == "-" && plansza2[kolumna+1][rzad+1] == "-"&&plansza2[kolumna+2][rzad-1] == "-" &&plansza2[kolumna+2][rzad] == "-" &&plansza2[kolumna+2][rzad+1] == "-"&&plansza2[kolumna+3][rzad+1] == "-"&&plansza2[kolumna+3][rzad] == "-"&&plansza2[kolumna+3][rzad-1] == "-")
    {
      plansza2[kolumna][rzad] = "S";
      plansza2[kolumna+1][rzad] = "S";
      plansza2[kolumna+2][rzad] = "S";
      wyswietl_p2((string *)plansza2);
    }
    else {
                cout << "Nie mozesz umiescic 2 statkow w tym samym miejscu. Nie moga sie tez stykac burtami, oraz wychodzic poza plansze. Sprobuj ustawic statek jeszcze raz." << endl<<endl;
      a--;
    }}
    else if (kierunek[0]=='l'){
        if (rzad!=1&&rzad!=2&&plansza2[kolumna][rzad] == "-" && plansza2[kolumna-1][rzad-1] == "-" && plansza2[kolumna-1][rzad] == "-" && plansza2[kolumna-1][rzad+1] == "-" && plansza2[kolumna][rzad-1] == "-" && plansza2[kolumna][rzad+1] == "-" && plansza2[kolumna+1][rzad-1] == "-" && plansza2[kolumna+1][rzad] == "-" && plansza2[kolumna+1][rzad+1] == "-"&&plansza2[kolumna-1][rzad-2] == "-" &&plansza2[kolumna][rzad-2] == "-" &&plansza2[kolumna+1][rzad-2] == "-"&& plansza2[kolumna-1][rzad-3] == "-"&& plansza2[kolumna][rzad-3] == "-"&& plansza2[kolumna+1][rzad-3] == "-")
    {
      plansza2[kolumna][rzad] = "S";
      plansza2[kolumna][rzad-1] = "S";
      plansza2[kolumna][rzad-2] = "S";
      wyswietl_p2((string *)plansza2);
    }
    else {
                cout << "Nie mozesz umiescic 2 statkow w tym samym miejscu. Nie moga sie tez stykac burtami, oraz wychodzic poza plansze. Sprobuj ustawic statek jeszcze raz." << endl<<endl;
      a--;
    }}
    else if (kierunek[0]=='p'){
        if (rzad!=10&&rzad!=9&&plansza2[kolumna][rzad] == "-" && plansza2[kolumna-1][rzad-1] == "-" && plansza2[kolumna-1][rzad] == "-" && plansza2[kolumna-1][rzad+1] == "-" && plansza2[kolumna][rzad-1] == "-" && plansza2[kolumna][rzad+1] == "-" && plansza2[kolumna+1][rzad-1] == "-" && plansza2[kolumna+1][rzad] == "-" && plansza2[kolumna+1][rzad+1] == "-"&&plansza2[kolumna-1][rzad+2] == "-" &&plansza2[kolumna][rzad+2] == "-" &&plansza2[kolumna+1][rzad+2] == "-"&& plansza2[kolumna-1][rzad+3] == "-"&& plansza2[kolumna][rzad+3] == "-"&& plansza2[kolumna+1][rzad+3] == "-")
    {
      plansza2[kolumna][rzad] = "S";
      plansza2[kolumna][rzad+1] = "S";
      plansza2[kolumna][rzad+2] = "S";
      wyswietl_p2((string *)plansza2);
    }
    else {
                cout << "Nie mozesz umiescic 2 statkow w tym samym miejscu. Nie moga sie tez stykac burtami, oraz wychodzic poza plansze. Sprobuj ustawic statek jeszcze raz." << endl<<endl;
      a--;
    }}
  }
for (int a = 0; a < cztero; a++)
  {
    cout << "Teraz podaj koordynaty dzioba CZTEROMASZTOWCA i (po spacji)kierunek, w ktorym ma byc zwrocony(lewo,prawo,gora,dol). Pamietaj, ze rozne statki nie moga sie stykac burtami:" << endl
         << endl;
    string kord, kierunek;
    cin >> kord>>kierunek;
    bool mozliwosc_rozstawienia = true;
    int rzad, kolumna;
    if (kord.size() == 2)
    {
      kolumna = kord[0] - 'A' + 1;
      rzad = kord[1] - '0';
    }
    else
    {
      rzad = 10;                  //cyferki(gora)
      kolumna = kord[0] - 65 + 1; //literki(bok)
    }
        if (kierunek[0]=='g'){
        if (kolumna!=1&&kolumna!=2&&kolumna!=3&&plansza2[kolumna][rzad] == "-" && plansza2[kolumna-1][rzad-1] == "-" && plansza2[kolumna-1][rzad] == "-" && plansza2[kolumna-1][rzad+1] == "-" && plansza2[kolumna][rzad-1] == "-" && plansza2[kolumna][rzad+1] == "-" && plansza2[kolumna+1][rzad-1] == "-" && plansza2[kolumna+1][rzad] == "-" && plansza2[kolumna+1][rzad+1] == "-"&&plansza2[kolumna-2][rzad-1] == "-" &&plansza2[kolumna-2][rzad] == "-" &&plansza2[kolumna-2][rzad+1] == "-"&&plansza2[kolumna-3][rzad-1] == "-"&&plansza2[kolumna-3][rzad] == "-"&&plansza2[kolumna-3][rzad+1] == "-"&&plansza2[kolumna-4][rzad+1] == "-"&&plansza2[kolumna-4][rzad] == "-"&&plansza2[kolumna-4][rzad-1] == "-")
    {
      plansza2[kolumna][rzad] = "S";
      plansza2[kolumna-1][rzad] = "S";
      plansza2[kolumna-2][rzad] = "S";
      plansza2[kolumna-3][rzad] = "S";
      wyswietl_p2((string *)plansza2);
    }
    else {
                cout << "Nie mozesz umiescic 2 statkow w tym samym miejscu. Nie moga sie tez stykac burtami, oraz wychodzic poza plansze. Sprobuj ustawic statek jeszcze raz." << endl<<endl;
      a--;
    }}
    else if (kierunek[0]=='d'){
        if (kolumna!=10&&kolumna!=9&&kolumna!=8&&plansza2[kolumna][rzad] == "-" && plansza2[kolumna-1][rzad-1] == "-" && plansza2[kolumna-1][rzad] == "-" && plansza2[kolumna-1][rzad+1] == "-" && plansza2[kolumna][rzad-1] == "-" && plansza2[kolumna][rzad+1] == "-" && plansza2[kolumna+1][rzad-1] == "-" && plansza2[kolumna+1][rzad] == "-" && plansza2[kolumna+1][rzad+1] == "-"&&plansza2[kolumna+2][rzad-1] == "-" &&plansza2[kolumna+2][rzad] == "-" &&plansza2[kolumna+2][rzad+1] == "-"&&plansza2[kolumna+3][rzad+1] == "-"&&plansza2[kolumna+3][rzad] == "-"&&plansza2[kolumna+3][rzad-1] == "-"&&plansza2[kolumna+4][rzad-1] == "-"&&plansza2[kolumna+4][rzad] == "-"&&plansza2[kolumna+4][rzad+1] == "-")
    {
      plansza2[kolumna][rzad] = "S";
      plansza2[kolumna+1][rzad] = "S";
      plansza2[kolumna+2][rzad] = "S";
      plansza2[kolumna+3][rzad] = "S";
      wyswietl_p2((string *)plansza2);
    }
    else {
                cout << "Nie mozesz umiescic 2 statkow w tym samym miejscu. Nie moga sie tez stykac burtami, oraz wychodzic poza plansze. Sprobuj ustawic statek jeszcze raz." << endl<<endl;
      a--;
    }}
    else if (kierunek[0]=='l'){
        if (rzad!=1&&rzad!=2&&rzad!=3&&plansza2[kolumna][rzad] == "-" && plansza2[kolumna-1][rzad-1] == "-" && plansza2[kolumna-1][rzad] == "-" && plansza2[kolumna-1][rzad+1] == "-" && plansza2[kolumna][rzad-1] == "-" && plansza2[kolumna][rzad+1] == "-" && plansza2[kolumna+1][rzad-1] == "-" && plansza2[kolumna+1][rzad] == "-" && plansza2[kolumna+1][rzad+1] == "-"&&plansza2[kolumna-1][rzad-2] == "-" &&plansza2[kolumna][rzad-2] == "-" &&plansza2[kolumna+1][rzad-2] == "-"&& plansza2[kolumna-1][rzad-3] == "-"&& plansza2[kolumna][rzad-3] == "-"&& plansza2[kolumna+1][rzad-3] == "-"&& plansza2[kolumna+1][rzad-4] == "-"&& plansza2[kolumna-1][rzad-4] == "-"&& plansza2[kolumna][rzad-4] == "-")
    {
      plansza2[kolumna][rzad] = "S";
      plansza2[kolumna][rzad-1] = "S";
      plansza2[kolumna][rzad-2] = "S";
      plansza2[kolumna][rzad-3] = "S";
      wyswietl_p2((string *)plansza2);
    }
    else {
                cout << "Nie mozesz umiescic 2 statkow w tym samym miejscu. Nie moga sie tez stykac burtami, oraz wychodzic poza plansze. Sprobuj ustawic statek jeszcze raz." << endl<<endl;
      a--;
    }}
    else if (kierunek[0]=='p'){
        if (rzad!=10&&rzad!=9&&rzad!=8&&plansza2[kolumna][rzad] == "-" && plansza2[kolumna-1][rzad-1] == "-" && plansza2[kolumna-1][rzad] == "-" && plansza2[kolumna-1][rzad+1] == "-" && plansza2[kolumna][rzad-1] == "-" && plansza2[kolumna][rzad+1] == "-" && plansza2[kolumna+1][rzad-1] == "-" && plansza2[kolumna+1][rzad] == "-" && plansza2[kolumna+1][rzad+1] == "-"&&plansza2[kolumna-1][rzad+2] == "-" &&plansza2[kolumna][rzad+2] == "-" &&plansza2[kolumna+1][rzad+2] == "-"&& plansza2[kolumna-1][rzad+3] == "-"&& plansza2[kolumna][rzad+3] == "-"&& plansza2[kolumna+1][rzad+3] == "-"&& plansza2[kolumna-1][rzad+4] == "-"&& plansza2[kolumna][rzad+4] == "-"&& plansza2[kolumna+1][rzad+4] == "-")
    {
      plansza2[kolumna][rzad] = "S";
      plansza2[kolumna][rzad+1] = "S";
      plansza2[kolumna][rzad+2] = "S";
      plansza2[kolumna][rzad+3] = "S";
      wyswietl_p2((string *)plansza2);
    }
    else {
                cout << "Nie mozesz umiescic 2 statkow w tym samym miejscu. Nie moga sie tez stykac burtami, oraz wychodzic poza plansze. Sprobuj ustawic statek jeszcze raz." << endl<<endl;
      a--;
    }}
  }
  for (int a = 0; a < piecio; a++)
  {
    cout << "Teraz podaj koordynaty dzioba PIECIOMASZTOWCA i (po spacji)kierunek, w ktorym ma byc zwrocony(lewo,prawo,gora,dol)(np.B5 dol). Pamietaj, ze rozne statki nie moga sie stykac burtami:" << endl
         << endl;
    string kord, kierunek;
    cin >> kord>>kierunek;
    bool mozliwosc_rozstawienia = true;
    int rzad, kolumna;
    if (kord.size() == 2)
    {
      kolumna = kord[0] - 'A' + 1;
      rzad = kord[1] - '0';
    }
    else
    {
      rzad = 10;                  //cyferki(gora)
      kolumna = kord[0] - 65 + 1; //literki(bok)
    }
        if (kierunek[0]=='g'){
        if (kolumna!=1&&kolumna!=2&&kolumna!=3&&kolumna!=4&&plansza2[kolumna][rzad] == "-" && plansza2[kolumna-1][rzad-1] == "-" && plansza2[kolumna-1][rzad] == "-" && plansza2[kolumna-1][rzad+1] == "-" && plansza2[kolumna][rzad-1] == "-" && plansza2[kolumna][rzad+1] == "-" && plansza2[kolumna+1][rzad-1] == "-" && plansza2[kolumna+1][rzad] == "-" && plansza2[kolumna+1][rzad+1] == "-"&&plansza2[kolumna-2][rzad-1] == "-" &&plansza2[kolumna-2][rzad] == "-" &&plansza2[kolumna-2][rzad+1] == "-"&&plansza2[kolumna-3][rzad-1] == "-"&&plansza2[kolumna-3][rzad] == "-"&&plansza2[kolumna-3][rzad+1] == "-"&&plansza2[kolumna-4][rzad+1] == "-"&&plansza2[kolumna-4][rzad] == "-"&&plansza2[kolumna-4][rzad-1] == "-"&&plansza1[kolumna-5][rzad+1] == "-"&&plansza2[kolumna-5][rzad] == "-"&&plansza2[kolumna-5][rzad-1] == "-")
    {
      plansza2[kolumna][rzad] = "S";
      plansza2[kolumna-1][rzad] = "S";
      plansza2[kolumna-2][rzad] = "S";
      plansza2[kolumna-3][rzad] = "S";
      plansza2[kolumna-4][rzad] = "S";
      wyswietl_p2((string *)plansza2);
    }
    else {
                cout << "Nie mozesz umiescic 2 statkow w tym samym miejscu. Nie moga sie tez stykac burtami, oraz wychodzic poza plansze. Sprobuj ustawic statek jeszcze raz." << endl<<endl;
      a--;
    }}
    else if (kierunek[0]=='d'){
        if (kolumna!=10&&kolumna!=9&&kolumna!=8&&kolumna!=7&&plansza2[kolumna][rzad] == "-" && plansza2[kolumna-1][rzad-1] == "-" && plansza2[kolumna-1][rzad] == "-" && plansza2[kolumna-1][rzad+1] == "-" && plansza2[kolumna][rzad-1] == "-" && plansza2[kolumna][rzad+1] == "-" && plansza2[kolumna+1][rzad-1] == "-" && plansza2[kolumna+1][rzad] == "-" && plansza2[kolumna+1][rzad+1] == "-"&&plansza2[kolumna+2][rzad-1] == "-" &&plansza2[kolumna+2][rzad] == "-" &&plansza2[kolumna+2][rzad+1] == "-"&&plansza2[kolumna+3][rzad+1] == "-"&&plansza2[kolumna+3][rzad] == "-"&&plansza2[kolumna+3][rzad-1] == "-"&&plansza2[kolumna+4][rzad-1] == "-"&&plansza2[kolumna+4][rzad] == "-"&&plansza2[kolumna+4][rzad+1] == "-"&&plansza2[kolumna+5][rzad+1] == "-"&&plansza2[kolumna+5][rzad] == "-"&&plansza2[kolumna+5][rzad-1] == "-")
    {
      plansza2[kolumna][rzad] = "S";
      plansza2[kolumna+1][rzad] = "S";
      plansza2[kolumna+2][rzad] = "S";
      plansza2[kolumna+3][rzad] = "S";
      plansza2[kolumna+4][rzad] = "S";
      wyswietl_p2((string *)plansza2);
    }
    else {
                cout << "Nie mozesz umiescic 2 statkow w tym samym miejscu. Nie moga sie tez stykac burtami, oraz wychodzic poza plansze. Sprobuj ustawic statek jeszcze raz." << endl<<endl;
      a--;
    }}
    else if (kierunek[0]=='l'){
        if (rzad!=1&&rzad!=2&&rzad!=3&&rzad!=4&&plansza2[kolumna][rzad] == "-" && plansza2[kolumna-1][rzad-1] == "-" && plansza2[kolumna-1][rzad] == "-" && plansza2[kolumna-1][rzad+1] == "-" && plansza2[kolumna][rzad-1] == "-" && plansza2[kolumna][rzad+1] == "-" && plansza2[kolumna+1][rzad-1] == "-" && plansza2[kolumna+1][rzad] == "-" && plansza2[kolumna+1][rzad+1] == "-"&&plansza2[kolumna-1][rzad-2] == "-" &&plansza2[kolumna][rzad-2] == "-" &&plansza2[kolumna+1][rzad-2] == "-"&& plansza2[kolumna-1][rzad-3] == "-"&& plansza2[kolumna][rzad-3] == "-"&& plansza2[kolumna+1][rzad-3] == "-"&& plansza2[kolumna+1][rzad-4] == "-"&& plansza2[kolumna-1][rzad-4] == "-"&& plansza2[kolumna][rzad-4] == "-"&& plansza2[kolumna-1][rzad-5] == "-"&& plansza2[kolumna][rzad-5] == "-"&& plansza2[kolumna+1][rzad-5] == "-")
    {
      plansza2[kolumna][rzad] = "S";
      plansza2[kolumna][rzad-1] = "S";
      plansza2[kolumna][rzad-2] = "S";
      plansza2[kolumna][rzad-3] = "S";
      plansza2[kolumna][rzad-4] = "S";
      wyswietl_p2((string *)plansza2);
    }
    else {
                cout << "Nie mozesz umiescic 2 statkow w tym samym miejscu. Nie moga sie tez stykac burtami, oraz wychodzic poza plansze. Sprobuj ustawic statek jeszcze raz." << endl<<endl;
      a--;
    }}
    else if (kierunek[0]=='p'){
        if (rzad!=10&&rzad!=9&&rzad!=8&&rzad!=7&&plansza2[kolumna][rzad] == "-" && plansza2[kolumna-1][rzad-1] == "-" && plansza2[kolumna-1][rzad] == "-" && plansza2[kolumna-1][rzad+1] == "-" && plansza2[kolumna][rzad-1] == "-" && plansza2[kolumna][rzad+1] == "-" && plansza2[kolumna+1][rzad-1] == "-" && plansza2[kolumna+1][rzad] == "-" && plansza2[kolumna+1][rzad+1] == "-"&&plansza2[kolumna-1][rzad+2] == "-" &&plansza2[kolumna][rzad+2] == "-" &&plansza2[kolumna+1][rzad+2] == "-"&& plansza2[kolumna-1][rzad+3] == "-"&& plansza2[kolumna][rzad+3] == "-"&& plansza2[kolumna+1][rzad+3] == "-"&& plansza2[kolumna-1][rzad+4] == "-"&& plansza2[kolumna][rzad+4] == "-"&& plansza2[kolumna+1][rzad+4] == "-"&& plansza2[kolumna-1][rzad+5] == "-"&& plansza2[kolumna][rzad+5] == "-"&& plansza2[kolumna+1][rzad+5] == "-")
    {
      plansza2[kolumna][rzad] = "S";
      plansza2[kolumna][rzad+1] = "S";
      plansza2[kolumna][rzad+2] = "S";
      plansza2[kolumna][rzad+3] = "S";
      plansza2[kolumna][rzad+4] = "S";
      wyswietl_p2((string *)plansza2);
    }
    else {
                cout << "Nie mozesz umiescic 2 statkow w tym samym miejscu. Nie moga sie tez stykac burtami, oraz wychodzic poza plansze. Sprobuj ustawic statek jeszcze raz." << endl<<endl;
      a--;
    }}
  }
cout<< "                     Rozpoczyna sie bitwa!"<<endl;
  while(hp1>0||hp2>0)
  {
    wyswietl_p02((string *)plansza02);
    cout << "Graczu nr1 - podaj koordynaty strzalu na gracza nr2 (np.B5):" << endl
         << endl;
    string kord;
    cin >> kord;
    int rzad, kolumna;

        if (kord.size() == 2)
        {
        kolumna = kord[0] - 'A' + 1;
        rzad = kord[1] - '0';
        }
        else
        {
      rzad = 10;                  //cyferki(gora)
      kolumna = kord[0] - 65 + 1; //literki(bok)
        }
            cout<<kolumna<<rzad;
        if (plansza2[kolumna][rzad]=="S"){
        if(plansza2[kolumna-1][rzad]=="S"||plansza2[kolumna+1][rzad]=="S"||plansza2[kolumna][rzad+1]=="S"||plansza2[kolumna][rzad-1]=="S")
        {
        cout<<"Trafiony!"<<endl;
        plansza02[kolumna][rzad]== "X";
        wyswietl_p02((string *)plansza02);
        hp2--;
        }
        else
        {
            cout<<"Trafiony! Zatopiony!"<<endl;
            plansza02[kolumna][rzad]=="X";
             wyswietl_p02((string *)plansza02);
            hp2--;
        }
        }
        else if (plansza2[kolumna][rzad]=="-")
        {
            cout<<"Pudlo!"<<endl;
            plansza02[kolumna][rzad]=="O";
            wyswietl_p02((string *)plansza02);
        }

    }
}

#include<iostream>
#include<ctime>
#include<string>

using std::cout;
using std::cin;
using std::endl;
using std::string;

int getValCard(int);
void GetTabCard(int[][2]);
void ShuffleDecK(int[][2]);
string AfficheCarte(int, int);
void TirerCarte(int &, int &, int &,int[][2],int Playa);
void unTourdeTable(int[][2], int*, int &, int &, int &, int Cont);
int Valeurdelamain(int[][3],int);
int CheckforOutandElevensandBj(int[][3],int);
bool PlayerContains1(int, int[][3]);


int CardDrawn[52][3];
int index = 0;
int money[] = { 0,100, 100, 100, 100 };
int valcache = 0;
void main()
{
	system("color F0");
	srand(time(0));
	int TabCard[52][2];
	GetTabCard(TabCard);
	ShuffleDecK(TabCard);
	int Count = 0, Ncard = 0, CCard = 0;
	int tabplayer[] = { 1, 2, 3, 4 };
	int Affichage = 4;
	cout << "		Bienvenue au jeu de Grey Jack" << endl << endl;
	char merdique;
	do{
		unTourdeTable(TabCard, tabplayer, Count, Ncard, CCard, 0);
		cout << "Joueur 1   Joueur 2   Joueur 3   Joueur 4" << endl;
		cout << "                                 " << AfficheCarte(CardDrawn[Affichage-1][1], CardDrawn[Affichage-1][2]) << endl;
		unTourdeTable(TabCard, tabplayer, Count, Ncard, CCard, 0);
		cout << AfficheCarte(CardDrawn[Affichage][1], CardDrawn[Affichage][2]) << "         " << AfficheCarte(CardDrawn[Affichage + 1][1], CardDrawn[Affichage + 1][2]) << "         " << AfficheCarte(CardDrawn[Affichage + 2][1], CardDrawn[Affichage + 2][2]) << "         " << AfficheCarte(CardDrawn[Affichage + 3][1], CardDrawn[Affichage + 3][2]) << "         ";
		char Continue;
		cout << "	  Continuer de tirer (o/n) ?? ";
		cin >> Continue;
		while (Continue == 'o')
		{
			unTourdeTable(TabCard, tabplayer, Count, Ncard, CCard, 0);
			if (CheckforOutandElevensandBj(CardDrawn, 0) == 0)
			{
				break;
			}
		}
		if (Continue != 'o'){
			unTourdeTable(TabCard, tabplayer, Count, Ncard, CCard, 1);
			CheckforOutandElevensandBj(CardDrawn, 1);
		}
		cout << "Voulez vous continuere (o/n) " << endl;
		cin >> merdique;
		Affichage = Count;
		if (Count >= 52)
		{
			break;
		}
	} while (merdique == 'o');
	
}
bool PlayerContains1(int player, int drawn[][3])
{
	for (int i = 0; i <= 52; i++)
	{
		if (drawn[i][0] == player)
		{
			if (drawn[i][1] == 1)
			{
				return true;
			}
		}
	}
	return false;
}
int CheckforOutandElevensandBj(int CardsDrawn[][3],int cont)
{
	int value = 0;
	int TabScoreP[] = { 0, 0, 0, 0, 0 };
	bool bj = false;
	int pwinner;
	string affichage[] = { "", "", "", "", "" };
	for (int i = 1; i <= 4; i++)
	{
		value = Valeurdelamain(CardsDrawn, i);
		if (value > 21 && PlayerContains1(i, CardsDrawn))
		{
			value -= 10;
			TabScoreP[i] = value;
		}
		else
		{
			TabScoreP[i] = value;
		}
		for (int j = 8; j < 52; j++)
		{
			if (CardsDrawn[j][0] == i)
			{
				affichage[i] = AfficheCarte(CardsDrawn[j][1], CardsDrawn[j][2]);
			}
		}
	}
	for (int i = 1; i <= 4; i++)
	{
		if (TabScoreP[i] > 21)
		{
			TabScoreP[i] = -1;
			affichage[i] = "OUT";
		}
		else if (TabScoreP[i] == 21)
		{
			affichage[i] = "BJ**";
			bj = true;
		}
	}
	if (TabScoreP[4] > 21 || bj || cont == 1)
	{
		affichage[1] == "" ? cout << "           " : cout << affichage[1] << "        ";
		affichage[2] == "" ? cout << "           " : cout << affichage[2] << "        ";
		affichage[3] == "" ? cout << "           " : cout << affichage[3] << "        ";
		affichage[4] == "" ? cout << "           " : cout << affichage[4] << "        " << endl;

		pwinner = 1;
		for (int i = 1; i < 4; i++)
			pwinner = (TabScoreP[i] < TabScoreP[i+1]) ? i+1 : i;

		for (int i = 1; i <= 4; i++)
			(i == pwinner) ? money[i] += 30 : money[i] -= 10;

		cout << "Argent restant" << endl;
		cout << money[1] << "         " << money[2] << "         " << money[3] << "         " << money[4] << "         " << endl;

		cout << "la valeur de la main du joueur 1 dont la carte cachee est de " << AfficheCarte(CardsDrawn[valcache][1], CardsDrawn[valcache][2]) << " Vaut : " << TabScoreP[1] << endl;
		cout << "la valeur de la main du joueur 2 dont la carte cachee est de " << AfficheCarte(CardsDrawn[valcache+1][1], CardsDrawn[valcache+1][2]) << " Vaut : " << TabScoreP[2] << endl;
		cout << "la valeur de la main du joueur 3 dont la carte cachee est de " << AfficheCarte(CardsDrawn[valcache+2][1], CardsDrawn[valcache+2][2]) << " Vaut : " << TabScoreP[3] << endl;
		cout << "La valeur de votre main est de : " << TabScoreP[4] << endl;
		return 0;
	}
	else
	{
		return 1;
	}
}
int Valeurdelamain(int CardsDrawn[][3], int Player)
{
	int Val = 0;
	for (int i = 0; i < 30; i++)
	{
		if (CardsDrawn[i][0] == Player)
		{
			Val += getValCard(CardsDrawn[i][1]);
		}
	}
	return Val;
}

void unTourdeTable(int TabCards[][2], int * TabPlayers,int &Count,int &Ncard,int &Ccard, int Cont)
{
	for (int i = 0; i < 3; i++)
	{
			if (Valeurdelamain(CardDrawn, i + 1)< 17)
				TirerCarte(Count, Ncard, Ccard, TabCards,i+1);
	}
	if (Cont == 0)
	{
		TirerCarte(Count, Ncard, Ccard, TabCards, 4);
	}
}

int getValCard(int Card)
{
	if (Card < 10)
	{
		if (Card == 1)
		{
			return 11;
		}
		else
		{
			return Card;
		}
	}
	else
	{
		return 10;
	}
}
void GetTabCard(int Tab[][2])
{
	int casesuiv = 0;
	for (int i = 1; i <= 13; i++)
	{
		for (int j = 1; j <= 4; j++)
		{
			Tab[casesuiv][0] = i;
			Tab[casesuiv][1] = j;
			casesuiv++;
		}
	}
}
void ShuffleDecK(int Tab[][2])
{
	int randRow;
	int Num1Alter,Num2Alter;
	for (int i = 0; i < 52; i++)
	{
		randRow = rand() % 52;
		Num1Alter = Tab[randRow][0];
		Num2Alter = Tab[randRow][1];
		Tab[randRow][0] = Tab[i][0];
		Tab[randRow][1] = Tab[i][1];
		Tab[i][0] = Num1Alter;
		Tab[i][1] = Num2Alter;
	}
}
string AfficheCarte(int Alternate1, int Alternate2)
{
	string OutputType[]= {"0","C","K","T","P"};
	string preview;
	if (Alternate1 < 11)
	{
		return std::to_string(Alternate1) + OutputType[Alternate2];
	}
	else
	{
		switch (Alternate1)
		{
		case 11:
			preview =  "V" + OutputType[Alternate2];
			return preview;
			break;
		case 12:
			preview = "D" + OutputType[Alternate2];
			return preview;
			break;
		case 13:
			preview =  "R" + OutputType[Alternate2];
			return preview;
			break;
		default:
			return "";
			break;
		}
	}
}
void TirerCarte(int & CountTab, int & NCard, int & Color,int Tab[][2], int Playa)
{
	NCard = Tab[CountTab][0];
	Color = Tab[CountTab][1];
	CountTab++;
	CardDrawn[index][0] = Playa;
	CardDrawn[index][1] = NCard;
	CardDrawn[index][2] = Color;
	index++;
}
//--------------------------------------------------------
//
//  Programme principal en mode console permettant de 
//  mettre en marche la solution au trajet du cavalier
//
//  Solution de départ pour les étudiants
//  par Pierre Prud'homme, novembre 2008
//--------------------------------------------------------
#include "board.h"
#include <iostream>
using namespace std;

unsigned int Lecture_Bornee (const unsigned int Borne_Min, const unsigned int Borne_Max);
void LireCoordonneesDepart  (unsigned int &x, unsigned int &y);
bool VeutUneTrace();

int main()
{
	system("Color f0");
	unsigned int x, y;

	LireCoordonneesDepart(x, y);
	CBoard oEchiquier (cout, VeutUneTrace());
	oEchiquier.PlacerCavalier(x,y);

}

void LireCoordonneesDepart(unsigned int &x, unsigned int &y)
{
	cout << "Coordonnee ligne; ";
	x = Lecture_Bornee(0, 7);
	cout << "Coordonnee colonne; ";
	y = Lecture_Bornee(0, 7);
}

unsigned int Lecture_Bornee (const unsigned int Borne_Min, const unsigned int Borne_Max)
{
   unsigned int Valeur_Lue;
   do
   {
      cout << "entrez un entier entre "
           << Borne_Min
           << " et "
           << Borne_Max
           << " inclusivement: ";
      cin >> Valeur_Lue;
   }
   while (Valeur_Lue < Borne_Min || Valeur_Lue > Borne_Max);
   return Valeur_Lue;
}

bool VeutUneTrace()
{
	char cReponse;

	cout << "Voulez-vous voir la trace d'execution (O/N) : ";
	cin >> cReponse;
	while (toupper(cReponse) != 'N' &&
		   toupper(cReponse) != 'O')
	{
		cout << "Voulez-vous voir la trace d'execution (O/N) : ";
		cin >> cReponse;
	}
	return (toupper(cReponse) == 'O');
}
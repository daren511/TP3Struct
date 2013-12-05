// Board.cpp: implementation of the CBoard class.
//
//////////////////////////////////////////////////////////////////////
#include "Board.h"
#include "atltime.h"   // pour la méthode Wait
#include <string>
using namespace std;

const int CBoard::MAXCASES = 8;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBoard::CBoard(ostream & sortie, bool veutTrace)
:out_(sortie), faireTrace_(veutTrace)
{
	grilleVisitee_.SetNbLignes(MAXCASES);
	grilleVisitee_.SetNbColonnes(MAXCASES);
	grilleTrajet_.SetNbLignes(MAXCASES);
	grilleTrajet_.SetNbColonnes(MAXCASES);

	for (int i=0; i<MAXCASES; i++)
		for (int j=0; j<MAXCASES; j++)
		{
			grilleVisitee_[i][j] = false;
			grilleTrajet_[i][j] = -1;
			noPasDuTrajet_ = 0;
		}
	continuerRecherche_ = true;
	nbDeSolutions_ = 0;
}

CBoard::~CBoard()
{
}

void CBoard::PlacerCavalier(unsigned int i, unsigned int j)
{
	ligneDepart_ = i;
	colonneDepart_ = j;
	PlacerCavalier (ligneDepart_, colonneDepart_);
}

	
	//Etablir les cases que l'on peut aller visiter à partir de la position reçue
	//Pour chaque case que l'on peut visiter à partir de cette position
	//	visiter cette case
	//	si (toutes les cases sont visitées)
	//		C'est fini
	//	sinon
	//		PlacerCavalier(coordonnées de cette case)
	//	finsi
	//	dévisiter cette case
	//finpour
void CBoard::PlacerCavalier(int i, int j)
{
	// Faire le nécessaire pour visiter cette case où on arrive
	grilleVisitee_[i][j] = true;
	grilleTrajet_[i][j]  = noPasDuTrajet_;
	noPasDuTrajet_++;

	if (faireTrace_) AfficherTrajetTrace();
	if (ToutEstVisite())
	{
		// Afficher à l'écran
		system("cls");
		AfficherTrajet(++nbDeSolutions_);
		system("pause"); 
	}
	else
	{
		// Etablir la liste des cases qu'on peut atteindre
		// Tantque la liste n'est pas vide
		//    retirer la première coordonnée a visiter
		//    Placer le Cavalier sur cette coordonnee
		// fin tantque
	}

	// Faire le nécessaire pour "dévisiter" cette case que l'on quitte 
}

void CBoard::AfficherNoSolution(int noSolution)
{
	out_ << endl 
		<< "Solution #" << noSolution << endl;
}

void CBoard::AfficherTrajet(int noSolution)
{
	out_ << "Cavalier en (" << ligneDepart_ << ", " << colonneDepart_ << ")" << endl;
	out_ << string(41,'-') << endl;
	for (int i=0; i<MAXCASES; i++)
	{
		out_ << "| ";
		for (int j = 0; j < MAXCASES; j++)
		{
			if (grilleTrajet_[i][j] != 0)
			{
				out_.width(2);
				out_ << grilleTrajet_[i][j] << " | ";
			}
			else
			{
				out_ << " C | ";
			}
		}
		out_ << endl;
		out_ << string(41,'-') << endl;
	}
	AfficherNoSolution( noSolution );
}

void CBoard::AfficherTrajetTrace()
{
	system("cls");
	out_ << string(41,'-') << endl;
	for (int i=0; i<MAXCASES; i++)
	{
		out_ << "| ";
		for (int j=0; j<MAXCASES; j++)
		{
			if (grilleTrajet_[i][j] != 0 && grilleTrajet_[i][j] != -1)
			{
				out_.width(2);
				out_ << grilleTrajet_[i][j] << " | ";
			}
			else if (grilleTrajet_[i][j] == -1)
			{
				out_ << "   | ";
			}
			else
			{
				out_ << " C | ";
			}
		}
		out_ << endl;
		out_ << string(41,'-') << endl;
	}
	Wait(1);
}

void CBoard::Wait(int nbSec)
{
	CTime startTime = CTime::GetCurrentTime();
	CTime endTime= CTime::GetCurrentTime();
	CTimeSpan elapsedTime = endTime - startTime;
	while (elapsedTime < nbSec)
	{
		endTime = CTime::GetCurrentTime();
		elapsedTime = endTime - startTime;
	}
}

bool CBoard::ToutEstVisite()
{
	return (noPasDuTrajet_ >= ((MAXCASES * MAXCASES)));
}

void CBoard::SetTrace(bool b)
{
	faireTrace_ = b;
}

CBoard::Position::Position(unsigned int i,unsigned int j) // Structure pour la position dans Verif boite -> Quadrant
{
	PosI = i;
	PosJ = j;
}
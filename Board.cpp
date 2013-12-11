// Board.cpp: implementation of the CBoard class.
//
//////////////////////////////////////////////////////////////////////
#include "Board.h"
#include "atltime.h"   // pour la méthode Wait
#include <string>
#include "Poids.h"
#include <algorithm>
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
	PoidsMatrice_.SetNbLignes(MAXCASES);
	PoidsMatrice_.SetNbColonnes(MAXCASES);

	for (int i=0; i<MAXCASES; i++)
		for (int j=0; j<MAXCASES; j++)
		{
			PoidsMatrice_[i][j].SetX(i);
			PoidsMatrice_[i][j].SetX(j);
			int DetPoids = DeterminerPoids(i,j);
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

void CBoard::PlacerCavalier(int i, int j)
{
	if( continuerRecherche_)
	{
		grilleVisitee_[i][j] = true;
		grilleTrajet_[i][j]  = noPasDuTrajet_;
		noPasDuTrajet_++;
		vector <CPoids> PasChevalier;
		ChercherCase(PasChevalier , i , j);
		for (int i = 0; i < PasChevalier.size() && continuerRecherche_; i++)
		{
			if (faireTrace_) 
				AfficherTrajetTrace();
			
			if (ToutEstVisite())
			{
				// Afficher à l'écran
				grilleTrajet_[PasChevalier[i].GetX()][PasChevalier[i].GetY()];
				continuerRecherche_ = false;
				system("cls");
				AfficherTrajet(++nbDeSolutions_);
			}
			else
			PlacerCavalier(PasChevalier[i].GetX(),PasChevalier[i].GetY());
			
			if ( continuerRecherche_)
			{
				grilleTrajet_[PasChevalier[i].GetX()][PasChevalier[i].GetY()] = -1;
				grilleVisitee_[PasChevalier[i].GetX()][PasChevalier[i].GetY()] = false;
				noPasDuTrajet_--;

			}	
		}
	}
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

/*
CBoard::Position::Position(unsigned int i,unsigned int j) // Structure pour la position dans Verif boite -> Quadrant
{
	PosI = i;
	PosJ = j;

}
*/

int CBoard::DeterminerPoids(int i , int j )
{
	
   int NbPossibilités = 0;

   if( i-2 >= 0 && j-1 >= 0)
      NbPossibilités++;
   
   if( i-1 >= 0 && j-2 >=0)
      NbPossibilités++;

   if( i+2 < MAXCASES && j-1 >= 0)
      NbPossibilités++;

   if( i+1 < MAXCASES && j-2 >= 0)
      NbPossibilités++;


   if( i-2 >= 0 && j+1 < MAXCASES)
      NbPossibilités++;

   if( i-1 >= 0 && j+2 < MAXCASES)
      NbPossibilités++;

   if( i+1 < MAXCASES && j+2 < MAXCASES)
      NbPossibilités++;

   if( i+2 < MAXCASES && j+1 < MAXCASES)
      NbPossibilités++;

   return NbPossibilités;
}
void CBoard::ChercherCase(vector<CPoids> &PasChevalier , int i , int j)
{
	if( i-1 >= 0 && j-2 >=0)
   {
      if (!grilleVisitee_[i-1][j-2])
         PasChevalier.push_back(PoidsMatrice_[i-1][j-2]);
   }

   if( i-2 >= 0 && j-1 >= 0)
   {
      if (!grilleVisitee_[i-2][j-1])
         PasChevalier.push_back(PoidsMatrice_[i-2][j-1]);
   }

   if( i-2 >= 0 && j+1 < MAXCASES)
   {
      if (!grilleVisitee_[i-2][j+1])
         PasChevalier.push_back(PoidsMatrice_[i-2][j+1]);
   }

   if( i-1 >= 0 && j+2 < MAXCASES)
   {
      if (!grilleVisitee_[i-1][j+2])
         PasChevalier.push_back(PoidsMatrice_[i-1][j+2]);
   }

   if( i+1 < MAXCASES && j+2 < MAXCASES)
   {
      if (!grilleVisitee_[i+1][j+2])
         PasChevalier.push_back(PoidsMatrice_[i+1][j+2]);
   }

   if( i+2 < MAXCASES && j+1 < MAXCASES)
   {
      if (!grilleVisitee_[i+2][j+1])
         PasChevalier.push_back(PoidsMatrice_[i+2][j+1]);
   }

   if( i+2 < MAXCASES && j-1 >= 0)
   {
      if (!grilleVisitee_[i+2][j-1])
         PasChevalier.push_back(PoidsMatrice_[i+2][j-1]);
   }

   if( i+1 < MAXCASES && j-2 >= 0)
   {
      if (!grilleVisitee_[i+1][j-2])
         PasChevalier.push_back(PoidsMatrice_[i+1][j-2]);
   }
   sort(PasChevalier.begin(),PasChevalier.end());
}


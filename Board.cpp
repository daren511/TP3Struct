//////////////////////////////////////////////////////////////////////
// B O A R D . C P P
// 12 Décembre 2012
// Francis Côté & Daren Ken St- Laurent
//////////////////////////////////////////////////////////////////////
#include "Board.h"
#include "Poids.h"
#include "atltime.h"   // pour la méthode Wait
#include <algorithm>
#include <string>
using namespace std;

const int CBoard::MAXCASES = 8;

//////////////////////////////////////////////////////////////////////
// C O N S T R U C T I O N / D E S T R U C T I O N
//////////////////////////////////////////////////////////////////////

CBoard::CBoard(ostream & sortie, bool veutTrace)
   :out_(sortie), faireTrace_(veutTrace)
{
   grilleVisitee_.SetNbLignes(MAXCASES);
   grilleVisitee_.SetNbColonnes(MAXCASES);
   grilleTrajet_.SetNbLignes(MAXCASES);
   grilleTrajet_.SetNbColonnes(MAXCASES);
   PoidsGrille_.SetNbLignes(MAXCASES);
   PoidsGrille_.SetNbColonnes(MAXCASES);

   for (int i=0; i<MAXCASES; i++)
      for (int j=0; j<MAXCASES; j++)
      {
		  PoidsGrille_[i][j].PosI_ = i;
		  PoidsGrille_[i][j].PosJ_ = j; 
         int Poids = TrouverPoids(i,j);
		 PoidsGrille_[i][j].poids_ = Poids;
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

CBoard::Position::Position(int i, int j,int poids)
{
	PosI_ = i;
	PosJ_ = j;
	poids_ = poids;
}
CBoard::Position::operator int()
{
   return poids_;
}


/////////////////////////////////////////////////////////////
// P L A C E R  C A V A L I E R
/////////////////////////////////////////////////////////////
void CBoard::PlacerCavalier(unsigned int i, unsigned int j)
{
   ligneDepart_ = i;
   colonneDepart_ = j;
   PlacerCavalier (ligneDepart_, colonneDepart_);
}


void CBoard::PlacerCavalier(int i, int j)
{
   if ( continuerRecherche_)
   {
      grilleVisitee_[i][j] = true;
      grilleTrajet_[i][j]  = noPasDuTrajet_;
      noPasDuTrajet_++;
      vector <Position> PasChevalier; // Déclaration du vecteur de déplacement chevalier
      TrouverCase(PasChevalier , i , j); // Fonction pour trouver la meilleure case 
      for ( int a = 0 ; a < PasChevalier.size() && continuerRecherche_ ; a++)
      {
         if (faireTrace_ ) 
            AfficherTrajetTrace();

         if(ToutEstVisite())
         {
			 grilleTrajet_[PasChevalier[a].PosI_][PasChevalier[a].PosJ_]  = noPasDuTrajet_;
            continuerRecherche_ = false;
            system("cls");
            AfficherTrajet(++nbDeSolutions_); 
         }
         else
         {
            PlacerCavalier(PasChevalier[a].PosI_ , PasChevalier[a].PosJ_);
         }
         if ( continuerRecherche_)
         {
            grilleTrajet_[PasChevalier[a].PosI_] [PasChevalier[a].PosJ_]  = -1;
            grilleVisitee_[PasChevalier[a].PosI_] [PasChevalier[a].PosJ_] = false;
            noPasDuTrajet_--;
         }	
      }
   }
}


/////////////////////////////////////////////////////////////////////
// M É T H O D E S  D ' A F F I C H A G E
/////////////////////////////////////////////////////////////////////
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


///////////////////////////////////////////////////////
// W A I T 
///////////////////////////////////////////////////////
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

/////////////////////////////////////////////////////
// T O U T E  E S T  V I S I T E
/////////////////////////////////////////////////////
bool CBoard::ToutEstVisite()
{
   return (noPasDuTrajet_ >= ((MAXCASES * MAXCASES)- 1));
}

/////////////////////////////////////////////////////
// S E T  T R A C E
/////////////////////////////////////////////////////
void CBoard::SetTrace(bool b)
{
   faireTrace_ = b;
}
////////////////////////////////////////////////////
// T R O U V E R  C A S E S
////////////////////////////////////////////////////
void CBoard::TrouverCase(vector<Position> &PasChevalier , int i , int j)
{
   if( i-1 >= 0 && j-2 >=0)
   {
      if (!grilleVisitee_[i-1][j-2])
         PasChevalier.push_back(PoidsGrille_[i-1][j-2]);
   }

   if( i-2 >= 0 && j-1 >= 0)
   {
      if (!grilleVisitee_[i-2][j-1])
         PasChevalier.push_back(PoidsGrille_[i-2][j-1]);
   }

   if( i-2 >= 0 && j+1 < MAXCASES)
   {
      if (!grilleVisitee_[i-2][j+1])
         PasChevalier.push_back(PoidsGrille_[i-2][j+1]);
   }

   if( i-1 >= 0 && j+2 < MAXCASES)
   {
      if (!grilleVisitee_[i-1][j+2])
         PasChevalier.push_back(PoidsGrille_[i-1][j+2]);
   }

   if( i+1 < MAXCASES && j+2 < MAXCASES)
   {
      if (!grilleVisitee_[i+1][j+2])
         PasChevalier.push_back(PoidsGrille_[i+1][j+2]);
   }

   if( i+2 < MAXCASES && j+1 < MAXCASES)
   {
      if (!grilleVisitee_[i+2][j+1])
         PasChevalier.push_back(PoidsGrille_[i+2][j+1]);
   }

   if( i+2 < MAXCASES && j-1 >= 0)
   {
      if (!grilleVisitee_[i+2][j-1])
         PasChevalier.push_back(PoidsGrille_[i+2][j-1]);
   }

   if( i+1 < MAXCASES && j-2 >= 0)
   {
      if (!grilleVisitee_[i+1][j-2])
         PasChevalier.push_back(PoidsGrille_[i+1][j-2]);
   }
   sort(PasChevalier.begin(),PasChevalier.end());
}
/////////////////////////////////////////////////////////////
// T R O U V E R  P O I D S
/////////////////////////////////////////////////////////////
int CBoard::TrouverPoids(int i,int j)
{
   int CasesPossibles = 0;

   if( i-1 >= 0 && j-2 >=0)
      CasesPossibles++;

   if( i-2 >= 0 && j-1 >= 0)
      CasesPossibles++;

   if( i-2 >= 0 && j+1 < MAXCASES)
      CasesPossibles++;

   if( i-1 >= 0 && j+2 < MAXCASES)
      CasesPossibles++;

   if( i+1 < MAXCASES && j+2 < MAXCASES)
      CasesPossibles++;

   if( i+2 < MAXCASES && j+1 < MAXCASES)
      CasesPossibles++;

   if( i+2 < MAXCASES && j-1 >= 0)
      CasesPossibles++;

   if( i+1 < MAXCASES && j-2 >= 0)
      CasesPossibles++;

   return CasesPossibles;
}
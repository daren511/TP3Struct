// Board.cpp: implementation of the CBoard class.
//
//////////////////////////////////////////////////////////////////////
#include "Board.h"
#include "Poids.h"
#include "atltime.h"   // pour la m�thode Wait
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
   PoidsGrille_.SetNbLignes(MAXCASES);
   PoidsGrille_.SetNbColonnes(MAXCASES);

   for (int i=0; i<MAXCASES; i++)
      for (int j=0; j<MAXCASES; j++)
      {
         PoidsGrille_[i][j].SetX(i);
         PoidsGrille_[i][j].SetY(j); 
         int Poids = TrouverPoids(i,j);
         PoidsGrille_[i][j].SetPoids(Poids);
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
   if ( continuerRecherche_)
   {
      grilleVisitee_[i][j] = true;
      grilleTrajet_[i][j]  = noPasDuTrajet_;
      noPasDuTrajet_++;
      vector <CPoids> PasChevalier;
      TrouverCase(PasChevalier , i , j);
      for ( int a = 0 ; a < PasChevalier.size() && continuerRecherche_ ; a++)
      {
         if (faireTrace_ ) 
            AfficherTrajetTrace();

         if(ToutEstVisite())
         {
            grilleTrajet_[PasChevalier[a].GetX()][PasChevalier[a].GetY()]  = noPasDuTrajet_;
            continuerRecherche_ = false;
            system("cls");
            AfficherTrajet(++nbDeSolutions_); 
         }
         else
         {
            PlacerCavalier(PasChevalier[a].GetX() , PasChevalier[a].GetY());
         }
         if ( continuerRecherche_)
         {
            grilleTrajet_[PasChevalier[a].GetX()] [PasChevalier[a].GetY()]  = -1;
            grilleVisitee_[PasChevalier[a].GetX()] [PasChevalier[a].GetY()] = false;
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
   return (noPasDuTrajet_ >= ((MAXCASES * MAXCASES)- 1));
}

void CBoard::SetTrace(bool b)
{
   faireTrace_ = b;
}
void CBoard::TrouverCase(vector<CPoids> &PasChevalier , int i , int j)
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
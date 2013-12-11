//////////////////////////////////////////////////////////////////////
// P O I D S . C P P
// 12 Décembre 2012
// Francis Côté & Daren Ken St- Laurent
/////////////////////////////////////////////////////////////////////
#include "Poids.h"
using namespace std;

//////////////////////////////////////
// C O N S T R U C T I O N 
//////////////////////////////////////
CPoids::CPoids()
{
   X_ = 0;
   Y_ = 0;
   Poids_ = 0;
}

/////////////////////////////////////
// S E T T E R  &  G E T T E R
/////////////////////////////////////
void CPoids::SetX(int x)
{
   X_ = x;
}
void CPoids::SetY(int y)
{
   Y_ = y;
}
void CPoids::SetPoids(int Poids)
{
   Poids_ = Poids;
}
int CPoids::GetX() const 
{
   return X_;
}
int CPoids::GetY() const 
{
   return Y_;
}

CPoids::operator int()
{
   return Poids_;
}
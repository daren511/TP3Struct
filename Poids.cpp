#include "Poids.h"
using namespace std;

CPoids::CPoids()
{
   X_ = 0;
   Y_ = 0;
   Poids_ = 0;
}
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
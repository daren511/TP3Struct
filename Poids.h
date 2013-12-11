//////////////////////////////////////////////////////////////////////
// P O I D S . H
// 12 Décembre 2012
// Francis Côté & Daren Ken St- Laurent
//
// La classe Poids est utilisé comme outil pour chercher la meilleure
// case possible pour le prochain déplacement
//////////////////////////////////////////////////////////////////////

#pragma once

class CPoids
{
public:
	CPoids();
	void SetX(int x);
	void SetY(int y);
	void SetPoids(int poids);
	int GetX() const;
	int GetY() const;
	operator int();


private:
	int X_;
	int Y_;
	int Poids_;
};
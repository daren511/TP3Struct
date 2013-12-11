//////////////////////////////////////////////////////////////////////
// P O I D S . H
// 12 D�cembre 2012
// Francis C�t� & Daren Ken St- Laurent
//
// La classe Poids est utilis� comme outil pour chercher la meilleure
// case possible pour le prochain d�placement
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
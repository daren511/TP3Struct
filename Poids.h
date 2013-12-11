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
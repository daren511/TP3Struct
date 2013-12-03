// Board.h: interface for the CBoard class.
//
//////////////////////////////////////////////////////////////////////
#pragma once
#include "Matrice.h"
#include <iostream>
using namespace std;

class CBoard
{
public:
	//--- Constructeur et destructeur
	CBoard(ostream &, bool veutTrace);
	virtual ~CBoard();

	//--- Méthode de lancement de la recherche de solution
	void PlacerCavalier(unsigned int i, unsigned int j);

	//--- Autre méthode publique
	void SetTrace(bool);

private:
	static const int MAXCASES;  // Nombre de cases de l'échiquier
	ostream & out_;
	bool continuerRecherche_;
	bool faireTrace_;
	int  noPasDuTrajet_;
	int  nbDeSolutions_;
	int  ligneDepart_;
	int  colonneDepart_;
	CMatrice<bool> grilleVisitee_;  
	CMatrice<int>  grilleTrajet_; 

private:
	//--- Méthode lancée par le PlacerCavalier public
	void PlacerCavalier(int i, int j);

	//--- Autres méthodes utiles
	void AfficherNoSolution(int);
	void AfficherTrajet(int noSolution);
	void AfficherTrajetTrace();
	bool ToutEstVisite();
	void Wait(int nbSec);
};

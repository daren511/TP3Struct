// Board.h: interface for the CBoard class.
//
//////////////////////////////////////////////////////////////////////
#pragma once
#include "Matrice.h"
#include "Poids.h"
#include <iostream>
using namespace std;

class CBoard
{
public:
	//--- Constructeur et destructeur
	CBoard(ostream &, bool veutTrace);
	virtual ~CBoard();

	//--- M�thode de lancement de la recherche de solution
	void PlacerCavalier(unsigned int i, unsigned int j);

	//--- Autre m�thode publique
	void SetTrace(bool);

private:
	static const int MAXCASES;  // Nombre de cases de l'�chiquier
	ostream & out_;
	bool continuerRecherche_;
	bool faireTrace_;
	int  noPasDuTrajet_;
	int  nbDeSolutions_;
	int  ligneDepart_;
	int  colonneDepart_;
	CMatrice<bool> grilleVisitee_;  
	CMatrice<int>  grilleTrajet_; 
   CMatrice<CPoids> PoidsGrille_;

private:
	//--- M�thode lanc�e par le PlacerCavalier public
	void PlacerCavalier(int i, int j);
	void TrouverCase(vector<CPoids> &ListeDeplacement , int i , int j);
	int TrouverPoids(int i,int j);

	//--- Autres m�thodes utiles
	void AfficherNoSolution(int);
	void AfficherTrajet(int noSolution);
	void AfficherTrajetTrace();
	bool ToutEstVisite();
	void Wait(int nbSec);
};

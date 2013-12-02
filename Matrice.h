#pragma once
#include <vector>
#include <exception>
using namespace std;

template <class Objet>
class CMatrice
{
  public:
    //--- Constructeurs
	CMatrice( ) { }
    CMatrice( int iNbLignes, int iNbColonnes ) : m_Vecteur( iNbLignes )
    {
        for( int i = 0; i < iNbLignes; i++ )
            m_Vecteur[ i ].resize( iNbColonnes );
    }
	CMatrice( const CMatrice & oDroite ) : m_Vecteur( oDroite.m_Vecteur ) { }

	//--- Accesseurs et Mutateurs
    int GetNbLignes( ) const
      { return static_cast<int>(m_Vecteur.size( )); }
    int GetNbColonnes( ) const
      { return GetNbLignes( ) > 0 ? static_cast<int>(m_Vecteur[ 0 ].size( )) : 0; }

    void SetNbLignes( int iNbLignes )
	  { m_Vecteur.resize(iNbLignes); }
	void SetNbColonnes ( int iNbColonnes )
	  {  for( int i = 0; i < static_cast<int>(m_Vecteur.size()); i++ )
            m_Vecteur[ i ].resize( iNbColonnes );
	  }

    //--- Surcharge de l'opérateur [ ] 
	//    pour lecture et écriture dans la matrice 
	const vector<Objet> & operator[]( int iLigne ) const
      { return m_Vecteur[ iLigne ]; }
	vector<Objet> & operator[]( int iLigne )
      { return m_Vecteur[ iLigne ]; }

    private:
       vector< vector<Objet> > m_Vecteur;
};

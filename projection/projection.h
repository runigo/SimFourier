/*
Copyright mars 2025, Stephan Runigo
runigo@free.fr
SimFourier 1.3 Transformation de Fourier
(d'après SiCP 2.5 simulateur de chaîne de pendules, février 2021)
Ce logiciel est un programme informatique servant à donner une représentation
graphique de la transformation de Fourier à 1 dimension et de la simulation
d'équations de propagation.
Ce logiciel est régi par la licence CeCILL soumise au droit français et
respectant les principes de diffusion des logiciels libres. Vous pouvez
utiliser, modifier et/ou redistribuer ce programme sous les conditions
de la licence CeCILL telle que diffusée par le CEA, le CNRS et l'INRIA
sur le site "http://www.cecill.info".
En contrepartie de l'accessibilité au code source et des droits de copie,
de modification et de redistribution accordés par cette licence, il n'est
offert aux utilisateurs qu'une garantie limitée. Pour les mêmes raisons,
seule une responsabilité restreinte pèse sur l'auteur du programme, le
titulaire des droits patrimoniaux et les concédants successifs.
A cet égard l'attention de l'utilisateur est attirée sur les risques
associés au chargement, à l'utilisation, à la modification et/ou au
développement et à la reproduction du logiciel par l'utilisateur étant
donné sa spécificité de logiciel libre, qui peut le rendre complexe à
manipuler et qui le réserve donc à des développeurs et des professionnels
avertis possédant des connaissances informatiques approfondies. Les
utilisateurs sont donc invités à charger et tester l'adéquation du
logiciel à leurs besoins dans des conditions permettant d'assurer la
sécurité de leurs systèmes et ou de leurs données et, plus généralement,
à l'utiliser et l'exploiter dans les mêmes conditions de sécurité.
Le fait que vous puissiez accéder à cet en-tête signifie que vous avez
pris connaissance de la licence CeCILL, et que vous en avez accepté les
termes.
*/

#ifndef _PROJECTION_
#define _PROJECTION_

#include "../projection/parametrSystem.h"		//	Projection du système vers le graphisme.
#include "../projection/parametrGraph.h"		//	Projection des graphes 3D sur les graphes 2D.
#include "../projection/parametrInitial.h"	//	Projection de initiale sur commande.

				//		Projections entre le modèle et l'interface

typedef struct ProjectionT projectionT;
	struct ProjectionT
	{
		parametrSystemT parametrSystem;	//	Projection des paramètres système et des observables sur le graphisme

		parametrGraphT parametrGraph;	//	Projection des courbes 3D sur les courbes 2D

		parametrInitialT parametrInitial;	//	Projection des paramètres initiale sur le graphisme

		grapheT fonction;	//	Graphe de la fonction

		grapheT fourier;	//	Graphe de la TF

		commandesT commandes;	//	Graphe des commandes

		int fenetreX;	// hauteur de la fenêtre
		int fenetreY;	// largeur de la fenêtre
	};

	//-----------------    INITIALISATION      -----------------------//
int projectionInitialise(projectionT * projection, int nombre);

	//-----------------    PROJECTION      -----------------------//
int projectionModele(projectionT * projection, modeleT * modele, int mode);
//int projectionObservablesCapteurs(observablesT * observables, projectionT * projection, capteursT * capteurs);
//int projectionSystemeCommandes(systemeT * systeme, projectionT * projection);
//int projectionControleurCommandes(projectionT * projection, commandesT * commandes, int duree, int mode);

	//-----------------    CHANGE      -----------------------//
int projectionChangeParametre(projectionT * projection, int fonction, int parametre, int variation, int pourMille);
int projectionChangeFenetre(projectionT * projection, int x, int y);

	//-----------------    AFFICHAGE      -----------------------//
void projectionAffiche(projectionT * projection);

#endif

/*
Copyright mars 2025, Stephan Runigo
runigo@free.fr
SimFourier 1.2.2 Transformation de Fourier
(SiCP 2.5 simulateur de chaîne de pendules fevrier 2021)
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

#ifndef _GRAPHES_
#define _GRAPHES_

#include "pointDeVue.h"

typedef struct GrapheT grapheT;
	struct GrapheT
		{
		int nombre;

			// Grandeurs 3D
		vecteurT point[NOMBRE_MAX]; // Fonction ou TF
		vecteurT axe[NOMBRE_MAX]; // Fonction ou TF
		vecteurT support[SUPPORT];	// Support fixe


			// Grandeurs 2D
		int xp[NOMBRE_MAX];		// Absisse 2D du point
		int yp[NOMBRE_MAX];		// Ordonnée 2D du point
		int xa[NOMBRE_MAX];		// Absisse 2D de l'axe
		int ya[NOMBRE_MAX];		// Ordonnée 2D de l'axe

		int supporX[7];		// Absisse 2D des axes
		int supporY[7];		// Ordonnée 2D des axes

			// Position de l'observateur
		pointDeVueT pointDeVue;

		int modeSupport;	// Change la représentation graphique du support

		int dessous;	// Vue de dessous
		int arriere;	// Vue de derrière
		int gauche;		// Vue de gauche

		int echelle;	// Echelle du graphe
		//int longueur;	// Longueur Ox
		//int rayon;	// Longueurs Oy et Oz
		
		float ratiox;	// rapport décalage X / fenetre X
		float ratioy;	// rapport décalage Y / fenetre Y
		};


typedef struct GraphesT graphesT;
	struct GraphesT
		{
		grapheT fonction;
		grapheT fourier;
		};

int graphesInitialisation(graphesT * graphes, int nombre);
//void grapheChangeSupport(grapheT * graphe);
int grapheAffiche(grapheT * graphe);
#endif

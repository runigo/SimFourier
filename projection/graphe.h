/*
Copyright avril 2025, Stephan Runigo
runigo@free.fr
SimFourier 1.3 Transformation de Fourier
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

#ifndef _GRAPHE_
#define _GRAPHE_

#include "pointDeVue.h"

/*************************************************************

	Contient les points des fonctions en 3D et en 2D,
	la projection en perspective,
	le point de vue, ses paramètres et les paramètres du graphe.

*/////////////////////////////////////////////////////////////

typedef struct GrapheT grapheT;
	struct GrapheT
		{
		int nombre;

			// Grandeurs 3D
		vecteurT point[NOMBRE_MAX]; // Fonction ou TF
		vecteurT axe[NOMBRE_MAX]; // Axe x
		vecteurT support[SUPPORT];	// Axes xyz


			// Grandeurs 2D
		int xp[NOMBRE_MAX];		// Absisse 2D du point
		int yp[NOMBRE_MAX];		// Ordonnée 2D du point
		int xa[NOMBRE_MAX];		// Absisse 2D de l'axe
		int ya[NOMBRE_MAX];		// Ordonnée 2D de l'axe

		int axeX[SUPPORT];		// Absisse 2D des axes
		int axeY[SUPPORT];		// Ordonnée 2D des axes

			// Position de l'observateur
		pointDeVueT pointDeVue;

		int axes;	// Change la représentation graphique des axes (avec ou sans)
		int trait;		// Change la représentation graphique de la fonction (points reliés ou non)
		int coord;		// Change la représentation graphique des coordonnées (vecteur ou cartésien)

		int dessous;	// Vue de dessous
		int arriere;	// Vue de derrière
		int gauche;		// Vue de gauche

		int echelle;	// Echelle du graphe
		//int longueur;	// Longueur Ox
		//int rayon;	// Longueurs Oy et Oz
		
		float ratiox;	// rapport décalage X / fenetre X
		float ratioy;	// rapport décalage Y / fenetre Y
		};

int graphe3D2D(grapheT * graphe, int fenetreX, int fenetreY);
int grapheInitialisation(grapheT * graphe, int nombre);
int grapheInitialiseSupport(grapheT * graphe);
int grapheInitialisePointDeVue(grapheT * graphe, float r, float psi, float phi);

int grapheChangeParametre(grapheT * graphe, int parametre, int variation, int pourMille);

int grapheReglageAxes(grapheT * graphe, int axes);
int grapheReglageTrait(grapheT * graphe, int trait);
int grapheReglageCoord(grapheT * graphe, int coord);
int grapheChangeCoord(grapheT * graphe, int coord);
int grapheAffiche(grapheT * graphe);
#endif

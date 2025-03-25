/*
Copyright mars 2025, Stephan Runigo
runigo@free.fr
SimFourier 1.2.3 Transformation de Fourier
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

#include "parametrGraph.h"

				//		Projections des caractéristiques de la fonction initiale
				//		  sur les commandes


	//-----------------    INITIALISATION      -----------------------//
int parametrGraphInitialise(parametrGraphT * parametrGraph, int nombre)
	{
	(void)nombre;
		//	facteur de proportionalité entre les grandeurs et la position des rotatifs
	(*parametrGraph).radianR = PIS2 / (DISTANCE_MAX - DISTANCE_MIN);

	return 0;
	}

	//-----------------    PROJECTION      -----------------------//

int parametrGraphCommandes(initialeT * initiale, parametrGraphT * parametrGraph, commandesT * commandes) {

	// Projette les caractéristiques de la fonction initiale sur les commandes dans le mode initiale

	float theta;
	int longueur = (*commandes).rotatifsDroite - (*commandes).rotatifsGauche;


			//	Projection sur les boutons rotatifs de la partie enveloppe
		//	Distance point de vue, r
	theta = (*parametrGraph).radianR;// * ((*initiale).enveloppe.rho);
	(*commandes).rotatifGraphe[0].positionX = (int)(-longueur*cos(theta));
	(*commandes).rotatifGraphe[0].positionY = (int)(-longueur*sin(theta));

				//	Projection sur les petits boutons
	int i;

	for(i=0;i<SELECTIF_INITIAL;i++) (*commandes).selectifGraphe[i].etat = 0;

			//	Tracé des axes, position du point de vue
	switch((*initiale).enveloppe.periodique) {
		case 2:
			(*commandes).selectifGraphe[0].etat = 1; break;	//	Implicite
		case 3:
			(*commandes).selectifGraphe[1].etat = 1; break;	//	Imaginaire
		case 4:
			(*commandes).selectifGraphe[2].etat = 1; break;	//	Réel
		case 5:
			(*commandes).selectifGraphe[3].etat = 1; break;	//	Sans axe
		default:
			;
		}

			//	Tracé de la courbe
	switch((*initiale).enveloppe.periodique) {
		case 0:
			(*commandes).selectifGraphe[4].etat = 1; break;	//	Point
		case 1:
			(*commandes).selectifGraphe[5].etat = 1; break;	//	Relié
		default:
			;
		}

			//	Tracé des coordonnées
	switch((*initiale).motif.forme) {
		case 0:
			(*commandes).selectifGraphe[6].etat = 1; break;	//	vecteur
		case 1:
			(*commandes).selectifGraphe[7].etat = 1; break;	//	cartésien
		case 2:
			(*commandes).selectifGraphe[8].etat = 1; break;	//	vide
		default:
			;
		}
	return 0;
	}

	//-----------------    CHANGE LA PROJECTION     -----------------------//

int parametrGraphChangeFenetre(parametrGraphT * parametrGraph, int x, int y) {

		//	Enregistre le changement de la taille de la fenêtre
	(void)parametrGraph;
	(void)x;
	(void)y;
	//(*parametrGraph).fenetreX=x;
	//(*parametrGraph).fenetreY=y;

	return 0;
	}

	//-----------------    AFFICHAGE      -----------------------//

void parametrGraphAffiche(parametrGraphT * parametrGraph) {

		//	Affiche les paramètres de la parametrGraph

	printf("(*parametrGraph).radianR = %f\n", (*parametrGraph).radianR);
	return ;
	}

//////////////////////////////////////////////////////////////////////////////////////

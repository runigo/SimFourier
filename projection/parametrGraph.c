/*
Copyright mai 2025, Stephan Runigo
runigo@free.fr
SimFourier 1.4 Transformation de Fourier
Ce logiciel est un programme informatique permettant de donner une représentation
graphique de la transformation de Fourier à 1 dimension et d'observer l'effet
d'un filtrage.
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

				//		Projections des caractéristiques des graphes
				//		  sur les commandes

int parametrGraphRotatifs(grapheT * graphe, parametrGraphT * parametrGraph, commandesT * commandes);
int parametrGraphSelectifs(grapheT * graphe, commandesT * commandes);

	//-----------------    INITIALISATION      -----------------------//
int parametrGraphInitialise(parametrGraphT * parametrGraph, int nombre)
	{
	(void)nombre;

		//	facteur de proportionalité entre les grandeurs et la position des rotatifs
	(*parametrGraph).radianR = PIS2 / (DISTANCE_MAX - DISTANCE_MIN);

	return 0;
	}

	//-----------------    PROJECTION      -----------------------//

int parametrGraphCommandes(grapheT * graphe, parametrGraphT * parametrGraph, commandesT * commandes)
	{
			//	Projette les caractéristiques des graphes sur les commandes

	parametrGraphRotatifs(graphe, parametrGraph, commandes);
	parametrGraphSelectifs(graphe, commandes);

	return 0;
	}

int parametrGraphRotatifs(grapheT * graphe, parametrGraphT * parametrGraph, commandesT * commandes)
	{
			// Projection sur les boutons linéaire des menus graphes
	int j;
	float theta;
	int longueur = (*commandes).rotatifsDroite - (*commandes).rotatifsGauche;

	for(j=0;j<2;j++)
		{
				//	Projection sur les boutons rotatifs de la partie enveloppe
			//	Distance point de vue, r
		theta = (*parametrGraph).radianR * ((*graphe).pointDeVue.position.r);
		(*commandes).rotatifGraph[j][0].positionX = (int)(-longueur*cos(theta));
		(*commandes).rotatifGraph[j][0].positionY = (int)(-longueur*sin(theta));
		}

	return 0;
	}

int parametrGraphSelectifs(grapheT * graphe, commandesT * commandes)
	{
			//	Projection sur les boutons selectifs

	int i, j;

	for(j=0;j<2;j++)
		{
		for(i=0;i<SELECTIF_INITIAL;i++)
			{
			(*commandes).selectifGraph[j][i].etat = 0;
			}

		switch((*graphe).axes) {	//	Tracé des axes, position du point de vue
			case 0:
				(*commandes).selectifGraph[j][0].etat = 1; break;	//	Implicite
			case 1:
				(*commandes).selectifGraph[j][1].etat = 1; break;	//	Imaginaire
			case 2:
				(*commandes).selectifGraph[j][2].etat = 1; break;	//	Réel
			default:
				; }

		switch((*graphe).trait) {	//	Tracé de la courbe
			case 0:
				(*commandes).selectifGraph[j][3].etat = 1; break;	//	Point
			case 1:
				(*commandes).selectifGraph[j][4].etat = 1; break;	//	Relié
			default:
				; }

		switch((*graphe).coord) {	//	Tracé des coordonnées
			case 0:
				(*commandes).selectifGraph[j][6].etat = 1; break;	//	vide
			case 1:
				(*commandes).selectifGraph[j][5].etat = 1; break;	//	vecteur
			default:
				; }
		}
	return 0;
	}

	//-----------------    AFFICHAGE      -----------------------//

void parametrGraphAffiche(parametrGraphT * parametrGraph) {

		//	Affiche les paramètres de parametrGraph

	printf("(*parametrGraph).radianR = %f\n", (*parametrGraph).radianR);
	return ;
	}

//////////////////////////////////////////////////////////////////////////////////////

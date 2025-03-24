/*
Copyright mars 2025, Stephan Runigo
runigo@free.fr
SimFourier 1.2.3 Transformation de Fourier
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

#include "projection.h"

				//		Projections entre le modèle et l'interface

	//	INITIALISATION
//int projectionInitialisePointDeVue(projectionSystemT * projection,  float r,float psi, float phi);
//int projectionReinitialiseBase(projectionSystemT * projection);

	//	PROJECTION
//int projectionPerspectiveChaine(projectionSystemT * projection, grapheT * graphe);
//int projectionSystemeGraphes3D(modeleT * modele, graphesT * graphes);

//int projectionInitialiseSupport(projectionSystemT * projection, int nombre);
//int projectionPerspectiveSupport(projectionSystemT * projection, grapheT * graphe);

	//	CHANGE

	//	AFFICHAGE


	//-----------------    INITIALISATION      -----------------------//
int projectionInitialise(projectionT * projection, int nombre)
	{
		//fprintf(stderr, " Initialisation des projections\n");
	projectionGraphInitialise(&(*projection).projectionGraph);
	projectionSystemInitialise(&(*projection).projectionSystem);
	projectionInitialInitialise(&(*projection).projectionInitial, nombre);

	return 0;
	}

	//-----------------    PROJECTION      -----------------------//

int projectionModeleGraphes(modeleT * modele, graphesT * graphes) {

		// Projection du Modele sur les graphes en perspective

		//		Projection du système sur les graphes 3D
	projectionSystemeGraphes3D(modele, graphes);

	return 0;
	}


int projectionModele(projectionT * projection, modeleT * modele, int mode)
	{

        //  modele -> 3D
	projectionSystemeGraphes(&(*controleur).modele, &(*controleur).graphes);
        //  3D -> 2D
	projectionGraphGraphes(&(*controleur).projection.projectionGraph, &(*controleur).graphes);

	//projectionObservablesCapteurs(&(*controleur).observables, &(*controleur).projectionSystem, &(*controleur).capteurs);

	//projectionInitialeCommandes(&(*controleur).projectionSystem, &(*controleur).commandes, (*controleur).options.duree, (*controleur).options.modePause);

	if(mode == 0)	//	Mode initiale
		{
	projectionInitialCommandes(&(*controleur).modele.initiale, &(*controleur).projection.projectionInitial, &(*controleur).commandes);
		}
	else
		{
	//projectionSystemeCommandes(&(*controleur).modele.systeme, &(*controleur).projectionSystem, &(*controleur).commandes);
		}


	return 0;
	}

int projectionCommandes(systemeT * systeme, projectionSystemT * projection, commandesT * commandes) {

		// Projette le système sur les commandes dans le mode simulation

(void)systeme;
(void)projection;
(void)commandes;
	return 0;
	}

int projectionControleurCommandes(projectionSystemT * projection, commandesT * commandes, int duree, int mode) {

		// Projette le controleur sur les commandes

(void)projection;
(void)commandes;
(void)duree;
(void)mode;
	return 0;
	}

	//-----------------    CHANGE LA PROJECTION     -----------------------//

int projectionSystemChangeFenetre(projectionSystemT * projection, int x, int y) {

		//	Enregistre le changement de la taille de la fenêtre

	(*projection).fenetreX=x;
	(*projection).fenetreY=y;

	return 0;
	}


	//-----------------    AFFICHAGE      -----------------------//

void projectionSystemAffiche(projectionSystemT * projection) {

	//	Affiche les paramètres de la projection
	(void)projection;

	//printf("(*projection).ratioXY = %f\n", (*projection).ratioXY);
	//printf("(*projection).hauteur = %d\n", (*projection).hauteur);
	//printf("(*projection).largeur = %d\n", (*projection).largeur);
	//printf("(*projection).fenetreX = %d\n", (*projection).fenetreX);
	//printf("(*projection).fenetreY = %d\n", (*projection).fenetreY);
	return ;
	}

//////////////////////////////////////////////////////////////////////////////////////

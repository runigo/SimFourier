/*
Copyright avril 2025, Stephan Runigo
runigo@free.fr
SimFourier 1.4 Transformation de Fourier
Ce logiciel est un programme informatique servant à donner une représentation
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

#include "projection.h"

				//		Projections entre le modèle et l'interface

	//	INITIALISATION

	//	PROJECTION
int projectionModeleGraphes(projectionT * projection, modeleT * modele, int mode);
int projectionModeleGraphes3D(modeleT * modele, projectionT * projection);
int projectionTronqueGraphes(projectionT * projection);

	//	CHANGE

	//	AFFICHAGE


	//-----------------    INITIALISATION      -----------------------//
int projectionInitialise(projectionT * projection, int nombre)
	{
		//fprintf(stderr, " Initialisation des projections\n");
	parametrGraphInitialise(&(*projection).parametrGraph, nombre);
	parametrSystemInitialise(&(*projection).parametrSystem);
	parametrInitialInitialise(&(*projection).parametrInitial, nombre);
	parametrFiltragInitialise(&(*projection).parametrFiltrag, nombre);

		//	Initialisation des graphes
	grapheInitialisation(&(*projection).fonction, nombre);
	(*projection).fonction.espace = 0;
	grapheInitialisation(&(*projection).fourier, nombre);
	(*projection).fourier.espace = 1;
	grapheInitialisation(&(*projection).fct, nombre);
	(*projection).fct.espace = 0;
	grapheInitialisation(&(*projection).fou, nombre);
	(*projection).fou.espace = 1;

		//	Position des graphes dans la fenêtre
	(*projection).fonction.positionX = 0.30;
	(*projection).fonction.positionY = 0.25;
	(*projection).fourier.positionX = 0.30;
	(*projection).fourier.positionY = 0.75;
	(*projection).fct.positionX = 0.75;
	(*projection).fct.positionY = 0.25;
	(*projection).fou.positionX = 0.75;
	(*projection).fou.positionY = 0.75;

		//	Style des courbes
	(*projection).fonction.trait = 1;
	(*projection).fourier.trait = 0;
	(*projection).fct.trait = 1;
	(*projection).fou.trait = 0;

	return 0;
	}


	//-----------------    PROJECTION      -----------------------//

int projectionModele(projectionT * projection, modeleT * modele, int mode)
	{
			//	Projette le modèle sur les graphes et les commandes

        //  Fonction -> graphe 3D -> graphe 2D
	projectionModeleGraphes(projection, modele, mode);

	//projectionObservablesCapteurs(&(*controleur).observables, &(*controleur).projection.parametrSystem, &(*controleur).capteurs);

		//	Paramètre -> commandes
	if(mode == 0)	//	Mode initiale
		{
	parametrInitialCommandes(&(*modele).initiale, &(*projection).parametrInitial, &(*projection).commandes);
	parametrGraphCommandes(&(*projection).fonction, &(*projection).parametrGraph, &(*projection).commandes);
	parametrGraphCommandes(&(*projection).fourier, &(*projection).parametrGraph, &(*projection).commandes);
	parametrFiltragCommandes(&(*modele).filtrage, &(*projection).parametrFiltrag, &(*projection).commandes);
		}
	else		//	Mode simulation
		{
	parametrSystemCommandes(&(*modele).systeme, &(*projection).parametrSystem, &(*projection).commandes);
		}

	return 0;
	}

int projectionModeleGraphes(projectionT * projection, modeleT * modele, int mode)
	{
		// Projection des fonctions du modèle sur les graphes en perspective
	(void) mode;
		//		Projection des fonctions sur les graphes 3D
	projectionModeleGraphes3D(modele, projection);

		//		Projection des graphes 3D sur les graphes 2D
	graphe3D2D(&(*projection).fonction, (*projection).fenetreX, (*projection).fenetreY);
	graphe3D2D(&(*projection).fourier, (*projection).fenetreX, (*projection).fenetreY);
	graphe3D2D(&(*projection).fct, (*projection).fenetreX, (*projection).fenetreY);
	graphe3D2D(&(*projection).fou, (*projection).fenetreX, (*projection).fenetreY);

		//	Tronque les graphes
	projectionTronqueGraphes(projection);

	return 0;
	}

int projectionModeleGraphes3D(modeleT * modele, projectionT * projection)
	{
			//	Projette les fonctions du modèle sur les graphes 3D

	int i;
	int nombre = (*modele).systeme.nombre;

	for(i=0;i<nombre;i++)	//	Projection de la fonction initiale et de fct
		{
		(*projection).fonction.point[i].y = (*modele).systeme.actuel.reel[i];//(*projection).fonction.hauteur * 
		(*projection).fonction.point[i].z = (*modele).systeme.actuel.imag[i];//(*projection).fonction.hauteur * 
		//(*projection).fourier.point[i].y = (*modele).fourier.spectre.reel[i];//(*projection).fourier.hauteur * 
		//(*projection).fourier.point[i].z = (*modele).fourier.spectre.imag[i];//(*projection).fourier.hauteur * 
		(*projection).fct.point[i].y = (*modele).filtrage.fct.spectre.reel[nombre - 1 - i];
		(*projection).fct.point[i].z = (*modele).filtrage.fct.spectre.imag[nombre - 1 - i];
		}

	int j=nombre/2;

	for(i=0;i<j;i++)	//	Projection et retournement des transformées de fourier
		{
		(*projection).fourier.point[i].y = (*modele).fourier.spectre.reel[j-i];		//[2*i]
		(*projection).fourier.point[i].z = (*modele).fourier.spectre.imag[j-i];		//[2*i]
		(*projection).fourier.point[nombre-i].y = (*modele).fourier.spectre.reel[j+i]; //[2*i+1]
		(*projection).fourier.point[nombre-i].z = (*modele).fourier.spectre.imag[j+i]; //[2*i+1]
		(*projection).fou.point[i].y = (*modele).filtrage.fou.reel[j-i];
		(*projection).fou.point[i].z = (*modele).filtrage.fou.imag[j-i];
		(*projection).fou.point[nombre-i].y = (*modele).filtrage.fou.reel[j+i];
		(*projection).fou.point[nombre-i].z = (*modele).filtrage.fou.imag[j+i];
		}

	return 0;
	}

int projectionTronqueGraphes(projectionT * projection) {

		//	Tronque les graphes
		//	Calcul de l'indice à partir duquel le graphe est dans ses limites

	int i = 0;
	int nombre = (*projection).fonction.nombre;

	while( ( (*projection).fonction.xa[i] < (*projection).commandes.fonctionsGauche
	 || (*projection).fonction.xa[nombre-1-i] < (*projection).commandes.fonctionsGauche )
	 && (i < nombre/2) )
		{
		i++;
		}
	(*projection).fonction.tronque = i;
	(*projection).fct.tronque = i;

	i = 0;
	while( ( (*projection).fourier.xa[i] < (*projection).commandes.fonctionsGauche
	 || (*projection).fourier.xa[nombre-1-i] < (*projection).commandes.fonctionsGauche )
	 && (i < nombre/2) )
		{
		i++;
		}
	(*projection).fourier.tronque = i;
	(*projection).fou.tronque = i;

	return 0;
	}


	//-----------------    CHANGE LA PROJECTION     -----------------------//

int projectionChangeParametre(projectionT * projection, int menu, int parametre, int variation, int pourMille)
	{
				//	Change un paramètre de la projection

	switch(menu) {
		case 4:	//		Fonction et fct
			grapheChangeParametre(&(*projection).fonction, parametre, variation, pourMille);
			grapheChangeParametre(&(*projection).fct, parametre, variation, pourMille); break;
		case 6:	//		Fourier et fou
			grapheChangeParametre(&(*projection).fourier, parametre, variation, pourMille);
			grapheChangeParametre(&(*projection).fou, parametre, variation, pourMille); break;
		default:
			printf("ERREUR projectionChangeParametre\n");
		}
	return 0;
	}

int projectionChangeFenetre(projectionT * projection, int x, int y) {

		//	Enregistre le changement de la taille de la fenêtre

	(*projection).fenetreX=x;
	(*projection).fenetreY=y;

	grapheInitialiseSupport(&(*projection).fourier);

	return 0;
	}


	//-----------------    AFFICHAGE      -----------------------//

void projectionAffiche(projectionT * projection) {

	//	Affiche les paramètres de la projection
	(void)projection;

	//printf("(*projection).ratioXY = %f\n", (*projection).ratioXY);
	//printf("(*projection).hauteur = %d\n", (*projection).hauteur);
	//printf("(*projection).largeur = %d\n", (*projection).largeur);
	printf("(*projection).fenetreX = %d\n", (*projection).fenetreX);
	printf("(*projection).fenetreY = %d\n", (*projection).fenetreY);
	return ;
	}

//////////////////////////////////////////////////////////////////////////////////////

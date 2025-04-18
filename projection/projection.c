/*
Copyright avril 2025, Stephan Runigo
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

#include "projection.h"

				//		Projections entre le modèle et l'interface

	//	INITIALISATION
//int projectionInitialisePointDeVue(projectionSystemT * projection,  float r,float psi, float phi);
//int projectionReinitialiseBase(projectionSystemT * projection);

	//	PROJECTION
int projectionModeleGraphes(projectionT * projection, modeleT * modele);
int projectionModeleGraphes3D(modeleT * modele, projectionT * projection);
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
	parametrGraphInitialise(&(*projection).parametrGraph, nombre);
	parametrSystemInitialise(&(*projection).parametrSystem);
	parametrInitialInitialise(&(*projection).parametrInitial, nombre);

		//	Initialisation des graphes
	grapheInitialisation(&(*projection).fonction, nombre);
	grapheInitialisation(&(*projection).fourier, nombre);

		//	Position des graphes dans la fenêtre
	(*projection).fonction.positionX = 0.5;
	(*projection).fonction.positionY = 0.25;
	(*projection).fourier.positionX = 0.5;
	(*projection).fourier.positionY = 0.75;

		//	Style des courbes
	(*projection).fonction.trait = 1;
	(*projection).fourier.trait = 0;

	return 0;
	}


	//-----------------    PROJECTION      -----------------------//

int projectionModele(projectionT * projection, modeleT * modele, int mode)
	{
			//	Projette le modèle sur les graphes et les commandes

        //  Fonction -> graphe 3D -> graphe 2D
	projectionModeleGraphes(projection, modele);

	//projectionObservablesCapteurs(&(*controleur).observables, &(*controleur).projection.parametrSystem, &(*controleur).capteurs);

		//	Paramètre -> commandes
	if(mode == 0)	//	Mode initiale
		{
	parametrInitialCommandes(&(*modele).initiale, &(*projection).parametrInitial, &(*projection).commandes);
		}
	else		//	Mode simulation
		{
	parametrSystemCommandes(&(*modele).systeme, &(*projection).parametrSystem, &(*projection).commandes);
		}


	return 0;
	}

int projectionModeleGraphes(projectionT * projection, modeleT * modele)
	{
		// Projection des fonctions du modèle sur les graphes en perspective

		//		Projection des fonctions sur les graphes 3D
	projectionModeleGraphes3D(modele, projection);

		//		Projection des graphes 3D sur les graphes 2D
	graphe3D2D(&(*projection).fonction, (*projection).fenetreX, (*projection).fenetreY);
	graphe3D2D(&(*projection).fourier, (*projection).fenetreX, (*projection).fenetreY);

	return 0;
	}

int projectionModeleGraphes3D(modeleT * modele, projectionT * projection)
	{
			//	Projette les fonctions du modèle sur les graphes 3D

	int i;
	int nombre = (*modele).systeme.nombre;

	for(i=0;i<nombre;i++)	//	Projection de la fonction initiale
		{
		(*projection).fonction.point[i].y = (*modele).systeme.actuel.reel[i];//(*projection).fonction.hauteur * 
		(*projection).fonction.point[i].z = (*modele).systeme.actuel.imag[i];//(*projection).fonction.hauteur * 
		//(*projection).fourier.point[i].y = (*modele).fourier.spectre.reel[i];//(*projection).fourier.hauteur * 
		//(*projection).fourier.point[i].z = (*modele).fourier.spectre.imag[i];//(*projection).fourier.hauteur * 
		}

	int j=nombre/2;

	for(i=0;i<j;i++)	//	Projection et retournement de la transformée de fourier
		{
		(*projection).fourier.point[i].y = (*modele).fourier.spectre.reel[j-i];		//[2*i]
		(*projection).fourier.point[i].z = (*modele).fourier.spectre.imag[j-i];		//[2*i]
		(*projection).fourier.point[nombre-i].y = (*modele).fourier.spectre.reel[j+i]; //[2*i+1]
		(*projection).fourier.point[nombre-i].z = (*modele).fourier.spectre.imag[j+i]; //[2*i+1]
		}

	return 0;
	}


int projectionCommandes(systemeT * systeme, parametrSystemT * projection, commandesT * commandes) {

		// Projette le système sur les commandes dans le mode simulation

(void)systeme;
(void)projection;
(void)commandes;
	return 0;
	}

int projectionControleurCommandes(parametrSystemT * projection, commandesT * commandes, int duree, int mode) {

		// Projette le controleur sur les commandes

(void)projection;
(void)commandes;
(void)duree;
(void)mode;
	return 0;
	}


	//-----------------    CHANGE LA PROJECTION     -----------------------//

int projectionChangeParametre(projectionT * projection, int menu, int parametre, int variation, int pourMille)
	{
				//	Change un paramètre de la projection

	switch(menu) {
		case 4:	//		Fonction
			grapheChangeParametre(&(*projection).fonction, parametre, variation, pourMille); break;
		case 6:	//		Fourier
			grapheChangeParametre(&(*projection).fourier, parametre, variation, pourMille); break;
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

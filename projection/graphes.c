/*
Copyright mars 2025, Stephan Runigo
runigo@free.fr
SimFourier 1.2.2 Transformation de Fourier
(D'après SiCP 1.3.7  simulateur de chaîne de pendules, septembre 2017)
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

#include "graphes.h"

int grapheInitialiseSupport(grapheT * graphe);
int grapheInitialisePointDeVue(graphesT * graphes, float r, float psi, float phi);
//int graphesInitialisePointDeVue(graphesT * graphes, float r, float psi, float phi);

int grapheInitialisation(grapheT * graphe, int nombre);

int graphesInitialisation(graphesT * graphes, int nombre)
	{
			//	Initalisation des graphes

	grapheInitialisation(&(*graphes).fonction, nombre);
	grapheInitialisation(&(*graphes).fourier, nombre);
	(*graphes).fonction.ratiox = 0.5;
	(*graphes).fonction.ratioy = 0.25;
	(*graphes).fourier.ratiox = 0.5;
	(*graphes).fourier.ratioy = 0.75;
	(*graphes).fonction.trait = 1;
	(*graphes).fourier.trait = 0;
	return 0;
	}

int grapheInitialisation(grapheT * graphe, int nombre)
	{
			//	Initalisation d'un graphe

	int i;
	(*graphe).nombre=nombre;

	(*graphe).axes = 1;	//	Avec ou sans axes
	(*graphe).trait = 1;	//	Points reliés ou non

	(*graphe).dessous = 0;
	(*graphe).arriere = 0;
	(*graphe).gauche = 0;

	(*graphe).echelle = ECHELLE_IMP;
	//(*graphe).longueur = LONGUEUR_IMP;
	//(*graphe).rayon = RAYON_IMP;

	(*graphe).ratiox = 0.0;
	(*graphe).ratioy = 0.0;

	for(i=0;i<NOMBRE_MAX;i++){
		vecteurInitialisePolaire(&(*graphe).point[i], 0.0, 0.0, 0.0);
		vecteurInitialisePolaire(&(*graphe).axe[i], 0.0, 0.0, 0.0);
		(*graphe).xp[i] = 0;
		(*graphe).yp[i] = 0;
		(*graphe).xa[i] = 0;
		(*graphe).ya[i] = 0;
		}

	for(i=0;i<SUPPORT;i++){
		vecteurInitialisePolaire(&(*graphe).support[i],0.0,0.0,0.0);
		(*graphe).supporX[i] = 0;
		(*graphe).supporY[i] = 0;
		}

	pointDeVueInitialise(&(*graphe).pointDeVue);
	grapheInitialiseSupport(graphe);

	return 0;
	}
/*
int graphesInitialisePointDeVue(graphesT * graphes, float r, float psi, float phi)
	{
		// Initialise la position de l'observateur et calcul les vecteurs perpendiculaires

	grapheInitialisePointDeVue(&(*graphes).fonction.pointDeVue, r, psi, phi);
	grapheInitialisePointDeVue(&(*graphes).fourier.pointDeVue, r, psi, phi);

	return 0;
	}

int grapheInitialisePointDeVue(grapheT * graphe, float r, float psi, float phi)
	{
		// Initialise la position de l'observateur et calcul les vecteurs perpendiculaires

	vecteurInitialisePolaire(&(*graphe).pointDeVue, r, psi, phi);
	
	GrapheReinitialiseBase(graphe);

	return 0;
	}

int grapheReinitialiseBase(grapheT * graphe)
	{
		// Réinitialise les vecteurs perpendiculaires

	vecteurInitialiseVecteurPhi(&(*graphe).pointDeVue.position, &(*graphe).pointDeVue.vecteurPhi, (*graphe).longueur);
	vecteurInitialiseVecteurPsi(&(*graphe).pointDeVue.position, &(*graphe).pointDeVue.vecteurPsi, (*graphe).rayon);

	return 0;
	}
*/
int grapheInitialiseSupport(grapheT * graphe){
//
//                                                Z
//                                          Y              X'
//                                                O
//                                                      Y'
//                                                Z'
//             X

	int i;
	for(i=0;i<SUPPORT;i++)
		{
		(*graphe).support[i].x = 0;
		(*graphe).support[i].y = 0;
		(*graphe).support[i].z = 0;
		}

					// AXE X'X
	(*graphe).support[0].x = -5.2 * (*graphe).echelle;
	(*graphe).support[1].x = 3.2 * (*graphe).echelle;

					// AXE Y'Y
	(*graphe).support[2].y = -1.2 * (*graphe).echelle;
	(*graphe).support[3].y = 1.2 * (*graphe).echelle;
	(*graphe).support[2].x = -4.2 * (*graphe).echelle;
	(*graphe).support[3].x = -4.2 * (*graphe).echelle;

					// AXE Z'Z
	(*graphe).support[4].z = -1.2 * (*graphe).echelle;
	(*graphe).support[5].z = 1.2 * (*graphe).echelle;
	(*graphe).support[4].x = -4.2 * (*graphe).echelle;
	(*graphe).support[5].x = -4.2 * (*graphe).echelle;

		//	Initialisation des abscisses du graphe
	int nombre=(*graphe).nombre;
	if(nombre==0)
		{
		printf("ERREUR, grapheInitialiseSupport, nombre == 0\n");
		exit(0);
		}
	else
		{
		for(i=0;i<nombre;i++)
			{
			(*graphe).axe[i].x = (7.9 * (float)i/nombre - 4.2) * (*graphe).echelle ;
			(*graphe).point[i].x = (*graphe).axe[i].x ;
			}
		}
	return 0;
	}

void grapheChangeSupport(grapheT * graphe){

	// Change la représentation graphique du support

	if((*graphe).axes==1)
		{(*graphe).axes=0;
		printf("Support invisible\n");}
	else
		{
		if((*graphe).axes==0)
			{
			(*graphe).axes=-1;
			printf("Support transparent\n");
			}
		else
			{
			(*graphe).axes=1;
			printf("Support plein\n");
			}
		}
	}

	//-----------------    AFFICHAGE      -----------------------//

int grapheAffiche(grapheT * graphe) {

		// Affiche les valeurs de psi et phi

	printf("(*graphe).pointDeVue.position :\n");
	vecteurAffiche(&(*graphe).pointDeVue.position);

	int i;
	for(i=0;i<3;i++){
		printf("\n(*graphe).support[%i] :\n", i);
		vecteurAffiche(&(*graphe).support[i]);}
	for(i=0;i<3;i++){
		printf("\n(*graphe).point[%i] :\n", i);
		vecteurAffiche(&(*graphe).point[i]);}
	for(i=0;i<3;i++){
		printf("\n(*graphe).axe[%i] :\n", i);
		vecteurAffiche(&(*graphe).axe[i]);}

//	printf("\n(*graphe).xa[0], ya[0] : %i, %i\n",(*graphe).xa[0],(*graphe).ya[0]);
//	printf("\n(*graphe).xp[0], yp[0] : %i, %i\n\n",(*graphe).xp[0],(*graphe).yp[0]);

	return 0;
	}

//////////////////////////////////////////////////////////////////

/*
Copyright octobre 2023, Stephan Runigo
runigo@free.fr
(SiCP 1.3.7  simulateur de chaîne de pendules septembre 2017)
SimFourier 1.0 Transformation de Fourier
Ce logiciel est un programme informatique servant à donner une représentation
graphique de la transformation de Fourier à 1 dimension.
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


int grapheInitialisation(grapheT * graphe, int nombre);

int graphesInitialisation(graphesT * graphes, int nombre)
	{
	grapheInitialisation(&(*graphes).fonction, nombre);
	grapheInitialisation(&(*graphes).fourier, nombre);
	(*graphes).fonction.ratiox = 0.5;
	(*graphes).fonction.ratioy = 0.33;
	(*graphes).fourier.ratiox = 0.5;
	(*graphes).fourier.ratioy = 0.66;
	return 0:
	}

int grapheInitialisation(grapheT * graphe, int nombre)
	{
	(*graphe).nombre=nombre;
	for(i=0;i<NOMBRE_MAX){
		pointInitialise(fonction[i])pointT ;
		}
	for(j=0;j<7){
		(*graphe).supporX[j] = 0;
		(*graphe).supporY[j] = 0;
		}

	(*graphe).support = 1;	// Change la représentation graphique du support

	(*graphe).dessous = 0;	// Vue de dessous
	(*graphe).arriere = 0;	// Vue de derrière
	(*graphe).gauche = 0;		// Vue de gauche

	(*graphe).longueur = LONGUEUR_IMP;// largeur de la chaîne
	(*graphe).rayon = RAYON_IMP;// hauteur de la chaîne

	pointDeVueInitialise((*graphe)pointDeVue);

	return 0;
	}

int graphesInitialisePointDeVue(graphesT * graphes, float r, float psi, float phi)
	{
		// Initialise la position de l'observateur et calcul les vecteurs perpendiculaires

	grapheInitialisePointDeVue(&(*graphes).fonction, r, psi, phi);
	grapheInitialisePointDeVue(&(*graphes).fourier, r, psi, phi);
	
	GrapheReinitialiseBase(graphe);

	return 0;
	}

int grapheInitialisePointDeVue(grapheT * graphe, float r, float psi, float phi)
	{
		// Initialise la position de l'observateur et calcul les vecteurs perpendiculaires

	vecteurInitialisePolaire(&(*graphe).pointDeVue, r, psi, phi);
	
	GrapheReinitialiseBase(graphe);

	return 0;
	}

int GrapheReinitialiseBase(grapheT * graphe)
	{
		// Réinitialise les vecteurs perpendiculaires

	vecteurInitialisePhi(&(*graphe).pointDeVue.pointDeVue, &(*graphe).pointDeVue.vecteurPhi, (*graphe).longueur);
	vecteurInitialisePsi(&(*graphe).pointDeVue.pointDeVue, &(*graphe).pointDeVue.vecteurPsi, (*graphe).rayon);

	return 0;
	}

int GrapheInitialiseSupport(grapheT * graphe)
//
//                                                Z
//                                          Y              X'
//                                                O
//                                                      Y'
//                                                Z'
//             X

	{
	int i;
	float xyz;
	for(i=0;i<6;i++)
		{
		(*graphe).support[i].x = 0;
		}

					// AXE Ox
	xyz = 1.2;//*(*graphe).rayon;
	(*graphe).support[0].x = xyz;
	(*graphe).support[1].x = -xyz;

					// AXE Oy
	xyz = 1.2;//*(*graphe).rayon;
	(*graphe).support[2].y = xyz;
	(*graphe).support[3].y = -xyz;

					// AXE Oz
	xyz = 6.5;// * (*graphe).longueur;
	(*graphe).support[4].z = xyz;
	xyz = 0.5;// * (*graphe).longueur;
	(*graphe).support[5].z = -xyz;
	(void)nombre;
	return 0;
	}

void grapheChangeSupport(grapheT * graphe){

	// Change la représentation graphique du support

	if((*graphe).support==1)
		{(*graphe).support=0;
		printf("Support invisible\n");}
	else
		{
		if((*graphe).support==0)
			{
			(*graphe).support=-1;
			printf("Support transparent\n");
			}
		else
			{
			(*graphe).support=1;
			printf("Support plein\n");
			}
		}
	}

//////////////////////////////////////////////////////////////////
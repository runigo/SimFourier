/*
Copyright octobre 2023, Stephan Runigo
runigo@free.fr
(SiCP 2.5 simulateur de chaîne de pendules, fevrier 2021)
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

#ifndef _PROJECTIONSYSTEM_
#define _PROJECTIONSYSTEM_

#include "../modele/systeme.h"
#include "../modele/observables.h"
#include "../projection/graphes.h"
#include "../interface/commandes.h"
#include "../interface/capteurs.h"

				//		Projections du systeme sur les commandes
				//		les capteurs et les graphes

typedef struct ProjectionSystemT projectionSystemT;
	struct ProjectionSystemT
		{
		int fenetreX;	// hauteur de la fenêtre
		int fenetreY;	// largeur de la fenêtre
		float ratioXY;	// rapport largeur / hauteur

			// facteurs entre les grandeurs et la position des boutons rotatifs
		float logCouplage;
		float logDissipation;
		float logJosephson;
		float logAmplitude;
		float logFrequence;
		};

	//-----------------    INITIALISATION      -----------------------//
int projectionSystemInitialise(projectionSystemT * projection);

	//-----------------    PROJECTION      -----------------------//
int projectionSystemeGraphes(systemeT * systeme, projectionSystemT * projection, graphesT * graphes);
int projectionObservablesCapteurs(observablesT * observables, projectionSystemT * projection, capteursT * capteurs);
int projectionSystemeCommandes(systemeT * systeme, projectionSystemT * projection, commandesT * commandes);
int projectionControleurCommandes(projectionSystemT * projection, commandesT * commandes, int duree, int mode);

	//-----------------    CHANGE      -----------------------//
int projectionSystemChangeFenetre(projectionSystemT * projection, int x, int y);

	//-----------------    AFFICHAGE      -----------------------//
void projectionSystemAffiche(projectionSystemT * projection);

#endif

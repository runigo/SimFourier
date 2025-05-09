/*
Copyright mars 2025, Stephan Runigo
runigo@free.fr
SimFourier 1.2.2 Transformation de Fourier
(d'après SiCF 2.0  simulateur de corde vibrante et spectre, mars 2019)
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

#ifndef _FONCTION_
#define _FONCTION_

#include "math.h"
#include "../donnees/constantes.h"


typedef struct FonctionT fonctionT;
	struct FonctionT
		{
		double reel[NOMBRE_MAX];	//   Une fonction est un tableau de réèl
		double imag[NOMBRE_MAX];	// et un tableau d'imaginaire.

		double module[NOMBRE_MAX];	// Enregistrement du module

		int nombre;					// Nombre de points
		};

int fonctionInitialise(fonctionT * spectre, int nombre);
int fonctionChangeNombre(fonctionT * spectre, int nombre);
int fonctionAnnule(fonctionT * fonction);


double fonctionSommeModuleCarre(fonctionT * fonction);

double fonctionModuleMax1(fonctionT * fonction);
double fonctionsModuleMax1(fonctionT * f1, fonctionT * f2);
int fonctionModuleDivise(fonctionT * fonction, double max);

int fonctionRacinesNemesDe1(fonctionT * rd1, int n);
int fonctionRacinesMoins1(fonctionT * rd1, int n);
int fonctionCalcule(fonctionT * spectre, int k, int n);

int fonctionAffiche(fonctionT * f);
int fonctionTest(fonctionT * f);

int fonctionEgale(fonctionT * fonction, fonctionT * resultat);
int fonctionReplier(fonctionT * spectre, int diviseur);
int fonctionNormale(fonctionT * f, fonctionT * nf);
int fonctionNormalise(fonctionT * f,  double max);
int fonctionNormaliseNombre(fonctionT * f);

//int fonctionModuleCarre(fonctionT * f, fonctionT * modCar);
int fonctionModuleCarreMax1(fonctionT * f, fonctionT * modCar);

double fonctionSomme(fonctionT * f);
double fonctionMoyenne(fonctionT * f);
double fonctionSommeModuleCarre(fonctionT * f);


#endif

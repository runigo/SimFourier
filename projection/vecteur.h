/*
Copyright octobre 2023, Stephan Runigo
runigo@free.fr
(SiCP 1.3 simulateur de chaîne de pendules, juillet 2017)
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
offert aux utilisateurs qu'une garantie limitée.  Pour les mêmes raisons,
seule une responsabilité restreinte pèse sur l'auteur du programme, le
titulaire des droits patrimoniaux et les concédants successifs.
A cet égard  l'attention de l'utilisateur est attirée sur les risques
associés au chargement,  à l'utilisation,  à la modification et/ou au
développement et à la reproduction du logiciel par l'utilisateur étant
donné sa spécificité de logiciel libre, qui peut le rendre complexe à
manipuler et qui le réserve donc à des développeurs et des professionnels
avertis possédant  des  connaissances  informatiques approfondies. Les
utilisateurs sont donc invités à charger  et  tester  l'adéquation du
logiciel à leurs besoins dans des conditions permettant d'assurer la
sécurité de leurs systèmes et ou de leurs données et, plus généralement,
à l'utiliser et l'exploiter dans les mêmes conditions de sécurité.
Le fait que vous puissiez accéder à cet en-tête signifie que vous avez
pris connaissance de la licence CeCILL, et que vous en avez accepté les
termes.
*/

#ifndef _VECTEUR_
#define _VECTEUR_

#include "../donnees/constantes.h"

	// Un vecteurT contient les trois coordonnées cartésienne
	// et éventuellement les coordonées polaires.

typedef struct VecteurT vecteurT;
	struct VecteurT
		{
		float x;
		float y;
		float z;
		float r;
		float psi;
		float phi;
		};

	// Initialisation des trois coordonées cartésiennes
void vecteurCartesien(vecteurT * v, float x, float y, float z);
	// Initialisation des coordonées polaire et calcul des coordonées cartésiennes
void vecteurInitialisePolaire(vecteurT * v, float r, float psi, float phi);
	// retourne le produit scalaire
float vecteurScalaireCartesien(vecteurT * v1, vecteurT * v2);
	// v3 = v1 + v2
void vecteurSommeCartesien(vecteurT * v1, vecteurT * v2, vecteurT * v3);
	// v3 = v1 - v2
void vecteurDifferenceCartesien(vecteurT * v1, vecteurT * v2, vecteurT * v3);

	// Calcul des vecteurs perpendiculaires au vecteur position
int vecteurInitialiseVecteurPhi(vecteurT * position, vecteurT * vecteurPhi, float hauteur);
int vecteurInitialiseVecteurPsi(vecteurT * position, vecteurT * vecteurPsi, float largeur);

	// Affiche les informations
void vecteurAffiche(vecteurT * v);
#endif

/*
Copyright mars 2025, Stephan Runigo
runigo@free.fr
SimFourier 1.2.2 Transformation de Fourier
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

#ifndef _MOTIF_
#define _MOTIF_

#include "fonction.h"
/*
		Un motif est une fonction non périodique.
		  L'enveloppe est ce motif éventuellement
		périodicisé.
*/

typedef struct MotifT motifT;
	struct MotifT
		{
		fonctionT fonction;	//	Fonction motif

		int forme;	//	0 : constante, 1 : harmonique, 2 : carrée, 3 : triangle.

		double symetrie;	//	0 <= symetrie <= 1

		double amplitude;	//	amplitude
		double moyenne;	//	décalage verticale
		};

	//	Initialisation
int motifInitialisation(motifT * motif, int nombre);

	// Calcul du motif
int motifCalculMotif(motifT * motif, int periode);

	// Changement des paramètres
int motifVariationParametre(motifT * motif, int parametre, int variation);
int motifRegleParametre(motifT * motif, int parametre, int pourMille);

	//	Affichage des paramètres
int motifAffiche(motifT * motif);

#endif

////////////////////////////////////////////////////////////

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

#ifndef _PARTIE_
#define _PARTIE_

#include "motif.h"

/*
		Une partie est une fonction éventuellement périodique.

		La fonction initiale est le produit de deux parties : une enveloppe
		et une porteuse.
*/

typedef struct PartieT partieT;
	struct PartieT
		{
		fonctionT fonction;		//	Enveloppe ou porteuse

		int eta;		//	Puissance de deux dans la période
		int rho;		//	Écart à la puissance de deux de la période
		int khi;		//	Décalage horizontal, déphasage : [0,N[
		int periode;			//	Période

		int complexe;		//	-1 SI enveloppe,
						// 0 porteuse réelle, 1 porteuse complexe, 2 peigne de Dirac, 3 constante/
		int periodique;		//	-1 SI porteuse, 0 enveloppe non-périodique, 1 enveloppe périodique.
		};

	//	Initialisation de partie
int partieInitialisation(partieT * partie, int nombre);

	//	Calcul des parties initiales
int partieCalculPorteuse(partieT * partie);
int partieCalculPeriode(partieT * partie);
int partieCalculHarmonique(partieT * partie);

	// Changement d'un paramètre
int partieChangeParametre(partieT * partie, int parametre, int variation);
int partieRegleParametre(partieT * partie, int parametre, int pourMille);

#endif

////////////////////////////////////////////////////////////

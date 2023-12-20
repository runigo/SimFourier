/*
Copyright novembre 2023, Stephan Runigo
runigo@free.fr
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

#ifndef _PARTIE_
#define _PARTIE_

#include "motif.h"

typedef struct PartieT partieT;
	struct PartieT
		{
		fonctionT fonction;	// Enveloppe ou porteuse

		int nombre;			//	Nombre de points

		int nombrePeriode;		//	Nombre de période
		int deltaPeriode;		//	Pourcentage
		float phase;			//	phase
		float amplitude;		//	amplitude
		float facteur;			//	facteur de symétrie

		int complexe;			//	oscillation harmonique
		int periodique;			//	périodise le carré et le triangle

		int forme;			//	0 : harmonique, 1 : carrée, 2 : triangle, 3 : gaussienne
		};

	//	Initialisation de partie
int partieInitialisation(partieT * partie, int nombre);
int partieCreationPosition(partieT * partie, int forme);
int partieChangeComplexe(partieT * partie, int mode);
int partieChangePeriodique(partieT * partie, int mode);


	// Changement des paramètres
int partieChangeForme(partieT * partie, int forme);
int partieChangeNombrePeriode(partieT * partie, int delta);
int partieChangeDeltaPeriode(partieT * partie, int delta);

	// Changement des paramètres du motif
int partieChangeForme(partieT * partie, int forme);
int partieChangeNombrePeriode(partieT * partie, int delta);
int partieChangeDeltaPeriode(partieT * partie, int delta);
int partieChangeAmplitude(partieT * partie, float facteur);

#endif

////////////////////////////////////////////////////////////

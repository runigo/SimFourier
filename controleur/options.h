/*
Copyright février 2025, Stephan Runigo
runigo@free.fr
SimFourier 1.2.1 Transformation de Fourier
(d'après SiCP 1.3.7 simulateur de chaîne de pendules, septembre 2017)
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

#ifndef _OPTIONS_
#define _OPTIONS_

#include "../donnees/constantes.h"
#include "string.h"

typedef struct OptionsT optionsT;
	struct OptionsT
		{
			// OPTIONS CONTROLEUR
		int fond;		// couleur du fond de l'affichage
		int modeDemo;		// 0 : SiCP, 1 Graphique démo, 2 Commande démo
		int modeClavier;	// Ctrl F1 :  SiCP, Ctrl F2 : Graphiques, Ctrl F3 : Paramètres, Ctrl F4 : moteurs
		int modePause;		// Evolution système
		int mode;		//	0 : initiale, 1 : simulation, 2 : énergie potentielle
		int duree;		// Nombre d'évolution du système entre les affichages

			// OPTIONS MODELE
		float dt;		// discrétisation du temps
		float echelle;		// échelle de l'amplitude de la TF
		int nombre;		// nombre de pendule
		int support;		// Chaîne avec ou sans support
		int equation;		// équation simulée

		};

int optionsTraitement(optionsT * opt, int nbOpt, char *option[]);
void optionsChangeMode(optionsT * opt);
void optionsChangeVitesse(optionsT * opt, float facteur);
int optionsChangeEchelle(optionsT * options, float facteur);
#endif

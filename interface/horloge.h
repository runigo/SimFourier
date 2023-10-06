/*
Copyright septembre 2019, Stephan Runigo
runigo@free.fr
SiCP 2.4 simulateur de chaîne de pendules
Ce logiciel est un programme informatique servant à simuler l'équation
d'une chaîne de pendules et à en donner une représentation graphique.
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

// Librement inspiré de 
// http://piconano2015.wixsite.com/soft/code
// Copyright 2015 par PicoSoft.

#ifndef _HORLOGE_
#define _HORLOGE_

#include "interface.h"

typedef struct HorlogeT horlogeT;
	struct HorlogeT
		{
		SDL_TimerID horloge;	// timer principal

		long int depart;	// Départ du chronomètre

		int projection[MEMOIRE_CHRONO];	// Durée de la projection du système sur le graphique
		int evolution[MEMOIRE_CHRONO];	// Durée de l'évolution du système
		int graphique[MEMOIRE_CHRONO];	// Durée de la construction graphique
		int total[MEMOIRE_CHRONO];	// Durée total de l'évolution du controleur

		int index; // instant présent des mémoire
		};

Uint32 horlogeEvenement(Uint32 it, horlogeT * horloge);

int horlogeCreation(horlogeT * horloge);
int horlogeSuppression(horlogeT * horloge);

int horlogeChrono(horlogeT * horloge, int etape);

int horlogeAffiche(horlogeT * horloge);

#endif

/*
Copyright octobre 2023, Stephan Runigo
runigo@free.fr
(SiCP 2.2 simulateur de chaîne de pendules avril 2018)
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

// Librement inspiré de 
// http://piconano2015.wixsite.com/soft/code
// Copyright 2015 par PicoSoft.

#include "horloge.h"

/*
	VARIABLES GLOBALES
*/

SDL_Event user_event;
int *paramTimer;

/*
	...............
*/

Uint32 callTimer(Uint32 it, void *para);

int horlogeCreation(horlogeT * horloge)
	{
		//fprintf(stderr, " Initialisation de l'horloge \n");

	user_event.type=SDL_USEREVENT;

		// Lancement du Timer principal
	(*horloge).horloge = SDL_AddTimer(TEMPS_AFFICHAGE, callTimer, &paramTimer);

	(*horloge).depart = 0;	// Date du départ du chronomètre

	return 0;
	}

Uint32 callTimer(Uint32 it, void *para)
	{				// Callback du timer principal
	SDL_PushEvent(&user_event);
	(void) para;
	return it;
	}

int horlogeSuppression(horlogeT * horloge)
	{
	SDL_RemoveTimer((*horloge).horloge);	// Suppression du timer
	return 0;
	}

int horlogeChronoDepart(horlogeT * horloge)
	{
	(*horloge).depart = SDL_GetTicks();	// Départ du chronomètre
	return 0;
	}

int horlogeChronoDuree(horlogeT * horloge)
	{					// Durée chronométrée
	return (int)(SDL_GetTicks() - (*horloge).depart);
	}

//////////////////////////////////////////////////////////////////////////////

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

#include "donnees.h"

	//		Initialisation du controleur

int donneesSysteme(systemeT * systeme, optionsT * options);
int donneesGraphe(grapheT * graphe, optionsT * options);

int donneesOptions(optionsT * options)
	{
		// Préréglage des valeurs optionnelles

	(*options).modeDemo = 1;		// 0 : SiCP, 1 Graphique démo, 2 Commande démo
	(*options).modeClavier = 1;		// 0 : SiCP, 1 Graphique démo, 2 Commande démo
	(*options).modeMenu = 0;		// 0 : SiCP, 1 Graphique démo, 2 Commande démo

	(*options).modePause = 1;		// avec ou sans attente
	(*options).duree = DUREE;		// 100 : temps réèl.

	(*options).fond=240;		// couleur du fond de l'affichage
	(*options).support=-1;		// Graphisme du support de la chaîne


	(*options).dt=DT;		// discrétisation du temps
	(*options).nombre=NOMBRE;		// Nombre implicite de points
	(*options).equation=1;		// 1 : pendule, 2 : linéarisation,
							//	 3 : corde, 4 : dioptre

	return 0;
	}

int donneesControleur(controleurT * controleur)
	{

	(*controleur).sortie = 0;	// Sortie de SiCP si <> 0
	(*controleur).appui = 0;	// Appuie sur la souris
	(*controleur).modeMenu = (*controleur).options.modeMenu;		// 0 : Menu, 1 SiCP, 2SiCF, 3 SiGP

		fprintf(stderr, " Initialisation du système\n");
	donneesSysteme(&(*controleur).systeme, &(*controleur).options);

		fprintf(stderr, " Initialisation des graphe\n");
	graphesInitialisation(&(*controleur).graphes.fonction, (*controleur).options.nombre);
	graphesInitialisation(&(*controleur).graphes.fourier, (*controleur).options.nombre);

		//fprintf(stderr, " Initialisation des capteurs\n");
	capteursInitialise(&(*controleur).capteurs);
	capteursMiseAJourLongueur(&(*controleur).capteurs, FENETRE_X, FENETRE_Y);

		//fprintf(stderr, " Initialisation de la projection\n");
	projectionInitialise(&(*controleur).projection);

		fprintf(stderr, " Initialisation SDL\n");
	interfaceInitialisationSDL();
		//fprintf(stderr, " Création de l'interface SDL\n");
	interfaceCreation(&(*controleur).interface);
		//fprintf(stderr, " Création du rendu\n");
	graphiqueInitialisation(&(*controleur).graphique, &(*controleur).interface, TAILLE_MASSE, (*controleur).options.fond);

	int fenetreX;
	int fenetreY;
	int x, y;
		fprintf(stderr, " Initialisation des commmandes\n");
	SDL_GetWindowSize((*controleur).interface.fenetre, &fenetreX, &fenetreY);
	(*controleur).graphique.fenetreX=fenetreX;
	(*controleur).graphique.fenetreY=fenetreY;
	commandesInitialiseBoutons(&(*controleur).commandes, fenetreX, fenetreY);

	SDL_PumpEvents();
	SDL_GetMouseState(&x,&y);
	commandesInitialiseSouris(&(*controleur).commandes, x, y);

		fprintf(stderr, " Initialisation horloge SDL\n");
	horlogeCreation(&(*controleur).horloge);

	return 0;
	}

int donneesSysteme(systemeT * systeme, optionsT * options)
	{
		// Initialisation du système
	systemeInitialisation(systeme, (*options).nombre, (*options).dt);

		// Initialisation du potentiel
	systemeInitialisePotentiel(systeme, 9);

		// Initialisation des positions
	systemeInitialisePosition(systeme, 10);

	return 0;
	}

//////////////////////////////////////////////////////////////////////////

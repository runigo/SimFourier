/*
Copyright juin 2025, Stephan Runigo
runigo@free.fr
SimFourier 1.4 Transformation de Fourier
(d'après SiCP 2.5 simulateur de chaîne de pendules, février 2021)
Ce logiciel est un programme informatique servant à donner une représentation
graphique de la transformation de Fourier à 1 dimension et d'observer l'effet
d'un filtrage.
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

int donneesInitiale(controleurT * controleur);
int donneesModele(modeleT * modele, optionsT * options);
int donneesGraphe(grapheT * graphe, optionsT * options);

int donneesOptions(optionsT * options)
	{
		// Préréglage des valeurs optionnelles

	(*options).mode = 0;		//	0 : initiale, 1 : simulation, 2 : filtrage, 3 : énergie potentielle
											//		-1 : pause simulation

	(*options).duree = DUREE_IMP;		// 100 : temps réèl.

	(*options).fond=200;			// couleur du fond de l'affichage
	(*options).support=-1;			// Graphisme du support de la chaîne

	(*options).dt=DT_IMP;			// discrétisation du temps
	(*options).nombre=NOMBRE_IMP;		// Nombre implicite de points
	(*options).echelle=100;			// dans fonctionNormalise

	return 0;
	}

int donneesControleur(controleurT * controleur)
	{

	(*controleur).sortie = 0;	// Sortie de SiCP si <> 0
	(*controleur).appui = 0;	// Appuie sur la souris

		fprintf(stderr, " Initialisation du modèle\n");
	donneesModele(&(*controleur).modele, &(*controleur).options);

		fprintf(stderr, " Initialisation des graphes\n");
	grapheInitialisation(&(*controleur).projection.fonction, (*controleur).options.nombre);
	grapheInitialisation(&(*controleur).projection.fourier, (*controleur).options.nombre);

		fprintf(stderr, " Initialisation des capteurs\n");
	capteursInitialise(&(*controleur).capteurs);
	capteursMiseAJourLongueur(&(*controleur).capteurs, FENETRE_X, FENETRE_Y);

		fprintf(stderr, " Initialisation des projections\n");
	projectionInitialise(&(*controleur).projection, (*controleur).options.nombre);

	donneesInitiale(controleur);

		fprintf(stderr, " Initialisation SDL\n");
	interfaceInitialisationSDL();
		fprintf(stderr, " Création de l'interface SDL\n");
	interfaceCreation(&(*controleur).interface);
		fprintf(stderr, " Création du rendu\n");
	graphiqueInitialisation(&(*controleur).graphique, &(*controleur).interface);

		//	Ajuste les grandeurs souris et fenêtre
	controleurFenetre(controleur);

		fprintf(stderr, " Initialisation de l'horloge SDL\n");
	horlogeCreation(&(*controleur).horloge);

	return 0;
	}

int donneesModele(modeleT * modele, optionsT * options)
	{
		// Initialisation du modèle
	modeleInitialisation(modele, (*options).nombre, (*options).dt);

	return 0;
	}

int donneesInitiale(controleurT * controleur)
	{
		// Réglage de la fonction initiale

		//fprintf(stderr, " Fonction implicite\n");
		//	enveloppe Période 1
	modeleChangeInitiale(&(*controleur).modele, 1, 1, 0, 500);
		//	porteuse Période 1
	modeleChangeInitiale(&(*controleur).modele, 2, 1, 0, 500);
		//	porteuse Période 1
	modeleChangeInitiale(&(*controleur).modele, 2, 1, 0, 100);
		//	motif	dent de scie
	modeleChangeInitiale(&(*controleur).modele, 0, 0, 0, 3);
		//	enveloppe Phase
	modeleChangeInitiale(&(*controleur).modele, 1, 3, 0, 500);
		//	Mode transformé de fourier ou non
	controleurChangeMode(controleur, (*controleur).options.mode);

		//	Enveloppe sinus cardinal
	modeleChangeInitiale(&(*controleur).modele, 1, 0, 0, 4);
		//	Porteuse peigne de dirac
	modeleChangeInitiale(&(*controleur).modele, 2, 0, 0, 2);
		//	Porteuse eta = 5
	//modeleChangeInitiale(&(*controleur).modele, 2, 1, 0, 5);
		//	Porteuse rho = 0
	//modeleChangeInitiale(&(*controleur).modele, 2, 2, 0, 0);
		//	rho = 6, période = 14

	return 0;
	}

//////////////////////////////////////////////////////////////////////////

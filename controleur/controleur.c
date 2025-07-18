/*
Copyright juin 2025, Stephan Runigo
runigo@free.fr
SimFourier 1.4 Transformation de Fourier
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

#include "controleur.h"
#include "controleClavier.h"

	//	ÉVOLUTION
int controleurEvolution(controleurT * controleur);
int controleurEvolutionModele(controleurT * controleur);
int controleurProjection(controleurT * controleur);
int controleurConstructionGraphique(controleurT * controleur);
int controleurConstructionGrapheFiltrage(controleurT * controleur);
int controleurConstructionGrapheFourier(controleurT * controleur);
int controleurConstructionGraphe(graphiqueT * graphique, grapheT * graphe);
int controleurTraiteEvenement(controleurT * controleur);
int controleurKEYDOWN(controleurT * controleur);

	//	CHANGE

	//	SUPRESSION



	//	-------  ÉVOLUTION  -------  //

int controleurDemarrage(controleurT * controleur)
	{
				//	Boucle d'évolution temporelle du programme
	do	{
		if (SDL_WaitEvent(&(*controleur).interface.evenement))
			{
			controleurTraiteEvenement(controleur);
			}
		}
	while((*controleur).sortie == 0);

	return 0;
	}

int controleurTraiteEvenement(controleurT * controleur)
	{
						//	 Traitement des évenements SDL

	switch((*controleur).interface.evenement.type)
		{
		case SDL_QUIT:
			(*controleur).sortie = 1;break;
		case SDL_MOUSEWHEEL:
			controleSouris(controleur, 0);break;
		case SDL_MOUSEMOTION:
			controleSouris(controleur,1);break;
		case SDL_MOUSEBUTTONDOWN:
			controleSouris(controleur, 2);break;
		case SDL_MOUSEBUTTONUP:
			controleSouris(controleur, 3);break;
		case SDL_USEREVENT:
			controleurEvolution(controleur);break;
		case SDL_KEYDOWN:
			controleurKEYDOWN(controleur);break;
		default:
			;
		}
	return (*controleur).sortie;
	}

int controleurEvolution(controleurT * controleur)
	{
			//	Évolution du modèle et de l'affichage

	//horlogeChrono(&(*controleur).horloge, 0);

	controleurProjection(controleur);

	//horlogeChrono(&(*controleur).horloge, 1);

	controleurEvolutionModele(controleur);

	//horlogeChrono(&(*controleur).horloge, 2);

	controleurConstructionGraphique(controleur);

	//horlogeChrono(&(*controleur).horloge, 3);

	return (*controleur).sortie;
	}

int controleurProjection(controleurT * controleur)
	{
			//		Projection du modèle sur les graphes

	    //	Mise à jour fenêtre et souris
	controleurFenetre(controleur);

		//	Projection du modèle sur les graphes et les commandes
	projectionModele(&(*controleur).projection, &(*controleur).modele, (*controleur).options.mode);

	return (*controleur).sortie;
	}

int controleurFenetre(controleurT * controleur)
	{
		//		Mise à jour de la taille de la fenêtre
		//		et de la position de la souris

	int x, y;	//	FENÊTRE puis SOURIS

		// Taille de la fenêtre
	SDL_GetWindowSize((*controleur).interface.fenetre, &x, &y);

		// Réinitialisation des commandes si la FENÊTRE change de taille
	if((*controleur).graphique.fenetreX!=x || (*controleur).graphique.fenetreY!=y)
		{
		(*controleur).graphique.fenetreX=x;
		(*controleur).graphique.fenetreY=y;
		projectionChangeFenetre(&(*controleur).projection, x, y);
		(*controleur).graphique.facteur = commandesAjusteCommandes(&(*controleur).projection.commandes, x, y);
		capteursMiseAJourLongueur(&(*controleur).capteurs, x, y);
		}

		// Réinitialisation des commandes de la SOURIS
	SDL_PumpEvents();
	SDL_GetMouseState(&x,&y);
	commandesInitialiseSouris(&(*controleur).projection.commandes, x, y);

	return (*controleur).sortie;
	}

int controleurEvolutionModele(controleurT * controleur)
	{
		//	Évolution du modèle selon le mode
	//	0 : initiale, 1 : simulation, 2 : énergie potentielle, -1 : pause de la simulation
		//fprintf(stderr, "controleurEvolutionModele mode = %d\n", (*controleur).options.mode);
	switch((*controleur).options.mode)
		{
		case 0:
			modeleEvolutionInitiale(&(*controleur).modele, 1, (*controleur).options.echelle);break;
		case 1:
			modeleEvolutionSimulation(&(*controleur).modele, 1, (*controleur).options.echelle);break;
		case 2:
			modeleEvolutionInitiale(&(*controleur).modele, 1, (*controleur).options.echelle);break;
		case 3:
			modeleEnergiePotentielle(&(*controleur).modele, 1, (*controleur).options.echelle);
			(*controleur).options.mode=0;break;
		default:
			;
		}

	return 0;
	}

int controleurConstructionGraphique(controleurT * controleur)
	{
	        //  Construction du graphisme

		//fprintf(stderr, "Nettoyage de l'affichage\n");
	//graphiqueNettoyage(&(*controleur).graphique);

		//fprintf(stderr, "Dessin des graphes\n");
	if((*controleur).options.mode==2)
		{
		controleurConstructionGrapheFiltrage(controleur);
		}
	else
		{
		controleurConstructionGrapheFourier(controleur);
		}

		//fprintf(stderr, "Dessin des Commandes\n");
	graphiqueCommandes(&(*controleur).graphique, &(*controleur).projection.commandes, (*controleur).options.mode);

		//fprintf(stderr, "Dessin des capteurs\n");
	//graphiqueCapteurs(&(*controleur).graphique, &(*controleur).capteurs);

		//fprintf(stderr, "Mise à jour de l'affichage\n");
	graphiqueMiseAJour(&(*controleur).graphique);

	return (*controleur).sortie;
	}

int controleurConstructionGrapheFiltrage(controleurT * controleur)
	{
	        //  Construction des graphe en mode Filtrage
		//fprintf(stderr, "Dessin des graphes\n");

	SDL_Rect rectangle;
	rectangle.x = (*controleur).graphique.fenetreX/2;
	rectangle.y = (*controleur).graphique.fenetreY/2;
	rectangle.w = (*controleur).graphique.fenetreX/2;
	rectangle.h = (*controleur).graphique.fenetreY/2;

	graphiqueChangeCouleur(&(*controleur).graphique, (*controleur).graphique.affichage.fond);
	SDL_RenderFillRect((*controleur).graphique.affichage.rendu, &rectangle);

	controleurConstructionGraphe(&(*controleur).graphique, &(*controleur).projection.fou);

	rectangle.x = 0;

	graphiqueChangeCouleur(&(*controleur).graphique, (*controleur).graphique.affichage.fond);
	SDL_RenderFillRect((*controleur).graphique.affichage.rendu, &rectangle);

	controleurConstructionGraphe(&(*controleur).graphique, &(*controleur).projection.fourier);

	rectangle.x = (*controleur).graphique.fenetreX/2;
	rectangle.y = 0;

	graphiqueChangeCouleur(&(*controleur).graphique, (*controleur).graphique.affichage.fond);
	SDL_RenderFillRect((*controleur).graphique.affichage.rendu, &rectangle);

	controleurConstructionGraphe(&(*controleur).graphique, &(*controleur).projection.fct);

	rectangle.x = 0;

	graphiqueChangeCouleur(&(*controleur).graphique, (*controleur).graphique.affichage.fond);
	SDL_RenderFillRect((*controleur).graphique.affichage.rendu, &rectangle);

	controleurConstructionGraphe(&(*controleur).graphique, &(*controleur).projection.fonction);

	return 0;
	}

int controleurConstructionGrapheFourier(controleurT * controleur)
	{
	        //  Construction du graphisme en mode Fourier
		//fprintf(stderr, "Dessin des graphes\n");
	SDL_Rect rectangle;
	rectangle.x = 0;
	rectangle.y = (*controleur).graphique.fenetreY/2;
	rectangle.w = (*controleur).graphique.fenetreX;
	rectangle.h = (*controleur).graphique.fenetreY/2;

	graphiqueChangeCouleur(&(*controleur).graphique, (*controleur).graphique.affichage.fond);
	SDL_RenderFillRect((*controleur).graphique.affichage.rendu, &rectangle);

	controleurConstructionGraphe(&(*controleur).graphique, &(*controleur).projection.fourier);

	rectangle.y = 0;

	graphiqueChangeCouleur(&(*controleur).graphique, (*controleur).graphique.affichage.fond);
	SDL_RenderFillRect((*controleur).graphique.affichage.rendu, &rectangle);

	controleurConstructionGraphe(&(*controleur).graphique, &(*controleur).projection.fonction);

	return 0;
	}

int controleurConstructionGraphe(graphiqueT * graphique, grapheT * graphe)
	{
		//		Dessine une fonction

	if((*graphe).axes==0)
		{
		graphiqueFonction(graphique, graphe);
		}
	else
		{
		if((*graphe).axes==1)
			{
			graphiqueAxe(graphique, graphe);
			graphiqueFonction(graphique, graphe);
			}
		else
			{
			graphiqueFonction(graphique, graphe);
			graphiqueAxe(graphique, graphe);
			}
		}
	return 0;
	}

int controleurKEYDOWN(controleurT * controleur)
	{
					// Action lors de l'appuie d'une touche
	int Maj = 0;
	int Ctrl = 0;

		//	Enregistrement de l'appuie sur les touche Maj et Ctrl
	if ((((*controleur).interface.evenement.key.keysym.mod & KMOD_LSHIFT) == KMOD_LSHIFT)
	|| (((*controleur).interface.evenement.key.keysym.mod & KMOD_RSHIFT) == KMOD_RSHIFT))
		{
		Maj = 1;
		}
	if ((((*controleur).interface.evenement.key.keysym.mod & KMOD_LCTRL) == KMOD_LCTRL)
	|| (((*controleur).interface.evenement.key.keysym.mod & KMOD_RCTRL) == KMOD_RCTRL))
		{
		Ctrl = 1;
		}
			//	Traitement selon Maj et Ctrl

	if(Maj == 0 && Ctrl == 0)
		{
		return controleClavier(controleur);
		}
	else
		{
		if(Maj == 1 && Ctrl == 1)
			{
			return controleClavierCtrlMaj(controleur);
			}
		else
			{
			if(Maj == 1 )
				{
				if(controleClavierMaj(controleur) == 1)
					{
					controleurPostReinitialisation(controleur);
					}
				}
			else
				{
				if(controleClavierCtrl(controleur) == 1)
					{
					controleurPostReinitialisation(controleur);
					}
				}
			}
		}
	return (*controleur).sortie;
	}

void controleurPostReinitialisation(controleurT * controleur) {
		//		Remise à zéro des observables
	(void)controleur;
	//observablesInitialise(&(*controleur).observables);
	return;
	}

int controleurChangeMode(controleurT * controleur, int mode) {

		//		Inverse le mode de fonctionnement si mode < -1
		//		Regle le mode de fonctionnement sinon

	if(mode < -1)
		{
		optionsVariationMode(&(*controleur).options);
		printf("mode =%d => optionsVariationMode\n",mode);
		}
	else
		{
		optionsRegleMode(&(*controleur).options, mode);
		printf("mode =%d => optionsRegleMode\n",mode);
		}

		//	Position des graphes dans la fenêtre
	if((*controleur).options.mode == 2)	//	mode filtrage
		{
		(*controleur).projection.fonction.longueur = LONGUEUR_IMP;
		(*controleur).projection.fonction.positionX = 0.30;
		(*controleur).projection.fonction.positionY = 0.25;
		(*controleur).projection.fourier.longueur = LONGUEUR_IMP;
		(*controleur).projection.fourier.positionX = 0.30;
		(*controleur).projection.fourier.positionY = 0.75;
		(*controleur).projection.fct.positionX = 0.75;
		(*controleur).projection.fct.positionY = 0.25;
		(*controleur).projection.fou.positionX = 0.75;
		(*controleur).projection.fou.positionY = 0.75;
		}
	else	//	mode sans filtre
		{
		(*controleur).projection.fonction.longueur = 2 * LONGUEUR_IMP;
		(*controleur).projection.fonction.positionX = 0.50;
		(*controleur).projection.fonction.positionY = 0.25;
		(*controleur).projection.fourier.longueur = 2 * LONGUEUR_IMP;
		(*controleur).projection.fourier.positionX = 0.50;
		(*controleur).projection.fourier.positionY = 0.75;
		}

projectionChangeFenetre(&(*controleur).projection, (*controleur).graphique.fenetreX, (*controleur).graphique.fenetreY);

	return 0;
	}

	//	-------  SUPPRESSION  -------  //

int controleurSuppression(controleurT * control){

		//		Suppression du controleur

	fprintf(stderr, "Suppression de l'horloge\n");
	horlogeSuppression(&(*control).horloge);

	fprintf(stderr, "Suppression du rendu\n");
	graphiqueSuppression(&(*control).graphique);

	fprintf(stderr, "Suppression de la fenêtre\n");
	interfaceSuppression(&(*control).interface);

	fprintf(stderr, "Sortie de la SDL\n");
	interfaceQuitteSDL();

	return 0;
	}


//////////////////////////////////////////////////////////////////////////////////////

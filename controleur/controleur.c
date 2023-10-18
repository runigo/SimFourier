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

#include "controleur.h"
#include "controleurClavier.h"

	//	ÉVOLUTION

int controleurEvolution(controleurT * controleur);

int controleurProjection(controleurT * controleur);
int controleurEvolutionSysteme(controleurT * controleur);
int controleurConstructionGraphique(controleurT * controleur);
int controleurConstructionGraphe(graphiqueT * graphique, grapheT * graphe);

int controleurTraiteEvenement(controleurT * controleur);

int controleurKEYDOWN(controleurT * controleur);

	//	CHANGE

	//	SUPRESSION



	//	-------  ÉVOLUTION  -------  //

int controleurSimulationGraphique(controleurT * controleur)
	{
	do	{
		if (SDL_WaitEvent(&(*controleur).interface.evenement))
			{
			controleurTraiteEvenement(controleur);
			}
		}
	while((*controleur).sortie == 0);

	return 0;
	}

int controleurEvolution(controleurT * controleur)
	{

	//horlogeChrono(&(*controleur).horloge, 0);

	controleurProjection(controleur);

	//horlogeChrono(&(*controleur).horloge, 1);

	if((*controleur).options.modePause > 0)
		{
		controleurEvolutionSysteme(controleur);
		}

	//horlogeChrono(&(*controleur).horloge, 2);

	controleurConstructionGraphique(controleur);

	//horlogeChrono(&(*controleur).horloge, 3);

	return (*controleur).sortie;
	}

int controleurProjection(controleurT * controleur)
	{
		//		Mise à jour de la taille de la fenêtre
		//		Projection du système sur les graphes 3D
		//		Projection des graphes 3D sur les graphes 2D

	int x, y; //  fenêtre puis souris

		// Taille de la fenêtre
	SDL_GetWindowSize((*controleur).interface.fenetre, &x, &y);

		// Réinitialisation des commandes si la fenêtre change de taille
	if((*controleur).graphique.fenetreX!=x || (*controleur).graphique.fenetreY!=y)
		{
		(*controleur).graphique.fenetreX=x;
		(*controleur).graphique.fenetreY=y;
		projectionChangeFenetre(&(*controleur).projection, x, y);
		commandesInitialiseBoutons(&(*controleur).commandes, x, y);
		capteursMiseAJourLongueur(&(*controleur).capteurs, x, y);
		}

		// Réinitialisation des commandes de la souris
	SDL_PumpEvents();
	SDL_GetMouseState(&x,&y);
	commandesInitialiseSouris(&(*controleur).commandes, x, y);

	projectionSystemeGraphes(&(*controleur).systeme, &(*controleur).projection, &(*controleur).graphes);

	projectionObservablesCapteurs(&(*controleur).observables, &(*controleur).projection, &(*controleur).capteurs);

	projectionSystemeCommandes(&(*controleur).systeme, &(*controleur).projection, &(*controleur).commandes, (*controleur).options.duree, (*controleur).options.modePause);

	return (*controleur).sortie;
	}

int controleurEvolutionSysteme(controleurT * controleur)
	{
		//fprintf(stderr, "Evolution temporelle du système\n");
	systemeEvolution(&(*controleur).systeme, (*controleur).options.duree);

		//fprintf(stderr, "Mise à jour des observables\n");
	observablesMiseAJour(&(*controleur).observables, &(*controleur).systeme);

	return 0;
	}

int controleurConstructionGraphique(controleurT * controleur)
	{

		//fprintf(stderr, "Nettoyage de l'affichage\n");
	//graphiqueNettoyage(&(*controleur).graphique);

		//fprintf(stderr, "Dessin des Commandes\n");
	graphiqueCommandes(&(*controleur).graphique, &(*controleur).commandes);

		//fprintf(stderr, "Dessin des capteurs\n");
	graphiqueCapteurs(&(*controleur).graphique, &(*controleur).capteurs);

		//fprintf(stderr, "Dessin des graphes\n");
	controleurConstructionGraphe(&(*controleur).graphique, &(*controleur).graphes.fonction);
	controleurConstructionGraphe(&(*controleur).graphique, &(*controleur).graphes.fourier);

		//fprintf(stderr, "Mise à jour de l'affichage\n");
	graphiqueMiseAJour(&(*controleur).graphique);

	return (*controleur).sortie;
	}

int controleurConstructionGraphe(graphiqueT * graphique, grapheT * graphe)
	{
		//		Dessine un graphe
	if((*graphe).support==0)
		{
		graphiquePendule(graphique, graphe);
		}
	else
		{
		if((*graphe).support==1)
			{
			graphiquePenduleSupport(graphique, graphe);
			}
		else
			{
			graphiquePenduleSupportPlein(graphique, graphe);
			}
		}
	return 0;
	}

int controleurTraiteEvenement(controleurT * controleur)
	{
	int sortie = 0;
	switch((*controleur).interface.evenement.type)
		{
		case SDL_QUIT:
			(*controleur).sortie = 1;break;
		case SDL_MOUSEWHEEL:
			controleurSourisDefile(controleur);break;
		case SDL_MOUSEMOTION:
			controleurSouris(controleur);break;
		case SDL_MOUSEBUTTONDOWN:
			controleurSourisBouton(controleur, 1);break;
		case SDL_MOUSEBUTTONUP:
			controleurSourisBouton(controleur, 0);break;
		case SDL_USEREVENT:
			controleurEvolution(controleur);break;
		case SDL_KEYDOWN:
			controleurKEYDOWN(controleur);break;
		default:
			;
		}
	if(sortie!=0) (*controleur).sortie = 1;
	return (*controleur).sortie;
	}

int controleurKEYDOWN(controleurT * controleur)
	{
	int Maj = 0;
	int ctrl = 0;

	if ((((*controleur).interface.evenement.key.keysym.mod & KMOD_LSHIFT) == KMOD_LSHIFT)
	|| (((*controleur).interface.evenement.key.keysym.mod & KMOD_RSHIFT) == KMOD_RSHIFT))
		{
		Maj = 1;
		}
	if ((((*controleur).interface.evenement.key.keysym.mod & KMOD_LCTRL) == KMOD_LCTRL)
	|| (((*controleur).interface.evenement.key.keysym.mod & KMOD_RCTRL) == KMOD_RCTRL))
		{
		ctrl = 1;
		}
	if(Maj == 0 && ctrl == 0)
		{
		return controleurClavier(controleur);
		}
	else
		{
		if(Maj == 1 && ctrl == 1)
			{
			return controleurClavierCtrlMaj(controleur);
			}
		else
			{
			if(Maj == 1 )
				{
				if (controleurClavierMaj(controleur) == 1)
					{
					controleurPostReinitialisation(controleur);
					}
				}
			else
				{
				if (controleurClavierCtrl(controleur) == 1)
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

	observablesInitialise(&(*controleur).observables);

	return;
	}

	//	-------  SUPPRESSION  -------  //

int controleurDestruction(controleurT * control){

		//		Suppression du controleur

	fprintf(stderr, "Suppression de l'horloge\n");
	horlogeSuppression(&(*control).horloge);

	fprintf(stderr, "Suppression du rendu\n");
	graphiqueDestruction(&(*control).graphique);

	fprintf(stderr, "Suppression de la fenêtre\n");
	interfaceDestruction(&(*control).interface);

	fprintf(stderr, "Sortie de la SDL\n");
	interfaceQuitteSDL();

	return 0;
	}


//////////////////////////////////////////////////////////////////////////////////////

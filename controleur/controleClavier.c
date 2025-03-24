/*
Copyright mars 2025, Stephan Runigo
runigo@free.fr
SimFourier 1.2.3 Transformation de Fourier
(d'après SiCP 2.5 simulateur de chaîne de pendules, février 2021)
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

#include "controleClavier.h"

int controleClavier(controleurT * controleur)
	{
	switch ((*controleur).interface.evenement.key.keysym.sym)
		{

		case SDLK_RETURN:
			controleurEvolution(controleur);break;
		case SDLK_BACKSPACE:
			optionsChangePause(&(*controleur).options);break;
		case SDLK_SPACE:
			optionsChangePause(&(*controleur).options);break;
		case SDLK_ESCAPE:
			optionsChangeMode(&(*controleur).options);break;

			// Vitesse de la simulation
		case SDLK_KP_PLUS:
			optionsChangeVitesse(&(*controleur).options, 1.1);break;
		case SDLK_KP_MINUS:
			optionsChangeVitesse(&(*controleur).options, 0.91);break;
		case SDLK_F9:
			optionsChangeVitesse(&(*controleur).options, 0.32);break;
		case SDLK_F10:
			optionsChangeVitesse(&(*controleur).options, 0.91);break;
		case SDLK_F11:
			optionsChangeVitesse(&(*controleur).options, 1.1);break;
		case SDLK_F12:
			optionsChangeVitesse(&(*controleur).options, 3.1);break;


			// Afficher des informations

	//	case SDLK_F1:
		//	projectionSystemAffiche(&(*controleur).projection.parametreSystem);break;
		case SDLK_F2: // Position de la souris
			controleSourisAffiche(controleur);break;
	//	case SDLK_F3:
		//	pointDeVueAffiche(&(*controleur).graphes.fonction.pointDeVue);break;
	//	case SDLK_F4:
		//	printf("GRAPHE FONCTION :\n");
		//	grapheAffiche(&(*controleur).graphes.fonction);break;
	//	case SDLK_F5:
		//	printf("GRAPHE FOURIER :\n");
		//	grapheAffiche(&(*controleur).graphes.fourier);break;
		//	observablesAfficheEnergie(&(*controleur).modele.systeme);break;
	//	case SDLK_F6:
		//	moteursAfficheHorloge(&(*controleur).modele.systeme.moteurs);break;
	//	case SDLK_F7:
		//	projectionGraphAffiche(&(*controleur).projection.projectionGraph);break;
	// Support
		case SDLK_F8:
			optionsInitialiseMode(&(*controleur).options, 2);break;

	// Paramètres motif
		case SDLK_t: // Amplitude +
			modeleChangeInitiale(&(*controleur).modele, 0, 2, 1, 0);break;
		case SDLK_g: // Amplitude -
			modeleChangeInitiale(&(*controleur).modele, 0, 2, -1, 0);break;
		case SDLK_y: // Décalage +
			modeleChangeInitiale(&(*controleur).modele, 0, 3, 1, 0);break;
		case SDLK_h: // Décalage -
			modeleChangeInitiale(&(*controleur).modele, 0, 3, -1, 0);break;
		case SDLK_w: // Forme +
			modeleChangeInitiale(&(*controleur).modele, 0, 0, 1, 0);break;
		case SDLK_x: // Forme -
			modeleChangeInitiale(&(*controleur).modele, 0, 0, -1, 0);break;
		case SDLK_c: // Symétrie +
			modeleChangeInitiale(&(*controleur).modele, 0, 1, 1, 0);break;
		case SDLK_v: // Symétrie -
			modeleChangeInitiale(&(*controleur).modele, 0, 1, -1, 0);break;

	// Paramètres enveloppe
		case SDLK_a: // Eta +
			modeleChangeInitiale(&(*controleur).modele, 1, 1, 1, 0);break;
		case SDLK_q: // Eta -
			modeleChangeInitiale(&(*controleur).modele, 1, 1, -1, 0);break;
		case SDLK_s: // Rho +
			modeleChangeInitiale(&(*controleur).modele, 1, 2, 1, 0);break;
		case SDLK_d: // Rho -
			modeleChangeInitiale(&(*controleur).modele, 1, 2, -1, 0);break;
		case SDLK_z: // Périodique
			modeleChangeInitiale(&(*controleur).modele, 1, 0, 1, 0);break;
		case SDLK_e: // Non périodique
			modeleChangeInitiale(&(*controleur).modele, 1, 0, 0, 0);break;
		case SDLK_r: // Khi +
			modeleChangeInitiale(&(*controleur).modele, 1, 3, 1, 0);break;
		case SDLK_f: // Khi -
			modeleChangeInitiale(&(*controleur).modele, 1, 3, -1, 0);break;

	// Paramètres porteuse
		case SDLK_p: // Eta +
			modeleChangeInitiale(&(*controleur).modele, 2, 1, 1, 0);break;
		case SDLK_m: // Eta -
			modeleChangeInitiale(&(*controleur).modele, 2, 1, -1, 0);break;
		case SDLK_l: // Rho +
			modeleChangeInitiale(&(*controleur).modele, 2, 2, 1, 0);break;
		case SDLK_k: // Rho -
			modeleChangeInitiale(&(*controleur).modele, 2, 2, -1, 0);break;
		case SDLK_o: // Complexe
			modeleChangeInitiale(&(*controleur).modele, 2, 0, 0, 0);break;
		case SDLK_i: // Réel
			modeleChangeInitiale(&(*controleur).modele, 2, 0, 1, 0);break;
		case SDLK_u: // Khi +
			modeleChangeInitiale(&(*controleur).modele, 2, 3, 1, 0);break;
		case SDLK_j: // Khi -
			modeleChangeInitiale(&(*controleur).modele, 2, 3, -1, 0);break;

	// Paramètres graphique
		case SDLK_b:
			optionsChangeEchelle(&(*controleur).options, 1.1);break;
		case SDLK_n:
			optionsChangeEchelle(&(*controleur).options, 0.91);break;

		default:
			;
		}
	return (*controleur).sortie;
	}

int controleClavierMaj(controleurT * controleur)
	{
        //      Réinitialisation du système
        //          Fichiers utilisateur
	(void)controleur;
	int reinitialisation = 1;
/*
	switch ((*controleur).interface.evenement.key.keysym.sym)
		{
		case SDLK_a:
			fichierLecture(&(*controleur).modele.systeme, &(*controleur).graphes, "a");break;
		case SDLK_z:
			fichierLecture(&(*controleur).modele.systeme, &(*controleur).graphes, "z");break;
		case SDLK_e:
			fichierLecture(&(*controleur).modele.systeme, &(*controleur).graphes, "e");break;
		case SDLK_r:
			fichierLecture(&(*controleur).modele.systeme, &(*controleur).graphes, "r");break;
		case SDLK_t:
			fichierLecture(&(*controleur).modele.systeme, &(*controleur).graphes, "t");break;
		case SDLK_y:
			fichierLecture(&(*controleur).modele.systeme, &(*controleur).graphes, "y");break;
		case SDLK_u:
			fichierLecture(&(*controleur).modele.systeme, &(*controleur).graphes, "u");break;
		case SDLK_i:
			fichierLecture(&(*controleur).modele.systeme, &(*controleur).graphes, "i");break;
		case SDLK_o:
			fichierLecture(&(*controleur).modele.systeme, &(*controleur).graphes, "o");break;
		case SDLK_p:
			fichierLecture(&(*controleur).modele.systeme, &(*controleur).graphes, "p");break;
		case SDLK_q:
			fichierLecture(&(*controleur).modele.systeme, &(*controleur).graphes, "q");break;
		case SDLK_s:
			fichierLecture(&(*controleur).modele.systeme, &(*controleur).graphes, "s");break;
		case SDLK_d:
			fichierLecture(&(*controleur).modele.systeme, &(*controleur).graphes, "d");break;
		case SDLK_f:
			fichierLecture(&(*controleur).modele.systeme, &(*controleur).graphes, "f");break;
		case SDLK_g:
			fichierLecture(&(*controleur).modele.systeme, &(*controleur).graphes, "g");break;
		case SDLK_h:
			fichierLecture(&(*controleur).modele.systeme, &(*controleur).graphes, "h");break;
		case SDLK_j:
			fichierLecture(&(*controleur).modele.systeme, &(*controleur).graphes, "j");break;
		case SDLK_k:
			fichierLecture(&(*controleur).modele.systeme, &(*controleur).graphes, "k");break;
		case SDLK_l:
			fichierLecture(&(*controleur).modele.systeme, &(*controleur).graphes, "l");break;
		case SDLK_m:
			fichierLecture(&(*controleur).modele.systeme, &(*controleur).graphes, "m");break;
		case SDLK_w:
			fichierLecture(&(*controleur).modele.systeme, &(*controleur).graphes, "w");break;
		case SDLK_x:
			fichierLecture(&(*controleur).modele.systeme, &(*controleur).graphes, "x");break;
		case SDLK_c:
			fichierLecture(&(*controleur).modele.systeme, &(*controleur).graphes, "c");break;
		case SDLK_v:
			fichierLecture(&(*controleur).modele.systeme, &(*controleur).graphes, "v");break;
		case SDLK_b:
			fichierLecture(&(*controleur).modele.systeme, &(*controleur).graphes, "b");break;
		case SDLK_n:
			fichierLecture(&(*controleur).modele.systeme, &(*controleur).graphes, "n");break;
		default:
			{
			reinitialisation = 0;
			}break;
		}
*/
	return reinitialisation;
	}

int controleClavierCtrl(controleurT * controleur)
	{
        //      Réinitialisation du système 
        //          Fichiers original

	(void)controleur;
	int reinitialisation = 1;
/*
	switch ((*controleur).interface.evenement.key.keysym.sym)
		{
		case SDLK_a:
			fichierLecture(&(*controleur).modele.systeme, &(*controleur).graphes, "aa");break;
		case SDLK_z:
			fichierLecture(&(*controleur).modele.systeme, &(*controleur).graphes, "zz");break;
		case SDLK_e:
			fichierLecture(&(*controleur).modele.systeme, &(*controleur).graphes, "ee");break;
		case SDLK_r:
			fichierLecture(&(*controleur).modele.systeme, &(*controleur).graphes, "rr");break;
		case SDLK_t:
			fichierLecture(&(*controleur).modele.systeme, &(*controleur).graphes, "tt");break;
		case SDLK_y:
			fichierLecture(&(*controleur).modele.systeme, &(*controleur).graphes, "yy");break;
		case SDLK_u:
			fichierLecture(&(*controleur).modele.systeme, &(*controleur).graphes, "uu");break;
		case SDLK_i:
			fichierLecture(&(*controleur).modele.systeme, &(*controleur).graphes, "ii");break;
		case SDLK_o:
			fichierLecture(&(*controleur).modele.systeme, &(*controleur).graphes, "oo");break;
		case SDLK_p:
			fichierLecture(&(*controleur).modele.systeme, &(*controleur).graphes, "pp");break;
		case SDLK_q:
			fichierLecture(&(*controleur).modele.systeme, &(*controleur).graphes, "qq");break;
		case SDLK_s:
			fichierLecture(&(*controleur).modele.systeme, &(*controleur).graphes, "ss");break;
		case SDLK_d:
			fichierLecture(&(*controleur).modele.systeme, &(*controleur).graphes, "dd");break;
		case SDLK_f:
			fichierLecture(&(*controleur).modele.systeme, &(*controleur).graphes, "ff");break;
		case SDLK_g:
			fichierLecture(&(*controleur).modele.systeme, &(*controleur).graphes, "gg");break;
		case SDLK_h:
			fichierLecture(&(*controleur).modele.systeme, &(*controleur).graphes, "hh");break;
		case SDLK_j:
			fichierLecture(&(*controleur).modele.systeme, &(*controleur).graphes, "jj");break;
		case SDLK_k:
			fichierLecture(&(*controleur).modele.systeme, &(*controleur).graphes, "kk");break;
		case SDLK_l:
			fichierLecture(&(*controleur).modele.systeme, &(*controleur).graphes, "ll");break;
		case SDLK_m:
			fichierLecture(&(*controleur).modele.systeme, &(*controleur).graphes, "mm");break;
		case SDLK_w:
			fichierLecture(&(*controleur).modele.systeme, &(*controleur).graphes, "ww");break;
		case SDLK_x:
			fichierLecture(&(*controleur).modele.systeme, &(*controleur).graphes, "xx");break;
		case SDLK_c:
			fichierLecture(&(*controleur).modele.systeme, &(*controleur).graphes, "cc");break;
		case SDLK_v:
			fichierLecture(&(*controleur).modele.systeme, &(*controleur).graphes, "vv");break;
		case SDLK_b:
			fichierLecture(&(*controleur).modele.systeme, &(*controleur).graphes, "bb");break;
		case SDLK_n:
			fichierLecture(&(*controleur).modele.systeme, &(*controleur).graphes, "nn");break;
		default:
			{
			reinitialisation = 0;
			}break;
		}
*/
	return reinitialisation;
	}

int controleClavierCtrlMaj(controleurT * controleur) {

		//		Sauvegarde du système
	(void)controleur;
/*
	switch ((*controleur).interface.evenement.key.keysym.sym)
		{
		case SDLK_a:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).modele.systeme, &(*controleur).graphes, "a");break;
		case SDLK_z:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).modele.systeme, &(*controleur).graphes, "z");break;
		case SDLK_e:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).modele.systeme, &(*controleur).graphes, "e");break;
		case SDLK_r:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).modele.systeme, &(*controleur).graphes, "r");break;
		case SDLK_t:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).modele.systeme, &(*controleur).graphes, "t");break;
		case SDLK_y:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).modele.systeme, &(*controleur).graphes, "y");break;
		case SDLK_u:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).modele.systeme, &(*controleur).graphes, "u");break;
		case SDLK_i:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).modele.systeme, &(*controleur).graphes, "i");break;
		case SDLK_o:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).modele.systeme, &(*controleur).graphes, "o");break;
		case SDLK_p:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).modele.systeme, &(*controleur).graphes, "p");break;
		case SDLK_q:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).modele.systeme, &(*controleur).graphes, "q");break;
		case SDLK_s:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).modele.systeme, &(*controleur).graphes, "s");break;
		case SDLK_d:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).modele.systeme, &(*controleur).graphes, "d");break;
		case SDLK_f:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).modele.systeme, &(*controleur).graphes, "f");break;
		case SDLK_g:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).modele.systeme, &(*controleur).graphes, "g");break;
		case SDLK_h:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).modele.systeme, &(*controleur).graphes, "h");break;
		case SDLK_j:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).modele.systeme, &(*controleur).graphes, "j");break;
		case SDLK_k:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).modele.systeme, &(*controleur).graphes, "k");break;
		case SDLK_l:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).modele.systeme, &(*controleur).graphes, "l");break;
		case SDLK_m:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).modele.systeme, &(*controleur).graphes, "m");break;
		case SDLK_w:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).modele.systeme, &(*controleur).graphes, "w");break;
		case SDLK_x:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).modele.systeme, &(*controleur).graphes, "x");break;
		case SDLK_c:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).modele.systeme, &(*controleur).graphes, "c");break;
		case SDLK_v:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).modele.systeme, &(*controleur).graphes, "v");break;
		case SDLK_b:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).modele.systeme, &(*controleur).graphes, "b");break;
		case SDLK_n:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).modele.systeme, &(*controleur).graphes, "n");break;
		default:
			;
		}
*/
	return (*controleur).sortie;
	}

//////////////////////////////////////////////////////////////////////////////////////

/*
Copyright octobre 2023, Stephan Runigo
runigo@free.fr
(SiCP 2.5 simulateur de chaîne de pendules, fevrier 2021)
SimFourier 0.1 Transformation de Fourier
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

#include "controleurClavier.h"

int controleurClavier(controleurT * controleur)
	{
	switch ((*controleur).interface.evenement.key.keysym.sym)
		{
	// Mode : évolution du système en pause
		case SDLK_RETURN:
			controleurEvolutionSysteme(controleur);break;
		case SDLK_BACKSPACE:
			optionsChangeMode(&(*controleur).options);break;
		case SDLK_SPACE:
			optionsChangeMode(&(*controleur).options);break;
		case SDLK_ESCAPE:
			controleurSourisAffiche(controleur);break;
			;

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



		case SDLK_F1:
			projectionSystemAffiche(&(*controleur).projectionSystem);break;
  // Afficher les observables
	//	case SDLK_F2: // Harmoniques
		//	observablesAffiche(&(*controleur).observables);break;

		case SDLK_F3: // Point de vue
			pointDeVueAffiche(&(*controleur).graphes.fonction.pointDeVue);break;

		case SDLK_F4: // Corde asymétrique
			controleurSourisAffiche(controleur);break;
	//	case SDLK_F5:
		//	observablesAfficheEnergie(&(*controleur).systeme);break;
	//	case SDLK_F6:
		//	moteursAfficheHorloge(&(*controleur).systeme.moteurs);break;
		case SDLK_F7:
			projectionGraphAffiche(&(*controleur).projectionGraph);break;
	// Support
	//	case SDLK_F8:
	//		grapheChangeSupport(&(*controleur).graphes);break;


		default:
			;
		}
	return (*controleur).sortie;
	}

int controleurClavierMaj(controleurT * controleur)
	{
        //      Réinitialisation du système
        //          Fichiers utilisateur

	int reinitialisation = 1;

	switch ((*controleur).interface.evenement.key.keysym.sym)
		{
		case SDLK_a:
			fichierLecture(&(*controleur).systeme, &(*controleur).graphes, "a");break;
		case SDLK_z:
			fichierLecture(&(*controleur).systeme, &(*controleur).graphes, "z");break;
		case SDLK_e:
			fichierLecture(&(*controleur).systeme, &(*controleur).graphes, "e");break;
		case SDLK_r:
			fichierLecture(&(*controleur).systeme, &(*controleur).graphes, "r");break;
		case SDLK_t:
			fichierLecture(&(*controleur).systeme, &(*controleur).graphes, "t");break;
		case SDLK_y:
			fichierLecture(&(*controleur).systeme, &(*controleur).graphes, "y");break;
		case SDLK_u:
			fichierLecture(&(*controleur).systeme, &(*controleur).graphes, "u");break;
		case SDLK_i:
			fichierLecture(&(*controleur).systeme, &(*controleur).graphes, "i");break;
		case SDLK_o:
			fichierLecture(&(*controleur).systeme, &(*controleur).graphes, "o");break;
		case SDLK_p:
			fichierLecture(&(*controleur).systeme, &(*controleur).graphes, "p");break;
		case SDLK_q:
			fichierLecture(&(*controleur).systeme, &(*controleur).graphes, "q");break;
		case SDLK_s:
			fichierLecture(&(*controleur).systeme, &(*controleur).graphes, "s");break;
		case SDLK_d:
			fichierLecture(&(*controleur).systeme, &(*controleur).graphes, "d");break;
		case SDLK_f:
			fichierLecture(&(*controleur).systeme, &(*controleur).graphes, "f");break;
		case SDLK_g:
			fichierLecture(&(*controleur).systeme, &(*controleur).graphes, "g");break;
		case SDLK_h:
			fichierLecture(&(*controleur).systeme, &(*controleur).graphes, "h");break;
		case SDLK_j:
			fichierLecture(&(*controleur).systeme, &(*controleur).graphes, "j");break;
		case SDLK_k:
			fichierLecture(&(*controleur).systeme, &(*controleur).graphes, "k");break;
		case SDLK_l:
			fichierLecture(&(*controleur).systeme, &(*controleur).graphes, "l");break;
		case SDLK_m:
			fichierLecture(&(*controleur).systeme, &(*controleur).graphes, "m");break;
		case SDLK_w:
			fichierLecture(&(*controleur).systeme, &(*controleur).graphes, "w");break;
		case SDLK_x:
			fichierLecture(&(*controleur).systeme, &(*controleur).graphes, "x");break;
		case SDLK_c:
			fichierLecture(&(*controleur).systeme, &(*controleur).graphes, "c");break;
		case SDLK_v:
			fichierLecture(&(*controleur).systeme, &(*controleur).graphes, "v");break;
		case SDLK_b:
			fichierLecture(&(*controleur).systeme, &(*controleur).graphes, "b");break;
		case SDLK_n:
			fichierLecture(&(*controleur).systeme, &(*controleur).graphes, "n");break;
		default:
			{
			reinitialisation = 0;
			}break;
		}

	return reinitialisation;
	}

int controleurClavierCtrl(controleurT * controleur)
	{
        //      Réinitialisation du système 
        //          Fichiers original

	int reinitialisation = 1;

	switch ((*controleur).interface.evenement.key.keysym.sym)
		{
		case SDLK_a:
			fichierLecture(&(*controleur).systeme, &(*controleur).graphes, "aa");break;
		case SDLK_z:
			fichierLecture(&(*controleur).systeme, &(*controleur).graphes, "zz");break;
		case SDLK_e:
			fichierLecture(&(*controleur).systeme, &(*controleur).graphes, "ee");break;
		case SDLK_r:
			fichierLecture(&(*controleur).systeme, &(*controleur).graphes, "rr");break;
		case SDLK_t:
			fichierLecture(&(*controleur).systeme, &(*controleur).graphes, "tt");break;
		case SDLK_y:
			fichierLecture(&(*controleur).systeme, &(*controleur).graphes, "yy");break;
		case SDLK_u:
			fichierLecture(&(*controleur).systeme, &(*controleur).graphes, "uu");break;
		case SDLK_i:
			fichierLecture(&(*controleur).systeme, &(*controleur).graphes, "ii");break;
		case SDLK_o:
			fichierLecture(&(*controleur).systeme, &(*controleur).graphes, "oo");break;
		case SDLK_p:
			fichierLecture(&(*controleur).systeme, &(*controleur).graphes, "pp");break;
		case SDLK_q:
			fichierLecture(&(*controleur).systeme, &(*controleur).graphes, "qq");break;
		case SDLK_s:
			fichierLecture(&(*controleur).systeme, &(*controleur).graphes, "ss");break;
		case SDLK_d:
			fichierLecture(&(*controleur).systeme, &(*controleur).graphes, "dd");break;
		case SDLK_f:
			fichierLecture(&(*controleur).systeme, &(*controleur).graphes, "ff");break;
		case SDLK_g:
			fichierLecture(&(*controleur).systeme, &(*controleur).graphes, "gg");break;
		case SDLK_h:
			fichierLecture(&(*controleur).systeme, &(*controleur).graphes, "hh");break;
		case SDLK_j:
			fichierLecture(&(*controleur).systeme, &(*controleur).graphes, "jj");break;
		case SDLK_k:
			fichierLecture(&(*controleur).systeme, &(*controleur).graphes, "kk");break;
		case SDLK_l:
			fichierLecture(&(*controleur).systeme, &(*controleur).graphes, "ll");break;
		case SDLK_m:
			fichierLecture(&(*controleur).systeme, &(*controleur).graphes, "mm");break;
		case SDLK_w:
			fichierLecture(&(*controleur).systeme, &(*controleur).graphes, "ww");break;
		case SDLK_x:
			fichierLecture(&(*controleur).systeme, &(*controleur).graphes, "xx");break;
		case SDLK_c:
			fichierLecture(&(*controleur).systeme, &(*controleur).graphes, "cc");break;
		case SDLK_v:
			fichierLecture(&(*controleur).systeme, &(*controleur).graphes, "vv");break;
		case SDLK_b:
			fichierLecture(&(*controleur).systeme, &(*controleur).graphes, "bb");break;
		case SDLK_n:
			fichierLecture(&(*controleur).systeme, &(*controleur).graphes, "nn");break;
		default:
			{
			reinitialisation = 0;
			}break;
		}

	return reinitialisation;
	}

int controleurClavierCtrlMaj(controleurT * controleur) {

		//		Sauvegarde du système

	switch ((*controleur).interface.evenement.key.keysym.sym)
		{
		case SDLK_a:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphes, "a");break;
		case SDLK_z:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphes, "z");break;
		case SDLK_e:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphes, "e");break;
		case SDLK_r:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphes, "r");break;
		case SDLK_t:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphes, "t");break;
		case SDLK_y:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphes, "y");break;
		case SDLK_u:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphes, "u");break;
		case SDLK_i:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphes, "i");break;
		case SDLK_o:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphes, "o");break;
		case SDLK_p:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphes, "p");break;
		case SDLK_q:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphes, "q");break;
		case SDLK_s:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphes, "s");break;
		case SDLK_d:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphes, "d");break;
		case SDLK_f:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphes, "f");break;
		case SDLK_g:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphes, "g");break;
		case SDLK_h:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphes, "h");break;
		case SDLK_j:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphes, "j");break;
		case SDLK_k:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphes, "k");break;
		case SDLK_l:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphes, "l");break;
		case SDLK_m:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphes, "m");break;
		case SDLK_w:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphes, "w");break;
		case SDLK_x:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphes, "x");break;
		case SDLK_c:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphes, "c");break;
		case SDLK_v:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphes, "v");break;
		case SDLK_b:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphes, "b");break;
		case SDLK_n:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, &(*controleur).graphes, "n");break;
		default:
			;
		}
	return (*controleur).sortie;
	}

//////////////////////////////////////////////////////////////////////////////////////

/*
Copyright février 2025, Stephan Runigo
runigo@free.fr
SimFourier 1.2.2 Transformation de Fourier
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

#include "controleurSouris.h"

int controleurSourisPosition(controleurT * controleur);

int controleurSourisMolette(controleurT * controleur, int zone);
int controleurSourisMouvement(controleurT * controleur, int zone);
int controleurSourisBouton(controleurT * controleur, int appui, int zone);

int controleurSourisCommandes(controleurT * controleur, int zone);
int controleurSourisDefilePointDeVue(controleurT * controleur, grapheT * graphe);
int controleurSourisDefileCommandes(controleurT * controleur, int zone);
int controleurSourisInitialisePosition(controleurT * controleur, int position);

int controleurSouris(controleurT * controleur, int action)
	{
		//	Zone et action de la souris

	int zone = commandesSourisPosition(&(*controleur).commandes);

	switch(action)	//	
		{
		case 0: // Molette
			controleurSourisMolette(controleur, zone);break;
		case 1: // Mouvement
			controleurSourisMouvement(controleur, zone);break;
		case 2: // appuie cliq gauche
			controleurSourisBouton(controleur, 1, zone);break;
		case 3: // relache cliq gauche
			controleurSourisBouton(controleur, 0, zone);break;
		default:
			;
		}
	return 0;
	}

int controleurSourisMouvement(controleurT * controleur, int zone)
	{
				// Action du mouvement de la souris :
		//	 Si cliq appuyé et dans la zone des représentations 3D : change le point de vue.

	if((*controleur).appui==1)
		{
		if(zone == 5)
			{
			pointDeVueChangePsi(&(*controleur).graphes.fonction.pointDeVue, (-0.0031*(float)((*controleur).interface.evenement.motion.xrel)));
			pointDeVueChangePhi(&(*controleur).graphes.fonction.pointDeVue, (0.0031*(float)((*controleur).interface.evenement.motion.yrel)));
			}
		if(zone == 7)
			{
			pointDeVueChangePsi(&(*controleur).graphes.fourier.pointDeVue, (-0.0031*(float)((*controleur).interface.evenement.motion.xrel)));
			pointDeVueChangePhi(&(*controleur).graphes.fourier.pointDeVue, (0.0031*(float)((*controleur).interface.evenement.motion.yrel)));
			}
		}
	return 0;
	}

int controleurSourisMolette(controleurT * controleur, int zone)
	{
				// Action des mouvements de la mollette

	switch(zone)	//	
		{
		case 2: //	Boutons rotatif
			controleurSourisDefileCommandes(controleur, 1);break;
		case 5: //	Zone de la fonction
			controleurSourisDefilePointDeVue(controleur, &(*controleur).graphes.fonction);break;
		case 7: //	Zone de fourier
			controleurSourisDefilePointDeVue(controleur, &(*controleur).graphes.fourier);break;
	//	case 4: // zone des curseurs linéaires de la fonction
	//		;break;
	//	case 6: // zone des curseurs linéaires de fourier
	//		;break;
		default:
			;
		}
	return 0;
	}

int controleurSourisDefilePointDeVue(controleurT * controleur, grapheT * graphe)
	{
				// Action des mouvements de la mollette dans la zone des fonctions)

	if((*controleur).interface.evenement.wheel.y > 0) // scroll up
		{
		pointDeVueChangeDistance(&(*graphe).pointDeVue, 1.03);
		}
	else if((*controleur).interface.evenement.wheel.y < 0) // scroll down
		{
		pointDeVueChangeDistance(&(*graphe).pointDeVue, 0.97);
		}

	return 0;
	}

int controleurSourisBouton(controleurT * controleur, int appui, int zone)
	{
				// Action du bouton gauche de la souris

	(void)zone;

	(*controleur).appui=appui;

	return 0;
	}
/*
int controleurSourisCommandes(controleurT * controleur, int zone)
	{
				// Action du bouton gauche de la souris
				// dans les zones 2 et 3

	int commande;
	if(zone==2)
		{
		commande = commandeBoutons(&(*controleur).commandes);
		switch(commande)	//	
			{
			case 0: // 
				;break;
			default:
				;
			}
		}

	int reinitialisation;

	if(zone==3)
		{
		commande = commandeTriangles(&(*controleur).commandes);
		switch(commande)	//	
			{
			case 11:
				controleurSourisInitialisePosition(controleur, 1);
				reinitialisation = 1; break;
			case 20:
			    fichierLecture(&(*controleur).modele.systeme, &(*controleur).graphes, "ddd");
				reinitialisation = 1; break;
				//controleurInitialiseNombre(controleur, 4);break;
			default:
				;
			}
		}
	return reinitialisation;
	}
*/
int controleurSourisInitialisePosition(controleurT * controleur, int position) {

		//		Réinitialise les positions.
(void)position;
	modeleProjectionInitiale(&(*controleur).modele);

	return 0;
	}

int controleurSourisDefileCommandes(controleurT * controleur, int zone)
	{
	(void)controleur;
	(void)zone;
	//int commande = -1;
/*	if(zone==1)
		{
		commande = commandeRotatifs(&(*controleur).commandes);
		if((*controleur).interface.evenement.wheel.y > 0) // scroll up
			{
			switch(commande)
				{
				case 0:
					(&(*controleur).modele.systeme, 1.1);break;
				case 1:
					(&(*controleur).modele.systeme, 1.1);break;
				default:
					;
				}
			}
		else if((*controleur).interface.evenement.wheel.y < 0) // scroll down
			{
			switch(commande)	
				{
				case 0:
					(&(*controleur).modele.systeme, 0.91);break;
				case 1:
					(&(*controleur).modele.systeme, 0.91);break;
				default:
					;
				}
			}
		}
	if(zone==3)
		{
		commande = commandeLineaires(&(*controleur).commandes);
		if((*controleur).interface.evenement.wheel.y > 0) // scroll up
			{
			switch(commande)
				{
				case 2:
					optionsChangeVitesse(&(*controleur).options, 1.1);break;
				case 3:
					optionsChangeVitesse(&(*controleur).options, 1.1);break;
				default:
					;
				}
			}
		else if((*controleur).interface.evenement.wheel.y < 0) // scroll down
			{
			switch(commande)
				{
				case 2:
					optionsChangeVitesse(&(*controleur).options, 0.91);break;
				case 3:
					optionsChangeVitesse(&(*controleur).options, 0.91);break;
				default:
					;
				}
			}
		}
*/
	return 0;
	}

int controleurSourisAffiche(controleurT * controleur)
	{
	fprintf(stderr, "(*controleur).graphique.fenetreY = %d\n", (*controleur).graphique.fenetreY);
	fprintf(stderr, "(*controleur).commandes.sourisY = %d\n", (*controleur).commandes.sourisY);
	fprintf(stderr, "(*controleur).graphique.fenetreX = %d\n", (*controleur).graphique.fenetreX);
	fprintf(stderr, "(*controleur).commandes.sourisX = %d\n", (*controleur).commandes.sourisX);

	fprintf(stderr, "\nfenetreY / sourisY = %f\n\n", (float)(*controleur).commandes.sourisY / (*controleur).graphique.fenetreY);
	fprintf(stderr, "fenetreX / sourisX = %f\n", (float)(*controleur).commandes.sourisX / (*controleur).graphique.fenetreX);

	return 0;
	}

//////////////////////////////////////////////////////////////////////////////////////

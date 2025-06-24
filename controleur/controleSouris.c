/*
Copyright juin 2025, Stephan Runigo
runigo@free.fr
SimFourier 1.4 Transformation de Fourier
(d'après SiCP 2.5 simulateur de chaîne de pendules, février 2021)
Ce logiciel est un programme informatique permettant de donner une représentation
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

#include "controleSouris.h"

int controleSourisMouvement(controleurT * controleur);

int controleSourisBouton(controleurT * controleur, int appui);
int controleSourisCliqRotatif(controleurT * controleur, int menu);
int controleSourisCliqSelectif(controleurT * controleur, int menu);

int controleSourisMolette(controleurT * controleur);
int controleSourisMolettePointDeVue(controleurT * controleur, grapheT * graphe);
int controleSourisMoletteRotatifsGraphes(controleurT * controleur, int TF);
int controleSourisMoletteRotatifsInitial(controleurT * controleur);
int controleSourisMoletteRotatifsFiltres(controleurT * controleur);

//////////////////////////////////////////////////////////////////////////////////

int controleSouris(controleurT * controleur, int action)
	{
		//	Action de la souris

	switch(action)	//	action sur la souris
		{
		case 0: // Molette
			controleSourisMolette(controleur);break;
		case 1: // Mouvement
			controleSourisMouvement(controleur);break;
		case 2: // Appuie cliq gauche
			controleSourisBouton(controleur, 1);break;
		case 3: // Relache cliq gauche
			controleSourisBouton(controleur, 0);break;
		default:
			;
		}
	return 0;
	}

///////////////////////           ACTION DU MOUVEMENT DE LA SOURIS

int controleSourisMouvement(controleurT * controleur)
	{
				// Action du mouvement de la souris :
		//	 Si cliq appuyé et dans la zone des représentations 3D : change le point de vue.

	if((*controleur).appui==1)
		{
			//	Le pointeur de la souris se trouvant dans la zone
		int zone = commandesSourisZone(&(*controleur).projection.commandes);
		if(zone == 5)
			{
			pointDeVueChangePsi(&(*controleur).projection.fonction.pointDeVue, (-0.0031*(float)((*controleur).interface.evenement.motion.xrel)));
			pointDeVueChangePhi(&(*controleur).projection.fonction.pointDeVue, (0.0031*(float)((*controleur).interface.evenement.motion.yrel)));
			pointDeVueChangePsi(&(*controleur).projection.fct.pointDeVue, (-0.0031*(float)((*controleur).interface.evenement.motion.xrel)));
			pointDeVueChangePhi(&(*controleur).projection.fct.pointDeVue, (0.0031*(float)((*controleur).interface.evenement.motion.yrel)));
			}
		if(zone == 7)
			{
			pointDeVueChangePsi(&(*controleur).projection.fourier.pointDeVue, (-0.0031*(float)((*controleur).interface.evenement.motion.xrel)));
			pointDeVueChangePhi(&(*controleur).projection.fourier.pointDeVue, (0.0031*(float)((*controleur).interface.evenement.motion.yrel)));
			pointDeVueChangePsi(&(*controleur).projection.fou.pointDeVue, (-0.0031*(float)((*controleur).interface.evenement.motion.xrel)));
			pointDeVueChangePhi(&(*controleur).projection.fou.pointDeVue, (0.0031*(float)((*controleur).interface.evenement.motion.yrel)));
			}
		}
	return 0;
	}

//////////////////////////        ACTION  DU BOUTON DE LA SOURIS

int controleSourisBouton(controleurT * controleur, int appui)
	{
				// Action du bouton gauche de la souris

		//	Enregistre l'appui
	(*controleur).appui=appui;

	if(appui==1)
		{
			//	Le pointeur de la souris se trouvant dans la zone
		int zone = commandesSourisZone(&(*controleur).projection.commandes);
		switch(zone)	//	
			{
			case 2: //	Boutons rotatif de initiale
				controleSourisCliqRotatif(controleur, 2);break;
			case 3: //	Boutons selectif de initiale
				controleSourisCliqSelectif(controleur, 3);break;
			case 4: // zone du menu graphe-fonction
				controleSourisCliqSelectif(controleur, 4);break;
			case 6: // zone du menu graphe-fourier
				controleSourisCliqSelectif(controleur, 6);break;
			case 8: // Boutons rotatif du filtrage
				controleSourisCliqRotatif(controleur, 8);break;
			case 9: // Boutons selectif du filtrage
				controleSourisCliqSelectif(controleur, 9);break;
			case 10: // Bouton filtrage
				controleSourisCliqSelectif(controleur, 10);break;
			default:
				;
			}
		}

	return 0;
	}

int controleSourisCliqRotatif(controleurT * controleur, int menu)
	{
	int rotatif;
	int pourMille;
	double angle = PI/4;
	if(menu==2)
		{			//	Action du cliq de souris dans le menu rotatif initiale
			//	Numéro du rotatif
		rotatif = commandeRotatifsInitiale(&(*controleur).projection.commandes);
		fprintf(stderr, "\n controleSourisCliqRotatif, numéro : %d\n", rotatif);
			//	Position angulaire de la souris dans le rotatif
		angle = atan( (double)((*controleur).projection.commandes.rotatifInitial[rotatif].Y
		+ (*controleur).projection.commandes.rotatifInitial[rotatif].dY - (*controleur).projection.commandes.sourisY)
		/ ((*controleur).projection.commandes.rotatifInitialDroite - (*controleur).projection.commandes.sourisX));
		//fprintf(stderr, " controleSourisCliqRotatif, angle = %f\n", angle);
		pourMille = (int)(angle*1000/PIS2);

		switch(rotatif)	//	
			{
			case 0: //	enveloppe Période 1
				modeleChangeInitiale(&(*controleur).modele, 1, 1, 0, pourMille);break;
			case 1: //	enveloppe Période 2
				modeleChangeInitiale(&(*controleur).modele, 1, 2, 0, pourMille);break;
			case 2: //	motif Symétrie
				modeleChangeInitiale(&(*controleur).modele, 0, 1, 0, pourMille);break;
			case 3: //	motif Amplitude
				modeleChangeInitiale(&(*controleur).modele, 0, 2, 0, pourMille);break;
			case 4: //	enveloppe Phase
				modeleChangeInitiale(&(*controleur).modele, 1, 3, 0, pourMille);break;
			case 5: //	motif Décalage
				modeleChangeInitiale(&(*controleur).modele, 0, 3, 0, pourMille);break;
			case 6: //	porteuse Période 1
				modeleChangeInitiale(&(*controleur).modele, 2, 1, 0, pourMille);break;
			case 7: //	porteuse Période 2
				modeleChangeInitiale(&(*controleur).modele, 2, 2, 0, pourMille);break;
			default:
				printf("ERREUR : controleSourisCliqRotatif");
			}
		}

	if(menu==8)
		{			//	Action du cliq de souris dans le menu rotatif filtrage
			//	Numéro du rotatif
		rotatif = commandeRotatifsFiltres(&(*controleur).projection.commandes);
		fprintf(stderr, "\n controleSourisCliqRotatif, numéro : %d\n", rotatif);
			//	Position angulaire de la souris dans le rotatif
		angle = atan( (double)((*controleur).projection.commandes.rotatifFiltrag[rotatif].Y
		 + (*controleur).projection.commandes.rotatifFiltrag[rotatif].dY - (*controleur).projection.commandes.sourisY)
		 / ((*controleur).projection.commandes.rotatifFiltrDroite - (*controleur).projection.commandes.sourisX));
		//fprintf(stderr, " controleSourisCliqRotatif, angle = %f\n", angle);
		pourMille = (int)(angle*1000/PIS2);

		switch(rotatif)	//	
			{
			case 0: //	Fréquence 1
				modeleChangeFiltrage(&(*controleur).modele, 1, 1, 0, pourMille);break;
			case 1: //	Ordre 1
				modeleChangeFiltrage(&(*controleur).modele, 1, 2, 0, pourMille);break;
			case 2: //	Fréquence 2
				modeleChangeFiltrage(&(*controleur).modele, 2, 1, 0, pourMille);break;
			case 3: //	Ordre 2
				modeleChangeFiltrage(&(*controleur).modele, 2, 2, 0, pourMille);break;
			case 4: //	Fréquence 3
				modeleChangeFiltrage(&(*controleur).modele, 3, 1, 0, pourMille);break;
			case 5: //	Ordre 3
				modeleChangeFiltrage(&(*controleur).modele, 3, 2, 0, pourMille);break;
			case 6: //	Delta fréquence
				modeleChangeFiltrage(&(*controleur).modele, 3, 3, 0, pourMille);break;
			case 7: //	Amplification
				modeleChangeFiltrage(&(*controleur).modele, 0, 1, 0, pourMille);break;
			default:
				printf("ERREUR : controleSourisCliqRotatif\n");
			}
		}
	return 0;
	}


int controleSourisCliqSelectif(controleurT * controleur, int menu)
	{
			//	Action du cliq de souris dans les menus selectifs

	int selectif = 0;

	if(menu == 10)
		{
		optionsChangeMode(&(*controleur).options);
		}

	if (menu == 3)
		{
		selectif = commandeSelectifsInitiale(&(*controleur).projection.commandes);
		switch(selectif)	//	fonction ,  parametre ,  variation ,  pourMille
			{
			case 0: //	motif	constant
				modeleChangeInitiale(&(*controleur).modele, 0, 0, 0, 0);break;
			case 1: //	motif	rectangle
				modeleChangeInitiale(&(*controleur).modele, 0, 0, 0, 2);break;
			case 2: //	motif	dent de scie
				modeleChangeInitiale(&(*controleur).modele, 0, 0, 0, 3);break;
			case 3: //	motif	sinusoïdale
				modeleChangeInitiale(&(*controleur).modele, 0, 0, 0, 1);break;
			case 4: //	enveloppe	apériodique
				modeleChangeInitiale(&(*controleur).modele, 1, 0, 0, 0);break;
			case 5: //	enveloppe	périodique
				modeleChangeInitiale(&(*controleur).modele, 1, 0, 0, 1);break;
			case 6: //	enveloppe	gaussienne
				modeleChangeInitiale(&(*controleur).modele, 1, 0, 0, 2);break;
			case 7: //	enveloppe	laurentzienne
				modeleChangeInitiale(&(*controleur).modele, 1, 0, 0, 3);break;
			case 8: //	enveloppe	sinus cardinale
				modeleChangeInitiale(&(*controleur).modele, 1, 0, 0, 4);break;
			case 9: //	enveloppe	Centrage horizontal
				modeleChangeInitiale(&(*controleur).modele, 3, 0, 0, 0);break;
			/*case 10: //	enveloppe	minimum = 0
				modeleChangeInitiale(&(*controleur).modele, 1, 0, 0, 3);break;
			case 11: //	centrage vertical
				modeleChangeInitiale(&(*controleur).modele, 1, 0, 0, 3);break;*/
			case 12: //	porteuse	constant
				modeleChangeInitiale(&(*controleur).modele, 2, 0, 0, 3);break;
			case 13: //	porteuse	peigne de dirac
				modeleChangeInitiale(&(*controleur).modele, 2, 0, 0, 2);break;
			case 14: //	porteuse	réelle
				modeleChangeInitiale(&(*controleur).modele, 2, 0, 0, 0);break;
			case 15: //	porteuse	complexe
				modeleChangeInitiale(&(*controleur).modele, 2, 0, 0, 1);break;
			default:
				;
			}
		}

		//	printf("controleSourisCliqSelectif, menu == %d\n", menu);
	if (menu == 4 || 6)
		{
		selectif = commandeSelectifsGraphes(&(*controleur).projection.commandes);
		switch(selectif)	//	fonction ,  parametre ,  variation ,  pourMille
			{
			case 0: //	point de vue implicite
				projectionChangeParametre(&(*controleur).projection, menu, 0, 0, 0);break;
			case 1: //	point de vue imaginaire
				projectionChangeParametre(&(*controleur).projection, menu, 1, 0, 1);break;
			case 2: //	point de vue réel
				projectionChangeParametre(&(*controleur).projection, menu, 2, 0, 2);break;
			case 3: //	graphe point
				projectionChangeParametre(&(*controleur).projection, menu, 3, 0, 0);break;
			case 4: //	graphe courbe
				projectionChangeParametre(&(*controleur).projection, menu, 4, 0, 1);break;
			case 5: //	coordonnées vecteur
				projectionChangeParametre(&(*controleur).projection, menu, 5, 0, 1);break;
			case 6: //	coordonnées sans
				projectionChangeParametre(&(*controleur).projection, menu, 6, 0, 0);break;
			default:
				;
			}
		}

		//	printf("controleSourisCliqSelectif, menu == %d\n", menu);
	if (menu == 9)
		{
		selectif = commandeSelectifsFiltres(&(*controleur).projection.commandes);
		switch(selectif)	//	filtre ,  parametre ,  variation ,  pourMille
			{
			case 0: //	Éteint le filtre passe bas
				modeleChangeFiltrage(&(*controleur).modele, 1, 5, 0, 0);break;
			case 1: 	//	Passe bas symétrique
				modeleChangeFiltrage(&(*controleur).modele, 1, 5, 0, 1);
				modeleChangeFiltrage(&(*controleur).modele, 1, 4, 0, 0);break;
			case 2: 	//	Passe bas droite
				modeleChangeFiltrage(&(*controleur).modele, 1, 5, 0, 1);
				modeleChangeFiltrage(&(*controleur).modele, 1, 4, 0, 1);break;
			case 3: 	//	Passe bas gauche
				modeleChangeFiltrage(&(*controleur).modele, 1, 5, 0, 1);
				modeleChangeFiltrage(&(*controleur).modele, 1, 4, 0, -1);break;
			case 4: //	Éteint le filtre passe haut
				modeleChangeFiltrage(&(*controleur).modele, 2, 5, 0, 0);break;
			case 5:		//	Passe haut symétrique
				modeleChangeFiltrage(&(*controleur).modele, 2, 5, 0, 1);
				modeleChangeFiltrage(&(*controleur).modele, 2, 4, 0, 0);break;
			case 6:		//	Passe haut gauche
				modeleChangeFiltrage(&(*controleur).modele, 2, 5, 0, 1);
				modeleChangeFiltrage(&(*controleur).modele, 2, 4, 0, -1);break;
			case 7:		//	Passe haut droite
				modeleChangeFiltrage(&(*controleur).modele, 2, 5, 0, 1);
				modeleChangeFiltrage(&(*controleur).modele, 2, 4, 0, 1);break;
			case 8: //	Éteint le filtre passe bande
				modeleChangeFiltrage(&(*controleur).modele, 3, 5, 0, 0);break;
			case 9: 	//	Passe bande symétrique
				modeleChangeFiltrage(&(*controleur).modele, 3, 5, 0, 1);
				modeleChangeFiltrage(&(*controleur).modele, 3, 4, 0, 0);break;
			case 10: 	//	Passe bande gauche
				modeleChangeFiltrage(&(*controleur).modele, 3, 5, 0, 1);
				modeleChangeFiltrage(&(*controleur).modele, 3, 4, 0, -1);break;
			case 11: 	//	Passe bande droite
				modeleChangeFiltrage(&(*controleur).modele, 3, 5, 0, 1);
				modeleChangeFiltrage(&(*controleur).modele, 3, 4, 0, 1);break;
			case 12: 	//	Passe bande inverse
				modeleChangeFiltrage(&(*controleur).modele, 3, 5, 0, 1);
				modeleChangeFiltrage(&(*controleur).modele, 3, 5, 0, -1);break;
			default:
				;
			}
		}
	return 0;
	}

/////////////////////////         ACTION DE LA MOLLETTE

int controleSourisMolette(controleurT * controleur)
	{
				// Action des mouvements de la mollette

		//	Le pointeur de la souris se trouvant dans la zone
	int zone = commandesSourisZone(&(*controleur).projection.commandes);
	switch(zone)	//	
		{
		case 2: //	Boutons rotatif initial
			controleSourisMoletteRotatifsInitial(controleur);break;
		case 4: // zone des curseurs linéaires de la fonction (TF = 0)
			controleSourisMoletteRotatifsGraphes(controleur, 0);break;
		case 5: //	Zone de la fonction
			controleSourisMolettePointDeVue(controleur, &(*controleur).projection.fonction);
			controleSourisMolettePointDeVue(controleur, &(*controleur).projection.fct);break;
		case 6: // zone des curseurs linéaires de fourier (TF = 1)
			controleSourisMoletteRotatifsGraphes(controleur, 1);break;
		case 7: //	Zone de fourier
			controleSourisMolettePointDeVue(controleur, &(*controleur).projection.fourier);
			controleSourisMolettePointDeVue(controleur, &(*controleur).projection.fou);break;
		case 8: //	Boutons rotatif initial
			controleSourisMoletteRotatifsFiltres(controleur);break;
		default:
			;
		}
	return 0;
	}

int controleSourisMolettePointDeVue(controleurT * controleur, grapheT * graphe)
	{
				// Action des mouvements de la mollette dans la zone des fonctions

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
int controleSourisMoletteRotatifsInitial(controleurT * controleur)
	{
	int commande = commandeRotatifsInitiale(&(*controleur).projection.commandes);
	//commande = -1;
	if((*controleur).interface.evenement.wheel.y > 0) // scroll up
		{
		switch(commande)
			{
			case 0:
				modeleChangeInitiale(&(*controleur).modele, 1, 1, 1, 0);break;
			case 1:
				modeleChangeInitiale(&(*controleur).modele, 1, 2, 1, 0);break;
			case 2:
				modeleChangeInitiale(&(*controleur).modele, 0, 1, 1, 0);break;
			case 3:
				modeleChangeInitiale(&(*controleur).modele, 0, 2, 1, 0);break;
			case 4:
				modeleChangeInitiale(&(*controleur).modele, 1, 3, 1, 0);break;
			case 5:
				modeleChangeInitiale(&(*controleur).modele, 0, 3, 1, 0);break;
			case 6:
				modeleChangeInitiale(&(*controleur).modele, 2, 1, 1, 0);break;
			case 7:
				modeleChangeInitiale(&(*controleur).modele, 2, 2, 1, 0);break;
			default:
				;
			}
		}
	else if((*controleur).interface.evenement.wheel.y < 0) // scroll down
		{
		switch(commande)	
			{
			case 0:
				modeleChangeInitiale(&(*controleur).modele, 1, 1, -1, 0);break;
			case 1:
				modeleChangeInitiale(&(*controleur).modele, 1, 2, -1, 0);break;
			case 2:
				modeleChangeInitiale(&(*controleur).modele, 0, 1, -1, 0);break;
			case 3:
				modeleChangeInitiale(&(*controleur).modele, 0, 2, -1, 0);break;
			case 4:
				modeleChangeInitiale(&(*controleur).modele, 1, 3, -1, 0);break;
			case 5:
				modeleChangeInitiale(&(*controleur).modele, 0, 3, -1, 0);break;
			case 6:
				modeleChangeInitiale(&(*controleur).modele, 2, 1, -1, 0);break;
			case 7:
				modeleChangeInitiale(&(*controleur).modele, 2, 2, -1, 0);break;
			default:
				;
			}
		}
	return 0;
	}

int controleSourisMoletteRotatifsFiltres(controleurT * controleur)
	{
	int commande = commandeRotatifsFiltres(&(*controleur).projection.commandes);
	printf("controleSourisMoletteRotatifsFiltres %d\n", commande);

	if((*controleur).interface.evenement.wheel.y > 0) // scroll up
		{
		switch(commande)
			{
			case 0:	//	Fréquence 1
				modeleChangeFiltrage(&(*controleur).modele, 1, 1, 1, 0);break;
			case 1:	//	Ordre 1
				modeleChangeFiltrage(&(*controleur).modele, 1, 2, 1, 0);break;
			case 2:	//	Fréquence 2
				modeleChangeFiltrage(&(*controleur).modele, 2, 1, 1, 0);break;
			case 3:	//	Ordre 2
				modeleChangeFiltrage(&(*controleur).modele, 2, 2, 1, 0);break;
			case 4:	//	Fréquence 3
				modeleChangeFiltrage(&(*controleur).modele, 3, 1, 1, 0);break;
			case 5:	//	Ordre 3
				modeleChangeFiltrage(&(*controleur).modele, 3, 2, 1, 0);break;
			case 6:	//	Delta f 3
				modeleChangeFiltrage(&(*controleur).modele, 3, 3, 1, 0);break;
			case 7:	//	Amplification
				modeleChangeFiltrage(&(*controleur).modele, 0, 1, 1, 0);break;
			default:
				;
			}
		}
	else if((*controleur).interface.evenement.wheel.y < 0) // scroll down
		{
		switch(commande)	
			{
			case 0:	//	Fréquence 1
				modeleChangeFiltrage(&(*controleur).modele, 1, 1, -1, 0);break;
			case 1:	//	Ordre 1
				modeleChangeFiltrage(&(*controleur).modele, 1, 2, -1, 0);break;
			case 2:	//	Fréquence 2
				modeleChangeFiltrage(&(*controleur).modele, 2, 1, -1, 0);break;
			case 3:	//	Ordre 2
				modeleChangeFiltrage(&(*controleur).modele, 2, 2, -1, 0);break;
			case 4:	//	Fréquence 3
				modeleChangeFiltrage(&(*controleur).modele, 3, 1, -1, 0);break;
			case 5:	//	Ordre 3
				modeleChangeFiltrage(&(*controleur).modele, 3, 2, -1, 0);break;
			case 6:	//	Delta f 3
				modeleChangeFiltrage(&(*controleur).modele, 3, 3, -1, 0);break;
			case 7:	//	Amplification
				modeleChangeFiltrage(&(*controleur).modele, 0, 1, -1, 0);break;
			default:
				;
			}
		}
	return 0;
	}

int controleSourisMoletteRotatifsGraphes(controleurT * controleur, int TF)
	{
	int commande = commandeRotatifsGraphes(&(*controleur).projection.commandes);
	printf("controleSourisMoletteRotatifsGraphes %d\n", TF);

	if(commande == 0)
		{	
		if(TF == 1)	//	Rotatif du graphe de la TF
			{
			controleSourisMolettePointDeVue(controleur, &(*controleur).projection.fourier);
			}
		else	//	Rotatif du graphe de la fonction
			{
			controleSourisMolettePointDeVue(controleur, &(*controleur).projection.fonction);
			}
		}
	return 0;
	}

int controleSourisAffiche(controleurT * controleur)
	{
	printf("(*controleur).graphique.fenetreY = %d\n", (*controleur).graphique.fenetreY);
	printf("(*controleur).commandes.sourisY = %d\n", (*controleur).projection.commandes.sourisY);
	printf("(*controleur).graphique.fenetreX = %d\n", (*controleur).graphique.fenetreX);
	printf("(*controleur).commandes.sourisX = %d\n", (*controleur).projection.commandes.sourisX);

	return 0;
	}

//////////////////////////////////////////////////////////////////////////////////////

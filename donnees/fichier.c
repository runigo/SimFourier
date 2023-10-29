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

#include "fichier.h"

int fichierEcritureParametre(systemeT * systeme, graphesT * graphes, char * nom);
int fichierLectureParametre(systemeT * systeme, graphesT * graphes, char * nom);
int fichierEcriturePosition(systemeT * systeme, char * nom);
int fichierLecturePosition(systemeT * systeme, char * nom);

int fichierFonctionNulle(systemeT * systeme, graphesT * graphes);
int fichierFonctionTriangle(systemeT * systeme, graphesT * graphes, int numero);
int fichierFonctionCarre(systemeT * systeme, graphesT * graphes, int numero);
int fichierFonctionSinus(systemeT * systeme, graphesT * graphes, int numero);



int fichierEcriture(systemeT * systeme, graphesT * graphes, char * nom)
	{
	fprintf(stderr, "Ecriture des paramètres %s\n", nom);
	fichierEcritureParametre(systeme, graphes, nom);
	fprintf(stderr, "Ecriture des positions %s\n", nom);
	fichierEcriturePosition(systeme, nom);
	return 0;
	}

int fichierLecture(systemeT * systeme, graphesT * graphes, char * nom)
	{
			fprintf(stderr, "Réinitialisation du système\n");
	fprintf(stderr, "Initialisation des paramètres %s\n", nom);
	fichierLectureParametre(systeme, graphes, nom);
	fprintf(stderr, "Initialisation des positions %s\n", nom);
	fichierLecturePosition(systeme, nom);
	return 0;
	}

int fichierEcritureParametre(systemeT * systeme, graphesT * graphes, char * nom)
	{
	FILE *fichier; /* pointeur sur FILE */
	float reel;
	int entier;
	(void)graphes;


	char chemin[120] = "./donnees/enregistrement/parametre_";

	char * extension = ".simfourier";

	strncat(chemin, nom, 20);

	strncat(chemin, extension, 40);

	fichier = fopen(chemin, "w");

	if(fichier == NULL)
		{
		printf("Erreur d'ouverture du fichier d'enregistrement\n");
		printf("	Vérifier le répertoire donnees/enregistrement\n");
		}
	else
		{
		// Moteurs
			// Paramètres d'horloge
	/*	reel = (*systeme).moteurs.dt;
			fprintf(fichier, "%f\n", reel);
		reel = (*systeme).moteurs.chrono;
			fprintf(fichier, "%f\n", reel);

			// Moteur périodique sur le premier pendule
		entier = (*systeme).moteurs.generateur;
			fprintf(fichier, "%d\n", entier);
		reel = (*systeme).moteurs.amplitude;
			fprintf(fichier, "%f\n", reel);
		reel = (*systeme).moteurs.frequence;
			fprintf(fichier, "%f\n", reel);
		reel = (*systeme).moteurs.phi;
			fprintf(fichier, "%f\n", reel);

			// Moteur courant Josephson
		entier = (*systeme).moteurs.etatJosephson;
			fprintf(fichier, "%d\n", entier);
		reel = (*systeme).moteurs.courantJosephson;
			fprintf(fichier, "%f\n", reel);

			// Moteur créateur de Fluxon
		entier = (*systeme).moteurs.fluxon;
			fprintf(fichier, "%d\n", entier);
		reel = (*systeme).moteurs.deltaDephasage;
			fprintf(fichier, "%f\n", reel);
		reel = (*systeme).moteurs.dephasage;
			fprintf(fichier, "%f\n", reel);
*/
		// Caractéristique de la chaîne
		entier = (*systeme).nombre;
			fprintf(fichier, "%d\n", entier);

		// Paramètres physiques
		reel = (*systeme).masse;
			fprintf(fichier, "%f\n", reel);

		fclose(fichier);
		}

	return 0;
	}

int fichierLectureParametre(systemeT * systeme, graphesT * graphes, char * nom)
	{
	FILE *fichier; /* pointeur sur FILE */
	float reel = 0;
	int entier = 0;
	//(void)graphes;

	char chemin[120] = "./donnees/enregistrement/parametre_";

	char * extension = ".simfourier";

	strncat(chemin, nom, 20);

	strncat(chemin, extension, 40);

	fichier = fopen(chemin, "r");

	if(fichier == NULL)
		{
		printf("Erreur d'ouverture du fichier d'enregistrement\n");
		printf("	Vérifier le répertoire donnees/enregistrement\n");
		}
	else
		{
		
			fprintf(stderr, " Initialisation du système\n");
		systemeInitialisation(systeme,NOMBRE_IMP, DT_IMP);
	/*	// Initialisation du moteurs
			// Paramètres d'horloge
		fscanf(fichier, "%f\n", &reel);
		moteursInitialiseDt(&(*systeme).moteurs, reel);
		fscanf(fichier, "%f\n", &reel);
		moteursInitialiseChrono(&(*systeme).moteurs, reel);

			// Moteur périodique sur le premier pendule
		fscanf(fichier, "%d\n", &entier);
		moteursInitialiseGenerateur(&(*systeme).moteurs, entier);
		fscanf(fichier, "%f\n", &reel);
		moteursInitialiseAmplitude(&(*systeme).moteurs, reel);
		fscanf(fichier, "%f\n", &reel);
		moteursInitialiseFrequence(&(*systeme).moteurs, reel);
		fscanf(fichier, "%f\n", &reel);
		moteursInitialisePhi(&(*systeme).moteurs, reel);

			// Moteur courant Josephson
		fscanf(fichier, "%d\n", &entier);
		moteursInitialiseEtatJosephson(&(*systeme).moteurs, entier);
		fscanf(fichier, "%f\n", &reel);
		moteursInitialiseCourantJosephson(&(*systeme).moteurs, reel);

			// Moteur créateur de Fluxon
		fscanf(fichier, "%d\n", &entier);
		moteursInitialiseFluxon(&(*systeme).moteurs, entier);
		fscanf(fichier, "%f\n", &reel);
		moteursInitialiseDeltaDephasage(&(*systeme).moteurs, reel);
		fscanf(fichier, "%f\n", &reel);
		moteursInitialiseDephasage(&(*systeme).moteurs, reel);

*/

		// Initialisation de la chaîne
			// Caractéristiques
		fscanf(fichier, "%d\n", &entier);
		systemeInitialiseNombre(systeme, entier);

			// Paramètres physiques
		fscanf(fichier, "%f\n", &reel);
		systemeInitialiseMasse(systeme, reel);
		fclose(fichier);

			fprintf(stderr, " Initialisation des graphes\n");
		graphesInitialisation(graphes, (*systeme).nombre);
		}

	return 0;
	}

int fichierEcriturePosition(systemeT * systeme, char * nom)
	{
	FILE *fichier; /* pointeur sur FILE */

	char chemin[120] = "./donnees/enregistrement/position_";

	char * extension = ".simfourier";

	strncat(chemin, nom, 20);

	strncat(chemin, extension, 40);

	fichier = fopen(chemin, "w");

	if(fichier == NULL)
		{
		printf("Erreur d'ouverture du fichier d'enregistrement\n");
		printf("	Vérifier le répertoire donnees/enregistrement\n");
		}
	else
	   	{
	    double ancien, actuel, nouveau;
		int i;
	    for(i=0;i<(*systeme).nombre;i++)
	    	{
	    	ancien = (*systeme).ancien.reel[i];
	    	actuel = (*systeme).actuel.reel[i];
	    	nouveau = (*systeme).nouveau.reel[i];
	    	fprintf(fichier, "%f %f %f\n", ancien, actuel, nouveau);
	    	ancien = (*systeme).ancien.imag[i];
	    	actuel = (*systeme).actuel.imag[i];
	    	nouveau = (*systeme).nouveau.imag[i];
	    	fprintf(fichier, "%f %f %f\n", ancien, actuel, nouveau);
	    	}

    	fclose(fichier);
		}

	return 0;
	}

int fichierLecturePosition(systemeT * systeme, char * nom)
	{
	FILE *fichier; /* pointeur sur FILE */

	char chemin[120] = "./donnees/enregistrement/position_";

	char * extension = ".simfourier";

	strncat(chemin, nom, 20);

	strncat(chemin, extension, 40);

	fichier = fopen(chemin, "r");

	if(fichier == NULL)
		{
		printf("Erreur d'ouverture du fichier d'enregistrement\n");
		printf("	Vérifier le répertoire donnees/enregistrement\n");
		}
	else
		{
		float ancien, actuel, nouveau;
		int i;
	    for(i=0;i<(*systeme).nombre;i++)
			{
			ancien = 0;
			actuel = 0;
			nouveau = 0;
			fscanf(fichier, "%f %f %f\n", &ancien, &actuel, &nouveau);
			systemeInitialisePoint(systeme, ancien, actuel, nouveau, i);
			}

		fclose(fichier);
		}

	return 0;
	}

int fichierFonction(systemeT * systeme, graphesT * graphes, int numero)
	{
	switch (numero)
		{
		case 0: // Touche A
			fichierFonctionNulle(systeme, graphes);break;
		case 1: // Touche Z
			fichierFonctionSinus(systeme, graphes, 1);break;
		case 2: // Touche E
			fichierFonctionTriangle(systeme, graphes, 2);break;
		case 3: // Touche R
			fichierFonctionTriangle(systeme, graphes, 3);break;
		case 4: // Touche T
			fichierFonctionTriangle(systeme, graphes, 4);break;
		case 5: // Touche Y
			fichierFonctionTriangle(systeme, graphes, 5);break;
		case 6: // Touche U
			fichierFonctionTriangle(systeme, graphes, 6);break;
		case 7: // Touche I
			fichierFonctionSinus(systeme, graphes, 7);break;
		case 8: // Touche O
			fichierFonctionSinus(systeme, graphes, 8);break;
		case 9: // Touche P
			fichierFonctionCarre(systeme, graphes, 9);break;
		case 10: // Touche Q
			fichierFonctionSinus(systeme, graphes, 1);break;
		case 11: // Touche S
			fichierFonctionSinus(systeme, graphes, 2);break;
		case 12: // Touche D
			fichierFonctionSinus(systeme, graphes, 3);break;
		case 13: // Touche F
			fichierFonctionSinus(systeme, graphes, 4);break;
		case 14: // Touche G
			fichierFonctionSinus(systeme, graphes, 5);break;
		case 15: // Touche H
			fichierFonctionCarre(systeme, graphes, 1);break;
		case 16: // Touche J
			fichierFonctionCarre(systeme, graphes, 2);break;
		case 17: // Touche K
			fichierFonctionCarre(systeme, graphes, 3);break;
		case 18: // Touche L
			fichierFonctionCarre(systeme, graphes, 4);break;
		case 19: // Touche M
			fichierFonctionCarre(systeme, graphes, 5);break;
		case 20: // Touche W
			fichierFonctionSinus(systeme, graphes, 1);break;
		case 21: // Touche X
			fichierFonctionSinus(systeme, graphes, 2);break;
		case 22: // Touche C
			fichierFonctionSinus(systeme, graphes, 3);break;
		case 23: // Touche V
			fichierFonctionSinus(systeme, graphes, 4);break;
		case 24: // Touche B
			fichierFonctionSinus(systeme, graphes, 5);break;
		case 25: // Touche N
			fichierFonctionCarre(systeme, graphes, 1);break;
		default:
			;
		}
	return 0;
	}

int fichierFonctionNulle(systemeT * systeme, graphesT * graphes)
	{
	(void)graphes;
	(void)systeme;
	int i;

    for(i=0;i<(*systeme).nombre;i++)
		{
		systemeInitialisePoint(systeme, 0, 0, 0, i);
		}
	return 0;
	}

int fichierFonctionTriangle(systemeT * systeme, graphesT * graphes, int numero)
	{
	//float ancien, actuel;
	(void)graphes;
	(void)numero;
	fichierFonctionNulle(systeme, graphes);
/*
	switch (numero)
		{
		case 1:
			printf("Réinitialisation du système, numero = %d\n", numero);
			for(i=0;i<(*systeme).nombre/2;i++)
				{
				ancien = (float)(i*numero)/(float)(*systeme).nombre;
				actuel = ancien;
				penduleInitialisePosition(&(*systeme).pendule[i], ancien, actuel);
				penduleInitialisePosition(&(*systeme).pendule[(*systeme).nombre-1-i], ancien, actuel);
				}break;
		case 2:
			printf("Réinitialisation du système, numero = %d\n", numero);
			for(i=0;i<(*systeme).nombre/4;i++)
				{
				ancien = (float)(i*numero)/(float)(*systeme).nombre;
				actuel = ancien;
				penduleInitialisePosition(&(*systeme).pendule[i], ancien, actuel);
				penduleInitialisePosition(&(*systeme).pendule[(*systeme).nombre/2-1-i], ancien, actuel);
				}break;
		case 3:
			printf("Réinitialisation du système, numero = %d\n", numero);
			for(i=0;i<(*systeme).nombre/8;i++)
				{
				ancien = (float)(i*numero)/(float)(*systeme).nombre;
				actuel = ancien;
				penduleInitialisePosition(&(*systeme).pendule[i], ancien, actuel);
				penduleInitialisePosition(&(*systeme).pendule[(*systeme).nombre/4-1-i], ancien, actuel);
				}break;
		case 4:
			printf("Réinitialisation du système, numero = %d\n", numero);
			for(i=0;i<(*systeme).nombre/16;i++)
				{
				ancien = (float)(i*numero)/(float)(*systeme).nombre;
				actuel = ancien;
				penduleInitialisePosition(&(*systeme).pendule[i], ancien, actuel);
				penduleInitialisePosition(&(*systeme).pendule[(*systeme).nombre/8-1-i], ancien, actuel);
				}break;
		case 5:
			printf("Réinitialisation du système, numero = %d\n", numero);
			for(i=0;i<(*systeme).nombre/32;i++)
				{
				ancien = (float)(i*numero)/(float)(*systeme).nombre;
				actuel = ancien;
				penduleInitialisePosition(&(*systeme).pendule[i], ancien, actuel);
				penduleInitialisePosition(&(*systeme).pendule[(*systeme).nombre/16-1-i], ancien, actuel);
				}break;
		case 6:
			printf("Réinitialisation du système, numero = %d\n", numero);
			for(i=0;i<(*systeme).nombre/64;i++)
				{
				ancien = (float)(i*numero)/(float)(*systeme).nombre;
				actuel = ancien;
				penduleInitialisePosition(&(*systeme).pendule[i], ancien, actuel);
				penduleInitialisePosition(&(*systeme).pendule[(*systeme).nombre/64-1-i], ancien, actuel);
				}break;
		}
*/
	return 0;
	}

int fichierFonctionCarre(systemeT * systeme, graphesT * graphes, int numero)
	{
	//float ancien, actuel;
	(void)graphes;
	(void)numero;
	fichierFonctionNulle(systeme, graphes);
/*
	if(numero == 1)
		{
		printf("Réinitialisation du système, numero = 1\n");
		}
	else
		{
		printf("Réinitialisation du système, numero != 1\n");
		for(i=0;i<(*systeme).nombre/2;i++)
			{
			ancien = i*numero/(*systeme).nombre;
			actuel = ancien;
			penduleInitialisePosition(&(*systeme).pendule[i], ancien, actuel);
			penduleInitialisePosition(&(*systeme).pendule[(*systeme).nombre-1-i], ancien, actuel);
			}
		}
*/
	return 0;
	}

int fichierFonctionSinus(systemeT * systeme, graphesT * graphes, int numero)
	{
	//float ancien, actuel;
	(void)graphes;
	(void)numero;
	fichierFonctionNulle(systeme, graphes);
/*
	if(numero == 1)
		{
		printf("Réinitialisation du système, numero = 1\n");
		}
	else
		{
		printf("Réinitialisation du système, numero != 1\n");
		for(i=0;i<(*systeme).nombre/2;i++)
			{
			ancien = i*numero/(*systeme).nombre;
			actuel = ancien;
			penduleInitialisePosition(&(*systeme).pendule[i], ancien, actuel);
			penduleInitialisePosition(&(*systeme).pendule[(*systeme).nombre-1-i], ancien, actuel);
			}
		}
*/
	return 0;
	}


///////////////////////////////////////////////////////////////////////////////////////////////

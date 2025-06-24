/*
Copyright juin 2025, Stephan Runigo
runigo@free.fr
SimFourier 1.4 Transformation de Fourier
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

#include "initiale.h"

	//		INITIALISATION

	//		CALCUL DES POSITIONS INITIALES
int initialeCalculInitiale(initialeT * initiale);
int initialeCalculParametre(initialeT * initiale);
//int initialeCalculPartie(partieT * partie);
int initialeCalculEnveloppe(initialeT * initiale);
int initialeCalculUnique(initialeT * initiale);
int initialeCalculPeriodique(initialeT * initiale);
int initialePeriodiseEnveloppe(initialeT * initiale);

	//		JAUGE ET NORMALISATION
int initialeJaugeZero(initialeT * initiale);

int InitialeRegleParametre(initialeT * initiale, int parametre);

/*------------------------  INITIALISATION  -------------------------*/

int initialeInitialisation(initialeT * initiale, int nombre) {

		partieInitialisation(&(*initiale).enveloppe, nombre);
		partieInitialisation(&(*initiale).porteuse, nombre);
		motifInitialisation(&(*initiale).motif, nombre);

		(*initiale).enveloppe.periodique = 0;	//	Enveloppe non périodique
		(*initiale).porteuse.complexe = 0;		//	Porteuse non complexe

	return 0;
}


/*--------------------  CALCUL DE LA FONCTION INITIALE  ---------------------*/

int initialeNettoyage(initialeT * initiale) {

		//	Annule les fonctions
		fonctionAnnule(&(*initiale).enveloppe.fonction);
		fonctionAnnule(&(*initiale).porteuse.fonction);
		fonctionAnnule(&(*initiale).motif.fonction);

	return 0;
}

int initialeCalculInitiale(initialeT * initiale) {

			//fprintf(stderr, " Calcul des fonctions initiales \n");

		//	Calcul du motif
	motifCalculMotif(&(*initiale).motif, (*initiale).enveloppe.periode);

		//	Calcul de l'enveloppe
	initialeCalculEnveloppe(initiale);

		//	Calcul de la porteuse
	partieCalculPartie(&(*initiale).porteuse, (*initiale).motif.amplitude);

	return 0; 

}

int initialeCalculEnveloppe(initialeT * initiale) {

				// Calcul de l'enveloppe

	switch ((*initiale).enveloppe.periodique)
		{
		case 0:	//	harmonique
			initialePeriodiseEnveloppe(initiale);break;
		case 1:	//	harmonique
			initialePeriodiseEnveloppe(initiale);break;
		default:
			partieCalculPartie(&(*initiale).enveloppe, (*initiale).motif.amplitude);
		}

	return 0;
}

int initialePeriodiseEnveloppe(initialeT * initiale) {

		// Périodise (ou non) le motif

	int i, j, d = 0;
	int nombre=(*initiale).enveloppe.fonction.nombre;

	if((*initiale).enveloppe.periodique==0)	//	Enveloppe non périodique
		{
		d = (*initiale).enveloppe.khi;
		for(i=0;i<nombre;i++)
			{
			j = (i-d) % nombre;
			(*initiale).enveloppe.fonction.reel[i] = (*initiale).motif.fonction.reel[j];
			(*initiale).enveloppe.fonction.imag[i] = (*initiale).motif.fonction.imag[j];
			}
		}
	else	//	Enveloppe périodique
		{
		d = (int)((2*PI*(*initiale).enveloppe.khi)/nombre);
	printf("initialePeriodiseEnveloppe  (*initiale).enveloppe.periode = %i\n", (*initiale).enveloppe.periode);
		for(i=0;i<nombre;i++)
			{
			j = (i-d) % (*initiale).enveloppe.periode;
			(*initiale).enveloppe.fonction.reel[i] = (*initiale).motif.fonction.reel[j];
			(*initiale).enveloppe.fonction.imag[i] = (*initiale).motif.fonction.imag[j];
			}
		}

	return 0;
}

/*------------------------  CHANGEMENT DES PARAMÈTRES  -------------------------*/

int initialeChangeParametre(initialeT * initiale, int fonction, int parametre, int variation, int pourMille)
	{
		//	Change un paramètre (réglage ou variation)

	fprintf(stderr, "initialeChangeParametre, %d, %d, %d, %d \n", fonction, parametre, variation, pourMille);

		//	Nettoyage des fonctions
	initialeNettoyage(initiale);

	if(parametre == 0 && fonction == 0)	//	réglage de la forme du motif
		{
		if((*initiale).enveloppe.periodique > 1)	//	enveloppe 2, 3 ou 4
			{
			(*initiale).enveloppe.periodique = 0; 
			}
		}

	if(variation == 0)
		{				// Réglage du paramètre ( fixe le paramètre à 'pourMille' )
		switch (fonction)
			{
			case 0:	// Motif
				motifRegleParametre(&(*initiale).motif, parametre, pourMille);break;
			case 1:	// Enveloppe
				partieRegleParametre(&(*initiale).enveloppe, parametre, pourMille);break;
			case 2:	// Porteuse
				partieRegleParametre(&(*initiale).porteuse, parametre, pourMille);break;
			case 3:	// Porteuse
				InitialeRegleParametre(initiale, parametre);break;
			default:
				fprintf(stderr, "ERREUR : initialeChangeParametre(initiale, %d, %d, %d, %d)", fonction, parametre, variation, pourMille);
			}
		}
	else
		{					// Variation du paramètre ( le fait varier de 'variation' )
		switch (fonction)
			{
			case 0:	// Motif
				motifVariationParametre(&(*initiale).motif, parametre, variation);break;
			case 1:	// Enveloppe
				partieVariationParametre(&(*initiale).enveloppe, parametre, variation);break;
			case 2:	// Porteuse
				partieVariationParametre(&(*initiale).porteuse, parametre, variation);break;
			default:
				fprintf(stderr, "ERREUR : initialeChangeParametre(initiale, %d, %d, %d, %d)", fonction, parametre, variation, pourMille);
			}
		}

		// Calcul de la fonction initiale
	initialeCalculInitiale(initiale);

	fprintf(stderr, "initialeChangeParametre, sortie \n\n");

	return 0;
	}

int InitialeRegleParametre(initialeT * initiale, int parametre)
	{
		//	Centre le motif
	(void)parametre;

	if((*initiale).enveloppe.periodique > 1)	//	Courbe en cloche
		{
		(*initiale).enveloppe.khi = (*initiale).enveloppe.fonction.nombre / 2;
		}
	else
		{
		(*initiale).enveloppe.khi = ((*initiale).enveloppe.fonction.nombre - (*initiale).enveloppe.periode ) / 2;
		}

	return 0;
	}

/*------------------------  AFFICHAGE DES PARAMÈTRES  -------------------------*/

int initialeAffiche(initialeT * initiale)
	{
	motifAffiche(&(*initiale).motif);
	partieAffiche(&(*initiale).enveloppe);
	partieAffiche(&(*initiale).porteuse);
	return 0;
	}
//////////////////////////////////////////////////////////////////////////

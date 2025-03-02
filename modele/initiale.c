/*
Copyright mars 2025, Stephan Runigo
runigo@free.fr
SimFourier 1.2.2 Transformation de Fourier
Ce logiciel est un programme informatique servant à donner une représentation
graphique de la transformation de Fourier à 1 dimension et de la simulation
d'équations de propagation.s
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

int initialeCalculInitiale(initialeT * initiale) {
	//	Mise à jour de la fonction initiale

		// Calcul des périodes
	partieCalculPeriode(&(*initiale).enveloppe);
	partieCalculPeriode(&(*initiale).porteuse);

		// Calcul du motif
	motifCalculMotif(&(*initiale).motif, (*initiale).enveloppe.P);

		fprintf(stderr, " Calcul des fonctions initiales \n");
	initialeCalculEnveloppe(initiale);
	partieCalculHarmonique(&(*initiale).porteuse);

	return 0; 

}

int initialeCalculEnveloppe(initialeT * initiale) {

		// Calcul de l'enveloppe

	int i;
	int nombre=(*initiale).enveloppe.fonction.nombre;

	if((*initiale).motif.forme == 0)
		{
		for(i=0;i<nombre;i++)
			{
			(*initiale).enveloppe.fonction.reel[i] = (*initiale).motif.A;
			(*initiale).enveloppe.fonction.imag[i] = (*initiale).motif.A;
			}
		}
	else
		{
		initialePeriodiseEnveloppe(initiale);
		}

	return 0;
}

int initialePeriodiseEnveloppe(initialeT * initiale) {

		// Périodise (ou non) le motif

	int i, j, d=0;
	int nombre=(*initiale).enveloppe.fonction.nombre;

	if((*initiale).enveloppe.periodique==0)
		{
		d = (*initiale).enveloppe.khi;
		for(i=0;i<nombre;i++)
			{
			j = (i+d) % nombre;
			(*initiale).enveloppe.fonction.reel[i] = (*initiale).motif.fonction.reel[j];
			(*initiale).enveloppe.fonction.imag[i] = (*initiale).motif.fonction.imag[j];
			}
		}
	else
		{
		d = (int)((2*PI*(*initiale).enveloppe.khi)/nombre);
	printf("initialePeriodiseEnveloppe  (*initiale).enveloppe.P = %i\n", (*initiale).enveloppe.P);
		for(i=0;i<nombre;i++)
			{
			j = (i+d) % (*initiale).enveloppe.P;
			(*initiale).enveloppe.fonction.reel[i] = (*initiale).motif.fonction.reel[j];
			(*initiale).enveloppe.fonction.imag[i] = (*initiale).motif.fonction.imag[j];
			}
		}

	return 0;
}

/*------------------------  CHANGEMENT DES PARAMÈTRES  -------------------------*/

int initialeChangeParametre(initialeT * initiale, int fonction, int parametre, int variation) {

	// Change un paramètre de initiale

	switch (fonction)
		{
		case 0:	// Change un paramètre du motif
			motifChangeParametre(&(*initiale).motif, parametre, variation);break;
		case 1:	// Change un paramètre de l'enveloppe
			partieChangeParametre(&(*initiale).enveloppe, parametre, variation);break;
		case 2:	// Change un paramètre de la porteuse
			partieChangeParametre(&(*initiale).porteuse, parametre, variation);break;
		default:
			;
		}

	return 0;
}


int initialeRegleParametre(initialeT * initiale, int fonction, int parametre, int pourMille) {

	// Règle un paramètre de initiale

	switch (fonction)
		{
		case 0:	// Règle un paramètre du motif
			motifRegleParametre(&(*initiale).motif, parametre, pourMille);break;
		case 1:	// Règle un paramètre de l'enveloppe
			partieRegleParametre(&(*initiale).enveloppe, parametre, pourMille);break;
		case 2:	// Règle un paramètre de la porteuse
			partieRegleParametre(&(*initiale).porteuse, parametre, pourMille);break;
		default:
			;
		}

	return 0;
}

//////////////////////////////////////////////////////////////////////////

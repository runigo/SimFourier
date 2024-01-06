/*
Copyright janvier 2024, Stephan Runigo
runigo@free.fr
SimFourier 1.1 Transformation de Fourier
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

#include "initiale.h"

	//		INITIALISATION
int initialeInitialisationPartie(partieT * partie, int nombre);
int initialeCreationPartie(partieT * partie);

	//		CRÉATION DES POSITIONS INITIALES

int initialeCalcule(partieT * partie);

int initialeCreationCarre(partieT * partie);
int initialeCreationUniforme(partieT * partie);
int initialeCreationHarmonique(partieT * partie);
/*
int initialeCreationEnveloppe(initialeT * initiale);
int initialeCreationPorteuse(initialeT * initiale);
int initialeCreationPorteuseHarmonique(initialeT * initiale);
int initialeCreationEnveloppeCarre(initialeT * initiale);
int initialeCreationEnveloppeUniforme(initialeT * initiale);
*/
	//		ÉVOLUTION TEMPORELLE
//int initialeIncremente(initialeT * initiale);

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

/*--------------------  CRÉATION DES POSITIONS INITIALES  ---------------------*/

	//	Mise à jour de la fonction initiale
int initialeCreationPosition(initialeT * initiale) {

(void)initiale;

		// Calcul de initial

	//	Mise à jour des paramètres

	//	Calcul des fonctions (motif, enveloppe, porteuse)

	return 0;

}

int initialeCalcul(initialeT * initiale) {

		//	Calcul des paramètres

		//fprintf(stderr, "initialeCreationPosition\n");
	initialeCreationPartie(&(*initiale).enveloppe);
	initialeCreationPartie(&(*initiale).porteuse);

	//initialeCreationCarre(&(*initiale).enveloppe);
	//initialeCreationHarmonique(&(*initiale).porteuse);

	return 0;

}

int initialeCreationPartie(partieT * partie) {
	switch ((*partie).complexe)
		{
		case -1:
			initialeCreationUniforme(partie);break;
		case 0:
			initialeCreationHarmonique(partie);break;
		case 1:
			initialeCreationHarmonique(partie);break;
		default:
			;
		}

	switch ((*partie).periodique)
		{
		case -1:
			initialeCreationUniforme(partie);break;
		case 0:
			initialeCreationUniforme(partie);break;
		case 1:
			initialeCreationCarre(partie);break;
		default:
			;
		}
	// Initialisation de l'enveloppe

//	initialeCreationCarre(partie);
	//partieCreationEnveloppeUniforme(partie);

	return 0;
}

/*------------------------  CHANGEMENT DES PARAMÈTRES  -------------------------*/

int initialeChangeComplexe(initialeT * initiale, int mode){

	switch (mode)
		{
		case 0:
			(*initiale).porteuse.complexe = 0;break;
		case 1:
			(*initiale).porteuse.complexe = 1;break;
		default:
			;
		}
	//printf("(*partie).complexe = %i\n", (*partie).complexe);

	return 0;
	}

//////////////////////////////////////////////////////////////////////////

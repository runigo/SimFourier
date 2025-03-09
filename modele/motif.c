/*
Copyright mars 2025, Stephan Runigo
runigo@free.fr
SimFourier 1.2.2 Transformation de Fourier
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

#include "motif.h"

	//		INITIALISATION

	//		CHANGEMENT DES PARAMÈTRES
int motifChangeA(motifT * motif, int delta);
int motifChangeB(motifT * motif, int delta);
int motifChangeForme(motifT * motif, int forme);
int motifChangeSymetrie(motifT * motif, int delta);
int motifRegleA(motifT * motif, int pourMille);
int motifRegleB(motifT * motif, int pourMille);
int motifRegleForme(motifT * motif, int forme);
int motifRegleSymetrie(motifT * motif, int pourMille);

	//		CALCUL DU MOTIF
int motifCalculParametres(motifT * motif, int periode);

int motifCalcul(motifT * motif);
int motifCalculUniforme(motifT * motif);
int motifCalculHarmonique(motifT * motif);
int motifCalculCarre(motifT * motif);
int motifCalculTriangle(motifT * motif);

	//		JAUGE ET NORMALISATION
int motifJaugeZero(motifT * motif);


/*------------------------  INITIALISATION  -------------------------*/

int motifInitialisation(motifT * motif, int nombre) {

		fonctionInitialise(&(*motif).fonction, nombre);	// Fonction motif

		(*motif).a=10;			//	Longueur horizontale (montée ou positif)
		(*motif).b=20;			//	Longueur horizontale (descente ou négatif)

		(*motif).A = 5.3;			//	Amplitude
		(*motif).B = 0.0;			//	Décalage verticale
		//(*motif).sym = (float)(*motif).a / (float)(*motif).b;	//	facteur de symétrie (a/b)

		(*motif).forme = 3;			//	0 : harmonique, 1 : carrée, 2 : triangle,
								//	3 : gaussienne, 4 : Lorentzienne

		motifCalculParametres(motif, (*motif).a + (*motif).b);
		motifCalculTriangle(motif);
	//	motifCalculPosition(motif);

	return 0;
}

/*--------------------  CALCUL DU MOTIF  ---------------------*/

int motifCalculMotif(motifT * motif, int periode) {

		// Calcul des paramètres
	motifCalculParametres(motif, periode);

		// Calcul du motif
	switch ((*motif).forme)
		{
		case 0:
			motifCalculUniforme(motif);break;
		case 1:
			motifCalculUniforme(motif);break;
		case 2:
			motifCalculCarre(motif);break;
		case 3:
			motifCalculTriangle(motif);break;
		default:
			;
		}
	return 0;
}

int motifCalculParametres(motifT * motif, int periode)
	{
			// Calcul des paramètres

	(*motif).b = periode-(*motif).a;
	if((*motif).b < 0)
		{
		fprintf(stderr, "ERREUR motifCalculParametres, disymétrie maximale atteinte. \n");
		(*motif).b = 0;
		}
	return 0;
}

int motifCalculUniforme(motifT * motif) {

	printf("Enveloppe uniforme \n");
	
	int i;
	int nombre=(*motif).a + (*motif).b;

	for(i=0;i<nombre;i++)
		{
		(*motif).fonction.reel[i] = (*motif).A;
		(*motif).fonction.imag[i] = (*motif).A;
		}

	return 0;
}

int motifCalculCarre(motifT * motif) {

	printf("Enveloppe rectangulaire \n");

	int i;
	int periode = (*motif).a +(*motif).b;

	for(i=0;i<(*motif).a;i++)
		{
		(*motif).fonction.reel[i] = (*motif).A;
		(*motif).fonction.imag[i] = (*motif).A;
		}

	for(i=(*motif).a;i<periode;i++)
		{
		(*motif).fonction.reel[i] = -(*motif).A;
		(*motif).fonction.imag[i] = -(*motif).A;
		}
	return 0;
}

int motifCalculTriangle(motifT * motif) {

	printf("Enveloppe dent de scie \n");
	
	int i;
	int periode = (*motif).a +(*motif).b;
	float alpha;
	float beta;

	if((*motif).a == 0)
		{
		alpha = 2*(*motif).A;
		printf(" Erreur dans motifCalculTriangle, (*motif).a == 0 \n");
		}
	else
		{
		alpha =  (2.0*(*motif).A)/(*motif).a;
		}

	for(i=0;i<(*motif).a;i++)
		{
		(*motif).fonction.reel[i] = i*alpha - (*motif).A;
		(*motif).fonction.imag[i] = (*motif).fonction.reel[i];
		}

	if((*motif).b == 0)
		{
		alpha = 2 * (*motif).A * (float)(*motif).a;
		beta = (*motif).A * (1 - 2 * (float)(*motif).a);
		printf(" Erreur dans motifCalculTriangle, (*motif).b == 0 \n");
		}
	else
		{
		alpha =  2 * (*motif).A * (float)(*motif).a / (*motif).b;
		beta = (*motif).A * (1 - 2 * (float)(*motif).a / (*motif).b) ;
		}


	for(i=(*motif).a;i<periode;i++)
		{
		(*motif).fonction.reel[i] = i*alpha - beta;
		(*motif).fonction.imag[i] = (*motif).fonction.reel[i];
		}

	return 0;
}

/*------------------------  CHANGEMENT DES PARAMÈTRES  -------------------------*/
int motifChangeParametre(motifT * motif, int parametre, int variation){

	switch (parametre)
		{
		case 0:
			motifChangeForme(motif, variation);break;
		case 1:
			motifChangeSymetrie(motif, variation);break;
		case 2:
			motifChangeA(motif, variation);break;
		case 3:
			motifChangeB(motif, variation);break;
		default:
			;
		}
	return 0;
}

int motifRegleParametre(motifT * motif, int parametre, int pourMille){

	switch (parametre)
		{
		case 0:
			motifRegleForme(motif, pourMille);break;
		case 1:
			motifRegleSymetrie(motif, pourMille);break;
		case 2:
			motifRegleA(motif, pourMille);break;
		case 3:
			motifRegleB(motif, pourMille);break;
		//case 4:
			//motifChangeC(motif, variation);break;
		default:
			;
		}
	return 0;
}

int motifChangeForme(motifT * motif, int forme)
	{
			//	Règle la forme motif

	if(forme>-1 && forme<4)
		{
		(*motif).forme = forme;			//	0 : constante, 1 : harmonique, 2 : carrée, 3 : triangle,
		}
	else
		{
		printf("Erreur dans motifChangeForme ");
		(*motif).forme = 0;	
		}

	printf("Forme  = %i\n", (*motif).forme);

	return 0;
}

int motifChangeSymetrie(motifT * motif, int delta)
	{
		// Change la symétrie du motif

	int a = (*motif).a;
	int periode = (*motif).a + (*motif).b;
	switch (delta)
		{
		case -1:
			a = a - 1;break;
		case 0:
			a = 0;break;
		case 1:
			a = a + 1;break;
		default:
			;
		}
	if(a <= periode)
		{
		if(a > -1)
			{
			(*motif).a = a;
			(*motif).b = periode - a;
			}
		else
			{
			printf("a minimum atteint. ");
			(*motif).a = 0;
			(*motif).b = periode;
			}
		}
	else
		{
		printf("a maximum atteint. ");
		(*motif).a = periode;
		(*motif).b = 0;
		}

	printf("a  = %i, b  = %i\n", (*motif).a, (*motif).b);

	return 0;
	}

int motifChangeA(motifT * motif, int delta) {

	// Change l'amplitude du motif

	float amplitude = (*motif).A + delta;

	if(amplitude < AMPLITUDE_MIN)
		{
		(*motif).A = AMPLITUDE_MIN;
		printf("Amplitude minimale atteinte. ");
		}
	else
		{
		if(amplitude > AMPLITUDE_MAX)
			{
			(*motif).A = AMPLITUDE_MAX;
			printf("Amplitude maximale atteinte. ");
			}
		else
			{
			(*motif).A = amplitude;
			}
		}
	printf("Amplitude motif = %f\n", (*motif).A);

	return 0;
	}

int motifChangeB(motifT * motif, int delta) {

	// Change le décalage verticale du motif

	float decalage = (*motif).B + delta;

	if(decalage < AMPLITUDE_MIN)
		{
		(*motif).B = AMPLITUDE_MIN;
		printf("Décalage minimale atteinte. ");
		}
	else
		{
		if(decalage > AMPLITUDE_MAX)
			{
			(*motif).B = AMPLITUDE_MAX;
			printf("Décalage maximale atteinte. ");
			}
		else
			{
			(*motif).B = decalage;
			}
		}
	printf("Décalage verticale = %f\n", (*motif).B);

	return 0;
	}
////////////////	Réglage
int motifRegleForme(motifT * motif, int forme){

	// Règle la forme du motif

	if(forme>-1 && forme<6)
		{
		(*motif).forme = forme;			//	0 : constante, 1 : harmonique, 2 : carrée, 3 : triangle,
							//	4 : gaussienne, 5 : lorentzienne
		}
	else
		{
		printf("Erreur dans motifRegleForme ");
		}

	printf("Forme  = %i\n", (*motif).forme);

	return 0;
}

int motifRegleSymetrie(motifT * motif, int pourMille) {

	// Règle l'asymétrie du motif

	int periode = (*motif).a + (*motif).b; 
	int a = (periode * pourMille) / 1000;

	if(a <= periode)
		{
		if(a > -1)
			{
			(*motif).a = a;
			(*motif).b = periode - a;
			}
		else
			{
			printf("Symétrie minimum atteint. ");
			(*motif).a = 0;
			(*motif).b = periode;
			}
		}
	else
		{
		printf("Symétrie maximum atteint. ");
		(*motif).a = periode;
		(*motif).b = 0;
		}

	printf("a / b = %f \n", ((double)(*motif).a) / (*motif).b);

	return 0;
	}

int motifRegleA(motifT * motif, int delta) {

	// Règle l'amplitude du motif

	float amplitude = ((*motif).A * delta)/100;

	if(amplitude < AMPLITUDE_MIN)
		{
		(*motif).A = AMPLITUDE_MIN;
		printf("Amplitude minimale atteinte. ");
		}
	else
		{
		if(amplitude > AMPLITUDE_MAX)
			{
			(*motif).A = AMPLITUDE_MAX;
			printf("Amplitude maximale atteinte. ");
			}
		else
			{
			(*motif).A = amplitude;
			}
		}
	printf("Amplitude motif = %f\n", (*motif).A);

	return 0;
	}

int motifRegleB(motifT * motif, int delta) {

	// Règle le décalage verticale du motif

	float decalage = ((*motif).A * delta)/100;

	if(decalage < AMPLITUDE_MIN)
		{
		(*motif).A = AMPLITUDE_MIN;
		printf("Décalage minimale atteinte. ");
		}
	else
		{
		if(decalage > AMPLITUDE_MAX)
			{
			(*motif).A = AMPLITUDE_MAX;
			printf("Décalage maximale atteinte. ");
			}
		else
			{
			(*motif).A = decalage;
			}
		}
	printf("Décalage verticale = %f\n", (*motif).A);

	return 0;
	}

//////////////////////////////////////////////////////////////////////////

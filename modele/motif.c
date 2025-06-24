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

#include "motif.h"

	//		INITIALISATION

	//		CHANGEMENT DES PARAMÈTRES
int motifVariationAmplitude(motifT * motif, int delta);
int motifVariationDecalage(motifT * motif, int delta);
int motifVariationForme(motifT * motif, int forme);
int motifVariationSymetrie(motifT * motif, int delta);
int motifRegleAmplitude(motifT * motif, int pourMille);
int motifRegleDecalage(motifT * motif, int pourMille);
int motifRegleForme(motifT * motif, int forme);
int motifRegleSymetrie(motifT * motif, int pourMille);

	//		CALCUL DU MOTIF
int motifCalcul(motifT * motif, int periode);
int motifCalculUniforme(motifT * motif, int periode);
int motifCalculHarmonique(motifT * motif, int periode);
int motifCalculCarre(motifT * motif, int periode);
int motifCalculTriangle(motifT * motif, int periode);


/*------------------------  INITIALISATION  -------------------------*/

int motifInitialisation(motifT * motif, int nombre) {

		fonctionInitialise(&(*motif).fonction, nombre);	// Fonction motif

		(*motif).symetrie = 0.5;	//	facteur de symétrie

		(*motif).amplitude = 5.3;			//	Amplitude
		(*motif).decalage = 0.0;			//	Décalage verticale
		//(*motif).sym = (float)(*motif).a / (float)(*motif).b;	//	facteur de symétrie (a/b)

		(*motif).forme = 3;			//	0 : constante, 1 : harmonique, 2 : carrée, 3 : triangle.

	//	motifCalculPosition(motif);

	return 0;
}

/*--------------------  CALCUL DU MOTIF  ---------------------*/

int motifCalculMotif(motifT * motif, int periode) {

		// Calcul du motif
	switch ((*motif).forme)
		{
		case 0:
			motifCalculUniforme(motif, periode);break;
		case 1:
			motifCalculUniforme(motif, periode);break;
		case 2:
			motifCalculCarre(motif, periode);break;
		case 3:
			motifCalculTriangle(motif, periode);break;
		default:
			;
		}
	return 0;
}

int motifCalculUniforme(motifT * motif, int periode) {

	printf("Enveloppe uniforme \n");
	(void)periode;
	int i;

	for(i=0;i<(*motif).fonction.nombre;i++)
		{
		(*motif).fonction.reel[i] = (*motif).amplitude;
		(*motif).fonction.imag[i] = (*motif).amplitude;
		}

	return 0;
}

int motifCalculCarre(motifT * motif, int periode) {

	printf("Enveloppe rectangulaire \n");

	int i;
	int a = periode * (*motif).symetrie;

	for(i=0;i<a;i++)
		{
		(*motif).fonction.reel[i] = (*motif).decalage + (*motif).amplitude;
		(*motif).fonction.imag[i] = (*motif).decalage + (*motif).amplitude;
		}

	for(i=a;i<periode;i++)
		{
		(*motif).fonction.reel[i] = (*motif).decalage -(*motif).amplitude;
		(*motif).fonction.imag[i] = (*motif).decalage -(*motif).amplitude;
		}
	return 0;
}

int motifCalculTriangle(motifT * motif, int periode) {

	printf("Enveloppe dent de scie \n");
	
	int i;
	int a = (int)(periode * (*motif).symetrie);
	int b = periode - a;
	float alpha;
	float beta;

	if(periode < 4 || periode > (*motif).fonction.nombre)
		{
		fprintf(stderr, "ERREUR : motifCalculTriangle, periode = %d\n\n", periode);
		motifAffiche(motif);
		//exit(0);
		}
	if((*motif).symetrie < 0 || (*motif).symetrie > 1)
		{
		fprintf(stderr, "ERREUR : motifCalculTriangle, symetrie = %f\n\n", (*motif).symetrie);
		motifAffiche(motif);
		exit(0);
		}

	if(a == 0)
		{
		alpha = -(2.0*(*motif).amplitude)/periode;
		beta = (*motif).amplitude;
		for(i=0;i<periode;i++)
			{
			(*motif).fonction.reel[i] = (*motif).decalage + i*alpha + beta;
			}
		}
	else
		{
		if(b == 0)
			{
			alpha = (2.0*(*motif).amplitude)/periode;
			beta = -(*motif).amplitude;
			for(i=0;i<periode;i++)
				{
				(*motif).fonction.reel[i] = (*motif).decalage + i*alpha + beta;
				}
			}
		else	//	a et b sont différent de 0
			{
			alpha = (*motif).amplitude / a;
			for(i=0;i<a;i++)
				{
				(*motif).fonction.reel[i] = (*motif).decalage + i * alpha;
				}
			alpha = (*motif).amplitude / (a-periode);
			beta = ((*motif).amplitude * periode) / b;
			for(i=a;i<periode;i++)
				{
				(*motif).fonction.reel[i] = (*motif).decalage + i * alpha + beta;
				}
			}
		}

	return 0;
}


/*---------------------     CHANGEMENT DES PARAMÈTRES     ----------------------*/

int motifVariationParametre(motifT * motif, int parametre, int variation){

	switch (parametre)
		{
		case 0:
			motifVariationForme(motif, variation);break;
		case 1:
			motifVariationSymetrie(motif, variation);break;
		case 2:
			motifVariationAmplitude(motif, variation);break;
		case 3:
			motifVariationDecalage(motif, variation);break;
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
			motifRegleAmplitude(motif, pourMille);break;
		case 3:
			motifRegleDecalage(motif, pourMille);break;
		default:
			;
		}
	return 0;
}

int motifVariationForme(motifT * motif, int forme)
	{
			//	Règle la forme du motif

	if(forme>-1 && forme<4)
		{
		(*motif).forme = forme;			//	0 : constante, 1 : harmonique, 2 : carrée, 3 : triangle,
		}
	else
		{
		printf("Erreur dans motifVariationForme \n");
		(*motif).forme = 0;	
		}

	return 0;
}

int motifVariationSymetrie(motifT * motif, int delta)
	{
		// Fait varier la symétrie du motif

	double symetrie = (*motif).symetrie  + (double)delta / 100;

	if(symetrie < 0)
		{
		(*motif).symetrie = 0;
		printf("Symétrie minimale atteinte, symétrie  = %f\n", (*motif).symetrie);
		return -1;
		}

	if(symetrie > 1.0)
		{
		(*motif).symetrie = 1.0;
		printf("Symétrie maximale atteinte, symétrie  = %f\n", (*motif).symetrie);
		return 1;
		}

	(*motif).symetrie = symetrie;
	printf("Symétrie  = %f\n", (*motif).symetrie);

	return 0;
	}

int motifVariationAmplitude(motifT * motif, int delta) {

	// Fait varier l'amplitude du motif

	double amplitude = (*motif).amplitude + (double)delta / 10;

	if(amplitude < AMPLITUDE_MIN)
		{
		(*motif).amplitude = AMPLITUDE_MIN;
		printf("Amplitude minimale atteinte, symétrie  = %f\n", (*motif).amplitude);
		return -1;
		}

	if(amplitude > AMPLITUDE_MAX)
		{
		(*motif).amplitude = AMPLITUDE_MAX;
		printf("Amplitude maximale atteinte, symétrie  = %f\n", (*motif).amplitude);
		return 1;
		}

	(*motif).amplitude = amplitude;
	printf("Amplitude motif = %f\n", (*motif).amplitude);

	return 0;
	}

int motifVariationDecalage(motifT * motif, int delta) {

	// Fait varier le décalage verticale du motif

	float decalage = (*motif).decalage + (double)delta / 10;

	if(decalage < AMPLITUDE_MIN)
		{
		(*motif).decalage = AMPLITUDE_MIN;
		printf("Décalage minimale atteinte, decalage  = %f\n", (*motif).decalage);
		return -1;
		}

	if(decalage > AMPLITUDE_MAX)
		{
		(*motif).decalage = AMPLITUDE_MAX;
		printf("Décalage maximale atteinte, decalage  = %f\n", (*motif).decalage);
		return 1;
		}

	(*motif).decalage = decalage;
	printf("Amplitude motif = %f\n", (*motif).decalage);

	return 0;
	}
////////////////	Réglage
int motifRegleForme(motifT * motif, int forme){

	// Règle la forme du motif

	if(forme>-1 && forme<4)
		{
		(*motif).forme = forme;	//	0 : constante, 1 : harmonique, 2 : carrée, 3 : triangle.
		}
	else
		{
		printf("ERREUR dans motifRegleForme ");
		}

	printf("Forme  = %i\n", (*motif).forme);

	return 0;
}

int motifRegleSymetrie(motifT * motif, int pourMille) {

	// Règle l'asymétrie du motif
		//printf("motifRegleSymetrie, entrée, pourMille = %f \n", pourMille);

	double symetrie = (double)pourMille / 1000;

	if(symetrie < 0)
		{
		(*motif).symetrie = 0;
		printf("Symétrie minimale atteinte, symétrie  = %f\n", (*motif).symetrie);
		return -1;
		}

	if(symetrie > 1.0)
		{
		(*motif).symetrie = 1.0;
		printf("Symétrie maximale atteinte, symétrie  = %f\n", (*motif).symetrie);
		return 1;
		}

	(*motif).symetrie = symetrie;
	printf("Symétrie = %f\n", (*motif).symetrie);
		printf("motifRegleSymetrie, sortie \n");

	return 0;
	}

int motifRegleAmplitude(motifT * motif, int pourMille) {

	// Règle l'amplitude du motif

	float amplitude = AMPLITUDE_MIN + ((AMPLITUDE_MAX * pourMille)/1000);

	if(amplitude < AMPLITUDE_MIN)
		{
		(*motif).amplitude = AMPLITUDE_MIN;
		printf("Amplitude minimale atteinte. ");
		}
	else
		{
		if(amplitude > AMPLITUDE_MAX)
			{
			(*motif).amplitude = AMPLITUDE_MAX;
			printf("Amplitude maximale atteinte. ");
			}
		else
			{
			(*motif).amplitude = amplitude;
			}
		}
	printf("Amplitude motif = %f\n", (*motif).amplitude);

	return 0;
	}

int motifRegleDecalage(motifT * motif, int pourMille) {

	// Règle le décalage verticale du motif

	float decalage = (AMPLITUDE_MAX * pourMille)/1000;

	if(decalage < 0)
		{
		(*motif).decalage = 0;
		printf("Décalage minimale atteint. ");
		}
	else
		{
		if(decalage > AMPLITUDE_MAX)
			{
			(*motif).decalage = AMPLITUDE_MAX;
			printf("Décalage maximale atteint. ");
			}
		else
			{
			(*motif).decalage = decalage;
			}
		}
	printf("Décalage verticale = %f\n", (*motif).decalage);

	return 0;
	}

int motifAffiche(motifT * motif)
	{
	printf("\nParamètres du motif : \n");
	printf("     forme = %d", (*motif).forme);printf("     symetrie = %f\n", (*motif).symetrie);
	printf("     amplitude = %f", (*motif).amplitude);printf("     decalage = %f\n", (*motif).decalage);
	return 0;
	}
//////////////////////////////////////////////////////////////////////////

/*
Copyright avril 2025, Stephan Runigo
runigo@free.fr
SimFourier 1.4 Transformation de Fourier
Ce logiciel est un programme informatique servant à donner une représentation
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

#include "filtre.h"

int filtreVariationFrequence(filtreT * filtre, int variation);
int filtreVariationOrdre(filtreT * filtre, int variation);
int filtreVariationDeltaF(filtreT * filtre, int variation);
int filtreVariationSymetrie(filtreT * filtre, int variation);
int filtreVariationMode(filtreT * filtre, int variation);
int filtreRegleFrequence(filtreT * filtre, int pourMille);
int filtreRegleOrdre(filtreT * filtre, int pourMille);
int filtreRegleDeltaF(filtreT * filtre, int pourMille);
int filtreRegleSymetrie(filtreT * filtre, int pourMille);
int filtreRegleMode(filtreT * filtre, int pourMille);


int filtreInitialise(filtreT * filtre, int nombre)
	{
			//	Initialisation du filtre

		//	Nombre de point
	(*filtre).nombre = nombre;

	(*filtre).frequence = nombre / 4;
	(*filtre).ordre = nombre / 16;
	(*filtre).deltaF = nombre / 16;	//	Ecart de fréquence (passe bande)
	(*filtre).symetrie = 0;
	(*filtre).mode = 0;

	filtreUniforme(filtre);

	return 0;
	}

int filtreUniforme(filtreT * filtre)
	{
			//	Initialise un filtre uniforme
	int i;
	for(i=0;i<NOMBRE_MAX;i++)
		{
		(*filtre).gain[i] = 1.0;
		}
	return 0;
	}

int filtrePasseBas(filtreT * filtre)
	{
			//	Crée un filtre passe bas
	int i;
	int max = (*filtre).nombre - 1;
	int frequence = (*filtre).frequence;
	for(i=0;i<frequence;i++)
		{
		(*filtre).gain[i]=1.0;
		(*filtre).gain[max-i]=1.0;
		}
	return 0;
	}

int filtrePasseHaut(filtreT * filtre)
	{
			//	Crée un filtre passe haut
	int i;
	int frequence = (*filtre).frequence;
	int max = (*filtre).nombre - 1 - frequence;
	for(i=frequence;i<max;i++)
		{
		(*filtre).gain[i]=1.0;
		(*filtre).gain[max-i]=1.0;
		}
	return 0;
	}


int filtrePasseBande(filtreT * filtre)
	{
			//	Crée un filtre passe bande
	int i;
	int frequence = (*filtre).frequence;
	int max = (*filtre).nombre - 1 - frequence;
	for(i=frequence;i<max;i++)
		{
		(*filtre).gain[i]=1.0;
		(*filtre).gain[max-i]=1.0;
		}
	return 0;
	}

		///////////////      CHANGEMENT D'UN PARAMETRE       /////////////////////////////

int filtreChangeParametre(filtreT * filtre, int parametre, int variation, int pourMille)
	{
	if(variation==0)	//	Règle le paramètre à pourMille
		{
		switch (parametre)
			{
			case 1:	//	Fréquence
				filtreRegleFrequence(filtre, pourMille);break;
			case 2:	//	Ordre
				filtreRegleOrdre(filtre, pourMille);break;
			case 3:	//	Delta fréquence
				filtreRegleDeltaF(filtre, pourMille);break;
			case 4:	//	Symétrie
				filtreRegleSymetrie(filtre, pourMille);break;
			case 5:	//	Mode
				filtreRegleMode(filtre, pourMille);break;
			default:
				fprintf(stderr, "ERREUR : filtreChangeParametre");
			}
		}
	else				//	Variation du paramètre
		{
		switch (parametre)
			{
			case 1:	//	Fréquence
				filtreVariationFrequence(filtre, variation);break;
			case 2:	//	Ordre
				filtreVariationOrdre(filtre, variation);break;
			case 3:	//	Delta fréquence
				filtreVariationDeltaF(filtre, variation);break;
			case 4:	//	Symétrie
				filtreVariationSymetrie(filtre, variation);break;
			case 5:	//	Mode
				filtreVariationMode(filtre, variation);break;
			default:
				fprintf(stderr, "ERREUR : filtreChangeParametre");
			}
		}

	return 0;
	}


int filtreVariationFrequence(filtreT * filtre, int variation)
	{
	int frequence = (*filtre).frequence + variation;
	if(frequence>(*filtre).nombre)
		{
		printf("Fréquence filtre maximal atteint\n");
		}
	else
		{
		if(frequence<(*filtre).nombre)
			{
			printf("Fréquence filtre minimal atteint\n");
			}
		else
			{
			(*filtre).frequence = frequence;
			printf("Fréquence filtre = %d \n", (*filtre).frequence);
			}
		}
	return 0;
	}

int filtreVariationOrdre(filtreT * filtre, int variation)
	{
	int ordre = (*filtre).ordre + variation;
	if(ordre>(*filtre).nombre)
		{
		printf("Ordre filtre maximal atteint\n");
		}
	else
		{
		if(ordre<0)
			{
			printf("Ordre filtre minimal atteint\n");
			}
		else
			{
			(*filtre).ordre = ordre;
			printf("Ordre filtre = %d \n", (*filtre).ordre);
			}
		}
	return 0;
	}

int filtreVariationDeltaF(filtreT * filtre, int variation)
	{
	int deltaF = (*filtre).deltaF + variation;
	if(deltaF>(*filtre).nombre)
		{
		printf("Delta fréquence filtre maximal atteint\n");
		}
	else
		{
		if(deltaF<0)
			{
			printf("Delta fréquence filtre minimal atteint\n");
			}
		else
			{
			(*filtre).deltaF = deltaF;
			printf("Delta fréquence filtre = %d \n", (*filtre).deltaF);
			}
		}
	return 0;
	}

int filtreVariationSymetrie(filtreT * filtre, int variation)
	{
	(void)filtre;
	(void)variation;
	fprintf(stderr,"ERREUR : filtreVariationSymetrie");
	return 0;
	}

int filtreVariationMode(filtreT * filtre, int variation)
	{
	(void)filtre;
	(void)variation;
	fprintf(stderr,"ERREUR : filtreVariationMode");
	return 0;
	}

int filtreRegleFrequence(filtreT * filtre, int pourMille)
	{
	int frequence = pourMille * (*filtre).nombre / 1000;
	if(frequence>(*filtre).nombre)
		{
		printf("Fréquence filtre maximal atteint\n");
		}
	else
		{
		if(frequence<0)
			{
			printf("Fréquence filtre minimal atteint\n");
			}
		else
			{
			(*filtre).frequence = frequence;
			printf("Fréquence filtre = %d \n", (*filtre).frequence);
			}
		}
	return 0;
	}

int filtreRegleOrdre(filtreT * filtre, int pourMille)
	{
	int ordre = pourMille * (*filtre).nombre / 1000;
	if(ordre>(*filtre).nombre)
		{
		printf("Ordre filtre maximal atteint\n");
		}
	else
		{
		if(ordre<0)
			{
			printf("Ordre filtre minimal atteint\n");
			}
		else
			{
			(*filtre).ordre = ordre;
			printf("Ordre filtre = %d \n", (*filtre).ordre);
			}
		}
	return 0;
	}

int filtreRegleDeltaF(filtreT * filtre, int pourMille)
	{
	int deltaF = pourMille * (*filtre).nombre / 1000;
	if(deltaF>(*filtre).nombre)
		{
		printf("Delta fréquence filtre maximal atteint\n");
		}
	else
		{
		if(deltaF<0)
			{
			printf("Delta fréquence filtre minimal atteint\n");
			}
		else
			{
			(*filtre).deltaF = deltaF;
			printf("Delta fréquence filtre = %d \n", (*filtre).deltaF);
			}
		}
	return 0;
	}

int filtreRegleSymetrie(filtreT * filtre, int pourMille)
	{
	switch (pourMille)
		{
		case 1:		//	Droite
			(*filtre).symetrie = 1;break;
		case 0:		//	Symétrique
			(*filtre).symetrie = 0;break;
		case -1:	//	Gauche
			(*filtre).symetrie = -1;break;
		default:
			fprintf(stderr, "ERREUR : filtreRegleSymetrie");
		}
	return 0;
	}

int filtreRegleMode(filtreT * filtre, int pourMille)
	{
	switch (pourMille)
		{
		case 1:		//	Allumé
			(*filtre).mode = 1;break;
		case 0:		//	Éteint
			(*filtre).mode = 0;break;
		case -1:	//	Inverse
			(*filtre).mode = -1;break;
		default:
			fprintf(stderr, "ERREUR : filtreRegleMode");
		}
	return 0;
	}


int filtreAffiche(filtreT * filtre)
	{
	(void) filtre;
	return 0;
	}

int filtreTest(filtreT * filtre)
	{
	filtreAffiche(filtre);
	return 0;
	}

////////////////////////////////////////////////////////////////

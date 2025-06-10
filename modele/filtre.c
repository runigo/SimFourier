/*
Copyright juin 2025, Stephan Runigo
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

	//		ÉTABLISSEMENT D'UN FILTRE
int filtreUniforme(filtreT * filtre);
int filtrePasseBasGauche(filtreT * filtre);
int filtrePasseHautGauche(filtreT * filtre);

	//		TRANSFORMATION D'UN FILTRE
int filtreSymetrise(filtreT * filtre);
int filtreInverseHB(filtreT * filtre);
int filtreInverseGD(filtreT * filtre);

	//		CHANGEMENT D'UN PARAMETRE
int filtreChangeFrequence(filtreT * filtre, int variation, int pourMille);
int filtreChangeOrdre(filtreT * filtre, int variation, int pourMille);
int filtreChangeDeltaF(filtreT * filtre, int variation, int pourMille);
int filtreChangeSymetrie(filtreT * filtre, int variation, int pourMille);
int filtreChangeMode(filtreT * filtre, int variation, int pourMille);


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

//////////////////		ÉTABLISSEMENT D'UN FILTRE		/////////////////

int filtreUniforme(filtreT * filtre)
	{
			//	Crée un filtre uniforme
	int i;
	for(i=0;i<NOMBRE_MAX;i++)
		{
		(*filtre).gain[i] = 1.0;
		}
	return 0;
	}

int filtrePasseHautGauche(filtreT * filtre)
	{
			//	Crée un filtre passe haut à gauche
	int i;
	int frequence = (*filtre).frequence;

	if((*filtre).ordre == 0)
		{
		for(i=0;i<frequence;i++)
			{
			(*filtre).gain[i]=0.0;
			}
		for(i=frequence;i<(*filtre).nombre;i++)
			{
			(*filtre).gain[i]=1.0;
			}
		}
	else
		{
		for(i=0;i<(*filtre).nombre;i++)
			{
			(*filtre).gain[i]=0.5 + (atan((float)(i-frequence) / (*filtre).ordre))/PI;
			}
		}
	return 0;
	}
int filtrePasseBasGauche(filtreT * filtre)
	{
			//	Crée un filtre passe haut à gauche
	int i;
	int frequence = (*filtre).frequence;
	int nombre = (*filtre).nombre;
	int nS2 = nombre / 2;

	if((*filtre).ordre == 0)
		{
		for(i=0;i<frequence;i++)
			{
			(*filtre).gain[i]=1.0;
			}
		for(i=frequence;i<nS2;i++)
			{
			(*filtre).gain[i]=0.0;
			}
		for(i=nS2;i<nombre;i++)
			{
			(*filtre).gain[i]=1.0;
			}
		}
	else
		{
		for(i=(nS2-1);i>(-1);i--)
			{
			(*filtre).gain[i]=0.5 + (atan((float)(frequence-i) / (*filtre).ordre))/PI;
			}
		for(i=(nombre-1);i>(nS2-1);i--)
			{
			(*filtre).gain[i]=0.5 + (atan((float)(frequence-i) / (*filtre).ordre))/PI;
			}
		}
	return 0;
	}
/*
int filtrePasseBasGauche(filtreT * filtre)
	{
			//	Crée un filtre passe bas à gauche

	filtrePasseHautGauche(filtre);

	int i;
	int nombre = (*filtre).nombre;
	int nS2 = nombre / 2;
	int tmp[nombre];

	for(i=0;i<nombre;i++)
		{
		tmp[i]=(*filtre).gain[i];
		}

	for(i=0;i<nS2;i++)
		{
		//(*filtre).gain[i] = tmp[nS2 - 1 - i];
		(*filtre).gain[nS2 + i] = tmp[nombre - 1 - i];
		}

	(void)tmp;
	return 0;
	}
*/
int filtrePasseBas(filtreT * filtre)
	{
			//	Crée un filtre passe bas

	if((*filtre).mode==0)
		{
		filtreUniforme(filtre);	//	Filtre inactif
		}
	else
		{
		filtrePasseBasGauche(filtre);	//	Passe bas gauche
		if((*filtre).symetrie==0)
			{
			filtreSymetrise(filtre);	//	Symétrique
			}
		else
			{
			if((*filtre).symetrie==1)
				{
				filtreInverseGD(filtre);	//	Droite
				}
			}
		if((*filtre).mode<0)
			{
			filtreInverseHB(filtre);	//	Passant -> coupant
			}
		}
	return 0;
	}

int filtrePasseHaut(filtreT * filtre)
	{
			//	Crée un filtre passe haut

	if((*filtre).mode==0)
		{
		filtreUniforme(filtre);	//	Filtre inactif
		}
	else
		{
		filtrePasseHautGauche(filtre);	//	Passe bas gauche
		if((*filtre).symetrie==0)
			{
			filtreSymetrise(filtre);	//	Symétrique
			}
		else
			{
			if((*filtre).symetrie==1)
				{
				filtreInverseGD(filtre);	//	Droite
				}
			}
		if((*filtre).mode<0)
			{
			filtreInverseHB(filtre);	//	Passant -> coupant
			}
		}

	return 0;
	}


int filtrePasseBande(filtreT * filtre)
	{
			//	Crée un filtre passe bande
	//int i;
	//int frequence = (*filtre).frequence;
	//int max = (*filtre).nombre - 1 - frequence;
	//if((*filtre).mode==0)
		{filtreUniforme(filtre);}
	return 0;
	}

		///////////////      TRANSFORMATION D'UN FILTRE       /////////////////////////////

int filtreSymetrise(filtreT * filtre)
	{
		//		Transforme un filtre gauche en un filtre symétrique
	int i;
	for(i=0;i<(*filtre).nombre/2;i++)
		{
		(*filtre).gain[(*filtre).nombre-1-i]=(*filtre).gain[i];
		}
	return 0;
	}

int filtreInverseHB(filtreT * filtre)
	{
		//		Transforme un filtre passant en filtre coupant
	int i;
	for(i=0;i<(*filtre).nombre;i++)
		{
		(*filtre).gain[i]=1.0-(*filtre).gain[i];
		}
	return 0;
	}

int filtreInverseGD(filtreT * filtre)
	{
		//		Transforme un filtre gauche en filtre droite
	int i;
	float tmp[(*filtre).nombre];
	for(i=0;i<(*filtre).nombre;i++)
		{
		tmp[i]=(*filtre).gain[i];
		}
	for(i=0;i<(*filtre).nombre;i++)
		{
		(*filtre).gain[i]=tmp[(*filtre).nombre-1-i];
		}
	return 0;
	}


		///////////////      CHANGEMENT D'UN PARAMETRE       /////////////////////////////

int filtreChangeParametre(filtreT * filtre, int parametre, int variation, int pourMille)
	{
	switch (parametre)
		{
		case 1:	//	Fréquence
			filtreChangeFrequence(filtre, variation, pourMille);break;
		case 2:	//	Ordre
			filtreChangeOrdre(filtre, variation, pourMille);break;
		case 3:	//	Delta fréquence
			filtreChangeDeltaF(filtre, variation, pourMille);break;
		case 4:	//	Symétrie
			filtreChangeSymetrie(filtre, variation, pourMille);break;
		case 5:	//	Mode
			filtreChangeMode(filtre, variation, pourMille);break;
		default:
			fprintf(stderr, "ERREUR : filtreChangeParametre");
		}

	return 0;
	}


int filtreChangeFrequence(filtreT * filtre, int variation, int pourMille)
	{
	int frequence = (*filtre).frequence + variation;
	
	if(variation==0)	//	Règle le paramètre à pourMille
		{
		frequence = pourMille * (*filtre).nombre / 2000 ;
		}

	if(frequence>((*filtre).nombre/2))
		{
		printf("Fréquence filtre maximal atteint. ");
		(*filtre).frequence = (*filtre).nombre/2;
		}
	else
		{
		if(frequence<1)
			{
			printf("Fréquence filtre minimal atteint. ");
			(*filtre).frequence = 1;
			}
		else
			{
			(*filtre).frequence = frequence;
			}
		}
	printf("Fréquence filtre = %d \n", (*filtre).frequence);
	return 0;
	}

int filtreChangeOrdre(filtreT * filtre, int variation, int pourMille)
	{
	int ordre = (*filtre).ordre + variation;

	if(variation==0)	//	Règle le paramètre à pourMille
		{
		ordre = pourMille * (*filtre).nombre / ORDRE_RATIO / 1000 ;
		}

	if(ordre > ((*filtre).nombre / ORDRE_RATIO))
		{
		printf("Ordre filtre maximal atteint. ");
		(*filtre).ordre = (*filtre).nombre / ORDRE_RATIO;
		}
	else
		{
		if(ordre<0)
			{
			printf("Ordre filtre minimal atteint. ");
			(*filtre).ordre = 0;
			}
		else
			{
			(*filtre).ordre = ordre;
			}
		}
	printf("Ordre filtre = %d \n", (*filtre).ordre);
	return 0;
	}

int filtreChangeDeltaF(filtreT * filtre, int variation, int pourMille)
	{
	int deltaF = (*filtre).deltaF + variation;

	if(variation==0)	//	Règle le paramètre à pourMille
		{
		deltaF = pourMille * (*filtre).nombre / DELTA_F_RATIO / 1000 ;
		}

	if(deltaF>(*filtre).nombre / DELTA_F_RATIO)
		{
		printf("Delta fréquence filtre maximal atteint. ");
		(*filtre).deltaF = (*filtre).nombre / DELTA_F_RATIO;
		}
	else
		{
		if(deltaF<1)
			{
			printf("Delta fréquence filtre minimal atteint. ");
			(*filtre).deltaF = 1;
			}
		else
			{
			(*filtre).deltaF = deltaF;
			}
		}
	printf("Delta fréquence filtre = %d \n", (*filtre).deltaF);
	return 0;
	}

int filtreChangeSymetrie(filtreT * filtre, int variation, int pourMille)
	{
	int symetrie = (*filtre).symetrie + variation;

	if(variation == 0)
		{
		symetrie = pourMille;
		}

	switch (symetrie)
		{
		case 1:		//	Droite
			(*filtre).symetrie = 1;
	printf("Symetrie filtre = droite\n");break;
		case 0:		//	Symétrique
			(*filtre).symetrie = 0;
	printf("Symetrie filtre = symétrique\n");break;
		case -1:	//	Gauche
			(*filtre).symetrie = -1;
	printf("Symetrie filtre = gauche\n");break;
		default:
			fprintf(stderr, "ERREUR : filtreChangeSymetrie\n");
		}
	return 0;
	}

int filtreChangeMode(filtreT * filtre, int variation, int pourMille)
	{
	int mode = (*filtre).mode + variation;

	if(variation == 0)
		{
		mode = pourMille;
		}

	switch (mode)
		{
		case 1:		//	Allumé
			(*filtre).mode = 1;
			printf("Mode filtre = actif\n");break;
		case 0:		//	Éteint
			(*filtre).mode = 0;
			printf("Mode filtre = inactif\n");break;
		case -1:	//	Inverse
			(*filtre).mode = -1;
			printf("Mode filtre = inverse\n");break;
		default:
			fprintf(stderr, "ERREUR : filtreChangeMode");
		}
	return 0;
	}

//////////		AFFICHE		////////////

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

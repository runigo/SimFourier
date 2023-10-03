/*
Copyright mars 2019, Stephan Runigo
runigo@free.fr
SiCF 2.0  simulateur de corde vibrante et spectre
Ce logiciel est un programme informatique servant à simuler l'équation
d'une corde vibrante, à calculer sa transformée de fourier, et à donner
une représentation graphique de ces fonctions.
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
/*
L'algorithme de fft écrit ci-dessous s'est librement inspiré de
http://www.ai.univ-paris8.fr/~audibert/tra/FFT.pdf
*/
#include "fourier.h"

void polynome(fonctionT * test, int n);
void fourierEvaluer(fonctionT * trF, fonctionT * echang, fonctionT * racineDe1, int k, int n);

int fourierModuleMax1(fourierT * fourier);
int fourierFiltreCoupe0(fourierT * fourier);

int fourierInitialise(fourierT * fourier, int nombre)
	{
	fonctionInitialise(&(*fourier).racineNDe1, nombre);
	fonctionInitialise(&(*fourier).racineNs2De1, nombre/2);
	fonctionInitialise(&(*fourier).echange, nombre);
	fonctionInitialise(&(*fourier).spectre, nombre);
	fonctionInitialise(&(*fourier).gauche, nombre/2);
	fonctionInitialise(&(*fourier).droite, nombre/2);

	fonctionRacinesNemesDe1(&(*fourier).racineNDe1, nombre);
	fonctionRacinesNemesDe1(&(*fourier).racineNs2De1, nombre/2);

	return 0;
	}

int fourierCalcule(fourierT * fourier)
	{
	fourierEvaluer(&(*fourier).spectre, &(*fourier).echange, &(*fourier).racineNDe1, 0, (*fourier).spectre.nombre);
	fourierEvaluer(&(*fourier).gauche, &(*fourier).echange, &(*fourier).racineNs2De1, 0, (*fourier).gauche.nombre);
	fourierEvaluer(&(*fourier).droite, &(*fourier).echange, &(*fourier).racineNs2De1, 0, (*fourier).droite.nombre);

	fourierFiltreCoupe0(fourier);

	fourierModuleMax1(fourier);

	return 0;
	}

int fourierModuleMax1(fourierT * fourier)
	{
	float max = fonctionModuleMax1(&(*fourier).spectre);
	fonctionModuleDivise(&(*fourier).gauche, max);
	fonctionModuleDivise(&(*fourier).droite, max);

	return 0;
	}

int fourierFiltreCoupe0(fourierT * fourier)
	{
	(*fourier).spectre.reel[0] = 0;
	(*fourier).gauche.reel[0] = 0;
	(*fourier).droite.reel[0] = 0;

	(*fourier).spectre.imag[0] = 0;
	(*fourier).gauche.imag[0] = 0;
	(*fourier).droite.imag[0] = 0;

	(*fourier).spectre.reel[(*fourier).spectre.nombre-1] = 0;
	(*fourier).gauche.reel[(*fourier).gauche.nombre-1] = 0;
	(*fourier).droite.reel[(*fourier).droite.nombre-1] = 0;

	(*fourier).spectre.imag[(*fourier).spectre.nombre-1] = 0;
	(*fourier).gauche.imag[(*fourier).gauche.nombre-1] = 0;
	(*fourier).droite.imag[(*fourier).droite.nombre-1] = 0;

	return 0;
	}


void fourierEvaluer(fonctionT * trFourier, fonctionT * echange, fonctionT * racineDe1, int k, int n)
	{
	double wPimpreel,wPimpimag;
	int nsur2,i,j,jj,expo;
	if (n==2)
		{
		(*echange).reel[0]=(*trFourier).reel[k]; (*echange).reel[1]=(*trFourier).reel[k+1]; /* test d’arrêt */
		(*trFourier).reel[k]=(*echange).reel[0]+(*echange).reel[1]; (*trFourier).reel[k+1]=(*echange).reel[0] - (*echange).reel[1];
		(*echange).imag[0]=(*trFourier).imag[k]; (*echange).imag[1]=(*trFourier).imag[k+1];
		(*trFourier).imag[k]=(*echange).imag[0]+(*echange).imag[1]; (*trFourier).imag[k+1]=(*echange).imag[0] - (*echange).imag[1];
		}
	else
		{
		nsur2=n/2;
		for(i=0;i<nsur2;i++)
			{
			j = k + 2*i;
			(*echange).reel[i]=(*trFourier).reel[j]; (*echange).reel[i+nsur2]=(*trFourier).reel[j+1]; /* P pair et P impair */
			(*echange).imag[i]=(*trFourier).imag[j]; (*echange).imag[i+nsur2]=(*trFourier).imag[j+1];
			}
		for(i=0;i<n;i++)
			{
			(*trFourier).reel[k+i]=(*echange).reel[i];
			(*trFourier).imag[k+i]=(*echange).imag[i];
			}
		fourierEvaluer(trFourier, echange, racineDe1, k, nsur2);
		fourierEvaluer(trFourier, echange, racineDe1, k+nsur2, nsur2);
		jj=(*trFourier).nombre/n;
		for(i=0;i<nsur2;i++)
			{
			expo=i*jj;
			wPimpreel= (*trFourier).reel[k+nsur2+i]*(*racineDe1).reel[expo] - (*trFourier).imag[k+nsur2+i]*(*racineDe1).imag[expo];
			wPimpimag= (*trFourier).reel[k+nsur2+i]*(*racineDe1).imag[expo] + (*trFourier).imag[k+nsur2+i]*(*racineDe1).reel[expo];
			(*echange).reel[i]=(*trFourier).reel[k+i]+wPimpreel;
			(*echange).imag[i]=(*trFourier).imag[k+i]+wPimpimag;
			(*echange).reel[i+nsur2]=(*trFourier).reel[k+i]-wPimpreel;
			(*echange).imag[i+nsur2]=(*trFourier).imag[k+i]-wPimpimag;
			}
		for(i=0;i<n;i++)
			{
			(*trFourier).reel[k+i]=(*echange).reel[i];
			(*trFourier).imag[k+i]=(*echange).imag[i];
			}
		}
	}


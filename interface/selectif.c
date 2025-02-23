/*
Copyright février 2025, Stephan Runigo
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

#include "selectif.h"

int selectifInitialiseBoutons(selectifT * selectif, int largeur, int hauteur)
	{

		 // Zone des petits boutons
	(*selectif).boutons=(int)(0.946459412781*largeur); // 1096 / 1158
		// PETITS BOUTONS SUIVANT X
	(*selectif).boutonX=(int)(0.0121*largeur); // Rayon suivant X // 14 / 1158
	(*selectif).boutonsCentre=(int)(0.9644*largeur); // 1117 // Positon X des petits boutons
		// PETITS BOUTONS SUIVANT Y
	(*selectif).boutonY=(int)(0.0168067226891*largeur); // Rayon suivant Y // 12 / 714
	(*selectif).boutonCentre[0]=(int)(0.049*hauteur); // 41	Périodique
	(*selectif).boutonCentre[1]=(int)(0.088*hauteur); // 74	Libre
	(*selectif).boutonCentre[2]=(int)(0.13099*hauteur); // 108 	Fixe // Positon Y des petits boutons
	//	PANNEAU BAS

		 // Zone du panneau
	(*selectif).bas=(int)(0.855742296919*hauteur); // 611 / 714
	(*selectif).fourier=(int)(0.427871148*hauteur); // 611 / 714

		// BOUTONS TRIANGULAIRES SUIVANT Y
	(*selectif).triangleY=(int)(0.0168067226891*hauteur); // Rayon suivant Y // 12 / 714
	(*selectif).trianglesCentre=(int)(0.928*hauteur); // 657 // Position Y des petits triangles
	(*selectif).trianglesLumiere=(int)(0.960784313725*hauteur); // 685 // Position Y des lumière
		// BOUTONS TRIANGULAIRES SUIVANT X
	(*selectif).triangleX=(int)(0.0120898100173*largeur); // Rayon suivant X // 14 / 1158
	(*selectif).triangleCentre[0]=(int)(0.047495682*largeur); // 	rotation gauche rapide
	(*selectif).triangleCentre[1]=(int)(0.076856649*largeur); // 	rotation gauche lente
	return 0;
	}

int selectifTriangles(selectifT * selectif)
	{
	int i;
	if((*selectif).trianglesCentre>(*selectif).sourisHaut && (*selectif).trianglesCentre<(*selectif).sourisBas)
		{
		for(i=0;i<TRIANGLE_COMMANDES;i++)
			{
			if((*selectif).triangleCentre[i]>(*selectif).sourisGauche && (*selectif).triangleCentre[i]<(*selectif).sourisDroite)
				return i;
			}
		}
	return -1;
	}

//////////////////////////////////////////////////////////////////

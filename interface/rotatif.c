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

#include "rotatif.h"

int rotatifInitialiseBoutons(rotatifT * rotatif, int largeur, int hauteur)
	{

	(*rotatif).fourier=(int)(0.833333333333*largeur); // 611 / 714
	//	PANNEAU DROIT

		 // Zone des boutons rotatifs
	(*rotatif).rotatifs=(int)(0.833333333333*largeur); // 965 / 1158
		// BOUTONS ROTATIFS SUIVANT X
	(*rotatif).rotatifX=(int)(0.020725388601*largeur); // 823       D-G = 24 / 1158 // Rayon suivant X
	(*rotatif).rotatifsCentre=(int)(0.892918825561*largeur); // 1034 // Positon X des boutons rotatifs
		// BOUTONS ROTATIFS SUIVANT Y
	(*rotatif).rotatifY=(int)(0.0322128851541*hauteur); // 23 / 714	Rayon suivant Y
	(*rotatif).rotatifCentre[0]=(int)(0.115*hauteur); // 97	Couplage
	(*rotatif).rotatifCentre[1]=(int)(0.2939*hauteur); // 248	Dissipation Positon Y des boutons rotatifs
	(*rotatif).rotatifCentre[2]=(int)(0.4760*hauteur); // 400	Josephson
	(*rotatif).rotatifCentre[3]=(int)(0.6517*hauteur); // 545	Amplitude
	(*rotatif).rotatifCentre[4]=(int)(0.7827*hauteur); // 654	Fréquence

		 // Zone des petits boutons
	(*rotatif).boutons=(int)(0.946459412781*largeur); // 1096 / 1158
		// PETITS BOUTONS SUIVANT X
	(*rotatif).boutonX=(int)(0.0121*largeur); // Rayon suivant X // 14 / 1158
	(*rotatif).boutonsCentre=(int)(0.9644*largeur); // 1117 // Positon X des petits boutons
		// PETITS BOUTONS SUIVANT Y
	(*rotatif).boutonY=(int)(0.0168067226891*largeur); // Rayon suivant Y // 12 / 714
	(*rotatif).boutonCentre[0]=(int)(0.049*hauteur); // 41	Périodique
	(*rotatif).boutonCentre[1]=(int)(0.088*hauteur); // 74	Libre
	(*rotatif).boutonCentre[2]=(int)(0.13099*hauteur); // 108 	Fixe // Positon Y des petits boutons
	(*rotatif).boutonCentre[3]=(int)(0.174*hauteur); // 145	Mixte
	(*rotatif).boutonCentre[4]=(int)(0.248*hauteur); // 207	Uniforme
	(*rotatif).boutonCentre[5]=(int)(0.2939*hauteur); // 245	Nulle
	(*rotatif).boutonCentre[6]=(int)(0.338*hauteur); // 283	Extrémité
	(*rotatif).boutonCentre[7]=(int)(0.41*hauteur); // 342	Marche
	(*rotatif).boutonCentre[8]=(int)(0.452*hauteur); // 376	Arrêt
	(*rotatif).boutonCentre[9]=(int)(0.4936*hauteur); // 410	Droite
	(*rotatif).boutonCentre[10]=(int)(0.53674*hauteur); // 445	Gauche
	(*rotatif).boutonCentre[11]=(int)(0.6022*hauteur); // 501	Arrêt
	(*rotatif).boutonCentre[12]=(int)(0.645*hauteur); // 537	Sinus
	(*rotatif).boutonCentre[13]=(int)(0.688*hauteur); // 572	Carré
	(*rotatif).boutonCentre[14]=(int)(0.73*hauteur); // 608	Impulsion
	(*rotatif).boutonCentre[15]=(int)(0.78115*hauteur); // 649	Fluxon
	(*rotatif).boutonCentre[16]=(int)(0.82428*hauteur); // 685	Anti F.


	//	PANNEAU BAS

		 // Zone du panneau
	(*rotatif).bas=(int)(0.855742296919*hauteur); // 611 / 714
	(*rotatif).fourier=(int)(0.427871148*hauteur); // 611 / 714

		// BOUTONS LINEAIRES SUIVANT Y
	(*rotatif).lineaireY=(int)(0.0392156862745*hauteur); // 693-636/2 =  / 714 // Rayon suivant Y
	(*rotatif).lineairesCentre=(int)(0.958181818182*hauteur); // 693+636/2 =  / 714 // Position Y des boutons linéaires
		// BOUTONS LINEAIRES SUIVANT X
	(*rotatif).lineaireX=(int)(0.0306563039724*largeur); // 332-261/2 / 1158	Rayon suivant X
	(*rotatif).lineaireCentre[0]=(int)(0.20067264574*largeur); // 261	Hauteur
	(*rotatif).lineaireCentre[1]=(int)(0.20067264574*largeur); // 332	Distance
	(*rotatif).lineaireCentre[2]=(int)(0.257847533632*largeur); // 414+596/2	Simulation < temps réèl
	(*rotatif).lineaireCentre[3]=(int)(0.406950672646*largeur); // 414+596/2	Simulation > temps réèl	

		// BOUTONS TRIANGULAIRES SUIVANT Y
	(*rotatif).triangleY=(int)(0.0168067226891*hauteur); // Rayon suivant Y // 12 / 714
	(*rotatif).trianglesCentre=(int)(0.928*hauteur); // 657 // Position Y des petits triangles
	(*rotatif).trianglesLumiere=(int)(0.960784313725*hauteur); // 685 // Position Y des lumière
		// BOUTONS TRIANGULAIRES SUIVANT X
	(*rotatif).triangleX=(int)(0.0120898100173*largeur); // Rayon suivant X // 14 / 1158
	(*rotatif).triangleCentre[0]=(int)(0.047495682*largeur); // 	rotation gauche rapide
	(*rotatif).triangleCentre[1]=(int)(0.076856649*largeur); // 	rotation gauche lente
	(*rotatif).triangleCentre[2]=(int)(0.104490501*largeur); //  	arrêt
	(*rotatif).triangleCentre[3]=(int)(0.129533679*largeur); // 	rotation droite lente
	(*rotatif).triangleCentre[4]=(int)(0.158031088*largeur); // 	rotation droite rapide

	(*rotatif).triangleCentre[5]=(int)(0.240932642*largeur); // 	simulation très ralenti
	(*rotatif).triangleCentre[6]=(int)(0.27806563*largeur); // 	simulation ralenti
	(*rotatif).triangleCentre[7]=(int)(0.311744387*largeur); // 	pause
	(*rotatif).triangleCentre[8]=(int)(0.352331606*largeur); // 	temps réèl
	(*rotatif).triangleCentre[9]=(int)(0.385146805*largeur); // 	simulation accéléré
	(*rotatif).triangleCentre[10]=(int)(0.423143351*largeur); // 	simulation trés accéléré

	(*rotatif).triangleCentre[11]=(int)(0.511226252*largeur); // 	1
	(*rotatif).triangleCentre[12]=(int)(0.540587219*largeur); // 	2
	(*rotatif).triangleCentre[13]=(int)(0.568221071*largeur); // 	3
	(*rotatif).triangleCentre[14]=(int)(0.59671848*largeur); // 	4
	(*rotatif).triangleCentre[15]=(int)(0.625215889*largeur); // 	5
	(*rotatif).triangleCentre[16]=(int)(0.654576857*largeur); // 	6

	(*rotatif).triangleCentre[17]=(int)(0.713298791*largeur); // 	1
	(*rotatif).triangleCentre[18]=(int)(0.7417962*largeur); // 	2
	(*rotatif).triangleCentre[19]=(int)(0.769430052*largeur); // 	3
	(*rotatif).triangleCentre[20]=(int)(0.799654577*largeur); // 	4

		//	Vitesse de la simulation

	(*rotatif).a=(0.277*largeur-0.23*largeur)/(DUREE_IMP-2);
	//(*rotatif).a=(((*rotatif).triangleCentre[6]-(*rotatif).triangleCentre[5])/(DUREE-2)));
	(*rotatif).b=0.23*largeur-(*rotatif).a;	//	Droite duree < DUREE
	//(*rotatif).b=((*rotatif).triangleCentre[5]-(*rotatif).a);	//	Droite duree < DUREE
	(*rotatif).A=(0.42*largeur-0.38*largeur)/(DUREE_MAX-DUREE_IMP-1);
	//(*rotatif).A=(((*rotatif).triangleCentre[10]-(*rotatif).triangleCentre[9])/(DUREE_MAX-DUREE-1));
	(*rotatif).B=0.38*largeur-(*rotatif).A*(DUREE_IMP+1);	//	Droite duree > DUREE
	//(*rotatif).B=((*rotatif).triangleCentre[9]-(*rotatif).A*(DUREE+1));	//	Droite duree > DUREE

	return 0;
	}

int rotatifRotatifs(rotatifT * rotatif)
	{
	int i;
	if((*rotatif).rotatifsCentre>(*rotatif).sourisGauche && (*rotatif).rotatifsCentre<(*rotatif).sourisDroite)
		{
		for(i=0;i<ROTATIF_COMMANDES;i++)
			{
			if((*rotatif).rotatifCentre[i]>(*rotatif).sourisHaut && (*rotatif).rotatifCentre[i]<(*rotatif).sourisBas)
				return i;
			}
		}
	return -1;
	}

int rotatifLineaires(rotatifT * rotatif)
	{
	int i;
	if((*rotatif).lineairesCentre>(*rotatif).sourisHaut && (*rotatif).lineairesCentre<(*rotatif).sourisBas)
		{
		for(i=0;i<LINEAIRE_COMMANDES;i++)
			{
			if((*rotatif).lineaireCentre[i]>(*rotatif).sourisGauche && (*rotatif).lineaireCentre[i]<(*rotatif).sourisDroite)
				return i;
			}
		}
	return -1;
	}

//////////////////////////////////////////////////////////////////

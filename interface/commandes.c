/*
Copyright février 2025, Stephan Runigo
runigo@free.fr
SimFourier 1.2.2 Transformation de Fourier
(d'après SiCP 2.5 simulateur de chaîne de pendules, fevrier 2021)
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

#include "commandes.h"

int commandesInitialiseBoutons(commandesT * commandes, int largeur, int hauteur)
	{

	(*commandes).fourier=(int)(0.833333333333*largeur); // 611 / 714
	//	PANNEAU DROIT

		 // Zone des boutons rotatifs
	(*commandes).rotatifs=(int)(0.833333333333*largeur); // 965 / 1158
		// BOUTONS ROTATIFS SUIVANT X
	(*commandes).rotatifX=(int)(0.020725388601*largeur); // 823       D-G = 24 / 1158 // Rayon suivant X
	(*commandes).rotatifsCentre=(int)(0.892918825561*largeur); // 1034 // Positon X des boutons rotatifs
		// BOUTONS ROTATIFS SUIVANT Y
	(*commandes).rotatifY=(int)(0.0322128851541*hauteur); // 23 / 714	Rayon suivant Y
	(*commandes).rotatifCentre[0]=(int)(0.115*hauteur); // 97	Couplage
	(*commandes).rotatifCentre[1]=(int)(0.2939*hauteur); // 248	Dissipation Positon Y des boutons rotatifs
	(*commandes).rotatifCentre[2]=(int)(0.4760*hauteur); // 400	Josephson
	(*commandes).rotatifCentre[3]=(int)(0.6517*hauteur); // 545	Amplitude
	(*commandes).rotatifCentre[4]=(int)(0.7827*hauteur); // 654	Fréquence

		 // Zone des petits boutons
	(*commandes).boutons=(int)(0.946459412781*largeur); // 1096 / 1158
		// PETITS BOUTONS SUIVANT X
	(*commandes).boutonX=(int)(0.0121*largeur); // Rayon suivant X // 14 / 1158
	(*commandes).boutonsCentre=(int)(0.9644*largeur); // 1117 // Positon X des petits boutons
		// PETITS BOUTONS SUIVANT Y
	(*commandes).boutonY=(int)(0.0168067226891*largeur); // Rayon suivant Y // 12 / 714
	(*commandes).boutonCentre[0]=(int)(0.049*hauteur); // 41	Périodique
	(*commandes).boutonCentre[1]=(int)(0.088*hauteur); // 74	Libre
	(*commandes).boutonCentre[2]=(int)(0.13099*hauteur); // 108 	Fixe // Positon Y des petits boutons
	(*commandes).boutonCentre[3]=(int)(0.174*hauteur); // 145	Mixte
	(*commandes).boutonCentre[4]=(int)(0.248*hauteur); // 207	Uniforme
	(*commandes).boutonCentre[5]=(int)(0.2939*hauteur); // 245	Nulle
	(*commandes).boutonCentre[6]=(int)(0.338*hauteur); // 283	Extrémité
	(*commandes).boutonCentre[7]=(int)(0.41*hauteur); // 342	Marche
	(*commandes).boutonCentre[8]=(int)(0.452*hauteur); // 376	Arrêt
	(*commandes).boutonCentre[9]=(int)(0.4936*hauteur); // 410	Droite
	(*commandes).boutonCentre[10]=(int)(0.53674*hauteur); // 445	Gauche
	(*commandes).boutonCentre[11]=(int)(0.6022*hauteur); // 501	Arrêt
	(*commandes).boutonCentre[12]=(int)(0.645*hauteur); // 537	Sinus
	(*commandes).boutonCentre[13]=(int)(0.688*hauteur); // 572	Carré
	(*commandes).boutonCentre[14]=(int)(0.73*hauteur); // 608	Impulsion
	(*commandes).boutonCentre[15]=(int)(0.78115*hauteur); // 649	Fluxon
	(*commandes).boutonCentre[16]=(int)(0.82428*hauteur); // 685	Anti F.


	//	PANNEAU BAS

		 // Zone du panneau
	(*commandes).bas=(int)(0.855742296919*hauteur); // 611 / 714
	(*commandes).fourier=(int)(0.427871148*hauteur); // 611 / 714

		// BOUTONS LINEAIRES SUIVANT Y
	(*commandes).lineaireY=(int)(0.0392156862745*hauteur); // 693-636/2 =  / 714 // Rayon suivant Y
	(*commandes).lineairesCentre=(int)(0.958181818182*hauteur); // 693+636/2 =  / 714 // Position Y des boutons linéaires
		// BOUTONS LINEAIRES SUIVANT X
	(*commandes).lineaireX=(int)(0.0306563039724*largeur); // 332-261/2 / 1158	Rayon suivant X
	(*commandes).lineaireCentre[0]=(int)(0.20067264574*largeur); // 261	Hauteur
	(*commandes).lineaireCentre[1]=(int)(0.20067264574*largeur); // 332	Distance
	(*commandes).lineaireCentre[2]=(int)(0.257847533632*largeur); // 414+596/2	Simulation < temps réèl
	(*commandes).lineaireCentre[3]=(int)(0.406950672646*largeur); // 414+596/2	Simulation > temps réèl	

		// BOUTONS TRIANGULAIRES SUIVANT Y
	(*commandes).triangleY=(int)(0.0168067226891*hauteur); // Rayon suivant Y // 12 / 714
	(*commandes).trianglesCentre=(int)(0.928*hauteur); // 657 // Position Y des petits triangles
	(*commandes).trianglesLumiere=(int)(0.960784313725*hauteur); // 685 // Position Y des lumière
		// BOUTONS TRIANGULAIRES SUIVANT X
	(*commandes).triangleX=(int)(0.0120898100173*largeur); // Rayon suivant X // 14 / 1158
	(*commandes).triangleCentre[0]=(int)(0.047495682*largeur); // 	rotation gauche rapide
	(*commandes).triangleCentre[1]=(int)(0.076856649*largeur); // 	rotation gauche lente
	(*commandes).triangleCentre[2]=(int)(0.104490501*largeur); //  	arrêt
	(*commandes).triangleCentre[3]=(int)(0.129533679*largeur); // 	rotation droite lente
	(*commandes).triangleCentre[4]=(int)(0.158031088*largeur); // 	rotation droite rapide

	(*commandes).triangleCentre[5]=(int)(0.240932642*largeur); // 	simulation très ralenti
	(*commandes).triangleCentre[6]=(int)(0.27806563*largeur); // 	simulation ralenti
	(*commandes).triangleCentre[7]=(int)(0.311744387*largeur); // 	pause
	(*commandes).triangleCentre[8]=(int)(0.352331606*largeur); // 	temps réèl
	(*commandes).triangleCentre[9]=(int)(0.385146805*largeur); // 	simulation accéléré
	(*commandes).triangleCentre[10]=(int)(0.423143351*largeur); // 	simulation trés accéléré

	(*commandes).triangleCentre[11]=(int)(0.511226252*largeur); // 	1
	(*commandes).triangleCentre[12]=(int)(0.540587219*largeur); // 	2
	(*commandes).triangleCentre[13]=(int)(0.568221071*largeur); // 	3
	(*commandes).triangleCentre[14]=(int)(0.59671848*largeur); // 	4
	(*commandes).triangleCentre[15]=(int)(0.625215889*largeur); // 	5
	(*commandes).triangleCentre[16]=(int)(0.654576857*largeur); // 	6

	(*commandes).triangleCentre[17]=(int)(0.713298791*largeur); // 	1
	(*commandes).triangleCentre[18]=(int)(0.7417962*largeur); // 	2
	(*commandes).triangleCentre[19]=(int)(0.769430052*largeur); // 	3
	(*commandes).triangleCentre[20]=(int)(0.799654577*largeur); // 	4

		//	Vitesse de la simulation

	(*commandes).a=(0.277*largeur-0.23*largeur)/(DUREE_IMP-2);
	//(*commandes).a=(((*commandes).triangleCentre[6]-(*commandes).triangleCentre[5])/(DUREE-2)));
	(*commandes).b=0.23*largeur-(*commandes).a;	//	Droite duree < DUREE
	//(*commandes).b=((*commandes).triangleCentre[5]-(*commandes).a);	//	Droite duree < DUREE
	(*commandes).A=(0.42*largeur-0.38*largeur)/(DUREE_MAX-DUREE_IMP-1);
	//(*commandes).A=(((*commandes).triangleCentre[10]-(*commandes).triangleCentre[9])/(DUREE_MAX-DUREE-1));
	(*commandes).B=0.38*largeur-(*commandes).A*(DUREE_IMP+1);	//	Droite duree > DUREE
	//(*commandes).B=((*commandes).triangleCentre[9]-(*commandes).A*(DUREE+1));	//	Droite duree > DUREE

	return 0;
	}

int commandesInitialiseSouris(commandesT * commandes, int sourisX, int sourisY)
	{
		 // Rayon des petits boutons
	int rayonX=(*commandes).boutonX;
	int rayonY=(*commandes).boutonY;

		 
	if(sourisX>(*commandes).rotatifs)
		{
		if(sourisX<(*commandes).boutons)// Zone des boutons rotatifs
			{
			rayonX=(*commandes).rotatifX;
			rayonY=(*commandes).rotatifY;
			}
		}
	else 
		{
		if(sourisY>(*commandes).bas) // Zone du bas
			{
			rayonX=(*commandes).triangleX;
			rayonY=(*commandes).triangleY;
			}
		}
		// POSITION DE LA SOURIS
	(*commandes).sourisX = sourisX; // position X de la souris
	(*commandes).sourisY = sourisY; // position Y de la souris

	(*commandes).sourisGauche = sourisX-rayonX; // position X de la souris - RayonBoutonX
	(*commandes).sourisDroite = sourisX+rayonX; // position X de la souris + RayonBoutonX
	(*commandes).sourisHaut = sourisY-rayonY; // position Y de la souris - RayonBoutonY
	(*commandes).sourisBas = sourisY+rayonY; // position Y de la souris + RayonBoutonY

	return 0;
	}

int commandeSelectifs(commandesT * commandes)
	{
			// Retourne le numéro de la commandes sélectionné
	int i;
			//	Si dans la zone suivant X
	if((*commandes).SelectifCentre>(*commandes).sourisGauche && (*commandes).SelectifCentre<(*commandes).sourisDroite)
		{
		for(i=0;i<BOUTON_COMMANDES;i++)
			{
			//	Si dans la zone suivant Y
			if((*commandes).Selectif[i]->Centre>(*commandes).sourisHaut && (*commandes).Selectif[i]->Centre<(*commandes).sourisBas)
				return i;
			}
		}
	return -1;
	}

int commandeRotatifs(commandesT * commandes)
	{
			// Retourne le numéro de la commandes sélectionné
	int i;
			//	Si dans la zone suivant X
	if((*commandes).rotatifsCentre>(*commandes).sourisGauche && (*commandes).rotatifsCentre<(*commandes).sourisDroite)
		{
		for(i=0;i<ROTATIF_COMMANDES;i++)
			{
			//	Si dans la zone suivant Y
			if((*commandes).rotatif[i]->centre>(*commandes).sourisHaut && (*commandes).rotatif[i]->centre<(*commandes).sourisBas)
				return i;
			}
		}
	return -1;
	}
/*
int commandeTriangles(commandesT * commandes)
	{
	int i;
	if((*commandes).trianglesCentre>(*commandes).sourisHaut && (*commandes).trianglesCentre<(*commandes).sourisBas)
		{
		for(i=0;i<TRIANGLE_COMMANDES;i++)
			{
			if((*commandes).triangleCentre[i]>(*commandes).sourisGauche && (*commandes).triangleCentre[i]<(*commandes).sourisDroite)
				return i;
			}
		}
	return -1;
	}

int commandeLineaires(commandesT * commandes)
	{
	int i;
	if((*commandes).lineairesCentre>(*commandes).sourisHaut && (*commandes).lineairesCentre<(*commandes).sourisBas)
		{
		for(i=0;i<LINEAIRE_COMMANDES;i++)
			{
			if((*commandes).lineaireCentre[i]>(*commandes).sourisGauche && (*commandes).lineaireCentre[i]<(*commandes).sourisDroite)
				return i;
			}
		}
	return -1;
	}
*/
//////////////////////////////////////////////////////////////////

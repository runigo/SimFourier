/*
Copyright Septembre 2023, Stephan Runigo
runigo@free.fr
(SiCP 2.5 simulateur de chaîne de pendules, fevrier 2021)
SimFourier 0.0 Transformation de Fourier
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

#include "graphique.h"

int graphiqueChangeCouleur(graphiqueT * graphique, SDL_Color couleur);
void graphiqueLigne(graphiqueT * graphique, int X, int Y, int x, int y);
void graphiqueTige(graphiqueT * graphique, int X, int Y, int x, int y, float sinT, float cosT);
//void graphiqueMasse(graphiqueT * graphique, int abs, int ord);

void graphiqueTriangleGris(graphiqueT * graphique, int X, int Y, int Ax, int Ay, int Bx, int By);
void graphiqueTriangle(graphiqueT * graphique, int X, int Y, int Ax, int Ay, int Bx, int By);
void graphiqueRectangle(graphiqueT * graphique, int Ax, int Ay, int Bx, int By, int Cx, int Cy, int Dx, int Dy);

void graphiqueMobile(graphiqueT * graphique, grapheT * graphe);

int graphiqueDestruction(graphiqueT * graphique)
	{
	SDL_DestroyRenderer((*graphique).rendu);
	return 0;
	}


int graphiqueInitialisation(graphiqueT * graphique, interfaceT * interface, int fond)
	{
	int retour = 0;
	int fenetreX;
	int fenetreY;
	SDL_GetWindowSize((*interface).fenetre, &fenetreX, &fenetreY);
	(*graphique).fenetreX=fenetreX;
	(*graphique).fenetreY=fenetreY;

		// Création du rendu
	(*graphique).rendu = SDL_CreateRenderer((*interface).fenetre, -1 , 
					SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(NULL == (*graphique).rendu)
		{
		(*graphique).rendu = SDL_CreateRenderer((*interface).fenetre, -1 , 
						SDL_RENDERER_SOFTWARE);
		if(NULL == (*graphique).rendu)
			{
			fprintf(stderr, "ERREUR interfaceInitialisation : Erreur SDL_CreateRenderer : %s \n", SDL_GetError());
			return EXIT_FAILURE;
			}
		}

	//SDL_Color orange = {255, 127, 40, 255};
	(*graphique).fond.r = fond; (*graphique).fond.g = fond; (*graphique).fond.b = fond; (*graphique).fond.a = 255;
	(*graphique).contraste.r = 255-fond; (*graphique).contraste.g = 255-fond; (*graphique).contraste.b = 255-fond; (*graphique).contraste.a = 255;
	(*graphique).jaune.r = 255; (*graphique).jaune.g = 255; (*graphique).jaune.b = 0; (*graphique).jaune.a = 255;

	(*graphique).orange.r = 255; (*graphique).orange.g = 127; (*graphique).orange.b = 40; (*graphique).orange.a = 255;
	(*graphique).orangeF.r = 198; (*graphique).orangeF.g = 8; (*graphique).orangeF.b = 0; (*graphique).orangeF.a = 255;

	(*graphique).gris.r = 127; (*graphique).gris.g = 127; (*graphique).gris.b = 127; (*graphique).gris.a = 255;
	(*graphique).grisF.r = 27; (*graphique).grisF.g = 27; (*graphique).grisF.b = 27; (*graphique).grisF.a = 255;

	(*graphique).rouge.r = 255; (*graphique).rouge.g = 0; (*graphique).rouge.b = 0; (*graphique).rouge.a = 255;
	(*graphique).bleue.r = 0; (*graphique).bleue.g = 0; (*graphique).bleue.b = 255; (*graphique).bleue.a = 255;

	//(*graphique).vert.r = 173; (*graphique).vert.g = 255; (*graphique).vert.b = 47; (*graphique).vert.a = 255;
	(*graphique).vert.r = 0; (*graphique).vert.g = 255; (*graphique).vert.b = 0; (*graphique).vert.a = 255;

	(*graphique).vertF.r = 0; (*graphique).vertF.g = 86; (*graphique).vertF.b = 27; (*graphique).vertF.a = 255;
	//(*graphique).vertF.r = 27; (*graphique).vertF.g = 79; (*graphique).vertF.b = 8;

	(*graphique).cyan.r = 127; (*graphique).cyan.g = 40; (*graphique).cyan.b = 255; (*graphique).cyan.a = 255;
	(*graphique).aubergine.r = 55; (*graphique).aubergine.g = 0; (*graphique).aubergine.b = 40; (*graphique).aubergine.a = 255;

		//(253, 63, 146) Fuschia
		//(255, 0, 255) Magenta
		//(52, 201, 36) Pomme

	//SDL_Texture *masse;

	SDL_Surface *panneau = 0;

	panneau = SDL_LoadBMP("sicp.bmp");
	if (!panneau)
		{
		fprintf(stderr,"ERREUR chargement image, sicp.bmp : %s\n",SDL_GetError());
		retour = 1;
		}
	(*graphique).SimFourier = SDL_CreateTextureFromSurface((*graphique).rendu, panneau);
	SDL_FreeSurface(panneau);
	if ((*graphique).SimFourier == 0)
		{
		fprintf(stderr,"ERREUR grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		retour = 2;
		}

	SDL_Surface *image = 0;

	image = SDL_LoadBMP("mobile.bmp");
	if (!image)
		{
		fprintf(stderr,"ERREUR chargement image, mobile.bmp : %s\n",SDL_GetError());
		retour = 3;
		}
	(*graphique).masse = SDL_CreateTextureFromSurface((*graphique).rendu, image);
	SDL_FreeSurface(image);
	if ((*graphique).masse == 0)
		{
		fprintf(stderr,"ERREUR grapheInitialisation : Erreur creation texture : %s\n",SDL_GetError());
		retour = 4;
		}
		// Activation de la transparence
	//SDL_BLENDMODE_NONE || SDL_BLENDMODE_BLEND || SDL_BLENDMODE_ADD || SDL_BLENDMODE_MOD
	if(SDL_SetTextureBlendMode((*graphique).masse, SDL_BLENDMODE_MOD) < 0)
		fprintf(stderr, "ERREUR grapheInitialisation : Erreur SDL_SetRenderDrawBlendMode : %s.", SDL_GetError());

	return retour;
}

int graphiqueNettoyage(graphiqueT * graphique)
	{
	SDL_RenderClear((*graphique).rendu);
	return 0;
	}

int graphiqueCommandes(graphiqueT * graphique, commandesT * commandes)
	{
		// Dessine le fond et les commandes sélectionées
	SDL_Rect coordonnee = {0, 0, (*graphique).fenetreX, (*graphique).fenetreY};
	SDL_RenderCopy((*graphique).rendu, (*graphique).SiCP, NULL, &coordonnee);
	
	int centrage = 5;
	coordonnee.w=10;
	coordonnee.h=10;
	coordonnee.x = (*commandes).boutonsCentre - centrage;	// Positon X de la zone des petits boutons
	int i;
	int X, Y, x, y;
			
	for(i=0;i<BOUTON_COMMANDES;i++)
		{
		if((*commandes).boutonEtat[i]==1)
			{
			coordonnee.y = (*commandes).boutonCentre[i] - centrage; // Positon Y des petits boutons
			//	Dessin des petits boutons
			SDL_RenderCopy((*graphique).rendu, (*graphique).masse, NULL, &coordonnee);
			}
		}

	graphiqueChangeCouleur(graphique, (*graphique).orange);
	X=(*commandes).rotatifsCentre;
	for(i=0;i<ROTATIF_COMMANDES;i++)
		{
		Y=(*commandes).rotatifCentre[i];
		x=X+(*commandes).rotatifPositionX[i];
		y=Y+(*commandes).rotatifPositionY[i];
		SDL_RenderDrawLine((*graphique).rendu, X-1, Y, x-1, y);
		SDL_RenderDrawLine((*graphique).rendu, X, Y-1, x, y-1);
		SDL_RenderDrawLine((*graphique).rendu, X+1, Y, x+1, y);
		SDL_RenderDrawLine((*graphique).rendu, X, Y+1, x, y+1);
		}

	return 0;
	}

int graphiqueCapteurs(graphiqueT * graphique, capteursT * capteurs)
	{
	int i, j;

		// Energie
	//graphiqueChangeCouleur(graphique, (*graphique).grisF);



	// Rouge
	graphiqueChangeCouleur(graphique, (*graphique).rouge);
		// Cinetique
	SDL_RenderDrawLines((*graphique).rendu, (*capteurs).capteur[1].somme, DUREE_CAPTEURS);
		// Energie Gauche
	SDL_RenderDrawLines((*graphique).rendu, (*capteurs).capteur[3].somme, DUREE_CAPTEURS);


	// Bleue
	graphiqueChangeCouleur(graphique, (*graphique).bleue);
		// Couplage
	SDL_RenderDrawLines((*graphique).rendu, (*capteurs).capteur[2].somme, DUREE_CAPTEURS);
		// Energie Droite
	SDL_RenderDrawLines((*graphique).rendu, (*capteurs).capteur[3].droite, DUREE_CAPTEURS);

	// Vert
	graphiqueChangeCouleur(graphique, (*graphique).vert);
		// Rappel - Gravitation
	SDL_RenderDrawLines((*graphique).rendu, (*capteurs).capteur[0].somme, DUREE_CAPTEURS);
		// Energie Gauche
	SDL_RenderDrawLines((*graphique).rendu, (*capteurs).capteur[3].gauche, DUREE_CAPTEURS);

						// 0 : Rappel, 1 : Cinetique, 2 : Couplage, 3 : Energie

						//		0, 1, 2 : Somme, 3, 4, 5 : droite/gauche
		// Epaississement du trait
	for(j=0;j<CAPTEURS;j++)
		{
		for(i=0;i<DUREE_CAPTEURS;i++)
			{
			(*capteurs).capteur[j].droite[i].y = (*capteurs).capteur[j].droite[i].y + 1;
			}
		}
		// Energie
	graphiqueChangeCouleur(graphique, (*graphique).grisF);

	//SDL_RenderDrawLines((*graphique).rendu, (*capteurs).capteur[0].somme, DUREE_CAPTEURS);
	//SDL_RenderDrawLines((*graphique).rendu, (*capteurs).capteur[3].gauche, DUREE_CAPTEURS);
	//SDL_RenderDrawLines((*graphique).rendu, (*capteurs).capteur[3].droite, DUREE_CAPTEURS);
/*
	graphiqueChangeCouleur(graphique, (*graphique).gauche);
	for(j=0;j<CAPTEURS;j++)
		{
		for(i=0;i<DUREE_CAPTEURS;i++)
			{
			(*capteurs).capteur[j].gauche[i].y = (*capteurs).capteur[j].gauche[i].y + 1;
			}
		}
	SDL_RenderDrawLines((*graphique).rendu, (*capteurs).capteur[0].gauche, DUREE_CAPTEURS);
	SDL_RenderDrawLines((*graphique).rendu, (*capteurs).capteur[1].gauche, DUREE_CAPTEURS);
	SDL_RenderDrawLines((*graphique).rendu, (*capteurs).capteur[2].gauche, DUREE_CAPTEURS);
*/

	return 0;
	}


int graphiqueMiseAJour(graphiqueT * graphique)
	{
	SDL_RenderPresent((*graphique).rendu);
	return 0;
	}

int graphiqueChangeCouleur(graphiqueT * graphique, SDL_Color couleur)
	{
	if(SDL_SetRenderDrawColor((*graphique).rendu, couleur.r, couleur.g, couleur.b, couleur.a) < 0)
	return -1;
	return 0;  
	}

void graphiqueTige(graphiqueT * graphique, int X, int Y, int x, int y, float sinT, float cosT)
	{
	int decalageDroit = 0;
	int decalageDiag = 1;
	float sinCarre=sinT*sinT;
	int sinusC = (int)(125*sinCarre);
	(void)cosT;

		// Horizontales 		    R	  V	  B
	SDL_SetRenderDrawColor((*graphique).rendu, sinusC, 55+sinusC, 125+sinusC, 255-sinusC);
	//graphiqueChangeCouleur(graphique, (*graphique).cyan);
	SDL_RenderDrawLine((*graphique).rendu, X-decalageDroit, Y-decalageDiag, x-decalageDroit, y-decalageDiag);
	SDL_RenderDrawLine((*graphique).rendu, X+decalageDroit, Y+decalageDiag, x+decalageDroit, y+decalageDiag);

		// Verticale
	SDL_SetRenderDrawColor((*graphique).rendu, 250-sinusC, 250-sinusC, 25, 255);
	//graphiqueChangeCouleur(graphique, (*graphique).jaune);
	SDL_RenderDrawLine((*graphique).rendu, X+decalageDiag, Y+decalageDroit, x+decalageDiag, y+decalageDroit);
	SDL_RenderDrawLine((*graphique).rendu, X-decalageDiag, Y-decalageDroit, x-decalageDiag, y-decalageDroit);

	return;
	}

void graphiqueTriangleGris(graphiqueT * graphique, int X, int Y, int Ax, int Ay, int Bx, int By)
	{
	int x[3];
	int y[3];
	float a = 0.0;
	float b = 0.0;
	float c = 0.0;
	float d = 0.0;

	//Uint32 couleurG = SDL_MapRGB(affichage->format, 127, 127, 127);

	if(Y>Ay && Y>By){x[2]=X;y[2]=Y;
		if(Ay>By)
			{x[0]=Bx; y[0]=By; x[1]=Ax; y[1]=Ay;}
		else
			{x[0]=Ax; y[0]=Ay; x[1]=Bx; y[1]=By;}
		}
	else
		{
		if(Y<Ay && Y<By){x[0]=X;y[0]=Y;
			if(By>Ay)
				{x[1]=Ax; y[1]=Ay; x[2]=Bx; y[2]=By;}
			else
				{x[1]=Bx; y[1]=By; x[2]=Ax; y[2]=Ay;}
			}
		else{x[1]=X;y[1]=Y;
			if(By>Ay)
				{x[0]=Ax; y[0]=Ay; x[2]=Bx; y[2]=By;}
			else
				{x[0]=Bx; y[0]=By; x[2]=Ax; y[2]=Ay;}
			}
		}

	int i;

	if(y[0]!=y[1])
		{a=(float)(x[1]-x[0])/(y[1]-y[0]);}
	b=x[0]-a*y[0];

	if(y[0]!=y[2])
		{c=(float)(x[2]-x[0])/(y[2]-y[0]);}
	d=x[0]-c*y[0];

	graphiqueChangeCouleur(graphique, (*graphique).gris);

	for(i=y[0];i<=y[1];i++)
		{
		SDL_RenderDrawLine((*graphique).rendu, a*i+b, i, c*i+d, i);
		}

	if(y[1]!=y[2])
		{a=(float)(x[2]-x[1])/(y[2]-y[1]);}
	b=x[1]-a*y[1];

	for(i=y[1];i<=y[2];i++)
		{
		SDL_RenderDrawLine((*graphique).rendu, a*i+b, i, c*i+d, i);
		}

	return;
	}

void graphiqueTrianglePlein(graphiqueT * graphique, int X, int Y, int Ax, int Ay, int Bx, int By)
	{
	graphiqueTriangleGris(graphique, X, Y, Ax, Ay, Bx, By);

	graphiqueChangeCouleur(graphique, (*graphique).contraste);

	SDL_RenderDrawLine((*graphique).rendu, X, Y, Ax, Ay);
	SDL_RenderDrawLine((*graphique).rendu, X, Y, Bx, By);
	SDL_RenderDrawLine((*graphique).rendu, Ax, Ay, Bx, By);

	return;
	}

void graphiqueRectanglePlein(graphiqueT * graphique, int Ax, int Ay, int Bx, int By, int Cx, int Cy, int Dx, int Dy)
	{

	graphiqueTriangleGris(graphique, Ax, Ay, Bx, By, Cx, Cy);
	graphiqueTriangleGris(graphique, Ax, Ay, Cx, Cy, Dx, Dy);

	graphiqueChangeCouleur(graphique, (*graphique).contraste);

	SDL_RenderDrawLine((*graphique).rendu, Bx, By, Ax, Ay);
	SDL_RenderDrawLine((*graphique).rendu, Dx, Dy, Ax, Ay);
	SDL_RenderDrawLine((*graphique).rendu, Cx, Cy, Bx, By);
	SDL_RenderDrawLine((*graphique).rendu, Cx, Cy, Dx, Dy);

	return;
	}

void graphiquePenduleSupportPlein(graphiqueT * graphique, grapheT * graphe)
	{
//                                                J   I
//                                             L   K
//                                               M
//                                               
//                                                H   G
//                                             F   E
//               N


//             D   C
//         B   A

	int Ax, Ay, Bx, By;
	int Ex, Ey, Fx, Fy, Gx, Gy, Hx, Hy;
	int Ix, Iy, Jx, Jy, Kx, Ky, Lx, Ly;
	int Nx, Ny;

		//	Point du support
	Ax = (*graphe).supporX[0]; Ay = (*graphe).supporY[0];
	Bx = (*graphe).supporX[1]; By = (*graphe).supporY[1];

	Ex = (*graphe).supporX[4]; Ey = (*graphe).supporY[4];
	Fx = (*graphe).supporX[5]; Fy = (*graphe).supporY[5];
	Gx = (*graphe).supporX[6]; Gy = (*graphe).supporY[6];
	Hx = (*graphe).supporX[7]; Hy = (*graphe).supporY[7];
	Ix = (*graphe).supporX[8]; Iy = (*graphe).supporY[8];
	Jx = (*graphe).supporX[9]; Jy = (*graphe).supporY[9];
	Kx = (*graphe).supporX[10]; Ky = (*graphe).supporY[10];
	Lx = (*graphe).supporX[11]; Ly = (*graphe).supporY[11];

	Nx = (*graphe).supporX[13]; Ny = (*graphe).supporY[13];


		// Boitier moteur et montant avant
	if((*graphe).arriere <= 0) // Vue de devant
		{
			// Boitier moteur	
		if((*graphe).gauche <= 0) // Montant gauche
			{
			graphiqueRectanglePlein(graphique, Ex, Ey, Gx, Gy, Ix, Iy, Kx, Ky);
			}
		else// Montant droit
			{
			graphiqueRectanglePlein(graphique, Fx, Fy, Hx, Hy, Jx, Jy, Lx, Ly);
			}

			// Face avant
		graphiqueRectanglePlein(graphique, Fx, Fy, Ex, Ey, Kx, Ky, Lx, Ly);

		if((*graphe).dessous <= 0) // Vue de dessus
			{
				// Chassis
			graphiqueRectanglePlein(graphique, Ax, Ay, Bx, By, Fx, Fy, Ex, Ey);
				// Dessus moteur
			graphiqueRectanglePlein(graphique, Kx, Ky, Ix, Iy, Jx, Jy, Lx, Ly);
			}
		}
	else // Vue de derriere
		{
		if((*graphe).dessous <= 0) // Vue de dessus
			{
				// Chassis
			graphiqueRectanglePlein(graphique, Ax, Ay, Bx, By, Fx, Fy, Ex, Ey);
				// Palier avant
			graphiqueTrianglePlein(graphique, Nx, Ny, Ax, Ay, Bx, By);
			}
		else // Vue de dessous
			{
				// Palier avant
			graphiqueTrianglePlein(graphique, Nx, Ny, Ax, Ay, Bx, By);
			}
		}


		// Chaine de pendule
	graphiquePendule(graphique, graphe);


		// Boitier moteur et montant avant	
	if((*graphe).arriere > 0) // Vue de derrière
		{
			// Boitier moteur	
		if((*graphe).gauche <= 0) // Montant gauche
			{
			graphiqueRectanglePlein(graphique, Ex, Ey, Gx, Gy, Ix, Iy, Kx, Ky);
			}
		else// Montant droit
			{
			graphiqueRectanglePlein(graphique, Fx, Fy, Hx, Hy, Jx, Jy, Lx, Ly);
			}
			// Face arrière
		graphiqueRectanglePlein(graphique, Hx, Hy, Gx, Gy, Ix, Iy, Jx, Jy);

		if((*graphe).dessous > 0) // Vue de dessous
			{	// Chassis
			graphiqueRectanglePlein(graphique, Ax, Ay, Bx, By, Hx, Hy, Gx, Gy);
			}
		else
			{	// Dessus moteur
			graphiqueRectanglePlein(graphique, Kx, Ky, Ix, Iy, Jx, Jy, Lx, Ly);
			}
		}
	else // Vue de devant
		{
		if((*graphe).dessous <= 0) // Vue de dessus
			{	// Palier avant
			graphiqueTrianglePlein(graphique, Nx, Ny, Ax, Ay, Bx, By);
			}
		else // Vue de dessous
			{
				// Palier avant
			graphiqueTrianglePlein(graphique, Nx, Ny, Ax, Ay, Bx, By);
				// Chassis
			graphiqueRectanglePlein(graphique, Ax, Ay, Bx, By, Hx, Hy, Gx, Gy);
			}
		}

	return;
	}

void graphiqueTriangle(graphiqueT * graphique, int X, int Y, int Ax, int Ay, int Bx, int By)
	{

	SDL_RenderDrawLine((*graphique).rendu, X, Y, Ax, Ay);
	SDL_RenderDrawLine((*graphique).rendu, X, Y, Bx, By);
	SDL_RenderDrawLine((*graphique).rendu, Ax, Ay, Bx, By);

	return;
	}

void graphiqueRectangle(graphiqueT * graphique, int Ax, int Ay, int Bx, int By, int Cx, int Cy, int Dx, int Dy)
	{

	SDL_RenderDrawLine((*graphique).rendu, Bx, By, Ax, Ay);
	SDL_RenderDrawLine((*graphique).rendu, Dx, Dy, Ax, Ay);
	SDL_RenderDrawLine((*graphique).rendu, Cx, Cy, Bx, By);
	SDL_RenderDrawLine((*graphique).rendu, Cx, Cy, Dx, Dy);

	return;
	}

void graphiquePenduleSupport(graphiqueT * graphique, grapheT * graphe)
	{
//                                                J   I
//                                             L   K
//                                               M
//                                               
//                                                H   G
//                                             F   E
//               N


//             D   C
//         B   A

	int Ax, Ay, Bx, By;
	int Ex, Ey, Fx, Fy, Gx, Gy, Hx, Hy;
	int Ix, Iy, Jx, Jy, Kx, Ky, Lx, Ly;
	int Nx, Ny;

		//	Point du support
	Ax = (*graphe).supporX[0]; Ay = (*graphe).supporY[0];
	Bx = (*graphe).supporX[1]; By = (*graphe).supporY[1];

	Ex = (*graphe).supporX[4]; Ey = (*graphe).supporY[4];
	Fx = (*graphe).supporX[5]; Fy = (*graphe).supporY[5];
	Gx = (*graphe).supporX[6]; Gy = (*graphe).supporY[6];
	Hx = (*graphe).supporX[7]; Hy = (*graphe).supporY[7];
	Ix = (*graphe).supporX[8]; Iy = (*graphe).supporY[8];
	Jx = (*graphe).supporX[9]; Jy = (*graphe).supporY[9];
	Kx = (*graphe).supporX[10]; Ky = (*graphe).supporY[10];
	Lx = (*graphe).supporX[11]; Ly = (*graphe).supporY[11];

	Nx = (*graphe).supporX[13]; Ny = (*graphe).supporY[13];


	graphiqueChangeCouleur(graphique, (*graphique).contraste);
		// Boitier moteur et montant avant
	if((*graphe).arriere <= 0) // Vue de devant
		{
			// Boitier moteur	
		//if((*graphe).gauche <= 0) // Montant gauche
			{
			graphiqueRectangle(graphique, Ex, Ey, Gx, Gy, Ix, Iy, Kx, Ky);
			}
		//else// Montant droit
			{
			graphiqueRectangle(graphique, Fx, Fy, Hx, Hy, Jx, Jy, Lx, Ly);
			}

			// Face avant
		graphiqueRectangle(graphique, Fx, Fy, Ex, Ey, Kx, Ky, Lx, Ly);
			// Face arrière
		graphiqueRectangle(graphique, Hx, Hy, Gx, Gy, Ix, Iy, Jx, Jy);

		if((*graphe).dessous <= 0) // Vue de dessus
			{
				// Chassis
			graphiqueRectangle(graphique, Ax, Ay, Bx, By, Fx, Fy, Ex, Ey);
				// Dessus moteur
			//graphiqueRectangle(graphique, Kx, Ky, Ix, Iy, Jx, Jy, Lx, Ly);
			}
		}
	else // Vue de derriere
		{
		if((*graphe).dessous <= 0) // Vue de dessus
			{
				// Chassis
			graphiqueRectangle(graphique, Ax, Ay, Bx, By, Fx, Fy, Ex, Ey);
				// Palier avant
			graphiqueTriangle(graphique, Nx, Ny, Ax, Ay, Bx, By);
			}
		else // Vue de dessous
			{
				// Palier avant
			graphiqueTriangle(graphique, Nx, Ny, Ax, Ay, Bx, By);
			}
		}


		// Chaine de pendule
	graphiquePendule(graphique, graphe);

	graphiqueChangeCouleur(graphique, (*graphique).contraste);

		// Boitier moteur et montant avant	
	if((*graphe).arriere > 0) // Vue de derrière
		{
			// Boitier moteur	
		//if((*graphe).gauche <= 0) // Montant gauche
			{
			graphiqueRectangle(graphique, Ex, Ey, Gx, Gy, Ix, Iy, Kx, Ky);
			}
		//else// Montant droit
			{
			graphiqueRectangle(graphique, Fx, Fy, Hx, Hy, Jx, Jy, Lx, Ly);
			}
			// Face arrière
		graphiqueRectangle(graphique, Hx, Hy, Gx, Gy, Ix, Iy, Jx, Jy);
			// Face avant
		graphiqueRectangle(graphique, Fx, Fy, Ex, Ey, Kx, Ky, Lx, Ly);

		if((*graphe).dessous > 0) // Vue de dessous
			{	// Chassis
			//graphiqueRectangle(graphique, Ax, Ay, Bx, By, Hx, Hy, Gx, Gy);
			graphiqueRectangle(graphique, Ax, Ay, Bx, By, Fx, Fy, Ex, Ey);
			}
		else
			{	// Dessus moteur
			//graphiqueRectangle(graphique, Kx, Ky, Ix, Iy, Jx, Jy, Lx, Ly);
			}
		}
	else // Vue de devant
		{
		if((*graphe).dessous <= 0) // Vue de dessus
			{	// Palier avant
			graphiqueTriangle(graphique, Nx, Ny, Ax, Ay, Bx, By);
			}
		else // Vue de dessous
			{
				// Palier avant
			graphiqueTriangle(graphique, Nx, Ny, Ax, Ay, Bx, By);
				// Chassis
			//graphiqueRectangle(graphique, Ax, Ay, Bx, By, Hx, Hy, Gx, Gy);
			graphiqueRectangle(graphique, Ax, Ay, Bx, By, Fx, Fy, Ex, Ey);
			}
		}

	return;
	}

void graphiquePendule(graphiqueT * graphique, grapheT * graphe)
	{
	int graphAbs, graphOrd, fixAbs, fixOrd;
	int sortie=0;
	//int centrage = (*graphique).taille / 2;
	int centrage = 4;
	pointsT *iter=(*graphe).premier;
	//SDL_Rect coordonnee = {0, 0, (*graphique).taille, (*graphique).taille};
	SDL_Rect coordonnee = {0, 0, 8, 8};

	// Axe des pendules
	graphiqueChangeCouleur(graphique, (*graphique).contraste);
	SDL_RenderDrawLine((*graphique).rendu, (*graphe).supporX[12], (*graphe).supporY[12], (*graphe).supporX[13], (*graphe).supporY[13]);

	// Pendules
	if((*graphe).arriere != 0) // Vue de derrière, la chaîne est dessinée vers les précédents.
		{iter = iter->precedent;}
	else {(*graphe).arriere = 0;}

	do
		{
		//	Dessin des tiges
		fixAbs=iter->xa;
		fixOrd=iter->ya;
		graphAbs=iter->xm;
		graphOrd=iter->ym;
		graphiqueTige(graphique, fixAbs, fixOrd, graphAbs, graphOrd, iter->sinTheta, iter->cosTheta);

		//	Dessin des masses
		coordonnee.x = iter->xm - centrage;
		coordonnee.y = iter->ym - centrage;
		SDL_RenderCopy((*graphique).rendu, (*graphique).masse, NULL, &coordonnee);

		if((*graphe).arriere == 0)
			{iter=iter->suivant;}
		else // Vue de derrière, la chaîne est dessinée vers les précédents.
			{iter=iter->precedent;}


		if((*graphe).arriere == 0)
			{if(iter==(*graphe).premier) sortie = 1;}
		else // Vue de derrière, la chaîne est dessinée vers les précédents.
			{if(iter==(*graphe).premier->precedent) sortie = 1;}
		}
	while(sortie==0);

	return;
	}

//////////////////////////////////////////////////////////////////////////////


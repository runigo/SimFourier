# Copyright novembre 2023, Stephan Runigo
# runigo@free.fr
# (SiCP 2.5 simulateur de chaîne de pendules)
# SimFourier 1.0 Transformation de Fourier
# Ce logiciel est un programme informatique servant à donner une représentation
# graphique de la transformation de Fourier à 1 dimension.
# Ce logiciel est régi par la licence CeCILL soumise au droit français et 
# respectant les principes de diffusion des logiciels libres. Vous pouvez 
# utiliser, modifier et/ou redistribuer ce programme sous les conditions 
# de la licence CeCILL telle que diffusée par le CEA, le CNRS et l'INRIA 
# sur le site "http://www.cecill.info".
# En contrepartie de l'accessibilité au code source et des droits de copie, 
# de modification et de redistribution accordés par cette licence, il n'est 
# offert aux utilisateurs qu'une garantie limitée.  Pour les mêmes raisons, 
# seule une responsabilité restreinte pèse sur l'auteur du programme, le 
# titulaire des droits patrimoniaux et les concédants successifs.
# A cet égard  l'attention de l'utilisateur est attirée sur les risques 
# associés au chargement,  à l'utilisation,  à la modification et/ou au 
# développement et à la reproduction du logiciel par l'utilisateur étant 
# donné sa spécificité de logiciel libre, qui peut le rendre complexe à 
# manipuler et qui le réserve donc à des développeurs et des professionnels 
# avertis possédant  des  connaissances  informatiques approfondies. Les 
# utilisateurs sont donc invités à charger  et  tester  l'adéquation du 
# logiciel à leurs besoins dans des conditions permettant d'assurer la 
# sécurité de leurs systèmes et ou de leurs données et, plus généralement, 
# à l'utiliser et l'exploiter dans les mêmes conditions de sécurité. 
# Le fait que vous puissiez accéder à cet en-tête signifie que vous avez 
# pris connaissance de la licence CeCILL, et que vous en avez accepté les 
# termes.

CC=gcc
EXEC=simFourier.out
CFLAGS= -Wall -Wextra -Werror --std=c99
#SDLFKAGS= `sdl-config --libs`
#LDFLAGS= -Wall -Wextra -Werror --std=c99 -lm -lpthread
LDFLAGS= -Wall -Wextra -Werror --std=c99 -lm

OBJDIR = ./obj

all : $(EXEC)

$(EXEC) : $(OBJDIR)/principale.o $(OBJDIR)/options.o $(OBJDIR)/fichier.o $(OBJDIR)/donnees.o $(OBJDIR)/controleur.o $(OBJDIR)/controleurClavier.o $(OBJDIR)/controleurSouris.o $(OBJDIR)/projectionSystem.o $(OBJDIR)/projectionGraph.o $(OBJDIR)/affichage.o $(OBJDIR)/textures.o $(OBJDIR)/graphique.o $(OBJDIR)/pointDeVue.o $(OBJDIR)/graphes.o $(OBJDIR)/commandes.o $(OBJDIR)/horloge.o $(OBJDIR)/interface.o $(OBJDIR)/capteurs.o $(OBJDIR)/vecteur.o $(OBJDIR)/fonction.o $(OBJDIR)/initiale.o $(OBJDIR)/partie.o $(OBJDIR)/motif.o $(OBJDIR)/fourier.o $(OBJDIR)/systeme.o $(OBJDIR)/modele.o
	$(CC) -g $(OBJDIR)/principale.o $(OBJDIR)/options.o $(OBJDIR)/fichier.o $(OBJDIR)/donnees.o $(OBJDIR)/controleur.o $(OBJDIR)/controleurClavier.o $(OBJDIR)/controleurSouris.o $(OBJDIR)/projectionSystem.o $(OBJDIR)/projectionGraph.o $(OBJDIR)/affichage.o $(OBJDIR)/textures.o $(OBJDIR)/graphique.o $(OBJDIR)/pointDeVue.o $(OBJDIR)/graphes.o $(OBJDIR)/commandes.o $(OBJDIR)/horloge.o $(OBJDIR)/interface.o $(OBJDIR)/capteurs.o $(OBJDIR)/vecteur.o $(OBJDIR)/fourier.o $(OBJDIR)/fonction.o $(OBJDIR)/initiale.o $(OBJDIR)/partie.o $(OBJDIR)/motif.o $(OBJDIR)/systeme.o $(OBJDIR)/modele.o `sdl2-config --libs` $(LDFLAGS) -o $(EXEC)

# $(OBJDIR)/observables.o $(OBJDIR)/chaine.o $(OBJDIR)/change.o $(OBJDIR)/moteurs.o
# $(OBJDIR)/observables.o $(OBJDIR)/chaine.o $(OBJDIR)/change.o $(OBJDIR)/moteurs.o

$(OBJDIR)/principale.o : controleur/principale.c controleur/principale.h
	$(CC) -c -g controleur/principale.c $(CFLAGS) -o $@

$(OBJDIR)/options.o : controleur/options.c controleur/options.h
	$(CC) -c -g controleur/options.c $(CFLAGS) -o $@

$(OBJDIR)/fichier.o : donnees/fichier.c donnees/fichier.h
	$(CC) -c -g donnees/fichier.c $(CFLAGS) -o $@

$(OBJDIR)/donnees.o : donnees/donnees.c donnees/donnees.h
	$(CC) -c -g donnees/donnees.c $(CFLAGS) -o $@

$(OBJDIR)/controleur.o : controleur/controleur.c controleur/controleur.h
	$(CC) -c -g controleur/controleur.c $(CFLAGS) -o $@

$(OBJDIR)/controleurClavier.o : controleur/controleurClavier.c controleur/controleurClavier.h
	$(CC) -c -g controleur/controleurClavier.c $(CFLAGS) -o $@

$(OBJDIR)/controleurSouris.o : controleur/controleurSouris.c controleur/controleurSouris.h
	$(CC) -c -g controleur/controleurSouris.c $(CFLAGS) -o $@

$(OBJDIR)/projectionSystem.o : projection/projectionSystem.c projection/projectionSystem.h
	$(CC) -c -g projection/projectionSystem.c $(CFLAGS) -o $@

$(OBJDIR)/projectionGraph.o : projection/projectionGraph.c projection/projectionGraph.h
	$(CC) -c -g projection/projectionGraph.c $(CFLAGS) -o $@

$(OBJDIR)/horloge.o : interface/horloge.c interface/horloge.h
	$(CC) -c -g interface/horloge.c $(CFLAGS) -o $@

$(OBJDIR)/interface.o : interface/interface.c interface/interface.h
	$(CC) -c -g interface/interface.c $(CFLAGS) -o $@

$(OBJDIR)/affichage.o : interface/affichage.c interface/affichage.h
	$(CC) -c -g interface/affichage.c $(CFLAGS) -o $@

$(OBJDIR)/textures.o : interface/textures.c interface/textures.h
	$(CC) -c -g interface/textures.c $(CFLAGS) -o $@

$(OBJDIR)/graphique.o : interface/graphique.c interface/graphique.h
	$(CC) -c -g interface/graphique.c $(CFLAGS) -o $@

$(OBJDIR)/pointDeVue.o : projection/pointDeVue.c projection/pointDeVue.h
	$(CC) -c -g projection/pointDeVue.c $(CFLAGS) -o $@

$(OBJDIR)/graphes.o : projection/graphes.c projection/graphes.h
	$(CC) -c -g projection/graphes.c $(CFLAGS) -o $@

$(OBJDIR)/commandes.o : interface/commandes.c interface/commandes.h
	$(CC) -c -g interface/commandes.c $(CFLAGS) -o $@

$(OBJDIR)/capteurs.o : interface/capteurs.c interface/capteurs.h
	$(CC) -c -g interface/capteurs.c $(CFLAGS) -o $@

$(OBJDIR)/initiale.o : modele/initiale.c modele/initiale.h
	$(CC) -c -g modele/initiale.c $(CFLAGS) -o $@

$(OBJDIR)/partie.o : modele/partie.c modele/partie.h
	$(CC) -c -g modele/partie.c $(CFLAGS) -o $@

$(OBJDIR)/motif.o : modele/motif.c modele/motif.h
	$(CC) -c -g modele/motif.c $(CFLAGS) -o $@

$(OBJDIR)/vecteur.o : projection/vecteur.c projection/vecteur.h
	$(CC) -c -g projection/vecteur.c $(CFLAGS) -o $@

#$(OBJDIR)/observables.o : modele/observables.c modele/observables.h
#	$(CC) -c -g modele/observables.c $(CFLAGS) -o $@

#$(OBJDIR)/change.o : modele/change.c modele/change.h
#	$(CC) -c -g modele/change.c $(CFLAGS) -o $@

$(OBJDIR)/fonction.o : modele/fonction.c modele/fonction.h
	$(CC) -c -g modele/fonction.c $(CFLAGS) -o $@

$(OBJDIR)/systeme.o : modele/systeme.c modele/systeme.h
	$(CC) -c -g modele/systeme.c $(CFLAGS) -o $@

$(OBJDIR)/moteurs.o : modele/moteurs.c modele/moteurs.h
	$(CC) -c -g modele/moteurs.c $(CFLAGS) -o $@

$(OBJDIR)/fourier.o : modele/fourier.c modele/fourier.h
	$(CC) -c -g modele/fourier.c $(CFLAGS) -o $@

$(OBJDIR)/modele.o : modele/modele.c modele/modele.h
	$(CC) -c -g modele/modele.c $(CFLAGS) -o $@

clean :
	rm $(OBJDIR)/*.o

net : clean
	rm $(EXEC)


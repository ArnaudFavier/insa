/*************************************************************************
         BarriereEntree  -  Gère une barrière d'entrée du parking
                             -------------------
    début                : 18/03/2016
    copyright            : (C) 2016 par Arnaud Favier & Marc Gagné
    e-mail               : arnaud.favier@insa-lyon.fr
                           marc.gagne@insa-lyon.fr
*************************************************************************/

//------ Interface de la tâche <BarriereEntree> (fichier BarriereEntree.h)
#if ! defined ( BARRIERE_E_H )
#define BARRIERE_E_H

//------------------------------------------------------------------------
// Rôle de la tâche <BarriereEntree>
//
// Barriere Entrée
//------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////  INCLUDE
//--------------------------------------------------- Interfaces utilisées
#include <Outils.h>

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
// type Nom ( liste de paramètres );
// Mode d'emploi :
//
// Contrat :
//

void BarriereEntree(enum TypeBarriere barriere, int shmid);
// Mode d'emploi :
// Point d'entrée d'une barrière d'entrèe
// Contrat :
// (auncun)

#endif // BARRIERE_ENTREE_H

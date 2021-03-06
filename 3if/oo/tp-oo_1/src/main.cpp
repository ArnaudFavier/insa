/*************************************************************************
              main - Ensemble de tests pour CollectionEntiers
                             -------------------
    début                : 06/10/2015
    copyright            : (C) 2015 par B3309
*************************************************************************/

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "CollectionEntiers.h"

//------------------------------------------------------------- Constantes
const unsigned int NUM_TESTS = 16;

const char * TESTS_NOMS[] = {
        "Construction (1)",
        "Construction de collection vide (1)",
        "Construction et affichage (1)",
        "Construction (2)",
        "Construction de collection vide (2)",
        "Construction et affichage (2)",
        "Ajouter (sans ajustement)",
        "Ajouter (avec ajustement)",
        "Retirer",
        "Retirer de collection vide",
        "Retirer aucun item",
        "Ajuster en augmentant",
        "Ajuster en diminuant",
        "Ajuster a zero",
        "Reunir deux collections (sans ajustement)",
        "Reunir deux collections (avec ajustement)"
};

//-------------------------------------------------------------- FONCTIONS

bool test_0_construction_1 ()
// Algorithme : Construit une nouvelle collection avec le constructeur 1,
// puis essaie de la supprimer.
{
    unsigned int taille = 5;
    CollectionEntiers * c = new CollectionEntiers(taille);
    delete c;
    return true;
}

bool test_1_construction_1_vide ()
// Algorithme : Construit une nouvelle collection vide avec le
// constructeur 1, puis essaie de la supprimer.
{
    unsigned int taille = 0;
    CollectionEntiers * c = new CollectionEntiers(taille);
    delete c;
    return true;
}

bool test_2_construction_1_affichage ()
// Algorithme : Construit une nouvelle collection avec le constructeur 1,
// puis affiche son contenu.
{
    cout << "\tAffichage attendu :\t" << endl;
    cout << "\tAffichage obtenu :\t";
    unsigned int taille = 10;
    CollectionEntiers * c = new CollectionEntiers(taille);
    c->Afficher();
    delete c;
    return true;
}

bool test_3_construction_2 ()
// Algorithme : Construit une nouvelle collection avec le constructeur 2,
// puis essaie de la supprimer.
{
    unsigned int taille = 5;
    int valeurs[] = {1, 2, 3, 4, 5};
    CollectionEntiers * c = new CollectionEntiers(taille, valeurs);
    delete c;
    return true;
}

bool test_4_construction_2_vide ()
// Algorithme : Construit une nouvelle collection vide avec le
// constructeur 2, puis essaie de la supprimer.
{
    unsigned int taille = 0;
    int valeurs[] = {};
    CollectionEntiers * c = new CollectionEntiers(taille, valeurs);
    delete c;
    return true;
}

bool test_5_construction_2_affichage ()
// Algorithme : Construit une nouvelle collection avec le constructeur 2,
// puis affiche son contenu.
{
    cout << "\tAffichage attendu :\t1 2 3 4 5 6 7 8 9 10 " << endl;
    cout << "\tAffichage obtenu :\t";
    unsigned int taille = 10;
    int valeurs[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    CollectionEntiers * c = new CollectionEntiers(taille, valeurs);
    c->Afficher();
    delete c;
    return true;
}

bool test_6_ajouter_sans_reallocation ()
// Algorithme : Construit une nouvelle collection, y ajoute plusieurs
// valeurs avec la méthode Ajouter, puis affiche son contenu. La
// collection est initialisée avec assez de mémoire allouée pour toutes
// les valeurs.
{
    cout << "\tAffichage attendu :\t1 2 3 4 5 " << endl;
    cout << "\tAffichage obtenu :\t";
    unsigned int taille = 5;
    CollectionEntiers * c = new CollectionEntiers(taille);
    for (int i = 1; i <= 5; i++)
    {
        c->Ajouter(i);
    }
    c->Afficher();
    delete c;
    return true;
}

bool test_7_ajouter_avec_reallocation ()
// Algorithme : Construit une nouvelle collection, y ajoute plusieurs
// valeurs avec la méthode Ajouter, puis affiche son contenu. La
// collection est initialisée sans aucune mémoire allouée ; Ajouter doit
// ré-allouer de la place à chaque appel.
{
    cout << "\tAffichage attendu :\t1 2 3 4 5 " << endl;
    cout << "\tAffichage obtenu :\t";
    unsigned int taille = 0;
    CollectionEntiers * c = new CollectionEntiers(taille);
    for (int i = 1; i <= 5; i++)
    {
        c->Ajouter(i);
    }
    c->Afficher();
    delete c;
    return true;
}

bool test_8_retirer ()
// Algorithme : Construit une nouvelle collection avec des valeurs
// initiales, puis essaie d'en retirer certaines avant d'afficher le
// résultat.
{
    cout << "\tAffichage attendu :\t1 3 4 " << endl;
    cout << "\tAffichage obtenu :\t";
    unsigned int taille = 5;
    int valeurs[] = {1, 2, 3, 4, 5};
    unsigned int n = 3;
    int retirer[] = {5, 2, 5, 6};
    CollectionEntiers * c = new CollectionEntiers(taille, valeurs);
    c->Retirer(n, retirer);
    c->Afficher();
    delete c;
    return true;
}

bool test_9_retirer_vide ()
// Algorithme : Construit une nouvelle collection de taille nulle, puis
// essaie d'en retirer certaines valeurs avant d'afficher le résultat.
{
    cout << "\tAffichage attendu :\t " << endl;
    cout << "\tAffichage obtenu :\t";
    unsigned int taille = 0;
    unsigned int n = 3;
    int retirer[] = {5, 2, 5};
    CollectionEntiers * c = new CollectionEntiers(taille);
    c->Retirer(n, retirer);
    c->Afficher();
    delete c;
    return true;
}

bool test_10_retirer_aucun ()
// Algorithme : Construit une nouvelle collection avec des valeurs
// initiales, puis essaie de retirer 0 valeurs de la collection avant
// d'afficher le résultat.
{
    cout << "\tAffichage attendu :\t1 2 3 4 5 " << endl;
    cout << "\tAffichage obtenu :\t";
    unsigned int taille = 5;
    int valeurs[] = {1, 2, 3, 4, 5};
    unsigned int n = 0;
    int retirer[] = {};
    CollectionEntiers * c = new CollectionEntiers(taille, valeurs);
    c->Retirer(n, retirer);
    c->Afficher();
    delete c;
    return true;
}

bool test_11_ajuster_augmenter ()
// Algorithme : Construit une nouvelle collection avec des valeurs
// initiales, puis essaie d'augmenter la taille allouée avant d'afficher
// le résultat.
{
    cout << "\tAffichage attendu :\t1 2 3 4 5 " << endl;
    cout << "\tAffichage obtenu :\t";
    unsigned int taille = 5;
    int valeurs[] = {1, 2, 3, 4, 5};
    unsigned int taille_augmentee = 10;
    CollectionEntiers * c = new CollectionEntiers(taille, valeurs);
    c->Ajuster(taille_augmentee);
    c->Afficher();
    delete c;
    return true;
}

bool test_12_ajuster_diminuer ()
// Algorithme : Construit une nouvelle collection avec des valeurs
// initiales, puis essaie de diminuer la taille allouée avant d'afficher
// le résultat.
{
    cout << "\tAffichage attendu :\t1 2 " << endl;
    cout << "\tAffichage obtenu :\t";
    unsigned int taille = 5;
    int valeurs[] = {1, 2, 3, 4, 5};
    unsigned int taille_reduite = 2;
    CollectionEntiers * c = new CollectionEntiers(taille, valeurs);
    c->Ajuster(taille_reduite);
    c->Afficher();
    delete c;
    return true;
}

bool test_13_ajuster_nul ()
// Algorithme : Construit une nouvelle collection avec des valeurs
// initiales, puis essaie de réduire la mémoire allouée à 0 avant
// d'afficher le résultat.
{
    cout << "\tAffichage attendu :\t " << endl;
    cout << "\tAffichage obtenu :\t";
    unsigned int taille = 5;
    int valeurs[] = {1, 2, 3, 4, 5};
    unsigned int taille_reduite = 0;
    CollectionEntiers * c = new CollectionEntiers(taille, valeurs);
    c->Ajuster(taille_reduite);
    c->Afficher();
    delete c;
    return true;
}

bool test_14_reunir_sans_reallocation ()
// Algorithme : Construit deux nouvelles collections avec des valeurs
// initiales, puis essaie de réunir les deux en une seule, sans qu'il soit
// nécessaire de ré-allouer lors de l'opération de réunion.
{
    cout << "\tAffichage attendu :\t1 2 3 4 5 6 7 8 " << endl;
    cout << "\tAffichage obtenu :\t";
    unsigned int taille1 = 5;
    int valeurs1[] = {1, 2, 3, 4, 5};
    unsigned int taille2 = 3;
    int valeurs2[] = {6, 7, 8};
    CollectionEntiers * c1 = new CollectionEntiers(taille1, valeurs1);
    c1->Ajuster(taille1 + taille2);
    CollectionEntiers * c2 = new CollectionEntiers(taille2, valeurs2);
    c1->Reunir(c2);
    c1->Afficher();
    delete c1;
    delete c2;
    return true;
}

bool test_15_reunir_avec_reallocation ()
// Algorithme : Construit deux nouvelles collections avec des valeurs
// initiales, puis essaie de réunir les deux en une seule, sachant que
// l'espace alloué à la collection qui sera modifiée sera insuffisant lors
// de la réunion, imposant une réallocation lors de la réunion.
{
    cout << "\tAffichage attendu :\t1 2 3 4 5 6 7 8 " << endl;
    cout << "\tAffichage obtenu :\t";
    unsigned int taille1 = 5;
    int valeurs1[] = {1, 2, 3, 4, 5};
    unsigned int taille2 = 3;
    int valeurs2[] = {6, 7, 8};
    CollectionEntiers * c1 = new CollectionEntiers(taille1, valeurs1);
    CollectionEntiers * c2 = new CollectionEntiers(taille2, valeurs2);
    c1->Reunir(c2);
    c1->Afficher();
    delete c1;
    delete c2;
    return true;
}

int main ()
// Algorithme : Lance chaque test et vérifie qu'ils fonctionnent tous.
// Note : Aucun test ne renverra une condition d'échec actuellement, par
// manque d'outils pour vérifier le contenu d'une CollectionEntiers, mais
// il est envisageable qu'une telle fonctionnalité pourrait être rajoutée
// par la suite.
{
    bool (*TESTS[]) () = {
            test_0_construction_1,
            test_1_construction_1_vide,
            test_2_construction_1_affichage,
            test_3_construction_2,
            test_4_construction_2_vide,
            test_5_construction_2_affichage,
            test_6_ajouter_sans_reallocation,
            test_7_ajouter_avec_reallocation,
            test_8_retirer,
            test_9_retirer_vide,
            test_10_retirer_aucun,
            test_11_ajuster_augmenter,
            test_12_ajuster_diminuer,
            test_13_ajuster_nul,
            test_14_reunir_sans_reallocation,
            test_15_reunir_avec_reallocation
    };

    for (unsigned int i = 0; i < NUM_TESTS; i++) {
        cout << "Test " << i << " : " << TESTS_NOMS[i] << endl;
        bool resultat = TESTS[i]();
        cout << "\t" << (resultat ? "[OK]" : "[FAIL]") << endl << endl;
    }
    return 0;
}

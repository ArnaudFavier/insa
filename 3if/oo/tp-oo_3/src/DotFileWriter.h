/*******************************************************************************
                      DotFileWriter - �crivain de DOT-file
                              --------------------
    d�but                : 01/12/2015
    copyright            : (C) 2015 par B3309
*******************************************************************************/

// Interface de la classe <DotFileWriter> (fichier DotFileWriter.h)
#if ! defined ( DOT_FILE_WRITER_H )
#define DOT_FILE_WRITER_H

//--------------------------------------------------------- Interfaces utilis�es
#include <forward_list>
#include <fstream>
#include <string>

//------------------------------------------------------------------------ Types
struct Link
{
    unsigned long sourceNodeId;  // L'ID du noeud de source du lien.
    unsigned long destinationNodeId;  // L'ID du noeud de destination du lien.
    std::string label;  // L'�tiquette � afficher � c�t� du lien.
};

//------------------------------------------------------------------------------
// R�le de la classe <DotFileWriter>
// Transcrit un graphe au format Graphviz et permet de l'�crire dans un fichier
// DOT.
//------------------------------------------------------------------------------

class DotFileWriter
{
//----------------------------------------------------------------------- PUBLIC
public:
//----------------------------------------------------------- M�thodes publiques
    void AddLink (
            unsigned long sourceId, unsigned long targetId,
            const std::string & linkLabel
    );
    // <sourceId> : l'ID du noeud de source du lien
    // <targetId> : l'ID du noeud de destination du lien
    // <linkLabel> : l'�tiquette � afficher � c�t� du lien
    // Mode d'emploi : Ajoute un lien entre le noeud <sourceId> et le noeud
    // <targetId>, avec une �tiquette <linkLabel> � c�t�.
    // Contrat : <sourceId> et <targetId> devraient d�j� avoir �t� ajout�s gr�ce
    // � <AddNode>. Le graphe doit �tre initialis� avec InitGraph au pr�alable.

    void AddNode (unsigned long id, const std::string & label);
    // <id> : l'ID identifiant le noeud
    // <label> : l'�tiquette � afficher � c�t� du noeud
    // Mode d'emploi : Ajoute un nouveau noeud du graphe, identifi� par son
    // <id>. Son <label> est affich� � c�t� du noeud dans le graphe g�n�r�.
    // Contrat : Le graphe doit �tre initialis� avec InitGraph au pr�alable.

    void Close ();
    // Mode d'emploi : Ferme le flux de fichier associ�, s'il a �t� ouvert. Si
    // aucun flux n'a �t� ouvert, aucune action n'est effectu�e.

    void InitGraph(unsigned long graphNodes);
    // <graphNodes> : le nombre de noeuds dans le graphe
    // Mode d'emploi : Initialise le graphe associ�, allouant assez de m�moire
    // pour stocker un nombre <graphNodes> de noeuds. Doit �tre appel� avant de
    // commencer � construire les noeuds et les liens. Si un graphe avait d�j�
    // �t� initialis�, l'ancien graphe est supprim� et un nouveau est cr��.

    bool Open (const std::string & filename);
    // <filename> : le nom de fichier � ouvrir en mode �criture
    // Mode d'emploi : Ouvre un fichier <filename> en mode �criture. Le fichier
    // devrait avoir une extension ".dot", mais ceci n'est pas obligatoire.

    void Write ();
    // Mode d'emploi : �crit le fichier DOT associ� au graphe initialis� par
    // InitGraph.
    // Contrat : Le graphe doit �tre initialis� avec InitGraph au pr�alable.

//------------------------------------------------------- Surcharge d'op�rateurs
    DotFileWriter & operator = (const DotFileWriter & writer) = delete;
    // <writer> : l'�crivain � copier
    // Mode d'emploi : Supprim�. La copie est interdite pour �viter d'avoir des
    // conflits li�s aux flux.

//-------------------------------------------------- Constructeurs - destructeur
    DotFileWriter ();
    // Mode d'emploi : Initialise un �crivain de fichier DOT sans graphe
    // associ�. Le graphe doit ensuite �tre initialis� avec InitGraph.

    DotFileWriter (const DotFileWriter & writer) = delete;
    // <writer> : l'�crivain � copier
    // Mode d'emploi : Supprim�. La copie est interdite pour �viter d'avoir des
    // conflits li�s aux flux.

    virtual ~DotFileWriter ();
    // Mode d'emploi : Supprime l'�crivain, ferme tout flux de fichier associ�
    // et supprime le graphe s'il a �t� initialis�.

//------------------------------------------------------------------------ PRIVE
protected:
//----------------------------------------------------------- Attributs prot�g�s
    std::ofstream dotFile;  // Le flux de fichier de sortie associ�
    std::forward_list<Link> links;  // La liste de liens de graphe
    std::string * nodes;  // Le tableau de noeuds de graphe
    unsigned long numNodes;  // Le nombre de noeuds de graphe

    static const std::string HEADER;  // L'en-t�te du fichier DOT � �crire
    static const std::string FOOTER;  // Le pied de page du fichier DOT � �crire
};

#endif // DOT_FILE_WRITER_H

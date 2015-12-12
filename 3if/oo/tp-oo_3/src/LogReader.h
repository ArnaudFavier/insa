/*******************************************************************************
                  LogReader - Lecteur de fichier de log Apache
                              --------------------
    d�but                : 01/12/2015
    copyright            : (C) 2015 par B3309
*******************************************************************************/

// Interface de la classe <LogReader> (fichier LogReader.h)
#if ! defined ( LOG_READER_H )
#define LOG_READER_H

//--------------------------------------------------------- Interfaces utilis�es
#include <fstream>
#include <string>

//------------------------------------------------------------------------ Types
class LogEntry;

//------------------------------------------------------------------------------
// R�le de la classe <LogReader>
// Permet de lire un fichier de log Apache pour en extraire les donn�es sur
// chaque ligne.
//------------------------------------------------------------------------------

class LogReader
{
//----------------------------------------------------------------------- PUBLIC
public:
//----------------------------------------------------------- M�thodes publiques
    void Close ();
    // Mode d'emploi : Ferme le flux de fichier associ�, s'il a �t� ouvert. Si
    // aucun flux n'a �t� ouvert, aucune action n'est effectu�e.

    bool Eof () const;
    // Mode d'emploi : Renvoie vrai si la fin de fichier a �t� atteinte.

    bool Open (const std::string & filename);
    // <filename> : le nom de fichier � ouvrir en mode lecture
    // Mode d'emploi : Ouvre un fichier de log <filename> en mode lecture.

    void ReadLine (LogEntry & entry);
    // <entry> : l'entr�e � remplir d'informations
    // Mode d'emploi : Lit une ligne du fichier et remplit <entry> des
    // informations extraites de la ligne.

//------------------------------------------------------- Surcharge d'op�rateurs
    LogReader & operator = (const LogReader & reader) = delete;
    // <reader> : le lecteur � copier
    // Mode d'emploi : Supprim�. La copie est interdite pour �viter d'avoir des
    // conflits li�s aux flux.

//-------------------------------------------------- Constructeurs - destructeur
    LogReader ();
    // Mode d'emploi : Initialise un lecteur sans flux ouvert.

    LogReader (const LogReader & reader) = delete;
    // <reader> : le lecteur � copier
    // Mode d'emploi : Supprim�. La copie est interdite pour �viter d'avoir des
    // conflits li�s aux flux.

    virtual ~LogReader ();
    // Mode d'emploi : Supprime le lecteur et ferme tout flux de fichier
    // associ�.

//------------------------------------------------------------------------ PRIVE
protected:
//----------------------------------------------------------- Attributs prot�g�s
    std::ifstream logFile;  // Le flux de fichier d'entr�e associ�
    int currentLine;  // Le num�ro de la ligne actuelle de lecture
};

#endif // LOG_READER_H

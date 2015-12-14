/*******************************************************************************
               ConfigReader - Lecteur de fichier de configuration
                              --------------------
    d�but                : 01/12/2015
    copyright            : (C) 2015 par B3309
*******************************************************************************/

// Interface de la classe <ConfigReader> (fichier ConfigReader.h)
#if ! defined ( CONFIG_READER_H )
#define CONFIG_READER_H

//--------------------------------------------------------- Interfaces utilis�es
#include <string>
#include <unordered_map>
#include <unordered_set>

//------------------------------------------------------------------------------
// R�le de la classe <ConfigReader>
// Lit un fichier de configuration et permet d'en extraire les associations
// cl�s -> valeurs. Un fichier de configuration est structur� de la mani�re
// suivante :
// cle1=valeur1
// cle2=valeur2
//------------------------------------------------------------------------------

class ConfigReader
{
//----------------------------------------------------------------------- PUBLIC
public:
//----------------------------------------------------------- M�thodes publiques
    int GetInteger (const std::string & key, int def = 0) const;
    // <key> : la cl� associ�e � la valeur d�sir�e
    // <def> : la valeur par d�faut � utiliser
    // Mode d'emploi : Essaie de trouver la cl� <key>. Si elle existe, renvoie
    // la valeur associ�e convertie en entier ; sinon, renvoie la valeur par
    // d�faut <def>.

    std::unordered_set<std::string> GetSet (
            const std::string & key, const std::unordered_set<std::string> & def
    ) const;
    // <key> : la cl� associ�e � la valeur d�sir�e
    // <def> : la valeur par d�faut � utiliser
    // Mode d'emploi : Essaie de trouver la cl� <key>. Si elle existe, renvoie
    // la valeur associ�e convertie en set ; sinon, renvoie la valeur par d�faut
    // <def>.

    std::string GetString (const std::string & key, const std::string & def = ""
    ) const;
    // <key> : la cl� associ�e � la valeur d�sir�e
    // <def> : la valeur par d�faut � utiliser
    // Mode d'emploi : Essaie de trouver la cl� <key>. Si elle existe, renvoie
    // la valeur associ�e ; sinon, renvoie la valeur par d�faut <def>.

//-------------------------------------------------- Constructeurs - destructeur
    ConfigReader (const std::string & filename);
    // <filename> : le nom du fichier de configuration � lire
    // Mode d'emploi : Initialise le lecteur � partir du fichier de
    // configuration sp�cifi� par <filename>.

    virtual ~ConfigReader ();
    // Mode d'emploi : D�truit le lecteur.

//------------------------------------------------------------------------ PRIVE
protected:
//----------------------------------------------------------- Attributs prot�g�s
    std::unordered_map<std::string, std::string> config;
};

#endif // CONFIG_READER_H

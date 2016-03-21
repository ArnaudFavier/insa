/*******************************************************************************
                LogEntry - Repr�sente une ligne du fichier de log
                              --------------------
    d�but                : 01/12/2015
    copyright            : (C) 2015 par B3309
*******************************************************************************/

// Interface de la classe <LogEntry> (fichier LogEntry.h)
#if ! defined ( LOG_ENTRY_H )
#define LOG_ENTRY_H

//--------------------------------------------------------- Interfaces utilis�es
#include <iostream>
#include <set>
#include <string>

// Utilisation de Boost si disponible, par souci de performance ; sinon, la
// biblioth�que regex de la STL est utilis�e, par d�faut.
#ifdef USE_BOOST
#include <boost/regex.hpp>
using boost::regex;
using boost::regex_match;
using boost::smatch;
#else
#include <regex>
using std::regex;
using std::regex_match;
using std::smatch;
#endif

//------------------------------------------------------------------------------
// R�le de la classe <LogEntry>
// Repr�sente une entr�e dans un fichier de log Apache.
//------------------------------------------------------------------------------

class LogEntry
{
//----------------------------------------------------------------------- PUBLIC
public:
//-------------------------------------------------------------- Fonctions amies
    friend std::istream & operator >> (
            std::istream & input, LogEntry & logEntry
    );
    // <input> : le flux d'entr�e d'un fichier de log Apache
    // <logEntry> : l'entr�e de log � remplir
    // Mode d'emploi : Permet de lire des entr�es de log directement � partir
    // d'un flux, en extrayant les donn�es importantes d'une ligne du fichier.

//----------------------------------------------------------- M�thodes publiques
    unsigned short GetHour () const;
    // Mode d'emploi : Renvoie l'heure de g�n�ration de l'entr�e de log.

    const std::string & GetRequestMethod () const;
    // Mode d'emploi : Renvoie la m�thode HTTP de requ�te du document.

    const std::string GetRequestUriConverted () const;
    // Mode d'emploi : Renvoie l'URI du document demand� par la requ�te HTTP.

    const std::string GetRequestUriExtension () const;
    // Mode d'emploi : Renvoie l'extension du document demand�. Si l'extension
    // ne peut �tre d�duite, renvoie une cha�ne vide.

    unsigned short GetStatusCode () const;
    // Mode d'emploi : Renvoie le statut de la requ�te.

    const std::string GetRefererUrlConverted (const std::string & local) const;
    // <local> : l'URL du serveur local
    // Mode d'emploi : Renvoie l'URL du r�f�rant de la requ�te. Si l'URL
    // commence par <local>, la requ�te vient du serveur local, et le pr�fixe
    // <local> est enlev� � l'URL.

//-------------------------------------------------- Constructeurs - destructeur
    LogEntry ();
    // Mode d'emploi : Construit une nouvelle entr�e vide.

    virtual ~LogEntry ();
    // Mode d'emploi : D�truit l'entr�e.

//------------------------------------------------------------------------ PRIVE
protected:
//----------------------------------------------------------- M�thodes prot�g�es
    bool parseUri (const std::string & uri, smatch & match) const;
    // <uri> : l'URI � analyser
    // <match> : le r�sultat de l'examination, � modifier
    // Mode d'emploi : Examine une URI pour en extraire les informations
    // int�ressantes.

protected:
//----------------------------------------------------------- Attributs prot�g�s
    unsigned short hour;  // L'heure de g�n�ration de la requ�te
    std::string requestMethod;  // La m�thode de requ�te HTTP
    std::string requestUri;  // L'URI du document demand�
    unsigned short statusCode;  // Le statut de la requ�te
    std::string refererUrl;  // L'URL du r�f�rant de la requ�te

    static const std::string EXTERNAL_DOCUMENT;  // L'�tiquette sp�ciale pour
                                                 // les documents externes
    static const regex APACHE_LOG_ENTRY;  // Le regex pour une ligne du log
    static const regex REQUEST_URI;  // Le regex pour traiter une URI
};

#endif // LOG_ENTRY_H

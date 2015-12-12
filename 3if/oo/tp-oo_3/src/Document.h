/*******************************************************************************
                Document - Repr�sente un document sur le serveur
                              --------------------
    d�but                : 01/12/2015
    copyright            : (C) 2015 par B3309
*******************************************************************************/

// Interface de la classe <Document> (fichier Document.h)
#if ! defined ( DOCUMENT_H )
#define DOCUMENT_H

//--------------------------------------------------------- Interfaces utilis�es
#include <string>
#include <unordered_map>

//------------------------------------------------------------------------ Types
typedef std::unordered_map<unsigned long, unsigned int> DocumentHits;

//------------------------------------------------------------------------------
// R�le de la classe <Document>
// Un <Document> repr�sente un document sur le serveur local. La classe stocke
// le nombre de fois que le document a �t� atteint, soit � partir d'un autre
// document sur le serveur loca, soit � partir d'un site ext�rieur ou inconnu.
// Note : il existe un document sp�cial (avec pour URI "*") qui repr�sente
// l'ext�rieur. Celui-ci ne devrait jamais �tre atteint, et peut seulement �tre
// une source d'acc�s au serveur local.
//------------------------------------------------------------------------------

class Document
{
//----------------------------------------------------------------------- PUBLIC
public:
//----------------------------------------------------------- M�thodes publiques
    void AddLocalHit ();
    // Mode d'emploi : Incr�mente le nombre de fois que ce document a �t�
    // atteint par d'autres documents, ce qui inclut des documents externes.

    void AddRemoteHit (unsigned long documentId);
    // <documentId> : l'ID du document que ce document a atteint
    // Mode d'emploi : Incr�mente le nombre de fois que le document <documentId>
    // a �t� atteint par ce document. Si le document <documentId> n'avait jamais
    // �t� atteint, le compte est initialis� � 1.
    // Contrat : <documentId> doit �tre un index dans le vecteur <documents> de
    // HistoryManager.

    unsigned int GetLocalHits () const;
    // Mode d'emploi : Renvoie le nombre de fois que ce document a �t� atteint.

    const DocumentHits & GetRemoteHits () const;
    // Mode d'emploi : Renvoie une liste associative de documents (identifi�s
    // par leur ID) et du nombre de fois qu'ils ont �t� atteints par celui-ci.
    // Si un document n'est pas dans la liste, il n'a jamais �t� atteint par ce
    // document.

    const std::string & GetUri () const;
    // Mode d'emploi : Renvoie l'URI correspondant au document. � noter que les
    // param�tres (�num�r�s apr�s l'extension, g�n�ralement en commen�ant par un
    // ?) ne sont pas pris en compte : index.php est le m�me document que
    // index.php?p=1. Si l'URI renvoy�e est �gale � "*", le "document" n'est pas
    // un vrai document, mais repr�sente tous les documents externes, qui ne
    // sont pas sur le serveur local.

//------------------------------------------------------- Surcharge d'op�rateurs
    bool operator > (const Document & document) const;
    // <document> : le document auquel comparer ce document
    // Mode d'emploi : Renvoie vrai si ce document a �t� atteint plus de fois
    // que l'autre document, et faux sinon.

//-------------------------------------------------- Constructeurs - destructeur
    Document (const std::string & documentUri);
    // <documentUri> : l'URI identifiant ce document (sans param�tres)
    // Mode d'emploi : Cr�e un nouveau document � partir de son URI,
    // pr�alablement �pur�e de ses param�tres (les informations variables qui
    // peuvent suivre l'extension de fichier, g�n�ralement pr�c�d�es d'un ?).

    virtual ~Document ();
    // Mode d'emploi : d�truit le document.

//------------------------------------------------------------------------ PRIVE
protected:
//----------------------------------------------------------- Attributs prot�g�s
    unsigned int localHits;  // Le nombre de fois que le document a �t� atteint
    DocumentHits remoteHits;  // Le nombre de fois que d'autres documents
    std::string uri;  // L'URI de ce document, relatif au serveur local
};

#endif // DOCUMENT_H

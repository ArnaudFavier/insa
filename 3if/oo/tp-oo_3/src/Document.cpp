/*******************************************************************************
                Document - Repr�sente un document sur le serveur
                              --------------------
    d�but                : 01/12/2015
    copyright            : (C) 2015 par B3309
*******************************************************************************/

// R�alisation de la classe <Document> (fichier Document.cpp)

//---------------------------------------------------------------------- INCLUDE

//------------------------------------------------------------ Include personnel
#include "Document.h"
#include "Logger.h"

//----------------------------------------------------------------------- PUBLIC

//----------------------------------------------------------- M�thodes publiques
void Document::AddLocalHit ()
{
    DEBUG("Appel � Document::AddLocalHit");
    localHits++;
} //----- Fin de AddLocalHit

void Document::AddRemoteHit (unsigned long documentId)
// Algorithme : Cr�e une case pour le document si elle n'existe pas d�j�, puis
// incr�mente le compteur dans cette case de 1.
{
    DEBUG("Appel � Document::AddRemoteHit");
    if (!remoteHits.count(documentId))
    {
        remoteHits[documentId] = 0;
    }
    remoteHits[documentId]++;
} //----- Fin de AddRemoteHit

unsigned int Document::GetLocalHits () const
{
    DEBUG("Appel � Document::GetLocalHits");
    return localHits;
} //----- Fin de GetLocalHits

const DocumentHits & Document::GetRemoteHits () const
{
    DEBUG("Appel � Document::GetRemoteHits");
    return remoteHits;
} //----- Fin de GetRemoteHits

const std::string & Document::GetUri () const
{
    DEBUG("Appel � Document::GetUri");
    return uri;
} //----- Fin de GetUri

//------------------------------------------------------- Surcharge d'op�rateurs
bool Document::operator > (const Document & document) const
{
    DEBUG("Appel � Document::operator >");
    return localHits > document.localHits;
} //----- Fin de la surcharge d'op�rateur >

//-------------------------------------------------- Constructeurs - destructeur
Document::Document (const std::string & documentUri) :
        localHits(0), uri(documentUri)
{
    DEBUG("Appel au constructeur de Document");
} //----- Fin du constructeur

Document::~Document()
{
    DEBUG("Appel au destructeur de Document");
} //----- Fin du destructeur

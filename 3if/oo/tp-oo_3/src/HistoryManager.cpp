/*******************************************************************************
            HistoryManager - G�re un graphe de parcours d'un serveur
                              --------------------
    d�but                : 01/12/2015
    copyright            : (C) 2015 par B3309
*******************************************************************************/

// R�alisation de la classe <HistoryManager> (fichier HistoryManager.cpp)

//---------------------------------------------------------------------- INCLUDE

//-------------------------------------------------------------- Include syst�me
#include <functional>
#include <sstream>

//------------------------------------------------------------ Include personnel
#include "Document.h"
#include "DotFileWriter.h"
#include "HistoryManager.h"
#include "LogEntry.h"
#include "Logger.h"
#include "LogReader.h"

//------------------------------------------------------------------- Constantes
const std::unordered_set<std::string> VALID_REQUEST_METHODS = {"GET", "POST"};
const unsigned short VALID_STATUS_CODES[2] = {200, 399};

//----------------------------------------------------------------------- PUBLIC

//----------------------------------------------------------- M�thodes publiques
bool HistoryManager::FromFile (
        LogReader & logFile,
        const std::unordered_set<std::string> & excludedExtensions,
        unsigned int startHour,
        unsigned int endHour
)
// Algorithme : Lit le fichier de log <logFile> ligne par ligne pour extraire
// les informations sur les documents parcourus, puis ne conserve que les
// documents satisfaisant les crit�res de filtre.
{
    DEBUG("Appel � HistoryManager::FromFile");
    while (!logFile.Eof())
    {
        LogEntry entry;
        try
        {
            logFile.ReadLine(entry);
        }
        catch (std::runtime_error & e)
        {
            WARNING(e.what());
            continue;
        }
        if (entry.GetHour() >= startHour && entry.GetHour() < endHour &&
            !excludedExtensions.count(entry.GetRequestUriExtension()) &&
            VALID_REQUEST_METHODS.count(entry.GetRequestMethod()) &&
            entry.GetStatusCode() >= VALID_STATUS_CODES[0] &&
            entry.GetStatusCode() <= VALID_STATUS_CODES[1])
        {
            addEntry(entry);
        }
    }
    return true;
} //----- Fin de FromFile

void HistoryManager::ListDocuments (unsigned int max) const
// Algorithme : Cr�e une copie tri�e (selon leur popularit�, par ordre
// d�croissant) de la liste des documents, puis affiche au plus <max> �l�ments
// de cette liste tri�e.
{
    DEBUG("Appel � HistoryManager::ListDocuments");
    Documents sortedDocuments = documents;
    std::sort(
            sortedDocuments.begin(), sortedDocuments.end(),
            std::greater<Document>()
    );
    for (Documents::size_type i=0, e=sortedDocuments.size(); i!=e && i<max; ++i)
    {
        if (sortedDocuments[i].GetLocalHits() == 0)
        {
            break;
        }
        std::cout << sortedDocuments[i].GetUri() << " (" <<
                sortedDocuments[i].GetLocalHits() << " hits)\n";
    }
    std::cout << std::flush;
} //----- Fin de ListDocuments

void HistoryManager::ToDotFile (DotFileWriter & dotFile) const
// Algorithme : Pour chaque document dans la liste de document, ajoute un noeud
// au DOT file, puis y ajoute tous les acc�s de ce document vers les autres
// documents comme des liens.
{
    DEBUG("Appel � HistoryManager::ToDotFile");
    dotFile.InitGraph(documents.size());
    for (Documents::size_type i = 0, e = documents.size(); i < e; ++i)
    {
        dotFile.AddNode(i, documents[i].GetUri());
        for (auto const & hit : documents[i].GetRemoteHits())
        {
            std::ostringstream ss;
            ss << hit.second;
            dotFile.AddLink(i, hit.first, ss.str());
        }
    }
    dotFile.Write();
} //----- Fin de ToDotFile

//-------------------------------------------------- Constructeurs - destructeur
HistoryManager::HistoryManager(const std::string & serverUrl) :
        localServerUrl(serverUrl)
{
    DEBUG("Appel au constructeur de HistoryManager");
} //----- Fin du constructeur

HistoryManager::~HistoryManager()
{
    DEBUG("Appel au destructeur de HistoryManager");
} //----- Fin du destructeur

//------------------------------------------------------------------------ PRIVE

//----------------------------------------------------------- M�thodes prot�g�es
void HistoryManager::addEntry (const LogEntry & entry)
// Algorithme : Essaie de trouver le document demand� dans la liste de documents
// (en le cr�ant s'il n'est pas trouv�), puis incr�mente son compteur d'acc�s
// locaux de 1. Ensuite, l'algorithme trouve le document r�f�rant (en le cr�ant
// s'il n'est pas trouv�), puis incr�mente le nombre d'acc�s de ce document vers
// le document demand�.
{
    DEBUG("Appel � HistoryManager::addEntry");
    // Incr�menter le nombre d'acc�s au document demand�.
    std::string requestUri = entry.GetRequestUriConverted();
    Documents::size_type requestIndex;
    auto it = documentsByName.find(requestUri);
    if (it == documentsByName.end())
    {
        requestIndex = documents.size();
        documents.emplace_back(requestUri);
        documentsByName[documents[requestIndex].GetUri()] = requestIndex;
    }
    else
    {
        requestIndex = it->second;
    }
    documents[requestIndex].AddLocalHit();

    // Incr�menter le nombre d'acc�s � ce document au document r�f�rent.
    std::string refererUri = entry.GetRefererUrlConverted(localServerUrl);
    Documents::size_type refererIndex;
    it = documentsByName.find(refererUri);
    if (it == documentsByName.end())
    {
        refererIndex = documents.size();
        documents.emplace_back(refererUri);
        documentsByName[documents[refererIndex].GetUri()] = refererIndex;
    }
    else
    {
        refererIndex = it->second;
    }
    documents[refererIndex].AddRemoteHit(requestIndex);
} //----- Fin de addEntry

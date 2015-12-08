/*******************************************************************************
            HistoryManager - Gère un graphe de parcours d'un serveur
                              --------------------
    début                : 01/12/2015
    copyright            : (C) 2015 par B3309
*******************************************************************************/

// Réalisation de la classe <HistoryManager> (fichier HistoryManager.cpp)

//---------------------------------------------------------------------- INCLUDE

//-------------------------------------------------------------- Include système
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

//----------------------------------------------------------- Méthodes publiques
bool HistoryManager::FromFile (
        LogReader * logFile,
        const std::unordered_set<std::string> & excludedExtensions,
        unsigned int startHour,
        unsigned int endHour
)
// Algorithme :
{
    Logger::Debug("Appel à HistoryManager::FromFile");
    while (!logFile->Eof())
    {
        LogEntry entry;
        try
        {
            logFile->ReadLine(entry);
        }
        catch (std::runtime_error & e)
        {
            Logger::Warning(e.what());
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
// Algorithme :
{
    Logger::Debug("Appel à HistoryManager::ListDocuments");
    Documents sortedDocuments = documents;
    std::sort(sortedDocuments.begin(), sortedDocuments.end(), std::greater<Document>());
    for (Documents::size_type i=0, e=sortedDocuments.size(); i!=e && i<max; ++i)
    {
        std::cout << sortedDocuments[i].GetUri() << " (" <<
                sortedDocuments[i].GetLocalHits() << " hits)\n";
    }
    std::cout << std::flush;
} //----- Fin de ListDocuments

void HistoryManager::ToDotFile (DotFileWriter * dotFile) const
// Algorithme :
{
    Logger::Debug("Appel à HistoryManager::ToDotFile");
    dotFile->InitGraph(documents.size());
    for (Documents::size_type i = 0, e = documents.size(); i < e; ++i)
    {
        dotFile->AddNode(i, documents[i].GetUri());
        for (auto const & hit : documents[i].GetRemoteHits())
        {
            std::ostringstream ss;
            ss << hit.second;
            dotFile->AddLink(i, hit.first, ss.str());
        }
    }
    dotFile->Write();
} //----- Fin de ToDotFile

//-------------------------------------------------- Constructeurs - destructeur
HistoryManager::HistoryManager(const std::string & serverUrl) :
        localServerUrl(serverUrl)
// Algorithme :
{
    Logger::Debug("Appel au constructeur de HistoryManager");
} //----- Fin du constructeur

HistoryManager::~HistoryManager()
// Algorithme :
{
    Logger::Debug("Appel au destructeur de HistoryManager");
} //----- Fin du destructeur

//------------------------------------------------------------------------ PRIVE

//----------------------------------------------------------- Méthodes protégées
void HistoryManager::addEntry (const LogEntry & entry)
{
    Logger::Debug("Appel à HistoryManager::addEntry");
    // Incrémenter le nombre d'accès au document demandé.
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

    // Incrémenter le nombre d'accès à ce document au document référent.
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

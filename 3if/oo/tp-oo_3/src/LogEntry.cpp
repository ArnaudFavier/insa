/*******************************************************************************
                LogEntry - Repr�sente une ligne du fichier de log
                              --------------------
    d�but                : 01/12/2015
    copyright            : (C) 2015 par B3309
*******************************************************************************/

// R�alisation de la classe <LogEntry> (fichier LogEntry.cpp)

//---------------------------------------------------------------------- INCLUDE

//-------------------------------------------------------------- Include syst�me
#include <cstdlib>
#include <stdexcept>

//------------------------------------------------------------ Include personnel
#include "LogEntry.h"
#include "Logger.h"

//------------------------------------------------------------------- Constantes
const std::string LogEntry::EXTERNAL_DOCUMENT = "*";
const regex LogEntry::REQUEST_URI(
        R"(^(?:\:\d+)?((?:\/(?:[^\/?]+\/)*)+([^.\/?][^\/?]+?)?(?:\.(\w*))?))"
        R"((?:((\?.*)|(;.+)))?$)"
);
const regex LogEntry::APACHE_LOG_ENTRY(
        R"(^(\d{1,3})\.(\d{1,3})\.(\d{1,3})\.(\d{1,3}) (\S+) (\S+) )"
        R"(\[(\d{2})\/(\w{3})\/(\d{4})\:(\d{2})\:(\d{2})\:(\d{2}) )"
        R"(\+(\d{2})(\d{2})] \"([A-Z]+) ([^\"]+?) +HTTP\/(\d\.\d)\" (\d+) )"
        R"((\d+|\-) \"([^\"]*)\" \"([^\"]*)\"$)"
);

//----------------------------------------------------------------------- PUBLIC

//-------------------------------------------------------------- Fonctions amies
std::istream & operator >> (std::istream & input, LogEntry & logEntry)
// Algorithme : Passe la ligne � travers un regex pour en extraire les
// informations sous forme de string, puis convertit les r�sultats vers une
// forme appropri�e.
{
    DEBUG("Appel � LogEntry::operator >>");
    std::string line;
    std::getline(input, line);
    if (line.empty())
    {
        return input;
    }
    smatch match;
    if (!regex_match(line, match, LogEntry::APACHE_LOG_ENTRY))
    {
        throw std::runtime_error("Invalid log entry");
    }
    logEntry.hour = atoi(match[10].str().c_str());
    logEntry.requestMethod = match[15];
    logEntry.requestUri = match[16];
    logEntry.statusCode = atoi(match[18].str().c_str());
    logEntry.refererUrl = match[20];
    return input;
} //----- Fin de operator >>

//----------------------------------------------------------- M�thodes publiques
unsigned short LogEntry::GetHour () const
{
    DEBUG("Appel � LogEntry::GetHour");
    return hour;
} //----- Fin de GetHour

const std::string & LogEntry::GetRequestMethod () const
{
    DEBUG("Appel � LogEntry::GetRequestMethod");
    return requestMethod;
} //----- Fin de GetRequestMethod

const std::string LogEntry::GetRequestUriConverted () const
// Algorithme : Essaie de voir si l'URI a une forme sp�ciale (num�ro de port,
// param�tres...) et ne renvoie que la partie de base si c'est le cas.
{
    DEBUG("Appel � LogEntry::GetRequestUriConverted");
    smatch match;
    if (!parseUri(requestUri, match))
    {
        return requestUri;
    }
    return match[1];
} //----- Fin de GetRequestUriConverted

const std::string LogEntry::GetRequestUriExtension () const
// Algorithme : Essaie d'interpr�ter l'URI avec un regex pour en extraire son
// extension de fichier.
{
    DEBUG("Appel � LogEntry::GetRequestUriExtension");
    smatch match;
    if (!parseUri(requestUri, match))
    {
        return "";
    }
    return match[3];
} //----- Fin de GetRequestUriExtension

unsigned short LogEntry::GetStatusCode () const
{
    DEBUG("Appel � LogEntry::GetStatusCode");
    return statusCode;
} //----- Fin de GetStatusCode

const std::string LogEntry::GetRefererUrlConverted (const std::string & local)
    const
// Algorithme : Essaie de simplifier l'URL du r�f�rant, en enlevant les
// param�tres, les num�ros de port �ventuels, et, pour les URL du serveur local,
// renvoie seulement l'URI du document, simplifi�e.
{
    DEBUG("Appel � LogEntry::GetRefererUrlConverted");
    if (!refererUrl.compare(0, local.size(), local))
    {
        std::string convertedUrl = refererUrl.substr(local.size());
        if (convertedUrl.length() == 0)
        {
            return "/";  // insa-lyon.fr est �quivalent � insa-lyon.fr/, donc on
                         // stocke le document avec l'URI / pour �viter les
                         // conflits.
        }
        smatch match;
        if (!parseUri(convertedUrl, match))
        {
            return convertedUrl;
        }
        return match[1];
    }
    return EXTERNAL_DOCUMENT;
} //----- Fin de GetRefererUrlConverted

//-------------------------------------------------- Constructeurs - destructeur
LogEntry::LogEntry () :
        hour(0), requestMethod(""), requestUri(""), statusCode(0),
        refererUrl("")
{
    DEBUG("Appel au constructeur de LogEntry");
} //----- Fin du constructeur

LogEntry::~LogEntry ()
{
    DEBUG("Appel au destructeur de LogEntry");
} //----- Fin du destructeur

//------------------------------------------------------------------------ PRIVE

//----------------------------------------------------------- M�thodes prot�g�es
bool LogEntry::parseUri (const std::string & uri, smatch & match) const
{
    DEBUG("Appel � LogEntry::parseUri");
    return regex_match(uri, match, REQUEST_URI);
} //----- Fin de parseUri

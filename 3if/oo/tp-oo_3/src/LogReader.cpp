/*******************************************************************************
                  LogReader - Lecteur de fichier de log Apache
                              --------------------
    d�but                : 01/12/2015
    copyright            : (C) 2015 par B3309
*******************************************************************************/

// R�alisation de la classe <LogReader> (fichier LogReader.cpp)

//---------------------------------------------------------------------- INCLUDE

//-------------------------------------------------------------- Include syst�me
#include <stdexcept>
#include <sstream>

//------------------------------------------------------------ Include personnel
#include "LogEntry.h"
#include "Logger.h"
#include "LogReader.h"

//----------------------------------------------------------------------- PUBLIC

//----------------------------------------------------------- M�thodes publiques
void LogReader::Close ()
{
    DEBUG("Appel � LogReader::Close");
    if (logFile.is_open())
    {
        logFile.close();
    }
} //----- Fin de Close

bool LogReader::Eof () const
{
    DEBUG("Appel � LogReader::Eof");
    return logFile.eof();
} //----- Fin de Eof

bool LogReader::Open (const std::string & filename)
// Algorithme : Ferme tout flux d�j� ouvert et ouvre un nouveau li� au fichier
// <filename>.
{
    DEBUG("Appel � LogReader::Open");
    Close();
    currentLine = 0;
    logFile.open(filename);
    return logFile.is_open();
} //----- Fin de Open

void LogReader::ReadLine (LogEntry & entry)
// Algorithme : Lit une seule ligne du fichier, si encore possible, puis en
// extrait les informations int�ressantes pour les stocker dans <entry>
{
    DEBUG("Appel � LogReader::ReadLine");
    currentLine++;
    try
    {
        logFile >> entry;
    }
    catch (std::runtime_error & e)
    {
        std::stringstream ss;
        ss << "Failed to parse line " << currentLine << " (" << e.what() << ")";
        throw std::runtime_error(ss.str());
    }
} //----- Fin de ReadLine

//-------------------------------------------------- Constructeurs - destructeur
LogReader::LogReader () : currentLine(0)
{
    DEBUG("Appel au constructeur de LogReader");
} //----- Fin du constructeur

LogReader::~LogReader ()
{
    DEBUG("Appel au destructeur de LogReader");
    Close();
} //----- Fin du destructeur

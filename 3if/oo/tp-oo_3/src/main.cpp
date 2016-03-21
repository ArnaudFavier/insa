/*******************************************************************************
                   main - Interpr�teur � la ligne de commande
                              --------------------
    d�but                : 01/12/2015
    copyright            : (C) 2015 par B3309
*******************************************************************************/

//---------------------------------------------------------------------- INCLUDE

//-------------------------------------------------------------- Include syst�me
using namespace std;
#include <list>
#include <string>
#include <tclap/CmdLine.h>
#include <unordered_set>

//------------------------------------------------------------ Include personnel
#include "ConfigReader.h"
#include "DotFileWriter.h"
#include "HistoryManager.h"
#include "Logger.h"
#include "LogReader.h"

//------------------------------------------------------------------- Constantes
// La description du programme, affich�e � l'appel de --help
const string DESCRIPTION = "Parser for Apache logs";

// La version en cours du programme, affich� � l'appel de --version
const string VERSION = "1.0";

// Le nom du fichier de configuration optionnel
const string CONFIG_FILENAME = "tp-oo_3.cfg";

// La liste des extensions de fichier � exclure par d�faut lorsque l'option -e
// est sp�cifi�e
const unordered_set<string> DEFAULT_EXCLUDED_EXTENSIONS = {
        // Images
        "art", "bm", "bmp", "dwg", "dxf", "fig", "flo", "fpx", "g3", "gif",
        "ico", "ief", "iefs", "jfif", "jfif-tbnl", "jpe", "jpeg", "jpg", "jps",
        "jut", "mcf", "nap", "naplps", "nif", "niff", "pbm", "pct", "pcx",
        "pgm", "pic", "pict", "pm", "png", "pnm", "ppm", "qif", "qti", "qtif",
        "ras", "rast", "rf", "rgb", "rp", "svg", "svf", "tif", "tiff", "turbot",
        "wbmp", "xbm", "xif", "xpm", "xwd",
        // CSS
        "css",
        // JavaScript
        "js"
};

// La racine de l'URL du serveur de base par d�faut
const string DEFAULT_LOCAL_URL = "http://intranet-if.insa-lyon.fr";

// Le nombre maximal de documents � afficher par d�faut
const unsigned int DEFAULT_MAX_DOCUMENTS = 10;

//-------------------------------------------------------------------- FONCTIONS
int main (int argc, const char * const * argv)
// Algorithme : Construit le lecteur d'arguments, traite l'entr�e pour voir
// quels arguments ont �t� pass�s, puis effectue toutes les op�rations
// demand�es par l'utilisateur en param�tre.
{
    ConfigReader config(CONFIG_FILENAME);
    string dotFilename;
    string logFilename;
    DotFileWriter dotFile;
    LogReader logFile;
    unordered_set<string> excludedExtensions;
    unsigned int startHour = 0, endHour = 24;

    // D�sactiver la synchronization avec la biblioth�que IO de C.
    cout.sync_with_stdio(false);

    // Initialiser le parseur d'arguments.
    TCLAP::CmdLine cmd(DESCRIPTION, ' ', VERSION);

    // Configurer l'argument du chemin de fichier log.
    TCLAP::UnlabeledValueArg<string> logFilenameArg(
            "log", "path to the Apache log file to parse", true, "", "FILE",
            cmd
    );

    // Configurer l'argument (optionnel) du chemin de fichier dot-file, pour
    // la g�n�ration d'un graphe Graphviz.
    TCLAP::ValueArg<string> dotFilenameArg(
            "g", "graphviz", "path to a Graphviz file to generate", false, "",
            "FILE", cmd
    );

    TCLAP::SwitchArg excludeExtensionsArg(
            "e", "exclude", "exclude restricted extensions", cmd, false
    );

    // Configurer l'argument (optionnel) de restriction de la plage horaire.
    // Seules des valeurs comprises entre 0 et 23 (incluses) sont accept�es.
    vector<unsigned int> allowedHours;
    for (unsigned int i = 0; i < 24; i++)
    {
        allowedHours.push_back(i);
    }
    TCLAP::ValuesConstraint<unsigned int> timeVals( allowedHours );
    TCLAP::ValueArg<unsigned int> timeArg(
            "t", "time", "restrict parsing to the specified hour", false,
            0, &timeVals, cmd
    );

    // R�cup�rer les valeurs des arguments � la ligne de commande.
    try
    {
        cmd.parse(argc, argv);

        // Essayer de lire le fichier de log.
        logFilename = logFilenameArg.getValue();
        if (!logFile.Open(logFilename))
        {
            ERROR("Failed to open log file for reading");
            return 1;
        }

        // Essayer de lire le DOT-file, si demand�.
        if (dotFilenameArg.isSet())
        {
            dotFilename = dotFilenameArg.getValue();
            if (!dotFile.Open(dotFilename))
            {
                ERROR("Failed to open DOT file for writing");
                return 1;
            }
        }

        // Enregistrer les extensions � exclure de la lecture du log.
        if (excludeExtensionsArg.getValue())
        {
            excludedExtensions = config.GetSet(
                    "EXCLUDED_EXTENSIONS", DEFAULT_EXCLUDED_EXTENSIONS
            );
        }

        // Restreindre la plage horaire autoris�e, si demand�e.
        if (timeArg.isSet())
        {
            startHour = timeArg.getValue();
            endHour = startHour + 1;
            WARNING(
                    "Only hits between ", startHour, "h and ", endHour,
                    "h have been taken into account."
            );
        }
    }
    catch (TCLAP::ArgException & e)
    {
        ERROR(e.what());
        return 1;
    }

    // Peupler l'historique de documents � partir du fichier log.
    HistoryManager historyMgr(config.GetString("LOCAL_URL", DEFAULT_LOCAL_URL));
    bool loaded = historyMgr.FromFile(
            logFile, excludedExtensions, startHour, endHour
    );
    logFile.Close();
    if (!loaded)
    {
        ERROR("Failed to parse log file");
        return 1;
    }

    // G�n�rer le dot-file, si demand�.
    if (dotFilenameArg.isSet())
    {
        historyMgr.ToDotFile(dotFile);
        dotFile.Close();
        INFO("Dot-file ", dotFilename, " generated");
    }

    // Afficher les documents les plus populaires.
    historyMgr.ListDocuments(
            static_cast<unsigned int>(
                    config.GetInteger("MAX_DOCUMENTS", DEFAULT_MAX_DOCUMENTS)
            )
    );

    return 0;
} //----- Fin de main

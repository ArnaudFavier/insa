/*******************************************************************************
            HistoryManager - G�re un graphe de parcours d'un serveur
                              --------------------
    d�but                : 01/12/2015
    copyright            : (C) 2015 par B3309
*******************************************************************************/

// Interface de la classe <HistoryManager> (fichier HistoryManager.h)
#if ! defined ( HISTORY_MANAGER_H )
#define HISTORY_MANAGER_H

//--------------------------------------------------------- Interfaces utilis�es
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

//------------------------------------------------------------------------ Types
class Document;
class DotFileWriter;
class LogEntry;
class LogReader;

typedef std::vector<Document> Documents;
typedef std::unordered_map<std::string, Documents::size_type> NamedDocuments;

//------------------------------------------------------------------------------
// R�le de la classe <HistoryManager>
// G�re un graphe d'historique de parcours d'un serveur Apache. Peut traiter les
// fichiers de log d'Apache pour en d�duire les documents qui ont �t� parcourus.
//------------------------------------------------------------------------------

class HistoryManager
{
//----------------------------------------------------------------------- PUBLIC
public:
//----------------------------------------------------------- M�thodes publiques
    bool FromFile (
            LogReader & logFile,
            const std::unordered_set<std::string> & excludedExtensions,
            unsigned int startHour,
            unsigned int endHour
    );
    // <logFile> : un lecteur de fichier Apache ouvert
    // <excludedExtensions> : la liste des extensions � exclure
    // <startHour> : l'heure de d�but pour la plage horaire (incluse)
    // <endHour> : l'heure de fin pour la plage horaire (exclue)
    // Mode d'emploi : Utilise le lecteur de logs Apache <logFile> pour extraire
    // l'historique de parcours d'un fichier. Seuls les documents avec des
    // extensions qui ne sont pas dans la liste <excludedExtensions> et qui
    // ont �t� visit�s dans la plage horaire [startHour; endHour[ sont trait�s.
    // Contrat : <logFile> doit �tre ouvert et disponible pour la lecture.

    void ListDocuments (unsigned int max) const;
    // <max> : le nombre maximum de documents � lister
    // Mode d'emploi : Affiche la liste des <max> documents les plus populaires
    // (ceux qui ont �t� le plus visit�). S'il y a moins de documents que max,
    // tous les documents ayant �t� visit�s au moins une fois sont list�s.

    void ToDotFile (DotFileWriter & dotFile) const;
    // <dotFile> : un �crivain de fichier DOT ouvert
    // Mode d'emploi : G�n�re un fichier DOT � partir de l'historique stock�. Le
    // fichier g�n�r� peut ensuite �tre pass� � Graphviz pour g�n�ration d'une
    // image du graphe.
    // Contrat : <dotFile> doit �tre ouvert et disponible pour l'�criture.

//-------------------------------------------------- Constructeurs - destructeur
    HistoryManager (const std::string & serverUrl);
    // <serverUrl> : l'URL du serveur local associ� � cet historique
    // Mode d'emploi : Construit un nouveau gestionnaire d'historique pour le
    // serveur sp�cifi� par <serverUrl>. Si une URL commence par <serverUrl>,
    // le document associ� est consid�r� comme faisant partie du serveur local.

    virtual ~HistoryManager ();
    // Mode d'emploi : D�truit le gestionnaire d'historique.

//------------------------------------------------------------------------ PRIVE
protected:
//----------------------------------------------------------- M�thodes prot�g�es
    void addEntry (const LogEntry & entry);
    // <entry> : L'entr�e � ajouter
    // Mode d'emploi : Ajoute une entr�e d'un fichier de log � l'historique.
    // Chaque entr�e correspond � un ou deux documents, qui sont ajout�s � la
    // liste de documents s'ils n'existent pas d�j� ; sinon, leurs compteurs
    // respectifs sont incr�ment�s.

protected:
//----------------------------------------------------------- Attributs prot�g�s
    Documents documents;  // Le tableau de documents ; leur position correspond
                          // � leur ID
    NamedDocuments documentsByName;  // La liste associant l'URI des documents
                                     // � leur ID, pour faciliter leur recherche
                                     // par URI
    const std::string localServerUrl;  // L'URL du serveur local associ� au
                                       // gestionnaire d'historique
};

#endif // HISTORY_MANAGER_H

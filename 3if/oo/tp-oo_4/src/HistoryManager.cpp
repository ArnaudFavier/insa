#include "Canvas.h"
#include "Figure.h"
#include "HistoryManager.h"

GroupEntry::~GroupEntry()
{
    for (HistoryEntry* entry : group)
        delete entry;
}

HistoryManager::~HistoryManager()
{
    for (HistoryEntry* entry : history)
        delete entry;
}

void HistoryManager::addEntry(HistoryEntry* entry)
{
    // Discard any previous future actions.
    if (current != history.size())
        clearEntries(current);

    history.push_back(entry);
    current++;
}

bool HistoryManager::redo(Canvas* canvas)
{
    if (current == history.size())
        return false;
    return doEntry(canvas, history[current++], true);
}

bool HistoryManager::undo(Canvas* canvas)
{
    if (current == 0)
        return false;
    return doEntry(canvas, history[--current], false);
}

void HistoryManager::clearEntries(History::size_type start)
{
    for (History::size_type i = start, s = history.size(); i < s; i++)
        delete history[i];
    history.erase(
            history.begin() + static_cast<History::difference_type>(start),
            history.end()
    );
}

bool HistoryManager::doEntry(Canvas* canvas, HistoryEntry* entry, bool doRedo)
{
    switch (entry->operation)
    {
        // Figure creation/deletion entry: create the figure if redo'ing a
        // creation or undo'ing a deletion, otherwise delete the figure.
        case HistoryEntry::FIGURE:
        {
            FigureEntry* fE = static_cast<FigureEntry*>(entry);
            if ((doRedo && fE->deleted) || (!doRedo && !fE->deleted))
            {
                canvas->deleteFigure(fE->name, false);
                return true;
            }
            canvas->addFigure(fE->name, fE->figure->createCopy(), false);
            return true;
        }

        // Figure movement entry: move the figure by the specified delta if
        // redo'ing, otherwise by its opposite.
        case HistoryEntry::MOVE:
        {
            MoveEntry* mE = static_cast<MoveEntry*>(entry);
            canvas->moveFigure(
                    mE->name,
                    doRedo ? mE->delta : mE->delta.opposite(),
                    false
            );
            return true;
        }

        // Group entry: execute each sub-entry.
        case HistoryEntry::GROUP:
        {
            GroupEntry* gE = static_cast<GroupEntry*>(entry);
            for (HistoryEntry * subEntry : gE->group)
                if (!doEntry(canvas, subEntry, doRedo))
                    return false;
            return true;
        }

        default:
            return false;
    }
}

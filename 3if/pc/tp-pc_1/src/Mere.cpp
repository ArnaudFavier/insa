#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>

#include <Heure.h>
#include <Outils.h>

#include "config.h"
#include "BarriereE.h"
#include "BarriereS.h"
#include "Simulateur.h"

int main ()
{
    //enum TypeTerminal terminal = XTERM;
    enum TypeTerminal terminal = VT220;

    size_t MAX_TACHES = NB_BARRIERES + 2;
    pid_t tachesPid[MAX_TACHES];
    size_t taches = 0;

    /* --- Initialisation --- */
    InitialiserApplication(terminal);
    int boites[] = {
        msgget(CLE_BARRIERE_PBP, IPC_CREAT),
        msgget(CLE_BARRIERE_ABP, IPC_CREAT),
        msgget(CLE_BARRIERE_EGB, IPC_CREAT),
        msgget(CLE_BARRIERE_SGB, IPC_CREAT)
    };
    tachesPid[taches++] = ActiverHeure();

    if ((tachesPid[taches++] = fork()) == 0)
    {
        // Fils - Barrière S (Sortie)
        BarriereS();
    }
    else
    {
        // Père
        if ((tachesPid[taches++] = fork()) == 0)
        {
            // Fils - Barrière PBP (Blaise Pascal - Profs)
            BarriereE(PROF_BLAISE_PASCAL);
        }
        else
        {
            // Père
            if ((tachesPid[taches++] = fork()) == 0)
            {
                // Fils - Simulateur
                Simulateur();
            }
            else
            {
                // Père
                /* --- Moteur --- */
                waitpid(tachesPid[taches--], NULL, 0);

                /* --- Destruction --- */
                while (taches)
                {
                    kill(tachesPid[--taches], SIGUSR2);
                }
                for (size_t i = 0; i < NB_BARRIERES; i++)
                {
                    msgctl(boites[i], IPC_RMID, NULL);
                }
                TerminerApplication(true);
                exit(0);
            }
        }
    }

    return 0;
}
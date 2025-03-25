#include "projetOS.h"

TablePTT *tablePTT = NULL; // Table des partitions
char cmdLine[1 + LINELENGTH];
char *cmd[MAXWORDS];

int main()
{
	printf("\n===============================\n");
	printf("\n  BIENVENUE DANS LE GESTIONNAIRE DE FICHIERS  \n");
	printf(" Besoin d'aide ? ---> help\n");
	printf("\n===============================\n");

	int nWords;
	int loop = 1;

	// Menu principal
	while (loop && (nWords = readCmd()) >= 0)
	{
		if (strcmp(cmd[0], "myformat") == 0 && cmd[1] != NULL)
		{
			myFormat(cmd[1]); // Formater la partition
		}
		else if (strcmp(cmd[0], "myopen") == 0 && cmd[1] != NULL)
		{
			if (tablePTT != NULL)
			{
				myOpen(cmd[1], tablePTT->ft); // Ouvrir un fichier
			}
			else
			{
				printf("Veuillez créer une partition avant d'ouvrir un fichier !\n");
			}
		}
		else if (strcmp(cmd[0], "mywrite") == 0 && cmd[1] != NULL && cmd[2] != NULL)
		{
			if (tablePTT != NULL)
			{
				File *f = getFile(tablePTT->ft, cmd[1]);
				if (f != NULL)
				{
					int res = myWrite(f, cmd[2], strlen(cmd[2])); // Écrire dans un fichier
					if (res != 0)
					{
						printf("Erreur lors de l'écriture.\n");
					}
				}
				else
				{
					printf("Fichier introuvable.\n");
				}
			}
		}
		else if (strcmp(cmd[0], "myread") == 0 && cmd[1] != NULL && cmd[2] != NULL)
		{
			if (tablePTT != NULL)
			{
				File *f = getFile(tablePTT->ft, cmd[1]);
				int bufferSize = atoi(cmd[2]);
				if (f != NULL && bufferSize > 0)
				{
					char buffer[bufferSize];
					printf("-> %d octets lus\n", myRead(f, buffer, bufferSize)); // Lire un fichier
				}
				else
				{
					printf("Erreur de lecture.\n");
				}
			}
		}
		else if (strcmp(cmd[0], "delete") == 0 && cmd[1] != NULL)
		{
			if (tablePTT != NULL)
			{
				int res = myDelete(cmd[1]); // Supprimer un fichier
				if (res == 0)
				{
					printf("Fichier %s supprimé avec succès.\n", cmd[1]);
				}
				else
				{
					printf("Erreur lors de la suppression du fichier.\n");
				}
			}
		}
		else if (strcmp(cmd[0], "mkdir") == 0 && cmd[1] != NULL)
		{
			myMkdir(cmd[1]); // Créer un répertoire
		}
		else if (strcmp(cmd[0], "rmdir") == 0 && cmd[1] != NULL)
		{
			myRmdir(cmd[1]); // Supprimer un répertoire
		}
		else if (strcmp(cmd[0], "link") == 0 && cmd[1] != NULL && cmd[2] != NULL)
		{
			myLink(cmd[1], cmd[2]); // Créer un lien symbolique
		}
		else if (strcmp(cmd[0], "help") == 0)
		{
			explication(); // Afficher l'aide
		}
		else if (strcmp(cmd[0], "exit") == 0)
		{
			loop = 0; // Quitter
		}
		else
		{
			printf("Commande invalide. Tapez 'help' pour obtenir la liste des commandes.\n");
		}
	}
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "projetOS.h"

/* Déclaration de variables globales */
TablePTT *tablePTT = NULL;	  // Table de fichiers de la partition
char cmdLine[1 + LINELENGTH]; // Ligne de commande
char *cmd[MAXWORDS];		  // Tableau de mots issus de la ligne de commande
int nWords;					  // Nombre de mots dans la commande

/**
 * Fonction principale de gestion du shell
 */
int main(void)
{
	int loop = 1; // Boucle principale
	while (loop && (nWords = readCmd()) >= 0)
	{
		// Interpréter la commande
		if (nWords == 0)
			continue; // S'il n'y a pas de commande, continuer la boucle

		if (strcmp(cmd[0], "format") == 0)
		{
			myFormat(cmd[1]);
		}
		else if (strcmp(cmd[0], "open") == 0)
		{
			if (tablePTT != NULL)
			{
				myOpen(cmd[1], tablePTT->ft);
			}
		}
		else if (strcmp(cmd[0], "write") == 0)
		{
			if (tablePTT != NULL)
			{
				File *f = getFile(tablePTT->ft, cmd[1]);
				if (f != NULL)
				{
					myWrite(f, cmd[2], strlen(cmd[2]));
				}
			}
		}
		else if (strcmp(cmd[0], "read") == 0)
		{
			if (tablePTT != NULL)
			{
				File *f = getFile(tablePTT->ft, cmd[1]);
				if (f != NULL)
				{
					char buffer[100];
					myRead(f, buffer, 100);
					printf("Contenu du fichier : %s\n", buffer);
				}
			}
		}
		else if (strcmp(cmd[0], "seek") == 0)
		{
			if (tablePTT != NULL)
			{
				File *f = getFile(tablePTT->ft, cmd[1]);
				if (f != NULL)
				{
					mySeek(f, atoi(cmd[2]), 0);
				}
			}
		}
		else if (strcmp(cmd[0], "delete") == 0)
		{
			if (tablePTT != NULL)
			{
				myDelete(cmd[1]);
			}
		}
		else if (strcmp(cmd[0], "mkdir") == 0)
		{
			myMkdir(cmd[1]);
		}
		else if (strcmp(cmd[0], "rmdir") == 0)
		{
			myRmdir(cmd[1]);
		}
		else if (strcmp(cmd[0], "link") == 0)
		{
			myLink(cmd[1], cmd[2]);
		}
		else if (strcmp(cmd[0], "exit") == 0)
		{
			loop = 0;
		}
		else
		{
			explication();
		}
	}
	return 0;
}

/**
 * Lit la commande entrée par l'utilisateur
 * @return Le nombre de mots dans la commande
 */
int readCmd(void)
{
	printf("> ");
	if (fgets(cmdLine, sizeof(cmdLine), stdin) == NULL)
	{
		return -1;
	}
	cmdLine[strcspn(cmdLine, "\n")] = 0; // Enlève le '\n' de la fin
	nWords = 0;
	char *word = strtok(cmdLine, " ");
	while (word != NULL)
	{
		cmd[nWords++] = word;
		word = strtok(NULL, " ");
	}
	return nWords;
}

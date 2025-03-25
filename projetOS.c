#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>	  // Pour mkdir
#include <sys/stat.h> // Pour mkdir
#include <fcntl.h>	  // Pour open
#include "projetOS.h"

// Définir les valeurs de taille et la structure TablePTT
#define LINELENGTH 1024
#define MAXWORDS 10

typedef struct
{
	FileTable *ft; // Table de fichiers (à ajuster selon la définition correcte)
} TablePTT;

// Fonction pour créer un répertoire
int myMkdir(const char *dirName)
{
	// Créer un répertoire avec des permissions par défaut (0777)
	if (mkdir(dirName, 0777) == 0)
	{
		printf("Répertoire créé avec succès : %s\n", dirName);
		return 0;
	}
	else
	{
		perror("Erreur lors de la création du répertoire");
		return -1;
	}
}

// Fonction pour créer un lien symbolique
int myLink(const char *source, const char *target)
{
	// Créer un lien symbolique entre source et target
	if (symlink(source, target) == 0)
	{
		printf("Lien symbolique créé : %s -> %s\n", source, target);
		return 0;
	}
	else
	{
		perror("Erreur lors de la création du lien symbolique");
		return -1;
	}
}

// Fonction pour lire une commande
int readCmd(void)
{
	// Exemple basique pour lire une ligne de commande
	char cmdLine[1 + LINELENGTH];
	printf("Entrez une commande : ");
	if (fgets(cmdLine, sizeof(cmdLine), stdin) != NULL)
	{
		// Si la ligne de commande est lue correctement, la traiter
		// Découper la ligne en mots et retourner le nombre de mots
		return 1; // Nombre de mots à ajuster selon votre logique
	}
	return -1; // En cas d'erreur
}

// Fonction pour ouvrir un fichier dans la table
void myOpen(char *filename, FileTable *ft)
{
	// Exemple de fonction d'ouverture de fichier
	// ft doit être une table de fichiers, à ajuster
	int fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("Erreur lors de l'ouverture du fichier");
	}
	else
	{
		printf("Fichier ouvert avec succès : %s\n", filename);
	}
}

// Fonction pour obtenir un fichier à partir de la table
File *getFile(FileTable *ft, char *filename)
{
	// Exemple de fonction pour récupérer un fichier dans une table de fichiers
	// Retourner un pointeur sur le fichier si trouvé
	return NULL; // À ajuster selon la logique de votre table
}

// Fonction principale pour traiter les commandes
int main()
{
	TablePTT *tablePTT = NULL;
	char *cmd[MAXWORDS];
	int nWords = 0;
	int loop = 1;

	// Exemple de boucle principale
	while (loop && (nWords = readCmd()) >= 0)
	{
		if (strcmp(cmd[0], "mkdir") == 0)
		{
			if (nWords >= 2)
			{
				myMkdir(cmd[1]);
			}
		}
		else if (strcmp(cmd[0], "link") == 0)
		{
			if (nWords >= 3)
			{
				myLink(cmd[1], cmd[2]);
			}
		}
		else if (strcmp(cmd[0], "open") == 0)
		{
			if (nWords >= 2)
			{
				myOpen(cmd[1], tablePTT->ft);
			}
		}
		else if (strcmp(cmd[0], "exit") == 0)
		{
			loop = 0;
		}
	}

	return 0;
}

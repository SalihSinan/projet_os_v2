#include "projetOS.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// Fonction pour créer un répertoire, compatible avec Windows
int myMkdir(char *dirName)
{
#ifdef __unix__
	if (mkdir(dirName, 0777) == 0)
#else
	if (mkdir(dirName) == 0)
#endif
	{
		printf("Répertoire créé : %s\n", dirName);
	}
	else
	{
		printf("Erreur de création du répertoire : %s\n", dirName);
	}
	return 0;
}

// Fonction pour créer un lien symbolique, compatible avec Windows/Unix
int myLink(char *source, char *target)
{
#ifdef __unix__
	if (symlink(source, target) == 0)
		printf("Lien symbolique créé de %s vers %s\n", source, target);
	else
		printf("Erreur de création du lien symbolique.\n");
#else
	printf("Les liens symboliques ne sont pas supportés sous Windows.\n");
#endif
	return 0;
}

// Fonction pour ouvrir un fichier, comme un `fopen`
File *getFile(void *ft, const char *fileName)
{
	File *file = malloc(sizeof(File));
	file->fd = open(fileName, O_RDWR | O_CREAT, 0777);
	if (file->fd == -1)
	{
		printf("Erreur à l'ouverture du fichier : %s\n", fileName);
		free(file);
		return NULL;
	}
	return file;
}

// Fonction pour écrire dans un fichier
int myWrite(File *file, const char *data, size_t dataSize)
{
	if (file == NULL || data == NULL)
	{
		printf("Erreur d'écriture : Fichier ou données invalides.\n");
		return -1;
	}

	int bytesWritten = write(file->fd, data, dataSize);
	if (bytesWritten < 0)
	{
		printf("Erreur lors de l'écriture du fichier.\n");
		return -1;
	}

	return bytesWritten;
}

// Fonction de lecture de fichier, maintenant avec size_t
int myRead(File *file, char *buffer, size_t bufferSize)
{
	if (file == NULL || buffer == NULL)
	{
		printf("Erreur de lecture : Fichier ou buffer invalide.\n");
		return -1;
	}

	int bytesRead = read(file->fd, buffer, bufferSize);
	if (bytesRead < 0)
	{
		printf("Erreur lors de la lecture du fichier.\n");
		return -1;
	}

	buffer[bytesRead] = '\0'; // Assurer que la chaîne est terminée par un '\0'
	return bytesRead;
}

// Fonction pour déplacer le curseur dans un fichier
int mySeek(File *file, int offset, int base)
{
	if (file == NULL)
	{
		printf("Erreur de seek : Fichier invalide.\n");
		return -1;
	}

	if (lseek(file->fd, offset, base) == -1)
	{
		printf("Erreur lors du déplacement du curseur.\n");
		return -1;
	}
	return 0;
}

// Fonction pour obtenir la taille d'un fichier
int size(File *file)
{
	if (file == NULL)
	{
		printf("Erreur de taille : Fichier invalide.\n");
		return -1;
	}

	struct stat fileStats;
	if (fstat(file->fd, &fileStats) == -1)
	{
		printf("Erreur lors de la récupération de la taille du fichier.\n");
		return -1;
	}

	return (int)fileStats.st_size;
}

// Fonction de formatage (ici simplifiée)
int myFormat(char *fileName)
{
	printf("Formatage du fichier : %s\n", fileName);
	return 0;
}

// Fonction pour supprimer un fichier
int myDelete(const char *fileName)
{
	if (remove(fileName) == 0)
	{
		printf("Fichier %s supprimé avec succès.\n", fileName);
		return 0;
	}
	else
	{
		printf("Erreur lors de la suppression du fichier : %s\n", fileName);
		return -1;
	}
}

// Fonction pour supprimer un répertoire
void myRmdir(const char *dirName)
{
#ifdef __unix__
	if (rmdir(dirName) == 0)
		printf("Répertoire supprimé : %s\n", dirName);
	else
		printf("Erreur de suppression du répertoire : %s\n", dirName);
#else
	printf("Les répertoires ne peuvent pas être supprimés sous Windows avec rmdir.\n");
#endif
}

// Fonction d'explication des commandes disponibles
void explication()
{
	printf("Liste des commandes disponibles :\n");
	printf("1. myformat <nom_fichier> : Formate un fichier.\n");
	printf("2. myopen <nom_fichier> : Ouvre un fichier.\n");
	printf("3. mywrite <nom_fichier> <données> : Écrit dans un fichier.\n");
	printf("4. myread <nom_fichier> <taille> : Lit un fichier.\n");
	printf("5. myseek <nom_fichier> <offset> <base> : Déplace le curseur.\n");
	printf("6. size <nom_fichier> : Affiche la taille d'un fichier.\n");
	printf("7. delete <nom_fichier> : Supprime un fichier.\n");
	printf("8. mkdir <nom_repertoire> : Crée un répertoire.\n");
	printf("9. rmdir <nom_repertoire> : Supprime un répertoire.\n");
	printf("10. link <source> <cible> : Crée un lien symbolique.\n");
	printf("11. exit : Quitte le programme.\n");
}

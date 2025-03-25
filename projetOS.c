/**
 * @file projetOS.c
 * @brief Implémentation des fonctionnalités du gestionnaire de fichiers
 * @author CHEBALLAH Jawed, Sinan, Samy
 * @date 2025
 */

#include "projetOS.h"

/**
 * @brief Crée une partition sous forme de fichier UNIX formaté
 * @param pttName Nom de la partition à créer
 * @return 0 en cas de succès, -1 en cas d'échec
 */
int myFormat(char *pttName)
{
	if (pttName == NULL)
	{
		printf("Nom de partition invalide.\n");
		return -1;
	}

	FILE *file = fopen(pttName, "wb");
	if (!file)
	{
		perror("Erreur lors de la création de la partition");
		return -1;
	}

	ftruncate(fileno(file), PTT_SIZE);
	fclose(file);
	printf("Partition %s créée avec succès.\n", pttName);
	return 0;
}

/**
 * @brief Crée un fichier dans la partition
 * @param fileName Nom du fichier
 * @param fileTable Table des fichiers
 * @return Pointeur vers le fichier créé ou NULL en cas d'échec
 */
File *myOpen(char *fileName, FileTable *fileTable)
{
	if (!fileTable)
		return NULL;

	for (int i = 0; i < fileTable->nbFile; i++)
	{
		if (strcmp(fileTable->table[i].nom, fileName) == 0)
		{
			printf("Fichier %s déjà existant.\n", fileName);
			return &fileTable->table[i];
		}
	}

	File *newFile = &fileTable->table[fileTable->nbFile++];
	strcpy(newFile->nom, fileName);
	newFile->posCurseurD = 0;
	newFile->posCurseurF = 0;
	printf("Fichier %s créé avec succès.\n", fileName);
	return newFile;
}

/**
 * @brief Supprime un fichier de la partition
 * @param fileName Nom du fichier à supprimer
 * @return 0 si succès, -1 sinon
 */
int myDelete(char *fileName)
{
	if (remove(fileName) == 0)
	{
		printf("Fichier %s supprimé.\n", fileName);
		return 0;
	}
	printf("Erreur lors de la suppression du fichier %s.\n", fileName);
	return -1;
}

/**
 * @brief Crée un répertoire dans la partition
 * @param dirName Nom du répertoire
 */
void myMkdir(char *dirName)
{
	if (mkdir(dirName, 0777) == 0)
	{
		printf("Répertoire %s créé avec succès.\n", dirName);
	}
	else
	{
		perror("Erreur lors de la création du répertoire");
	}
}

/**
 * @brief Supprime un répertoire vide
 * @param dirName Nom du répertoire à supprimer
 */
void myRmdir(char *dirName)
{
	if (rmdir(dirName) == 0)
	{
		printf("Répertoire %s supprimé avec succès.\n", dirName);
	}
	else
	{
		perror("Erreur lors de la suppression du répertoire");
	}
}

/**
 * @brief Crée un lien symbolique entre deux fichiers
 * @param source Fichier source
 * @param target Cible du lien
 */
void myLink(char *source, char *target)
{
	if (symlink(source, target) == 0)
	{
		printf("Lien %s -> %s créé avec succès.\n", target, source);
	}
	else
	{
		perror("Erreur lors de la création du lien");
	}
}

/**
 * @brief Recherche un fichier dans la table des fichiers
 * @param fileTable Table des fichiers
 * @param fileName Nom du fichier
 * @return Pointeur vers le fichier trouvé ou NULL
 */
File *getFile(FileTable *fileTable, char *fileName)
{
	if (!fileTable)
		return NULL;

	for (int i = 0; i < fileTable->nbFile; i++)
	{
		if (strcmp(fileTable->table[i].nom, fileName) == 0)
		{
			return &fileTable->table[i];
		}
	}
	return NULL;
}

/**
 * @brief Écrit dans un fichier
 * @param file Pointeur vers le fichier
 * @param buffer Données à écrire
 * @param size Taille des données à écrire
 * @return 0 en cas de succès, -1 en cas d'erreur
 */
int myWrite(File *file, const char *buffer, size_t size)
{
	if (!file)
		return -1;

	FILE *fp = fopen(file->nom, "a");
	if (!fp)
	{
		perror("Erreur lors de l'ouverture du fichier en écriture");
		return -1;
	}

	fwrite(buffer, sizeof(char), size, fp);
	fclose(fp);
	return 0;
}

/**
 * @brief Lit dans un fichier
 * @param file Pointeur vers le fichier
 * @param buffer Tampon de lecture
 * @param size Taille maximale à lire
 * @return Le nombre d'octets lus
 */
int myRead(File *file, char *buffer, size_t size)
{
	if (!file)
		return -1;

	FILE *fp = fopen(file->nom, "r");
	if (!fp)
	{
		perror("Erreur lors de l'ouverture du fichier en lecture");
		return -1;
	}

	int bytesRead = fread(buffer, sizeof(char), size, fp);
	fclose(fp);
	return bytesRead;
}

/**
 * @brief Déplace le curseur de lecture/écriture d'un fichier
 * @param file Pointeur vers le fichier
 * @param offset Décalage à appliquer
 * @param base Position de départ (SEEK_SET, SEEK_CUR, SEEK_END)
 */
void mySeek(File *file, int offset, int base)
{
	if (!file)
		return;

	FILE *fp = fopen(file->nom, "r+");
	if (!fp)
	{
		perror("Erreur lors de l'ouverture du fichier pour seek");
		return;
	}

	fseek(fp, offset, base);
	fclose(fp);
}

/**
 * @brief Retourne la taille d'un fichier
 * @param file Pointeur vers le fichier
 * @return Taille du fichier en octets
 */
int size(File *file)
{
	if (!file)
		return -1;

	FILE *fp = fopen(file->nom, "r");
	if (!fp)
	{
		perror("Erreur lors de l'ouverture du fichier pour obtenir sa taille");
		return -1;
	}

	fseek(fp, 0, SEEK_END);
	int fileSize = ftell(fp);
	fclose(fp);
	return fileSize;
}

/**
 * @brief Affiche l'aide pour les commandes
 */
void explication()
{
	printf("Commandes disponibles:\n");
	printf("- myformat <nom_partition> : Crée une nouvelle partition\n");
	printf("- myopen <nom_fichier> : Ouvre un fichier\n");
	printf("- mywrite <nom_fichier> <texte> : Écrit dans un fichier\n");
	printf("- myread <nom_fichier> <taille> : Lit un fichier\n");
	printf("- myseek <nom_fichier> <offset> <base> : Déplace le curseur dans le fichier\n");
	printf("- size <nom_fichier> : Affiche la taille d'un fichier\n");
	printf("- delete <nom_fichier> : Supprime un fichier\n");
	printf("- mkdir <nom_répertoire> : Crée un répertoire\n");
	printf("- rmdir <nom_répertoire> : Supprime un répertoire\n");
	printf("- link <source> <cible> : Crée un lien symbolique\n");
	printf("- help : Affiche cette aide\n");
	printf("- exit : Quitte le programme\n");
}

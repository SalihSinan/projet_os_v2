/**
 * @file projetOS.h
 * @brief Déclarations des fonctions et structures pour le gestionnaire de fichiers
 * @author Jawed CHEBALLAH, Sinan, Samy
 * @date 2025
 */

#ifndef PROJET_OS_H
#define PROJET_OS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>

// Définition de constantes
#define MAXWORDS 10    // Nombre maximal de mots dans une ligne de commande
#define LINELENGTH 100 // Longueur maximale d'une ligne de commande

// Structure de fichier
typedef struct
{
    char name[255];
    int size;
    int offset;
} File;

// Structure de la Table des Partitions de Table de Fichiers (TablePTT)
typedef struct
{
    char partitionName[255];
    int numFiles;
    File *ft; // Tableau de fichiers
} TablePTT;

// Déclaration des fonctions

/**
 * @brief Lit la commande entrée par l'utilisateur
 * @return Le nombre de mots dans la commande
 */
int readCmd(void);

/**
 * @brief Crée une partition de table de fichiers
 * @param partitionName Le nom de la partition à créer
 */
void myFormat(char *partitionName);

/**
 * @brief Ouvre un fichier dans la partition
 * @param fileName Le nom du fichier à ouvrir
 * @param ft La table de fichiers de la partition
 */
void myOpen(char *fileName, File *ft);

/**
 * @brief Écrit dans un fichier
 * @param file Le fichier dans lequel écrire
 * @param data Les données à écrire
 * @param size La taille des données à écrire
 * @return 0 si l'écriture réussie, sinon une erreur
 */
int myWrite(File *file, char *data, size_t size);

/**
 * @brief Lit un fichier
 * @param file Le fichier à lire
 * @param buffer Le tampon où stocker les données lues
 * @param size La taille du tampon
 * @return Le nombre d'octets lus
 */
int myRead(File *file, char *buffer, size_t size);

/**
 * @brief Déplace le curseur de lecture/écriture dans un fichier
 * @param file Le fichier dont on déplace le curseur
 * @param offset L'offset à partir duquel déplacer le curseur
 * @param base Base de l'offset (0: début, 1: actuel, 2: fin)
 */
void mySeek(File *file, int offset, int base);

/**
 * @brief Supprime un fichier
 * @param fileName Le nom du fichier à supprimer
 * @return 0 si la suppression réussie, sinon une erreur
 */
int myDelete(char *fileName);

/**
 * @brief Crée un répertoire
 * @param dirName Le nom du répertoire à créer
 */
void myMkdir(char *dirName);

/**
 * @brief Supprime un répertoire
 * @param dirName Le nom du répertoire à supprimer
 */
void myRmdir(char *dirName);

/**
 * @brief Crée un lien symbolique entre deux fichiers
 * @param source Le fichier source
 * @param target Le fichier cible
 */
void myLink(char *source, char *target);

/**
 * @brief Affiche l'explication des commandes disponibles
 */
void explication(void);

/**
 * @brief Récupère un fichier depuis une table de fichiers
 * @param ft La table des fichiers
 * @param fileName Le nom du fichier
 * @return Le fichier trouvé, ou NULL si non trouvé
 */
File *getFile(File *ft, char *fileName);

/**
 * @brief Retourne la taille d'un fichier
 * @param file Le fichier dont on veut obtenir la taille
 * @return La taille du fichier
 */
int size(File *file);

#endif // PROJET_OS_H

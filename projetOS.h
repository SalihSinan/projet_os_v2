#ifndef PROJETOS_H
#define PROJETOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// Définition des structures

/**
 * @struct File
 * @brief Structure représentant un fichier
 *
 * Cette structure contient un descripteur de fichier (fd) qui sera utilisé pour gérer les fichiers ouverts.
 */
typedef struct
{
    int fd; ///< Descripteur du fichier
} File;

// Déclaration des fonctions

/**
 * @brief Crée un répertoire.
 *
 * Cette fonction crée un répertoire avec les droits d'accès spécifiés.
 * @param dirName Nom du répertoire à créer.
 * @return 0 si la création a réussi, sinon une valeur négative.
 */
int myMkdir(char *dirName);

/**
 * @brief Crée un lien symbolique entre deux fichiers.
 *
 * Cette fonction crée un lien symbolique entre le fichier source et le fichier cible.
 * @param source Fichier source.
 * @param target Fichier cible pour le lien symbolique.
 * @return 0 si le lien symbolique a été créé avec succès, sinon une valeur négative.
 */
int myLink(char *source, char *target);

/**
 * @brief Ouvre un fichier et retourne un pointeur vers la structure File correspondante.
 *
 * Cette fonction ouvre un fichier spécifié et retourne un pointeur vers la structure `File` qui contient le descripteur de fichier.
 * @param ft Table des fichiers ouverts.
 * @param fileName Nom du fichier à ouvrir.
 * @return Pointeur vers une structure `File` contenant le descripteur de fichier, ou NULL si l'ouverture échoue.
 */
File *getFile(void *ft, const char *fileName);

/**
 * @brief Écrit dans un fichier.
 *
 * Cette fonction écrit des données dans un fichier ouvert.
 * @param file Pointeur vers la structure `File` représentant le fichier.
 * @param data Données à écrire dans le fichier.
 * @param dataSize Taille des données à écrire.
 * @return 0 si l'écriture a réussi, sinon une valeur négative.
 */
int myWrite(File *file, const char *data, size_t dataSize);

/**
 * @brief Lit des données d'un fichier.
 *
 * Cette fonction lit les données à partir d'un fichier ouvert et les stocke dans un tampon.
 * @param file Pointeur vers la structure `File` représentant le fichier.
 * @param buffer Tampon dans lequel les données seront lues.
 * @param bufferSize Taille du tampon.
 * @return Le nombre d'octets lus, ou une valeur négative en cas d'erreur.
 */
int myRead(File *file, char *buffer, size_t bufferSize);

/**
 * @brief Déplace le curseur d'un fichier ouvert à un offset spécifique.
 *
 * Cette fonction déplace le curseur de lecture/écriture d'un fichier à un offset spécifié par rapport à une base donnée.
 * @param file Pointeur vers la structure `File` représentant le fichier.
 * @param offset Décalage par rapport à la base.
 * @param base Base à partir de laquelle le décalage est appliqué.
 * @return 0 si le déplacement a réussi, sinon une valeur négative.
 */
int mySeek(File *file, int offset, int base);

/**
 * @brief Retourne la taille d'un fichier.
 *
 * Cette fonction retourne la taille d'un fichier en octets.
 * @param file Pointeur vers la structure `File` représentant le fichier.
 * @return Taille du fichier en octets, ou une valeur négative en cas d'erreur.
 */
int size(File *file);

/**
 * @brief Formate un fichier en tant que partition.
 *
 * Cette fonction initialise un fichier comme une partition vide prête à être utilisée.
 * @param fileName Nom du fichier à formater.
 * @return 0 si le formatage a réussi, sinon une valeur négative.
 */
int myFormat(char *fileName);

/**
 * @brief Supprime un fichier.
 *
 * Cette fonction supprime un fichier spécifié.
 * @param fileName Nom du fichier à supprimer.
 * @return 0 si la suppression a réussi, sinon une valeur négative.
 */
int myDelete(const char *fileName);

/**
 * @brief Supprime un répertoire.
 *
 * Cette fonction supprime un répertoire vide.
 * @param dirName Nom du répertoire à supprimer.
 */
void myRmdir(const char *dirName);

/**
 * @brief Affiche l'aide pour les commandes disponibles.
 *
 * Cette fonction affiche une liste des commandes disponibles avec une brève description de chaque commande.
 */
void explication();

#endif // PROJETOS_H

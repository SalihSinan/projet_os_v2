/**
 * @file projetOS.h
 * @brief Fichier d'en-tête du gestionnaire de fichiers
 * @author CHEBALLAH Jawed, Sinan, Samy
 * @date 2025
 */

 #ifndef PROJETOS_H_
 #define PROJETOS_H_
 
 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <sys/types.h>
 #include <sys/stat.h>
 #include <fcntl.h>
 #include <errno.h>
 #include <string.h>
 
 #define PTT_SIZE 1000
 #define MAX_FILES 100
 #define LINELENGTH 255
 #define MAXWORDS LINELENGTH / 2
 
 /**
  * @brief Structure représentant un fichier dans la partition
  */
 typedef struct {
     char nom[25];                  ///< Nom du fichier
     off_t posCurseurD;             ///< Position du curseur de début
     off_t posCurseurF;             ///< Position du curseur de fin
 } File;
 
 /**
  * @brief Structure représentant la table des fichiers dans la partition
  */
 typedef struct {
     char *PTT_PATH;  ///< Chemin du fichier représentant la partition
     File table[MAX_FILES]; ///< Tableau des fichiers
     int nbFile;      ///< Nombre de fichiers
 } FileTable;
 
 /**
  * @brief Structure représentant une liste de partitions
  */
 typedef struct tPTT {
     FileTable *ft;
     struct tPTT *next;
 } TablePTT;
 
 extern TablePTT *tablePTT;
 extern char cmdLine[];
 extern char *cmd[];
 
 /**
  * @brief Formate une partition
  * @param pttName Nom de la partition
  * @return 0 si succès, -1 sinon
  */
 int myFormat(char *pttName);
 
 /**
  * @brief Crée ou ouvre un fichier
  * @param fileName Nom du fichier
  * @param fileTable Table des fichiers
  * @return Pointeur vers le fichier
  */
 File *myOpen(char *fileName, FileTable *fileTable);
 
 /**
  * @brief Supprime un fichier
  * @param fileName Nom du fichier
  * @return 0 si succès, -1 sinon
  */
 int myDelete(char *fileName);
 
 /**
  * @brief Crée un répertoire
  * @param dirName Nom du répertoire
  */
 void myMkdir(char *dirName);
 
 /**
  * @brief Supprime un répertoire vide
  * @param dirName Nom du répertoire
  */
 void myRmdir(char *dirName);
 
 /**
  * @brief Crée un lien symbolique
  * @param source Fichier source
  * @param target Cible du lien
  */
 void myLink(char *source, char *target);
 
 #endif /* PROJETOS_H_ */
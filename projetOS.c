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
 int myFormat(char *pttName) {
	 if (pttName == NULL) {
		 printf("Nom de partition invalide.\n");
		 return -1;
	 }
	 
	 FILE *file = fopen(pttName, "wb");
	 if (!file) {
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
 File *myOpen(char *fileName, FileTable *fileTable) {
	 if (!fileTable) return NULL;
	 
	 for (int i = 0; i < fileTable->nbFile; i++) {
		 if (strcmp(fileTable->table[i].nom, fileName) == 0) {
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
 int myDelete(char *fileName) {
	 if (remove(fileName) == 0) {
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
 void myMkdir(char *dirName) {
	 if (mkdir(dirName, 0777) == 0) {
		 printf("Répertoire %s créé avec succès.\n", dirName);
	 } else {
		 perror("Erreur lors de la création du répertoire");
	 }
 }
 
 /**
  * @brief Supprime un répertoire vide
  * @param dirName Nom du répertoire à supprimer
  */
 void myRmdir(char *dirName) {
	 if (rmdir(dirName) == 0) {
		 printf("Répertoire %s supprimé avec succès.\n", dirName);
	 } else {
		 perror("Erreur lors de la suppression du répertoire");
	 }
 }
 
 /**
  * @brief Crée un lien symbolique entre deux fichiers
  * @param source Fichier source
  * @param target Cible du lien
  */
 void myLink(char *source, char *target) {
	 if (symlink(source, target) == 0) {
		 printf("Lien %s -> %s créé avec succès.\n", target, source);
	 } else {
		 perror("Erreur lors de la création du lien");
	 }
 }
 
// Carnet de notes -  Gestion de liste



#include "fiche.h"

#define _CRT_SECURE_NO_WARNINGS   // pour les warnings par rapport � strcpy

//D�finition des bibliotheques dont on aura besoin dans tout le code
#include <stdio.h>
#include <string.h>
#include <malloc.h>


void printFiche(FICHE fiche)
{
  printf("\n----CARNET DE L'ETUDIANT-----\n");
  printf("Nom :\t%s\t\n", fiche.name);
  printf("Prenom\t:%s\n", fiche.surname);
  printf("Id :\t%u\t\n", fiche.id);

  printf("Matieres:\n");
  for (int i = 0; i < taille; i++) {
    printf(" %-10s : %5.2lf\n", fiche.tab[i].title, fiche.tab[i].score);
    //printf(" %-lf\n", fiche.tab[i].score);
  }

}

/*fonction qui ajoute un fiche a la fin de la liste*/
void appendToList(LIST* list, FICHE fiche)
{
  // Cr�er un nouveau n�ud pour la nouvelle fiche
  NODE* newNode = (NODE*)malloc(sizeof(NODE));
  newNode->file = fiche;
  newNode->next = NULL;

  // Ajouter le nouveau n�ud � la fin de la liste
  if (list->head == NULL) {
    // Si la liste est vide, le nouveau n�ud est le premier et le dernier
    newNode->prev = NULL;
    list->head = newNode;
    list->tail = newNode;
  }
  else {
    // Sinon, ajouter le nouveau n�ud apr�s le dernier n�ud
    newNode->prev = list->tail;
    list->tail->next = newNode;
    list->tail = newNode;
  }
}


//fonction qui affiche une liste passer en argument
void printList(LIST list) {
  int cpt = 1; // variable qui compte de nombre de fiche contenu dans la liste
  // Parcourir la liste � partir de la t�te
  NODE* current = list.head;
  while (current != NULL)
  {
    printf("FICHE # %d\n", cpt);
    // Afficher les donn�es de chaque n�ud
    printf("Nom\t: %s\n", current->file.name);
    printf("Prenom\t: %s\n", current->file.surname);
    printf("Id\t: %d\n", current->file.id);
    printf("Matieres : \n");
    for (int i = 0; i < 3; i++)
    {
      if (strlen(current->file.tab[i].title) > 0) {
        printf(" %-10s : %5.2lf\n", current->file.tab[i].title, current->file.tab[i].score);
      }
    }
    printf("\n");

    // Passer au n�ud suivant

    current = current->next;
    cpt++;

  }
}


/*fonction qui retire une fiche de la liste a partir de son id entr� en parametre*/
FICHE removeFromList(LIST* list, int id)
{
  NODE* current = list->head;

  while (current != NULL)
  {
    if (current->file.id == id)
    {
      // On retrouve le noeud grace � l'ID, on le retire de la liste
      FICHE fiche = current->file;

      if (current->prev == NULL)
      {
        // Premier noeud de la liste
        list->head = current->next;
      }
      else
      {
        current->prev->next = current->next;
      }

      if (current->next == NULL)
      {
        // Dernier noeud de la liste
        list->tail = current->prev;
      }
      else
      {
        current->next->prev = current->prev;
      }

      free(current);
      return fiche;
    }

    current = current->next;
  }

  // Pas de noeud correspondant, on retourne une fiche vide
  FICHE empty_fiche = { "", "", 0, {{"", 0}, {"", 0}, {"", 0}} };
  printf("la liste ne contient pas cet etudiant \n");
  return empty_fiche;
}


/*fonction qui lit toutes les lignes du fichier file et retourne la liste contenant les fiches */
LIST loadList(FILE* file) {
  LIST list = { NULL, NULL };
  FICHE fiche = { "","" ,0 ,
 {{"" ,0} ,{"" ,0} ,{"" ,0}} };;
  char line[SIZE];
  char* token;
  int i;
  while (fgets(line, SIZE, file) != NULL) {
    // Parsing de la ligne pour extraire les informations de la fiche
    token = strtok(line, ";");
    strcpy(fiche.name, token);
    token = strtok(NULL, ";");
    strcpy(fiche.surname, token);
    token = strtok(NULL, ";");
    fiche.id = atoi(token);
    for (i = 0; i < 3; i++) {
      token = strtok(NULL, ";");
      strcpy(fiche.tab[i].title, token);
      token = strtok(NULL, ";");
      fiche.tab[i].score = atof(token);
    }

    // Ajout de la fiche a la fin de la liste
    appendToList(&list, fiche);
  }
  return list;
}

/*fonction qui sauvegarde les fiches de la liste au format ascii dans le fichier.*/
void saveList(FILE* file, LIST list) {
  NODE* current = list.head;
  int i;

  while (current != NULL) {
    // Ecriture de la fiche dans le fichier
    fprintf(file, "%s;%s;%d", current->file.name, current->file.surname, current->file.id);
    for (i = 0; i < 3; i++) {
      fprintf(file, ";%s;%.1f", current->file.tab[i].title, current->file.tab[i].score);
    }
    fprintf(file, "\n");

    current = current->next;
  }
}

//Question a
//Ins�re la fiche dans la liste � sa place, par ordre de num�ro id croissant.
void insertInList(LIST* list, FICHE fiche) 
{
  NODE* newNode = malloc(sizeof(NODE));
  newNode->file = fiche;
  newNode->prev = NULL;
  newNode->next = NULL;

  //La liste est vide
  if (list->head == NULL && list->tail == NULL) {
    list->head = newNode;
    list->tail = newNode;
    return;
  }
  //la fiche est ins�r�e en d�but de liste
  if (fiche.id < list->head->file.id) {
    newNode->next = list->head;
    list->head->prev = newNode;
    list->head = newNode;
    return;
  }
  // Parcourir la liste pour trouver l'emplacement o� ins�rer la fiche
  NODE* current = list->head;
  while (current != NULL) {
    if (fiche.id == current->file.id) {
      printf("Erreur : une fiche avec cet id existe d�j�\n");
      return;
    }
    if (fiche.id > current->file.id && (current->next == NULL || fiche.id < current->next->file.id)) {
      newNode->next = current->next;
      if (current->next != NULL) {
        current->next->prev = newNode;
      }
      else {
        list->tail = newNode;
      }
      current->next = newNode;
      newNode->prev = current;
      return;
    }
    current = current->next;
  }
}


//Question b
/*fonction qui aide a stocker les informations entrer par l'utilisateur dans une fiche*/
FICHE ficheFromInput(void)
{
  FICHE etudiant = { "", "", 0, {{"", 0.0}, {"", 0.0}, {"", 0.0}} };

  printf("Entrer le nom de l'etudiant : ");
  fgets(etudiant.name, SIZE, stdin);
  etudiant.name[strcspn(etudiant.name, "\n")] = '\0';
  setName2(&etudiant, etudiant.name);

  printf("\nEntrer le prenom de l'etudiant : ");
  fgets(etudiant.surname, SIZE, stdin);
  setSurname(&etudiant, etudiant.surname);

  etudiant.surname[strcspn(etudiant.surname, "\n")] = '\0';
  printf("\nEntrer l'id de l'etudiant: ");
  char idStr[SIZE] = { 0 };
  fgets(idStr, SIZE, stdin);
  setID(&etudiant, atof(idStr));
  //etudiant.id = atof(idStr);

  printf("\nVeuillez entrer 3 cours suivis par l'etudiant et les notes associees\n");
  for (int i = 0; i < taille; i++)
  {
    etudiant.tab[i] = courseFromInput();
  }
  return etudiant;
}


/*fonction pour stocker le champs tab de l'etudiant */
COURSE courseFromInput(void)
{
  COURSE cours = { "", 0 };

  printf("Intitule du cours : ");
  fgets(cours.title, SIZE, stdin);
  cours.title[strcspn(cours.title, "\n")] = '\0';  // Supprimer le caract�re '\n' � la fin de la cha�ne
  setTitle(&cours, cours.title);

  printf("\Note obtenue: ");
  char scoreStr[SIZE] = { 0 };
  fgets(scoreStr, SIZE, stdin);
  setScore(&cours, atof(scoreStr));

  return cours;
}


// Fonction qui permet de sauvegarder dans un fichier les �l�ments entr�s par un utilisateur
void saveFiche(FILE* file, FICHE fiche)
{
  if (file == NULL)
  {
    fprintf(stderr, " le fichier est vide");
    return;
  }
  else
  {
    int i;
    fprintf(file, "%s;%s;%u", getName(&fiche), getSurname(&fiche), getID(&fiche));
    for (i = 0; i < taille; i++)
      fprintf(file, ";%s;%f", getTitle(&fiche.tab[i]), getScore(&fiche.tab[i]));
    fprintf(file, "\n");
  }
}


void load_fiche(FICHE* fiche, char* str)
{
  char* token;
  int i;

  token = strtok(str, ";");
  if (token != NULL) {
    setName(fiche, str);

  }

  token = strtok(NULL, ";");
  if (token != NULL) {
    setSurname(fiche, token);

  }

  token = strtok(NULL, ";");
  if (token != NULL) {
    setID(fiche, atoi(token));
  }

  for (i = 0; i < taille; i++) {
    token = strtok(NULL, ";");
    if (token != NULL) {
      setTitle(&fiche->tab[i], token);
    }
    else {
      break;
    }

    token = strtok(NULL, ";");
    if (token != NULL) {
      setScore(&(fiche->tab[i]), atof(token));
    }
    else {
      break;
    }
  }
}

void menu()
{

  printf("Menu:\n");
  printf("[1] Ajouter et afficher une fiche\n");
  printf("[2] Supprimer la fiche\n");
  printf("[3] Sauvegarder la fiche\n");
  printf("[4] Quitter\n");
  printf("Votre Choix: ");
}


const char* getName(FICHE* pfichier)
{
  if (pfichier == NULL) {
    fprintf(stderr, "erreur:fichier vide \n");
    return 0;
  }
  return pfichier->name;
}

//Fonction pour que le nom soit toujours stock� et affich� en majuscule
void setName2(FICHE* fiche, STRING name2)
{
  int j = 0;
  char* new_name2;

  if (name2 != '\0')
  {
    // Allocation de m�moire pour la chaine modifiable
    new_name2 = malloc(strlen(name2) + 1);

    if (new_name2 != NULL)
    {
      // Copie de la chaine constante dans la chaine modifiable
      strcpy(new_name2, name2);
      while (new_name2[j] != '\0')
      {
        if (new_name2[j] >= 'a')
        {
          new_name2[j] = (name2[j] - 32); // Car le code ASCII d�une lettre en majuscule est le code de la lettre en minuscule moins 32
        }
        j++;
      }
      strcpy(fiche->name, new_name2, SIZE);
    }
  }
  else
  {
    printf("\n Erreur: Le fichier est vide");
  }
}

const char* getSurname(FICHE* pfichier)
{
  if (pfichier == NULL) {
    fprintf(stderr, "erreur:fichier vide \n");
    return 0;
  }
  return pfichier->surname;
}

int getID(FICHE* pfichier)
{
  if (pfichier == NULL) {
    fprintf(stderr, "erreur:fichier vide \n");
    return 0;
  }
  return pfichier->id;
}

const char* getTitle(COURSE* pfichier)
{
  if (pfichier == NULL) {
    fprintf(stderr, "erreur:fichier vide \n");
    return 0;
  }
  return pfichier->title;
}

const float getScore(COURSE* pfichier)
{
  if (pfichier == NULL) {
    fprintf(stderr, "erreur:fichier vide \n");
    return 0;
  }
  return pfichier->score;
}

COURSE getcourse(FICHE* pfichier, int n)
{
  return pfichier->tab[n];
}

void setName(FICHE* pfichier, char str[SIZE])
{

  if (pfichier == NULL)
  {
    fprintf(stderr, "la fiche est vide :");
    return;
  }
  char chaine[SIZE];
  strcpy(chaine, str);
  int i = 0;
  for (i = 0; chaine[i] != '\0'; i++)
  {
    if (chaine[i] >= 'a' && chaine[i] <= 'z')
      chaine[i] -= 'a' - 'A';
  }

  strncpy(pfichier->name, chaine, SIZE);
}

void setSurname(FICHE* pfichier, char* str)
{
  if (pfichier == NULL) {
    fprintf(stderr, "erreur:fichier vide \n");
    return;
  }
  strncpy(pfichier->surname, str, SIZE);
}

void setID(FICHE* pfichier, unsigned int ID)
{
  if (pfichier == NULL) {
    fprintf(stderr, "erreur:fichier vide \n");
    return;
  }
  pfichier->id = ID;
}

void setCourse(FICHE* pfichier, COURSE course, int n)
{
  if (pfichier == NULL) {
    fprintf(stderr, "erreur:fichier vide \n");
    return;
  }
  pfichier->tab[n] = course;
}

void setTitle(COURSE* pcourse, char* str)
{
  if (pcourse == NULL) {
    fprintf(stderr, "erreur:fichier vide \n");
    return;
  }
  char chaine[SIZE];
  strcpy(chaine, str);
  int i = 0;
  for (i = 0; chaine[i] != '\0'; i++)
  {
    if (chaine[i] >= 'a' && chaine[i] <= 'z')
      chaine[i] -= 'a' - 'A';
  }
  strncpy(pcourse->title, chaine, SIZE);
}

void setScore(COURSE* pcourse, float n)
{
  if (pcourse == NULL) {
    fprintf(stderr, "erreur:fichier vide \n");
    return;
  }
  pcourse->score = n;
}

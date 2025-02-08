// SANGANG DCHYMKOU Ornella
// N° étudiant: 12311483
// Carnet de notes -  Gestion de liste
// 27/02/2024


#define _CRT_SECURE_NO_WARNINGS   // pour les warnings par rapport à strcpy

//Définition des bibliotheques dont on aura besoin dans tout le code
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef const char* STRING;


//definition des macros
#define SIZE 80 
#define taille 3 

//Définition des structures et de leurs allias
typedef struct _COURSE {
  char title[SIZE];
  double score;
} COURSE;

typedef struct _FICHE {
  char name[SIZE];
  char surname[SIZE];
  unsigned int id;
  COURSE tab[taille];
} FICHE;




//declaration de la liste doublement chainée
typedef struct _NODE {
  FICHE file;
  struct _NODE* next;
  struct _NODE* prev;
} NODE;

typedef struct _LIST {
  NODE* head;
  NODE* tail;
} LIST;


//Déclaration des fonctions 
void printFiche(FICHE fiche);
void saveFiche(FILE* file, FICHE fiche);
void load_fiche(FICHE* fiche, char* str);
const char* getName(FICHE* pfichier);
const char* getSurname(FICHE* pfichier);
unsigned int getID(FICHE* pfichier);
const char* getTitle(COURSE* pfichier);
const float getScore(COURSE* pfichier);
COURSE getcourse(FICHE* pfichier, int n);
void setName(FICHE* pfichier, char str[SIZE]);
void setName2(FICHE* fiche, STRING name2);
void setSurname(FICHE* pfichier, char* str);
void setID(FICHE* pfichier, unsigned int ID);
void setCourse(FICHE* pfichier, COURSE course, int n);
void setTitle(COURSE* pcourse, char* str);
void setScore(COURSE* pcourse, float n);
//fonctions teste
void exo1(void);
void exo2(void);
void exo3(void);
void exo4(void);
void exo5(void);
void questiona(void);
void questionb(void);

//declaration des differentes fonctions utiliser
void printFiche(FICHE fiche);
void appendToList(LIST* list, FICHE fiche);
void printList(LIST list);
FICHE removeFromList(LIST* list, int id);
LIST loadList(FILE* file);
void saveList(FILE* file, LIST list);
void insertInList(LIST* list, FICHE fiche);
FICHE ficheFromInput(void);
COURSE courseFromInput(void);
void menu();

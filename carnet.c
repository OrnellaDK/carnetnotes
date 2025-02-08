// Carnet de notes -  Gestion de liste


#include "fiche.h"
#include <malloc.h>

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//fonction principale
int main(void)
{
  exo1();
  exo2();
  exo3();
  exo4();
  exo5();
  questiona();
  questionb();
  return 0;



  return EXIT_SUCCESS;
}


void exo1(void)
{
  printf("\n******************************************************\n");
  printf("**                  QUESTION 1                      **\n");
  printf("******************************************************\n");

  printf("Rien a afficher!\n");
}




/*teste de la fonction appendToList qui ajoute la fiche dans la liste*/
void exo2(void)
{
  printf("\n******************************************************\n");
  printf("**                  QUESTION 2                      **\n");
  printf("******************************************************\n");

  FICHE etudiant_1 = { " Marc "," Joseph " ,1123455 ,{{" Maths " ,16.0} ,{" Info " ,9.5} ,{" Physics " ,14.0}}};
  LIST list = { NULL, NULL };
  printf("Test de la fonction appendToList...\n");
  printf("Rien a afficher, mais vous pouvez voir sur la liste dans Visual Studio !\n ");
  printf("(Ne pas oublier d'utiliser un point de rupture !)\n ");
  appendToList(&list, etudiant_1);
  //printList(list);
}

/*teste de la fonction printList avec une fiche contenant 3 fiche initialiser avec la fonction appendToList*/
void exo3(void)
{
  printf("\n******************************************************\n");
  printf("**                  QUESTION 3                      **\n");
  printf("******************************************************\n");

  FICHE etudiant_1 = { " Doe "," John " ,115 ,{{" Maths " ,12.0} ,{" Info " ,15.5} ,{" Physics " ,12.75}} };
  FICHE etudiant_2 = { " David "," Marco " ,27 ,{{" Maths " ,17.0} ,{" Info " ,18.5} ,{" Physics " ,10.0}} };
  FICHE etudiant_3 = { " Smith "," Eric " ,33 ,{{" Maths " ,5.5} ,{" Info " ,20.0} ,{" Physics " ,11.0}} };
  LIST list = { NULL , NULL };

  printf(" Test de la fonction printList avec une liste de 3 etudiants \n");
  appendToList(&list, etudiant_1);
  appendToList(&list, etudiant_2);
  appendToList(&list, etudiant_3);
  //printf(" List initiale :\n");
  printList(list);

}

/*On teste de la fonction removeFromList pour different cas*/
void exo4(void)
{
  printf("\n******************************************************\n");
  printf("**                  QUESTION 4                      **\n");
  printf("******************************************************\n");

  FICHE etudiant_1 = { " Doe "," John " ,115 ,
 {{" Maths " ,12.0} ,{" Info " ,8.5} ,{" Physics " ,10.0}} };
  FICHE etudiant_2 = { " David "," Marco " ,27 ,
  {{" Maths " ,16.0} ,{" Info " ,15.5} ,{" Physics " ,11.75}} };
  FICHE etudiant_3 = { " Smith "," Eric " ,33 ,
  {{" Maths " ,13.0} ,{" Info " ,12.25} ,{" Physics " ,8.5}} };
  FICHE tmp = { "","" ,0 ,{{"" ,0} ,{"" ,0} ,{"" ,0}} };
  LIST list = { NULL , NULL };
  appendToList(&list, etudiant_1);
  appendToList(&list, etudiant_2);
  appendToList(&list, etudiant_3);
  printf(" Liste initiale :\n");
  printList(list);
  printf("\n\n");

  // Enlever un element non existant
  tmp = removeFromList(&list, 335);
  printFiche(tmp);

  // Enlever l'element du milieu
  tmp = removeFromList(&list, 27);
  printf("Retrait de l'element du milieu\n");
  printFiche(tmp); // affiche la fiche
  printList(list); // affiche la liste
  printf("\n\n");

  // Enlever le premier element
  printf("Retrait du premier element\n");
  tmp = removeFromList(&list, 115);
  printFiche(tmp); // affiche la fiche
  printList(list); // affiche la liste

  // Enlever le dernier element
  printf("Retrait du dernier element\n");
  tmp = removeFromList(&list, 33);
  printFiche(tmp); // affiche la fiche
  printList(list); // affiche la liste
  printf("\n\n");

  // Liste vide
  printf("Liste vide\n");
  printf("Test de retrait sur une liste vide\n");
  tmp = removeFromList(&list, 115);
  printFiche(tmp); // affiche la fiche
  printList(list); // affiche la liste
  printf("\n\n");
}


/*test de la fonction loadList et saveList*/
void exo5(void)
{
  printf("\n******************************************************\n");
  printf("**                  QUESTION 5                      **\n");
  printf("******************************************************\n");

  FILE* file = fopen("database.csv", "r");
  if (file == NULL)
  {
    fprintf(stderr, "erreur lors de l'ouerture du fichier \n");
    return;
  }

  LIST list2 = { NULL , NULL };
  printf("\n");
  list2 = loadList(file);
  saveList(stdout, list2);
  printf("\n");
  printList(list2);
}



void questiona(void)
{
  printf("\n******************************************************\n");
  printf("**                  QUESTION a                      **\n");
  printf("******************************************************\n");

  FILE* file = fopen("database.csv", "r");
  if (file == NULL)
  {
    fprintf(stderr, "erreur lors de l'ouerture du fichier \n");
    return;
  }

  LIST list2 = { NULL , NULL };
  printf("\n");
  list2 = loadList(file);
  saveList(stdout, list2);
  printf("\n");
  printList(list2);
  //teste de la fonction insertInlist
  FICHE etudiant_2 = { " Ben "," Manon " ,42 ,
  {{" Maths " ,12.0} ,{" Info " ,8.5} ,{" Physics " ,10.0}} };
  insertInList(&list2, etudiant_2);
  printf("Apres l'ajout on a :\n");
  printf("\n\n");

  printList(list2);
}


void questionb(void)
{
  printf("\n******************************************************\n");
  printf("**                  QUESTION b                      **\n");
  printf("******************************************************\n");
  int choix = 0;
  do
  {
    menu();
    scanf("%d", &choix);
    getchar(); // Consomme le retour à la ligne
    FICHE fiche = { "", "", 0, {{"", 0.0}, {"", 0.0}, {"", 0.0}} };
    FILE* fichier = fopen("database2.csv", "w");//On ouvre le fichier database2.csv

    switch (choix)
    {
    case 1:
      fiche = ficheFromInput();
      printFiche(fiche);
      break;
    case 2:
      ficheFromInput;
      printf("Fiche supprimeE\n");
      break;
    case 3:
      saveFiche(fichier, fiche);
      printf("Fiche sauvegardee\n");
      break;
    case 4:
      printf("Fin du programme.\n");
      break;
    default:
      printf("Choix invalide. Veuillez saisir un nombre entre 1 et 5.\n");
      break;
    }
  } while (choix != 4);
}






#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

char
option(char opt)
{
    switch (opt) {
    case 'o': return (opt);
    default :
        printf("L'argument n'est pas valide. \n");
        exit(1);
    }
}

int main(int argc, char **argv)
{
    /*Déclaration des variables*/
    DIR * repertoire;
    char * chemin;
    char opt;
    struct stat file_stat;
    char * buffer = NULL;
    int taille;

/*Vérification de s'il y a un argument ou pas*/
    if (argc < 2) {
        printf("il faut indiquer un chemin\n");
        return (1);
    }

/*Si il y un argument, on l'affiche*/
    chemin = argv[1];

/* Capture d'un troisième argument*/
    if (argc == 3){
        opt = option(*argv[2]);

    }

    if(argc > 3){
        printf("Il y a trop d'arguments. 2 arguments maximum : Chemin + Option. \n");
        return (1);
    }

/* Vérification du chemin entré en argument*/
    repertoire = opendir(chemin);

    if(repertoire != NULL){

        printf("Liste des fichiers et dossiers du chemin : %s\n", chemin);

        /*Vérification des fichiers contenu dans le répertoire*/
        struct dirent * structTest;

        while((structTest = readdir(repertoire)) != NULL){
            if(opt == 'o'){
                taille = strlen(argv[1]) + 1 + structTest->d_namlen + 1;
                buffer = malloc(taille);
                strcpy(buffer,argv[1]);
                strcat(buffer,structTest->d_name);
                int laStat = stat(buffer, &file_stat);
                free(buffer);

                if (laStat != 0){
                    printf("Erreur2. \n");
                    return(1);
                }else{
                    printf("%u\t%u\t%u\t%u\t", file_stat.st_nlink,
                  file_stat.st_uid, file_stat.st_gid, file_stat.st_size);
                }

            }
             printf("- %s\n", structTest->d_name);
        }
        closedir(repertoire);
    }
    else{
        printf("Le chemin n'existe pas.\n");
        return (1);
    }

    return 0;
}

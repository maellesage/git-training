#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>


char
checkOption(char optionATester) {
    switch (optionATester) {
    case 'l': return (optionATester);
    default:
        printf("L'option autorise est l.\n");
        exit(1);
    }
}

int
main(int argc, char **argv)
{
    int i = 0;
    DIR *rep;
    struct stat maStat;
    struct dirent *structRep;
    char option;

    /* On vérifie qu'un argument est passé dans l'appel du programme. */
    if (argc < 2) {
        printf("Il est necessaire de specifier un chemin\n");
        return (1);
    }

    /* On limite le nombre d'argument a passer. */
    if (argc > 3) {
        printf("La commande est limitee a 2 arguments.\n");
    }

    /* On verifie si une option est passe. */
    if (argc == 3) {
        option = checkOption(*argv[2]);
    }


    /* On verifie que l'argument passe est bel et bien un repertoire. */
    rep = opendir(argv[1]);
    if (rep == NULL) {
        printf("Le chemin renseigne est introuvable.\n");
        return(1);
    }

    /* On affiche le contenu du répertoire. */
    while((structRep = readdir(rep)) != NULL) {
        if (option == 'l') {
            /* On calcul la taille du chemin relatif et du fichier. */
            int taille = strlen(argv[1]) + 1 + structRep -> d_namlen + 1;
            char *buffer = malloc(taille);
            strcpy(buffer, argv[1]);
            strcat(buffer, structRep -> d_name);
            int intStat = stat(buffer, &maStat);
            free(buffer);

            if (intStat != 0) {
                printf("Erreur lors de la recuperation des statistiques.\n");
                return(1);
            }

            printf("%u\t%u\t%u\t%u\t%s\n", maStat.st_nlink,
                  maStat.st_uid, maStat.st_gid, maStat.st_size, structRep -> d_name);

        } else {
            printf("%s\n", structRep -> d_name);
        }
    }

    /* On ferme le repertoire ouvert. */
    i = closedir(rep);
    if (i != 0) {
        printf("Le repertoire ne s'est pas ferme correctement.\n");
        return (1);
    };


    return (0);
}

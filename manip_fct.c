#include "manip_fct.h"

// Création d'une image contenant 3 couches de la même taille qui représentent les couleurs RVB
Image* creation_image(int l, int h, int r) {
    Image* image = malloc(sizeof(Image));
    image->longueur = l;
    image->hauteur = h;
    image->resolution = r;

    image->img = malloc(3 * sizeof(unsigned char**));
    for (int i = 0; i < 3; i++) {
        image->img[i] = malloc((r*l) * sizeof(unsigned char*));
        for (int j = 0; j < r*l; j++) {
            image->img[i][j] = malloc((r*h) * sizeof(unsigned char));
        }
    }

    return image;
}

// Initialiser l'image avec des valeurs aléatoires
void initialiser_image_aleatoire(Image *image) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < image->resolution * image->longueur; j++) {
      for (int k = 0; k < image->resolution * image->hauteur; k++) {
        image->img[i][j][k] = rand() % 256;
      }
    }
  }}

// Initialiser l'image avec le clavier
void initialiser_image_clavier(Image *image) {
    for (int i = 0; i < 3; i++) {
        printf("Entrez les valeurs des pixels pour la couche %d :\n", i + 1);

        for (int j = 0; j < image->resolution * image->longueur; j++) {
            for (int k = 0; k < image->resolution * image->hauteur; k++) {
                printf("Entrez la valeur du pixel à la position (%d, %d) : ", j, k);
                scanf("%hhu", &image->img[i][j][k]);
            }
        }
    }
}

// Initialiser avec un fichier
void initialiser_image_fichier(Image *image, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier.\n");
        exit(EXIT_FAILURE);
    }

    for (int j = 0; j < image->resolution * image->longueur; j++) {
        for (int k = 0; k < image->resolution * image->hauteur; k++) {
            unsigned int r, g, b;
            if (fscanf(file, "%u,%u,%u ", &r, &g, &b) == 3) {
                image->img[0][j][k] = (unsigned char)r;
                image->img[1][j][k] = (unsigned char)g;
                image->img[2][j][k] = (unsigned char)b;
            }
        }
    }

    fclose(file);
}

// Afficher l'image
void afficher_image(Image *image) {
    for (int j = 0; j < image->longueur * image->resolution; j++) {
        for (int k = 0; k < image->hauteur * image->resolution; k++) {
            printf("%d,%d,%d ",
                   image->img[0][image->resolution * j][image->resolution * k],
                   image->img[1][image->resolution * j][image->resolution * k],
                   image->img[2][image->resolution * j][image->resolution * k]);
        }
        printf("\n");
    }

    printf("\n");
}

// Libérer l'image
void liberer_image(Image *image) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < image->resolution * image->longueur; j++) {
            free(image->img[i][j]);
        }
        free(image->img[i]);
    }

    free(image->img);
    free(image);
}

// Écrire les données dans un fichier
void ecrire_fichier(const char *filename, Image *image) {
    FILE *fichier_data = fopen(filename, "w");

    if (fichier_data == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier de données pour l'écriture.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < image->resolution * image->longueur; i++) {
        for (int j = 0; j < image->resolution * image->hauteur; j++) {
            fprintf(fichier_data, "%d %d %d\n", image->img[0][i][j], image->img[1][i][j], image->img[2][i][j]);
        }
        fprintf(fichier_data, "\n");
    }

    fclose(fichier_data);
}

// Visualiser l'image avec Gnuplot
void visualiser_image_avec_gnuplot(const char *nom_fichier, int indice) {
    FILE *gnuplot = popen("C:\\gnuplot\\bin\\gnuplot -persistent", "w");
    FILE *fp = fopen("data.txt", "r");
    if (gnuplot == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture de Gnuplot.\n");
        fclose(fp);
        exit(EXIT_FAILURE);
    }
    fprintf(gnuplot, "unset pm3d\n");
    fprintf(gnuplot, "set palette rgbformulae 3,12,15\n");
    fprintf(gnuplot, "set view map\n");
    fprintf(gnuplot, "set size ratio -1\n");
    fprintf(gnuplot, "set size square\n");
    fprintf(gnuplot, "splot '-' matrix with image\n");
    int r, g, b;
    while (fscanf(fp, "%d %d %d", &r, &g, &b) == 3) {
        switch (indice) {
            case 0: fprintf(gnuplot, "%d 0 0\n", r); break;    // Composante rouge
            case 1: fprintf(gnuplot, "0 %d 0\n", g); break;    // Composante verte
            case 2: fprintf(gnuplot, "0 0 %d\n", b); break;    // Composante bleue
            default:
                fprintf(stderr, "Indice de composante de couleur invalide.\n");
                fclose(fp);
                pclose(gnuplot);
                exit(EXIT_FAILURE);
        }
    }

    fprintf(gnuplot, "e\n");
    fclose(fp);
    pclose(gnuplot);
}

// Afficher la composante rouge
void afficher_composante_rouge(Image *image) {
    printf("Composante Rouge :\n");
    for (int i = 0; i < image->hauteur * image->resolution; i++) {
        for (int j = 0; j < image->longueur * image->resolution; j++) {
            printf("%d ", image->img[0][i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Afficher la composante verte
void afficher_composante_verte(Image *image) {
    printf("Composante Verte :\n");
    for (int i = 0; i < image->hauteur * image->resolution; i++) {
        for (int j = 0; j < image->longueur * image->resolution; j++) {
            printf("%d ", image->img[1][i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Afficher la composante bleue
void afficher_composante_bleue(Image *image) {
    printf("Composante Bleue :\n");
    for (int i = 0; i < image->hauteur * image->resolution; i++) {
        for (int j = 0; j < image->longueur * image->resolution; j++) {
            printf("%d ", image->img[2][i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

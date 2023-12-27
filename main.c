#include <stdlib.h>
#include <stdio.h>
#include "manip_fct.h"

int main() {
    Image *image = creation_image(5, 5, 1);

    initialiser_image_aleatoire(image);
    //afficher_image(image);
    //ecrire_fichier("data.txt", image);
    visualiser_image_avec_gnuplot("data.txt", 0);
    //afficher_composante_rouge(image);
    //afficher_composante_verte(image);
    //afficher_composante_bleue(image);

    /*for (int i = 0; i < 3; i++) {
        afficher_image(image);
        visualiser_image_avec_gnuplot("data.txt", i);
    }*/

    liberer_image(image);

    return 0;
}

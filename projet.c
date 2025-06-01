#include <stdio.h>

// Variables globales
int TAILLE_PAGE;
int NB_PAGES;
int NB_CADRES;
int table_cadres[100];
int bit_presence[100];

// === Fonctions pour les calculs ===

// Fonction pour afficher l'espace d'adressage
void afficher_espace_adressage() {
    printf("\nL'espace d'adressage est de %d octets.\n", NB_PAGES * TAILLE_PAGE);
}

// Fonction pour afficher la mémoire vive utilisée
void afficher_memoire_vive() {
    printf("\nLa memoire vive utilisee est de %d cadres × %d mots = %d mots.\n", NB_CADRES, TAILLE_PAGE, NB_CADRES * TAILLE_PAGE);
}

// Fonction de traduction d'une adresse virtuelle
int traduire_adresse(int adresse_virtuelle) {
    int numero_page = adresse_virtuelle / TAILLE_PAGE;
    int deplacement = adresse_virtuelle % TAILLE_PAGE;

    if (numero_page >= NB_PAGES) {
        printf("Erreur : numero de page %d invalide !\n", numero_page);
        return -1;
    }
    if (!bit_presence[numero_page]) {
        printf("Erreur : la page %d n'est pas presente en memoire !\n", numero_page);
        return -1;
    }

    int numero_cadre = table_cadres[numero_page];
    int adresse_physique = numero_cadre * TAILLE_PAGE + deplacement;
    return adresse_physique;
}

// Fonction pour traduire des adresses prédéfinies
void traduire_adresses_virtuelles() {
    int adresses_virtuelles[] = {240, 546, 1578, 2072};
    int nb_adresses = sizeof(adresses_virtuelles) / sizeof(int);

    printf("\n------------- Traduction d'adresses predefinies ---------------\n");
    for (int i = 0; i < nb_adresses; i++) {
        int av = adresses_virtuelles[i];
        int ap = traduire_adresse(av);
        if (ap != -1) {
            printf("Adresse virtuelle %d → Adresse physique %d\n", av, ap);
        }
    }
}

// Fonction pour traduire une adresse entrée par l'utilisateur
void traduire_adresse_utilisateur() {
    int adresse;
    printf("\nEntrez une adresse virtuelle à traduire : ");
    scanf("%d", &adresse);

    int ap = traduire_adresse(adresse);
    if (ap != -1) {
        printf("Adresse virtuelle %d → Adresse physique %d\n", adresse, ap);
    }
}

// === Programme Principal ===

int main() {
    int choix;

    printf("-------- Saisie des parametres ----------\n");

    printf("Entrez la taille d'une page (en mots) : ");
    scanf("%d", &TAILLE_PAGE);

    printf("Entrez le nombre total de pages : ");
    scanf("%d", &NB_PAGES);

    printf("Entrez le nombre de cadres utilises : ");
    scanf("%d", &NB_CADRES);

    printf("\n-------- Saisie des cadres associes aux pages ----------\n");
    for (int i = 0; i < NB_PAGES; i++) {
        printf("Cadre pour la page %d : ", i);
        scanf("%d", &table_cadres[i]);
    }

    printf("\n----------- Saisie des bits de presence --------------\n");
    for (int i = 0; i < NB_PAGES; i++) {
        printf("Bit de presence pour la page %d (0 ou 1) : ", i);
        scanf("%d", &bit_presence[i]);
    }

    // Menu
    do {
        printf("\n-------------- MENU ---------------\n");
        printf("1. Afficher l'espace d'adressage\n");
        printf("2. Afficher la memoire vive utilisee\n");
        printf("3. Traduire des adresses virtuelles predefinies\n");
        printf("4. Traduire une adresse virtuelle saisie\n");
        printf("5. Quitter\n");
        printf("Choisissez une option : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                afficher_espace_adressage();
                break;
            case 2:
                afficher_memoire_vive();
                break;
            case 3:
                traduire_adresses_virtuelles();
                break;
            case 4:
                traduire_adresse_utilisateur();
                break;
            case 5:
                printf("\nFin du programme. Merci !\n");
                break;
            default:
                printf("\n Option invalide, veuillez réessayer.\n");
        }
    } while (choix != 5);

    return 0;
}
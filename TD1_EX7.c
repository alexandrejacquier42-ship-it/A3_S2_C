#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char id [20];
    int alt;
    float vitesse;
} Avion;

int montee(Avion *a, int gain){
    a->alt += gain;
}

int main () {
    Avion a1 = {"A320", 2000, 250.0};

    int gain = 1000;

    printf("Altitude avant montee : %d ft\n", a1.alt);
    montee(&a1, gain);
    printf("Altitude apres montee : %d ft\n", a1.alt);

    return 0;
}
#include <stdio.h>

void energie(float tension, float courant, float *puissance, float *resistance){
    *puissance = tension * courant;
    *resistance = tension / courant;
}

int main () {
    float tension = 4.0;
    float courant = 2.0;
    float P = 0.0;
    float R = 0.0;

    energie(tension, courant, &P, &R);
    printf("Puissance : %f W\nResistance : %f Ohm\n", P, R);
}
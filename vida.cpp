#include "vida.h"

float diminui_vida_aquiles(float vida) {
    // Exemplo de lógica para diminuir vida
    return vida - 10.0f;
}

void diminui_vida_heitor(float *vida, float *dano) {
    // Exemplo de lógica para diminuir vida
    *vida -= *dano;
}

#ifndef TIPOS_H
#define TIPOS_H

#include "raylib.h"

enum STATUS {RIGHT, LEFT};

typedef struct{
    float largura;
    float altura;
} Dimensao;

typedef struct{
    int Idle;
    int Run;
    int Attack;
} Status;

typedef struct{
    Rectangle barra;
} Vida;

typedef struct{
    float posX;
    float posY;
    int postura;
} Dados;

#endif // TIPOS_H

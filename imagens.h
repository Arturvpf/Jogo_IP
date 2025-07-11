#ifndef IMAGENS_H
#define IMAGENS_H

#include "raylib.h"

void carregaImagemaquiles(Texture2D Imagem, int Frame, float larguraFrame,
                         float *const PosX, float *const PosY, long int Tecla);
void carregaImagemheitor(Texture2D Imagem, int Frame, float larguraFrame,
                         float *const PosX, float *const PosY, long int Tecla);

#endif // IMAGENS_H

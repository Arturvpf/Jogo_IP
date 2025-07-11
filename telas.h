#ifndef TELAS_H
#define TELAS_H

// Protótipos das funções de tela
void tela_menu(bool *janela_inicial, bool *janela_inst, bool *janela_config, bool *tela_carregamento, bool *music_on, Texture2D desert, Texture2D configuracoes, Vector2 position, int SCREEN_WIDTH, int SCREEN_HEIGHT, Rectangle config, Rectangle button_jogar, Rectangle button_inst, Rectangle config_lines, Rectangle config_music_on, Rectangle config_music_off, Rectangle config_close, Rectangle button_voltar);
void tela_carregamento_func(bool *tela_carregamento, bool *janela_inicial, bool *jogo_rodando, float *rectTime, float *rectSize, Rectangle *retangulo_carregamento, float rectSpeed, Rectangle retangulo_carregamento_lines, Texture2D telacarregamento, Vector2 position, Rectangle button_voltar);
void tela_jogo(bool *jogo_rodando, bool *janela_inicial, bool *janela_config, bool *music_on, Vida *vida_aquiles, Vida *vida_heitor, Dados *player1, Dados *player2, Rectangle *aquiles, Rectangle *heitor, int *frame, float *timer, bool *aquiles_win, bool *heitor_win, Texture2D desert, Texture2D fundojogo, Texture2D configuracoes, Texture2D versus, Vector2 position, Rectangle config, Rectangle button_voltar, Dimensao frameIdle1, Dimensao frameRun1, Dimensao frameAttack1, Dimensao frameIdle2, Dimensao frameRun2, Dimensao frameAttack2, Status maxFrame1, Status maxFrame2, Texture2D aquilesIdleRight, Texture2D aquilesIdleLeft, Texture2D aquilesRunRight, Texture2D aquilesRunLeft, Texture2D aquilesAttackRight, Texture2D aquilesAttackLeft, Texture2D heitorIdleRight, Texture2D heitorIdleLeft, Texture2D heitorRunRight, Texture2D heitorRunLeft, Texture2D heitorAttackRight, Texture2D heitorAttackLeft, Sound Sound_attackW, Sound Sound_attackI, Sound Sound_death, Texture2D fundojogo2, Rectangle vida_aquiles_linha, Rectangle vida_aquiles_fundo, Rectangle vida_heitor_linha, Rectangle vida_heitor_fundo, Rectangle config_lines, Rectangle config_music_on, Rectangle config_music_off, Rectangle config_close);
void tela_vitoria_aquiles(bool *aquiles_win, bool *janela_inicial, Vida *vida_aquiles, Vida *vida_heitor, Dados *player1, Dados *player2, int *frame, float *timer, Texture2D fundojogo, Texture2D configuracoes, Texture2D versus, Vector2 position, Rectangle vida_aquiles_linha, Rectangle vida_aquiles_fundo, Rectangle vida_heitor_linha, Rectangle vida_heitor_fundo, Texture2D aquilesIdleRight, Texture2D aquilesIdleLeft, Texture2D heitor_died, Texture2D heitor_died2, Dimensao player1Dead, Dimensao player2Dead, Rectangle end_of_game, Rectangle button_restart, Rectangle button_voltar);
void tela_vitoria_heitor(bool *heitor_win, bool *janela_inicial, Vida *vida_aquiles, Vida *vida_heitor, Dados *player1, Dados *player2, int *frame, float *timer, Texture2D fundojogo, Texture2D configuracoes, Texture2D versus, Vector2 position, Rectangle vida_aquiles_linha, Rectangle vida_aquiles_fundo, Rectangle vida_heitor_linha, Rectangle vida_heitor_fundo, Texture2D heitorIdleRight, Texture2D heitorIdleLeft, Texture2D aquiles_died, Texture2D aquiles_died2, Dimensao player1Dead, Dimensao player2Dead, Rectangle end_of_game, Rectangle button_restart, Rectangle button_voltar);

#endif // TELAS_H
#ifndef TELAS_H
#define TELAS_H

#include "raylib.h"
#include "tipos.h"
#include "vida.h"
#include "imagens.h"

void exibirMenu(bool *janela_inicial, bool *janela_config, bool *janela_inst, bool *tela_carregamento, bool *music_on, Texture2D desert, Texture2D configuracoes, Rectangle config, Rectangle button_jogar, Rectangle button_inst, Rectangle config_music_on, Rectangle config_music_off, Rectangle config_close, Rectangle config_lines, int SCREEN_WIDTH, int SCREEN_HEIGHT);
void exibirInstrucoes(bool *janela_inst, Texture2D desert, Rectangle button_voltar, Rectangle button_W, Rectangle button_A, Rectangle button_I, Rectangle button_J, Rectangle button_L, Rectangle button_D, int SCREEN_WIDTH, int SCREEN_HEIGHT);
void exibirCarregamento(bool *tela_carregamento, bool *janela_inicial, bool *jogo_rodando, Texture2D telacarregamento, Rectangle button_voltar, Rectangle retangulo_carregamento, Rectangle retangulo_carregamento_lines, float *rectTime, float *rectSize, float rectSpeed, int *apertei_voltar, int SCREEN_WIDTH, int SCREEN_HEIGHT, bool music_on, Music music);
// Outras funções de tela podem ser adicionadas aqui

#endif // TELAS_H

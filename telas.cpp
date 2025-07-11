#include "raylib.h"
#include "tipos.h"
#include "vida.h"
#include "imagens.h"
#include "telas.h"

// Implementações mínimas das funções de tela
void tela_menu(bool *janela_inicial, bool *janela_inst, bool *janela_config, bool *tela_carregamento, bool *music_on, Texture2D desert, Texture2D configuracoes, Vector2 position, int SCREEN_WIDTH, int SCREEN_HEIGHT, Rectangle config, Rectangle button_jogar, Rectangle button_inst, Rectangle config_lines, Rectangle config_music_on, Rectangle config_music_off, Rectangle config_close, Rectangle button_voltar) {
    if(*music_on){
        UpdateMusicStream(music);
        SetMusicVolume(music,0.3f);
    }
    if(!(*janela_config) && !(*janela_inst)){
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(desert, position.x, position.y, WHITE);
        DrawTexture(configuracoes, 1400, 20, BLACK);
        DrawText("Jogar", SCREEN_WIDTH/2-130, SCREEN_HEIGHT/2, 80, WHITE);
        DrawText("Instrucoes", SCREEN_WIDTH / 2 - 160, SCREEN_HEIGHT /2+130, 50, WHITE);
        if (CheckCollisionPointRec(GetMousePosition(), config)){
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                *janela_config = true;
            }
        }
        if (CheckCollisionPointRec(GetMousePosition(), button_jogar)){
            DrawText("Jogar", SCREEN_WIDTH/2-130, SCREEN_HEIGHT/2, 80, LIGHTGRAY);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                *tela_carregamento = true;
                *janela_inicial = false;
                *janela_config = false;
            }
        }
        if (CheckCollisionPointRec(GetMousePosition(), button_inst)) {
            DrawText("Instrucoes", SCREEN_WIDTH / 2 - 160, SCREEN_HEIGHT /2+130, 50, LIGHTGRAY);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                *janela_inst = true;
            }
        }
        EndDrawing();
    }
    else if(!(*janela_inst)){
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(desert, position.x, position.y, WHITE);
        DrawText("Jogar", SCREEN_WIDTH/2-130, SCREEN_HEIGHT/2, 80, WHITE);
        DrawText("Instrucoes", SCREEN_WIDTH / 2 - 160, SCREEN_HEIGHT /2+130, 50, WHITE);
        DrawTexture(configuracoes, 1425, 8, BLACK);
        DrawRectangleRoundedLines(config_lines, 0.3, 1000, 3, BLACK);
        if(*music_on)
            DrawRectangleRounded(config_music_on,0.3,1000,GREEN);
        if(!(*music_on))
            DrawRectangleRounded(config_music_off,0.3,1000,RED);
        DrawText("MUSIC on | off",1300,80,20,BLACK);
        DrawText("x",1453,55,30,GRAY);
        if(CheckCollisionPointRec(GetMousePosition(),config_music_off)){
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                *music_on = false;
            }
        }
        if(CheckCollisionPointRec(GetMousePosition(),config_music_on)){
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                *music_on = true;
            }
        }
        if(CheckCollisionPointRec(GetMousePosition(),config_close)){
            DrawText("x",1453,55,30,RED);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                *janela_config = false;
            }
        }
        if (CheckCollisionPointRec(GetMousePosition(), button_jogar)){
            DrawText("Jogar", SCREEN_WIDTH/2-130, SCREEN_HEIGHT/2, 80, LIGHTGRAY);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                *tela_carregamento = true;
                *janela_inicial = false;
            }
        }
        if (CheckCollisionPointRec(GetMousePosition(), button_inst)) {
            DrawText("Instrucoes", SCREEN_WIDTH / 2 - 160, SCREEN_HEIGHT /2+130, 50, LIGHTGRAY);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                *janela_inst = true;
                *janela_config = false;
            }
        }
        EndDrawing();
    }
    else if(!(*janela_config)){
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(desert, position.x, position.y, WHITE);
        DrawText("<-",6,5,30,WHITE);
        DrawRectangleLines(5, 5,30, 30,WHITE);
        DrawRectangleRoundedLines(button_W, 0.3,1000, 3, BLACK);
        DrawText("W",280,213,60,BLUE);
        DrawRectangleRoundedLines(button_A, 0.3, 1000, 3, BLACK);
        DrawText("A",183,315,60,BLUE);
        DrawRectangleRoundedLines(button_I, 0.3, 1000, 3, BLACK);
        DrawText("I",990,213,60,RED);
        DrawRectangleRoundedLines(button_J, 0.3, 1000, 3, BLACK);
        DrawText("J",883,315,60,RED);
        DrawRectangleRoundedLines(button_L, 0.3, 1000, 3, BLACK);
        DrawText("L",1090,315,60,RED);
        DrawRectangleRoundedLines(button_D, 0.3, 1000, 3, BLACK);
        DrawText("D",383,315,60,BLUE);
        DrawText("Aquiles:",150,100,50,BLUE);
        DrawText("Heitor:",850,100,50,RED);
        DrawText("W:Ataque",150,600,40,BLUE);
        DrawText("I:Ataque",850,600,40,RED);
        DrawText("A:Mover para esquerda",150,700,40,BLUE);
        DrawText("J:Mover para esquerda",850,700,40,RED);
        DrawText("L:Mover para direita",850,800,40,RED);
        DrawText("D:Mover para direita",150,800,40,BLUE);
        if(CheckCollisionPointRec(GetMousePosition(),button_voltar)){
            DrawText("<-",6,5,30,LIGHTGRAY);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                *janela_inst = false;
            }
        }
        EndDrawing();
    }
}

void tela_carregamento_func(bool *tela_carregamento, bool *janela_inicial, bool *jogo_rodando, float *rectTime, float *rectSize, Rectangle *retangulo_carregamento, float rectSpeed, Rectangle retangulo_carregamento_lines, Texture2D telacarregamento, Vector2 position, Rectangle button_voltar) {
    int apertei_voltar = 0;
    if(*music_on){
        UpdateMusicStream(music);
        SetMusicVolume(music,0.3f);
    }
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawTexture(telacarregamento, position.x, position.y,WHITE);
    DrawRectangleLines(5, 5,30, 30,WHITE);
    DrawText("<-",6,5,30,WHITE);
    DrawText("Aquiles era filho de Tetis, que o mergulhou nas aguas do rio Esfinge tornando-o \ninvulneravel, exceto  pelo seu calcanhar,por onde sua mae o segurou. O calcanhar de \nAquiles era seu ponto fraco.",100,30,30,WHITE);
    DrawText("\n\n\nHeitor era filho de Priamo, rei de Troia, e no mais famoso confronto da Guerra de Troia,\nAquiles, o maior guerreiro de todos os tempos, venceu facilmente o mais valoroso dos \ntroianos,que era Heitor.",100,30,30,WHITE);
    DrawText("\n\n\n\n\nAquiles se recusava a participar da guerra, porem seu grande amigo Patroclo furta-lhe \na armadura e vai para o campo de batalha onde acabou por encontrar a morte nas \n mãos de Heitor,que pensava estar lutando com Aquiles. Enlouquecido de dor pela perda",100,30,30,WHITE);
    DrawText("\n\n\n\n\n\n\n\nde seu amigo, Aquiles saltousem armas para o campo de batalha e num bramido demente \ne insano, so pensou em vingar-se e investiu sobre Heitor matando-o.",100,30,30,WHITE);
    if(CheckCollisionPointRec(GetMousePosition(),button_voltar)){
        DrawText("<-",6,5,30,LIGHTGRAY);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            *tela_carregamento = false;
            *janela_inicial = true;
            apertei_voltar = 1;
        }
    }
    *rectTime += GetFrameTime();
    if (*rectTime >= 25.0f || apertei_voltar){
        *tela_carregamento = false;
        if(!(*janela_inicial)) *jogo_rodando = true;
        *rectSize = 0.0f;
        retangulo_carregamento->width = 0.0f;
        *rectTime = 0.0f;
    }
    *rectSize += rectSpeed * GetFrameTime();
    retangulo_carregamento->width = *rectSize-8;
    DrawRectangleRoundedLines(retangulo_carregamento_lines,0.5,1000,2, WHITE);
    DrawRectangleRounded(*retangulo_carregamento,0.5,1000, WHITE);
    EndDrawing();
}

void tela_jogo(bool *jogo_rodando, bool *janela_inicial, bool *janela_config, bool *music_on, Vida *vida_aquiles, Vida *vida_heitor, Dados *player1, Dados *player2, Rectangle *aquiles, Rectangle *heitor, int *frame, float *timer, bool *aquiles_win, bool *heitor_win, Texture2D desert, Texture2D fundojogo, Texture2D configuracoes, Texture2D versus, Vector2 position, Rectangle config, Rectangle button_voltar, Dimensao frameIdle1, Dimensao frameRun1, Dimensao frameAttack1, Dimensao frameIdle2, Dimensao frameRun2, Dimensao frameAttack2, Status maxFrame1, Status maxFrame2, Texture2D aquilesIdleRight, Texture2D aquilesIdleLeft, Texture2D aquilesRunRight, Texture2D aquilesRunLeft, Texture2D aquilesAttackRight, Texture2D aquilesAttackLeft, Texture2D heitorIdleRight, Texture2D heitorIdleLeft, Texture2D heitorRunRight, Texture2D heitorRunLeft, Texture2D heitorAttackRight, Texture2D heitorAttackLeft, Sound Sound_attackW, Sound Sound_attackI, Sound Sound_death, Texture2D fundojogo2, Rectangle vida_aquiles_linha, Rectangle vida_aquiles_fundo, Rectangle vida_heitor_linha, Rectangle vida_heitor_fundo, Rectangle config_lines, Rectangle config_music_on, Rectangle config_music_off, Rectangle config_close) {
    if(!(*janela_config)){
        if(*music_on){
            UpdateMusicStream(musicluta);
            SetMusicVolume(musicluta,0.2f);
        }
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(fundojogo, position.x, position.y,WHITE);
        DrawTexture(configuracoes, 1400, 20, WHITE);
        DrawTexture(versus,680,30,WHITE);
        DrawRectangleLines(5, 5,30, 30,WHITE);
        DrawText("<-",6,5,30,WHITE);
        // Vida Aquiles
        if(vida_aquiles->barra.width>250.0f){
            DrawRectangleRoundedLines(vida_aquiles_linha,0.5,1000,3, GREEN);
            DrawRectangleRounded(vida_aquiles_fundo, 0.5,1000, DARKGREEN);
            DrawRectangleRounded(vida_aquiles->barra, 0.5,1000, LIME);
        } else if(vida_aquiles->barra.width>150.0f && vida_aquiles->barra.width<250.0f){
            DrawRectangleRoundedLines(vida_aquiles_linha,0.5,1000,3, GOLD);
            DrawRectangleRounded(vida_aquiles_fundo, 0.5,1000, amarelo_claro);
            DrawRectangleRounded(vida_aquiles->barra, 0.5,1000, YELLOW);
        } else if(vida_aquiles->barra.width<150.0f){
            DrawRectangleRoundedLines(vida_aquiles_linha,0.5,1000,3, MAROON);
            DrawRectangleRounded(vida_aquiles_fundo, 0.5,1000,vermelho_claro);
            DrawRectangleRounded(vida_aquiles->barra, 0.5,1000, RED);
        }
        // Vida Heitor
        if(vida_heitor->barra.width>250.0f){
            DrawRectangleRoundedLines(vida_heitor_linha,0.5,1000,3, GREEN);
            DrawRectangleRounded(vida_heitor_fundo, 0.5,1000, DARKGREEN);
            DrawRectangleRounded(vida_heitor->barra, 0.5,1000, LIME);
        } else if(vida_heitor->barra.width>150.0f && vida_heitor->barra.width<250.0f){
            DrawRectangleRoundedLines(vida_heitor_linha,0.5,1000,3, GOLD);
            DrawRectangleRounded(vida_heitor_fundo, 0.5,1000, amarelo_claro);
            DrawRectangleRounded(vida_heitor->barra, 0.5,1000, YELLOW);
        } else if(vida_heitor->barra.width<150.0f){
            DrawRectangleRoundedLines(vida_heitor_linha,0.5,1000,3, MAROON);
            DrawRectangleRounded(vida_heitor_fundo, 0.5,1000,vermelho_claro);
            DrawRectangleRounded(vida_heitor->barra, 0.5,1000, RED);
        }
        if (CheckCollisionPointRec(GetMousePosition(), config)){
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                *janela_config = true;
            }
        }
        if(CheckCollisionPointRec(GetMousePosition(),button_voltar)){
            DrawText("<-",6,5,30,LIGHTGRAY);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                *jogo_rodando = false;
                *janela_inicial = true;
            }
        }
        // Controle Aquiles
        if (IsKeyUp(KEY_A) && IsKeyUp(KEY_D) && IsKeyUp(KEY_W)){
            if (*frame >= maxFrame1.Idle){ *frame = 0; }
            if (player1->postura == RIGHT){
                carregaImagemaquiles(aquilesIdleRight, *frame, frameIdle1.largura, &player1->posX, &player1->posY, KEY_NULL);
            } else if (player1->postura == LEFT){
                carregaImagemaquiles(aquilesIdleLeft, *frame, frameIdle1.largura, &player1->posX, &player1->posY, KEY_NULL);
            }
        } else {
            if (IsKeyDown(KEY_A)){
                player1->postura = LEFT;
                if (*frame >= maxFrame1.Run){ *frame = 0; }
                carregaImagemaquiles(aquilesRunLeft, *frame, frameRun1.largura, &player1->posX, &player1->posY, KEY_A);
            } else if (IsKeyDown(KEY_D)){
                player1->postura = RIGHT;
                if (*frame >= maxFrame1.Run){ *frame = 0; }
                carregaImagemaquiles(aquilesRunRight, *frame, frameRun1.largura, &player1->posX, &player1->posY, KEY_D);
            } else if (IsKeyDown(KEY_W)){
                if (*frame >= maxFrame1.Attack){ *frame = 0; }
                if (player1->postura == RIGHT){
                    carregaImagemaquiles(aquilesAttackRight, *frame, frameAttack1.largura, &player1->posX, &player1->posY, KEY_W);
                    if( ((aquiles->x + aquiles->width-40)> (heitor->x)) && ((aquiles->x+aquiles->width)<(heitor->x+heitor->width+30)) ){
                        diminui_vida_heitor(&vida_heitor->barra.width,&vida_heitor->barra.x);
                        PlaySound(Sound_attackW);
                    }
                } else if (player1->postura == LEFT){
                    carregaImagemaquiles(aquilesAttackLeft, *frame, frameAttack1.largura, &player1->posX, &player1->posY, KEY_W);
                    if( ((aquiles->x) < (heitor->x+heitor->width-40)) && ((aquiles->x)>(heitor->x)) ){
                        diminui_vida_heitor(&vida_heitor->barra.width,&vida_heitor->barra.x);
                        PlaySound(Sound_attackW);
                    }
                }
            }
            aquiles->x=player1->posX;
            aquiles->y=player1->posY;
        }
        // Controle Heitor
        if (IsKeyUp(KEY_J) && IsKeyUp(KEY_L) && IsKeyUp(KEY_I)){
            if (*frame >= maxFrame2.Idle){ *frame = 0; }
            if (player2->postura == RIGHT){
                carregaImagemheitor(heitorIdleRight, *frame, frameIdle2.largura, &player2->posX, &player2->posY, KEY_NULL);
            } else if (player2->postura == LEFT){
                carregaImagemheitor(heitorIdleLeft, *frame, frameIdle2.largura, &player2->posX, &player2->posY, KEY_NULL);
            }
        } else if (IsKeyDown(KEY_J)){
            player2->postura = LEFT;
            if (*frame >= maxFrame2.Run){ *frame = 0; }
            carregaImagemheitor(heitorRunLeft, *frame, frameRun2.largura, &player2->posX, &player2->posY, KEY_J);
        } else if (IsKeyDown(KEY_L)){
            player2->postura = RIGHT;
            if (*frame >= maxFrame2.Run){ *frame = 0; }
            carregaImagemheitor(heitorRunRight, *frame, frameRun2.largura, &player2->posX, &player2->posY, KEY_L);
        } else if (IsKeyDown(KEY_I)){
            if (*frame >= maxFrame2.Attack){ *frame = 0; }
            if (player2->postura == RIGHT){
                carregaImagemheitor(heitorAttackRight, *frame, frameAttack2.largura, &player2->posX, &player2->posY, KEY_I);
                if( ((heitor->x + heitor->width-40)> (aquiles->x)) && ((heitor->x+heitor->width)<(aquiles->x+aquiles->width+30)) ){
                    vida_aquiles->barra.width=diminui_vida_aquiles(vida_aquiles->barra.width);
                    PlaySound(Sound_attackW);
                }
            } else if (player2->postura == LEFT){
                carregaImagemheitor(heitorAttackLeft, *frame, frameAttack2.largura, &player2->posX, &player2->posY, KEY_I);
                if( ((heitor->x) < (aquiles->x+aquiles->width-40)) && ((heitor->x)>(aquiles->x)) ){
                    vida_aquiles->barra.width=diminui_vida_aquiles(vida_aquiles->barra.width);
                    PlaySound(Sound_attackW);
                }
            }
            heitor->x=player2->posX;
            heitor->y=player2->posY;
        }
        EndDrawing();
    } else {
        if(*music_on){
            UpdateMusicStream(musicluta);
            SetMusicVolume(musicluta,0.2f);
        }
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(fundojogo, position.x, position.y,WHITE);
        DrawTexture(versus,680,30,WHITE);
        // Vida Aquiles
        if(vida_aquiles->barra.width>250.0f){
            DrawRectangleRoundedLines(vida_aquiles_linha,0.5,1000,3, GREEN);
            DrawRectangleRounded(vida_aquiles_fundo, 0.5,1000, DARKGREEN);
            DrawRectangleRounded(vida_aquiles->barra, 0.5,1000, LIME);
        } else if(vida_aquiles->barra.width>150.0f && vida_aquiles->barra.width<250.0f){
            DrawRectangleRoundedLines(vida_aquiles_linha,0.5,1000,3, GOLD);
            DrawRectangleRounded(vida_aquiles_fundo, 0.5,1000, amarelo_claro);
            DrawRectangleRounded(vida_aquiles->barra, 0.5,1000, YELLOW);
        } else if(vida_aquiles->barra.width<150.0f){
            DrawRectangleRoundedLines(vida_aquiles_linha,0.5,1000,3, MAROON);
            DrawRectangleRounded(vida_aquiles_fundo, 0.5,1000,vermelho_claro);
            DrawRectangleRounded(vida_aquiles->barra, 0.5,1000, RED);
        }
        // Vida Heitor
        if(vida_heitor->barra.width>250.0f){
            DrawRectangleRoundedLines(vida_heitor_linha,0.5,1000,3, GREEN);
            DrawRectangleRounded(vida_heitor_fundo, 0.5,1000, DARKGREEN);
            DrawRectangleRounded(vida_heitor->barra, 0.5,1000, LIME);
        } else if(vida_heitor->barra.width>150.0f && vida_heitor->barra.width<250.0f){
            DrawRectangleRoundedLines(vida_heitor_linha,0.5,1000,3, GOLD);
            DrawRectangleRounded(vida_heitor_fundo, 0.5,1000, amarelo_claro);
            DrawRectangleRounded(vida_heitor->barra, 0.5,1000, YELLOW);
        } else if(vida_heitor->barra.width<150.0f){
            DrawRectangleRoundedLines(vida_heitor_linha,0.5,1000,3, MAROON);
            DrawRectangleRounded(vida_heitor_fundo, 0.5,1000,vermelho_claro);
            DrawRectangleRounded(vida_heitor->barra, 0.5,1000, RED);
        }
        DrawRectangleLines(5, 5,30, 30,WHITE);
        DrawText("<-",6,5,30,WHITE);
        if(CheckCollisionPointRec(GetMousePosition(),button_voltar)){
            DrawText("<-",6,5,30,LIGHTGRAY);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                *jogo_rodando = false;
                *janela_inicial = true;
            }
        }
        // Controle Aquiles
        if (IsKeyUp(KEY_A) && IsKeyUp(KEY_D) && IsKeyUp(KEY_W)){
            if (*frame >= maxFrame1.Idle){ *frame = 0; }
            if (player1->postura == RIGHT){
                carregaImagemaquiles(aquilesIdleRight, *frame, frameIdle1.largura, &player1->posX, &player1->posY, KEY_NULL);
            } else if (player1->postura == LEFT){
                carregaImagemaquiles(aquilesIdleLeft, *frame, frameIdle1.largura, &player1->posX, &player1->posY, KEY_NULL);
            }
        } else {
            if (IsKeyDown(KEY_A)){
                player1->postura = LEFT;
                if (*frame >= maxFrame1.Run){ *frame = 0; }
                carregaImagemaquiles(aquilesRunLeft, *frame, frameRun1.largura, &player1->posX, &player1->posY, KEY_A);
            } else if (IsKeyDown(KEY_D)){
                player1->postura = RIGHT;
                if (*frame >= maxFrame1.Run){ *frame = 0; }
                carregaImagemaquiles(aquilesRunRight, *frame, frameRun1.largura, &player1->posX, &player1->posY, KEY_D);
            } else if (IsKeyDown(KEY_W)){
                if (*frame >= maxFrame1.Attack){ *frame = 0; }
                if (player1->postura == RIGHT){
                    carregaImagemaquiles(aquilesAttackRight, *frame, frameAttack1.largura, &player1->posX, &player1->posY, KEY_W);
                    PlaySound(Sound_attackW);
                } else if (player1->postura == LEFT){
                    carregaImagemaquiles(aquilesAttackLeft, *frame, frameAttack1.largura, &player1->posX, &player1->posY, KEY_W);
                    PlaySound(Sound_attackW);
                }
            }
            aquiles->x=player1->posX;
            aquiles->y=player1->posY;
        }
        // Controle Heitor
        if (IsKeyUp(KEY_J) && IsKeyUp(KEY_L) && IsKeyUp(KEY_I)){
            if (*frame >= maxFrame2.Idle){ *frame = 0; }
            if (player2->postura == RIGHT){
                carregaImagemheitor(heitorIdleRight, *frame, frameIdle2.largura, &player2->posX, &player2->posY, KEY_NULL);
            } else if (player2->postura == LEFT){
                carregaImagemheitor(heitorIdleLeft, *frame, frameIdle2.largura, &player2->posX, &player2->posY, KEY_NULL);
            }
        } else {
            if (IsKeyDown(KEY_J)){
                player2->postura = LEFT;
                if (*frame >= maxFrame2.Run){ *frame = 0; }
                carregaImagemheitor(heitorRunLeft, *frame, frameRun2.largura, &player2->posX, &player2->posY, KEY_J);
            } else if (IsKeyDown(KEY_L)){
                player2->postura = RIGHT;
                if (*frame >= maxFrame2.Run){ *frame = 0; }
                carregaImagemheitor(heitorRunRight, *frame, frameRun2.largura, &player2->posX, &player2->posY, KEY_L);
            } else if (IsKeyDown(KEY_I)){
                if (*frame >= maxFrame2.Attack){ *frame = 0; }
                if (player2->postura == RIGHT){
                    carregaImagemheitor(heitorAttackRight, *frame, frameAttack2.largura, &player2->posX, &player2->posY, KEY_I);
                    PlaySound(Sound_attackW);
                } else if (player2->postura == LEFT){
                    carregaImagemheitor(heitorAttackLeft, *frame, frameAttack2.largura, &player2->posX, &player2->posY, KEY_I);
                    PlaySound(Sound_attackW);
                }
            }
            heitor->x=player2->posX;
            heitor->y=player2->posY;
        }
        DrawTexture(configuracoes, 1425, 8, BLACK);
        DrawRectangleRoundedLines(config_lines, 0.3, 1000, 3, BLACK);
        if(*music_on)
            DrawRectangleRounded(config_music_on,0.3,1000,GREEN);
        if(!(*music_on))
            DrawRectangleRounded(config_music_off,0.3,1000,RED);
        DrawText("MUSIC on | off",1300,80,20,BLACK);
        DrawText("x",1453,55,30,GRAY);
        if(CheckCollisionPointRec(GetMousePosition(),config_music_off)){
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                *music_on = false;
            }
        }
        if(CheckCollisionPointRec(GetMousePosition(),config_music_on)){
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                *music_on = true;
            }
        }
        if(CheckCollisionPointRec(GetMousePosition(),config_close)){
            DrawText("x",1453,55,30,RED);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                *janela_config = false;
            }
        }
        EndDrawing();
    }
    if (*timer >= 0.2){
        atualizaFrame(timer, frame);
    }
    *timer += GetFrameTime();
    if(vida_heitor->barra.width==0.0f){
        *jogo_rodando=false;
        *aquiles_win=true;
        PlaySound(Sound_death);
        *frame=0;
    }
    if(vida_aquiles->barra.width==0.0f){
        *jogo_rodando=false;
        *heitor_win=true;
        PlaySound(Sound_death);
        *frame=0;
    }
}

void tela_vitoria_aquiles(bool *aquiles_win, bool *janela_inicial, Vida *vida_aquiles, Vida *vida_heitor, Dados *player1, Dados *player2, int *frame, float *timer, Texture2D fundojogo, Texture2D configuracoes, Texture2D versus, Vector2 position, Rectangle vida_aquiles_linha, Rectangle vida_aquiles_fundo, Rectangle vida_heitor_linha, Rectangle vida_heitor_fundo, Texture2D aquilesIdleRight, Texture2D aquilesIdleLeft, Texture2D heitor_died, Texture2D heitor_died2, Dimensao player1Dead, Dimensao player2Dead, Rectangle end_of_game, Rectangle button_restart, Rectangle button_voltar) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawTexture(fundojogo, position.x, position.y, WHITE);
    DrawTexture(configuracoes, 1400, 20, WHITE);
    DrawTexture(versus,680,30,WHITE);
    DrawRectangleRoundedLines(vida_aquiles_linha,0.5,1000,3, GREEN);
    DrawRectangleRounded(vida_aquiles_fundo, 0.5,1000, DARKGREEN);
    DrawRectangleRounded(vida_aquiles->barra, 0.5,1000, LIME);
    DrawRectangleRoundedLines(vida_heitor_linha,0.5,1000,3, MAROON);
    DrawRectangleRounded(vida_heitor_fundo, 0.5,1000, RED);
    DrawRectangleRounded(vida_heitor->barra, 0.5,1000, RED);
    DrawText("AQUILES VENCEU!", (int)end_of_game.x+10, (int)end_of_game.y+10, 40, BLUE);
    DrawTextureRec(aquilesIdleRight, (Rectangle){player1Dead.largura*(*frame), 0, player1Dead.largura, aquilesIdleRight.height}, (Vector2){end_of_game.x+30, end_of_game.y+60}, WHITE);
    DrawTextureRec(heitor_died, (Rectangle){player2Dead.largura*(*frame), 0, player2Dead.largura, heitor_died.height}, (Vector2){end_of_game.x+160, end_of_game.y+60}, WHITE);
    DrawRectangleRoundedLines(button_restart,0.5,1000,2, WHITE);
    DrawText("Reiniciar", (int)button_restart.x+10, (int)button_restart.y+2, 20, WHITE);
    DrawRectangleLines((int)button_voltar.x, (int)button_voltar.y, (int)button_voltar.width, (int)button_voltar.height, WHITE);
    DrawText("<-", (int)button_voltar.x+1, (int)button_voltar.y+1, 20, WHITE);
    if(CheckCollisionPointRec(GetMousePosition(),button_restart)){
        DrawText("Reiniciar", (int)button_restart.x+10, (int)button_restart.y+2, 20, LIGHTGRAY);
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            *aquiles_win = false;
            *janela_inicial = true;
            *frame = 0;
        }
    }
    if(CheckCollisionPointRec(GetMousePosition(),button_voltar)){
        DrawText("<-", (int)button_voltar.x+1, (int)button_voltar.y+1, 20, LIGHTGRAY);
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            *aquiles_win = false;
            *janela_inicial = true;
            *frame = 0;
        }
    }
    EndDrawing();
}

void tela_vitoria_heitor(bool *heitor_win, bool *janela_inicial, Vida *vida_aquiles, Vida *vida_heitor, Dados *player1, Dados *player2, int *frame, float *timer, Texture2D fundojogo, Texture2D configuracoes, Texture2D versus, Vector2 position, Rectangle vida_aquiles_linha, Rectangle vida_aquiles_fundo, Rectangle vida_heitor_linha, Rectangle vida_heitor_fundo, Texture2D heitorIdleRight, Texture2D heitorIdleLeft, Texture2D aquiles_died, Texture2D aquiles_died2, Dimensao player1Dead, Dimensao player2Dead, Rectangle end_of_game, Rectangle button_restart, Rectangle button_voltar) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawTexture(fundojogo, position.x, position.y, WHITE);
    DrawTexture(configuracoes, 1400, 20, WHITE);
    DrawTexture(versus,680,30,WHITE);
    DrawRectangleRoundedLines(vida_aquiles_linha,0.5,1000,3, MAROON);
    DrawRectangleRounded(vida_aquiles_fundo, 0.5,1000, RED);
    DrawRectangleRounded(vida_aquiles->barra, 0.5,1000, RED);
    DrawRectangleRoundedLines(vida_heitor_linha,0.5,1000,3, GREEN);
    DrawRectangleRounded(vida_heitor_fundo, 0.5,1000, DARKGREEN);
    DrawRectangleRounded(vida_heitor->barra, 0.5,1000, LIME);
    DrawText("HEITOR VENCEU!", (int)end_of_game.x+10, (int)end_of_game.y+10, 40, RED);
    DrawTextureRec(heitorIdleRight, (Rectangle){player2Dead.largura*(*frame), 0, player2Dead.largura, heitorIdleRight.height}, (Vector2){end_of_game.x+30, end_of_game.y+60}, WHITE);
    DrawTextureRec(aquiles_died, (Rectangle){player1Dead.largura*(*frame), 0, player1Dead.largura, aquiles_died.height}, (Vector2){end_of_game.x+160, end_of_game.y+60}, WHITE);
    DrawRectangleRoundedLines(button_restart,0.5,1000,2, WHITE);
    DrawText("Reiniciar", (int)button_restart.x+10, (int)button_restart.y+2, 20, WHITE);
    DrawRectangleLines((int)button_voltar.x, (int)button_voltar.y, (int)button_voltar.width, (int)button_voltar.height, WHITE);
    DrawText("<-", (int)button_voltar.x+1, (int)button_voltar.y+1, 20, WHITE);
    if(CheckCollisionPointRec(GetMousePosition(),button_restart)){
        DrawText("Reiniciar", (int)button_restart.x+10, (int)button_restart.y+2, 20, LIGHTGRAY);
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            *heitor_win = false;
            *janela_inicial = true;
            *frame = 0;
        }
    }
    if(CheckCollisionPointRec(GetMousePosition(),button_voltar)){
        DrawText("<-", (int)button_voltar.x+1, (int)button_voltar.y+1, 20, LIGHTGRAY);
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            *heitor_win = false;
            *janela_inicial = true;
            *frame = 0;
        }
    }
    EndDrawing();
}
#include "telas.h"

void exibirMenu(bool *janela_inicial, bool *janela_config, bool *janela_inst, bool *tela_carregamento, bool *music_on, Texture2D desert, Texture2D configuracoes, Rectangle config, Rectangle button_jogar, Rectangle button_inst, Rectangle config_music_on, Rectangle config_music_off, Rectangle config_close, Rectangle config_lines, int SCREEN_WIDTH, int SCREEN_HEIGHT) {
    // ...implementar lógica do menu principal aqui...
}

void exibirInstrucoes(bool *janela_inst, Texture2D desert, Rectangle button_voltar, Rectangle button_W, Rectangle button_A, Rectangle button_I, Rectangle button_J, Rectangle button_L, Rectangle button_D, int SCREEN_WIDTH, int SCREEN_HEIGHT) {
    // ...implementar lógica da tela de instruções aqui...
}

void exibirCarregamento(bool *tela_carregamento, bool *janela_inicial, bool *jogo_rodando, Texture2D telacarregamento, Rectangle button_voltar, Rectangle retangulo_carregamento, Rectangle retangulo_carregamento_lines, float *rectTime, float *rectSize, float rectSpeed, int *apertei_voltar, int SCREEN_WIDTH, int SCREEN_HEIGHT, bool music_on, Music music) {
    // ...implementar lógica da tela de carregamento aqui...
}

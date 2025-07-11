// Includes
#include <stdio.h>
#include "raylib.h"
#include "tipos.h"
#include "vida.h"

#include "imagens.h"
#include "telas.h"

enum STATUS {RIGHT, LEFT};

int main(void)
{   
    Color amarelo_claro={220,220,0,255},vermelho_claro={ 140, 0, 0, 255 };  
    Dimensao frameIdle1,frameIdle2; // variável referente a um frame da postura idle
    Dimensao frameRun1,frameRun2;  // variável referente a um frame da postura run
    Dimensao frameAttack1,frameAttack2; // variável referente a um frame da postura de ataque
    Dimensao player1Dead,player2Dead;
    Status maxFrame1,maxFrame2;
    Dados player1;
    player1.posX = 200;       
    player1.posY = 800;
    player1.postura = RIGHT;
    Rectangle aquiles={200,800};
    Vida vida_aquiles;
    vida_aquiles.barra={270,70,350,20};   
    Dados player2;
    player2.posX = 1000;       
    player2.posY = 800;
    player2.postura = LEFT;
    Rectangle heitor={1000,800};
    Vida vida_heitor;
    vida_heitor.barra={920,70,350,20};   
    const int SCREEN_WIDTH = 1500;
    const int SCREEN_HEIGHT = 1000;
    bool janela_inicial=true;
    bool janela_inst=false;
    bool tela_carregamento=false;
    bool jogo_rodando = false;   
    bool janela_config = false;
    bool music_on=true;
    bool aquiles_win=false,heitor_win=false;
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Heitor_X_Aquiles");
    SetTargetFPS(60);
    Rectangle config={1270,30,220,30},config_close={1453,55,20,20},config_lines{1280, 63,200, 100},
    
                //////////////////////////////////////////////////////////////////
                
              button_jogar={SCREEN_WIDTH/2-130,SCREEN_HEIGHT/2,230,80},button_voltar{5, 5,30, 30},
              
              /////////////////////////////////////////////////////////////////////
              
              retangulo_carregamento{600,900,0,15},retangulo_carregamento_lines{600,900,240,15},
              
              /////////////////////////////////////////////////////////////////////
              
              vida_aquiles_linha{270,70,350,20},vida_heitor_linha{920,70,350,20},
              vida_aquiles_fundo={270,70,350,20},vida_heitor_fundo{920,70,350,20},
              
              ///////////////////////////////////////////////////////////////////
              
              config_music_on{1370,80,30,20},config_music_off{1418,80,30,20},
              
              ////////////////////////////////////////////////////////////////
              
              end_of_game{SCREEN_WIDTH/2-130,SCREEN_HEIGHT/2-50,300,175},button_restart{end_of_game.x+70,end_of_game.y+100,160,20};  
              
            ////////////////////////////////////////////////////////////////////
            
            Rectangle button_inst = {SCREEN_WIDTH / 2-150,SCREEN_HEIGHT / 2 +130,250,80}, 
            
            /////////////////////////////////////////////////////////////////
            
                    button_A = {150,300,100,80}, button_W = {250,200,100,80}, 
                    button_D ={350,300,100,80}, button_J ={850,300,100,80}, 
                    button_I ={950,200,100,80}, button_L ={1050,300,100,80};
                    
                //////////////////////////////////////////////////////   
    
    Image background = LoadImage("assets/imagens/background1.png");
    Image carregamento = LoadImage("assets/imagens/carregamento.png");
    Image fundofinal=LoadImage("assets/imagens/fundofinal.png");
    Image c=LoadImage("assets/imagens/textura_config1.png");
    Image v=LoadImage("assets/imagens/Versus.png");
    Texture2D versus= LoadTextureFromImage(v);  
    Texture2D configuracoes= LoadTextureFromImage(c);   
    Texture2D desert = LoadTextureFromImage(background);
    Texture2D telacarregamento=LoadTextureFromImage(carregamento);
    Texture2D fundojogo=LoadTextureFromImage(fundofinal);
    UnloadImage(background);
    UnloadImage(carregamento);
    UnloadImage(fundofinal);
    UnloadImage(c);
    UnloadImage(v);

    /////////////////////////////////////////////////////
    
    Texture2D aquilesIdleRight  = LoadTexture("assets/imagens/aquilesidle_direita.png");
    Texture2D aquilesIdleLeft  = LoadTexture("assets/imagens/aquilesidle_esquerda.png");
    Texture2D aquilesRunRight  = LoadTexture("assets/imagens/aquilesrun_direita.png");
    Texture2D aquilesRunLeft  = LoadTexture("assets/imagens/aquilesrun_esquerda.png");
    Texture2D aquilesAttackRight  = LoadTexture("assets/imagens/aquilesataque_direita.png");
    Texture2D aquilesAttackLeft  = LoadTexture("assets/imagens/aquilesataque_esquerda.png");
    Texture2D aquiles_died = LoadTexture("assets/imagens/aquiles_dead.png");
    Texture2D aquiles_died2 = LoadTexture("assets/imagens/aquiles_dead2.png");
    //
    Texture2D heitorIdleRight  = LoadTexture("assets/imagens/heitoridle_direita.png");
    Texture2D heitorIdleLeft  = LoadTexture("assets/imagens/heitoridle_esquerda.png");
    Texture2D heitorRunRight  = LoadTexture("assets/imagens/heitorrun_direita.png");
    Texture2D heitorRunLeft  = LoadTexture("assets/imagens/heitorrun_esquerda.png");
    Texture2D heitorAttackRight  = LoadTexture("assets/imagens/heitorataque_direita.png");
    Texture2D heitorAttackLeft  = LoadTexture("assets/imagens/heitorataque_esquerda.png");
    Texture2D heitor_died= LoadTexture("assets/imagens/heitor_dead.png");
    Texture2D heitor_died2= LoadTexture("assets/imagens/heitor_dead2.png");
    //////////////////////////////////////////////////////////////////
    maxFrame1.Idle = 6;
    maxFrame1.Run = 6;
    maxFrame1.Attack = 4;
    maxFrame2.Idle = 5;
    maxFrame2.Run = 6;
    maxFrame2.Attack = 4;
    //aquiles sizes
    frameIdle1.largura = (float)aquilesIdleRight.width / maxFrame1.Idle;
    frameRun1.largura = (float)aquilesRunRight.width / maxFrame1.Run;
    frameAttack1.largura = (float)aquilesAttackRight.width / maxFrame1.Attack;
    player1Dead.largura =(float)aquiles_died.width/4;
    //heitor sizes
    frameIdle2.largura = (float)heitorIdleRight.width / maxFrame2.Idle;
    frameRun2.largura = (float)heitorRunRight.width / maxFrame2.Run;
    frameAttack2.largura = (float)heitorAttackRight.width / maxFrame2.Attack;
    player2Dead.largura =(float)heitor_died.width/4;
    //
    aquiles.width=frameAttack1.largura;
    heitor.width=frameAttack2.largura;
    int frame = 0;
    float timer = 0.0;
    //////////////////////////////////////////////////////////////////////
    Vector2 position = { (float)(SCREEN_WIDTH/2 - desert.width/2), (float)(SCREEN_HEIGHT/2 - desert.height/2 - 20) };
    InitAudioDevice();// Initialize audio device
    
    Music music = LoadMusicStream("assets/musica/musica_jogo.mp3");
    Music musicluta= LoadMusicStream("assets/musica/musica_jogo_luta.mp3");
    Sound Sound_attackW =LoadSound("assets/audio/attack.wav");
    Sound Sound_attackI =LoadSound("assets/audio/attack.wav");
    Sound Sound_death =LoadSound("assets/audio/death.wav");
    
    PlayMusicStream(music);
    PlayMusicStream(musicluta);
    SetSoundVolume(Sound_attackW, 0.5f);
    SetSoundVolume(Sound_attackI, 0.5f);
    //float timePlayed = 0.0f;
    float rectTime= 0.0f,rectSize=1.0f;
    float rectSpeed=10.0f;
    int apertei_voltar=0;
    SetTargetFPS(60);  
    
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {                
        if(janela_inicial){
            tela_menu(&janela_inicial, &janela_inst, &janela_config, &tela_carregamento, &music_on, desert, configuracoes, position, SCREEN_WIDTH, SCREEN_HEIGHT, config, button_jogar, button_inst, config_lines, config_music_on, config_music_off, config_close, button_voltar);
        }
        if(tela_carregamento){
            tela_carregamento_func(&tela_carregamento, &janela_inicial, &jogo_rodando, &rectTime, &rectSize, &retangulo_carregamento, rectSpeed, retangulo_carregamento_lines, telacarregamento, position, button_voltar);
        }
        if(jogo_rodando){
            tela_jogo(&jogo_rodando, &janela_inicial, &janela_config, &music_on, &vida_aquiles, &vida_heitor, &player1, &player2, &aquiles, &heitor, &frame, &timer, &aquiles_win, &heitor_win, desert, fundojogo, configuracoes, versus, position, config, button_voltar, frameIdle1, frameRun1, frameAttack1, frameIdle2, frameRun2, frameAttack2, maxFrame1, maxFrame2, aquilesIdleRight, aquilesIdleLeft, aquilesRunRight, aquilesRunLeft, aquilesAttackRight, aquilesAttackLeft, heitorIdleRight, heitorIdleLeft, heitorRunRight, heitorRunLeft, heitorAttackRight, heitorAttackLeft, Sound_attackW, Sound_attackI, Sound_death, fundojogo, vida_aquiles_linha, vida_aquiles_fundo, vida_heitor_linha, vida_heitor_fundo, config_lines, config_music_on, config_music_off, config_close);
        }
        //----------------------------------------------------------------------------------
        
        if(aquiles_win){
            tela_vitoria_aquiles(&aquiles_win, &janela_inicial, &vida_aquiles, &vida_heitor, &player1, &player2, &frame, &timer, fundojogo, configuracoes, versus, position, vida_aquiles_linha, vida_aquiles_fundo, vida_heitor_linha, vida_heitor_fundo, aquilesIdleRight, aquilesIdleLeft, heitor_died, heitor_died2, player1Dead, player2Dead, end_of_game, button_restart, button_voltar);
        }
           
        if(heitor_win){
            tela_vitoria_heitor(&heitor_win, &janela_inicial, &vida_aquiles, &vida_heitor, &player1, &player2, &frame, &timer, fundojogo, configuracoes, versus, position, vida_aquiles_linha, vida_aquiles_fundo, vida_heitor_linha, vida_heitor_fundo, heitorIdleRight, heitorIdleLeft, aquiles_died, aquiles_died2, player1Dead, player2Dead, end_of_game, button_restart, button_voltar);
        }
    }             
    // De-Initialization
    //--------------------------------------------------------------------------------------
    
    // Descarregar recursos de áudio
    UnloadSound(Sound_death);
    UnloadSound(Sound_attackW);
    UnloadSound(Sound_attackI);
    UnloadMusicStream(music);
    UnloadMusicStream(musicluta);

    // Descarregar texturas
    UnloadTexture(aquilesIdleRight);
    UnloadTexture(aquilesIdleLeft);
    UnloadTexture(aquilesRunRight);
    UnloadTexture(aquilesRunLeft);
    UnloadTexture(aquilesAttackRight);
    UnloadTexture(aquilesAttackLeft);
    UnloadTexture(aquiles_died);
    UnloadTexture(aquiles_died2);
    UnloadTexture(heitorIdleRight);
    UnloadTexture(heitorIdleLeft);
    UnloadTexture(heitorRunRight);
    UnloadTexture(heitorRunLeft);
    UnloadTexture(heitorAttackRight);
    UnloadTexture(heitorAttackLeft);
    UnloadTexture(heitor_died);
    UnloadTexture(heitor_died2);
    UnloadTexture(versus);
    UnloadTexture(configuracoes);
    UnloadTexture(desert);
    UnloadTexture(telacarregamento);
    UnloadTexture(fundojogo);

    // Fechar dispositivos
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
void atualizaFrame(float *const ptrTimer, int *const ptrFrame){
    *ptrTimer = 0;
    *ptrFrame += 1;
}

void carregaImagemaquiles(Texture2D Imagem, int Frame, float larguraFrame, 
                    float *const PosX, float *const PosY, long int Tecla)
{   
    if(*PosX>=0&&*PosX<=1500-larguraFrame){
        if (Tecla == KEY_A){
            DrawTextureRec(
                    Imagem, 
                    (Rectangle){
                        (float)Frame * larguraFrame, 
                        0, 
                        larguraFrame, 
                        (float)Imagem.height}, 
                    (Vector2){*PosX -= 3, *PosY},
                    WHITE);
        }
        else if (Tecla == KEY_D){
            DrawTextureRec(
                    Imagem, 
                    (Rectangle){
                        (float)Frame * larguraFrame, 
                        0, 
                        larguraFrame, 
                        (float)Imagem.height}, 
                    (Vector2){*PosX += 3, *PosY},
                    WHITE);
        }
        else if (Tecla == KEY_W){
            DrawTextureRec(
                    Imagem, 
                    (Rectangle){
                        (float)Frame * larguraFrame, 
                        0, 
                        larguraFrame, 
                        (float)Imagem.height}, 
                    (Vector2){*PosX, *PosY},
                    WHITE);
        }
        else{
            DrawTextureRec(
                    Imagem, 
                    (Rectangle){
                        (float)larguraFrame*Frame, 
                        0, 
                        larguraFrame, 
                        (float)Imagem.height}, 
                    (Vector2){*PosX, *PosY},
                    WHITE);
        }
    }
    if(*PosX<0){
        *PosX=0;
        DrawTextureRec(
                Imagem, 
                (Rectangle){
                    (float)Frame * larguraFrame, 
                    0, 
                    larguraFrame, 
                    (float)Imagem.height}, 
                (Vector2){*PosX, *PosY},
                WHITE);
        
    }
    if(*PosX+larguraFrame>=1500){
        *PosX = 1500 - larguraFrame;
        DrawTextureRec(
                Imagem, 
                (Rectangle){
                    (float)Frame * larguraFrame, 
                    0, 
                    larguraFrame, 
                    (float)Imagem.height}, 
                (Vector2){*PosX, *PosY},
                WHITE);        
    }
}
void carregaImagemheitor(Texture2D Imagem, int Frame, float larguraFrame, 
                    float *const PosX, float *const PosY, long int Tecla)
{
    if(*PosX>=0&&*PosX<=1500-larguraFrame){
        if (Tecla == KEY_J){
            DrawTextureRec(
                    Imagem, 
                    (Rectangle){
                        (float)Frame * larguraFrame, 
                        0, 
                        larguraFrame, 
                        (float)Imagem.height}, 
                    (Vector2){*PosX -= 3, *PosY},
                    WHITE);
        }
        else if (Tecla == KEY_L){
            DrawTextureRec(
                    Imagem, 
                    (Rectangle){
                        (float)Frame * larguraFrame, 
                        0, 
                        larguraFrame, 
                        (float)Imagem.height}, 
                    (Vector2){*PosX += 3, *PosY},
                    WHITE);
        }
        else if (Tecla == KEY_I){
            DrawTextureRec(
                    Imagem, 
                    (Rectangle){
                        (float)Frame * larguraFrame, 
                        0, 
                        larguraFrame, 
                        (float)Imagem.height}, 
                    (Vector2){*PosX, *PosY},
                    WHITE);
        }
        else{
            DrawTextureRec(
                    Imagem, 
                    (Rectangle){
                        (float)larguraFrame*Frame, 
                        0, 
                        larguraFrame, 
                        (float)Imagem.height}, 
                    (Vector2){*PosX, *PosY},
                    WHITE);
        }
    }
    if(*PosX<0){
        *PosX=0;
        DrawTextureRec(
                Imagem, 
                (Rectangle){
                    (float)Frame * larguraFrame, 
                    0, 
                    larguraFrame, 
                    (float)Imagem.height}, 
                (Vector2){*PosX, *PosY},
                WHITE);       
    }
    if(*PosX+larguraFrame>=1500){
        *PosX = 1500 - larguraFrame;

        DrawTextureRec(
                Imagem, 
                (Rectangle){
                    (float)Frame * larguraFrame, 
                    0, 
                    larguraFrame, 
                    (float)Imagem.height}, 
                (Vector2){*PosX, *PosY},
                WHITE);
        
        
    }
}
float diminui_vida_aquiles(float diminui){
    diminui-=0.25;
    return diminui;
}
void diminui_vida_heitor(float *muda_tam, float *muda_pos){
    (*muda_tam)-=0.25;
    (*muda_pos)+=0.25;
}




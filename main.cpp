#include <stdio.h>
#include "raylib.h"

enum STATUS {RIGHT, LEFT};

typedef struct{
    float largura;
    float altura;
}Dimensao;
//teste
typedef struct{
    int Idle;
    int Run;
    int Attack;
}Status;
typedef struct{
    Rectangle barra;   
}Vida;
typedef struct{
    
    float posX;
    float posY;
    int postura;
}Dados;
float diminui_vida_aquiles(float);
void diminui_vida_heitor(float *,float *);
void carregaImagemaquiles(Texture2D Imagem, int Frame, float larguraFrame,
                            float *const PosX, float *const PosY, long int Tecla);
void carregaImagemheitor(Texture2D Imagem, int Frame, float larguraFrame,
                            float *const PosX, float *const PosY, long int Tecla);
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
    
    Image background = LoadImage("background1.png");
    Image carregamento = LoadImage("carregamento.png");
    Image fundofinal=LoadImage("fundofinal.png");
    Image c=LoadImage("textura_config1.png");
    Image v=LoadImage("Versus.png");
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
    
    Texture2D aquilesIdleRight  = LoadTexture("aquilesidle_direita.png");
    Texture2D aquilesIdleLeft  = LoadTexture("aquilesidle_esquerda.png");
    Texture2D aquilesRunRight  = LoadTexture("aquilesrun_direita.png");
    Texture2D aquilesRunLeft  = LoadTexture("aquilesrun_esquerda.png");
    Texture2D aquilesAttackRight  = LoadTexture("aquilesataque_direita.png");
    Texture2D aquilesAttackLeft  = LoadTexture("aquilesataque_esquerda.png");
    Texture2D aquiles_died = LoadTexture("aquiles_dead.png");
    Texture2D aquiles_died2 = LoadTexture("aquiles_dead2.png");
    //
    Texture2D heitorIdleRight  = LoadTexture("heitoridle_direita.png");
    Texture2D heitorIdleLeft  = LoadTexture("heitoridle_esquerda.png");
    Texture2D heitorRunRight  = LoadTexture("heitorrun_direita.png");
    Texture2D heitorRunLeft  = LoadTexture("heitorrun_esquerda.png");
    Texture2D heitorAttackRight  = LoadTexture("heitorataque_direita.png");
    Texture2D heitorAttackLeft  = LoadTexture("heitorataque_esquerda.png");
    Texture2D heitor_died= LoadTexture("heitor_dead.png");
    Texture2D heitor_died2= LoadTexture("heitor_dead2.png");
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
    
    Music music = LoadMusicStream("musica_jogo.mp3");
    Music musicluta= LoadMusicStream("musica_jogo_luta.mp3");
    Sound Sound_attackW =LoadSound("attack.wav");
    Sound Sound_attackI =LoadSound("attack.wav");
    Sound Sound_death =LoadSound("death.wav");
    
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
        if(janela_inicial){                                //esta sera a janela inicial, onde sera a melhor oportunidade para testar 
            if(music_on){UpdateMusicStream(music);         //a manipulacao de audio do menu congig
            SetMusicVolume(music,0.3f);}
                          
            if(!janela_config&&!janela_inst){
                BeginDrawing();
                ClearBackground(RAYWHITE);
                DrawTexture(desert, position.x, position.y, WHITE);
                DrawTexture(configuracoes, 1400, 20, BLACK);
                DrawText("Jogar", SCREEN_WIDTH/2-130, SCREEN_HEIGHT/2, 80, WHITE);              
                DrawText("Instrucoes", SCREEN_WIDTH / 2 - 160, SCREEN_HEIGHT /2+130, 50, WHITE);
                if (CheckCollisionPointRec(GetMousePosition(), config)){                                     
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                        janela_config=true;    
                    }
                }
                if (CheckCollisionPointRec(GetMousePosition(), button_jogar)){
                    DrawText("Jogar", SCREEN_WIDTH/2-130, SCREEN_HEIGHT/2, 80, LIGHTGRAY);
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){                        
                        tela_carregamento=true;  
                        janela_inicial=false;
                        janela_config=false;
                    }
                }
                if (CheckCollisionPointRec(GetMousePosition(), button_inst)) {
                    DrawText("Instrucoes",SCREEN_WIDTH / 2 - 160, SCREEN_HEIGHT /2+130, 50, LIGHTGRAY);
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                        janela_inst = true;
                    }
                }
                EndDrawing();
            }
            else if(!janela_inst){          
                BeginDrawing();
                ClearBackground(RAYWHITE);
                DrawTexture(desert, position.x, position.y, WHITE);
                DrawText("Jogar", SCREEN_WIDTH/2-130, SCREEN_HEIGHT/2, 80, WHITE);
                DrawText("Instrucoes",SCREEN_WIDTH / 2 - 160, SCREEN_HEIGHT /2+130, 50, WHITE);
                DrawTexture(configuracoes, 1425, 8, BLACK);                            
                ////////////////////////////////////////////////
                DrawRectangleRoundedLines(config_lines, 0.3, 1000, 3, BLACK); 
                if(music_on)
                DrawRectangleRounded(config_music_on,0.3,1000,GREEN);
                if(!music_on)
                    DrawRectangleRounded(config_music_off,0.3,1000,RED);
                DrawText("MUSIC on | off",1300,80,20,BLACK);
                DrawText("x",1453,55,30,GRAY);
                ////////////////////////////////////////////////  
                if(CheckCollisionPointRec(GetMousePosition(),config_music_off)){
                    
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                        music_on=false;    
                    }
                }
                if(CheckCollisionPointRec(GetMousePosition(),config_music_on)){
                    
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                        music_on=true;    
                    }
                }
                if(CheckCollisionPointRec(GetMousePosition(),config_close)){
                    DrawText("x",1453,55,30,RED);
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                        janela_config=false;    
                    }
                }
                if (CheckCollisionPointRec(GetMousePosition(), button_jogar)){
                    DrawText("Jogar", SCREEN_WIDTH/2-130, SCREEN_HEIGHT/2, 80, LIGHTGRAY);
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                        tela_carregamento=true;
                        janela_inicial=false;
                    }
                }
                if (CheckCollisionPointRec(GetMousePosition(), button_inst)) {
                    DrawText("Instrucoes",SCREEN_WIDTH / 2 - 160, SCREEN_HEIGHT /2+130, 50, LIGHTGRAY);
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                        janela_inst = true;
                        janela_config=false;
                    }
                }
                EndDrawing();
            }
            else if(!janela_config){
                BeginDrawing();
                ClearBackground(RAYWHITE);
                DrawTexture(desert, position.x, position.y, WHITE);
                DrawText("<-",6,5,30,WHITE);
                DrawRectangleLines(5, 5,30, 30,WHITE);
                
                ////////////////////////////////////////////////
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
                ////////////////////////////////////////////////
                if(CheckCollisionPointRec(GetMousePosition(),button_voltar)){
                    DrawText("<-",6,5,30,LIGHTGRAY);
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                        janela_inst=false; 
                        
                    }
                }
                EndDrawing();
            }
        }
        if(tela_carregamento){// esta e a tela de carregamento, o ideal seria ter uma introducao da guerra de troia aqui
            if(music_on){UpdateMusicStream(music);         //a manipulacao de audio do menu congig
            SetMusicVolume(music,0.3f);}// se quiser aumentar o timer da tela de carregamento, me pergunbta que posso alterar
            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawTexture(telacarregamento, position.x, position.y,WHITE);
            DrawRectangleLines(5, 5,30, 30,WHITE);
            DrawText("<-",6,5,30,WHITE);
            DrawText("Aquiles era filho de Tetis, que o mergulhou nas aguas do rio Esfinge tornando-o \ninvulneravel, exceto  pelo seu calcanhar,por onde sua mae o segurou. O calcanhar de \nAquiles era seu ponto fraco.",100,30,30,WHITE);
            DrawText("\n\n\nHeitor era filho de Priamo, rei de Troia, e no mais famoso confronto da Guerra de Troia,\nAquiles, o maior guerreiro de todos os tempos, venceu facilmente o mais valoroso dos \ntroianos,que era Heitor.",100,30,30,WHITE);
            DrawText("\n\n\n\n\n\nAquiles se recusava a participar da guerra, porem seu grande amigo Patroclo furta-lhe \na armadura e vai para o campo de batalha onde acabou por encontrar a morte nas \nmãos de Heitor,que pensava estar lutando com Aquiles. Enlouquecido de dor pela perda",100,30,30,WHITE);
            DrawText("\n\n\n\n\n\n\n\n\nde seu amigo, Aquiles saltousem armas para o campo de batalha e num bramido demente \ne insano, so pensou em vingar-se e investiu sobre Heitor matando-o.",100,30,30,WHITE);
            apertei_voltar=0;
            if(CheckCollisionPointRec(GetMousePosition(),button_voltar)){
                DrawText("<-",6,5,30,LIGHTGRAY);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                    tela_carregamento=false; 
                    janela_inicial=true;
                    apertei_voltar=1;
                }
            }
            rectTime += GetFrameTime();
            if (rectTime >= 25.0f||apertei_voltar){
                tela_carregamento=false;
                if(!janela_inicial)jogo_rodando=true;
                rectSize=0.0f;
                retangulo_carregamento.width=0.0f;
                rectTime=0.0f;
            }
            rectSize += rectSpeed * GetFrameTime();
            retangulo_carregamento.width = rectSize-8;
            
            DrawRectangleRoundedLines(retangulo_carregamento_lines,0.5,1000,2, WHITE);
            DrawRectangleRounded(retangulo_carregamento,0.5,1000, WHITE);
            EndDrawing();
        }
        if(jogo_rodando){
            if(!janela_config){// mesma ideia da janela inicial, quando a janela de config esta fechada
           
                if(music_on){
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
                //////vida do aquiles              
                if(vida_aquiles.barra.width>250.0f){
                    DrawRectangleRoundedLines(vida_aquiles_linha,0.5,1000,3, GREEN);                   
                    DrawRectangleRounded(vida_aquiles_fundo, 0.5,1000, DARKGREEN);
                    DrawRectangleRounded(vida_aquiles.barra, 0.5,1000, LIME);
                }
                else if(vida_aquiles.barra.width>150.0f&&vida_aquiles.barra.width<250.0f){
                    DrawRectangleRoundedLines(vida_aquiles_linha,0.5,1000,3, GOLD);                   
                    DrawRectangleRounded(vida_aquiles_fundo, 0.5,1000, amarelo_claro);
                    DrawRectangleRounded(vida_aquiles.barra, 0.5,1000, YELLOW);
                }
                else if(vida_aquiles.barra.width<150.0f){          
                    DrawRectangleRoundedLines(vida_aquiles_linha,0.5,1000,3, MAROON);
                    DrawRectangleRounded(vida_aquiles_fundo, 0.5,1000,vermelho_claro);
                    DrawRectangleRounded(vida_aquiles.barra, 0.5,1000, RED);
                }
                //////vida do heitor
                if(vida_heitor.barra.width>250.0f){
                    DrawRectangleRoundedLines(vida_heitor_linha,0.5,1000,3, GREEN);                   
                    DrawRectangleRounded(vida_heitor_fundo, 0.5,1000, DARKGREEN);
                    DrawRectangleRounded(vida_heitor.barra, 0.5,1000, LIME);
                }
                else if(vida_heitor.barra.width>150.0f&&vida_heitor.barra.width<250.0f){
                    DrawRectangleRoundedLines(vida_heitor_linha,0.5,1000,3, GOLD);                   
                    DrawRectangleRounded(vida_heitor_fundo, 0.5,1000,amarelo_claro);
                    DrawRectangleRounded(vida_heitor.barra, 0.5,1000, YELLOW);
                }
                else if(vida_heitor.barra.width<150.0f){          
                    DrawRectangleRoundedLines(vida_heitor_linha,0.5,1000,3, MAROON);
                    DrawRectangleRounded(vida_heitor_fundo, 0.5,1000,vermelho_claro);
                    DrawRectangleRounded(vida_heitor.barra, 0.5,1000, RED);
                }
                
                if (CheckCollisionPointRec(GetMousePosition(), config)){                                     
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                        janela_config=true;    
                    }
                }
                if(CheckCollisionPointRec(GetMousePosition(),button_voltar)){
                    DrawText("<-",6,5,30,LIGHTGRAY);
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                        jogo_rodando=false; 
                        janela_inicial=true;
                    }
                }
                if (IsKeyUp(KEY_A) && IsKeyUp(KEY_D) && IsKeyUp(KEY_W)){
                    if (frame >= maxFrame1.Idle){
                            frame = 0;
                    }
                    if (player1.postura == RIGHT){
                        carregaImagemaquiles(aquilesIdleRight, frame, frameIdle1.largura, 
                        &player1.posX, &player1.posY, KEY_NULL);
                    
                    }
                    else if (player1.postura == LEFT){
                        carregaImagemaquiles(aquilesIdleLeft, frame, frameIdle1.largura, 
                        &player1.posX, &player1.posY, KEY_NULL);
                        
                    }
                    
                }
                else{
                    
                    if (IsKeyDown(KEY_A)){
                        player1.postura = LEFT;
                        if (frame >= maxFrame1.Run){
                            frame = 0;
                        }
                        carregaImagemaquiles(aquilesRunLeft, frame, frameRun1.largura, 
                        &player1.posX, &player1.posY, KEY_A);  
                        
                    }
                    
                    else if (IsKeyDown(KEY_D)){ 
                        player1.postura = RIGHT;
                        if (frame >= maxFrame1.Run){
                            frame = 0;
                        }
                        carregaImagemaquiles(aquilesRunRight, frame, frameRun1.largura, 
                        &player1.posX, &player1.posY, KEY_D);
                    }
                    
                    else if (IsKeyDown(KEY_W)){
                       
                        if (frame >= maxFrame1.Attack){
                            frame = 0;
                        }
                        if (player1.postura == RIGHT){
                            carregaImagemaquiles(aquilesAttackRight, frame, frameAttack1.largura, 
                            &player1.posX, &player1.posY, KEY_W);
                            if( ( (aquiles.x + aquiles.width-40)> (heitor.x) )&&( (aquiles.x+aquiles.width)<(heitor.x+heitor.width+30) ) ){
                                diminui_vida_heitor(&vida_heitor.barra.width,&vida_heitor.barra.x); 
                                PlaySound(Sound_attackW);                               
                            }
                        }
                        else if (player1.postura == LEFT){
                            carregaImagemaquiles(aquilesAttackLeft, frame, frameAttack1.largura, 
                            &player1.posX, &player1.posY, KEY_W);
                            if( ( (aquiles.x) < (heitor.x+heitor.width-40) )&&( (aquiles.x)>(heitor.x) ) ){
                                diminui_vida_heitor(&vida_heitor.barra.width,&vida_heitor.barra.x); 
                                PlaySound(Sound_attackW);
                            }
                        }
                    }
                    
                    //atualizar a posicao do retangulo que contem o boneco1
                    aquiles.x=player1.posX;
                    aquiles.y=player1.posY;
                    
                    
                }
         
                if (IsKeyUp(KEY_J) && IsKeyUp(KEY_L) && IsKeyUp(KEY_I)){
                    if (frame >= maxFrame2.Idle){
                            frame = 0;
                    }
                    if (player2.postura == RIGHT){
                        carregaImagemheitor(heitorIdleRight, frame, frameIdle2.largura, 
                        &player2.posX, &player2.posY, KEY_NULL);
                    
                    }
                    else if (player2.postura == LEFT){
                        carregaImagemheitor(heitorIdleLeft, frame, frameIdle2.largura, 
                        &player2.posX, &player2.posY, KEY_NULL);
                        
                    }
                    
                }
                else if (IsKeyDown(KEY_J)){
                        
                        player2.postura = LEFT;
                        if (frame >= maxFrame2.Run){
                            frame = 0;
                        }
                        carregaImagemheitor(heitorRunLeft, frame, frameRun2.largura, 
                        &player2.posX, &player2.posY, KEY_J);  
                        //printf("frame RunLeft: %d\n", frame);
                    }
                    else if (IsKeyDown(KEY_L)){
                      
                        player2.postura = RIGHT;
                        if (frame >= maxFrame2.Run){
                            frame = 0;
                        }
                        carregaImagemheitor(heitorRunRight, frame, frameRun2.largura, 
                        &player2.posX, &player2.posY, KEY_L);
                        
                    }
                    else if (IsKeyDown(KEY_I)){
                        
                        if (frame >= maxFrame2.Attack){
                            frame = 0;
                        }
                        if (player2.postura == RIGHT){
                            carregaImagemheitor(heitorAttackRight, frame, frameAttack2.largura, 
                            &player2.posX, &player2.posY, KEY_I);
                            if( ( (heitor.x + heitor.width-40)> (aquiles.x) )&&( (heitor.x+heitor.width)<(aquiles.x+aquiles.width+30) ) ){
                                vida_aquiles.barra.width=diminui_vida_aquiles(vida_aquiles.barra.width);
                                PlaySound(Sound_attackW);                                
                            }
                            
                        }
                        else if (player2.postura == LEFT){
                            carregaImagemheitor(heitorAttackLeft, frame, frameAttack2.largura, 
                            &player2.posX, &player2.posY, KEY_I);
                            if( ( (heitor.x) < (aquiles.x+aquiles.width-40) )&&( (heitor.x)>(aquiles.x) ) ){
                                vida_aquiles.barra.width=diminui_vida_aquiles(vida_aquiles.barra.width); 
                                PlaySound(Sound_attackW);                         
                            }
                        }
                    } 
                    
                    //atualizar a posicao do retangulo que contem o boneco2
                    heitor.x=player2.posX;
                    heitor.y=player2.posY;               
                
                EndDrawing();
            }
            else{// mesma ideia da janela inicial, quando a janela de config esta fechada
                if(music_on){
                    UpdateMusicStream(musicluta);
                    SetMusicVolume(musicluta,0.2f);
                } 
                BeginDrawing();             
                ClearBackground(RAYWHITE);
                DrawTexture(fundojogo, position.x, position.y,WHITE);
                DrawTexture(versus,680,30,WHITE);
                //vida dos personagens
                if(vida_aquiles.barra.width>250.0f){
                    DrawRectangleRoundedLines(vida_aquiles_linha,0.5,1000,3, GREEN);                   
                    DrawRectangleRounded(vida_aquiles_fundo, 0.5,1000, DARKGREEN);
                    DrawRectangleRounded(vida_aquiles.barra, 0.5,1000, LIME);
                }
                else if(vida_aquiles.barra.width>150.0f&&vida_aquiles.barra.width<250.0f){
                    DrawRectangleRoundedLines(vida_aquiles_linha,0.5,1000,3, GOLD);                   
                    DrawRectangleRounded(vida_aquiles_fundo, 0.5,1000, amarelo_claro);
                    DrawRectangleRounded(vida_aquiles.barra, 0.5,1000, YELLOW);
                }
                else if(vida_aquiles.barra.width<150.0f){          
                    DrawRectangleRoundedLines(vida_aquiles_linha,0.5,1000,3, MAROON);
                    DrawRectangleRounded(vida_aquiles_fundo, 0.5,1000,vermelho_claro);
                    DrawRectangleRounded(vida_aquiles.barra, 0.5,1000, RED);
                }
                //////vida do heitor
                if(vida_heitor.barra.width>250.0f){
                    DrawRectangleRoundedLines(vida_heitor_linha,0.5,1000,3, GREEN);                   
                    DrawRectangleRounded(vida_heitor_fundo, 0.5,1000, DARKGREEN);
                    DrawRectangleRounded(vida_heitor.barra, 0.5,1000, LIME);
                }
                else if(vida_heitor.barra.width>150.0f&&vida_heitor.barra.width<250.0f){
                    DrawRectangleRoundedLines(vida_heitor_linha,0.5,1000,3, GOLD);                   
                    DrawRectangleRounded(vida_heitor_fundo, 0.5,1000, amarelo_claro);
                    DrawRectangleRounded(vida_heitor.barra, 0.5,1000, YELLOW);
                }
                else if(vida_heitor.barra.width<150.0f){
                    DrawRectangleRoundedLines(vida_heitor_linha,0.5,1000,3, MAROON);
                    DrawRectangleRounded(vida_heitor_fundo, 0.5,1000,vermelho_claro);
                    DrawRectangleRounded(vida_heitor.barra, 0.5,1000, RED);
                }  
                //
                DrawRectangleLines(5, 5,30, 30,WHITE);
                DrawText("<-",6,5,30,WHITE);
      
                if(CheckCollisionPointRec(GetMousePosition(),button_voltar)){
                    DrawText("<-",6,5,30,LIGHTGRAY);
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                        jogo_rodando=false; 
                        janela_inicial=true;
                    }
                }
                if (IsKeyUp(KEY_A) && IsKeyUp(KEY_D) && IsKeyUp(KEY_W)){
                    if (frame >= maxFrame1.Idle){
                            frame = 0;
                    }
                    if (player1.postura == RIGHT){
                        carregaImagemaquiles(aquilesIdleRight, frame, frameIdle1.largura, 
                        &player1.posX, &player1.posY, KEY_NULL);
                    
                    }
                    else if (player1.postura == LEFT){
                        carregaImagemaquiles(aquilesIdleLeft, frame, frameIdle1.largura, 
                        &player1.posX, &player1.posY, KEY_NULL);
                        
                    }
                }
                else{
                    if (IsKeyDown(KEY_A)){
                        player1.postura = LEFT;
                        if (frame >= maxFrame1.Run){
                            frame = 0;
                        }
                        carregaImagemaquiles(aquilesRunLeft, frame, frameRun1.largura, 
                        &player1.posX, &player1.posY, KEY_A);  
                        //printf("frame RunLeft: %d\n", frame);
                    }
                    else if (IsKeyDown(KEY_D)){
                        player1.postura = RIGHT;
                        if (frame >= maxFrame1.Run){
                            frame = 0;
                        }
                        carregaImagemaquiles(aquilesRunRight, frame, frameRun1.largura, 
                        &player1.posX, &player1.posY, KEY_D);
                        
                    }
                    else if (IsKeyDown(KEY_W)){
                        
                        if (frame >= maxFrame1.Attack){
                            frame = 0;
                        }
                        if (player1.postura == RIGHT){
                            carregaImagemaquiles(aquilesAttackRight, frame, frameAttack1.largura, 
                            &player1.posX, &player1.posY, KEY_W); 
                            PlaySound(Sound_attackW);
                            
                        }
                        else if (player1.postura == LEFT){
                            carregaImagemaquiles(aquilesAttackLeft, frame, frameAttack1.largura, 
                            &player1.posX, &player1.posY, KEY_W); 
                            PlaySound(Sound_attackW);
                            
                        }
                    }
                    aquiles.x=player1.posX;
                    aquiles.y=player1.posY;
                }
                if (IsKeyUp(KEY_J) && IsKeyUp(KEY_L) && IsKeyUp(KEY_I)){
                    if (frame >= maxFrame2.Idle){
                            frame = 0;
                    }
                    if (player2.postura == RIGHT){
                        carregaImagemheitor(heitorIdleRight, frame, frameIdle2.largura, 
                        &player2.posX, &player2.posY, KEY_NULL);
                    
                    }
                    else if (player2.postura == LEFT){
                        carregaImagemheitor(heitorIdleLeft, frame, frameIdle2.largura, 
                        &player2.posX, &player2.posY, KEY_NULL);
                        
                    }
                }
                else{
                    if (IsKeyDown(KEY_J)){
                        player2.postura = LEFT;
                        if (frame >= maxFrame2.Run){
                            frame = 0;
                        }
                        carregaImagemheitor(heitorRunLeft, frame, frameRun2.largura, 
                        &player2.posX, &player2.posY, KEY_J);  
                        //printf("frame RunLeft: %d\n", frame);
                    }
                    else if (IsKeyDown(KEY_L)){
                        player2.postura = RIGHT;
                        if (frame >= maxFrame2.Run){
                            frame = 0;
                        }
                        carregaImagemheitor(heitorRunRight, frame, frameRun2.largura, 
                        &player2.posX, &player2.posY, KEY_L);
                        
                    }
                    else if (IsKeyDown(KEY_I)){
                        if (frame >= maxFrame2.Attack){
                            frame = 0;
                        }
                        if (player2.postura == RIGHT){
                            carregaImagemheitor(heitorAttackRight, frame, frameAttack2.largura, 
                            &player2.posX, &player2.posY, KEY_I); 
                            PlaySound(Sound_attackW);
                            
                        }
                        else if (player2.postura == LEFT){
                            carregaImagemheitor(heitorAttackLeft, frame, frameAttack2.largura, 
                            &player2.posX, &player2.posY, KEY_I); 
                            PlaySound(Sound_attackW);
                            
                        }
                    }
                    heitor.x=player2.posX;
                    heitor.y=player2.posY;
                }                 
                DrawTexture(configuracoes, 1425, 8, BLACK);                            
                ////////////////////////////////////////////////
                DrawRectangleRoundedLines(config_lines, 0.3, 1000, 3, BLACK); 
                if(music_on)
                DrawRectangleRounded(config_music_on,0.3,1000,GREEN);
                if(!music_on)
                    DrawRectangleRounded(config_music_off,0.3,1000,RED);
                DrawText("MUSIC on | off",1300,80,20,BLACK);
                
                DrawText("x",1453,55,30,GRAY);
                ////////////////////////////////////////////////  
                if(CheckCollisionPointRec(GetMousePosition(),config_music_off)){
                    
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                        music_on=false;    
                    }
                }
                if(CheckCollisionPointRec(GetMousePosition(),config_music_on)){
                    
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                        music_on=true;    
                    }
                }
                if(CheckCollisionPointRec(GetMousePosition(),config_close)){
                    DrawText("x",1453,55,30,RED);
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                        janela_config=false;    
                    }
                    
                }EndDrawing();
            }
            if (timer >= 0.2){
                // atualiza o frame
                void atualizaFrame(float *const ptrTimer, int *const ptrFrame);
                atualizaFrame(&timer, &frame);
            }
            timer += GetFrameTime();
            if(vida_heitor.barra.width==0.0f){//aqui vamos averiguar qual dos personagens morre primeiro
                jogo_rodando=false;
                aquiles_win=true;
                PlaySound(Sound_death);
                frame=0;
            } 
            if(vida_aquiles.barra.width==0.0f){
                jogo_rodando=false;
                heitor_win=true;
                PlaySound(Sound_death);
                frame=0;
            }
        }
        //----------------------------------------------------------------------------------
        
        if(aquiles_win){//aqui sera a janela de frames que aquiles ganha, com heitor morrendo
            
            BeginDrawing();
                ClearBackground(RAYWHITE);
                DrawTexture(fundojogo, position.x, position.y,WHITE);
                DrawTexture(configuracoes, 1400, 20, WHITE);
                DrawTexture(versus,680,30,WHITE);
                DrawRectangleLines(5, 5,30, 30,WHITE);
                DrawText("<-",6,5,30,WHITE);
                
                //////vida do aquiles              
                if(vida_aquiles.barra.width>250.0f){
                    DrawRectangleRoundedLines(vida_aquiles_linha,0.5,1000,3, GREEN);                   
                    DrawRectangleRounded(vida_aquiles_fundo, 0.5,1000, DARKGREEN);
                    DrawRectangleRounded(vida_aquiles.barra, 0.5,1000, LIME);
                }
                else if(vida_aquiles.barra.width>150.0f&&vida_aquiles.barra.width<250.0f){
                    DrawRectangleRoundedLines(vida_aquiles_linha,0.5,1000,3, GOLD);                   
                    DrawRectangleRounded(vida_aquiles_fundo, 0.5,1000, amarelo_claro);
                    DrawRectangleRounded(vida_aquiles.barra, 0.5,1000, YELLOW);
                }
                else if(vida_aquiles.barra.width<150.0f){          
                    DrawRectangleRoundedLines(vida_aquiles_linha,0.5,1000,3, MAROON);
                    DrawRectangleRounded(vida_aquiles_fundo, 0.5,1000,vermelho_claro);
                    DrawRectangleRounded(vida_aquiles.barra, 0.5,1000, RED);
                }
                //////vida do heitor
                if(vida_heitor.barra.width>250.0f){
                    DrawRectangleRoundedLines(vida_heitor_linha,0.5,1000,3, GREEN);                   
                    DrawRectangleRounded(vida_heitor_fundo, 0.5,1000, DARKGREEN);
                    DrawRectangleRounded(vida_heitor.barra, 0.5,1000, LIME);
                }
                else if(vida_heitor.barra.width>150.0f&&vida_heitor.barra.width<250.0f){
                    DrawRectangleRoundedLines(vida_heitor_linha,0.5,1000,3, GOLD);                   
                    DrawRectangleRounded(vida_heitor_fundo, 0.5,1000,amarelo_claro);
                    DrawRectangleRounded(vida_heitor.barra, 0.5,1000, YELLOW);
                }
                else if(vida_heitor.barra.width<150.0f){          
                    DrawRectangleRoundedLines(vida_heitor_linha,0.5,1000,3, MAROON);
                    DrawRectangleRounded(vida_heitor_fundo, 0.5,1000,vermelho_claro);
                    DrawRectangleRounded(vida_heitor.barra, 0.5,1000, RED);
                }
                //                
                if(CheckCollisionPointRec(GetMousePosition(),button_voltar)){
                    DrawText("<-",6,5,30,LIGHTGRAY);
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                        aquiles_win=false; 
                        janela_inicial=true;
                    }
                }
                
                    
                    if (player1.postura == RIGHT){
                        carregaImagemaquiles(aquilesIdleRight, frame, frameIdle1.largura, 
                        &player1.posX, &player1.posY, KEY_NULL);
                    
                    }
                    else if (player1.postura == LEFT){
                        carregaImagemaquiles(aquilesIdleLeft, frame, frameIdle1.largura, 
                        &player1.posX, &player1.posY, KEY_NULL);
                        
                    }
                                                         
                if (player2.postura == RIGHT){
                    if(frame<4){
                        carregaImagemheitor(heitor_died, frame, player2Dead.largura, 
                                &player2.posX, &player2.posY, KEY_NULL);        
                    }
                }
                else if (player2.postura == LEFT){
                    if(frame<4){
                        carregaImagemheitor(heitor_died2, frame, player2Dead.largura, 
                                &player2.posX, &player2.posY, KEY_NULL);
                    }    
                }              
                if(frame<4){
                    if (timer >= 0.3){                        
                        // atualiza o frame
                        void atualizaFrame(float *const ptrTimer, int *const ptrFrame);
                        atualizaFrame(&timer, &frame);
                    }
                }
                timer += GetFrameTime();
                if(frame==4){
                    if (player2.postura == RIGHT){
                        DrawTextureRec(heitor_died,(Rectangle){(float)player2Dead.largura*3,0,player2Dead.largura,(float)heitor_died.height},(Vector2){player2.posX, player2.posY},WHITE);
                    }
                    if (player2.postura == LEFT){
                        DrawTextureRec(heitor_died2,(Rectangle){(float)0*player2Dead.largura,0,player2Dead.largura,(float)heitor_died.height},(Vector2){player2.posX, player2.posY},WHITE);
                    }
                }
                //pequeno texto de vitoria e botao para reiniciar game                
                DrawRectangleRoundedLines(end_of_game, 0.3, 1000, 3, BLACK);
                DrawRectangleRounded(end_of_game, 0.3, 1000, BLANK);
                DrawRectangleRoundedLines(button_restart,0.3,1000,2,BLACK);
                DrawText("AQUILES WINS",end_of_game.x+40,end_of_game.y+40,30,BLACK);
                DrawText("Restart Game",end_of_game.x+80,end_of_game.y+100,20,BLACK);
                if(CheckCollisionPointRec(GetMousePosition(),button_restart)){
                    DrawText("Restart Game",end_of_game.x+80,end_of_game.y+100,20,RED);
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                        aquiles_win=false; 
                        janela_inicial=true;
                        vida_aquiles.barra.width=350;
                        vida_heitor.barra.width=350;
                        vida_heitor.barra.x=920;
                        player1.posX = 200;
                        player2.posX = 1000;
                    }
                }
            EndDrawing();
        }
           
        if(heitor_win){//aqui seria o frame que heitor ganha, com aquiles morrendo.
            
            BeginDrawing();
                ClearBackground(RAYWHITE);
                DrawTexture(fundojogo, position.x, position.y,WHITE);
                DrawTexture(configuracoes, 1400, 20, WHITE);
                DrawTexture(versus,680,30,WHITE);
                DrawRectangleLines(5, 5,30, 30,WHITE);
                DrawText("<-",6,5,30,WHITE);
                
                //////vida do aquiles              
                if(vida_aquiles.barra.width>250.0f){
                    DrawRectangleRoundedLines(vida_aquiles_linha,0.5,1000,3, GREEN);                   
                    DrawRectangleRounded(vida_aquiles_fundo, 0.5,1000, DARKGREEN);
                    DrawRectangleRounded(vida_aquiles.barra, 0.5,1000, LIME);
                }
                else if(vida_aquiles.barra.width>150.0f&&vida_aquiles.barra.width<250.0f){
                    DrawRectangleRoundedLines(vida_aquiles_linha,0.5,1000,3, GOLD);                   
                    DrawRectangleRounded(vida_aquiles_fundo, 0.5,1000, amarelo_claro);
                    DrawRectangleRounded(vida_aquiles.barra, 0.5,1000, YELLOW);
                }
                else if(vida_aquiles.barra.width<150.0f){          
                    DrawRectangleRoundedLines(vida_aquiles_linha,0.5,1000,3, MAROON);
                    DrawRectangleRounded(vida_aquiles_fundo, 0.5,1000,vermelho_claro);
                    DrawRectangleRounded(vida_aquiles.barra, 0.5,1000, RED);
                }
                //////vida do heitor
                if(vida_heitor.barra.width>250.0f){
                    DrawRectangleRoundedLines(vida_heitor_linha,0.5,1000,3, GREEN);                   
                    DrawRectangleRounded(vida_heitor_fundo, 0.5,1000, DARKGREEN);
                    DrawRectangleRounded(vida_heitor.barra, 0.5,1000, LIME);
                }
                else if(vida_heitor.barra.width>150.0f&&vida_heitor.barra.width<250.0f){
                    DrawRectangleRoundedLines(vida_heitor_linha,0.5,1000,3, GOLD);                   
                    DrawRectangleRounded(vida_heitor_fundo, 0.5,1000,amarelo_claro);
                    DrawRectangleRounded(vida_heitor.barra, 0.5,1000, YELLOW);
                }
                else if(vida_heitor.barra.width<150.0f){          
                    DrawRectangleRoundedLines(vida_heitor_linha,0.5,1000,3, MAROON);
                    DrawRectangleRounded(vida_heitor_fundo, 0.5,1000,vermelho_claro);
                    DrawRectangleRounded(vida_heitor.barra, 0.5,1000, RED);
                }
                //                
                if(CheckCollisionPointRec(GetMousePosition(),button_voltar)){
                    DrawText("<-",6,5,30,LIGHTGRAY);
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                        aquiles_win=false; 
                        janela_inicial=true;
                    }
                }                                  
                if (player2.postura == RIGHT){
                    carregaImagemheitor(heitorIdleRight, frame, frameIdle2.largura, 
                    &player2.posX, &player2.posY, KEY_NULL);                    
                }
                else if (player2.postura == LEFT){
                    carregaImagemheitor(heitorIdleLeft, frame, frameIdle2.largura, 
                    &player2.posX, &player2.posY, KEY_NULL);                        
                }
                if (player1.postura == RIGHT){
                    if(frame<4){
                        carregaImagemaquiles(aquiles_died, frame, player1Dead.largura, 
                                &player1.posX, &player1.posY, KEY_NULL);        
                    }
                }
                else if (player1.postura == LEFT){
                    if(frame<4){
                        carregaImagemaquiles(aquiles_died2, frame, player1Dead.largura, 
                                &player1.posX, &player1.posY, KEY_NULL);
                    }    
                }
                if(frame<4){
                    if (timer >= 0.3){                        
                        // atualiza o frame
                        void atualizaFrame(float *const ptrTimer, int *const ptrFrame);
                        atualizaFrame(&timer, &frame);
                    }
                }
                timer += GetFrameTime();
                if(frame==4){
                    if (player1.postura == RIGHT){
                        DrawTextureRec(aquiles_died,(Rectangle){(float)player1Dead.largura*3,0,player1Dead.largura,(float)aquiles_died.height},(Vector2){player1.posX, player1.posY},WHITE);
                    }
                    if (player1.postura == LEFT){
                        DrawTextureRec(aquiles_died2,(Rectangle){(float)0*player1Dead.largura,0,player1Dead.largura,(float)aquiles_died2.height},(Vector2){player1.posX, player1.posY},WHITE);
                    }
                }
                //pequeno texto de vitoria e botao para reiniciar game 
                DrawRectangleRoundedLines(end_of_game, 0.3, 1000, 3, BLACK);
                DrawRectangleRounded(end_of_game, 0.3, 1000, BLANK);
                DrawRectangleRoundedLines(button_restart,0.3,1000,2,BLACK);
                DrawText("HEITOR WINS",end_of_game.x+40,end_of_game.y+40,30,BLACK);
                DrawText("Restart Game",end_of_game.x+80,end_of_game.y+100,20,BLACK);
                if(CheckCollisionPointRec(GetMousePosition(),button_restart)){
                    DrawText("Restart Game",end_of_game.x+80,end_of_game.y+100,20,RED);
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                        heitor_win=false; 
                        janela_inicial=true;
                        vida_aquiles.barra.width=350;
                        vida_heitor.barra.width=350;
                        vida_heitor.barra.x=920;
                        player1.posX = 200;
                        player2.posX = 1000;
                    }
                }
            EndDrawing();
        }
    }             
    // De-Initialization
    //--------------------------------------------------------------------------------------
    
    UnloadSound(Sound_death);
    UnloadSound(Sound_attackW);
    UnloadSound(Sound_attackI);
    UnloadMusicStream(music); 
    UnloadMusicStream(musicluta);     
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
    CloseAudioDevice();         // Close audio device (music streaming is automatically stopped)

    CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    
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




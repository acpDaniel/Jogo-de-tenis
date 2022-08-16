#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

const int limiteBola = 12;
const int pontuacaoMax = 10;
const float FPS = 100;  


const int SCREEN_W = 680;
const int SCREEN_H = 650;
 

const int rect_w = 100;
const int rect_h = 30;
 
 
void desenhaQuadra(){
	
	al_clear_to_color(al_map_rgb(0,210,0));
	al_draw_line(0 , SCREEN_H/2 , SCREEN_W , SCREEN_H/2 , al_map_rgb(255,255,255) , 3);
	
}
// x1 , y1 são cordenadas do pontos esquerdo superior do retangulo e x2 , y2 cordenadas do ponto direito inferior do retangulo
typedef struct jogador {
	float x1,y1, x2,y2;
	int direita, esquerda, cima, baixo;
	ALLEGRO_COLOR cor;
	int id; 
	int velocidade;
	
}jogador;

//jogador 1 = vermelho
// valores de direita,esquerda,baixo,cima = 0 significa que ele não ta andando nessas direções
void initJogador1(jogador *jogador){
	jogador->x1 = SCREEN_W/2 - rect_w/2 ;
	jogador->y1 = SCREEN_H - 4* rect_h;
	jogador->x2 = SCREEN_W/2 + rect_w/2;
	jogador->y2 = SCREEN_H - 3*rect_h;
	jogador-> cor = al_map_rgb(255,0,0);
	jogador->direita = 0;
	jogador->esquerda = 0;
	jogador->cima = 0;
	jogador->baixo = 0;
	jogador->velocidade = 2;
}

//jogador 2 = azul
// valores de direita,esquerda,baixo,cima = 0 significa que ele não ta andando nessas direções
void initJogador2(jogador *jogador){
	jogador->x1 = SCREEN_W/2 - rect_w/2 ;
	jogador->y1 = 3*rect_h;
	jogador->x2 = SCREEN_W/2 + rect_w/2;
	jogador->y2 = 4* rect_h;
	jogador-> cor = al_map_rgb(0,0,255);
	jogador->direita = 0;
	jogador->esquerda = 0;
	jogador->cima = 0;
	jogador->baixo = 0;
	jogador->velocidade = 2;
}


void desenhaJogadores(jogador jogador1, jogador jogador2){
	al_draw_filled_rectangle(jogador1.x1,jogador1.y1,jogador1.x2,jogador1.y2,jogador1.cor);
	al_draw_filled_rectangle(jogador2.x1,jogador2.y1,jogador2.x2,jogador2.y2,jogador2.cor);
}


void atualizaPosicaoJogadores(jogador *jogador1, jogador *jogador2){
	// jogador1 ta indo para esquerda e tem espaço para movimentar para esquerda sem passar do limite da borda
	if(jogador1->esquerda && jogador1->x1 - jogador1->velocidade >= 0){
		jogador1->x1 -= jogador1->velocidade;
		jogador1->x2 -= jogador1->velocidade;
	}
	// jogador1 ta indo para direita e tem espaço para movimentar para direita sem passar do limite da borda
	if(jogador1->direita && jogador1->x2 + jogador1->velocidade <= SCREEN_W){
		jogador1->x1 += jogador1->velocidade;
		jogador1->x2 += jogador1->velocidade;
	}
	// jogador1 ta indo para cima e tem espaço para movimentar para cima sem passar do limite da borda
	if(jogador1->cima && jogador1->y1 - jogador1->velocidade >= SCREEN_H/2){
		jogador1->y1 -= jogador1->velocidade;
		jogador1->y2 -= jogador1->velocidade;
	}
	// jogador1 ta indo para baixo e tem espaço para movimentar para baixo sem passar do limite da borda
	if(jogador1->baixo && jogador1->y2 + jogador1->velocidade <= SCREEN_H){
		jogador1->y1 += jogador1->velocidade;
		jogador1->y2 += jogador1->velocidade;
	}
	// jogador2 ta indo para esquerda e tem espaço para movimentar para esquerda sem passar do limite da borda
	if(jogador2->esquerda && jogador2->x1 - jogador2->velocidade >= 0 ){
		jogador2->x1 -= jogador2->velocidade;
		jogador2->x2 -= jogador2->velocidade;
	}
	// jogador2 ta indo para direita e tem espaço para movimentar para direita sem passar do limite da borda
	if(jogador2->direita  && jogador2->x2 + jogador2->velocidade <= SCREEN_W){
		jogador2->x1 += jogador2->velocidade;
		jogador2->x2 += jogador2->velocidade;
	}
	// jogador2 ta indo para cima e tem espaço para movimentar para cima sem passar do limite da borda
	if(jogador2->cima && jogador2->y1 - jogador2->velocidade >= 0 ){
		jogador2->y1 -= jogador2->velocidade;
		jogador2->y2 -= jogador2->velocidade;
	}
	// jogador2 ta indo para baixo e tem espaço para movimentar para baixo sem passar do limite da borda
	if(jogador2->baixo && jogador2->y2 + jogador2-> velocidade <= SCREEN_H/2){
		jogador2->y1 += jogador2->velocidade;
		jogador2->y2 += jogador2->velocidade;
	}
	
} 

typedef struct canhao{
	int x,y;
	int id;
	bool cima;
	bool direita;
} canhao;


void initCanhoes(canhao *canhao, int i){
	//canhão superior direita, as propriedades cima,direita são false pq as bolas que saem dele vao para esquerda e para baixo
	if(i==0){
		canhao->x = SCREEN_W;
		canhao->y = 0;
		canhao->id = i;
		canhao->cima = false;
		canhao->direita = false;
	}
	//canhão superior esquerda, as propriedades cima é false e direita é true pq as bolas vao pra direita e para baixo
	else if(i==1){
		canhao->x = 0;
		canhao->y = 0;
		canhao->id = i;
		canhao->cima = false;
		canhao->direita = true;	
	}
	//canhão inferior esquerda, as propriedades cima e direita são true pq as bolas que saem dele vao para direita e para cima
	else if(i==2){
		canhao->x = 0;
		canhao->y = SCREEN_H;
		canhao->id = i;
		canhao->cima = true;
		canhao->direita = true;	
	}
	//canhão inferior direita, as propriedades cima é true e direita é false pq as bolas vao para esquerda e para cima
	else if(i==3){
		canhao->x = SCREEN_W;
		canhao->y = SCREEN_H;
		canhao->id = i;
		canhao->cima = true;
		canhao->direita = false;	
	}
}

typedef struct bola{
	float cx , cy;
	int raio;
	float velocidadex,velocidadey;
	float tamanho;
	bool emJogo;
	bool cima;
	bool direita;
	int id;
	int posicaoCanhao;
	
	ALLEGRO_COLOR cor;
} bola;


// parametros iniciais de uma bola (de uma bola no geral)
void initBola(bola *bola, int id){
	bola->id = id;
	bola->raio = 1;
	bola->emJogo = false;
}

// desenha somente as bolas que estão em jogo
void desenhaBola(bola bolas[]){
	int i =0; 	
	for(i=0; i<limiteBola;i++){
		if(bolas[i].emJogo == true){
			al_draw_circle(bolas[i].cx , bolas[i].cy , bolas[i].raio , bolas[i].cor, bolas[i].tamanho);
		}
	}
}
 

// retorna o endereço de uma bola que não ta em jogo
bola* pegaBolaDisponivel(bola bolas[]){
	int i;
	for(i=0;i<limiteBola;i++){
		if(bolas[i].emJogo == false){
			return &bolas[i];
		}
	}
	return NULL;
}

// lança uma bola atribuindo alguns valores aleatoriamente e alguns valores de acordo com as propriedades do canhão que vai lançar ela
void lancaBola(bola *bola, canhao canhoes[], int *canhaoAtual){
		bola->posicaoCanhao = *canhaoAtual;
		bola->cx = canhoes[*canhaoAtual].x;
		bola->cy = canhoes[*canhaoAtual].y;
		bola->velocidadex = (0.25+(float)rand()/(float)(RAND_MAX)) * 2.0; 
		bola->velocidadey = (0.10+(float)rand()/(float)(RAND_MAX)) * 1.5; 
		bola->tamanho = 6+rand()%6;
		bola->cima = canhoes[*canhaoAtual].cima;
		bola->direita = canhoes[*canhaoAtual].direita;
		bola->cor = al_map_rgb(255, 229, 0);
		bola->emJogo = true;
		
		if(*canhaoAtual == 3){
			*canhaoAtual = 0;
		}else{
			*canhaoAtual = *canhaoAtual + 1;
		}
}	
 
// faz as bolas se movimentarem e em caso de colisao com parede lateral inverte a direção 
void atualizaPosicaoBola(bola bolas[]){
	int i = 0;
				
	for(i=0;i<limiteBola;i++){
		if(bolas[i].emJogo == true){	
			if(bolas[i].cima == true){
				bolas[i].cy -= bolas[i].velocidadey;
			}
			else{
				bolas[i].cy += bolas[i].velocidadey;
			}
			if(bolas[i].direita == true){
				bolas[i].cx += bolas[i].velocidadex;
				if(bolas[i].cx > SCREEN_W){
					 bolas[i].direita = false;
				 }
			}else{
				bolas[i].cx -= bolas[i].velocidadex;
				if(bolas[i].cx < 0){
					 bolas[i].direita = true;
				 }
			}	
		}
	}
}

// atualiza caso de colisao com jogador 
 void atualizaPorColisaoj1(bola bolas[], jogador j1){
	 int i= 0;
	 for(i=0;i<12;i++){
		 // vai mudar de direção apenas se a bola tiver indo para baixo e as cordenadas da bola estiver entre os pontos que delimitam o jogador
		 if(bolas[i].cx  +bolas[i].raio > j1.x1 && bolas[i].cx + bolas[i].raio < j1.x2 && bolas[i].cy + bolas[i].raio > j1.y1 && bolas[i].cy + bolas[i].raio < j1.y2 && bolas[i].cima == false){ 
			 bolas[i].cima = true;
		 }
	 }
}
 void atualizaPorColisaoj2(bola bolas[],  jogador j2){
	 int i= 0;
	 for(i=0;i<12;i++){
		 // vai mudar de direção apenas se a bola tiver indo para cima e as cordenadas da bola estiver entre os pontos que delimitam o jogador
		 if(bolas[i].cx  + bolas[i].raio> j2.x1 && bolas[i].cx + bolas[i].raio < j2.x2 && bolas[i].cy + bolas[i].raio< j2.y2 && bolas[i].cy + bolas[i].raio> j2.y1 && bolas[i].cima == true){
			 bolas[i].cima = false;
		 }
	 }
	
}

void pontuacao(bola bolas[],int *pontuacaoJogador1, int *pontuacaoJogador2){
	int i = 0;
	for(i=0; i< limiteBola; i++){
		if(bolas[i].emJogo){
			if(bolas[i].cy < 0){	
				 bolas[i].emJogo = false;
				*pontuacaoJogador1 = *pontuacaoJogador1 +1 ;
			}
			else if(bolas[i].cy > SCREEN_H ){
				 bolas[i].emJogo = false;
				*pontuacaoJogador2 = *pontuacaoJogador2 +1;		
			}
			
		}
	}
}


int main(int argc, char **argv){
	srand(time(NULL));
	float aleatorio = ((float)rand()/(float)(RAND_MAX)) * 2.0;  // fiz isso aqui por causa do rand float ja que o primeiro valor é sempre mais ou menos igual
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
   
	//----------------------- rotinas de inicializacao ---------------------------------------
    
	//inicializa o Allegro
	if(!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}
	
    //inicializa o módulo de primitivas do Allegro
    if(!al_init_primitives_addon()){
		fprintf(stderr, "failed to initialize primitives!\n");
        return -1;
    }	
	
	//inicializa o modulo que permite carregar imagens no jogo
	if(!al_init_image_addon()){
		fprintf(stderr, "failed to initialize image module!\n");
		return -1;
	}
   
	//cria um temporizador que incrementa uma unidade a cada 1.0/FPS segundos
    timer = al_create_timer(1.0 / FPS);
    if(!timer) {
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}
 
	//cria uma tela com dimensoes de SCREEN_W, SCREEN_H pixels
	display = al_create_display(SCREEN_W, SCREEN_H);
	if(!display) {
		fprintf(stderr, "failed to create display!\n");
		al_destroy_timer(timer);
		return -1;
	}

	//instala o teclado
	if(!al_install_keyboard()) {
		fprintf(stderr, "failed to install keyboard!\n");
		return -1;
	}
	
	//inicializa o modulo allegro que carrega as fontes
	al_init_font_addon();

	//inicializa o modulo allegro que entende arquivos tff de fontes
	if(!al_init_ttf_addon()) {
		fprintf(stderr, "failed to load tff font module!\n");
		return -1;
	}
	
	//carrega o arquivo arial.ttf da fonte Arial e define que sera usado o tamanho 32 (segundo parametro)
    ALLEGRO_FONT *size_32 = al_load_font("arial.ttf", 32, 1);   
	if(size_32 == NULL) {
		fprintf(stderr, "font file does not exist or cannot be accessed!\n");
	}

 	//cria a fila de eventos
	event_queue = al_create_event_queue();
	if(!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_display(display);
		return -1;
	}
   


	//registra na fila os eventos de tela (ex: clicar no X na janela)
	al_register_event_source(event_queue, al_get_display_event_source(display));
	//registra na fila os eventos de tempo: quando o tempo altera de t para t+1
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	//registra na fila os eventos de teclado (ex: pressionar uma tecla)
	al_register_event_source(event_queue, al_get_keyboard_event_source());


	//inicia o temporizador
	al_start_timer(timer);
	
	//criar os jogadores
	jogador jogador1;
	jogador jogador2;
	initJogador1(&jogador1);
	initJogador2(&jogador2);
	
	//criar canhões
	canhao canhoes[4];
	int i;
	for(i=0;i<4;i++){
		initCanhoes(&canhoes[i],i);
	}
	
	int canhaoAtual = 0;
	
	//criar bolas
	bola bolas[limiteBola];
	for(i=0;i<limiteBola;i++)
		initBola(&bolas[i],i);
	
	
	al_flip_display();
	
	int pontuacaoJogador1 = 0; // jogador vermelho 
	int pontuacaoJogador2 = 0; // jogador azul
	
	int vitoriasJogador1, derrotasJogador1;
	int vitoriasJogador2, derrotasJogador2;
	FILE *historico = fopen("historicoJogo.txt","r");
	fscanf(historico,"%d %d %d %d",&vitoriasJogador1,&derrotasJogador1,&vitoriasJogador2,&derrotasJogador2);
	fclose(historico);
	
	int programaRodando = 1; 
	int fimJogo = 0;	
	
	while(programaRodando) {

		ALLEGRO_EVENT ev;
		//espera por um evento e o armazena na variavel de evento ev
		al_wait_for_event(event_queue, &ev);
		if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			programaRodando = 0;
		}else{
			if(fimJogo == 0){
				//se o tipo de evento for um evento do temporizador, ou seja, se o tempo passou de t para t+1
				if(ev.type == ALLEGRO_EVENT_TIMER) {
					
					
					desenhaQuadra();
					al_draw_textf(size_32, al_map_rgb(255,0,0),150,20, 1, "%d", pontuacaoJogador1); 
					al_draw_textf(size_32, al_map_rgb(0,0,255), 530, 20, 1, "%d", pontuacaoJogador2); 
					
					atualizaPosicaoJogadores(&jogador1,&jogador2);
					desenhaJogadores(jogador1,jogador2);
							
					// sempre que o timer for um numero inteiro maior que zero e multiplo de 5
					if(al_get_timer_count(timer)%(int)FPS == 0 && (int)(al_get_timer_count(timer)/FPS) % 5 == 0){
						bola* bola = pegaBolaDisponivel(bolas);
						if(bola != NULL)
						lancaBola(bola, canhoes, &canhaoAtual);
					}
					atualizaPosicaoBola(bolas);
					pontuacao(bolas, &pontuacaoJogador1, &pontuacaoJogador2);
					desenhaBola(bolas);
					if(pontuacaoJogador1 == pontuacaoMax || pontuacaoJogador2 == pontuacaoMax){
						fimJogo = 1;
						if(pontuacaoJogador1 == pontuacaoMax){
							vitoriasJogador1++;
							derrotasJogador2++;
						}else if( pontuacaoJogador2 == pontuacaoMax){
							vitoriasJogador2++;
							derrotasJogador1++;
						}
						FILE *historico = fopen("historicoJogo.txt","w");
						fprintf(historico,"%d %d %d %d", vitoriasJogador1, derrotasJogador1,vitoriasJogador2, derrotasJogador2);
						fclose(historico);
					}
					
					//atualiza a tela (quando houver algo para mostrar)
					al_flip_display();
					
					if(al_get_timer_count(timer)%(int)FPS == 0)
						printf("\n%d segundos se passaram...", (int)(al_get_timer_count(timer)/FPS));
				}
				//se o tipo de evento for um pressionar de uma tecla
				else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
					  if(ev.keyboard.keycode == ALLEGRO_KEY_K){
						  atualizaPorColisaoj1(bolas,jogador1);
					  }
					  if(ev.keyboard.keycode == ALLEGRO_KEY_P){
						  atualizaPorColisaoj2(bolas,jogador2);
					  }
					
					switch(ev.keyboard.keycode){
						case ALLEGRO_KEY_A:
						  jogador1.esquerda = 1;
						  break;
						  
						case ALLEGRO_KEY_D:
						  jogador1.direita = 1;
						  break;  
						  
						case ALLEGRO_KEY_W:
						  jogador1.cima = 1;
						  break; 
						  
						case ALLEGRO_KEY_S:
						  jogador1.baixo = 1;
						  break;    
						  
						case ALLEGRO_KEY_LEFT:
						  jogador2.esquerda = 1;
						  break;	  
						  
						 case ALLEGRO_KEY_RIGHT:
						  jogador2.direita = 1;
						  break;	
						
						case ALLEGRO_KEY_UP:
						  jogador2.cima = 1;
						  break;	

						case ALLEGRO_KEY_DOWN:
						  jogador2.baixo = 1;
						  break;	 
						  
					}
				}
				
				else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
					switch(ev.keyboard.keycode){
						case ALLEGRO_KEY_A:
						  jogador1.esquerda = 0;
						  break;
						  
						case ALLEGRO_KEY_D:
						  jogador1.direita = 0;
						  break;  
						  
						case ALLEGRO_KEY_W:
						  jogador1.cima = 0;
						  break; 
						  
						case ALLEGRO_KEY_S:
						  jogador1.baixo = 0;
						  break;    

						case ALLEGRO_KEY_LEFT:
						  jogador2.esquerda = 0;
						  break;	

						case ALLEGRO_KEY_RIGHT:
						  jogador2.direita = 0;
						  break;	
						
						case ALLEGRO_KEY_UP:
						  jogador2.cima = 0;
						  break;	

						case ALLEGRO_KEY_DOWN:
						  jogador2.baixo = 0;
						  break;	
			
					}
				}
			}
			else{
				al_clear_to_color(al_map_rgb(230,232,250));
				al_draw_textf(size_32, al_map_rgb(0,0,0),SCREEN_W/2,SCREEN_H/2-300, 1, "Pontuações:");  
				al_draw_textf(size_32, al_map_rgb(255,0,0),SCREEN_W/2,SCREEN_H/2-250, 1, "Pontuação jogador 1: %d", pontuacaoJogador1);  
				al_draw_textf(size_32, al_map_rgb(0,0,255), SCREEN_W/2, SCREEN_H/2-200, 1, "Pontuação jogador 2: %d", pontuacaoJogador2);
				al_draw_textf(size_32, al_map_rgb(0,0,0),SCREEN_W/2,SCREEN_H/2, 1, "Histórico de Partidas:");  
				al_draw_textf(size_32, al_map_rgb(255,0,0),SCREEN_W/2,SCREEN_H/2+50, 1, "jogador 1:  %d vitorias e %d derrotas", vitoriasJogador1, derrotasJogador1); 
				al_draw_textf(size_32, al_map_rgb(0,0,255),SCREEN_W/2,SCREEN_H/2+100, 1, "jogador 2:  %d vitorias e %d derrotas", vitoriasJogador2, derrotasJogador2); 
				al_flip_display();		
			}
		}

	

	} //fim do while
     
	//procedimentos de fim de jogo (fecha a tela, limpa a memoria, etc)
 
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
   
 
	return 0;
}





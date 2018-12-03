#include "meufiltro.h"
#include<math.h>

void inicializarWidgetsMeuFiltro() {
	//widgets das opcoes de filtro
	widgetControleNivel = 	gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 0, 30, 1);
	//widgetMisturarCanais = gtk_check_button_new_with_label("Misturar canais");

	widgetPinceladasComprimento = gtk_spin_button_new_with_range(1,640000,1);
	widgetPinceladasAltura = gtk_spin_button_new_with_range(1,640000,1);
	widgetComprimento = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 1, 100, 1);
	//widgetEspessura = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 1, 100, 1);
	widgetAleatorio = gtk_check_button_new_with_label("Pintar Aleatoriamente");

	widgetCanvasR = gtk_spin_button_new_with_range(0,255,1);
	widgetCanvasG = gtk_spin_button_new_with_range(0,255,1);
	widgetCanvasB = gtk_spin_button_new_with_range(0,255,1);

	widgetLabelComprimento = gtk_label_new("Tamanho das pinceladas");
	widgetLabelPinceladasAltura = gtk_label_new("Quantidade de pinceladas por altura");
	widgetLabelPinceladasComprimento = gtk_label_new("Quantidade de pinceladas por comprimento");

	//g_signal_connect(G_OBJECT(widgetControleNivel), "value-changed", G_CALLBACK(funcaoAplicar), NULL);
}

void adicionarWidgetsMeuFiltro(GtkWidget *container) {

	GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_container_set_border_width(GTK_CONTAINER(vbox), 20);
	gtk_container_add(GTK_CONTAINER(container), vbox);
	//gtk_container_add(GTK_CONTAINER(vbox), widgetControleNivel);
	GtkWidget *boxTamanho = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_container_add(GTK_CONTAINER(vbox), boxTamanho);
	gtk_container_add(GTK_CONTAINER(boxTamanho), widgetLabelComprimento);
	gtk_container_add(GTK_CONTAINER(boxTamanho), widgetComprimento);
	gtk_container_add(GTK_CONTAINER(boxTamanho), widgetLabelPinceladasComprimento);
	gtk_container_add(GTK_CONTAINER(boxTamanho), widgetPinceladasComprimento);
	gtk_container_add(GTK_CONTAINER(boxTamanho), widgetLabelPinceladasAltura);
	gtk_container_add(GTK_CONTAINER(boxTamanho), widgetPinceladasAltura);
	gtk_container_add(GTK_CONTAINER(vbox), widgetAleatorio);
	GtkWidget *frameCor = gtk_frame_new("Cor RGB do quadro");
	gtk_container_add(GTK_CONTAINER(vbox), frameCor);
	GtkWidget *boxCor = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	gtk_container_add(GTK_CONTAINER(vbox), boxCor);
	gtk_container_add(GTK_CONTAINER(boxCor), widgetCanvasR);
	gtk_container_add(GTK_CONTAINER(boxCor), widgetCanvasG);
	gtk_container_add(GTK_CONTAINER(boxCor), widgetCanvasB);
}

Imagem meuFiltro(Imagem origem) {
	int i, j;
	//Imagem destino = alocarImagem(origem);
	Imagem destino = alocarImagemDimensao(origem.w, origem.h, origem.numCanais);
	
	//int niveis = (int) gtk_range_get_value(GTK_RANGE(widgetControleNivel));
	int area = 0;
	int comprimento = (int) gtk_range_get_value(GTK_RANGE(widgetComprimento));
	int pinceladasComprimento = (int) gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(widgetPinceladasComprimento));
	int pinceladasAltura = (int) gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(widgetPinceladasAltura));
	int x,y;
	int raio, altura;
	unsigned char canaisMeio[3];

	for(i = 0; i < destino.w; i++)
		for(j=0; j < destino.h; j++){
			destino.m[j][i][0] = (int) gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(widgetCanvasR));
			destino.m[j][i][1] = (int) gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(widgetCanvasG));
			destino.m[j][i][2] = (int) gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(widgetCanvasB));
		}

	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widgetAleatorio))) {
	//faz i pinceladas, onde que a quantidade é determinada pelas pinceladas por área

	area = pinceladasAltura * pinceladasComprimento;

	for(i = 0; i < area; i++){
		//escolhe um ponto qualquer na imagem
		x = rand()%destino.w;
		y = rand()%destino.h;

		//checa os limites do ponto na imagem
		if(x < 0)
			x = 0;
		if(y < 0)
			y = 0; 
		if(x >= destino.w)
			x = destino.w - 1;
		if(y >= destino.h)
			y = destino.h - 1;

		//determina os canais desse ponto
		canaisMeio[0] = origem.m[y][x][0];
		canaisMeio[1] = origem.m[y][x][1];
		canaisMeio[2] = origem.m[y][x][2];

		

		//vai para pixel superior esquerdo(comeco) da pincelada
		raio = comprimento/2;
		//printf("%d", radius);

		//laço da pincelada

		for (int w = -raio; w < raio ; w++)
		{
    		altura = sqrt(raio * raio - w * w);
    		for (int h = -altura; h < altura; h++){
				if(w+x < 0)
					continue;
				if(h+y < 0)
					continue;
				if(w+x >= destino.w)
					break;
				if(h+y >= destino.h)
					break;
				destino.m[h+y][w+x][0] = canaisMeio[0];
				destino.m[h+y][w+x][1] = canaisMeio[1];
				destino.m[h+y][w+x][2] = canaisMeio[2];
				//printf("%d %d \n", h+y, w+x);
			}
		}
		//fim de uma pincelada
	}

	}
	else{
	for(i = 0; i < destino.w; i += destino.w / pinceladasComprimento ){
	for(j = 0; j < destino.h; j += destino.h / pinceladasAltura){

		// marca o pixel na imagem
		x = i;
		y = j;

		//checa os limites do ponto na imagem
		if(x < 0)
			x = 0;
		if(y < 0)
			y = 0; 
		if(x >= destino.w)
			x = destino.w - 1;
		if(y >= destino.h)
			y = destino.h - 1;

		//determina os canais desse ponto
		canaisMeio[0] = origem.m[y][x][0];
		canaisMeio[1] = origem.m[y][x][1];
		canaisMeio[2] = origem.m[y][x][2];

		

		//vai para pixel superior esquerdo(comeco) da pincelada
		raio = comprimento/2;
		//printf("%d", radius);

		//laço da pincelada

		for (int w = -raio; w < raio ; w++)
		{
    		altura = sqrt(raio * raio - w * w);
    		for (int h = -altura; h < altura; h++){
				if(w+x < 0)
					continue;
				if(h+y < 0)
					continue;
				if(w+x >= destino.w)
					break;
				if(h+y >= destino.h)
					break;
				destino.m[h+y][w+x][0] = canaisMeio[0];
				destino.m[h+y][w+x][1] = canaisMeio[1];
				destino.m[h+y][w+x][2] = canaisMeio[2];
				//printf("%d %d \n", h+y, w+x);
			}
		}
            		
		
		/*
		for(int w = x; w < x+comprimento; w++){
			for(int h = y; h < y+espessura; h++){
				//checa os limites da pincelada
				if(w < 0)
					w = 0;
				if(h < 0)
					h = 0; 
				if(w >= destino.w)
					break;
				if(h >= destino.h)
					break;
				//pinta de fato
				destino.m[h][w][0] = canaisMeio[0];
				destino.m[h][w][1] = canaisMeio[1];
				destino.m[h][w][2] = canaisMeio[2];

				printf("%d %d \n", w, h );
			}
		}*/
		//fim de uma pincelada
	}
	}
	//fim de TODAS pinceladas
	}
	
	return destino;
}

/*for(i = 0; i < destino.w; i += destino.w / pinceladasComprimento ){
	for(j = 0; j < destino.h; j += destino.h / pinceladasAltura){
		// marca o pixel na imagem
		x = i;
		y = j;

		//checa os limites do ponto na imagem
		if(x < 0)
			x = 0;
		if(y < 0)
			y = 0; 
		if(x >= destino.w)
			x = destino.w - 1;
		if(y >= destino.h)
			y = destino.h - 1;

		//determina os canais desse ponto
		canaisMeio[0] = origem.m[y][x][0];
		canaisMeio[1] = origem.m[y][x][1];
		canaisMeio[2] = origem.m[y][x][2];

		//vai para pixel superior esquerdo(comeco) da pincelada
		x = x - (comprimento/2);
		y = y - (espessura/2);
		
		//laço da pincelada
		for(int w = x; w < x+comprimento; w++){
			for(int h = y; h < y+espessura; h++){
				//checa os limites da pincelada
				if(w < 0)
					w = 0;
				if(h < 0)
					h = 0; 
				if(w >= destino.w)
					break;
				if(h >= destino.h)
					break;
				//pinta de fato
				destino.m[h][w][0] = canaisMeio[0];
				destino.m[h][w][1] = canaisMeio[1];
				destino.m[h][w][2] = canaisMeio[2];

				printf("%d %d \n", w, h );
			}
		}
		//fim de uma pincelada
	}
	}
	}*/



#include "meufiltro.h"

void inicializarWidgetsMeuFiltro() {
	//widgets das opcoes de filtro
	widgetControleNivel = 	gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 0, 30, 1);
	//widgetMisturarCanais = gtk_check_button_new_with_label("Misturar canais");

	widgetPinceladasArea = gtk_spin_button_new_with_range(1,2556,1);
	widgetComprimento = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 1, 100, 1);
	widgetEspessura = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 1, 100, 1);
	widgetAleatorio = gtk_check_button_new_with_label("Pintar Aleatoriamente");

	g_signal_connect(G_OBJECT(widgetControleNivel), "value-changed", G_CALLBACK(funcaoAplicar), NULL);
}

void adicionarWidgetsMeuFiltro(GtkWidget *container) {

	GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_container_set_border_width(GTK_CONTAINER(vbox), 20);
	gtk_container_add(GTK_CONTAINER(container), vbox);
	gtk_container_add(GTK_CONTAINER(vbox), widgetControleNivel);
	GtkWidget *boxTamanho = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_container_add(GTK_CONTAINER(vbox), boxTamanho);
	gtk_container_add(GTK_CONTAINER(boxTamanho), widgetEspessura);
	gtk_container_add(GTK_CONTAINER(boxTamanho), widgetComprimento);
	gtk_container_add(GTK_CONTAINER(boxTamanho), widgetPinceladasArea);
	gtk_container_add(GTK_CONTAINER(vbox), widgetAleatorio);
}

Imagem meuFiltro(Imagem origem) {
	int i, j;
	//Imagem destino = alocarImagem(origem);
	Imagem destino = alocarImagemDimensao(origem.w, origem.h, origem.numCanais);
	
	int nivel = (int) gtk_range_get_value(GTK_RANGE(widgetControleNivel));

	int espessura = (int) gtk_range_get_value(GTK_RANGE(widgetEspessura));
	int comprimento = (int) gtk_range_get_value(GTK_RANGE(widgetComprimento));
	int area = (int) gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(widgetPinceladasArea));
	int x,y;
	unsigned char canaisMeio[3];

	for(i = 0; i < destino.w; i++)
		for(j=0; j < destino.h; j++){
			destino.m[j][i][0] = 0;
			destino.m[j][i][1] = 0;
			destino.m[j][i][2] = 0;
		}

	//faz i pinceladas, onde que a quantidade é determinada pelas pinceladas por área
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
	
	return destino;
}

/*int ch1, ch2, ch3;

	ch1 = 0;
	ch2 = 1;
	ch3 = 2;
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widgetMisturarCanais))) {
		ch1 = rand()%3;
		ch2 = (ch1+1+rand()%2)%3;
		ch3 = 3 - ch2 - ch1;
	}*/

	/*for(j = 0; j < destino.w; j++) {
		for(i = 0; i < destino.h; i++) {
			int x = j/2 - nivel + rand()%(2*nivel+1);
			int y = i/2 - nivel + rand()%(2*nivel+1);
			if(x < 0)
				x = 0;
			if(y < 0)
				y = 0;
			if(x >= origem.w)
				x = origem.w - 1;
			if(y >= origem.h)
				y = origem.h - 1;
			destino.m[i][j][0] = origem.m[y][x][ch1];
			destino.m[i][j][1] = origem.m[y][x][ch2];
			destino.m[i][j][2] = origem.m[y][x][ch3];
		}
	}*/



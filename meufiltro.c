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
	Imagem destino = alocarImagem(origem);
	int nivel = (int) gtk_range_get_value(GTK_RANGE(widgetControleNivel));
	int espessura = (int) gtk_range_get_value(GTK_RANGE(widgetEspessura));
	int comprimento = (int) gtk_range_get_value(GTK_RANGE(widgetComprimento));
	int ch1, ch2, ch3;

	ch1 = 0;
	ch2 = 1;
	ch3 = 2;
	/*if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widgetMisturarCanais))) {
		ch1 = rand()%3;
		ch2 = (ch1+1+rand()%2)%3;
		ch3 = 3 - ch2 - ch1;
	}
	*/

	for(j = 0; j < destino.w; j+=comprimento) {
		for(i = 0; i < destino.h; i+=espessura) {
			int x = j - (comprimento/2);
			int y = i - (espessura/2);
			char canaisMeio[3] = {origem.m[i][j][0], origem.m[i][j][1], origem.m[i][j][2]} ;
			if(x < 0)
				x = 0;
			if(y < 0)
				y = 0;
			if(x >= destino.w)
				x = destino.w - 1;
			if(y >= destino.h)
				y = destino.h - 1;
			
			for(x; x < comprimento; x++){
				for(y; y < espessura; y++){
					destino.m[y][x][0] = canaisMeio[0];
					destino.m[y][x][1] = canaisMeio[1];
					destino.m[y][x][2] = canaisMeio[2];
				}
			}
			/*
			destino.m[i][j][0] = origem.m[y][x][ch1];
			destino.m[i][j][1] = origem.m[y][x][ch2];
			destino.m[i][j][2] = origem.m[y][x][ch3];
			*/
		}
	}
	return destino;
}



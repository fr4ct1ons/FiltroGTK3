#ifndef MEUFILTRO_H
#define MEUFILTRO_H

#include <gtk/gtk.h>
#include <glib.h>
#include <stdlib.h>
#include <time.h>
#include "imagem.h"

//declare aqui os seus widgets
GtkWidget *widgetControleNivel;
//GtkWidget *widgetMisturarCanais;
GtkWidget *widgetEspessura, *widgetComprimento;
GtkWidget *widgetAleatorio;
GtkWidget *widgetPinceladasComprimento;
GtkWidget *widgetPinceladasAltura;
GtkWidget *widgetCanvasR;
GtkWidget *widgetCanvasG;
GtkWidget *widgetCanvasB;

GtkWidget *widgetLabelEspessura;
GtkWidget *widgetLabelComprimento;
GtkWidget *widgetLabelPinceladasAltura;
GtkWidget *widgetLabelPinceladasComprimento;
GtkWidget *widgetLabelCores;

Imagem meuFiltro(Imagem origem);
void inicializarWidgetsMeuFiltro();
void adicionarWidgetsMeuFiltro(GtkWidget *container);

//esta funcao esta implementada em filtroGtk.c, nao precisa alterar
void funcaoAplicar(GtkWidget *widget, gpointer data);

#endif



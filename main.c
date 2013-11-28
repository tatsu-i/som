#define GTK_DISABLE_DEPRECATED 1
#define LIBGLADE_DISABLE_DEPRECATED 1
#include <gtk/gtk.h>
#include <glade/glade.h>
#include <pthread.h>
#include <stdlib.h>
#include <math.h>
#include "data.h"
#include "som.h"

G_BEGIN_DECLS
void input_button_clicked();
void winner_button_clicked();
void learn_button_clicked();
void auto_learn_button_clicked();
void reload_button_clicked();
G_END_DECLS
void* auto_learn(){
	while (som.t != T) {
		input();
		select_win();
		update_map();
		usleep(1000);
	}
}

void input_button_clicked() {
	input();
}
void winner_button_clicked(){
	select_win();
}
void learn_button_clicked() {
	update_map();
}
void auto_learn_button_clicked() {
	pthread_t tid1;
	pthread_create(&tid1, NULL, auto_learn, NULL);

}
void reload_button_clicked(){
	som.t = 1;
	init_map();
}
static gboolean ivent_loop(GtkWidget *widget)
{
	if (widget->window == NULL)
		return FALSE;
	gtk_widget_queue_draw(widget);
	return TRUE;
}
gboolean cb_expose_event(GtkWidget *widget,
		GdkEventExpose *event, gpointer user_data)
{
	cairo_t *cr;
	double r = 10.5;
	int i = 0,j = 0;
	char str[25];

	cr = gdk_cairo_create(widget->window);
	cairo_set_line_width(cr, 5.0);	 //線の太さ
	for(i = 0;i < N;i++){
		for(j = 0;j < N;j++){
			//円形
			cairo_set_source_rgb(cr, 0.01*gui.arcr[j][i], 0.0, 0.0);
			cairo_arc(cr, 35.0+35*i, 35.0+35*j, r, 0.0, 2.0*3.14);
			cairo_stroke_preserve(cr);
			cairo_set_source_rgb(cr, som.map[j][i][0], 
					som.map[j][i][1], som.map[j][i][2]);
			cairo_fill(cr);
		}
	}
	cairo_set_source_rgb(cr, 0.1, 0.1, 0.1); 
	cairo_select_font_face(cr, "VL ゴシック",
			CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
	cairo_set_font_size(cr, 13);
	//文字の先頭位置を指定する。
	cairo_move_to(cr, 35*N+50, 30);
	//改行は，y座標を動かすことで表現する
	cairo_show_text(cr, gui.str);
	//矩形の描画
	cairo_set_source_rgb(cr, 0, 0, 0);
	cairo_rectangle(cr, 35*N+50, 50.0, 100.0, 25.0);
	cairo_stroke_preserve(cr);
	cairo_set_source_rgb(cr, som.select[0], som.select[1], som.select[2]);
	cairo_fill(cr);

	cairo_destroy(cr);
	return FALSE;
}
int main(int argc, char* argv[]) {
	GladeXML* xml;
	GtkWidget* window;
	GtkWidget* drawingarea;
	som.t = 1;
	init_map();//ランダムに初期化

	gtk_init(&argc, &argv);
	xml = glade_xml_new("som.glade", NULL, NULL); 
	if (!xml) {
		printf("glade file error.\n");
		return 1;
	}
	window = glade_xml_get_widget(xml, "window");
	drawingarea = glade_xml_get_widget(xml, "drawingarea");
	glade_xml_signal_autoconnect(xml);
	g_object_unref(G_OBJECT(xml));

	//画面の更新処理
	g_timeout_add(200, (GSourceFunc)ivent_loop, drawingarea);

	gtk_widget_show_all(window);
	gtk_main();
	return 0;
}

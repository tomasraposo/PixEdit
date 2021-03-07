#include "ppmviewer.h"
#include "libutilities.h"

static gboolean gtk_resize_image(GtkWidget* widget, GdkRectangle* allocation, gpointer data) {
	GtkWidget* image = GTK_WIDGET (data);
	GtkWidget* toplevel = gtk_widget_get_toplevel (image);
    GdkPixbuf* pb = gtk_image_get_pixbuf(GTK_IMAGE(image));
	GdkPixbuf* pbscaled;
	int width, height;
	pbscaled = gdk_pixbuf_scale_simple(pb, allocation->width, allocation->height, GDK_INTERP_BILINEAR);
    gtk_image_set_from_pixbuf(GTK_IMAGE(image), pbscaled);
    g_object_unref (pbscaled);
    return FALSE;
}

int img_viewer(int argc, char** argv) {
	GtkWidget* window;
	GtkWidget* image;
	GdkPixbuf* pb;
	int width, height;

	gtk_init (&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window), 230, 150);
    gtk_window_set_title(GTK_WINDOW(window), argv[2]);
    gtk_window_set_resizable(GTK_WINDOW(window), TRUE);

	image  = gtk_image_new();
	if (!(pb = gdk_pixbuf_new_from_file(argv[2], NULL))) 
		err("Unable to load image.");
	
	gtk_window_get_size(GTK_WINDOW(window), &width, &height);
	pb = gdk_pixbuf_scale_simple(pb,width,height,GDK_INTERP_BILINEAR);
	gtk_image_set_from_pixbuf(GTK_IMAGE(image), pb);

	g_signal_connect(window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
	g_signal_connect(window, "size-allocate", G_CALLBACK(gtk_resize_image), image);

	gtk_container_add(GTK_CONTAINER (window), image);
	gtk_widget_show_all(window);
	gtk_main();
	g_object_unref(pb);
	return 0;
}

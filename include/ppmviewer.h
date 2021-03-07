#ifndef __PPMVIEWER__H__
#define __PPMVIEWER__H__
#include <gtk/gtk.h>
static gboolean gtk_resize_image(GtkWidget* widget, GtkAllocation* allocation, gpointer data);
int img_viewer(int argc, char** argv);
#endif  //!__PPMVIEWER__H__
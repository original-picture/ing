
#include "ing_main_loop.h"
#include "ing_main_loop_extension_api.h"

#include "ing_qt_context_data.h"

static void qt_deinit_(void* data) {
    gtk_context_data* gtk_data = data;

    g_main_loop_unref(gtk_data->loop);
}

static void qt_init_() {
    gtk_context_data* data = ing_allocate_context_data(gtk_context_data_key, sizeof(gtk_context_data), gtk_deinit_);

    data->loop = g_main_loop_new(g_main_context_default(), false);
}

static void gtk_next_frame_() {
    gtk_context_data* data = ing_get_context_data(gtk_context_data_key);

    g_main_context_iteration(g_main_loop_get_context(data->loop), FALSE);
}

bool ing_next_frame() {
    return ing_next_frame_internal(gtk_init_, gtk_next_frame_, NULL);
}

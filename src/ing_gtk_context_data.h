#pragma once

#include "gtk/gtk.h"

const char* gtk_context_data_key = "ing_gtk_context_data";

typedef struct {
    GMainLoop* loop;

} gtk_context_data;
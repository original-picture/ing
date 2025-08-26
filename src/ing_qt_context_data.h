#pragma once

#include <QApplication>



const char* gtk_context_data_key = "ing_qt_context_data";

typedef struct {
    GMainLoop* loop;

} gtk_context_data;
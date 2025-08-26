#pragma once

#define ING_STRINGIFY2(X) #X
#define ING_STRINGIFY(X) STRINGIFY2(X) // this is necessary because of how macro expansion works

const char* gtk_context_data_key = "ing_gtk_context_data";


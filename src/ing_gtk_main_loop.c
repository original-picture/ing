
#include "ing_internal_main_loop_api.h"

#include "gtk/gtk.h"

static void ing_gtk_init_() {

}

static void ing_gtk_next_frame_() {

}

bool ing_next_frame() {
    return ing_next_frame_internal(ing_gtk_init_, ing_gtk_next_frame_);
}

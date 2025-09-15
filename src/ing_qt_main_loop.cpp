
#include "ing_main_loop.h"
#include "ing_main_loop_extension_api.h"

#include "ing_qt_context_data.h"

static void qt_deinit_(void* data) {
    static_cast<qt_context_data*>(data)->application.~QApplication();
}

static void qt_init_() {
    auto* data = static_cast<qt_context_data*>(ing_allocate_context_data(context_data_key, sizeof(qt_context_data), qt_deinit_));

    int argc = 1;
    static char args[4] = {'i', 'n', 'g', '\0'}; // TODO: figure out a way to expose this in the public api?
    static char* a = &args[0];

    if(!QApplication::instance()) {  // check if a qt application already exists (this should only happen if we're running in a plugin or something like that)
        new (&(data->application)) QApplication(argc, &a);
    }
}

static void qt_next_frame_() {
    QApplication::processEvents();
}

extern "C" {
    bool ing_next_frame() {
        return ing_next_frame_internal(qt_init_, qt_next_frame_, NULL);
    }
}


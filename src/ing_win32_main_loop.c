
#include "ing_main_loop.h"
#include "ing_main_loop_extension_api.h"

#include "ing_win32_context_data.h" // includes windows.h

// doesn't matter where we put this, so I'll just put it here
#pragma comment(linker,"\"/manifestdependency:type='win32' \
                           name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
                           processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

static void win32_init_() {
    win32_context_data* data = ing_allocate_context_data(context_data_key, sizeof(win32_context_data), NULL);

    data->instance = GetModuleHandleW(NULL); // TODO: make sure this works if we're running in a dll too!
}

static void win32_next_frame_() {
    win32_context_data* data = ing_get_context_data(context_data_key);

    MSG messages;

    if(GetMessage(&messages, NULL, 0, 0))
    {
        for(unsigned i = 0; i < data->top_level_windows.size; ++i) {
            /* Translate virtual-key messages into character messages */
            if(IsDialogMessage(dynamic_array_at(HWND, &data->top_level_windows, i), &messages) == 0)
            {
                TranslateMessage(&messages);
                /* Send message to WindowProcedure */
                DispatchMessage(&messages);
            }
        }
    }
}

bool ing_next_frame() {
    return ing_next_frame_internal(win32_init_, win32_next_frame_, NULL);
}


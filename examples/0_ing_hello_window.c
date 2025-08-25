
#include "ing.h"

int main() {
    while(ing_next_frame()) {
        ing_begin_window("hello window");
    }
}

#pragma once

#define ing_testing_assert(condition_expression, /*message*/...)                                                                             \
    {                                                                                                                                        \
        void ing_generic_assert_(_Bool condition, const char* condition_str, const char* message,                                            \
                                 const char* file, int line, const char* function, const char* header_text, const char* footer_text);        \
                                                                                                                                             \
        ing_generic_assert_(condition_expression, #condition_expression, "" __VA_ARGS__, __FILE__, __LINE__, __func__,                       \
                            "ing testing assertion failed!",                                                                                 \
                            "");                                                                                                             \
    } (void)0
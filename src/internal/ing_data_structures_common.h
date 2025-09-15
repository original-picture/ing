#pragma once

#define ing_make_lvalue(type, rvalue_expression) ((type){rvalue_expression})

#define ing_struct_init(struct_type, brace_enclosed_initializer) ((struct_type) brace_enclosed_initializer )
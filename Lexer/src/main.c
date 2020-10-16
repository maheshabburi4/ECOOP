#include <stdio.h>
#include "include/lexer.h"

int main()
{
    lexer_T* lexer = init_lexer(
        "int main()\n"
        "{\n"
        "char name += \"john doe\" ;\n"
        "int x = 569*46 ;\n"
        "char y = `c`;\n"
        "public: int x = 5;\n"
        "print(name) ;\n"
        "}\n"
    ) ;

    token_T* token = (void*)0 ;
    while((token = lexer_get_next_token(lexer)) != (void*)0)
    {
        printf("%s %s\n", token->value,token->token_type) ;
    }
    return 0 ;
}
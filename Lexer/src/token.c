#include "include/token.h"
#include <stdlib.h>

token_T* init_token(int type,char* value,char* token_type)
{
    token_T* token = calloc(1,sizeof(struct TOKEN_STRUCT)) ;
    token->type = type ;
    token->value = value ;
    token->token_type = token_type ;

    return token ;
}
#ifndef TOKEN_H
#define TOKEN_H
typedef struct TOKEN_STRUCT
{
    enum {
        TOKEN_IDENTIFIER,
        TOKEN_ID,
        TOKEN_TYPEID,
        TOKEN_INTCONST,
        TOKEN_EQUALS,
        TOKEN_STRING,
        TOKEN_SEMI,
        TOKEN_COLON,
        TOKEN_QUOTE,
        TOKEN_LPAREN,
        TOKEN_RPAREN,
        TOKEN_LBRACE,
        TOKEN_RBRACE,
        TOKEN_LSQUARE,
        TOKEN_RSQUARE,
        TOKEN_PLUS,
        TOKEN_MINUS,
        TOKEN_MULT,
        TOKEN_DIV,
        TOKEN_KEYWORDS
    } type ;
    char *value ;
    char *token_type ;
} token_T ;

token_T* init_token(int type, char* value,char *token_type);
#endif
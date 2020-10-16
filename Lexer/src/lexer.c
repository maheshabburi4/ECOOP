#include "include/lexer.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

lexer_T* init_lexer(char* contents) 
{
    lexer_T* lexer = calloc(1,sizeof(struct LEXER_STRUCT)) ;
    lexer->contents = contents ;
    lexer->i = 0 ;
    lexer->c = contents[lexer->i] ;

    return lexer ;
}

void lexer_advance(lexer_T* lexer)
{
    if(lexer->c != '\0' && lexer->i < strlen(lexer->contents))
    {
        lexer->i += 1 ;
        lexer->c = lexer->contents[lexer->i] ;
    }
}

void lexer_skip_whitespace(lexer_T* lexer) 
{
    while(lexer->c == ' '|| lexer-> c == 10)
    {
        lexer_advance(lexer) ; 
    }
}

char* lexer_get_current_char_as_string(lexer_T* lexer) 
{
    char* str = calloc(2,sizeof(char)) ;
    str[0] = lexer->c ;
    str[1] = '\0' ;
    return str ;
}

token_T* lexer_get_next_token(lexer_T* lexer) 
{
    while(lexer-> c != '\0' && lexer->i <strlen(lexer->contents))
    {
        if(lexer->c == ' ' || lexer->c == 10)
            lexer_skip_whitespace(lexer) ;

        if(isalpha(lexer->c))
        {
            token_T* temp = lexer_collect_identifier(lexer) ;
            if(temp != (void*)0)
            {
                return temp ;
            }
        }

        if(isdigit(lexer->c))
        {
            token_T* temp = lexer_collect_integer_constant(lexer) ;
            if(temp != (void*)0)
            {
                return temp ;
            }
        }

        if(isalnum(lexer->c))
        {
            return lexer_collect_id(lexer) ;
        }

        if(lexer->c == '"')
        {
            return lexer_collect_string(lexer) ;
        }
        
        switch(lexer->c)
        {
            case '=': return lexer_advance_with_token(lexer,init_token(TOKEN_EQUALS, lexer_get_current_char_as_string(lexer),"EQUALS")); break ;
            case ';': return lexer_advance_with_token(lexer,init_token(TOKEN_SEMI, lexer_get_current_char_as_string(lexer),"SEMI_COLON")); break ;
            case ':': return lexer_advance_with_token(lexer,init_token(TOKEN_COLON, lexer_get_current_char_as_string(lexer),"COLON")); break ;
            case '`': return lexer_advance_with_token(lexer,init_token(TOKEN_QUOTE, lexer_get_current_char_as_string(lexer),"QUOTE")); break ;
            case '(': return lexer_advance_with_token(lexer,init_token(TOKEN_LPAREN, lexer_get_current_char_as_string(lexer),"LPAREN")); break ;
            case ')': return lexer_advance_with_token(lexer,init_token(TOKEN_RPAREN, lexer_get_current_char_as_string(lexer),"RPAREN")); break ;
            case '+': return lexer_advance_with_token(lexer,init_token(TOKEN_PLUS, lexer_get_current_char_as_string(lexer),"PLUS")); break ;
            case '-': return lexer_advance_with_token(lexer,init_token(TOKEN_MINUS, lexer_get_current_char_as_string(lexer),"MINUS")); break ;
            case '*': return lexer_advance_with_token(lexer,init_token(TOKEN_MULT, lexer_get_current_char_as_string(lexer),"MULT")); break ;
            case '/': return lexer_advance_with_token(lexer,init_token(TOKEN_DIV, lexer_get_current_char_as_string(lexer),"DIV")); break ;
            case '{': return lexer_advance_with_token(lexer,init_token(TOKEN_LBRACE, lexer_get_current_char_as_string(lexer),"LBRACE")); break ;
            case '}': return lexer_advance_with_token(lexer,init_token(TOKEN_RBRACE, lexer_get_current_char_as_string(lexer),"RBRACE")); break ;
            case '[': return lexer_advance_with_token(lexer,init_token(TOKEN_LSQUARE, lexer_get_current_char_as_string(lexer),"LSQUARE")); break ;
            case ']': return lexer_advance_with_token(lexer,init_token(TOKEN_RSQUARE, lexer_get_current_char_as_string(lexer),"RSQUARE")); break ;
        }
    }

    return (void*)0 ;
}

token_T* lexer_collect_integer_constant(lexer_T* lexer)
{
    char *value = calloc(1,sizeof(char)) ;
    value[0] = '\0' ;
    int n = lexer->i ;

    while(lexer->contents[n] != ' ' && lexer->contents[n] != 10 && n<strlen(lexer->contents))
    {
        if(isdigit(lexer->contents[n]))
        {
            char* s = (char*)calloc(2,sizeof(char)) ;
            s[0] = lexer->contents[n] ;
            s[1] = '\0' ;
             value = realloc(value, (strlen(value)+strlen(s)+1)*sizeof(char)) ;
            strcat(value,s);
            n++ ;
        }
        else {
            char c = lexer->contents[n] ;
            if(c == '+' || c == '-' || c == '*' || c == '/' || c == ';')
                break ;
            return (void*)0 ;
        }
    }
    lexer->i = n ;
    lexer->c = lexer->contents[n] ;
    return init_token(TOKEN_INTCONST,value,"INTCONST") ;
}

token_T* lexer_collect_identifier(lexer_T* lexer)
{
    char *value = calloc(1,sizeof(char)) ;
    value[0] = '\0' ;
    int n = lexer->i ;

    while(lexer->contents[n] != ' ' && lexer->contents[n] != 10 && n<strlen(lexer->contents))
    {
        if(isalpha(lexer->contents[n]))
        {
            char* s = (char*)calloc(2,sizeof(char)) ;
            s[0] = lexer->contents[n] ;
            s[1] = '\0' ;
             value = realloc(value, (strlen(value)+strlen(s)+1)*sizeof(char)) ;
            strcat(value,s);
            n++ ;
        }
        else {
            return (void*)0 ;
        }
    }
    if(strcmp(value,"main") == 0 || strcmp(value,"return") == 0 || strcmp(value,"inherits")==0 || strcmp(value,"class") == 0)
    {
        lexer->i = n ;
        lexer->c = lexer->contents[n] ;
        return init_token(TOKEN_IDENTIFIER,value,"IDENTIFIER") ;
    }
    if(strcmp(value,"char") == 0 || strcmp(value,"int") == 0) 
    {
        lexer->i = n ;
        lexer->c = lexer->contents[n] ;
        return init_token(TOKEN_IDENTIFIER,value,"TYPEID") ;
    }
    return (void*)0 ;
} 


token_T* lexer_collect_string(lexer_T* lexer) 
{
    lexer_advance(lexer) ;

    char *value = calloc(1,sizeof(char)) ;
    value[0] = '\0' ;

    while(lexer->c != '"')
    {
        char *s = lexer_get_current_char_as_string(lexer) ;
        value = realloc(value, (strlen(value)+strlen(s)+1)*sizeof(char)) ;
        strcat(value,s);
        lexer_advance(lexer);
    }

    lexer_advance(lexer) ;


    return init_token(TOKEN_STRING,value,"STRING");
}


token_T* lexer_collect_id(lexer_T* lexer)
{
  //  lexer_advance(lexer) ;

    char *value = calloc(1,sizeof(char)) ;
    value[0] = '\0' ;

    while(isalnum(lexer->c))
    {
        char *s = lexer_get_current_char_as_string(lexer) ;
        value = realloc(value, (strlen(value)+strlen(s)+1)*sizeof(char)) ;
        strcat(value,s);
        lexer_advance(lexer);
    }
    if(strcmp(value,"public")==0 ||strcmp(value,"private")==0 ||strcmp(value,"protected")==0)
    {
        return init_token(TOKEN_KEYWORDS,value,"KEYWORD");
    }
  //lexer_advance(lexer) ;

    return init_token(TOKEN_ID,value,"OBJECTID");
}

token_T* lexer_advance_with_token(lexer_T* lexer, token_T* token)
{
    lexer_advance(lexer) ;

    return token ;
}



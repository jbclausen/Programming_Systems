/*-----------------------------------------------------------------*/
/* NAME: Jens Clausen         FILENAME: decomment.c                */
/* NETID: jclausen                                                 */   
/* Assignment: 1                                                   */
/* Description: implementation of a text processing DFA that removes 
                comments from text files and replaces them with a 
                whitespace character. Prints an error message to 
                stderr if there is an unterminated comment at the 
                end of the file                                    */
/*-----------------------------------------------------------------*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

enum Statetype {NORMAL, NORMALSLASH, INCOMMENT, INCOMMENTSTAR, 
    INSTRING, INSTRINGBACKSLASH, INCHAR, INCHARBACKSLASH}; 

/* handle the normal state */ 
enum Statetype handleNormalState(int c)
{   enum Statetype state;
    if (c == '"') {
        putchar(c);
        state = INSTRING;
        return state;
    }

    if (c == '\'') {
        putchar(c);
        state = INCHAR; 
        return state; 
    }

    if (c == '/') {
        state = NORMALSLASH; 
        return state;
    }

    else {
        state = NORMAL;
        putchar(c); 
        return state;
    }
}

/* handle the normalSlash state */ 
enum Statetype handleNormalSlashState(int c)
{   enum Statetype state;

    if (c == '*') {
        putchar(' ');         /* replace comments with a space */ 
        state = INCOMMENT;
        return state;
    }

    if (c == '"') {
        putchar('/'); 
        putchar(c);
        state = INSTRING;
        return state; 
    }

    if (c == '\'') {
        putchar('/');
        putchar(c);
        state = INCHAR;
        return state; 
    }

    if (c == '/') {
        putchar('/'); 
        state = NORMALSLASH; 
        return state; 
    }

    else {
        state = NORMAL; 
        putchar('/');
        putchar(c); 
        return state;
    }
}

/* handle the inComment state */ 
enum Statetype handleInCommentState(int c)  
{   enum Statetype state;

    if (c == '\n') {      /* preserve the original line numbering */ 
        putchar('\n');
        state = INCOMMENT;
        return state;
    }

    if (c == '*') {
        state = INCOMMENTSTAR; 
        return state; 
    }

    else {
        state = INCOMMENT;
        return state; 
    }
}

/* handle the inCommentStar state */ 
enum Statetype handleInCommentStarState(int c)
{   enum Statetype state;

    if (c == '/') {
        state = NORMAL; 
        return state; 
    }

    if (c == '*') {
        state = INCOMMENTSTAR; 
        return state; 
    }

    if (c == '\n') {      /* preserve the original line numbering */ 
        putchar('\n');
        state = INCOMMENT;
        return state;
    }

    else {
        state = INCOMMENT;
        return state; 
    }
}

/* handle the inString state */ 
enum Statetype handleInStringState(int c)
{   enum Statetype state;

    if (c == '"') { 
        state = NORMAL; 
        putchar(c);
        return state;
    }

    if (c == '\\') { /* check this */              
        state = INSTRINGBACKSLASH;
        putchar(c);
        return state; 
    }

    else {
        state = INSTRING; 
        putchar(c);
        return state; 
    }
}

/* handle the inStringBackslash state */ 
enum Statetype handleInStringBackslashState(int c)
{   enum Statetype state;

    state = INSTRING;
    putchar(c);
    return state; 
}

/* handle the inCHar state */ 
enum Statetype handleInCharState(int c)
{   enum Statetype state;

    if (c == '\'') { 
        state = NORMAL; 
        putchar(c);
        return state;
    }

    if (c == '\\') {              
        state = INCHARBACKSLASH;
        putchar(c);
        return state; 
    }

    else {
        state = INCHAR; 
        putchar(c);
        return state; 
    }
}

/* handle the inCharBackslash state */ 
enum Statetype handleInCharBackslashState(int c)
{   enum Statetype state;

    state = INCHAR;
    putchar(c);
    return state; 
}

/* Read text from stdin. Remove the comments from the code & replace
   with a whitespace char. Preserve the original line numbering. 
   Write the result to stdout. Return 0. If there is an unterminated 
   comment, prints an error message with the line number of the start
   of the unterminated comment */ 

int main(void) 
{
    int c; 
    int line = 1; 
    int commentStartLine; 
    int inComment = 0; /* 0 = false, 1 = true */ 

    enum Statetype state = NORMAL; 

    while ((c = getchar()) != EOF) 
    {   
        /* challenge */   
        if (c == '\n') /* newline character */ 
            line++; 

        /* if not already in a comment, save the line number */ 
        if (state == INCOMMENT && inComment == 0) {
            inComment = 1; 
            commentStartLine = line; 
            }

        /* if previously in a comment, flip boolean variable */ 
        if (state == NORMAL && inComment == 1) {
            inComment = 0; 
        }

        /* select function to execute based on the state */ 
        switch (state)
        {
            case NORMAL:  
                state = handleNormalState(c);
                break;

            case NORMALSLASH:  
                state = handleNormalSlashState(c);
                break;

            case INCOMMENT:  
                state = handleInCommentState(c);
                break;

            case INCOMMENTSTAR:  
                state = handleInCommentStarState(c);
                break;

            case INSTRING:  
                state = handleInStringState(c);
                break;

            case INSTRINGBACKSLASH:  
                state = handleInStringBackslashState(c);
                break;  

            case INCHAR:  
                state = handleInCharState(c);
                break; 

            case INCHARBACKSLASH:  
                state = handleInCharBackslashState(c);
                break; 

        } 
    }

    if (state == NORMALSLASH){ 
        putchar('/');
    }

    /* print error message to stderr if  unterminated comment */ 
    if (state == INCOMMENT || state == INCOMMENTSTAR) {
        fprintf(stderr, "Error: line %d: unterminated comment\n",
            commentStartLine);
        return EXIT_FAILURE; 
    }              

    return 0;
}


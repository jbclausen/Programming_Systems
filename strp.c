/*-----------------------------------------------------------------*/
/* NAME: Jens Clausen         FILENAME: strp.c                     */
/* NETID: jclausen                                                 */   
/* Assignment: 2                                                   */
/* Description:     Pointer implementation of a Str module that 
                    contains versions of the most commonly used 
                    standard string handling functions.            */
/*-----------------------------------------------------------------*/

#include "str.h" 
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stddef.h>

/*-----------------------------------------------------------------*/
/* This code was taken from the course website */ 

size_t Str_getLength(const char *pcSrc) 
{
   const char *pcEnd;
   assert(pcSrc != NULL);
   pcEnd = pcSrc;
   while (*pcEnd != '\0')
      pcEnd++;
   return (size_t)(pcEnd - pcSrc);
}

/*-----------------------------------------------------------------*/

char *Str_copy(char *pcDest, const char *pcString)
{
    char *pcTemp;
    char *pcReturn = pcDest; 

    assert (pcDest != NULL && pcString != NULL);  

    pcTemp = (char*) pcString; 
   
    while (*pcTemp != '\0') {
        *pcDest = *pcTemp;
        pcDest++; 
        pcTemp++;  
    }

    *pcDest = '\0';

    return pcReturn; 
}   

/*-----------------------------------------------------------------*/
  
char *Str_concat(char *pcDest, const char *pcString)
{
    char *pcTemp;
    char *pcReturn = pcDest; 

    assert (pcDest != NULL && pcString != NULL); 

    pcTemp = (char*) pcString; 

    while (*pcDest != '\0') {
        pcDest++; 
    }

    (void) Str_copy(pcDest, pcTemp); 

    return pcReturn; 
}

/*-----------------------------------------------------------------*/

int Str_compare(const char *pcS1, const char *pcS2) {  

    char *pcTemp1;
    char *pcTemp2;

    assert (pcS1 != NULL && pcS2 != NULL); 

    pcTemp1 = (char*) pcS1; 
    pcTemp2 = (char*) pcS2; 

    while (*pcTemp1 == *pcTemp2) {
        if (*pcTemp1 == '\0' || *pcTemp2 == '\0')
            break; 
        pcTemp1++; 
        pcTemp2++; 
    }

    return (int) (*pcTemp1 - *pcTemp2); 
}

/*-----------------------------------------------------------------*/

char *Str_search(const char *pcHaystack,const char *pcNeedle) {  

    char *pcTemp1;
    char *pcTemp2;
    size_t iMatchCount = 0;  

    assert (pcHaystack != NULL && pcNeedle != NULL); 

    pcTemp1 = (char*) pcHaystack; 
    pcTemp2 = (char*) pcNeedle;

    /* boundary cases */ 
    if (*pcTemp2 == '\0') {
        return (char*) pcHaystack;
    }

    if (*pcTemp1 == '\0') {
        return NULL; 
    }

    /* walk through Haystack and check for a match */ 
    while (*pcTemp1 != '\0') {
        /* if substring found, return pointer to the start of it */ 
        if (*pcTemp2 == '\0') {
            return pcTemp1 -= iMatchCount; 
        }

        if (*pcTemp1 == *pcTemp2) {
            iMatchCount++;
            pcTemp2++;
        }
        else {
            pcTemp2 = (char*) pcNeedle;
            pcTemp1 -= iMatchCount;
            iMatchCount = 0;
        }

        pcTemp1++; 
    } 

    /* if substring found, return pointer to the start of it */ 
    if ((*pcTemp1 == '\0' && *pcTemp2 == '\0') && iMatchCount != 0) {
        return pcTemp1 -= iMatchCount; 
    }

    return NULL;

}

/*-----------------------------------------------------------------*/

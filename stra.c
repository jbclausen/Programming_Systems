/*-----------------------------------------------------------------*/
/* NAME: Jens Clausen         FILENAME: stra.c                     */
/* NETID: jclausen                                                 */   
/* Assignment: 2                                                   */
/* Description:     Array implementation of a Str module that 
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

size_t Str_getLength(const char pcSrc[]) 
{
   size_t iLength = 0;
   assert(pcSrc != NULL);
   while (pcSrc[iLength] != '\0')
      iLength++;
   return iLength;
}

/*-----------------------------------------------------------------*/

char *Str_copy(char pcDest[], const char pcString[]) 
{

    size_t i; 
    size_t iL2 = Str_getLength(pcString);

    assert (pcDest != NULL && pcString != NULL);  

    for (i = 0; i <= iL2; i++) {
        pcDest[i] = pcString[i];
        if (pcString[i] == '\0') 
            break; /* write the terminating null byte then break */ 
    }

    return &pcDest[0];  
}

/*-----------------------------------------------------------------*/
  
char *Str_concat(char pcDest[], const char pcString[])
{
    size_t j; 
    size_t i = 0;
    
    
    size_t iL1 = Str_getLength(pcDest);
    size_t iL2 = Str_getLength(pcString);
    j = iL1;

    assert (pcDest != NULL && pcString != NULL); 
     
    for(i = 0; i < iL2; i++) {
        pcDest[j] = pcString[i]; 
        j++;
    }

    pcDest[j] = '\0';

    return &pcDest[0];  
}  

/*-----------------------------------------------------------------*/

int Str_compare(const char pcS1[], const char pcS2[]) { 
    
    int i = 0;
    
    assert (pcS1 != NULL && pcS2 != NULL); 

    while (pcS1[i] == pcS2[i] && pcS1[i] != '\0' && pcS2[i] != '\0') {
        i++;
    }
    
    return (int) (pcS1[i] - pcS2[i]); 
}

/*-----------------------------------------------------------------*/

char *Str_search(const char pcHaystack[], const char pcNeedle[]) {

    size_t i; 
    size_t iMatchCount = 0; 

    size_t iHaystackLen = Str_getLength(pcHaystack);
    size_t iNeedleLen = Str_getLength(pcNeedle);

    assert (pcHaystack != NULL && pcNeedle != NULL); 
    
    /* boundary cases */ 
    if (iNeedleLen == 0) {
        return (char*) &pcHaystack[0];
    }

    if (iHaystackLen == 0) {
        return NULL; 
    }

    /* walk through Haystack and check for a match */ 
    for (i = 0; i < iHaystackLen; i++) {
        if ((pcHaystack[i] == pcNeedle[iMatchCount])) {
            iMatchCount++;
        }
        else {
            i -= iMatchCount; 
            iMatchCount = 0; 
        }

        /* if substring found, return pointer to the start of it */ 
        if (iMatchCount == iNeedleLen) {
            return (char*) &pcHaystack[i - iNeedleLen + 1]; 
        }
    }

    return NULL; 
    
}


/*-----------------------------------------------------------------*/
/* NAME: Jens Clausen         FILENAME: str.h                      */
/* NETID: jclausen                                                 */   
/* Assignment: 2                                                   */
/* Description:                                                    */
/*-----------------------------------------------------------------*/

#include <stddef.h>

#ifndef STR 
#define STR 

/*-----------------------------------------------------------------*/

/* Returns the length of the string pcSrc excluding the null byte at 
   the end '\0' */ 

size_t Str_getLength(const char pcSrc[]); 

/*-----------------------------------------------------------------*/

/* The Str_copy() function copies the string pointed to by pcString, 
   including the terminating null byte ('\0'), to the string pointed 
   to by pcDest. The strings may not overlap, and the  destination 
   string pcDest must be large enough to receive the copy. Returns a 
   pointer to the start of the resulting pcDest string */ 

char *Str_copy(char pcDest[], const char pcString[]); 

/*-----------------------------------------------------------------*/

/* The Str_concat() function appends the pcString string to the 
   pcDest string, overwriting the terminating null byte ('\0') at 
   the end of pcDest, and then  adds  a  terminating  null  byte. 
   The strings may  not  overlap, and the aDest string must have 
   enough space for the result. If pcDest is not large enough, 
   program  behavior is  unpredictable. Returns a pointer to the 
   start of the resulting pcDest string */ 

char *Str_concat(char pcDest[], const char pcString[]); 


/*-----------------------------------------------------------------*/

/* The Str_compare() function compares the two strings pcS1 and pcS2.  
   It returns an integer less than, equal to, or greater than zero 
   if pcS1 is found, respectively, to be less than, to match, or be 
   greater than pcS2. */ 

int Str_compare(const char pcS1[], const char pcS2[]);


/*-----------------------------------------------------------------*/

/* The Str_search() function finds the first occurrence of the 
   substring pcNeedle in the string pcHaystack.  The terminating null 
   bytes ('\0') are not compared. Returns a pointer to the start of 
   the substring in aHaystack if it exists or to the start of 
   pcHaystack if pcNeedle is empty or NULL otherwise */ 

char *Str_search(const char pcHaystack[], const char pcNeedle[]);

#endif

/*
Str_getLength	strlen
Str_copy	strcpy
Str_concat	strcat
Str_compare	strcmp
Str_search	strstr
*/ 
/*---------- ID HEADER -------------------------------------
/  Author(s):   Andrew Boisvert, Kyle Scidmore
/  Email(s):    abois526@mtroyal.ca, kscid125@mtroyal.ca
/  File Name:   stringlib.c
/
/  Program Purpose(s):
/    String functions including comparison, length, copying, 
/    and converting process IDs to strings.
/---------------------------------------------------------*/

#include "stringlib.h"
#include <sys/types.h>

/*---------- FUNCTION: string_comp ------------------------- 
/  PURPOSE:
/    Compares two strings for equality. Returns 0 if the 
/    strings are equal, -1 if they are different.
/  
/  CALLER INPUT:
/    const char *str1
/      Pointer to the first string to be compared.
/    const char *str2
/      Pointer to the second string to be compared.
/  
/  CALLER OUTPUT:
/    Returns '0' if both strings are equal; otherwise, 
/    returns '-1'.
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    - Both input strings should be null-terminated. 
/      No bounds checking is performed on the input strings.
/---------------------------------------------------------*/
int string_comp(const char *str1, const char *str2) {
    while (*str1 && *str2) {
        if (*str1 != *str2) {
            return -1;
        }
        str1++;
        str2++;
    }
    return (*str1 != *str2) ? -1 : 0;
}

/*---------- FUNCTION: string_len -------------------------- 
/  PURPOSE:
/    Calculates the length of a string.
/  
/  CALLER INPUT:
/    const char *str
/      Pointer to a string.
/  
/  CALLER OUTPUT:
/    Returns the length of the string as an int.
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    - The input string should be null-terminated.
/---------------------------------------------------------*/
int string_len(const char *str){

    int length = 0;

    while(*str != '\0'){

        length++;
        str++;

    }


    return length;
}


/*---------- FUNCTION: string_copy ------------------------- 
/  PURPOSE:
/    Copies a string into a buffer, 
/  
/  CALLER INPUT:
/    const char *src
/      Pointer to the source string.
/    char *dst
/      Pointer to the destination buffer.
/  
/  CALLER OUTPUT:
/    N/A-No return value. dst contains the copied string.
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    - dst must be large enough to hold the source.
/---------------------------------------------------------*/
void string_copy(const char *src, char *dst){

    while(*src != '\0'){

        *dst = *src;

        src++;
        dst++;
    }

    *dst = '\0';

}

/*---------- FUNCTION: pid_to_string ---------------------- 
/  PURPOSE:
/    Converts a PID to a string.
/  
/  CALLER INPUT:
/    pid_t pid
/      The PID to convert.
/    char *buffer
/      Pointer to a buffer for the string.
/  
/  CALLER OUTPUT:
/    N/A-No return value. The buffer contains the PID as a
/    string
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    N/A
/---------------------------------------------------------*/
void pid_to_string(pid_t pid, char *buffer){
    int i = 0;

    if (pid == 0) {
        buffer[i++] = '0';
    } else {

        while (pid > 0) {
            buffer[i++] = (pid % 10) + '0'; 
            pid /= 10; 
        }
    }

    buffer[i] = '\0';
    for (int j = 0; j < i / 2; j++) {
        char temp = buffer[j];
        buffer[j] = buffer[i - j - 1];
        buffer[i - j - 1] = temp;
    }
}

/*---------- FUNCTION: str_comp_by_len ---------------------
/  PURPOSE:
/    Compares two strings up to a specified length for equality.
/  
/  CALLER INPUT:
/    const char *str1
/      First string to compare.
/  
/    const char *str2
/      Second string to compare.
/  
/    int len
/      Number of characters to compare.
/  
/  CALLER OUTPUT:
/    Returns 0 if the strings are equal up to len; -1 if not.
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    - Assumes both strings are null-terminated. 
/---------------------------------------------------------*/
int str_comp_by_len(const char *str1, const char *str2, int len){

    for (int i = 0; i < len; i++) {
        if(str1[i] != str2[i]){
            return -1;
        }
    }

    return 0;
}

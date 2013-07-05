
/** @file libfortune-0.1.h
@author Daniel Black  */
/**
\mainpage libfortune is a small library creater for the OpenFortune fortune cookie program.
It contails libraries for string manipulation,math,and JSON file parsing.

Using libfortune to parse JSON is very simple.
 Just call JSON_Get_Root_object(*file) on the string containing the JSON you want to parse.
 It will return a pointer, which you can then pass to the other JSON functions.

 None of the JSON handling functions make a copy of the hierarchy in memory.
 All the magic happens in place on the file.

 Most of the JSON functions will return a null pointer on failure.

 There may be files that are NOT valid json that can be paresed with libfortune.
 The focus of this library is size, portability, and ease of use, not error handling.

The string libraries are also easy to use,
 and include many useful functions like copying,token replacement,adding two strings together, and automatically fixing capitolization.

The random number generator is based on the Authors own XABC-2,
designed for maximum speed and even distribution of entropy across the bits of the returned value.
The generator passes the most common tests of randomness and has a period of between 300 million and 2^32.

*/

/*+**************************************************************************************************
JSON function prototypes:
****************************************************************************************************/
/*JSON Data Types:*/
#define JSON_INVALID 0
#define JSON_NUM 1
#define JSON_ARRAY 2
#define JSON_OBJ 3
#define JSON_STRING 4

/** A valid JSON onject pointer in this library either points to the first char after the starting delimiter
    Or to the first digit or minus sign of a number. Ponters to numeric arrays are therefore ambiguous,
    but this should not be much of a practical concern. Ambiguity is resolved by assuming type of JSON_ARRAY,
    but getting integers still works, so really the context of what function is being run is used to resolve ambiguity.*/


void string_replace( unsigned char *str,
                     unsigned int strlen,
                     unsigned char *old,
                     unsigned char oldlen,
                     unsigned char *newstr,
                     unsigned char newlen,
                     unsigned char *output
                   );

unsigned char char_is_alphanumeric(char chr);
unsigned char char_is_printable(char chr);
char char_Upper(char chr);

void string_CapitalizationFixer(char *str);
void string_assign(char *to,char *str);
void string_append(char *to, char *from);
void string_replace_null( char *str,
                          char *old,
                          char *newstr,
                          char *output
                        );


char *JSON_Get_Object(  char *within,  char *objectname);
unsigned char is_a_number( char chr);
unsigned int JSONCount( char *within);
char *JSON_Array_Access( char *within, unsigned int index);
unsigned char JSON_Type( char *object);
void JSON_Get_String( char *from,  char *to);
signed int JSON_Get_Integer_Simple(char *obj);
char *JSON_Get_Root_Object(char *file);
char *JSON_Random_Pick(char *from);
unsigned int JSON_Count(char *within);
/*+*********************************************************************************************
Math Functions:
***********************************************************************************************/
unsigned int random_up_to(unsigned int max);
unsigned char randomize();
void init_rng(char s1,char s2,char s3);


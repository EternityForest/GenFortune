
/*this file is part of OpenFortune. OpenFortune is a replacement for the unix fortune utility with additional features
to support dynamicly generating fortunes in a phrasal template type system from JSON files describing how to put together a fortune.
OpenFortune is free software under the MIT licence. the docs and datafiles are Creative Commons atribution sharealike 3.0.*/

/** @file libfortune-0.1.c
 */

/**************************************************************************************************
 ***************************************************************************************************/
#include "libfortune-0.1.h"

/*&*************************************************************************************************
String Handling Functions:
 ****************************************************************************************************/
/**Replace all instances of old in str with newstr. Uses lengths instead of null-termination*/

/**@param *str A pointer to the start of str
 * @param *old A pointer to the start of old
 * @param *newstr A pointer to the start of newstr
 * @param oldlen The length of old
 * @param newlen The length of newstr
 * @param strlen The length of str
 * @param *output A pointer to the first byte of the output buffer*/
void
string_replace (unsigned char *str,
                unsigned int strlen,
                unsigned char *old,
                unsigned char oldlen,
                unsigned char *newstr,
                unsigned char newlen,
                unsigned char *output
               )
{
    //i is the input pointer, k is the output pointer and the two are nt synchronized.
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int k = 0;
    //This variable is used in the lookahaed to see if two strings match so far
    unsigned int match;
    for (i = 0; i < strlen; i++)
    {
        //If this character is not a possible starting point for the replacement string
        if (str[i] != old[0])
        {
            i++;
        }
        //Look ahead to see if this is a match
        else
        {
            match = 1;
            //check all next oldlen chars to match with old
            for (j = 0; j < oldlen; j++)
            {
                if (str[i + j] != old[j])
                {
                    //if at any point it doesnt match break the loop and pass
                    //the byte unchanged normally.
                    match = 0;
                    break;
                }
            }
            //if it was a match, then output the newstr string and skip i past the old strinng
            if (match)
            {
                for (j = 0; j < newlen; j++)
                {
                    output[k] = newstr[j];
                    k++;
                    i = i + oldlen;
                }

            }
            //if it was not a match just pass the char unchanged.
            else
            {
                output[k] = str[i];
                k++;
            }
        }
    }
}

/** Fix the capitalization of a string in place. Understands sentences, quotes, and singular pronoun 'I' and contractions beginning with 'i'.
    Does not understand separator commas, relationships,etc. Will not De-Captalize anything.
 @param *str The string to be capitalization-fixed in place
 */
void
string_CapitalizationFixer (char *str)
{
    unsigned int i = 0;
    unsigned char New_Sentence = 0;
    unsigned char Quotes = 0;
    unsigned char SingleQuotes = 0;

    //first letter of string
    str[0] = char_Upper (str[0]);
    if (str[0] == '"')
    {
        Quotes = 1;
    }
    i++;
    //Go over the whole string
    while (str[i])
    {
        //Always captalize the start of a new sentence
        if (New_Sentence)
        {
            //Wait till an anphanumeric char is found then capitalize it
            if (char_is_alphanumeric (str[i]))
            {
                str[i] = char_Upper (str[i]);
                New_Sentence = 0;
            }
        }

        //Check for the start of a new sentence
        else if (((str[i]) == '.') | (str[i] == '!') | (str[i] == '?'))
        {
            New_Sentence = 1;
        }

        //check for a quote mark
        if (str[i] == '"')
        {
            //Assume that quotes preceded by numbers are Imperial inches.
            //Also assume that a qute preceeded by not a space is incorrect and should be ignored.
            if (str[i - 1] == ' ')
            {
                Quotes = !Quotes;
                New_Sentence = Quotes;
            }

        }

        //check for a single quote mark.
        if (str[i] == '\'')
        {
            //Assume that quotes preceded by numbers are Imperial Feet.
            //Also assume that a qute preceeded by not a space is incorrect and should be ignored.
            if (str[i - 1] == ' ')
            {
                SingleQuotes = !SingleQuotes;
                New_Sentence = SingleQuotes;
            }

        }

        //Capitalize the singular pronoun "I"
        if (str[i] == 'i')
        {
            //Check that it is preceded by a space and not the previous part of a word
            if (str[i - 1] == ' ')
            {
                if ((str[i + 1] == 0) | (str[i + 1] == ' ') | (str[i - 1] == '\''))
                {
                    str[i] = char_Upper (str[i]);

                }
            }

        }
        i++;
    }
}

/**Turns any lowercase ascii value into the equivalent uppercase and passes anything else unchanged.
 * @param chr the character to be capitalized
 * @return A capitalized version of chr
 */
char
char_Upper (char chr)
{
    //make sure it is in the ASCII(or UTF-8) lowercasse range
    if ((chr <= 122)&((chr >= 97)))
    {
        //subtract the difference between a character and its ascii uppercase equivalent
        return (chr - (97 - 65));
    }
    else
    {
        return (chr);
    }
}

/**Returns weather or not the character is 0-9 a-z or A-Z
 * @param chr the character to be tested.
 * @return weather or not the character is 0-9 a-z or A-Z
 */
unsigned char
char_is_alphanumeric (char chr)
{
    return (((chr >= 48)&(chr <= 57)) | ((chr >= 65) &(chr <= 90)) | ((chr >= 97)&(chr <= 122)));
}

/**Returns true if char is printable
 * @param chr the ascii char to be tested
 * @return true if char is printable
 */
unsigned char
char_is_printable (char chr)
{
    return ((chr >= 32)&(chr <= 126));
}
/**Replace all instances of old in str with newstr. Uses null-termination.
You must not use this for in place replacement unless *old and *new are the same length.*/

/**@param *str A pointer to the start of str
 * @param *old A pointer to the start of old
 * @param *newstr A pointer to the start of newstr
 * @param *output A pointer to the first byte of the output buffer*/
void
string_replace_null (char *str,
                     char *old,
                     char *newstr,
                     char *output
                    )
{
    //i is the input pointer, k is the output pointer and the two are nt synchronized.
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int k = 0;
    unsigned int oldlen;
    //This variable is used in the lookahaed to see if two strings match so far
    unsigned int match = 0;
    while (str[i])
    {
        //If this character is a possible starting point for the replacement string
        if (str[i] == old[0])
        {
            match = 1;
            //check all next oldlen chars to match with old
            j = 0;
            while (old[j])
            {

                if (str[i + j] != old[j])
                {
                    //if at any point it doesnt match break the loop and pass
                    //the byte unchanged normally.
                    match = 0;
                    break;

                }
                j++;
            }
        }
        oldlen = j;
        //if it was a match, then output the newstr string and skip i past the old strinng
        if (match)
        {
            j = 0;
            while (newstr[j])
            {
                output[k] = newstr[j];
                k++;
                j++;
            }
            //Compensate for the posint at loop's end
            i = i + oldlen - 1;
            match = 0;
        }
        //if it was not a match just pass the char unchanged.
        else
        {
            output[k] = str[i];
            match = 0;
            k++;
        }


        i++;

    }
    output[k] = 0;
}

/**
Append a cpy of *from to *to.
@param *to the base string
@param *from the string to be appended
 */
void
string_append (char *to, char *from)
{
    unsigned int i = 0;
    unsigned int j = 0;
    while (1)
    {
        if (to[i])
        {
            i++;
        }
        else
        {
            break;
        }
    }

    while (1)
    {
        if (from[j])
        {
            to[i] = from[j];
            i++;
            j++;
        }
        else
        {
            break;
        }
    }
    to[i] = 0;


}

/** Assign a string literal to an array at runtime.
@param  *to a string that is to contain str
@param  *str a string to be stored in to.
 */
void
string_assign (char *to, char *str)
{
    int i = 0;
    while (str[i])
    {
        to[i] = str[i];
        i++;
    }
    to[i] = 0;
}
/*!********************************************************************************************************
JSON Parsing Functions
 ***********************************************************************************************************/

/**Get the pointer to the highest-level object in a JSON file string given a pointer to the start of that string
@param *file A pointer t the first character of a JSON file.
@return A pointer to the root object that can be passed to the fuctions in this library that expect an object*/
char *
JSON_Get_Root_Object (char *file)
{
    /*Basically just skip ahead to the first byte after the '{' */
    while ((*file) != '{')
    {
        file++;
    }
    file++;
    return file;
}

/**
 * Get a pointer to the start of a JSON object,number,array,or string within a JSON object.
 * may be run recursively to provide simple read only JSON input.
 * @param *within A pointer to the start of the JSON object to be searched within
 * @param *objectname a null-terminated string containing the name of the object we want a pointer to
 * @return Success:A pointer to the character after the starting delimeter of the object.
 * 		   Failure:The NULL Pointer.
 */
char *
JSON_Get_Object (char *within, char *objectname)
{

    unsigned int i = 0;
    unsigned int k = 0;
    unsigned char issuccess = 0;
    //the char under i
    unsigned char thischar = 1;
    unsigned char lastchar = 1;
    //Was the last char an unescaped escape?
    unsigned char lastcharwasescape = 0;
    //Is this char an unescaped escape?
    unsigned char thischarisescape = 0;
    //Are we looking at an identifier in the root of the object that
    //we have not already eliminated?
    unsigned char looking_at_top_level_identifier = 1;
    //are we outside of a pair of quotes?
    unsigned char NotInQuotes = 1;
    unsigned char objectnamepointer = 0;
    //How deep are we in the data heirarchy
    unsigned char CurrentNestingLevel = 1;
    //Search until we reach the end of the object.
    //Or until we hit a null terminator
    while (CurrentNestingLevel && thischar)
    {
        thischar = within[k];
        thischarisescape = 0;
        if (!lastcharwasescape)
        {


            if (thischar == '\\')
            {

                thischarisescape = 1;

            }
            //toggle the quotation status if we find an unescaped quotation mark starting or ending a quotation.

            if (thischar == '"')
            {
                NotInQuotes = !NotInQuotes;
            }

        }
        //Only check for braces outside of quotation marks
        if (NotInQuotes)
        {
            //when we find a starting brace go one level deeper
            if ((thischar == '{') | (thischar == '['))
            {
                CurrentNestingLevel++;
            }
            //same thing if we find an ending brace reduce by one level
            if ((thischar == '}') | (thischar == ']'))
            {
                CurrentNestingLevel--;
            }

            //if we see a comma, and we are in the top nesting level
            //and we are not already looking at something interesting
            //and we are not in quotes, it must be the delimiter to start the net value,
            //so what follows after the whitespace should be...the next identifier!!!!
            if (thischar == ',')
            {
                if (CurrentNestingLevel == 1)
                {
                    if (!looking_at_top_level_identifier)
                    {
                        looking_at_top_level_identifier = 1;
                    }
                }
            }
        }

        //do not try and look for the name in a string literal or something annoying like that.
        if (looking_at_top_level_identifier)
        {

            //if we are not along the path of a possible match
            if (issuccess == 0)
            {
                //changed
                //if the last char was the start of an identifier
                if (lastchar =='"')
                {


                    //detect start of a possible match path
                    if (thischar == objectname[0])
                    {
                        //set variable indicating a possible match has started ans is in progress.
                        issuccess = 1;
                        //we already did 0
                        objectnamepointer = 1;
                    }
                }


            }
            //if we are currently on the train of a match
            else
            {
                //if we have sucessfully matched all of the objectname get out of the loop!
                //but only if we have also reached the end of the identifier we are searching.
                if (objectname[objectnamepointer] == 0)
                {
                    if (within[(k)] == '"')
                    {
                        break;
                    }
                }
                if (thischar == objectname[objectnamepointer])
                {
                    objectnamepointer++;
                }
                //when we detect a non matching character

                else
                {
                    issuccess = 0;
                    looking_at_top_level_identifier = 0;
                }

            }

        }
        ////
        k++;
        lastchar = thischar;
        lastcharwasescape = thischarisescape;
    }
    i = k;
    //if we sucessfully found the objectname, then skip past all whitespace to the first byte past the object delimiter
    //or to the first digit if a number
    if (issuccess && (thischar != 0))
    {
        //skip to the :
        while (1)
        {
            if (within[i] == ':')
            {
                break;
            }
            i++;
        }
        //ship to the first valid JSON value start
        while (1)
        {

            if ((within[i] == '"') | (within[i] == '[') | (within[i] == '{'))
                return (within + i + 1);
            if (is_a_number (within[i]))
                return (within + i);
            i++;
        }
    }
    else
    {
        //return a null pointer.
        return (0);
    }
}

/**
 * Return true if the input is a numeric digit.
 * @param chr the character to be tested for numeric content.
 */
unsigned char
is_a_number (char chr)
{
    return ((chr > 0x30)&&(chr < 0x39));
}

/**
 * Count the size of a JSON array or the number of members of an object.
 * @param *within A pointer to the start of an array(one past the delimiter)
 * @return The number of members in *within or zero if an error occurred.
 */
unsigned int
JSON_Count (char *within)
{
    unsigned char CurrentNestingLevel = 1;
    unsigned char thischar = 'f'; //arbitrary
    unsigned char lastchar;
    unsigned char lastcharwasescape = 0;
    unsigned char thischarisescape;
    unsigned char NotInQuotes = 1;
    unsigned int i = 0;
    //assume we have one to start with
    unsigned int ArrayCount = 1;
    if (!within)
    {
        return (0);
    }
    //search until end of object or null terminator
    while (CurrentNestingLevel && thischar)
    {
        thischar = within[i];
        thischarisescape = 0;
        if(!lastcharwasescape)
        {


            if (thischar == '\\')
            {
                thischarisescape = 1;
            }


            if (thischar == '"')
            {
                NotInQuotes = !NotInQuotes;
            }
        }

        if (NotInQuotes)
        {
            if (CurrentNestingLevel == 1)
            {
                if (thischar == ',')
                {
                    ArrayCount++;
                }
            }
            //when we find a starting brace go one level deeper
            if ((thischar == '{') | (thischar == '['))
            {
                CurrentNestingLevel++;
            }
            //same thing if we find an ending brace reduce by one level
            if ((thischar == '}') | (thischar == ']'))
            {
                CurrentNestingLevel--;
            }

        }
        i++;
        lastcharwasescape = thischarisescape;
        lastchar = thischar;

    }

    if (thischar)
    {
        return (ArrayCount);
    }
    else
    {
        return (0);
    }

}

/**
 *Return a pointer to element N of JSON array or object N. If used on an object the pointer returned will
 *be to the key. Array index is assumed to be zero based.
 *Should return null on out of bounds errors
 *@param *within A pointer to the beginning of a JSON array or Object.(One past the starting delimiter)
 *@param index An index into the JSON array.
 *@return a pointer to element N of array(one past the delimiter)
 */
char *
JSON_Array_Access (char *within, unsigned int index)
{
    unsigned char CurrentNestingLevel = 1;
    unsigned char thischar = 1;
    unsigned char lastchar;
    unsigned int ArrayCount = 0;
    unsigned int i = 0;
    unsigned char NotInQuotes = 1;
    unsigned char lastcharwasescape = 0;
    unsigned char thischarisescape = 0;

    if (!within)
    {
        return (0);
    }

    //Loop over all the characters of the object until we are at nesting level 0,
    //which means we are outside of the object we started in
    while (CurrentNestingLevel && thischar)
    {
        thischar = within[i];
        thischarisescape = 0;
        if (thischar == '\\')
        {
            if (!lastcharwasescape)
            {
                thischarisescape = 1;
            }
        }
        //If the array count is actually the one we want then just skip to the useful data
        if (ArrayCount == index)
        {
            while (1)
            {
                //Skip to where we want to return a pointer to

                if ((within[i] == '"') | (within[i] == '[') | (within[i] == '{'))
                    return (within + i + 1); //The plus one is because object pointers in this file always are one past the delimiter or are the first byte of a numeric string
                if (is_a_number (within[i]))
                    return (within + i);
                i++;
            }
        }

        //When we find an un-escaped string, set a flag acknowledging that the quotation status has changed
        if (thischar == '"')
        {
            if (!lastcharwasescape)
            {
                NotInQuotes = !NotInQuotes;
            }
        }

        //Only check for array members and nesting level changes outside of quotes
        if (NotInQuotes)
        {
            //We only want to count direct members of the object, not the members of members
            if (CurrentNestingLevel == 1)
            {
                if (thischar == ',')
                {
                    ArrayCount++;
                }
            }
            //when we find a starting brace go one level deeper
            if ((thischar == '{') | (thischar == '['))
            {
                CurrentNestingLevel++;
            }
            //same thing if we find an ending brace reduce by one level
            if ((thischar == '}') | (thischar == ']'))
            {
                CurrentNestingLevel--;
            }

        }
        i++;
        lastchar = thischar;
        lastcharwasescape = thischarisescape;
    }
    //return null on out of bounds
    return (JSON_INVALID);
}

/**
Take a JSON pointer to a numeric value and return its value as an signed int.
Anything after the decimal point is ignored, so it rounds down.
Exponents are also ignored, thats why its called "Simple"
Overflow will occur if the value is too big for an int.
@param *obj A pointer to the start of the number. This is either the first digit or the minus sign if one is present.
@returns The value of the numeric string.
 */
signed int
JSON_Get_Integer_Simple (char *obj)
{
    unsigned int i = 0;
    signed int OrderOfMagnitude = 1;
    signed int Total = 0;
    //check if the number is negative
    if (obj[0] == '-')
    {
        i++;
        OrderOfMagnitude = -1;
    }

    while (1)
    {
        //seek to least significant digit.
        if (is_a_number (obj[i]))
        {
            i++;
        }
        else
        {
            break;
        }
    }
    i--;
    while (1)
    {
        if (!is_a_number (obj[i]))
        {
            break;
        }
        //48 is to translate ASCII->Digit
        Total += (obj[i] - 48) * OrderOfMagnitude;
        OrderOfMagnitude *= 10;
        if(i)i--; else break;
    }
    return (Total);
}

/**
Get the type of an object pointed to by a JSON object pointer.
Recieving a valid response does not mean the object is truly valid, just that the beginning looks valid
@param *object A pointer to the byte after the delimeter of the object.
@return An unsigned char which may be referenced to JSON_OBJ, JSON_NUM,JSON_ARRAY, or JSON_STRING
@bug will return a string not obj of pointed at an object's key.
 */
unsigned char
JSON_Type (char *object)
{

    //if passed a null pointer
    if (object == 0)
    {
        return (JSON_INVALID);
    }
    if (object[-1] == '[')
    {
        return (JSON_ARRAY);
    }
    if (object[-1] == '{')
    {
        return (JSON_OBJ);
    }
    if (object[-1] == '"')
    {
        return (JSON_STRING);
    }
    //Numbers are made of all digits unless the start with a minus sign.
    //We check this last to catch quoted numbers in the earlier statement
    if (is_a_number (object[0]) | (object[0] == '-'))
    {
        return (JSON_NUM);
    }

    //If control makes it this far, then it did not match obj num str or array so we assume invalid.
    return (JSON_INVALID);
}

/**
Copy a string from a JSON object into memory. Add a null terminator to the copy.
If passed a null pointer in from, does nothing.
@param *from A pointer to one byte past the delimiter of the string
@param *to A pointedr to the first byte of the area the string is to be copied to
 */
void
JSON_Get_String (char *from, char *to)
{
    unsigned char lastcharwasescape = 0;
    unsigned char thischarisescape;
    unsigned char thischar = 0;
    unsigned int i = 0;
    unsigned int j = 0;

    if ((from == 0))
    {
        string_assign (to, "ERROR");
    }


    //check for null pointers
    if (from)
    {


        while (1)
        {
            thischar = from[i];
            thischarisescape = 0;
            if (!lastcharwasescape)
            {
                //unescaped ending quotation mark
                if (thischar == '"')
                {

                    break;

                }
                if (thischar == '\\')
                {

                    thischarisescape = 1;
                }
                else
                {
                    to[j] = from[i];
                    j++;

                }
            }


            //handle escaple sequences

            else
            {
                switch (thischar)
                {
                case '"':
                    to[j] = '"';
                    break;
                case 'n':
                    //Ascii CRLF not just newline
                    to[j] = 13;
                    to[++j] = 10;
                    break;
                case'\\':
                    to[j] = '\\';
                    break;
                case'/':
                    to[j] = '/';
                    break;
                case't':
                    to[j] = '\t';
                    break;
                }
                j++;
            }
            i++;
            lastcharwasescape = thischarisescape;
        }
        //add null terminator
        to[j] = 0;
    }
}

char *
JSON_Random_Pick (char *from)
{
    int ArraySize;
    ArraySize = JSON_Count (from);
    return (JSON_Array_Access (from, (random_up_to (ArraySize - 1))));

}
/*!***************************************************************************************************
Math Functions:
 ******************************************************************************************************/
static unsigned char a, b, c, x;


static const unsigned char inv_s[256] =
{
    0x52, 0x09, 0x6A, 0xD5, 0x30, 0x36, 0xA5, 0x38, 0xBF, 0x40, 0xA3, 0x9E, 0x81, 0xF3, 0xD7, 0xFB,
    0x7C, 0xE3, 0x39, 0x82, 0x9B, 0x2F, 0xFF, 0x87, 0x34, 0x8E, 0x43, 0x44, 0xC4, 0xDE, 0xE9, 0xCB,
    0x54, 0x7B, 0x94, 0x32, 0xA6, 0xC2, 0x23, 0x3D, 0xEE, 0x4C, 0x95, 0x0B, 0x42, 0xFA, 0xC3, 0x4E,
    0x08, 0x2E, 0xA1, 0x66, 0x28, 0xD9, 0x24, 0xB2, 0x76, 0x5B, 0xA2, 0x49, 0x6D, 0x8B, 0xD1, 0x25,
    0x72, 0xF8, 0xF6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xD4, 0xA4, 0x5C, 0xCC, 0x5D, 0x65, 0xB6, 0x92,
    0x6C, 0x70, 0x48, 0x50, 0xFD, 0xED, 0xB9, 0xDA, 0x5E, 0x15, 0x46, 0x57, 0xA7, 0x8D, 0x9D, 0x84,
    0x90, 0xD8, 0xAB, 0x00, 0x8C, 0xBC, 0xD3, 0x0A, 0xF7, 0xE4, 0x58, 0x05, 0xB8, 0xB3, 0x45, 0x06,
    0xD0, 0x2C, 0x1E, 0x8F, 0xCA, 0x3F, 0x0F, 0x02, 0xC1, 0xAF, 0xBD, 0x03, 0x01, 0x13, 0x8A, 0x6B,
    0x3A, 0x91, 0x11, 0x41, 0x4F, 0x67, 0xDC, 0xEA, 0x97, 0xF2, 0xCF, 0xCE, 0xF0, 0xB4, 0xE6, 0x73,
    0x96, 0xAC, 0x74, 0x22, 0xE7, 0xAD, 0x35, 0x85, 0xE2, 0xF9, 0x37, 0xE8, 0x1C, 0x75, 0xDF, 0x6E,
    0x47, 0xF1, 0x1A, 0x71, 0x1D, 0x29, 0xC5, 0x89, 0x6F, 0xB7, 0x62, 0x0E, 0xAA, 0x18, 0xBE, 0x1B,
    0xFC, 0x56, 0x3E, 0x4B, 0xC6, 0xD2, 0x79, 0x20, 0x9A, 0xDB, 0xC0, 0xFE, 0x78, 0xCD, 0x5A, 0xF4,
    0x1F, 0xDD, 0xA8, 0x33, 0x88, 0x07, 0xC7, 0x31, 0xB1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xEC, 0x5F,
    0x60, 0x51, 0x7F, 0xA9, 0x19, 0xB5, 0x4A, 0x0D, 0x2D, 0xE5, 0x7A, 0x9F, 0x93, 0xC9, 0x9C, 0xEF,
    0xA0, 0xE0, 0x3B, 0x4D, 0xAE, 0x2A, 0xF5, 0xB0, 0xC8, 0xEB, 0xBB, 0x3C, 0x83, 0x53, 0x99, 0x61,
    0x17, 0x2B, 0x04, 0x7E, 0xBA, 0x77, 0xD6, 0x26, 0xE1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0C, 0x7D
};

/**Put up to 3 bytes of new entropy by XORing into the state and cycle the genarator to
avoid ill effects resulting from biases in seed data
 */
void
init_rng (char s1, char s2, char s3)//Can also be used to seed the rng with more entropy during use.
{
    //XOR new entropy into key state
    a ^= s1;
    b ^= s2;
    c ^= s3;

    x++;
    a = (a^c^x);
    b = (b + a);
    c = ((c + (b >> 1))^a);
}

/** Generate a random byte using XABC
 *  @return 1 unsigned char containing an evenly distributed random number
 * */
unsigned char
randomize ()
{
    x++; //x is incremented every round and is not affected by any other variable
    a = (a ^ c ^ x); //note the mix of addition and XOR
    b = (b + a); //And the use of very few instructions
    c = ((c + inv_s[b]) ^ a); // the AES S-Box Operation ensures an even distributon of entropy
    return (c);
}
/** Generate a random number between 0 and x inclusive. I am not a math professor, so be wary of my untested speed hack :)
Basically we generate random numbers till one fits in the range. however, we also progressivly mask off more and more high order bits
until the mask is >= twice the max number we want. The RNG was specifically designed not to have bias issues.
 * @return 1 random number between 0 and x
 */

/*
What we do is we continually generate numbers till we get one in the right range.
However we mask off one extra high bit until the mask is smaller than the max.
 */
unsigned int
random_up_to (unsigned int max)
{
    unsigned int mask = 0xFFFF; //all ones
    unsigned int total;
    while (1)
    {


        x++; //x is incremented every round and is not affected by any other variable
        a = (a ^ c ^ x); //note the mix of addition and XOR
        b = (b + a); //And the use of very few instructions
        c = ((c + inv_s[b]) ^ a); // the AES S-Box Operation ensures an even distributon of entropy
        total = c;

        x++; //x is incremented every round and is not affected by any other variable
        a = (a ^ c ^ x); //note the mix of addition and XOR
        b = (b + a); //And the use of very few instructions
        c = ((c + inv_s[b]) ^ a); // the AES S-Box Operation ensures an even distributon of entropy
        total += (unsigned int) c << 8;

        if (((total & mask) <= max))
        {
            return (total & mask); //z
        }

        if ((mask >> 1) >= max)
        {
            mask = mask >> 1;
        }
    }
}

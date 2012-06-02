/*this file is part of OpenFortune. OpenFortune is a replacement for the unix fortune utility with additional features
to support dynamicly generating fortunes in a phrasal template type system from JSON files describing how to put together a fortune.
OpenFortune is free software under the MIT licence. the docs and datafiles are Creative Commons atribution sharealike 3.0.*/

#include <stdio.h>
#include <time.h>
#include "libfortune-0.1.h"
#include <signal.h>
#include <stdlib.h>

#define DEFAULT_FANTASY
#include "default.h"
void generate_fortune();

char outputbuffer[20000];
char outputbuffer2[20000];
char *here ;
char *root;
char *parts;
char *macro;
char thiskeyword[255];
char thiskeywordselection[255];
int recursion;
//what output buffer was last written to
int lastused;

FILE *JSON_File;
void SegFaultHandler();
int i;
int j;
int temp;
int totalpatterns;

int main(int argc,char **argv)
{
    signal(SIGSEGV,SegFaultHandler);
    //Seed the random number generator with all sorts of timing stuff cast to unsigned char
    init_rng((char)time(0),(char)clock(),(char)clock());

    //if there is at least one argument
    if(argc-1)
    {
        JSON_File = fopen(*(argv+1),"r");
        //for some reason, fread would not work i remember
        while((temp=fgetc(JSON_File))!=EOF)
        {
            json[i]=temp;
            i++;
        }
        json[i]=0;
        fclose(JSON_File);

    }

    root = JSON_Get_Root_Object(json);
//User interface loop. press any key to generate a new fortune or uppercase Q to quit
    while(1)
    {
        generate_fortune();
        printf(outputbuffer2);
        printf("\n");
        if ('Q'==getchar()) exit(0);
    }

}
void SegFaultHandler()
{
    printf("An error occured(Segmentation Fault). Please check that the fortune file is correct.");
    getchar();
    exit(1);
}

void generate_fortune()
{
    //get a starting pattern
    here = JSON_Get_Object(root,"Patterns");
    here = JSON_Random_Pick(here);
    JSON_Get_String(here,outputbuffer);

    here = JSON_Get_Object(root,"Recursion");
    recursion = JSON_Get_Integer_Simple(here) + 1;

    //iterate for recursion
    for(i = 0; i <= (recursion); i++)
    {
        //iterate over patterns
        totalpatterns = JSON_Count(JSON_Get_Object(root,"Parts"));
        for(j = 0; j<= totalpatterns; j++)
        {
            //Seed the random number generator with all sorts of timing stuff cast to unsigned char
            init_rng((char)time(0),0,0);
            parts = JSON_Get_Object(root,"Parts");
            here = JSON_Array_Access(parts,j);

            JSON_Get_String(here,thiskeyword);
            here = JSON_Get_Object(parts,thiskeyword);
/////////////////
            here = JSON_Random_Pick(here);
            JSON_Get_String(here,thiskeywordselection);
            //All this lastused is to handle the back and forth replacement becaus libfortune doesnt do
            //inplace replacement at the moment
            if(j&1)
            {
                string_replace_null(outputbuffer2,thiskeyword,thiskeywordselection,outputbuffer);
                lastused = 1;
            }
            else
            {
                string_replace_null(outputbuffer,thiskeyword,thiskeywordselection,outputbuffer2);
                lastused = 2;
            }
        }
        if (lastused == 2)
        {
            string_assign(outputbuffer,outputbuffer2);
        }
        //iterate over macros
        totalpatterns = JSON_Count(JSON_Get_Object(root,"Macro"));
        for(j = 0; j<= totalpatterns; j++)
        {
            //Seed the random number generator with all sorts of timing stuff cast to unsigned char
            init_rng((char)time(0),0,0);
            macro = JSON_Get_Object(root,"Macro");
            here = JSON_Array_Access(macro,j);

            JSON_Get_String(here,thiskeyword);
            here = JSON_Get_Object(macro,thiskeyword);

            here = JSON_Random_Pick(here);
            JSON_Get_String(here,thiskeywordselection);
            if(j&1)
            {
                string_replace_null(outputbuffer2,thiskeyword,thiskeywordselection,outputbuffer);
                lastused = 1;
            }
            else
            {
                string_replace_null(outputbuffer,thiskeyword,thiskeywordselection,outputbuffer2);
                lastused = 2;
            }
        }


        if (lastused == 2)
        {
            string_assign(outputbuffer,outputbuffer2);
        }
    }


    //Add endings and beginnings
    here = JSON_Get_Object(root,"Introductions");
    JSON_Get_String(JSON_Random_Pick(here),outputbuffer2);
    string_append(outputbuffer2,outputbuffer);
    here = JSON_Get_Object(root,"Endings");
    JSON_Get_String(JSON_Random_Pick(here),outputbuffer);
    string_append(outputbuffer2,outputbuffer);
    string_CapitalizationFixer(outputbuffer2);
    //Seed the random number generator with all sorts of timing stuff cast to unsigned char
    init_rng((char)time(0),(char)clock(),(char)clock());
}

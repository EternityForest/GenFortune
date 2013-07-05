//VERY basic Test suite for libfortune. also mit licenced.
//Not intended as a comprehensive test, this is as much about demonstrating the library as it is about testing.
#include <stdio.h>
#include <time.h>
#include "libfortune-0.1.h"
#include <signal.h>
#include <stdlib.h>

//an example json file
char *example_json_two_strings = "{\"str\":[\"one\",\"two\"]}"; //{"str":["one","two"]};
char *example_json_number = "1234,random garbage";
char *temp, temp2[100];


main()
{
    //get root test
    printf("Getting JSON root. should say: \"str\":[\"one\",\"two\"]}\n");
    temp = JSON_Get_Root_Object(example_json_two_strings);
    printf(temp);
    printf("\n");

    //object test
    printf("Getting array object. should say: \"one\",\"two\"]\n");
    temp = JSON_Get_Object(temp,"str");
    printf(temp);
    printf("\n");

    //counting arrays  test
    printf("Counting array elements. should say: 2\n");
    printf("%d",JSON_Count(temp));

    printf("\n");

    //getting string object test
    printf("getting secon string object. should say: two\"XXXXXXXXXXXXXXXXXXXX where xxxx is don't care");
    temp = JSON_Array_Access(temp,1);//is zero based
    printf("\n");
    printf(temp);
    printf("\n");

//getting string itself test
    printf("Getting string directly. should say: two");
    JSON_Get_String(temp,temp2);
    printf("\n");
    printf(temp2);
    printf("\n");

//Random number test
    printf("Making a random number again and again. should be up to 255: \n");
    init_rng((char)time(0),0,0);
    printf("%d    ",randomize());
    printf("%d    ",randomize());
    printf("%d    ",randomize());
    printf("%d    ",randomize());
    printf("%d    ",randomize());
    printf("%d    ",randomize());
    printf("%d    ",randomize());
    printf("%d    ",randomize());
    printf("%d    ",randomize());
    printf("%d    ",randomize());
    printf("%d    ",randomize());
    printf("%d    ",randomize());
    printf("%d    ",randomize());
    printf("\n");
    printf("%d    ",randomize());
    printf("%d    ",randomize());
    printf("%d    ",randomize());
    printf("%d    ",randomize());
    printf("%d    ",randomize());
    printf("%d    ",randomize());
    printf("%d    ",randomize());
    printf("%d    ",randomize());
    printf("%d    ",randomize());
    printf("%d    ",randomize());
    printf("%d    ",randomize());
    printf("%d    ",randomize());
    printf("\n");
    printf("thinking of numbers between zero and ten\n");
    printf("%d    ",random_up_to(10));
    printf("%d    ",random_up_to(10));
    printf("%d    ",random_up_to(10));
    printf("%d    ",random_up_to(10));
    printf("%d    ",random_up_to(10));
    printf("%d    ",random_up_to(10));
    printf("%d    ",random_up_to(10));
    printf("%d    ",random_up_to(10));
    printf("%d    ",random_up_to(10));
    printf("%d    ",random_up_to(10));
    printf("%d    ",random_up_to(10));
    printf("\n");
    printf("%d    ",random_up_to(10));
    printf("%d    ",random_up_to(10));
    printf("%d    ",random_up_to(10));
    printf("%d    ",random_up_to(10));
    printf("%d    ",random_up_to(10));
    printf("%d    ",random_up_to(10));
    printf("%d    ",random_up_to(10));
    printf("%d    ",random_up_to(10));
    printf("%d    ",random_up_to(10));
    printf("%d    ",random_up_to(10));
    printf("%d    ",random_up_to(10));
    printf("\n");


//string replacement test
    printf("replacing strings. Should say: \"never mind the man behind the curtain\"\n");
    string_replace_null("never mind the boy behind the curtain","boy","man",temp2);
    printf(temp2);
    printf("\n");

// Capitalization fixer test

    printf("fixing capitalization. Should not have capitalization errors: \n");
    //note the errors which the function will hopefully fix.
    string_assign(temp2,"the quick brown fox jumps over the lazy dog. i think the red squirrel is big for this area.");
    string_CapitalizationFixer(temp2); //this function always works in place.
    printf(temp2);
    printf("\n");
    printf("\n");

//String appending test
    printf("concatenating. should say \"I fart in your general direction!\"\n");
    string_assign(temp2,"I fart ");
    string_append(temp2,"in your general direction!");
    printf(temp2);
    printf("\n");

    printf("checking json get number. should say 1234\n");


    printf("%d",JSON_Get_Integer_Simple(example_json_number));
    printf("\n");


    printf("checking array acess out of bounds detection. should say: Passed.\n");
    if(JSON_Array_Access(example_json_two_strings,2) == 0)
    {

        printf("Passed");
    }
    else
    {
        printf("Failed");
    }

}

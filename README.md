# GenFortune

Like the standard linux fortune program, except it uses a Mad Libs style algorithm to generate the fortunes instead of just
choosing from a list.  

The C version is officially just archived here. Use  the python version.  The python version also supports Non-Kitten-Item formatted files.


Please note that nethack and robotfindskitten files are under their own license




## Usage:

Pick randomly(Prefers a Fortune Files dir in the same dir as the script, else uses /usr/share/genfortune)
```
daniel@castletown ~/P/G/Python Version> python3 genfortune.py
I declare a grand tournament do determine who is worthy of this ampoule of wig powder.

daniel@castletown ~/P/GenFortune> genfortune -v
Fortune generated from /usr/share/genfortune/anachronism.frtn:
I would pay 100 credits for that pair of spitoonworker's gloves.
```

Use a specific file(This is a parody of Intel CPU names)
```
daniel@castletown ~/P/GenFortune> genfortune list
Installed Fortune Files:

fantasy
harvardsentences
intelliname
anachronism
steampunk
armycodes
pirate
farts
emo
wilde
perlis
magicquotes

daniel@castletown ~/P/GenFortune> python3 genfortune.py from intelliname
Shadow Corner
daniel@castletown ~/P/GenFortune> python3 genfortune.py from intelliname
Ivy Bridge
daniel@castletown ~/P/GenFortune> python3 genfortune.py from intelliname
Lantern Hill
daniel@castletown ~/P/GenFortune> python3 genfortune.py from intelliname
Echo Pass
daniel@castletown ~/P/GenFortune> python3 genfortune.py from intelliname
Fallen Rock
daniel@castletown ~/P/GenFortune> python3 genfortune.py from intelliname
Badger Town
daniel@castletown ~/P/GenFortune> python3 genfortune.py from intelliname
Blue Gate
daniel@castletown ~/P/GenFortune> python3 genfortune.py from intelliname
Night Hall
daniel@castletown ~/P/GenFortune> python3 genfortune.py from intelliname
Battle Tree
daniel@castletown ~/P/GenFortune> python3 genfortune.py from intelliname
Gallows Bridge
```


To install on linux, "sudo sh linux_install.sh" and then you can run it with "genfortune".


### Creating your own files:

They are just JSON files(.frtn or .json names acceptable). It chooses a pattern, an ending, and an Introduction.

Then it replaces every Part name it finds with a rendom selection from that category. Once a selection
in a Part category has been used, it will not be used again in that fortune.

After that, it replaces every Macro it finds with one from that category. Unlike Parts, selections may be reused an unlimited number of times.

It repeats these two steps N times(Controlled by the number of recursions).

As you can see, here we use the rules to ensure two different -Objects are chosen.


```
{
    "Recursion" : 1,
    "Introductions":
        [
            "I wrote a letter saying ",
            "I should write a letter saying "
        ],
    "Endings":
        [
            " I should do that now."
        ],
    "Patterns":
        [
            "I went to the store and bought -Object and -2Object."
        ],
    "Parts":
        {
            "-Object":
                [
                    "a rug",
                    "a lamp",
                    "a lampshade"
                ]
        },
    "Macro":
        {
            "-2Object":
                [
                    "-Object"
                ]
        }
```
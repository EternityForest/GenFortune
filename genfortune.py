#!/usr/bin/python3

import sys

from random import choice, random
from random import seed
import os



availiblefortunefiles = []
availiblefortunefileslistforprinting = []
d = os.path.abspath(__file__)

d= os.path.dirname(d)



def load(d):
    global FortunesDir
    FortunesDir = d
    for i in os.listdir(d):
        x = os.path.join(d,i)
        if os.path.isfile(x) and (i.endswith(".frtn") or i.endswith(".json") or i.endswith(".nki")):
            availiblefortunefiles.append(x)
            availiblefortunefileslistforprinting.append(i[:-5])

if os.path.isdir(os.path.join(d,"Fortune Files")):
    load(os.path.join(d,"Fortune Files"))

elif os.path.isdir("/usr/share/genfortune"):
   load("/usr/share/genfortune")

seed(os.urandom(24))

def fixCap(string):
    output = ""
    inasentence = False
    for i in string:
        if inasentence:
            output+=(i)
            if i in '.?!':
                inasentence = False
        else:
            output+=(i.upper())
            if not i in " ?!":
                inasentence = True
                
    return output.replace(" i "," I ")


if len(sys.argv) ==1 or( (len(sys.argv)==2 )and '-v' in sys.argv):
    n = choice(availiblefortunefiles)
    if n.endswith("frtn"):
        filetype="gen"
    else:
        filetype="nki"
    

    f = open(n)
    
    if '-v' in sys.argv:
        print ("Fortune generated from "+n+":")
    
if len(sys.argv) > 1:
    if sys.argv[1] == '-f':
        f = open(sys.argv[2],'r')


    elif sys.argv[1] == 'from':
        if os.path.isfile(os.path.join(FortunesDir,sys.argv[2]+".frtn")):
            f = open(os.path.join(FortunesDir,sys.argv[2]+".frtn"))
            filetype="gen"
        elif os.path.isfile(os.path.join(FortunesDir,sys.argv[2]+".nki")):
            f = open(os.path.join(FortunesDir,sys.argv[2]+".nki"))
            filetype='nki' 
        else:
            print("No fortune file at " +os.path.join("/usr/share/genfortune",sys.argv[2]+".frtn"))
            quit()
    elif sys.argv[1] in ['help','-h']:
        print (
"""Usage:
>>>genfortune
    Print a fortune using a randomly chosen .frtn file from /usr/share/genfortune

>>>genfortune -v
    Print a fortune using a randomly chosen .frtn file from /usr/share/genfortune
    And also display what file it came from.

>>>genfortune -f <file>
    Print a fortune using the fortune file specified

>>>genfortune from <name>
    Print a fortune from a speciic file in /usr/share/genfortune. You do not need to add the .frtn at the end.

>>>openfortue list 
    List availible fortune files in /usr/share/genfortune (With file extensions removed)
    
    A
""")
        quit()
    elif sys.argv[1] == 'list':
        print("Installed Fortune Files:\n")
        for i in availiblefortunefileslistforprinting:
            print(i)
        quit()
    

dat = f.read()
f.close()
if filetype=='nki':
    x=[i.strip() for i in dat.split("\n")]
    l=[i for i in x if not i.startswith("#")]
    print(choice(l))

if filetype=='gen':
    Temp = 0
    import json
    Data = json.loads(dat)
    #Choose a random pattern from Patterns
    Pattern = choice(Data['Patterns'])

    #Repeat the substitution as many times as Recursion says to.
    #Or until we break.  So we add a few extra because htis wi
    for i in range(Data.get('Recursion',32) + 1):
        b = True
        #Iterate over all the keywords
        for j in Data['Parts'].keys():
            if j in Pattern:
                part = j
                #Replace each keyword with a random selection from Parts['keyword']
                x =choice(Data['Parts'][j])
                Pattern = Pattern.replace(j , x)
                #Unless the naming convention specifies that you can use the same selection twice removeit.
                if j.count("duplicate") == 0 :
                    Data['Parts'][j].remove(x)
                b=False

        for j in Data['Macro'].keys():
            if j in Pattern:
                #Replace each keyword with a random selection from Macro['keyword']
                Temp = choice(Data['Macro'][j]) 
                Pattern = Pattern.replace(j, choice(Data['Macro'][j]))
                #Unless the naming convention specifies that you can use the same selection twice remove it.
                b = False

        if b:
            break
            
    #Add intro and outtro and print the output
    Pattern = choice(Data['Introductions']) + Pattern
    Pattern = Pattern + choice(Data['Endings'])
    print(fixCap(Pattern))





    


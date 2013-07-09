#!/usr/bin/python

import sys

from random import choice
from random import seed
import os,dircache

availiblefortunefiles = []
availiblefortunefileslistforprinting = []
if os.path.isdir("/usr/share/openfortune"):
    for i in dircache.listdir("/usr/share/openfortune"):
        x = os.path.join("/usr/share/openfortune",i)
        if os.path.isfile(x) and i.endswith(".frtn"):
            availiblefortunefiles.append(x)
            availiblefortunefileslistforprinting.append(i[:-5])

seed()

def fixCap(string):
    output = ""
    inasentence = False
    for i in string:
        if inasentence:
            output+=(i)
            if i== '.':
                inasentence = False
        else:
            output+=(i.upper())
            if not i ==" ":
                inasentence = True
                
    return output.replace(" i "," I ")


if len(sys.argv) ==1 :
    f = open(choice(availiblefortunefiles))

if len(sys.argv) > 1:
    if sys.argv[1] == '-f':
        f = open(sys.argv[2],'r')


    elif sys.argv[1] == 'from':
        if os.path.isfile(os.path.join("/usr/share/openfortune",sys.argv[2]+".frtn")):
            f = open(os.path.join("/usr/share/openfortune",sys.argv[2]+".frtn"))
        else:
            print("No fortune file at " +os.path.join("/usr/share/openfortune",sys.argv[2]+".frtn"))
            quit()
    elif sys.argv[1] in ['help','-h']:
        print (
"""Usage:
>>>openfortune
    Print a fortune using a randomly chosen .frtn file from /usr/share/openfortune

>>>openfortune -f <file>
    Print a fortune using the fortune file specified

>>>openfortune from <name>
    Print a fortune from a speciic file in /usr/share/openfortune. You do not need to add the .frtn at the end.

>>>openfortue list 
    List availible fortune files in /usr/share/openfortune (With file extensions removed)
""")
        quit()
    elif sys.argv[1] == 'list':
        print("Installed Fortune Files:\n")
        for i in availiblefortunefileslistforprinting:
            print(i)
        quit()
    

dat = f.read()
f.close()
Temp = 0
import json
Data = json.loads(dat)
#Choose a random pattern from Patterns
Pattern = choice(Data['Patterns'])

#Repeat the substitution as many times as Recursion says to.
for i in range(Data['Recursion'] + 1):
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

    for j in Data['Macro'].keys():
            #Replace each keyword with a random selection from Macro['keyword']
            Temp = choice(Data['Macro'][j]) 
            Pattern = Pattern.replace(j, choice(Data['Macro'][j]))
            #Unless the naming convention specifies that you can use the same selection twice remove it.
        
#Add intro and outtro and print the output
Pattern = choice(Data['Introductions']) + Pattern
Pattern = Pattern + choice(Data['Endings'])
print(fixCap(Pattern))





    


#!/usr/bin/python

import sys

from random import choice
from random import seed
import os,dircache

availiblefortunefiles = []
if os.path.isdir("/usr/share/openfortune"):
    for i in dircache.listdir("/usr/share/openfortune"):
        x = os.path.join("/usr/share/openfortune",i)
        if os.path.isfile(x) and i.endswith(".frtn"):
            availiblefortunefiles.append(x)

seed()

if len(sys.argv)>1:
    f = open(sys.argv[1],'r')
else:
    f = open(choice(availiblefortunefiles))
dat = f.read()
f.close()
Temp = 0
import json
Data = json.loads(dat)
#Choose a random pattern from Patterns
Pattern = choice(Data['Patterns'])
try:
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
    print(Pattern)
except:
    print j

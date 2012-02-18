#!/usr/bin/python

import os
import random
import sys
wiki_dir="convertedData/wiki/"
uncyclo_dir="convertedData/uncyclopedia/"
mixed_dir="convertedData/mixed/"
nana_dir="convertedData/nana/"
file_id = 1

def createfile(wiki_lines,nana_lines,i):
    global file_id
    print nana_dir+str(file_id)+"_old"
    fd_nana1 = open(nana_dir+str(file_id)+"-old.txt",'w')
    fd_nana2 = open(nana_dir+str(file_id)+"-new.txt",'w')
    for j in wiki_lines:
        fd_nana1.write(j)
    fd_nana1.close()
    for j in nana_lines:
        fd_nana2.write(j)
    for j in wiki_lines[i:len(wiki_lines)]:
        fd_nana2.write(j)
    fd_nana2.close()
    file_id=file_id+1

for file in os.listdir(wiki_dir):
    try:
        fd_wiki = open(wiki_dir+file,'r')
        fd_mixed = open(mixed_dir+file.replace('wiki','mixed'),'r')
        #print wiki_dir+file
        wiki_lines = fd_wiki.readlines()
        mixed_lines = fd_mixed.readlines()
        nana_lines = []
        i=0
        while(i < len(wiki_lines)):
            no_lines_to_change = random.randint(1,3)
            while(i < len(wiki_lines) and (wiki_lines[i] == mixed_lines[i]) ):
                nana_lines.append(mixed_lines[i])
                i=i+1
            j=i
            no_edits=0
            while(i < len(wiki_lines) and (mixed_lines[j]!=wiki_lines[i]) ):
                nana_lines.append(mixed_lines[j])
                #print "*."+mixed_lines[j]
                mixed_lines.pop(j)
                no_edits = no_edits+1
            #print no_edits,no_lines_to_change
            if no_edits > no_lines_to_change: 
                if no_edits > 6:
                    print "mahesh"+no_edits
                createfile(wiki_lines,nana_lines,i)
                nana_lines = wiki_lines[0:i+1]
        #sys.exit(0)
    except IOError:
        print "File Not Found", file

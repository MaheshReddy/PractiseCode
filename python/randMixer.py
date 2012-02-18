#!/usr/bin/python
import os
import sys
import re
import random
import time
import nltk.tokenize

wiki_dir="convertedData/wiki/"
uncyclo_dir="convertedData/uncyclopedia/"
mixed_dir="convertedData/mixed/"

fileno = 1
def getNextPara(fd):
    para=[]
    line= fd.readline()
    while (line!='\n' and line != ""):
        para.append(line)
        line=fd.readline()
    if line == '\n':
        para.append(line)
    return para
#Decides if  the para is suitable for change
#def isSuitableForChange(para):
def isSuitableForChange(lines):
    #tokenizer = nltk.tokenize.PunktSentenceTokenizer()
    #lines = tokenizer.tokenize(para)
    if len(lines)<3:
        return 0
    regex_content = re.compile("\s*\*")
    for line in lines:
        if regex_content.search(line)!=None:
            return 0
    return 1

#def mix_paras(wiki_para_text,uncylo_para_text):
def mix_paras(wiki_para,uncylo_para):
    #Using nltk.tokenize.PunktSentenceTokenizer to tokenize give para to sentences
    #tokenizer = nltk.tokenize.PunktSentenceTokenizer()
    #wiki_para = tokenizer.tokenize(wiki_para_text)
    #uncylo_para=tokenizer.tokenize(uncylo_para_text)
    # I use randomization to either alter the wiki_para or not, else I use the random number to decide how many lines to edit
    random.seed(time.time())
    r = random.randint(0,4)
    if r == 0: # return original wiki text
        return wiki_para
    else : # add 'r' line from uncyclopedia
        while(r>=0):
            line_to_change = random.randint(0,len(wiki_para)-1)
            line_from_uncyclo = random.randint(0,len(uncylo_para)-1)
            wiki_para.insert(line_to_change,uncylo_para[line_from_uncyclo]) 
            #print wiki_para
            #print uncylo_para[line_from_uncyclo]
            uncylo_para.pop(line_from_uncyclo)
            if len(uncylo_para) == 0 or len(wiki_para) == 0: # not enought lines in uncylopedia/wiki para
                break
            r=r-1
    #rtr_str=""
    #for i in wiki_para:
    #    rtr_str=rtr_str+i
    #print wiki_para
    #return rtr_str
    return wiki_para

for file in os.listdir(wiki_dir):
    try:
        fd_wiki = open(wiki_dir+file,'r')
        fd_uncyclo = open(uncyclo_dir+file.replace('wiki','uncyclopedia'))
        fd_mixed = open(mixed_dir+file.replace('wiki','mixed'),'w')
        #print wiki_dir+file
        para_wiki = getNextPara(fd_wiki)
        #para_wiki = fd_wiki.readline()
        intial=0
        while para_wiki != []:
            #para_wiki = fd_wiki.readline() # I am assuing is each line is a para !! or rather each para is a line
            #print para_wiki
            # now checking if this para is suitable for change 
            #Ignoring if its intial 3 para's so that I don't change the intial crap in wiki
            #print para_wiki
            if isSuitableForChange(para_wiki) and intial >3:
                para_uncyclo = getNextPara(fd_uncyclo)
                #para_uncyclo = fd_uncyclo.readline()
                while((isSuitableForChange(para_uncyclo)!=1) and para_uncyclo!=[]):
                    para_uncyclo = getNextPara(fd_uncyclo)
                #    para_uncyclo = fd_uncyclo.readline()
                if(para_uncyclo != []):
                    para_wiki = (mix_paras(para_wiki,para_uncyclo))
            for i in para_wiki:
                fd_mixed.write(i)
            intial=intial+1
            para_wiki = getNextPara(fd_wiki)
        #sys.exit(0)
        #print uncyclo_dir+file.replace('wiki','uncyclopedia')
        fd_wiki.close()
        fd_mixed.close()
        fd_uncyclo.close()
    except IOError:
        print "File Not Found:",file

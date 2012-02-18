#!/usr/bin/python
import os
import sys
import re
import random
import time
import nltk.tokenize
count = 0
wiki_dir="data/wiki/"
uncyclo_dir="data/uncyclopedia/"
target_wiki_dir="convertedData/wiki/"
target_uncyclo_dir="convertedData/uncyclopedia/"
def getNextPara(fd):
    para=[]
    line=" "
    while (line!='\n' and line != ""):
        line=fd.readline()
        para.append(line)
    return para
#Decides if  the para is suitable for change
def isSuitableForChange(para):
    if len(para)<2:
        return 0
    regex_content = re.compile("\s*\*")
    for line in para:
        if regex_content.search(line)!=None:
            return 0
    return 1

def convert_para(para):
    para_string=""
    for i in para:
        para_string=para_string+" "+i.strip()
    # no remove all '\n' 
    #para_string.replace("\n","")
    para_string=para_string+"\n"+"\n"
    return para_string
def convertLynxCorpus(src_dir,src_dir1,target_dir,target_dir1):
    global count
    for file in os.listdir(src_dir):
        try:
            if(os.path.exists(target_dir1+file.replace('wiki','uncyclopedia'))):
                print target_dir1+file.replace('wiki','uncyclopedia')
                continue
            if(os.path.exists(target_dir+file)):
                print target_dir+file 
                continue
            if(count > 14000):
                break
            count=count+1
            fd_wiki = open(src_dir+file,'r')
            fd_uncyclo = open(src_dir1+file.replace('wiki','uncyclopedia'))
            fd_convert1 = open(target_dir+file,'w')
            fd_convert2 = open(target_dir1+file.replace('wiki','uncyclopedia'),'w')
            print src_dir+file,count
            para_wiki = getNextPara(fd_wiki)
            intial=0
            while para_wiki != ['']:
                para_wiki = getNextPara(fd_wiki)
                #print para_wiki
                if isSuitableForChange(para_wiki) and intial >1:
                    str=convert_para(para_wiki)
                    #print str
                    tokenizer = nltk.tokenize.PunktSentenceTokenizer()
                    lines = tokenizer.tokenize(str)
                    for i in lines:
                        fd_convert1.write(i+'\n')
                else:
                    fd_convert1.writelines(para_wiki)
                intial=intial+1
            #print uncyclo_dir+file.replace('wiki','uncyclopedia')
            para_uncyclo = getNextPara(fd_uncyclo)
            intial=0
            while para_uncyclo != ['']:
                para_uncyclo = getNextPara(fd_uncyclo)
                #print para_uncyclo
                if isSuitableForChange(para_uncyclo) and intial >1:
                    str=convert_para(para_uncyclo)
                    #print str
                    tokenizer = nltk.tokenize.PunktSentenceTokenizer()
                    lines = tokenizer.tokenize(str)
                    for i in lines:
                        fd_convert2.write(i+'\n')
                else:
                    fd_convert2.writelines(para_uncyclo)
                intial=intial+1
            

            fd_wiki.close()
            fd_uncyclo.close()
            fd_convert2.close()
            fd_convert1.close()

        except IOError:
            print "File Not Found:",file
count = 0
convertLynxCorpus(wiki_dir,uncyclo_dir,target_wiki_dir,target_uncyclo_dir)
#count = 0
#convertLynxCorpus(uncyclo_dir,target_uncyclo_dir)

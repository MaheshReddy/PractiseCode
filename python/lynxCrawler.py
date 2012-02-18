#/usr/bin/python
import os
import sys


lynx_commad="lynx -crawl -traversal -dump "
wiki_base_url="http://en.wikipedia.org/wiki/"
uncyclopedia_base_url="http://uncyclopedia.wikia.com/wiki/"

wiki_base_dir = "data/wiki"
uncyclopedia_base_dir = "data/uncyclopedia"


def executeLynx(keyword,type):
    command=""
    file_name= type+"_"+keyword+".txt"
    if type == "wiki":
        command="cd %s;"%(wiki_base_dir)+lynx_commad+wiki_base_url+keyword+" > "+ file_name +" ; if [ $? != 0 ] ; then rm %s; fi;"%(file_name)
    if type == "uncyclopedia":
        command="cd %s;"%(uncyclopedia_base_dir)+lynx_commad+uncyclopedia_base_url+keyword+" > "+ file_name +" ; if [ $? != 0 ] ; then rm %s; fi;"%(file_name)
    os.system(command)




fd = open("uncyclopedia_titles.txt",'r')
lines = fd.readlines()
for i in lines:
    print i
    executeLynx(i.strip(),"wiki")
    executeLynx(i.strip(),"uncyclopedia")
    #sys.exit(0)

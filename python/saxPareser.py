#!/usr/bin/python
import sys

from xml.sax import make_parser, handler
import pickle
import re

output = open('uncyclopedia_titles.txt','a')
title_list=[]
class FancyCounter(handler.ContentHandler):

    def __init__(self):
        self.title=0
        self.buffer=""
        #self.ignore_pat="[^a-zA-Z0-9\s]"
        self.ignore_pat="[:;]"

    def startElement(self, name, attrs):
        if name == "title":
            self.title=1;
        else:
            self.title=0
            self.buffer=""

    def characters(self,data):
        if self.title:
            self.buffer+=data

    def endElement(self,name):
        global title_list
        if self.title:
            out = self.buffer.strip().encode("iso-8859-1","replace").replace(" ","_")
            #match = re.match(self.ignore_pat,out)
            #if (match == None):
            #print out
            if out.find(":") == -1:
                #print out
                output.write(out)
                output.write("\n")
            #print self.buffer
parser = make_parser()
parser.setContentHandler(FancyCounter())
parser.parse(sys.argv[1])
#print title_list
output.close()

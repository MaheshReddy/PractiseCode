#!/usr/bin/python
import nltk
import os
import shelve
from nltk import bigrams
from nltk import trigrams
labels = ['in','of','on']

def buildTrainingData(input_file,output_file): 
    fd_read = open(input_file,'r')
    fd_write = open(output_file,'w')
    lines = fd_read.readlines()
    for line in lines:
        line = line.strip()
        if line[-1] == '.': # filtering out sentences not ending with .
            words = ["[SOL]"]
            words.extend(line.split(' '));
            words.append("[EOL]")
            written_words = list(words)
            atleast_one = 1
            while(atleast_one):
                atleast_one = 0
                for label in labels:
                    try:
                        index = words.index(label)
                        words[index] = "[TOKEN]"
                        written_words[index] = "[TOKEN]"
                        written_words.append(label)
                        atleast_one = 1
                        for word in written_words:
                            if (word != "\n"):
                                fd_write.write(word+" ")
                        fd_write.write("\n")
                        written_words[index]=label
                        written_words.pop()
                    except ValueError:
                        continue
    fd_read.close()
    fd_write.close()

def buildTagsData(input_file,output_file):
  fd_read = open(input_file,'r')
  fd_write = open(output_file,'w')
  lines = fd_read.readlines()
  for line in lines:
      text=(nltk.word_tokenize(line))
      for token in nltk.pos_tag(text):
          fd_write.write(token[0]+'/'+token[1]+" ")
      fd_write.write("\n")
  fd_read.close()
  fd_write.close()

def copyAllIntoOne(dir,outputfile):
    fd_write = open(dir+outputfile,'w')
    for i in os.listdir(dir):
        fd_read = open(dir+i,'r')
        lines = fd_read.readlines()
        for line in lines:
            for word in line.split():
                fd_write.write(word+" ");
            fd_write.write("\n");
        fd_read.close()
    fd_write.close()

def buildGrams(input_file,output_file):
    fd_shelve = shelve.open(output_file)
    fd_read = open(input_file,'r')
    lines = fd_read.readlines()
    fd_read.close()
    unigram_words = []
    bigram_words = []
    trigram_words = []
    for line in lines:
        words = line.split()
        words.pop()
        unigram_words.extend(words)
        bigram_words.extend(bigrams(words))
        trigram_words.extend(trigrams(words))
    unigram_fd=nltk.FreqDist(unigram_words)
    trigram_fd=nltk.FreqDist(trigram_words)
    bigram_fd =nltk.FreqDist(bigram_words)
    #bigram_fd = nltk.ConditionalFreqDist(bigram_words)
    fd_shelve["unigram"]=unigram_fd
    fd_shelve["bigram"]=bigram_fd
    fd_shelve["trigram"]=trigram_fd
    fd_shelve.close()
    #print type(fd1)
              

data_dir = "C:\\Share\\data_stage_one\\training_set\\"
#copyAllIntoOne(data_dir,"all_in_one_original.txt")
print "Done all in one"
#buildTrainingData(data_dir+"all_in_one_original.txt",data_dir+"modified_data.txt")
print "Done modification"
buildGrams(data_dir+"modified_data.txt",data_dir+"grams")
print "Done grams"
fd_shelve= shelve.open(data_dir+"grams")
print fd_shelve["unigram"]["the"]
print fd_shelve["bigram"][("american","people")]
fd_shelve.close()
#data_dir = "/Users/mahesh/Documents/Semester2/NLP/assign1/convote_v1.1/data_stage_one/test_set/"
#copyAllIntoOne(data_dir,"all_in_one_original.txt")
#buildTrainingData(data_dir+"all_in_one_original.txt",data_dir+"modified_data.txt")
#buildTagsData(data_dir+"modified_data.txt",data_dir+"tags.txt")
#print "Done tagging"

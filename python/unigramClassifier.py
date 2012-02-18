#!/usr/bin/python

import os
import nltk.tokenize
import shelve
dirs = {"my_vandal":"diffs/my-vandal-diff-split/","pan_vandal":"diffs/pan-vandal-diff-split/","pan_non_vandal":"diffs/nonvandal-diff-split/"}
#dirs = {"my_vandal":"diffs/my-vandal-diff-split/"}

training_file_name="vandal_test_file.txt"
#training_file_name="vandal_training_file.txt"

vandal_freqdist = nltk.probability.FreqDist()
nonvandal_freqdist = nltk.probability.FreqDist()

max_files = 1000
def collectUnigramWords():
    no_vandal = 0
    no_non_vandal = 0
    for list in dirs:
        for i in range(1,5):
            print "mahesh",dirs[list]+str(i)
            dir = dirs[list]+str(i)+"/"
            for file in os.listdir(dir):
                print file
                fd = open(dir+file,'r')
                contents = fd.read()
                tokenizer = nltk.tokenize.PunktWordTokenizer()
                words = tokenizer.tokenize(contents)
                if list == 'pan_non_vandal':
                    nonvandal_freqdist.update(nltk.probability.FreqDist(words))
                    no_non_vandal = no_non_vandal +1
                    if (no_non_vandal > 1000):
                        break
                else:
                    vandal_freqdist.update(nltk.probability.FreqDist(words))
                    no_vandal = no_vandal + 1
                    if (no_vandal > 1000):
                        break
                fd.close()
def buildInputFile():
    no_vandal = 0
    no_non_vandal = 0
    for list in dirs:
        #for i in range(1,5):
        for i in ["test"]:
            print "mahesh",dirs[list]+str(i)
            dir = dirs[list]+str(i)+"/"
            for file in os.listdir(dir):
                print file
                fd = open(dir+file,'r')
                contents = fd.read()
                tokenizer = nltk.tokenize.PunktWordTokenizer()
                words = tokenizer.tokenize(contents)
                vandal_score = 1
                non_vandal_score = 1
                for word in words:
                    vandal_score = vandal_score * (vandal_freqdist.freq(word)+0.1)
                    #vandal_score = vandal_score + vandal_freqdist[word]
                    #non_vandal_score  = non_vandal_score + nonvandal_freqdist[word]
                    non_vandal_score  = non_vandal_score * (nonvandal_freqdist.freq(word)+0.1)
                fd_dump = open(training_file_name,'a')
                if list == 'pan_non_vandal':
                    fd_dump.write('1 ')
                    no_non_vandal=no_non_vandal+1
                    if (no_non_vandal > max_files):
                        break
                else:
                    fd_dump.write('-1 ')
                    no_vandal=no_vandal+1
                    if (no_vandal > max_files):
                        break
                fd_dump.write(str(1)+":"+str(vandal_score)+" ")
                fd_dump.write(str(2)+":"+str(non_vandal_score)+" ")
                fd_dump.write('\n')
                fd_dump.close()
                fd.close()

    
shelve_fd =  shelve.open('unigram_dump.db')
#collectUnigramWords()
#shelve_fd['vandal_freqdist']=vandal_freqdist
#shelve_fd['nonvandal_freqdist']=nonvandal_freqdist
vandal_freqdist=shelve_fd['vandal_freqdist']
nonvandal_freqdist=shelve_fd['nonvandal_freqdist']
#print vandal_freqdist,nonvandal_freqdist
shelve_fd.close()   
buildInputFile()

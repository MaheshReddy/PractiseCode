#!/usr/bin/python
import random
import os
import shelve
import nltk
import sys
class featureFunctions:
    def __init__(self,data_dir):
        self.data_dir=data_dir
        self.tags=[]
        self.cfd1={}
        self.fd1={}
        print "in contruction "
        #fd = open(self.data_dir+"tags.txt",'r');
        #lines = fd.readlines()
        #for line in lines:
        #    for word in line.split():
        #        self.tags.append(nltk.tag.str2tuple(word))

        #self.cfd1 = nltk.ConditionalFreqDist(self.tags)
        #self.fd1 = nltk.FreqDist(i[0] for i in self.tags)
        self.shelvefd = shelve.open(self.data_dir+"grams")
        self.unigram = self.shelvefd["unigram"]
        self.bigram = self.shelvefd["bigram"]
        self.trigram =self.shelvefd["trigram"]
        self.shelvefd.close()
        self.total_no_words = float(self.unigram["in"]) + float(self.unigram["on"]) +float(self.unigram["of"])
        #print self.tags
    def feature_random_one(self,string):
        return random.random()
    
    
    def feature_random_two(self,string):
        return random.random()
    def feature_pos_tagger_in(self,string):
        return self.feature_pos_tagger(string,"in")
    def feature_pos_tagger_on(self,string):
        return self.feature_pos_tagger(string,"on")
    def feature_pos_tagger_of(self,string):
        return self.feature_pos_tagger(string,"of")

    def feature_bigram_in(self,string):
        return self.feature_bigram(string,"in")
    def feature_bigram_on(self,string):
        return self.feature_bigram(string,"of")
    def feature_bigram_of(self,string):
        return self.feature_bigram(string,"on")
    
    def feature_unigram_in(self,string):
        return self.feature_unigram(string,"in")
    def feature_unigram_on(self,string):
        return self.feature_unigram(string,"of")
    def feature_unigram_of(self,string):
        return self.feature_unigram(string,"on")

    def feature_trigram_in(self,string):
        return self.feature_trigram(string,"in")
    def feature_trigram_on(self,string):
        return self.feature_trigram(string,"of")
    def feature_trigram_of(self,string):
        return self.feature_trigram(string,"on")

    def feature_pos_tagger(self,string,label):
        new_string = string.replace("[TOKEN]",label)
        tokens = nltk.pos_tag(nltk.word_tokenize(new_string))
        prob = 1
        for token in tokens:
            word = token[0]
            tag = token[1]
            tag_freq = 0.0001+float(self.cfd1[word][tag])
            word_freq = 0.0001+float(self.fd1[word])
            prob = prob + tag_freq / word_freq
        prob=(prob/len(tokens))
        if prob < 0.6:
            print label+">",string,new_string
        #print label+">"+str(prob)
        return (prob/len(tokens))


    def feature_bigram(self,string,label):
        string = string.replace("[TOKEN]",label)
        words = string.split()
        bigrams = nltk.bigrams(words)
        p = 1
        for (a,b) in bigrams:
            if a == label or b == label:
                if self.unigram[a] == 0:
                    print a,string
                    return 0.00001
                p = p * (self.bigram[(a,b)] / self.unigram[a])
        return p

    def feature_trigram(self,string,label):
        string = string.replace("[TOKEN]",label)
        words = string.split()
        trigrams = nltk.trigrams(words)
        p = 1
        for (a,b,c) in trigrams:
            if a == label or b == label or c == label:
                if self.bigram[(a,b)] == 0:
                    #print (a,b,c),string
                    return 0.00001
                p = p * (self.trigram[(a,b,c)] / self.bigram[(a,b)])
        return p


    def feature_unigram(self,string,label):
        return float(self.unigram[label]) / self.total_no_words

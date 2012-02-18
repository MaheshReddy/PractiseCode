import util
from featureListFunctions import * 
import os
import logging
import sys

MAX_ITERATIONS=2

class Perceptron:
  """
  Perceptron classifier.
  """
  def __init__( self, labels,train_dir,test_dir):
    logging.basicConfig(filename=train_dir+"logfile",level=logging.INFO)
    self.labels = labels
    self.weights = {}
    self.weights_sign = {}
    self.train_dir = train_dir
    self.test_dir = test_dir 
    self.featureClass = featureFunctions(train_dir)
    self.feature_list = [self.featureClass.feature_random_two,
                        #self.featureClass.feature_pos_tagger_in,
                        #self.featureClass.feature_pos_tagger_on,
                        #self.featureClass.feature_pos_tagger_of]
                         self.featureClass.feature_bigram_in,
                         self.featureClass.feature_bigram_on,
                         self.featureClass.feature_bigram_of,
                         #self.featureClass.feature_trigram_in,
                         #self.featureClass.feature_trigram_on,
                         #self.featureClass.feature_trigram_of,
                         self.featureClass.feature_unigram_of,
                         self.featureClass.feature_unigram_in,
                         self.featureClass.feature_unigram_on]
    for label in labels:
      self.weights[label] = util.Counter()
      self.weights_sign[label] = util.Counter()
      for feature in self.feature_list:
          self.weights[label][feature]=0.001; # intilize al weight with 0.1 
          if (feature.__name__).split('_')[-1] == label:
              self.weights_sign[label][feature]=1; # intilize al weight with 0.1 
          else:
              self.weights_sign[label][feature]=-1 # intilize al weight with 0.1 
    #print self.weights
    #sys.exit() 
  def train(self):
    for iteration in range(MAX_ITERATIONS):
      print "Starting iteration ", iteration, "..."
      fd_read = open(self.train_dir+"modified_data.txt",'r')
      tuples = fd_read.readlines()
      for tuple in tuples:
         feature_result = util.Counter()
         line = tuple.rsplit('.',1)[0]
         line=line+" [EOL]"
         gold_standard = tuple.rsplit('.',1)[1].split()[-1]
         gold_standard = gold_standard.strip()
         for feature in self.feature_list:
             feature_result[feature] = feature(line)
         dot_product = util.Counter()


         for label in self.labels:
             dot_product[label] = feature_result * self.weights[label]
         guess = dot_product.argMax()
         print guess,gold_standard
         #print i
         if (guess.find(gold_standard) != -1): # made the right guess
             print "hurrah got one"
         else:  # guess is wrong correct yourself ass
             #self.weights[gold_standard][0] = self.weights[gold_standard] + actual_featureresult[gold_standard]
             self.weights[gold_standard] = self.weights[gold_standard] + feature_result
             #self.weights[gold_standard][0] = self.weights[guess] - actual_featureresult[guess]
             self.weights[guess] = self.weights[guess] - feature_result
    logging.info(str(self.weights))
    print "done"
    #return

    
  def classify(self):
    """
    Classifies each datum as the label that most closely matches the prototype vector
    for that label.  See the project description for details.
    """
    success = 0
    failure = 0
    total_number_of_predicts = {}
    total_number_of_goldStandard = {}
    total_number_of_rightPredicts = {}
    for l in self.labels:
        total_number_of_predicts[l] = 1
        total_number_of_goldStandard [l]= 1
        total_number_of_rightPredicts [l] = 1

    fd_read = open(self.test_dir+"modified_data.txt",'r')
    tuples = fd_read.readlines()
    for tuple in tuples:
        feature_result = util.Counter()
        line = tuple.rsplit('.',1)[0]
        line = line+" [EOL]"
        gold_standard = tuple.rsplit('.',1)[1].split()[-1]
        gold_standard = gold_standard.strip()
        for feature in self.feature_list:
            feature_result[feature] = feature(line)
        #print feature_result
        #print self.weights
        dot_product = util.Counter()
        for label in self.labels:
           dot_product[label] = feature_result * self.weights[label]

        guess = dot_product.argMax()
        logging.info("goldStandard[%s] guess[%s]",gold_standard,guess)
        print guess,gold_standard
        total_number_of_goldStandard[gold_standard] = total_number_of_goldStandard[gold_standard]+1
        total_number_of_predicts[guess] = total_number_of_predicts[guess]+1

        if (guess == gold_standard):
            total_number_of_rightPredicts[guess]=total_number_of_rightPredicts[guess]+1
            success=success+1
        else:
            failure=failure+1
    logging.info("Success rate [%s]",success)
    logging.info("Failure rate [%s]",failure)
    precision = {}
    f_score = {}
    recall = {}
    for l in self.labels:
        print l,total_number_of_predicts[l],total_number_of_rightPredicts[l],total_number_of_goldStandard[l]
        precision[l] = float(total_number_of_rightPredicts[l]) / float(total_number_of_predicts[l])
        recall[l] = float(total_number_of_rightPredicts[l]) / float(total_number_of_goldStandard[l])
        f_score[l] = (2*precision[l] * recall[l]) / (precision[l]+recall[l])
        logging.info("[%s] Precision [%s] Recall [%s] f_score[%s]",l,precision[l],recall[l],f_score[l])

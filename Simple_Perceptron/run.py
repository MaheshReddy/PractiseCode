
from perceptron import * 
import sys
import util


train_dir = "/Users/mahesh/Documents/Semester2/NLP/assign1/convote_v1.1/data_stage_one/training_set/"
test_dir = "/Users/mahesh/Documents/Semester2/NLP/assign1/convote_v1.1/data_stage_one/test_set/"
lables = ['in','of','on']

def runClassifier():
  classifier = Perceptron(lables,train_dir,test_dir)
  print "Training..."
  classifier.train()
  print "Done Training"
  classifier.classify()

if __name__ == "__main__":
  runClassifier()

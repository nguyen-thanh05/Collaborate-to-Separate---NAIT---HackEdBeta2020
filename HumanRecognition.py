import tensorflow as tf
from tensorflow.keras import datasets, layers, models
import matplotlib.pyplot as plt

class HumanRecognition():

    #trainImages and labelledImages are list of images

    def __init__(self, trainImages, labelledImages):
        self.trainImages = trainImages
        self.labelledImages = labelledImages

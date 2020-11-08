Our idea is to use a convolutional network to help enforce social distancing. The robot has a phone, streaming live to a pi. The pi has a model installed so that it recognises if there is a person in the frame. If so, the robot will rotate such that the person is at the middle of the frame, then use an ultrasonic sensor to measure the distance to the person 1. Then it will rotate and find another person, and proceed to measure the distance to person 2. Then it calculates the distance between person 1 and person 2, if < 2m then it will pose some form of punishment (that we have not decided yet).

We had difficulties getting the neural network to function properly, so we loaded a pre-trained model from Tensorflow detection API instead (with customised layers of code to make sure it focuses on humans only). We also ran out of time so some of the features of the robots, such that the punishment and distance sensor are not available.

Demo videos are labelled: demo[#].mp4

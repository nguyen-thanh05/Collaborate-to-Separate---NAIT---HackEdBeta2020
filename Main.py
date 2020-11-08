import os
import cv2
TRAIN_IMG = []
TRAIN_POSITION = []
def main():
    readData()

def readData():
    folder = os.listdir("trainData/train-210")
    for file in folder:
        if file.endswith(".png") or file.endswith(".jpg"):
            img = cv2.imread("trainData/train-210/"+ file)
            # img = cv2.resize(img, ())
            TRAIN_IMG.append(img)
        elif file.endswith(".idl"):
            idlFile = open("trainData/train-210/"+file)
            for line in idlFile:
                lineAsList = line.split(":")
                lineAsList[1] = lineAsList[1].strip().replace("(", "").replace(")", "")

                # [xmin, ymin, xmax, ymax]. Values are int
                rectanglePosition = lineAsList[1].split(", ")
                for i, coordinate in enumerate(rectanglePosition):
                    rectanglePosition[i] = int(coordinate)
                TRAIN_POSITION.append(rectanglePosition)

if __name__ == "__main__":
    main()
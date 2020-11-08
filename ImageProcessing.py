import cv2
import numpy as np

class ImageProcessing():
    def __init__(self, width, length):
        self.camera = cv2.VideoCapture("rtsp://192.168.1.95:8080/video/h264")
        self.width = width
        self.length = length
        self.camera.set(cv2.CAP_PROP_FRAME_WIDTH, self.width)
        self.camera.set(cv2.CAP_PROF_FRAME_HEIGHT, self.length)


    def frameToNumpy(self, displayImg = False):
        ret, frame = self.camera.read()
        frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        if displayImg:
            cv2.imshow("Me diitect hoomans", frame)
            cv2.waitKey(0)

        frame = cv2.resize(frame, (self.width, self.length))
        cameraImg = []
        cameraImg.append(frame)
        cameraImg = np.array(cameraImg, np.uint8)
        self.camera.release();
        cv2.destroyAllWindows();
        return cameraImg






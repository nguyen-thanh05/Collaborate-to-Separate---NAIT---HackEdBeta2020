import cv2

camera = cv2.VideoCapture("rtsp://192.168.1.95:8080/video/h264");

camera.set(cv2.CAP_PROP_FRAME_WIDTH, 1280);
camera.set(cv2.CAP_PROF_FRAME_HEIGHT, 720);

while True:
    ret, frame = camera.read();
    frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB);
    frame = cv2.resize(frame, (1280, 720));


camera.release();
cv2.destroyAllWindows();

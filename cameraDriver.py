from ClassifyImage import *
from ImageProcessing import *
import time

def main():
    classifier = ClassifyImage('centernet_resnet50_v1_fpn_512x512_coco17_tpu-8/saved_model', 'mscoco_label_map.pbtxt')
    camera = ImageProcessing(960, 720)
    while True:
        coords = classifier.find_person(camera.frameToNumpy())
        #print(coords)
        if not coords is False:
            print(coords)
        else:
            print("nothing")
        time.sleep(2)
    self.camera.release()

if __name__ == "__main__":
    main()

import ClassifyImage
import ImageProcessing
import time

def main():
    classifer = ClassifyImage('centernet_resnet50_v1_fpn_512x512_coco17_tpu-8/saved_model/saved_model.pb', 'mscoco_labal_map.pbtxt')
    camera = ImageProcessing(960, 720)
    while True:
        coords = classifier.find_person(camera.frameToNumpy(displayImg=True))
        if coords:
            print(coords)
        time.sleep(2)

if __name__ == "__main__":
    main()

import tensorflow as tf
from object_detection.utils import *
import numpy as np

class ClassifyImage():
    def __init__(self, model_path, label_path):
        self.obj_detect = tf.saved_model.load(model_path)
        self.labels = label_map_util.create_category_index_from_labelmap(label_path, use_display_name = True)

    def find_person(self, np_image):
        img_tensor = tf.convert_to_tensor(np_image)
        img_tensor = img_tensor[tf.newaxis, ...]
        objects = self.obj_detect(img_tensor)
        num_objs = int(detections.pop('num_detections'))
        objects = {key: value[0,:numdetections].numpy() for key, value in objects.items()}
        detections['detection_classes'] = detections['detection_classes'].astype(np,int64)
        if 1 not in objects['detection_classes']:
            return False
        else:
            max_score = 0
            max_index = 0
            for i in objects['detection_classes']:
                if objects['detection_classes'][i] == 1 and objects['detection_scores'][i] >= max_score:
                    max_score = objects['detection_scores'][i]
                    max_index = i
            return objects['detection_boxes']

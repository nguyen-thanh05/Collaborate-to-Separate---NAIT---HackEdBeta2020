import tensorflow as tf
from object_detection.utils import label_map_util
from object_detection.utils import viz_utils
import numpy as np
import cv2

class ClassifyImage():
    def __init__(self, model_path, label_path):
        self.obj_detect = tf.saved_model.load(model_path)
        self.labels = label_map_util.create_category_index_from_labelmap(label_path, use_display_name = True)

    def find_person(self, np_image):
        img_tensor = tf.convert_to_tensor(np_image)
        img_tensor = img_tensor[tf.newaxis, ...]
        objects = self.obj_detect(img_tensor)
        num_objs = int(objects.pop('num_detections'))
        objects = {key: value[0,:num_objs].numpy() for key, value in objects.items()}
        objects['detection_classes'] = objects['detection_classes'].astype(np.int64)

        image_np_with_detections = np_image.copy()
        viz_utils.visualize_boxes_and_labels_on_image_array(
          image_np_with_detections,
          objects['detection_boxes'],
          objects['detection_classes'],
          objects['detection_scores'],
          self.labels,
          use_normalized_coordinates=True,
          max_boxes_to_draw=200,
          min_score_thresh=.30,
          agnostic_mode=False)

        cv2.imshow(image_np_with_detections)
        if 1 not in objects['detection_classes']:
            return False
        else:
            max_score = 0
            max_index = 0
            for i in objects['detection_classes']:
                if objects['detection_classes'][i] == 1 and objects['detection_scores'][i] >= max_score:
                    max_score = objects['detection_scores'][i]
                    max_index = i
            if (max_score >= 0.5):
                return objects['detection_boxes'][max_index]
            else:
                return False

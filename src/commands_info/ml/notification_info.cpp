/*  Copyright (C) 2014-2023 FastoGT. All right reserved.

    This file is part of FastoTV.

    FastoTV is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    FastoTV is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FastoTV. If not, see <http://www.gnu.org/licenses/>.
*/

#include <fastotv/commands_info/ml/notification_info.h>

#define ID_FIELD "id"
#define IMAGES_FIELD "images"

#define SENDER_FIELD "sender"
#define UNIQUE_COMPONENT_ID_FIELD "unique_component_id"
#define CLASS_ID_FIELD "class_id"
#define CONFIDENCE_FIELD "confidence"
#define TIMESTAMP_FIELD "timestamp"
#define OBJECT_ID_FIELD "object_id"
#define LEFT_FIELD "left"
#define TOP_FIELD "top"
#define WIDTH_FIELD "width"
#define HEIGHT_FIELD "height"

#define LAYERS_FIELD "layers"
#define LABELS_FIELD "labels"

#define LAYER_NAME_FIELD "name"
#define LAYER_SIZE_FIELD "size"
#define LAYER_TYPE_FIELD "type"
#define LAYER_DATA_FIELD "data"

#define LABEL_LABEL_FIELD "label"
#define LABEL_CLASS_ID_FIELD "class_id"
#define LABEL_PROBABILITY_FIELD "probability"
#define LABEL_ID_FIELD "id"

namespace fastotv {
namespace commands_info {
namespace ml {

namespace {
json_object* make_json_from_label(const LabelInfo& label) {
  json_object* jlabel = json_object_new_object();
  ignore_result(common::serializer::json_set_string(jlabel, LABEL_LABEL_FIELD, label.label));
  ignore_result(common::serializer::json_set_int(jlabel, LABEL_CLASS_ID_FIELD, label.class_id));
  ignore_result(common::serializer::json_set_int(jlabel, LABEL_ID_FIELD, label.label_id));
  ignore_result(common::serializer::json_set_float(jlabel, LABEL_PROBABILITY_FIELD, label.probability));
  return jlabel;
}

LabelInfo make_label_from_json(json_object* obj) {
  LabelInfo label;
  ignore_result(common::serializer::json_get_string(obj, LABEL_LABEL_FIELD, &label.label));
  int class_id = 0;
  ignore_result(common::serializer::json_get_int(obj, LABEL_CLASS_ID_FIELD, &class_id));
  label.class_id = class_id;
  int label_id = 0;
  ignore_result(common::serializer::json_get_int(obj, LABEL_ID_FIELD, &label_id));
  label.label_id = label_id;
  ignore_result(common::serializer::json_get_float(obj, LABEL_PROBABILITY_FIELD, &label.probability));
  return label;
}

json_object* make_json_from_layer(const InferLayer& layer) {
  json_object* jlayer = json_object_new_object();

  ignore_result(common::serializer::json_set_string(jlayer, LAYER_NAME_FIELD, layer.name));
  ignore_result(common::serializer::json_set_uint64(jlayer, LAYER_SIZE_FIELD, layer.size));
  ignore_result(common::serializer::json_set_int(jlayer, LAYER_TYPE_FIELD, layer.type));

  json_object* jdata = json_object_new_array();
  void* raw = layer.data.get();
  if (raw) {
    for (uint64_t i = 0; i < layer.size; ++i) {
      json_object* jvalue = nullptr;
      InferLayer::fp32_t* data = static_cast<InferLayer::fp32_t*>(raw);
      auto place = data + i;
      if (layer.type == FLOAT) {
        jvalue = json_object_new_double(*place);
      } else if (layer.type == HALF) {
        jvalue = json_object_new_double(*place);
      } else if (layer.type == INT8) {
        jvalue = json_object_new_int(*place);
      } else {
        jvalue = json_object_new_int(*place);
      }
      json_object_array_add(jdata, jvalue);
    }
  }
  ignore_result(common::serializer::json_set_array(jlayer, LAYER_DATA_FIELD, jdata));
  return jlayer;
}

InferLayer make_layer_from_json(json_object* obj) {
  InferLayer layer;
  ignore_result(common::serializer::json_get_string(obj, LAYER_NAME_FIELD, &layer.name));
  ignore_result(common::serializer::json_get_uint64(obj, LAYER_SIZE_FIELD, &layer.size));
  int type = 0;
  ignore_result(common::serializer::json_get_int(obj, LAYER_TYPE_FIELD, &type));
  layer.type = static_cast<InferDataType>(type);

  json_object* jdata = nullptr;
  size_t len = 0;
  common::Error err = common::serializer::json_get_array(obj, LAYER_DATA_FIELD, &jdata, &len);
  if (!err) {
    if (len != 0) {
      auto allocated = InferLayer::AllocateData(len);
      for (size_t i = 0; i < len; ++i) {
        json_object* jval = json_object_array_get_idx(jdata, i);
        auto start = static_cast<InferLayer::fp32_t*>(allocated.get());
        if (layer.type == FLOAT) {
          *(start + i) = json_object_get_double(jval);
        } else if (layer.type == HALF) {
          *(start + i) = json_object_get_double(jval);
        } else if (layer.type == INT8) {
          *(start + i) = json_object_get_int(jval);
        } else {
          *(start + i) = json_object_get_int(jval);
        }
      }
      layer.data = allocated;
    }
  }
  return layer;
}

json_object* make_json_from_image(const ImageBox& box) {
  json_object* jimage = json_object_new_object();

  ignore_result(common::serializer::json_set_string(jimage, SENDER_FIELD, box.sender));
  ignore_result(common::serializer::json_set_int(jimage, UNIQUE_COMPONENT_ID_FIELD, box.unique_component_id));
  ignore_result(common::serializer::json_set_int(jimage, CLASS_ID_FIELD, box.class_id));
  ignore_result(common::serializer::json_set_double(jimage, CONFIDENCE_FIELD, box.confidence));
  ignore_result(common::serializer::json_set_int(jimage, TIMESTAMP_FIELD, box.timestamp));
  ignore_result(common::serializer::json_set_uint64(jimage, OBJECT_ID_FIELD, box.object_id));
  const auto point = box.rect.origin();
  ignore_result(common::serializer::json_set_int(jimage, LEFT_FIELD, point.x()));
  ignore_result(common::serializer::json_set_int(jimage, TOP_FIELD, point.y()));
  const auto size = box.rect.size();
  ignore_result(common::serializer::json_set_int(jimage, WIDTH_FIELD, size.width()));
  ignore_result(common::serializer::json_set_int(jimage, HEIGHT_FIELD, size.height()));

  json_object* jlayers = json_object_new_array();
  for (size_t i = 0; i < box.layers.size(); ++i) {
    json_object_array_add(jlayers, make_json_from_layer(box.layers[i]));
  }
  ignore_result(common::serializer::json_set_array(jimage, LAYERS_FIELD, jlayers));

  json_object* jlabels = json_object_new_array();
  for (size_t i = 0; i < box.labels.size(); ++i) {
    json_object_array_add(jlabels, make_json_from_label(box.labels[i]));
  }
  ignore_result(common::serializer::json_set_array(jimage, LABELS_FIELD, jlabels));

  return jimage;
}

ImageBox make_image_from_json(json_object* obj) {
  ImageBox image;
  ignore_result(common::serializer::json_get_string(obj, SENDER_FIELD, &image.sender));
  ignore_result(common::serializer::json_get_int(obj, UNIQUE_COMPONENT_ID_FIELD, &image.unique_component_id));
  ignore_result(common::serializer::json_get_int(obj, CLASS_ID_FIELD, &image.class_id));
  ignore_result(common::serializer::json_get_float(obj, CONFIDENCE_FIELD, &image.confidence));
  ignore_result(common::serializer::json_get_uint64(obj, OBJECT_ID_FIELD, &image.object_id));
  ignore_result(common::serializer::json_get_int64(obj, TIMESTAMP_FIELD, &image.timestamp));

  int x;
  common::Error err = common::serializer::json_get_int(obj, LEFT_FIELD, &x);
  if (!err) {
    image.rect.set_x(x);
  }

  int y;
  err = common::serializer::json_get_int(obj, TOP_FIELD, &y);
  if (!err) {
    image.rect.set_y(y);
  }

  int width;
  err = common::serializer::json_get_int(obj, WIDTH_FIELD, &width);
  if (!err) {
    image.rect.set_width(width);
  }

  int height;
  err = common::serializer::json_get_int(obj, HEIGHT_FIELD, &height);
  if (!err) {
    image.rect.set_height(height);
  }

  json_object* jlayers = nullptr;
  size_t len = 0;
  err = common::serializer::json_get_array(obj, LAYERS_FIELD, &jlayers, &len);
  if (!err) {
    for (size_t i = 0; i < len; ++i) {
      json_object* jlayer = json_object_array_get_idx(jlayers, i);
      image.layers.push_back(make_layer_from_json(jlayer));
    }
  }

  json_object* jlabels = nullptr;
  err = common::serializer::json_get_array(obj, LABELS_FIELD, &jlabels, &len);
  if (!err) {
    for (size_t i = 0; i < len; ++i) {
      json_object* jlabel = json_object_array_get_idx(jlabels, i);
      image.labels.push_back(make_label_from_json(jlabel));
    }
  }

  return image;
}
}  // namespace

NotificationInfo::NotificationInfo() : sid_(), images_() {}

NotificationInfo::NotificationInfo(const stream_id_t& sid, const images_t& images) : sid_(sid), images_(images) {}

fastotv::stream_id_t NotificationInfo::GetStreamID() const {
  return sid_;
}

void NotificationInfo::SetStreamID(const fastotv::stream_id_t& sid) {
  sid_ = sid;
}

NotificationInfo::images_t NotificationInfo::GetImages() const {
  return images_;
}

void NotificationInfo::SetImages(const images_t& images) {
  images_ = images;
}

void NotificationInfo::AddImage(const ImageBox& image) {
  images_.push_back(image);
}

void NotificationInfo::ClearImages() {
  images_.clear();
}

common::Error NotificationInfo::SerializeFields(json_object* deserialized) const {
  json_object* jimages = json_object_new_array_ext(images_.size());
  for (const auto& image : images_) {
    json_object* jimage = make_json_from_image(image);
    json_object_array_add(jimages, jimage);
  }
  ignore_result(SetStringField(deserialized, ID_FIELD, sid_));
  ignore_result(SetArrayField(deserialized, IMAGES_FIELD, jimages));
  return common::Error();
}

common::Error NotificationInfo::DoDeSerialize(json_object* serialized) {
  std::string id;
  common::Error err = GetStringField(serialized, ID_FIELD, &id);
  if (err) {
    return err;
  }

  json_object* jimages;
  size_t len;
  err = GetArrayField(serialized, IMAGES_FIELD, &jimages, &len);
  if (err) {
    return err;
  }

  images_t images;
  for (size_t i = 0; i < len; ++i) {
    json_object* jimage = json_object_array_get_idx(jimages, i);
    images.push_back(make_image_from_json(jimage));
  }

  *this = NotificationInfo(id, images);
  return common::Error();
}

bool NotificationInfo::Equals(const NotificationInfo& norification) const {
  return sid_ == norification.sid_ && images_ == norification.images_;
}

}  // namespace ml
}  // namespace commands_info
}  // namespace fastotv

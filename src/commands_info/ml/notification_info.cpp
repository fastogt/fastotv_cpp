/*  Copyright (C) 2014-2021 FastoGT. All right reserved.

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

#include <string>  // for string

#define ID_FIELD "id"
#define IMAGES_FIELD "images"

#define UNIQUE_COMPONENT_ID_FIELD "unique_component_id"
#define CLASS_ID_FIELD "class_id"
#define CONFIDENCE_FIELD "confidence"
#define OBJECT_ID_FIELD "object_id"
#define LEFT_FIELD "left"
#define TOP_FIELD "top"
#define WIDTH_FIELD "width"
#define HEIGHT_FIELD "height"

namespace fastotv {
namespace commands_info {
namespace ml {

namespace {
json_object* make_json_from_image(const ImageBox& box) {
  json_object* jimage = json_object_new_object();

  ignore_result(common::serializer::json_set_int(jimage, UNIQUE_COMPONENT_ID_FIELD, box.unique_component_id));
  ignore_result(common::serializer::json_set_int(jimage, CLASS_ID_FIELD, box.class_id));
  ignore_result(common::serializer::json_set_double(jimage, CONFIDENCE_FIELD, box.confidence));
  ignore_result(common::serializer::json_set_int64(jimage, OBJECT_ID_FIELD, box.object_id));
  const auto point = box.rect.origin();
  ignore_result(common::serializer::json_set_int(jimage, LEFT_FIELD, point.x()));
  ignore_result(common::serializer::json_set_int(jimage, TOP_FIELD, point.y()));
  const auto size = box.rect.size();
  ignore_result(common::serializer::json_set_int(jimage, WIDTH_FIELD, size.width()));
  ignore_result(common::serializer::json_set_int(jimage, HEIGHT_FIELD, size.height()));

  return jimage;
}

ImageBox make_image_from_json(json_object* obj) {
  ImageBox image;
  ignore_result(common::serializer::json_get_int(obj, UNIQUE_COMPONENT_ID_FIELD, &image.unique_component_id));
  ignore_result(common::serializer::json_get_int(obj, CLASS_ID_FIELD, &image.class_id));
  ignore_result(common::serializer::json_get_float(obj, CONFIDENCE_FIELD, &image.confidence));
  ignore_result(common::serializer::json_get_uint64(obj, OBJECT_ID_FIELD, &image.object_id));

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
  for (const auto image : images_) {
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

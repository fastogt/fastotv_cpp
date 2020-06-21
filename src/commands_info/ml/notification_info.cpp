/*  Copyright (C) 2014-2020 FastoGT. All right reserved.

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

#define CLASS_ID_FIELD "class_id"
#define CONFIDENCE_FIELD "confidence"
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

  json_object_object_add(jimage, CLASS_ID_FIELD, json_object_new_int(box.class_id));
  json_object_object_add(jimage, CONFIDENCE_FIELD, json_object_new_double(box.confidence));
  json_object_object_add(jimage, LEFT_FIELD, json_object_new_int(box.start.x));
  json_object_object_add(jimage, TOP_FIELD, json_object_new_int(box.start.y));
  json_object_object_add(jimage, WIDTH_FIELD, json_object_new_int(box.size.width()));
  json_object_object_add(jimage, HEIGHT_FIELD, json_object_new_int(box.size.height()));

  return jimage;
}

ImageBox make_image_from_json(json_object* obj) {
  ImageBox image;
  json_object* jlabel = nullptr;
  json_bool jlabel_exists = json_object_object_get_ex(obj, CLASS_ID_FIELD, &jlabel);
  if (jlabel_exists) {
    image.class_id = json_object_get_int(jlabel);
  }

  json_object* jprob = nullptr;
  json_bool jprob_exists = json_object_object_get_ex(obj, CONFIDENCE_FIELD, &jprob);
  if (jprob_exists) {
    image.confidence = json_object_get_double(jprob);
  }

  json_object* jx = nullptr;
  json_bool jx_exists = json_object_object_get_ex(obj, LEFT_FIELD, &jx);
  if (jx_exists) {
    image.start.x = json_object_get_int(jx);
  }

  json_object* jy = nullptr;
  json_bool jy_exists = json_object_object_get_ex(obj, TOP_FIELD, &jy);
  if (jy_exists) {
    image.start.y = json_object_get_int(jy);
  }

  json_object* jwidth = nullptr;
  json_bool jwidth_exists = json_object_object_get_ex(obj, WIDTH_FIELD, &jwidth);
  if (jwidth_exists) {
    image.size.set_width(json_object_get_int(jwidth));
  }

  json_object* jheight = nullptr;
  json_bool jheight_exists = json_object_object_get_ex(obj, HEIGHT_FIELD, &jheight);
  if (jheight_exists) {
    image.size.set_height(json_object_get_int(jheight));
  }

  return image;
}
}  // namespace

NotificationInfo::NotificationInfo() : sid_(), images_() {}

NotificationInfo::NotificationInfo(const stream_id_t& sid, const images_t& images) : sid_(sid), images_(images) {}

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
  json_object* jimages = json_object_new_array();
  for (const auto image : images_) {
    json_object* jimage = make_json_from_image(image);
    json_object_array_add(jimages, jimage);
  }
  json_object_object_add(deserialized, ID_FIELD, json_object_new_string(sid_.c_str()));
  json_object_object_add(deserialized, IMAGES_FIELD, jimages);
  return common::Error();
}

common::Error NotificationInfo::DoDeSerialize(json_object* serialized) {
  json_object* jid = nullptr;
  json_bool jid_exists = json_object_object_get_ex(serialized, ID_FIELD, &jid);
  if (!jid_exists) {
    return common::make_error_inval();
  }

  json_object* jimages = nullptr;
  json_bool jimages_exists = json_object_object_get_ex(serialized, IMAGES_FIELD, &jimages);
  if (!jimages_exists) {
    return common::make_error_inval();
  }

  images_t iamges;
  size_t len = json_object_array_length(jimages);
  for (size_t i = 0; i < len; ++i) {
    json_object* jimage = json_object_array_get_idx(jimages, i);
    iamges.push_back(make_image_from_json(jimage));
  }

  NotificationInfo ainf(json_object_get_string(jid), iamges);
  *this = ainf;
  return common::Error();
}

bool NotificationInfo::Equals(const NotificationInfo& auth) const {
  return images_ == auth.images_;
}

}  // namespace ml
}  // namespace commands_info
}  // namespace fastotv

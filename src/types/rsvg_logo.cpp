/*  Copyright (C) 2014-2021 FastoGT. All right reserved.
    This file is part of fastocloud.
    fastocloud is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    fastocloud is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with fastocloud.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <fastotv/types/rsvg_logo.h>

#include <fastotv/types/utils.h>

#define LOGO_PATH_FIELD "path"
#define LOGO_POSITION_FIELD "position"
#define LOGO_SIZE_FIELD "size"

namespace fastotv {

RSVGLogo::RSVGLogo() : RSVGLogo(url_t(), common::draw::Point()) {}

RSVGLogo::RSVGLogo(const url_t& path, const common::draw::Point& position)
    : path_(path), position_(position), size_() {}

bool RSVGLogo::Equals(const RSVGLogo& inf) const {
  return path_ == inf.path_;
}

RSVGLogo::url_t RSVGLogo::GetPath() const {
  return path_;
}

void RSVGLogo::SetPath(const url_t& path) {
  path_ = path;
}

common::draw::Point RSVGLogo::GetPosition() const {
  return position_;
}

void RSVGLogo::SetPosition(const common::draw::Point& position) {
  position_ = position;
}

RSVGLogo::image_size_t RSVGLogo::GetSize() const {
  return size_;
}

void RSVGLogo::SetSize(const image_size_t& size) {
  size_ = size;
}

common::Optional<RSVGLogo> RSVGLogo::Make(common::HashValue* hash) {
  if (!hash) {
    return common::Optional<RSVGLogo>();
  }

  RSVGLogo res;
  common::Value* logo_path_field = hash->Find(LOGO_PATH_FIELD);
  std::string logo_path;
  if (logo_path_field && logo_path_field->GetAsBasicString(&logo_path)) {
    res.SetPath(url_t(logo_path));
  }

  common::Value* logo_pos_field = hash->Find(LOGO_POSITION_FIELD);
  common::HashValue* point_hash = nullptr;
  if (logo_pos_field && logo_pos_field->GetAsHash(&point_hash)) {
    auto point = MakePoint(point_hash);
    if (point) {
      res.SetPosition(*point);
    }
  }

  common::Value* logo_size_field = hash->Find(LOGO_SIZE_FIELD);
  common::HashValue* size_hash = nullptr;
  if (logo_size_field && logo_size_field->GetAsHash(&size_hash)) {
    auto size = MakeSize(size_hash);
    if (size) {
      res.SetSize(*size);
    }
  }

  return res;
}

common::Error RSVGLogo::DoDeSerialize(json_object* serialized) {
  RSVGLogo res;
  json_object* jpath = nullptr;
  json_bool jpath_exists = json_object_object_get_ex(serialized, LOGO_PATH_FIELD, &jpath);
  if (jpath_exists) {
    res.SetPath(url_t(json_object_get_string(jpath)));
  }

  json_object* jposition = nullptr;
  json_bool jposition_exists = json_object_object_get_ex(serialized, LOGO_POSITION_FIELD, &jposition);
  if (jposition_exists) {
    auto point = MakePoint(jposition);
    if (point) {
      res.SetPosition(*point);
    }
  }

  json_object* jsize = nullptr;
  json_bool jsize_exists = json_object_object_get_ex(serialized, LOGO_SIZE_FIELD, &jsize);
  if (jsize_exists) {
    auto sz = MakeSize(jsize);
    if (sz) {
      res.SetSize(*sz);
    }
  }

  *this = res;
  return common::Error();
}

common::Error RSVGLogo::SerializeFields(json_object* out) const {
  const std::string logo_path = path_.spec();
  ignore_result(SetStringField(out, LOGO_PATH_FIELD, logo_path));
  ignore_result(SetObjectField(out, LOGO_POSITION_FIELD, MakeJson(position_)));
  if (size_) {
    ignore_result(SetObjectField(out, LOGO_SIZE_FIELD, MakeJson(*size_)));
  }

  return common::Error();
}

}  // namespace fastotv

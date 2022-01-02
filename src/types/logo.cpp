/*  Copyright (C) 2014-2022 FastoGT. All right reserved.
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

#include <fastotv/types/logo.h>

#include <fastotv/types/utils.h>

#define LOGO_PATH_FIELD "path"
#define LOGO_POSITION_FIELD "position"
#define LOGO_ALPHA_FIELD "alpha"
#define LOGO_SIZE_FIELD "size"

namespace fastotv {

Logo::Logo() : Logo(url_t(), common::draw::Point(), alpha_t()) {}

Logo::Logo(const url_t& path, const common::draw::Point& position, alpha_t alpha)
    : path_(path), position_(position), size_(), alpha_(alpha) {}

bool Logo::Equals(const Logo& inf) const {
  return path_ == inf.path_;
}

Logo::url_t Logo::GetPath() const {
  return path_;
}

void Logo::SetPath(const url_t& path) {
  path_ = path;
}

common::draw::Point Logo::GetPosition() const {
  return position_;
}

void Logo::SetPosition(const common::draw::Point& position) {
  position_ = position;
}

Logo::image_size_t Logo::GetSize() const {
  return size_;
}

void Logo::SetSize(const image_size_t& size) {
  size_ = size;
}

Logo::alpha_t Logo::GetAlpha() const {
  return alpha_;
}

void Logo::SetAlpha(alpha_t alpha) {
  alpha_ = alpha;
}

common::Optional<Logo> Logo::Make(common::HashValue* hash) {
  if (!hash) {
    return common::Optional<Logo>();
  }

  Logo res;
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

  common::Value* alpha_field = hash->Find(LOGO_ALPHA_FIELD);
  double alpha;
  if (alpha_field && alpha_field->GetAsDouble(&alpha)) {
    res.SetAlpha(alpha);
  }
  return res;
}

common::Error Logo::DoDeSerialize(json_object* serialized) {
  Logo res;
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

  json_object* jalpha = nullptr;
  json_bool jalpha_exists = json_object_object_get_ex(serialized, LOGO_ALPHA_FIELD, &jalpha);
  if (jalpha_exists) {
    res.SetAlpha(json_object_get_double(jalpha));
  }

  *this = res;
  return common::Error();
}

common::Error Logo::SerializeFields(json_object* out) const {
  const std::string logo_path = path_.spec();
  ignore_result(SetStringField(out, LOGO_PATH_FIELD, logo_path));
  ignore_result(SetObjectField(out, LOGO_POSITION_FIELD, MakeJson(position_)));
  if (size_) {
    ignore_result(SetObjectField(out, LOGO_SIZE_FIELD, MakeJson(*size_)));
  }
  ignore_result(SetDoubleField(out, LOGO_ALPHA_FIELD, GetAlpha()));

  return common::Error();
}

}  // namespace fastotv

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

#include <fastotv/commands_info/content_request_info.h>

#include <string>  // for string

#define TITLE_FIELD "title"
#define CONTENT_TYPE_FIELD "type"

namespace fastotv {
namespace commands_info {

ContentRequestInfo::ContentRequestInfo() : text_(), type_(LIVE) {}

ContentRequestInfo::ContentRequestInfo(const std::string& text, ContentType type) : text_(text), type_(type) {}

common::Error ContentRequestInfo::SerializeFields(json_object* deserialized) const {
  json_object_object_add(deserialized, TITLE_FIELD, json_object_new_string(text_.c_str()));
  json_object_object_add(deserialized, CONTENT_TYPE_FIELD, json_object_new_int(type_));
  return common::Error();
}

common::Error ContentRequestInfo::DoDeSerialize(json_object* serialized) {
  json_object* jtext = nullptr;
  json_bool jtext_exists = json_object_object_get_ex(serialized, TITLE_FIELD, &jtext);
  if (!jtext_exists) {
    return common::make_error_inval();
  }

  ContentType type = LIVE;
  json_object* jtype = nullptr;
  json_bool jtype_exists = json_object_object_get_ex(serialized, CONTENT_TYPE_FIELD, &jtype);
  if (jtype_exists) {
    type = static_cast<ContentType>(json_object_get_int(jtype));
  }

  ContentRequestInfo ainf(json_object_get_string(jtext), type);
  *this = ainf;
  return common::Error();
}

std::string ContentRequestInfo::GetText() const {
  return text_;
}

void ContentRequestInfo::SetText(const std::string& text) {
  text_ = text;
}

ContentRequestInfo::ContentType ContentRequestInfo::GetType() const {
  return type_;
}

void ContentRequestInfo::SetType(ContentType type) {
  type_ = type;
}

bool ContentRequestInfo::Equals(const ContentRequestInfo& auth) const {
  return text_ == auth.text_ && type_ == auth.type_;
}

}  // namespace commands_info
}  // namespace fastotv

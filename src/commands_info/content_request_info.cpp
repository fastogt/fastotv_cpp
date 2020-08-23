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
#define REQUEST_STATUS_FIELD "status"

#define ID_FIELD "id"

namespace fastotv {
namespace commands_info {

CreateContentRequestInfo::CreateContentRequestInfo() : CreateContentRequestInfo(std::string(), LIVE, NEW) {}

CreateContentRequestInfo::CreateContentRequestInfo(const std::string& text, ContentType type, RequestStatus status)
    : text_(text), type_(type), status_(status) {}

common::Error CreateContentRequestInfo::SerializeFields(json_object* deserialized) const {
  json_object_object_add(deserialized, TITLE_FIELD, json_object_new_string(text_.c_str()));
  json_object_object_add(deserialized, CONTENT_TYPE_FIELD, json_object_new_int(type_));
  json_object_object_add(deserialized, REQUEST_STATUS_FIELD, json_object_new_int(status_));
  return common::Error();
}

common::Error CreateContentRequestInfo::DoDeSerialize(json_object* serialized) {
  CreateContentRequestInfo ainf;
  json_object* jtext = nullptr;
  json_bool jtext_exists = json_object_object_get_ex(serialized, TITLE_FIELD, &jtext);
  if (!jtext_exists) {
    return common::make_error_inval();
  }
  ainf.text_ = json_object_get_string(jtext);

  json_object* jtype = nullptr;
  json_bool jtype_exists = json_object_object_get_ex(serialized, CONTENT_TYPE_FIELD, &jtype);
  if (!jtype_exists) {
    return common::make_error_inval();
  }

  ainf.type_ = static_cast<ContentType>(json_object_get_int(jtype));
  json_object* jstatus = nullptr;
  json_bool jstatus_exists = json_object_object_get_ex(serialized, REQUEST_STATUS_FIELD, &jstatus);
  if (!jstatus_exists) {
    return common::make_error_inval();
  }

  ainf.status_ = static_cast<RequestStatus>(json_object_get_int(jstatus));
  *this = ainf;
  return common::Error();
}

std::string CreateContentRequestInfo::GetText() const {
  return text_;
}

void CreateContentRequestInfo::SetText(const std::string& text) {
  text_ = text;
}

CreateContentRequestInfo::ContentType CreateContentRequestInfo::GetType() const {
  return type_;
}

void CreateContentRequestInfo::SetType(ContentType type) {
  type_ = type;
}

CreateContentRequestInfo::RequestStatus CreateContentRequestInfo::GetStatus() const {
  return status_;
}

void CreateContentRequestInfo::SetStatus(RequestStatus status) {
  status_ = status;
}

bool CreateContentRequestInfo::Equals(const CreateContentRequestInfo& auth) const {
  return text_ == auth.text_ && type_ == auth.type_ && status_ == auth.status_;
}

ContentRequestInfo::ContentRequestInfo() : base_class(), rid_(invalid_stream_id) {}

ContentRequestInfo::ContentRequestInfo(const content_request_id_t& rid,
                                       const std::string& text,
                                       ContentType type,
                                       RequestStatus status)
    : base_class(text, type, status), rid_(rid) {}

bool ContentRequestInfo::IsValid() const {
  return rid_ != invalid_stream_id;
}

common::Error ContentRequestInfo::SerializeFields(json_object* deserialized) const {
  if (!IsValid()) {
    return common::make_error_inval();
  }

  json_object_object_add(deserialized, ID_FIELD, json_object_new_string(rid_.c_str()));
  return base_class::SerializeFields(deserialized);
}

common::Error ContentRequestInfo::DoDeSerialize(json_object* serialized) {
  ContentRequestInfo inf;
  common::Error err = inf.base_class::DoDeSerialize(serialized);
  if (err) {
    return err;
  }

  json_object* jrid = nullptr;
  json_bool jrid_exists = json_object_object_get_ex(serialized, ID_FIELD, &jrid);
  if (!jrid_exists) {
    return common::make_error_inval();
  }

  inf.rid_ = json_object_get_string(jrid);
  *this = inf;
  return common::Error();
}

bool ContentRequestInfo::Equals(const ContentRequestInfo& auth) const {
  return base_class::Equals(auth) && rid_ == auth.rid_;
}

}  // namespace commands_info
}  // namespace fastotv

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
  ignore_result(SetStringField(deserialized, TITLE_FIELD, text_));
  ignore_result(SetEnumField(deserialized, CONTENT_TYPE_FIELD, type_));
  ignore_result(SetEnumField(deserialized, REQUEST_STATUS_FIELD, status_));
  return common::Error();
}

common::Error CreateContentRequestInfo::DoDeSerialize(json_object* serialized) {
  std::string text;
  common::Error err = GetStringField(serialized, TITLE_FIELD, &text);
  if (err) {
    return err;
  }

  ContentType type;
  err = GetEnumField(serialized, CONTENT_TYPE_FIELD, &type);
  if (err) {
    return err;
  }

  RequestStatus status;
  err = GetEnumField(serialized, REQUEST_STATUS_FIELD, &status);
  if (err) {
    return err;
  }

  *this = CreateContentRequestInfo(text, type, status);
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

ContentRequestInfo::ContentRequestInfo() : base_class(), rid_(kInvalidStreamId) {}

ContentRequestInfo::ContentRequestInfo(const content_request_id_t& rid,
                                       const std::string& text,
                                       ContentType type,
                                       RequestStatus status)
    : base_class(text, type, status), rid_(rid) {}

bool ContentRequestInfo::IsValid() const {
  return rid_ != kInvalidStreamId;
}

common::Error ContentRequestInfo::SerializeFields(json_object* deserialized) const {
  if (!IsValid()) {
    return common::make_error_inval();
  }

  ignore_result(SetStringField(deserialized, ID_FIELD, rid_));
  return base_class::SerializeFields(deserialized);
}

common::Error ContentRequestInfo::DoDeSerialize(json_object* serialized) {
  ContentRequestInfo inf;
  common::Error err = inf.base_class::DoDeSerialize(serialized);
  if (err) {
    return err;
  }

  std::string rid;
  err = GetStringField(serialized, ID_FIELD, &rid);
  if (err) {
    return err;
  }

  inf.rid_ = rid;
  *this = inf;
  return common::Error();
}

bool ContentRequestInfo::Equals(const ContentRequestInfo& auth) const {
  return base_class::Equals(auth) && rid_ == auth.rid_;
}

}  // namespace commands_info
}  // namespace fastotv

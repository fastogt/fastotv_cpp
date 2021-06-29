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

#include <fastotv/types/input_url.h>

#define ID_FIELD "id"
#define URI_FIELD "uri"

namespace fastotv {

InputUrl::InputUrl() : InputUrl(0, url_t()) {}

InputUrl::InputUrl(uri_id_t id, const url_t& input) : base_class(), id_(id), url_(input) {}

bool InputUrl::IsValid() const {
  return url_.is_valid();
}

InputUrl::uri_id_t InputUrl::GetID() const {
  return id_;
}

void InputUrl::SetID(uri_id_t id) {
  id_ = id;
}

InputUrl::url_t InputUrl::GetUrl() const {
  return url_;
}

void InputUrl::SetUrl(const url_t& uri) {
  url_ = uri;
}

bool InputUrl::Equals(const InputUrl& inf) const {
  return id_ == inf.id_ && url_ == inf.url_;
}

common::Optional<InputUrl> InputUrl::Make(common::HashValue* hash) {
  if (!hash) {
    return common::Optional<InputUrl>();
  }

  std::string url_str;
  common::Value* url_str_field = hash->Find(URI_FIELD);
  if (!url_str_field || !url_str_field->GetAsBasicString(&url_str)) {
    return common::Optional<InputUrl>();
  }

  url_t uri(url_str);
  if (!uri.is_valid()) {
    return common::Optional<InputUrl>();
  }

  common::Value* input_id_field = hash->Find(ID_FIELD);
  int64_t uid;
  if (!input_id_field || !input_id_field->GetAsInteger64(&uid)) {
    return common::Optional<InputUrl>();
  }

  InputUrl url;
  url.SetUrl(uri);
  url.SetID(uid);
  return common::Optional<InputUrl>(url);
}

common::Error InputUrl::DoDeSerialize(json_object* serialized) {
  std::string uri;
  common::Error err = GetStringField(serialized, URI_FIELD, &uri);
  if (err) {
    return err;
  }

  int id;
  err = GetIntField(serialized, ID_FIELD, &id);
  if (err) {
    return err;
  }

  *this = InputUrl(id, url_t(uri));
  return common::Error();
}

common::Error InputUrl::SerializeFields(json_object* out) const {
  if (!IsValid()) {
    return common::make_error_inval();
  }

  ignore_result(SetInt64Field(out, ID_FIELD, GetID()));
  const std::string url_str = url_.spec();
  ignore_result(SetStringField(out, URI_FIELD, url_str));
  return common::Error();
}

}  // namespace fastotv

/*  Copyright (C) 2014-2020 FastoGT. All right reserved.
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

#include <fastotv/types/output_url.h>

#define ID_FIELD "id"
#define URI_FIELD "uri"

namespace fastotv {

OutputUrl::OutputUrl() : OutputUrl(0, url_t()) {}

OutputUrl::OutputUrl(uri_id_t id, const url_t& output) : base_class(), id_(id), url_(output) {}

bool OutputUrl::IsValid() const {
  return url_.is_valid();
}

OutputUrl::uri_id_t OutputUrl::GetID() const {
  return id_;
}

void OutputUrl::SetID(uri_id_t id) {
  id_ = id;
}

OutputUrl::url_t OutputUrl::GetUrl() const {
  return url_;
}

void OutputUrl::SetUrl(const url_t& uri) {
  url_ = uri;
}

bool OutputUrl::Equals(const OutputUrl& inf) const {
  return inf.id_ == id_ && inf.url_ == url_;
}

common::Optional<OutputUrl> OutputUrl::Make(common::HashValue* hash) {
  if (!hash) {
    return common::Optional<OutputUrl>();
  }

  std::string url_str;
  common::Value* url_str_field = hash->Find(URI_FIELD);
  if (!url_str_field || !url_str_field->GetAsBasicString(&url_str)) {
    return common::Optional<OutputUrl>();
  }
  url_t uri(url_str);
  if (!uri.is_valid()) {
    return common::Optional<OutputUrl>();
  }

  common::Value* input_id_field = hash->Find(ID_FIELD);
  int uid;
  if (!input_id_field || !input_id_field->GetAsInteger(&uid)) {
    return common::Optional<OutputUrl>();
  }

  OutputUrl url;
  url.SetUrl(uri);
  url.SetID(uid);
  return url;
}

common::Error OutputUrl::DoDeSerialize(json_object* serialized) {
  json_object* juri = nullptr;
  json_bool juri_exists = json_object_object_get_ex(serialized, URI_FIELD, &juri);
  if (!juri_exists) {
    return common::make_error_inval();
  }

  json_object* jid = nullptr;
  json_bool jid_exists = json_object_object_get_ex(serialized, ID_FIELD, &jid);
  if (!jid_exists || !json_object_is_type(jid, json_type_int)) {
    return common::make_error_inval();
  }

  OutputUrl res;
  res.SetID(json_object_get_int(jid));
  url_t url(json_object_get_string(juri));
  res.SetUrl(url);

  *this = res;
  return common::Error();
}

common::Error OutputUrl::SerializeFields(json_object* out) const {
  if (!IsValid()) {
    return common::make_error_inval();
  }

  json_object_object_add(out, ID_FIELD, json_object_new_int(GetID()));
  std::string url_str = url_.spec();
  json_object_object_add(out, URI_FIELD, json_object_new_string(url_str.c_str()));
  return common::Error();
}

}  // namespace fastotv

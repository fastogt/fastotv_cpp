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

#include <fastotv/types/output_uri.h>

#define ID_FIELD "id"
#define URI_FIELD "uri"
#define HTTP_ROOT_FIELD "http_root"
#define HLS_TYPE_FIELD "hls_type"
#define SRT_MODE_FIELD "srt_mode"

namespace fastotv {

OutputUri::OutputUri() : OutputUri(0, url_t()) {}

OutputUri::OutputUri(uri_id_t id, const url_t& output)
    : base_class(), id_(id), output_(output), http_root_(), hls_type_(), srt_mode_() {}

bool OutputUri::IsValid() const {
  return output_.is_valid();
}

OutputUri::uri_id_t OutputUri::GetID() const {
  return id_;
}

void OutputUri::SetID(uri_id_t id) {
  id_ = id;
}

OutputUri::url_t OutputUri::GetOutput() const {
  return output_;
}

void OutputUri::SetOutput(const url_t& uri) {
  output_ = uri;
}

OutputUri::http_root_t OutputUri::GetHttpRoot() const {
  return http_root_;
}

void OutputUri::SetHttpRoot(const http_root_t& root) {
  http_root_ = root;
}

OutputUri::hls_t OutputUri::GetHlsType() const {
  return hls_type_;
}

void OutputUri::SetHlsType(hls_t type) {
  hls_type_ = type;
}

OutputUri::srt_mode_t OutputUri::GetSrtMode() const {
  return srt_mode_;
}

void OutputUri::SetSrtMode(srt_mode_t mode) {
  srt_mode_ = mode;
}

bool OutputUri::Equals(const OutputUri& inf) const {
  return id_ == inf.id_ && output_ == inf.output_ && http_root_ == inf.http_root_;
}

common::Optional<OutputUri> OutputUri::Make(common::HashValue* hash) {
  if (!hash) {
    return common::Optional<OutputUri>();
  }

  std::string url_str;
  common::Value* url_str_field = hash->Find(URI_FIELD);
  if (!url_str_field || !url_str_field->GetAsBasicString(&url_str)) {
    return common::Optional<OutputUri>();
  }
  url_t uri(url_str);
  if (!uri.is_valid()) {
    return common::Optional<OutputUri>();
  }

  common::Value* input_id_field = hash->Find(ID_FIELD);
  int uid;
  if (!input_id_field || !input_id_field->GetAsInteger(&uid)) {
    return common::Optional<OutputUri>();
  }

  OutputUri url;
  url.SetOutput(uri);
  url.SetID(uid);

  std::string http_root_str;
  common::Value* http_root_str_field = hash->Find(HTTP_ROOT_FIELD);
  if (http_root_str_field && http_root_str_field->GetAsBasicString(&http_root_str)) {
    const common::file_system::ascii_directory_string_path http_root(http_root_str);
    url.SetHttpRoot(http_root);
  }

  int hls_type;
  common::Value* hls_type_field = hash->Find(HLS_TYPE_FIELD);
  if (hls_type_field && hls_type_field->GetAsInteger(&hls_type)) {
    url.SetHlsType(static_cast<HlsType>(hls_type));
  }

  int srt_mode;
  common::Value* srt_mode_field = hash->Find(SRT_MODE_FIELD);
  if (srt_mode_field && srt_mode_field->GetAsInteger(&srt_mode)) {
    url.SetSrtMode(static_cast<SrtMode>(srt_mode));
  }

  return url;
}

common::Error OutputUri::DoDeSerialize(json_object* serialized) {
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

  OutputUri res;
  res.SetID(json_object_get_int(jid));
  url_t url(json_object_get_string(juri));
  res.SetOutput(url);

  json_object* jhttp_root = nullptr;
  json_bool jhttp_root_exists = json_object_object_get_ex(serialized, HTTP_ROOT_FIELD, &jhttp_root);
  if (jhttp_root_exists) {
    const char* http_root_str = json_object_get_string(jhttp_root);
    const common::file_system::ascii_directory_string_path http_root(http_root_str);
    res.SetHttpRoot(http_root);
  }

  json_object* jhls_type = nullptr;
  json_bool jhls_type_exists = json_object_object_get_ex(serialized, HLS_TYPE_FIELD, &jhls_type);
  if (jhls_type_exists) {
    res.SetHlsType(static_cast<HlsType>(json_object_get_int(jhls_type)));
  }

  json_object* jsrt_mode = nullptr;
  json_bool jsrt_mode_exists = json_object_object_get_ex(serialized, SRT_MODE_FIELD, &jsrt_mode);
  if (jsrt_mode_exists) {
    res.SetSrtMode(static_cast<SrtMode>(json_object_get_int(jsrt_mode)));
  }

  *this = res;
  return common::Error();
}

common::Error OutputUri::SerializeFields(json_object* out) const {
  if (!IsValid()) {
    return common::make_error_inval();
  }

  json_object_object_add(out, ID_FIELD, json_object_new_int(GetID()));
  std::string url_str = output_.spec();
  json_object_object_add(out, URI_FIELD, json_object_new_string(url_str.c_str()));
  auto ps = GetHttpRoot();
  if (ps) {
    const std::string http_root_str = ps->GetPath();
    json_object_object_add(out, HTTP_ROOT_FIELD, json_object_new_string(http_root_str.c_str()));
  }
  if (hls_type_) {
    json_object_object_add(out, HLS_TYPE_FIELD, json_object_new_int(*hls_type_));
  }
  if (srt_mode_) {
    json_object_object_add(out, SRT_MODE_FIELD, json_object_new_int(*srt_mode_));
  }
  return common::Error();
}

}  // namespace fastotv

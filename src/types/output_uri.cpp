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

#define HLSSINK_TYPE_FILED "hlssink_type"
#define HTTP_ROOT_FIELD "http_root"
#define HLS_TYPE_FIELD "hls_type"
#define CHUNK_DURATION_FIELD "chunk_duration"
#define PLAYLIST_ROOT_FIELD "playlist_root"
#define SRT_MODE_FIELD "srt_mode"

namespace fastotv {

OutputUri::OutputUri() : OutputUri(0, url_t()) {}

OutputUri::OutputUri(uri_id_t id, const url_t& url)
    : base_class(id, url), hlssink_type_(), http_root_(), hls_type_(), chunk_duration_(), srt_mode_() {}

bool OutputUri::IsValid() const {
  return base_class::IsValid();
}

OutputUri::hlssink_type_t OutputUri::GetHlsSinkType() const {
  return hlssink_type_;
}

void OutputUri::SetHlsSinkType(hlssink_type_t hlssink) {
  hlssink_type_ = hlssink;
}

OutputUri::http_root_t OutputUri::GetHttpRoot() const {
  return http_root_;
}

void OutputUri::SetHttpRoot(const http_root_t& root) {
  http_root_ = root;
}

OutputUri::chunk_duration_t OutputUri::GetChunkDuration() const {
  return chunk_duration_;
}

void OutputUri::SetChunkDuration(chunk_duration_t duration) {
  chunk_duration_ = duration;
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

OutputUri::playlist_root_t OutputUri::GetPlaylistRoot() const {
  return playlist_root_;
}

void OutputUri::SetPlaylistRoot(const OutputUri::playlist_root_t& playlist) {
  playlist_root_ = playlist;
}

bool OutputUri::Equals(const OutputUri& url) const {
  return base_class::Equals(url) && http_root_ == url.http_root_;
}

common::Optional<OutputUri> OutputUri::Make(common::HashValue* hash) {
  if (!hash) {
    return common::Optional<OutputUri>();
  }

  common::Optional<OutputUrl> base = base_class::Make(hash);
  if (!base) {
    return common::Optional<OutputUri>();
  }

  OutputUri url(base->GetID(), base->GetUrl());
  int hlssink2;
  common::Value* hlssink2_field = hash->Find(HLSSINK_TYPE_FILED);
  if (hlssink2_field && hlssink2_field->GetAsInteger(&hlssink2)) {
    url.SetHlsSinkType(static_cast<HlsSinkType>(hlssink2));
  }

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

  int chunk_duration;
  common::Value* chunk_duration_field = hash->Find(CHUNK_DURATION_FIELD);
  if (chunk_duration_field && chunk_duration_field->GetAsInteger(&chunk_duration)) {
    url.SetChunkDuration(chunk_duration);
  }

  std::string playlist_root;
  common::Value* playlist_field = hash->Find(PLAYLIST_ROOT_FIELD);
  if (playlist_field && playlist_field->GetAsBasicString(&playlist_root)) {
    url.SetPlaylistRoot(common::uri::GURL(playlist_root));
  }

  int srt_mode;
  common::Value* srt_mode_field = hash->Find(SRT_MODE_FIELD);
  if (srt_mode_field && srt_mode_field->GetAsInteger(&srt_mode)) {
    url.SetSrtMode(static_cast<SrtMode>(srt_mode));
  }

  return url;
}

common::Error OutputUri::DoDeSerialize(json_object* serialized) {
  OutputUri res;
  common::Error err = res.base_class::DoDeSerialize(serialized);
  if (err) {
    return err;
  }

  HlsSinkType hlssink2;
  err = GetEnumField(serialized, HLSSINK_TYPE_FILED, &hlssink2);
  if (!err) {
    res.SetHlsSinkType(hlssink2);
  }

  std::string http_root;
  err = GetStringField(serialized, HTTP_ROOT_FIELD, &http_root);
  if (!err) {
    res.SetHttpRoot(common::file_system::ascii_directory_string_path(http_root));
  }

  HlsType hls_type;
  err = GetEnumField(serialized, HLS_TYPE_FIELD, &hls_type);
  if (!err) {
    res.SetHlsType(hls_type);
  }

  int chunk_duration;
  err = GetIntField(serialized, CHUNK_DURATION_FIELD, &chunk_duration);
  if (!err) {
    res.SetChunkDuration(chunk_duration);
  }

  SrtMode srt_mode;
  err = GetEnumField(serialized, SRT_MODE_FIELD, &srt_mode);
  if (!err) {
    res.SetSrtMode(srt_mode);
  }

  *this = res;
  return common::Error();
}

common::Error OutputUri::SerializeFields(json_object* deserialized) const {
  if (!IsValid()) {
    return common::make_error_inval();
  }

  common::Error err = base_class::SerializeFields(deserialized);
  if (err) {
    return err;
  }

  if (hlssink_type_) {
    json_object_object_add(deserialized, HLSSINK_TYPE_FILED, json_object_new_int(*hlssink_type_));
  }
  auto ps = GetHttpRoot();
  if (ps) {
    const std::string http_root_str = ps->GetPath();
    json_object_object_add(deserialized, HTTP_ROOT_FIELD, json_object_new_string(http_root_str.c_str()));
  }
  if (hls_type_) {
    json_object_object_add(deserialized, HLS_TYPE_FIELD, json_object_new_int(*hls_type_));
  }
  if (chunk_duration_) {
    json_object_object_add(deserialized, CHUNK_DURATION_FIELD, json_object_new_int(*chunk_duration_));
  }
  if (playlist_root_) {
    const std::string root = playlist_root_->spec();
    json_object_object_add(deserialized, PLAYLIST_ROOT_FIELD, json_object_new_string(root.c_str()));
  }
  if (srt_mode_) {
    json_object_object_add(deserialized, SRT_MODE_FIELD, json_object_new_int(*srt_mode_));
  }
  return common::Error();
}

}  // namespace fastotv

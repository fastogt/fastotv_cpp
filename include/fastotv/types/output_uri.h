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

#pragma once

#include <common/file_system/path.h>
#include <common/serializer/json_serializer.h>
#include <common/uri/gurl.h>
#include <common/value.h>

#include <fastotv/types.h>

namespace fastotv {

class OutputUri : public common::serializer::JsonSerializer<OutputUri> {
 public:
  typedef JsonSerializer<OutputUri> base_class;
  typedef common::Optional<common::file_system::ascii_directory_string_path> http_root_t;
  enum HlsType { HLS_PULL = 0, HLS_PUSH = 1 };
  enum SrtMode { NONE = 0, CALLER = 1, LISTENER = 2, RENDEZVOUS = 3 };

  typedef fastotv::channel_id_t uri_id_t;
  typedef common::Optional<HlsType> hls_t;
  typedef common::Optional<unsigned> chunk_duration_t;
  typedef common::Optional<SrtMode> srt_mode_t;
  typedef common::uri::GURL url_t;

  OutputUri();
  explicit OutputUri(uri_id_t id, const url_t& output);

  bool IsValid() const;

  uri_id_t GetID() const;
  void SetID(uri_id_t id);

  url_t GetOutput() const;
  void SetOutput(const url_t& uri);

  http_root_t GetHttpRoot() const;
  void SetHttpRoot(const http_root_t& root);

  chunk_duration_t GetChunkDuration() const;
  void SetChunkDuration(chunk_duration_t duration);

  hls_t GetHlsType() const;
  void SetHlsType(hls_t type);

  srt_mode_t GetSrtMode() const;
  void SetSrtMode(srt_mode_t mode);

  bool Equals(const OutputUri& inf) const;

  static common::Optional<OutputUri> Make(common::HashValue* hash);

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* out) const override;

 private:
  // required
  uri_id_t id_;
  url_t output_;
  // http
  http_root_t http_root_;
  hls_t hls_type_;
  chunk_duration_t chunk_duration_;
  // srt
  srt_mode_t srt_mode_;
};

}  // namespace fastotv

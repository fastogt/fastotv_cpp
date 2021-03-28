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

#pragma once

#include <common/file_system/path.h>

#include <fastotv/types/output_url.h>
#include <fastotv/types/srt_key.h>

namespace fastotv {

class OutputUri : public OutputUrl {
 public:
  typedef OutputUrl base_class;
  typedef common::Optional<common::file_system::ascii_directory_string_path> http_root_t;
  enum HlsType { HLS_PULL = 0, HLS_PUSH = 1 };
  enum HlsSinkType { HLSSINK = 0, HLSSINK2 = 1 };
  enum SrtMode { NONE = 0, CALLER = 1, LISTENER = 2, RENDEZVOUS = 3 };

  typedef common::Optional<HlsType> hls_t;
  typedef common::Optional<common::uri::GURL> playlist_root_t;
  typedef common::Optional<unsigned> chunk_duration_t;
  typedef common::Optional<SrtMode> srt_mode_t;
  typedef common::Optional<HlsSinkType> hlssink_type_t;
  typedef common::Optional<SrtKey> srt_key_t;

  OutputUri();
  explicit OutputUri(uri_id_t id, const url_t& url);

  bool IsValid() const;

  hlssink_type_t GetHlsSinkType() const;
  void SetHlsSinkType(hlssink_type_t hlssink);

  http_root_t GetHttpRoot() const;
  void SetHttpRoot(const http_root_t& root);

  chunk_duration_t GetChunkDuration() const;
  void SetChunkDuration(chunk_duration_t duration);

  hls_t GetHlsType() const;
  void SetHlsType(hls_t type);

  srt_mode_t GetSrtMode() const;
  void SetSrtMode(srt_mode_t mode);

  srt_key_t GetSrtKey() const;
  void SetSrtKey(const srt_key_t& pass);

  playlist_root_t GetPlaylistRoot() const;
  void SetPlaylistRoot(const playlist_root_t& playlist);

  bool Equals(const OutputUri& url) const;

  static common::Optional<OutputUri> Make(common::HashValue* hash);

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* deserialized) const override;

 private:
  // http
  hlssink_type_t hlssink_type_;
  http_root_t http_root_;
  hls_t hls_type_;
  chunk_duration_t chunk_duration_;
  playlist_root_t playlist_root_;
  // srt
  srt_mode_t srt_mode_;
  srt_key_t srt_key_;
};

inline bool operator==(const OutputUri& left, const OutputUri& right) {
  return left.Equals(right);
}

inline bool operator!=(const OutputUri& x, const OutputUri& y) {
  return !(x == y);
}

}  // namespace fastotv

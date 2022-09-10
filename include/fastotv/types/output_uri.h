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

#pragma once

#include <common/file_system/path.h>
#include <fastotv/types/azure_prop.h>
#include <fastotv/types/google_prop.h>
#include <fastotv/types/kvs_prop.h>
#include <fastotv/types/output_url.h>
#include <fastotv/types/srt_key.h>
#include <fastotv/types/webrtc_prop.h>

namespace fastotv {

class OutputUri : public OutputUrl {
 public:
  typedef OutputUrl base_class;
  typedef common::Optional<common::file_system::ascii_directory_string_path> http_root_t;
  enum HlsType { HLS_PULL = 0, HLS_PUSH = 1 };
  enum HlsSinkType { HLSSINK = 0, HLSSINK2 = 1 };
  enum SrtMode { NONE = 0, CALLER = 1, LISTENER = 2, RENDEZVOUS = 3 };
  enum RtmpSinkType { RTMPSINK = 0, RTMP2SINK = 1 };

  typedef common::Optional<HlsType> hls_t;
  typedef common::Optional<common::uri::GURL> playlist_root_t;
  typedef common::Optional<unsigned> chunk_duration_t;
  typedef common::Optional<SrtMode> srt_mode_t;
  typedef common::Optional<HlsSinkType> hlssink_type_t;
  typedef common::Optional<SrtKey> srt_key_t;
  typedef common::Optional<RtmpSinkType> rtmp_type_t;
  typedef common::Optional<KVSProp> kvs_t;
  typedef common::Optional<AzureProp> azure_t;
  typedef common::Optional<GoogleProp> google_t;
  // webrtc
  typedef common::Optional<WebRTCProp> webrtc_t;
  // udp
  typedef common::Optional<std::string> multicast_iface_t;

  OutputUri();
  explicit OutputUri(uri_id_t id, const url_t& url);

  bool IsValid() const;

  bool IsHls() const;

  multicast_iface_t GetMulticastIface() const;
  void SetMulticastIface(multicast_iface_t iface);

  rtmp_type_t GetRtmpSinkType() const;
  void SetRtmpSinkType(rtmp_type_t rtmpsink);

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

  kvs_t GetKVS() const;
  void SetKVS(const kvs_t& kvs);

  azure_t GetAzure() const;
  void SetAzure(const azure_t& azure);

  google_t GetGoogle() const;
  void SetGoogle(const google_t& google);

  webrtc_t GetWebRTC() const;
  void SetWebRTC(const webrtc_t& web);

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
  // rtmp
  rtmp_type_t rtmpsink_type_;
  //
  kvs_t kvs_;
  //
  azure_t azure_;
  //
  google_t google_;
  // webrtc
  webrtc_t webrtc_;
  // udp
  multicast_iface_t iface_;
};

inline bool operator==(const OutputUri& left, const OutputUri& right) {
  return left.Equals(right);
}

inline bool operator!=(const OutputUri& x, const OutputUri& y) {
  return !(x == y);
}

}  // namespace fastotv

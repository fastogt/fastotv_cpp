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

#include <string>

#include <fastotv/types/input_url.h>
#include <fastotv/types/programme.h>
#include <fastotv/types/pyfastostream.h>
#include <fastotv/types/srt_key.h>
#include <fastotv/types/webrtc_prop.h>
#include <fastotv/types/wpe.h>

namespace fastotv {

class InputUri : public InputUrl {
 public:
  typedef InputUrl base_class;
  enum UserAgent : int { GSTREAMER = 0, VLC = 1, FFMPEG = 2, WINK = 3, CHROME = 4, MOZILLA = 5, SAFARI = 6 };
  enum SrtMode { NONE = 0, CALLER = 1, LISTENER = 2, RENDEZVOUS = 3 };
  typedef common::Optional<UserAgent> user_agent_t;
  enum RtmpSrcType { RTMPSRC = 0, RTMP2SRC = 1 };
  // optionals
  typedef common::Optional<common::uri::GURL> http_proxy_url_t;
  typedef common::Optional<PyFastoStream> stream_url_t;
  typedef common::Optional<Wpe> wpe_t;
  // udp
  typedef common::Optional<int> program_number_t;
  typedef common::Optional<std::string> multicast_iface_t;
  // srt
  typedef common::Optional<SrtKey> srt_key_t;
  typedef common::Optional<SrtMode> srt_mode_t;
  typedef common::Optional<Programme> programme_t;
  // rtmp
  typedef common::Optional<RtmpSrcType> rtmpsrc_type_t;
  // webrtc
  typedef common::Optional<WebRTCProp> webrtc_t;

  InputUri();
  explicit InputUri(uri_id_t id, const url_t& input);

  bool IsValid() const;

  user_agent_t GetUserAgent() const;
  void SetUserAgent(user_agent_t agent);

  stream_url_t GetPyFastoStream() const;
  void SetPyFastoStream(stream_url_t stream);

  http_proxy_url_t GetHttpProxyUrl() const;
  void SetHttpProxyUrl(const http_proxy_url_t& url);

  wpe_t GetWPE() const;
  void SetWPE(const wpe_t& wpe);

  program_number_t GetProgramNumber() const;
  void SetProgramNumber(program_number_t id);

  multicast_iface_t GetMulticastIface() const;
  void SetMulticastIface(multicast_iface_t iface);

  srt_mode_t GetSrtMode() const;
  void SetSrtMode(srt_mode_t mode);

  srt_key_t GetSrtKey() const;
  void SetSrtKey(const srt_key_t& pass);

  programme_t GetProgramme() const;
  void SetProgramme(const programme_t& programme);

  rtmpsrc_type_t GetRtmpSrcType() const;
  void SetRtmpSrcType(const rtmpsrc_type_t& type);

  webrtc_t GetWebRTC() const;
  void SetWebRTC(const webrtc_t& web);

  bool Equals(const InputUri& url) const;

  static common::Optional<InputUri> Make(common::HashValue* hash);

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* deserialized) const override;

 private:
  // http
  user_agent_t user_agent_;
  stream_url_t stream_url_;
  http_proxy_url_t http_proxy_url_;
  wpe_t wpe_;

  // udp
  program_number_t program_number_;
  multicast_iface_t iface_;

  // srt
  srt_mode_t srt_mode_;
  srt_key_t srt_key_;

  // programme
  programme_t programme_;

  // rtmp
  rtmpsrc_type_t rtmpsrc_type_;
  // webrtc
  webrtc_t webrtc_;
};

inline bool operator==(const InputUri& left, const InputUri& right) {
  return left.Equals(right);
}

inline bool operator!=(const InputUri& x, const InputUri& y) {
  return !(x == y);
}

}  // namespace fastotv

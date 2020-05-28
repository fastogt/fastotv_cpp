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

#include <string>

#include <common/serializer/json_serializer.h>
#include <common/uri/gurl.h>
#include <common/value.h>

#include <fastotv/types.h>
#include <fastotv/types/http_proxy.h>
#include <fastotv/types/stream_link.h>

namespace fastotv {

class InputUri : public common::serializer::JsonSerializer<InputUri> {
 public:
  typedef JsonSerializer<InputUri> base_class;
  typedef fastotv::channel_id_t uri_id_t;
  enum UserAgent : int { GSTREAMER = 0, VLC = 1, FFMPEG = 2, WINK = 3, CHROME = 4, MOZILLA = 5, SAFARI = 6 };
  typedef common::Optional<UserAgent> user_agent_t;
  // optionals
  typedef common::Optional<int> program_number_t;
  typedef common::Optional<std::string> multicast_iface_t;
  typedef common::Optional<HttpProxy> http_proxy_url_t;
  typedef common::Optional<StreamLink> stream_url_t;
  typedef common::uri::GURL url_t;

  InputUri();
  explicit InputUri(uri_id_t id, const url_t& input);

  bool IsValid() const;

  uri_id_t GetID() const;
  void SetID(uri_id_t id);

  url_t GetInput() const;
  void SetInput(const url_t& uri);

  user_agent_t GetUserAgent() const;
  void SetUserAgent(user_agent_t agent);

  stream_url_t GetStreamLink() const;
  void SetStreamLink(stream_url_t stream);

  http_proxy_url_t GetHttpProxyUrl() const;
  void SetHttpProxyUrl(const http_proxy_url_t& url);

  program_number_t GetProgramNumber() const;
  void SetProgramNumber(program_number_t id);

  multicast_iface_t GetMulticastIface() const;
  void SetMulticastIface(multicast_iface_t iface);

  bool Equals(const InputUri& inf) const;

  static common::Optional<InputUri> Make(common::HashValue* hash);

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* out) const override;

 private:
  // required
  uri_id_t id_;
  url_t input_;
  // http
  user_agent_t user_agent_;
  stream_url_t stream_url_;
  http_proxy_url_t http_proxy_url_;

  // udp
  program_number_t program_number_;
  multicast_iface_t iface_;
};

}  // namespace fastotv

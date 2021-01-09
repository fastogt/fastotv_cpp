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

#include <string>

#include <common/serializer/json_serializer.h>
#include <common/uri/gurl.h>
#include <common/value.h>

#include <fastotv/types.h>

namespace fastotv {

class StreamLink : public common::serializer::JsonSerializer<StreamLink> {
 public:
  typedef JsonSerializer<StreamLink> base_class;
  typedef common::Optional<common::uri::GURL> http_proxy_t;
  typedef common::Optional<common::uri::GURL> https_proxy_t;

  StreamLink();
  explicit StreamLink(const http_proxy_t& http, const http_proxy_t& https);

  bool IsValid() const;

  http_proxy_t GetHttp() const;
  void SetHttp(const http_proxy_t& url);

  https_proxy_t GetHttps() const;
  void SetHttps(const https_proxy_t& url);

  bool Equals(const StreamLink& url) const;

  static common::Optional<StreamLink> Make(common::HashValue* json);

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* out) const override;

 private:
  common::Optional<common::uri::GURL> http_proxy_;
  common::Optional<common::uri::GURL> https_proxy_;
};

inline bool operator==(const StreamLink& left, const StreamLink& right) {
  return left.Equals(right);
}

inline bool operator!=(const StreamLink& x, const StreamLink& y) {
  return !(x == y);
}

}  // namespace fastotv

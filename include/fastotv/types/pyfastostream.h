/*  Copyright (C) 2014-2023 FastoGT. All right reserved.
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

#include <common/serializer/json_serializer.h>
#include <common/uri/gurl.h>
#include <common/value.h>
#include <fastotv/types.h>

#include <string>

namespace fastotv {

enum QualityPrefer { QP_AUDIO = 0, QP_VIDEO = 1, QP_BOTH = 2 };

class PyFastoStream : public common::serializer::JsonSerializer<PyFastoStream> {
 public:
  typedef JsonSerializer<PyFastoStream> base_class;
  typedef common::Optional<common::uri::GURL> http_proxy_t;
  typedef common::Optional<common::uri::GURL> https_proxy_t;

  PyFastoStream();
  explicit PyFastoStream(const http_proxy_t& http, const http_proxy_t& https, QualityPrefer prefer);

  bool IsValid() const;

  http_proxy_t GetHttp() const;
  void SetHttp(const http_proxy_t& url);

  https_proxy_t GetHttps() const;
  void SetHttps(const https_proxy_t& url);

  QualityPrefer GetPrefer() const;
  void SetPrefer(QualityPrefer prefer);

  bool Equals(const PyFastoStream& url) const;

  static common::Optional<PyFastoStream> Make(common::HashValue* json);

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* out) const override;

 private:
  common::Optional<common::uri::GURL> http_proxy_;
  common::Optional<common::uri::GURL> https_proxy_;
  QualityPrefer prefer_;
};

inline bool operator==(const PyFastoStream& left, const PyFastoStream& right) {
  return left.Equals(right);
}

inline bool operator!=(const PyFastoStream& x, const PyFastoStream& y) {
  return !(x == y);
}

}  // namespace fastotv

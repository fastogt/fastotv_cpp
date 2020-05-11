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

namespace fastotv {

class HttpProxy : public common::serializer::JsonSerializer<HttpProxy> {
 public:
  typedef common::Optional<std::string> password_t;
  typedef common::Optional<std::string> user_id_t;
  typedef common::uri::GURL url_t;

  HttpProxy();
  explicit HttpProxy(const url_t& url);

  bool IsValid() const;

  bool Equals(const HttpProxy& proxy) const;

  url_t GetUrl() const;
  void SetUrl(const url_t& url);

  user_id_t GetUserID() const;
  void SetUserID(const user_id_t& sid);

  password_t GetPassword() const;
  void SetPassword(const password_t& password);

  static common::Optional<HttpProxy> Make(common::HashValue* value);

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* out) const override;

 private:
  url_t url_;
  user_id_t user_;
  password_t password_;
};

}  // namespace fastotv

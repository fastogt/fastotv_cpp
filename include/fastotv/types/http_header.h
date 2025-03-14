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
#include <common/value.h>

#include <string>

namespace fastotv {

class HttpHeader : public common::serializer::JsonSerializer<HttpHeader> {
 public:
  typedef JsonSerializer<HttpHeader> base_class;
  typedef std::string key_t;
  typedef std::string value_t;

  HttpHeader();
  explicit HttpHeader(const key_t& key, const value_t& value);

  bool IsValid() const;

  key_t GetKey() const;
  void SetKey(const key_t& key);

  value_t GetValue() const;
  void SetValue(const value_t& value);

  bool Equals(const HttpHeader& inf) const;

  static common::Optional<HttpHeader> Make(common::HashValue* json);

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* out) const override;

 private:
  // required
  key_t key_;
  value_t value_;
};

inline bool operator==(const HttpHeader& left, const HttpHeader& right) {
  return left.Equals(right);
}

inline bool operator!=(const HttpHeader& x, const HttpHeader& y) {
  return !(x == y);
}

typedef common::serializer::JsonSerializerArray<HttpHeader> HttpHeaders;

}  // namespace fastotv

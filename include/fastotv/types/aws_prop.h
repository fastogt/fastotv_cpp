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

class S3Prop : public common::serializer::JsonSerializer<S3Prop> {
 public:
  typedef JsonSerializer<S3Prop> base_class;
  typedef std::string access_key_t;
  typedef std::string secret_key_t;

  S3Prop();
  explicit S3Prop(const access_key_t& access_key, const secret_key_t& secret_key);

  bool IsValid() const;

  access_key_t GetAccessKey() const;
  void SetAccessKey(const access_key_t& key);

  secret_key_t GetSecretKey() const;
  void SetSecretKey(const secret_key_t& key);

  bool Equals(const S3Prop& key) const;

  static common::Optional<S3Prop> Make(common::HashValue* json);

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* out) const override;

 private:
  access_key_t access_key_;
  secret_key_t secret_key_;
};

inline bool operator==(const S3Prop& left, const S3Prop& right) {
  return left.Equals(right);
}

inline bool operator!=(const S3Prop& x, const S3Prop& y) {
  return !(x == y);
}

}  // namespace fastotv

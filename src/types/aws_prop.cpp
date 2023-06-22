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

#include <fastotv/types/aws_prop.h>

#define ACCESS_KEY_FIELD "access_key"
#define SECRET_KEY_FIELD "secret_key"

namespace fastotv {

S3Prop::S3Prop() : S3Prop(std::string(), std::string()) {}

S3Prop::S3Prop(const access_key_t& access_key, const secret_key_t& secret_key)
    : access_key_(access_key), secret_key_(secret_key) {}

bool S3Prop::IsValid() const {
  return !access_key_.empty() && !secret_key_.empty();
}

S3Prop::access_key_t S3Prop::GetAccessKey() const {
  return access_key_;
}

void S3Prop::SetAccessKey(const access_key_t& key) {
  access_key_ = key;
}

S3Prop::secret_key_t S3Prop::GetSecretKey() const {
  return secret_key_;
}

void S3Prop::SetSecretKey(const secret_key_t& key) {
  secret_key_ = key;
}

bool S3Prop::Equals(const S3Prop& key) const {
  return access_key_ == key.access_key_ && secret_key_ == key.secret_key_;
}

common::Optional<S3Prop> S3Prop::Make(common::HashValue* json) {
  if (!json) {
    return common::Optional<S3Prop>();
  }

  S3Prop res;
  common::Value* acc_field = json->Find(ACCESS_KEY_FIELD);
  std::string acc;
  if (!acc_field || !acc_field->GetAsBasicString(&acc)) {
    return common::Optional<S3Prop>();
  }
  res.access_key_ = acc;

  common::Value* sec_field = json->Find(SECRET_KEY_FIELD);
  std::string sec;
  if (!sec_field || !sec_field->GetAsBasicString(&sec)) {
    return common::Optional<S3Prop>();
  }
  res.secret_key_ = sec;

  return res;
}

common::Error S3Prop::DoDeSerialize(json_object* serialized) {
  S3Prop res;
  std::string acc;
  common::Error err = GetStringField(serialized, ACCESS_KEY_FIELD, &acc);
  if (err) {
    return err;
  }
  res.access_key_ = acc;

  std::string sec;
  err = GetStringField(serialized, SECRET_KEY_FIELD, &sec);
  if (err) {
    return err;
  }
  res.secret_key_ = sec;

  *this = res;
  return common::Error();
}

common::Error S3Prop::SerializeFields(json_object* out) const {
  if (!IsValid()) {
    return common::make_error_inval();
  }

  ignore_result(SetStringField(out, ACCESS_KEY_FIELD, access_key_));
  ignore_result(SetStringField(out, SECRET_KEY_FIELD, secret_key_));
  return common::Error();
}

}  // namespace fastotv

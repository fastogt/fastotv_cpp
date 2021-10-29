/*  Copyright (C) 2014-2021 FastoGT. All right reserved.

    This file is part of FastoTV.

    FastoTV is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    FastoTV is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FastoTV. If not, see <http://www.gnu.org/licenses/>.
*/

#include <fastotv/commands_info/auth_info.h>

#define ID_FIELD "device_id"
#define EXPIRED_DATE_FIELD "exp_date"

namespace fastotv {
namespace commands_info {

AuthInfo::AuthInfo() : AuthInfo(base_class(), std::string()) {}

AuthInfo::AuthInfo(const base_class& login, const device_id_t& dev) : base_class(login), device_id_(dev) {}

bool AuthInfo::IsValid() const {
  return base_class::IsValid() && !device_id_.empty();
}

common::Error AuthInfo::SerializeFields(json_object* deserialized) const {
  if (!IsValid()) {
    return common::make_error_inval();
  }

  ignore_result(SetStringField(deserialized, ID_FIELD, device_id_));
  return base_class::SerializeFields(deserialized);
}

common::Error AuthInfo::DoDeSerialize(json_object* serialized) {
  base_class login;
  common::Error err = login.DeSerialize(serialized);
  if (err) {
    return err;
  }

  device_id_t dev;
  err = GetStringField(serialized, ID_FIELD, &dev);
  if (err) {
    return common::make_error_inval();
  }

  *this = AuthInfo(login, dev);
  return common::Error();
}

device_id_t AuthInfo::GetDeviceID() const {
  return device_id_;
}

void AuthInfo::SetDeviceID(const device_id_t& dev) {
  device_id_ = dev;
}

bool AuthInfo::Equals(const AuthInfo& auth) const {
  return base_class::Equals(auth) && device_id_ == auth.device_id_;
}

ServerAuthInfo::ServerAuthInfo() : expired_date_(0) {}

ServerAuthInfo::ServerAuthInfo(const base_class& login, timestamp_t exp_date)
    : base_class(login), expired_date_(exp_date) {}

bool ServerAuthInfo::IsValid() const {
  return base_class::IsValid();
}

timestamp_t ServerAuthInfo::GetExpiredDate() const {
  return expired_date_;
}

void ServerAuthInfo::SetExpiredDate(timestamp_t date) {
  expired_date_ = date;
}

bool ServerAuthInfo::Equals(const ServerAuthInfo& auth) const {
  return base_class::Equals(auth) && expired_date_ == auth.expired_date_;
}

common::Error ServerAuthInfo::SerializeFields(json_object* deserialized) const {
  if (!IsValid()) {
    return common::make_error_inval();
  }

  ignore_result(SetInt64Field(deserialized, EXPIRED_DATE_FIELD, expired_date_));
  return base_class::SerializeFields(deserialized);
}

common::Error ServerAuthInfo::DoDeSerialize(json_object* serialized) {
  base_class login;
  common::Error err = login.DeSerialize(serialized);
  if (err) {
    return err;
  }

  int64_t exp;
  err = GetInt64Field(serialized, EXPIRED_DATE_FIELD, &exp);
  if (err) {
    return err;
  }

  *this = ServerAuthInfo(login, exp);
  return common::Error();
}

}  // namespace commands_info
}  // namespace fastotv

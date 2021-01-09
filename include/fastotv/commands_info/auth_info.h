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

#pragma once

#include <fastotv/commands_info/login_info.h>

namespace fastotv {
namespace commands_info {

class AuthInfo : public LoginInfo {
 public:
  typedef LoginInfo base_class;

  AuthInfo();
  AuthInfo(const base_class& login, const device_id_t& dev);

  bool IsValid() const;

  device_id_t GetDeviceID() const;
  void SetDeviceID(const device_id_t& dev);

  bool Equals(const AuthInfo& auth) const;

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* deserialized) const override;

 private:
  device_id_t device_id_;
};

inline bool operator==(const AuthInfo& lhs, const AuthInfo& rhs) {
  return lhs.Equals(rhs);
}

inline bool operator!=(const AuthInfo& x, const AuthInfo& y) {
  return !(x == y);
}

class ServerAuthInfo : public AuthInfo {
 public:
  typedef AuthInfo base_class;

  ServerAuthInfo();
  ServerAuthInfo(const base_class& login, timestamp_t exp_date);

  bool IsValid() const;

  timestamp_t GetExpiredDate() const;
  void SetExpiredDate(timestamp_t date);

  bool Equals(const ServerAuthInfo& auth) const;

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* deserialized) const override;

 private:
  timestamp_t expired_date_;
};

inline bool operator==(const ServerAuthInfo& lhs, const ServerAuthInfo& rhs) {
  return lhs.Equals(rhs);
}

inline bool operator!=(const ServerAuthInfo& x, const ServerAuthInfo& y) {
  return !(x == y);
}

}  // namespace commands_info
}  // namespace fastotv

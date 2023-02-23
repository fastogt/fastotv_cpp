/*  Copyright (C) 2014-2023 FastoGT. All right reserved.

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

#include <fastotv/commands_info/login_info.h>

#define LOGIN_FIELD "login"
#define PASSWORD_FIELD "password"

namespace fastotv {
namespace commands_info {

LoginInfo::LoginInfo() : LoginInfo(std::string(), std::string()) {}

LoginInfo::LoginInfo(const login_t& login, const password_t& password) : login_(login), password_(password) {}

bool LoginInfo::IsValid() const {
  return !login_.empty() && !password_.empty();
}

common::Error LoginInfo::SerializeFields(json_object* deserialized) const {
  if (!IsValid()) {
    return common::make_error_inval();
  }

  ignore_result(SetStringField(deserialized, LOGIN_FIELD, login_));
  ignore_result(SetStringField(deserialized, PASSWORD_FIELD, password_));
  return common::Error();
}

common::Error LoginInfo::DoDeSerialize(json_object* serialized) {
  std::string login;
  common::Error err = GetStringField(serialized, LOGIN_FIELD, &login);
  if (err) {
    return err;
  }

  std::string pass;
  err = GetStringField(serialized, PASSWORD_FIELD, &pass);
  if (err) {
    return err;
  }

  *this = LoginInfo(login, pass);
  return common::Error();
}

login_t LoginInfo::GetLogin() const {
  return login_;
}

void LoginInfo::SetLogin(const login_t& login) {
  login_ = login;
}

LoginInfo::password_t LoginInfo::GetPassword() const {
  return password_;
}

void LoginInfo::SetPassword(const fastotv::commands_info::LoginInfo::password_t& password) {
  password_ = password;
}

bool LoginInfo::Equals(const LoginInfo& auth) const {
  return login_ == auth.login_ && password_ == auth.password_;
}

}  // namespace commands_info
}  // namespace fastotv

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

#include <fastotv/types/login_and_password.h>

#define LOGIN_FIELD "login"
#define PASSWORD_FIELD "password"

namespace fastotv {

LoginAndPassword::LoginAndPassword() : LoginAndPassword(std::string(), std::string()) {}

LoginAndPassword::LoginAndPassword(const login_t& login, const password_t& password) : login_(login), password_(password) {}

bool LoginAndPassword::IsValid() const {
  return !login_.empty() && !password_.empty();
}

common::Error LoginAndPassword::SerializeFields(json_object* deserialized) const {
  if (!IsValid()) {
    return common::make_error_inval();
  }

  ignore_result(SetStringField(deserialized, LOGIN_FIELD, login_));
  ignore_result(SetStringField(deserialized, PASSWORD_FIELD, password_));
  return common::Error();
}

common::Error LoginAndPassword::DoDeSerialize(json_object* serialized) {
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

  *this = LoginAndPassword(login, pass);
  return common::Error();
}

login_t LoginAndPassword::GetLogin() const {
  return login_;
}

void LoginAndPassword::SetLogin(const login_t& login) {
  login_ = login;
}

LoginAndPassword::password_t LoginAndPassword::GetPassword() const {
  return password_;
}

void LoginAndPassword::SetPassword(const fastotv::LoginAndPassword::password_t& password) {
  password_ = password;
}

bool LoginAndPassword::Equals(const LoginAndPassword& auth) const {
  return login_ == auth.login_ && password_ == auth.password_;
}

common::Optional<LoginAndPassword> LoginAndPassword::Make(common::HashValue* json) {
  if (!json) {
    return common::Optional<LoginAndPassword>();
  }

  LoginAndPassword res;
  common::Value* login_field = json->Find(LOGIN_FIELD);
  std::string login_str;
  if (login_field && login_field->GetAsBasicString(&login_str)) {
    res.login_ = login_str;
  }

  common::Value* password_field = json->Find(PASSWORD_FIELD);
  if (password_field && password_field->GetAsBasicString(&login_str)) {
    res.password_ = login_str;
  }
  return res;
}

}  // namespace fastotv

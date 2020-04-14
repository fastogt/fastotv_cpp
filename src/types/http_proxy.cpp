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

#include <fastotv/types/http_proxy.h>

#include <string>

#include <json-c/json_object.h>
#include <json-c/json_tokener.h>

#include <common/sprintf.h>

#define URI_FIELD "uri"
#define USER_FIELD "user"
#define PASSWORD_FIELD "password"

namespace fastotv {

HttpProxy::HttpProxy() : HttpProxy(common::uri::Url()) {}

HttpProxy::HttpProxy(const common::uri::Url& url) : url_(url), user_(), password_() {}

bool HttpProxy::IsValid() const {
  return url_.IsValid();
}

bool HttpProxy::Equals(const HttpProxy& proxy) const {
  return url_ == proxy.url_;
}

common::uri::Url HttpProxy::GetUrl() const {
  return url_;
}

void HttpProxy::SetUrl(const common::uri::Url& path) {
  url_ = path;
}

HttpProxy::user_id_t HttpProxy::GetUserID() const {
  return user_;
}

void HttpProxy::SetUserID(const user_id_t& sid) {
  user_ = sid;
}

HttpProxy::password_t HttpProxy::GetPassword() const {
  return password_;
}

void HttpProxy::SetPassword(const password_t& password) {
  password_ = password;
}

common::Optional<HttpProxy> HttpProxy::Make(common::HashValue* hash) {
  if (!hash) {
    return common::Optional<HttpProxy>();
  }

  HttpProxy res;
  common::Value* url_field = hash->Find(URI_FIELD);
  std::string url_str;
  common::uri::Url uri;
  if (!url_field || !url_field->GetAsBasicString(&url_str) || !common::ConvertFromString(url_str, &uri)) {
    return common::Optional<HttpProxy>();
  }
  res.SetUrl(uri);

  common::Value* user_field = hash->Find(USER_FIELD);
  common::Value* password_field = hash->Find(PASSWORD_FIELD);
  std::string user_str;
  std::string password_str;

  if (user_field && user_field->GetAsBasicString(&user_str) && password_field &&
      password_field->GetAsBasicString(&password_str)) {
    res.SetUserID(user_str);
    res.SetPassword(password_str);
  }
  return res;
}

common::Error HttpProxy::DoDeSerialize(json_object* serialized) {
  HttpProxy res;
  json_object* jurl = nullptr;
  json_bool jurl_exists = json_object_object_get_ex(serialized, URI_FIELD, &jurl);
  if (!jurl_exists) {
    return common::make_error_inval();
  }
  res.SetUrl(common::uri::Url(json_object_get_string(jurl)));

  json_object* juser = nullptr;
  json_object* jpassword = nullptr;
  json_bool juser_exists = json_object_object_get_ex(serialized, USER_FIELD, &juser);
  json_bool jpassword_exists = json_object_object_get_ex(serialized, USER_FIELD, &jpassword);
  if (juser_exists && jpassword_exists) {
    std::string user = json_object_get_string(juser);
    res.SetUserID(user);

    std::string password = json_object_get_string(jpassword);
    res.SetPassword(password);
  }
  *this = res;
  return common::Error();
}

common::Error HttpProxy::SerializeFields(json_object* out) const {
  if (!IsValid()) {
    return common::make_error_inval();
  }

  const std::string url_path = url_.GetUrl();
  json_object_object_add(out, URI_FIELD, json_object_new_string(url_path.c_str()));
  if (user_ && password_) {
    const std::string user_str = *user_;
    const std::string password_str = *password_;
    json_object_object_add(out, USER_FIELD, json_object_new_string(user_str.c_str()));
    json_object_object_add(out, PASSWORD_FIELD, json_object_new_string(password_str.c_str()));
  }
  return common::Error();
}

}  // namespace fastotv

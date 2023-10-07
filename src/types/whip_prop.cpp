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

#include <fastotv/types/whip_prop.h>

#define AUTH_TOKEN_FIELD "auth_token"

namespace fastotv {

WhipProp::WhipProp() : WhipProp(auth_token_t()) {}

WhipProp::WhipProp(const auth_token_t& auth) : auth_token_(auth) {}

bool WhipProp::IsValid() const {
  return true;
}

WhipProp::auth_token_t WhipProp::GetAuthToken() const {
  return auth_token_;
}

void WhipProp::SetAuthToken(const auth_token_t& auth) {
  auth_token_ = auth;
}

bool WhipProp::Equals(const WhipProp& key) const {
  return auth_token_ == key.auth_token_;
}

common::Optional<WhipProp> WhipProp::Make(common::HashValue* json) {
  if (!json) {
    return common::Optional<WhipProp>();
  }

  WhipProp res;
  common::Value* name_field = json->Find(AUTH_TOKEN_FIELD);
  std::string name;
  if (name_field && name_field->GetAsBasicString(&name)) {
    res.auth_token_ = name;
  }

  return res;
}

common::Error WhipProp::DoDeSerialize(json_object* serialized) {
  WhipProp res;
  std::string name;
  common::Error err = GetStringField(serialized, AUTH_TOKEN_FIELD, &name);
  if (!err) {
    res.auth_token_ = name;
  }

  *this = res;
  return common::Error();
}

common::Error WhipProp::SerializeFields(json_object* out) const {
  if (!IsValid()) {
    return common::make_error_inval();
  }

  if (auth_token_) {
    ignore_result(SetStringField(out, AUTH_TOKEN_FIELD, *auth_token_));
  }
  return common::Error();
}

}  // namespace fastotv

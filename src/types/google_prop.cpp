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

#include <fastotv/types/google_prop.h>

#define ACCOUNT_CREDS_FIELD "account_creds"

namespace fastotv {

GoogleProp::GoogleProp() : GoogleProp(std::string()) {}

GoogleProp::GoogleProp(const account_creds_t& creds) : account_creds_(creds) {}

bool GoogleProp::IsValid() const {
  return !account_creds_.empty();
}

GoogleProp::account_creds_t GoogleProp::GetAccountCreds() const {
  return account_creds_;
}

void GoogleProp::SetAccountCreds(const account_creds_t& creds) {
  account_creds_ = creds;
}

bool GoogleProp::Equals(const GoogleProp& key) const {
  return account_creds_ == key.account_creds_;
}

common::Optional<GoogleProp> GoogleProp::Make(common::HashValue* json) {
  if (!json) {
    return common::Optional<GoogleProp>();
  }

  GoogleProp res;
  common::Value* creds_field = json->Find(ACCOUNT_CREDS_FIELD);
  std::string creds;
  if (!creds_field || !creds_field->GetAsBasicString(&creds)) {
    return common::Optional<GoogleProp>();
  }
  res.account_creds_ = creds;

  return common::Optional<GoogleProp>(res);
}

common::Error GoogleProp::DoDeSerialize(json_object* serialized) {
  GoogleProp res;
  std::string name;
  common::Error err = GetStringField(serialized, ACCOUNT_CREDS_FIELD, &name);
  if (err) {
    return err;
  }
  res.account_creds_ = name;

  *this = res;
  return common::Error();
}

common::Error GoogleProp::SerializeFields(json_object* out) const {
  if (!IsValid()) {
    return common::make_error_inval();
  }

  ignore_result(SetStringField(out, ACCOUNT_CREDS_FIELD, account_creds_));
  return common::Error();
}

}  // namespace fastotv

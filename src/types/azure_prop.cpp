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

#include <fastotv/types/azure_prop.h>

#define ACCOUNT_NAME_FIELD "account_name"
#define ACCOUNT_KEY_FIELD "account_key"
#define LOCATION_FIELD "location"

namespace fastotv {

AzureProp::AzureProp() : AzureProp(std::string(), std::string(), std::string()) {}

AzureProp::AzureProp(const account_name_t& name, const account_key_t& account_key, const location_t& location)
    : account_name_(name), account_key_(account_key), location_(location) {}

bool AzureProp::IsValid() const {
  return !account_name_.empty() && !account_key_.empty() && !location_.empty();
}

AzureProp::account_name_t AzureProp::GetAccountName() const {
  return account_name_;
}

void AzureProp::SetAccountName(const account_name_t& name) {
  account_name_ = name;
}

AzureProp::account_key_t AzureProp::GetAccountKey() const {
  return account_key_;
}

void AzureProp::SetAccountKey(const account_key_t& key) {
  account_key_ = key;
}

AzureProp::location_t AzureProp::GetLocation() const {
  return location_;
}

void AzureProp::SetLocation(const location_t& location) {
  location_ = location;
}

bool AzureProp::Equals(const AzureProp& key) const {
  return account_key_ == key.account_key_ && account_name_ == key.account_name_ && location_ == key.location_;
}

common::Optional<AzureProp> AzureProp::Make(common::HashValue* json) {
  if (!json) {
    return common::Optional<AzureProp>();
  }

  AzureProp res;
  common::Value* name_field = json->Find(ACCOUNT_NAME_FIELD);
  std::string name;
  if (!name_field || !name_field->GetAsBasicString(&name)) {
    return common::Optional<AzureProp>();
  }
  res.account_name_ = name;

  common::Value* acc_field = json->Find(ACCOUNT_KEY_FIELD);
  std::string acc;
  if (!acc_field || !acc_field->GetAsBasicString(&acc)) {
    return common::Optional<AzureProp>();
  }
  res.account_key_ = acc;

  common::Value* sec_field = json->Find(LOCATION_FIELD);
  std::string sec;
  if (!sec_field || !sec_field->GetAsBasicString(&sec)) {
    return common::Optional<AzureProp>();
  }
  res.location_ = sec;

  return res;
}

common::Error AzureProp::DoDeSerialize(json_object* serialized) {
  AzureProp res;
  std::string name;
  common::Error err = GetStringField(serialized, ACCOUNT_NAME_FIELD, &name);
  if (err) {
    return err;
  }
  res.account_name_ = name;

  std::string acc;
  err = GetStringField(serialized, ACCOUNT_KEY_FIELD, &acc);
  if (err) {
    return err;
  }
  res.account_key_ = acc;

  std::string sec;
  err = GetStringField(serialized, LOCATION_FIELD, &sec);
  if (err) {
    return err;
  }
  res.location_ = sec;

  *this = res;
  return common::Error();
}

common::Error AzureProp::SerializeFields(json_object* out) const {
  if (!IsValid()) {
    return common::make_error_inval();
  }

  ignore_result(SetStringField(out, ACCOUNT_NAME_FIELD, account_name_));
  ignore_result(SetStringField(out, ACCOUNT_KEY_FIELD, account_key_));
  ignore_result(SetStringField(out, LOCATION_FIELD, location_));
  return common::Error();
}

}  // namespace fastotv

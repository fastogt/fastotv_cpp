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

#include <fastotv/types/drm_key.h>

#define KID_FIELD "kid"
#define KEY_FIELD "key"

namespace fastotv {

DrmKey::DrmKey() : kid_(), key_() {}

DrmKey::DrmKey(const hexed_kid_t& kid, const hexed_kid_t& key) : kid_(kid), key_(key) {}

bool DrmKey::IsValid() const {
  return !kid_.empty() && !key_.empty();
}

DrmKey::hexed_kid_t DrmKey::GetHexedKid() const {
  return kid_;
}

void DrmKey::SetHexedKid(const hexed_kid_t& kid) {
  kid_ = kid;
}

void DrmKey::SetHexedKey(const hexed_key_t& key) {
  key_ = key;
}

DrmKey::hexed_key_t DrmKey::GetHexedKey() const {
  return key_;
}

bool DrmKey::Equals(const DrmKey& key) const {
  return kid_ == key.kid_ && key_ == key.key_;
}

common::Optional<DrmKey> DrmKey::Make(common::HashValue* json) {
  if (!json) {
    return common::Optional<DrmKey>();
  }

  DrmKey res;
  common::Value* kid_field = json->Find(KID_FIELD);
  hexed_kid_t kid;
  if (!kid_field || !kid_field->GetAsBasicString(&kid)) {
    return common::Optional<DrmKey>();
  }
  res.kid_ = kid;

  common::Value* key_field = json->Find(KEY_FIELD);
  hexed_key_t key;
  if (!key_field || !key_field->GetAsBasicString(&key)) {
    return common::Optional<DrmKey>();
  }
  res.key_ = key;
  return res;
}

common::Error DrmKey::DoDeSerialize(json_object* serialized) {
  DrmKey res;
  hexed_kid_t kid;
  common::Error err = GetStringField(serialized, KID_FIELD, &kid);
  if (err) {
    return err;
  }
  res.kid_ = kid;

  hexed_key_t key;
  err = GetStringField(serialized, KEY_FIELD, &key);
  if (err) {
    return err;
  }
  res.key_ = key;

  *this = res;
  return common::Error();
}

common::Error DrmKey::SerializeFields(json_object* out) const {
  if (!IsValid()) {
    return common::make_error_inval();
  }

  ignore_result(SetStringField(out, KID_FIELD, kid_));
  ignore_result(SetStringField(out, KEY_FIELD, key_));
  return common::Error();
}

}  // namespace fastotv

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

#include <fastotv/types/srt_key.h>

#define PASSPHRASE_FIELD "passphrase"
#define KEY_LEN_FIELD "pbkeylen"

namespace fastotv {

SrtKey::SrtKey() : passphrase_(), key_len_(0) {}

SrtKey::SrtKey(const srt_passphrase_t& passphrase, key_len_t key_len) : passphrase_(passphrase), key_len_(key_len) {}

bool SrtKey::IsValid() const {
  return !passphrase_.empty() && key_len_ != 0;
}

SrtKey::srt_passphrase_t SrtKey::GetSrtPassPhrase() const {
  return passphrase_;
}

void SrtKey::SetSrtPassPhrase(const srt_passphrase_t& pass) {
  passphrase_ = pass;
}

void SrtKey::SetKeyLen(key_len_t key_len) {
  key_len_ = key_len;
}

SrtKey::key_len_t SrtKey::GetKeyLen() const {
  return key_len_;
}

bool SrtKey::Equals(const SrtKey& key) const {
  return passphrase_ == key.passphrase_ && key_len_ == key.key_len_;
}

common::Optional<SrtKey> SrtKey::Make(common::HashValue* json) {
  if (!json) {
    return common::Optional<SrtKey>();
  }

  SrtKey res;
  common::Value* pass_field = json->Find(PASSPHRASE_FIELD);
  std::string pass;
  if (!pass_field || !pass_field->GetAsBasicString(&pass)) {
    return common::Optional<SrtKey>();
  }
  res.passphrase_ = pass;

  key_len_t kl;
  common::Value* kl_field = json->Find(KEY_LEN_FIELD);
  if (!kl_field || !kl_field->GetAsInteger(&kl)) {
    return common::Optional<SrtKey>();
  }
  res.key_len_ = kl;
  return res;
}

common::Error SrtKey::DoDeSerialize(json_object* serialized) {
  SrtKey res;
  std::string pass;
  common::Error err = GetStringField(serialized, PASSPHRASE_FIELD, &pass);
  if (err) {
    return err;
  }
  res.passphrase_ = pass;

  key_len_t kl;
  err = GetIntField(serialized, KEY_LEN_FIELD, &kl);
  if (err) {
    return err;
  }

  res.key_len_ = kl;
  *this = res;
  return common::Error();
}

common::Error SrtKey::SerializeFields(json_object* out) const {
  if (!IsValid()) {
    return common::make_error_inval();
  }

  ignore_result(SetStringField(out, PASSPHRASE_FIELD, passphrase_));
  ignore_result(SetIntField(out, KEY_LEN_FIELD, key_len_));
  return common::Error();
}

}  // namespace fastotv

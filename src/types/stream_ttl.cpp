/*  Copyright (C) 2014-2022 FastoGT. All right reserved.
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

#include <fastotv/types/stream_ttl.h>

#define TTL_FIELD "ttl"
#define PHOENIX_FIELD "pbkeylen"

namespace fastotv {

StreamTTL::StreamTTL() : ttl_(0), phoenix_(false) {}

StreamTTL::StreamTTL(const ttl_t& ttl, bool phoenix) : ttl_(ttl), phoenix_(phoenix) {}

bool StreamTTL::IsValid() const {
  return true;
}

StreamTTL::ttl_t StreamTTL::GetTTL() const {
  return ttl_;
}

void StreamTTL::SetTTL(const ttl_t& ttl) {
  ttl_ = ttl;
}

void StreamTTL::SetPhoenix(bool phoenix) {
  phoenix_ = phoenix;
}

bool StreamTTL::GetPhoenix() const {
  return phoenix_;
}

bool StreamTTL::Equals(const StreamTTL& key) const {
  return phoenix_ == key.phoenix_ && ttl_ == key.ttl_;
}

common::Optional<StreamTTL> StreamTTL::Make(common::HashValue* json) {
  if (!json) {
    return common::Optional<StreamTTL>();
  }

  StreamTTL res;
  common::Value* pass_field = json->Find(TTL_FIELD);
  ttl_t ttl;
  if (!pass_field || !pass_field->GetAsTime(&ttl)) {
    return common::Optional<StreamTTL>();
  }
  res.ttl_ = ttl;

  bool phoenix;
  common::Value* kl_field = json->Find(PHOENIX_FIELD);
  if (!kl_field || !kl_field->GetAsBoolean(&phoenix)) {
    return common::Optional<StreamTTL>();
  }
  res.phoenix_ = phoenix;
  return res;
}

common::Error StreamTTL::DoDeSerialize(json_object* serialized) {
  StreamTTL res;
  int64_t ttl;
  common::Error err = GetInt64Field(serialized, TTL_FIELD, &ttl);
  if (err) {
    return err;
  }
  res.ttl_ = ttl;

  bool phoenix;
  err = GetBoolField(serialized, PHOENIX_FIELD, &phoenix);
  if (err) {
    return err;
  }

  res.phoenix_ = phoenix;
  *this = res;
  return common::Error();
}

common::Error StreamTTL::SerializeFields(json_object* out) const {
  if (!IsValid()) {
    return common::make_error_inval();
  }

  ignore_result(SetInt64Field(out, TTL_FIELD, ttl_));
  ignore_result(SetBoolField(out, PHOENIX_FIELD, phoenix_));
  return common::Error();
}

}  // namespace fastotv

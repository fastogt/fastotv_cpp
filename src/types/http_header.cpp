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

#include <fastotv/types/http_header.h>

#define KEY_FIELD "key"
#define VALUE_FIELD "value"

namespace fastotv {

HttpHeader::HttpHeader() : HttpHeader(key_t(), value_t()) {}

HttpHeader::HttpHeader(const key_t& key, const value_t& value) : base_class(), key_(key), value_(value) {}

bool HttpHeader::IsValid() const {
  return !key_.empty() && !value_.empty();
}

HttpHeader::key_t HttpHeader::GetKey() const {
  return key_;
}

void HttpHeader::SetKey(const key_t& key) {
  key_ = key;
}

HttpHeader::value_t HttpHeader::GetValue() const {
  return value_;
}

void HttpHeader::SetValue(const value_t& val) {
  value_ = val;
}

bool HttpHeader::Equals(const HttpHeader& inf) const {
  return key_ == inf.key_ && value_ == inf.value_;
}

common::Optional<HttpHeader> HttpHeader::Make(common::HashValue* json) {
  if (!json) {
    return common::Optional<HttpHeader>();
  }

  HttpHeader res;
  common::Value* key_field = json->Find(KEY_FIELD);
  std::string key;
  if (!key_field || !key_field->GetAsBasicString(&key)) {
    return common::Optional<HttpHeader>();
  }
  res.key_ = key;

  common::Value* value_field = json->Find(VALUE_FIELD);
  std::string value;
  if (!value_field || !value_field->GetAsBasicString(&value)) {
    return common::Optional<HttpHeader>();
  }
  res.value_ = value;
  return res;
}

common::Error HttpHeader::DoDeSerialize(json_object* serialized) {
  std::string key;
  common::Error err = GetStringField(serialized, KEY_FIELD, &key);
  if (err) {
    return err;
  }

  std::string value;
  err = GetStringField(serialized, VALUE_FIELD, &value);
  if (err) {
    return err;
  }

  *this = HttpHeader(key, value);
  return common::Error();
}

common::Error HttpHeader::SerializeFields(json_object* out) const {
  if (!IsValid()) {
    return common::make_error_inval();
  }

  ignore_result(SetStringField(out, KEY_FIELD, key_));
  ignore_result(SetStringField(out, VALUE_FIELD, value_));
  return common::Error();
}

}  // namespace fastotv

/*  Copyright (C) 2014-2021 FastoGT. All right reserved.
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

#include <fastotv/types/kvs_prop.h>

#define STREAM_NAME_FIELD "stream_name"

namespace fastotv {

KVSProp::KVSProp() : stream_name_() {}

KVSProp::KVSProp(const stream_name_t& name) : stream_name_(name) {}

bool KVSProp::IsValid() const {
  return !stream_name_.empty();
}

KVSProp::stream_name_t KVSProp::GetStreamName() const {
  return stream_name_;
}

void KVSProp::SetStreamName(const stream_name_t& name) {
  stream_name_ = name;
}

bool KVSProp::Equals(const KVSProp& key) const {
  return stream_name_ == key.stream_name_;
}

common::Optional<KVSProp> KVSProp::Make(common::HashValue* json) {
  if (!json) {
    return common::Optional<KVSProp>();
  }

  KVSProp res;
  common::Value* name_field = json->Find(STREAM_NAME_FIELD);
  std::string name;
  if (!name_field || !name_field->GetAsBasicString(&name)) {
    return common::Optional<KVSProp>();
  }
  res.stream_name_ = name;

  return res;
}

common::Error KVSProp::DoDeSerialize(json_object* serialized) {
  KVSProp res;
  std::string name;
  common::Error err = GetStringField(serialized, STREAM_NAME_FIELD, &name);
  if (err) {
    return err;
  }
  res.stream_name_ = name;

  *this = res;
  return common::Error();
}

common::Error KVSProp::SerializeFields(json_object* out) const {
  if (!IsValid()) {
    return common::make_error_inval();
  }

  ignore_result(SetStringField(out, STREAM_NAME_FIELD, stream_name_));
  return common::Error();
}

}  // namespace fastotv

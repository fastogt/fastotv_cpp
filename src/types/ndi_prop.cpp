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

#include <fastotv/types/ndi_prop.h>

#define NDI_NAME_FIELD "name"

namespace fastotv {

NDIProp::NDIProp() : NDIProp(ndi_name_t()) {}

NDIProp::NDIProp(const ndi_name_t& name) : ndi_name_(name) {}

bool NDIProp::IsValid() const {
  return !ndi_name_.empty();
}

NDIProp::ndi_name_t NDIProp::GetName() const {
  return ndi_name_;
}

void NDIProp::SetName(const ndi_name_t& name) {
  ndi_name_ = name;
}

bool NDIProp::Equals(const NDIProp& key) const {
  return ndi_name_ == key.ndi_name_;
}

common::Optional<NDIProp> NDIProp::Make(common::HashValue* json) {
  if (!json) {
    return common::Optional<NDIProp>();
  }

  NDIProp res;
  common::Value* name_field = json->Find(NDI_NAME_FIELD);
  std::string name;
  if (!name_field || !name_field->GetAsBasicString(&name)) {
    return common::Optional<NDIProp>();
  }
  res.ndi_name_ = name;

  return res;
}

common::Error NDIProp::DoDeSerialize(json_object* serialized) {
  NDIProp res;
  std::string name;
  common::Error err = GetStringField(serialized, NDI_NAME_FIELD, &name);
  if (err) {
    return err;
  }
  res.ndi_name_ = name;

  *this = res;
  return common::Error();
}

common::Error NDIProp::SerializeFields(json_object* out) const {
  if (!IsValid()) {
    return common::make_error_inval();
  }

  ignore_result(SetStringField(out, NDI_NAME_FIELD, ndi_name_));
  return common::Error();
}

}  // namespace fastotv

/*  Copyright (C) 2014-2020 FastoGT. All right reserved.

    This file is part of FastoTV.

    FastoTV is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    FastoTV is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FastoTV. If not, see <http://www.gnu.org/licenses/>.
*/

#include <fastotv/commands_info/device_info.h>

#define DEVICE_INFO_ID_FIELD "id"
#define DEVICE_INFO_NAME_FIELD "name"

namespace fastotv {
namespace commands_info {

DeviceInfo::DeviceInfo() : DeviceInfo(device_t(), std::string()) {}

DeviceInfo::DeviceInfo(const device_t& did, const std::string& name) : did_(did), name_(name) {}

bool DeviceInfo::IsValid() const {
  return did_ && !name_.empty();
}

void DeviceInfo::SetDeviceID(const device_t& did) {
  did_ = did;
}

DeviceInfo::device_t DeviceInfo::GetDeviceID() const {
  return did_;
}

void DeviceInfo::SetName(const std::string& name) {
  name_ = name;
}

std::string DeviceInfo::GetName() const {
  return name_;
}

common::Error DeviceInfo::SerializeFields(json_object* deserialized) const {
  if (!IsValid()) {
    return common::make_error_inval();
  }

  const std::string did = *did_;
  json_object_object_add(deserialized, DEVICE_INFO_ID_FIELD, json_object_new_string(did.c_str()));
  json_object_object_add(deserialized, DEVICE_INFO_NAME_FIELD, json_object_new_string(name_.c_str()));
  return common::Error();
}

common::Error DeviceInfo::DoDeSerialize(json_object* serialized) {
  device_id_t did;
  common::Error err = GetStringField(serialized, DEVICE_INFO_ID_FIELD, &did);
  if (err) {
    return err;
  }

  std::string name;
  err = GetStringField(serialized, DEVICE_INFO_NAME_FIELD, &name);
  if (err) {
    return err;
  }

  DeviceInfo dev(did, name);
  if (!dev.IsValid()) {
    return common::make_error_inval();
  }

  *this = dev;
  return common::Error();
}

bool DeviceInfo::Equals(const DeviceInfo& url) const {
  return did_ == url.did_ && name_ == url.name_;
}

}  // namespace commands_info
}  // namespace fastotv

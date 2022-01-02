/*  Copyright (C) 2014-2022 FastoGT. All right reserved.

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

#pragma once

#include <string>

#include <common/serializer/json_serializer.h>

#include <fastotv/types.h>

namespace fastotv {
namespace commands_info {

class DeviceInfo : public common::serializer::JsonSerializer<DeviceInfo> {
 public:
  typedef common::Optional<device_id_t> device_t;

  DeviceInfo();
  DeviceInfo(const device_t& did, const std::string& name);

  bool IsValid() const;

  void SetDeviceID(const device_t& did);
  device_t GetDeviceID() const;

  void SetName(const std::string& name);
  std::string GetName() const;

  bool Equals(const DeviceInfo& url) const;

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* deserialized) const override;

 private:
  device_t did_;
  std::string name_;
};

inline bool operator==(const DeviceInfo& left, const DeviceInfo& right) {
  return left.Equals(right);
}

inline bool operator!=(const DeviceInfo& x, const DeviceInfo& y) {
  return !(x == y);
}

}  // namespace commands_info
}  // namespace fastotv

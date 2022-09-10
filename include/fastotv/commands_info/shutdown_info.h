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

#include <common/serializer/json_serializer.h>
#include <common/time.h>

#include <string>

namespace fastotv {
namespace commands_info {

class ShutDownInfo : public common::serializer::JsonSerializer<ShutDownInfo> {
 public:
  ShutDownInfo();
  explicit ShutDownInfo(common::time64_t timeout);

  common::time64_t GetTimeout() const;
  void SetTimeout(common::time64_t time);

  bool Equals(const ShutDownInfo& shut) const;

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* deserialized) const override;

 private:
  common::time64_t timeout_;
};

inline bool operator==(const ShutDownInfo& lhs, const ShutDownInfo& rhs) {
  return lhs.Equals(rhs);
}

inline bool operator!=(const ShutDownInfo& x, const ShutDownInfo& y) {
  return !(x == y);
}

}  // namespace commands_info
}  // namespace fastotv

/*  Copyright (C) 2014-2021 FastoGT. All right reserved.

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

#include <fastotv/commands_info/shutdown_info.h>

#define TIMEOUT_FIELD "timeout"

namespace fastotv {
namespace commands_info {

ShutDownInfo::ShutDownInfo() : timeout_(0) {}

ShutDownInfo::ShutDownInfo(common::time64_t timeout) : timeout_(timeout) {}

common::Error ShutDownInfo::SerializeFields(json_object* deserialized) const {
  ignore_result(SetInt64Field(deserialized, TIMEOUT_FIELD, timeout_));
  return common::Error();
}

common::Error ShutDownInfo::DoDeSerialize(json_object* serialized) {
  int64_t timeout;
  common::Error err = GetInt64Field(serialized, TIMEOUT_FIELD, &timeout);
  if (err) {
    return err;
  }

  *this = ShutDownInfo(timeout);
  return common::Error();
}

common::time64_t ShutDownInfo::GetTimeout() const {
  return timeout_;
}

void ShutDownInfo::SetTimeout(common::time64_t time) {
  timeout_ = time;
}

bool ShutDownInfo::Equals(const ShutDownInfo& shut) const {
  return timeout_ == shut.timeout_;
}

}  // namespace commands_info
}  // namespace fastotv

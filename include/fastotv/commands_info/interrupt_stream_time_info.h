/*  Copyright (C) 2014-2023 FastoGT. All right reserved.

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
#include <fastotv/types.h>

#include <string>

namespace fastotv {
namespace commands_info {

class InterruptStreamTimeInfo : public common::serializer::JsonSerializer<InterruptStreamTimeInfo> {
 public:
  InterruptStreamTimeInfo();
  InterruptStreamTimeInfo(const stream_id_t& id, timestamp_t time);

  bool IsValid() const;

  void SetChannel(const stream_id_t& channel);
  stream_id_t GetChannel() const;

  void SetTime(timestamp_t time);
  timestamp_t GetTime() const;

  bool Equals(const InterruptStreamTimeInfo& eq) const;

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* deserialized) const override;

 private:
  stream_id_t id_;
  timestamp_t time_;
};

inline bool operator==(const InterruptStreamTimeInfo& lhs, const InterruptStreamTimeInfo& rhs) {
  return lhs.Equals(rhs);
}

inline bool operator!=(const InterruptStreamTimeInfo& x, const InterruptStreamTimeInfo& y) {
  return !(x == y);
}

}  // namespace commands_info
}  // namespace fastotv

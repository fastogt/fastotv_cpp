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

#pragma once

#include <common/serializer/json_serializer.h>

#include <fastotv/types.h>

namespace fastotv {
namespace commands_info {

class ServerPingInfo : public common::serializer::JsonSerializer<ServerPingInfo> {
 public:
  ServerPingInfo();

  timestamp_t GetTimeStamp() const;
  void SetTimestamp(timestamp_t time);

  bool Equals(const ServerPingInfo& ping) const;

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* deserialized) const override;

 private:
  timestamp_t timestamp_;  // utc time
};

inline bool operator==(const ServerPingInfo& lhs, const ServerPingInfo& rhs) {
  return lhs.Equals(rhs);
}

inline bool operator!=(const ServerPingInfo& x, const ServerPingInfo& y) {
  return !(x == y);
}

class ClientPingInfo : public common::serializer::JsonSerializer<ClientPingInfo> {
 public:
  ClientPingInfo();

  timestamp_t GetTimeStamp() const;

  bool Equals(const ClientPingInfo& ping) const;

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* deserialized) const override;

 private:
  timestamp_t timestamp_;  // utc time
};

inline bool operator==(const ClientPingInfo& lhs, const ClientPingInfo& rhs) {
  return lhs.Equals(rhs);
}

inline bool operator!=(const ClientPingInfo& x, const ClientPingInfo& y) {
  return !(x == y);
}

}  // namespace commands_info
}  // namespace fastotv

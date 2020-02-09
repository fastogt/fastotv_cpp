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

#include <common/net/types.h>  // for HostAndPort

#include <common/serializer/json_serializer.h>
#include <common/uri/url.h>

namespace fastotv {
namespace commands_info {

class ServerInfo : public common::serializer::JsonSerializer<ServerInfo> {
 public:
  ServerInfo();
  explicit ServerInfo(const common::uri::Url& epg_url);

  common::uri::Url GetEpgUrl() const;
  void SetEpgUrl(const common::uri::Url& url);

  bool Equals(const ServerInfo& serv) const;

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* deserialized) const override;

 private:
  common::uri::Url epg_url_;
};

inline bool operator==(const ServerInfo& lhs, const ServerInfo& rhs) {
  return lhs.Equals(rhs);
}

inline bool operator!=(const ServerInfo& x, const ServerInfo& y) {
  return !(x == y);
}

}  // namespace commands_info
}  // namespace fastotv

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

#include <fastotv/commands_info/server_info.h>

#define EPG_URL_FIELD "epg_url"

namespace fastotv {
namespace commands_info {

ServerInfo::ServerInfo() : epg_url_() {}

ServerInfo::ServerInfo(const common::uri::Url& epg_url) : epg_url_(epg_url) {}

common::Error ServerInfo::SerializeFields(json_object* deserialized) const {
  const std::string epg_url_str = epg_url_.GetUrl();
  json_object_object_add(deserialized, EPG_URL_FIELD, json_object_new_string(epg_url_str.c_str()));
  return common::Error();
}

common::Error ServerInfo::DoDeSerialize(json_object* serialized) {
  ServerInfo inf;
  json_object* jepg_url = nullptr;
  json_bool jepg_url_exists = json_object_object_get_ex(serialized, EPG_URL_FIELD, &jepg_url);
  if (jepg_url_exists) {
    const std::string epg_url_str = json_object_get_string(jepg_url);
    common::uri::Url hs;
    if (common::ConvertFromString(epg_url_str, &hs)) {
      inf.epg_url_ = hs;
    }
  }

  *this = inf;
  return common::Error();
}

common::uri::Url ServerInfo::GetEpgUrl() const {
  return epg_url_;
}

void ServerInfo::SetEpgUrl(const common::uri::Url& url) {
  epg_url_ = url;
}

bool ServerInfo::Equals(const ServerInfo& serv) const {
  return serv.epg_url_ == epg_url_;
}

}  // namespace commands_info
}  // namespace fastotv

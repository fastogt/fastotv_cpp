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
#define LOCKED_STREAM_TEXT_FIELD "locked_stream_text"

namespace fastotv {
namespace commands_info {

ServerInfo::ServerInfo() : epg_url_(), locked_stream_text_() {}

ServerInfo::ServerInfo(const url_t& epg_url, const std::string& locked_stream_text)
    : epg_url_(epg_url), locked_stream_text_(locked_stream_text) {}

common::Error ServerInfo::SerializeFields(json_object* deserialized) const {
  const std::string epg_url_str = epg_url_.spec();
  json_object_object_add(deserialized, EPG_URL_FIELD, json_object_new_string(epg_url_str.c_str()));
  const char* locked = !locked_stream_text_.empty() ? locked_stream_text_.c_str() : "";
  json_object_object_add(deserialized, LOCKED_STREAM_TEXT_FIELD, json_object_new_string(locked));
  return common::Error();
}

common::Error ServerInfo::DoDeSerialize(json_object* serialized) {
  ServerInfo inf;
  json_object* jepg_url = nullptr;
  json_bool jepg_url_exists = json_object_object_get_ex(serialized, EPG_URL_FIELD, &jepg_url);
  if (jepg_url_exists) {
    const std::string epg_url_str = json_object_get_string(jepg_url);
    url_t hs(epg_url_str);
    if (hs.is_valid()) {
      inf.epg_url_ = hs;
    }
  }

  json_object* jlocked = nullptr;
  json_bool jlocked_exists = json_object_object_get_ex(serialized, LOCKED_STREAM_TEXT_FIELD, &jlocked);
  if (jlocked_exists) {
    inf.locked_stream_text_ = json_object_get_string(jlocked);
  }

  *this = inf;
  return common::Error();
}

ServerInfo::url_t ServerInfo::GetEpgUrl() const {
  return epg_url_;
}

void ServerInfo::SetEpgUrl(const url_t& url) {
  epg_url_ = url;
}

std::string ServerInfo::GetLockedStreamText() const {
  return locked_stream_text_;
}

void ServerInfo::SetLockedStreamText(const std::string& text) {
  locked_stream_text_ = text;
}

bool ServerInfo::Equals(const ServerInfo& serv) const {
  return serv.epg_url_ == epg_url_;
}

}  // namespace commands_info
}  // namespace fastotv

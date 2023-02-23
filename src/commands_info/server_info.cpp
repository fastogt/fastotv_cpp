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
  ignore_result(SetStringField(deserialized, EPG_URL_FIELD, epg_url_str));
  ignore_result(SetStringField(deserialized, LOCKED_STREAM_TEXT_FIELD, locked_stream_text_));
  return common::Error();
}

common::Error ServerInfo::DoDeSerialize(json_object* serialized) {
  ServerInfo inf;
  std::string epg_url_str;
  common::Error err = GetStringField(serialized, EPG_URL_FIELD, &epg_url_str);
  if (!err) {
    inf.epg_url_ = url_t(epg_url_str);
  }

  std::string locked;
  err = GetStringField(serialized, LOCKED_STREAM_TEXT_FIELD, &locked);
  if (!err) {
    inf.locked_stream_text_ = locked;
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

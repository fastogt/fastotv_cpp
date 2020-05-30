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

#include <fastotv/commands_info/serial_info.h>

#define ID_FIELD "id"
#define NAME_FIELD "name"
#define ICON_FIELD "icon"
#define GROUPS_FIELD "groups"
#define DESCRIPTION_FIELD "description"
#define SEASON_FIELD "season"
#define EPISODES_FIELD "episodes"
#define VIEW_COUNT_FIELD "view_count"

namespace fastotv {
namespace commands_info {

SerialInfo::SerialInfo()
    : SerialInfo(invalid_stream_id, std::string(), common::uri::GURL(), groups_t(), std::string(), 0, episodes_t(), 0) {
}

SerialInfo::SerialInfo(serial_id_t sid,
                       const std::string& name,
                       const common::uri::GURL& icon,
                       groups_t groups,
                       const std::string& description,
                       size_t season,
                       episodes_t episodes,
                       view_count_t views)
    : sid_(sid),
      name_(name),
      icon_(icon),
      groups_(groups),
      description_(description),
      season_(season),
      episodes_(episodes),
      view_count_(views) {}

bool SerialInfo::IsValid() const {
  return sid_ != invalid_stream_id;
}

serial_id_t SerialInfo::GetSerialID() const {
  return sid_;
}

void SerialInfo::SetSerialID(serial_id_t sid) {
  sid_ = sid;
}

std::string SerialInfo::GetName() const {
  return name_;
}

void SerialInfo::SetName(const std::string& name) {
  name_ = name;
}

common::uri::GURL SerialInfo::GetIcon() const {
  return icon_;
}

void SerialInfo::SetIcon(const common::uri::GURL& icon) {
  icon_ = icon;
}

SerialInfo::groups_t SerialInfo::GetGroups() const {
  return groups_;
}

void SerialInfo::SetGroups(groups_t groups) {
  groups_ = groups;
}

SerialInfo::view_count_t SerialInfo::GetViewCount() const {
  return view_count_;
}

void SerialInfo::SetViewCount(view_count_t view) {
  view_count_ = view;
}

std::string SerialInfo::GetDescription() const {
  return description_;
}

void SerialInfo::SetDescription(const std::string& description) {
  description_ = description;
}

size_t SerialInfo::GetSeason() const {
  return season_;
}

void SerialInfo::SetSeason(size_t season) {
  season_ = season;
}

SerialInfo::episodes_t SerialInfo::GetEpisodes() const {
  return episodes_;
}

void SerialInfo::SetEpisodes(episodes_t episodes) {
  episodes_ = episodes;
}

common::Error SerialInfo::SerializeFields(json_object* deserialized) const {
  if (!IsValid()) {
    return common::make_error_inval();
  }

  json_object_object_add(deserialized, ID_FIELD, json_object_new_string(sid_.c_str()));
  json_object_object_add(deserialized, NAME_FIELD, json_object_new_string(name_.c_str()));
  const std::string url_str = icon_.spec();
  json_object_object_add(deserialized, ICON_FIELD, json_object_new_string(url_str.c_str()));
  json_object* jgroups = json_object_new_array();
  for (const auto group : groups_) {
    json_object* jgroup = json_object_new_string(group.c_str());
    json_object_array_add(jgroups, jgroup);
  }
  json_object_object_add(deserialized, GROUPS_FIELD, jgroups);
  json_object_object_add(deserialized, DESCRIPTION_FIELD, json_object_new_string(description_.c_str()));
  json_object_object_add(deserialized, SEASON_FIELD, json_object_new_int64(season_));

  json_object* jepisodes = json_object_new_array();
  for (const auto episode : episodes_) {
    json_object* jepisode = json_object_new_string(episode.c_str());
    json_object_array_add(jepisodes, jepisode);
  }
  json_object_object_add(deserialized, EPISODES_FIELD, jepisodes);
  json_object_object_add(deserialized, VIEW_COUNT_FIELD, json_object_new_int(view_count_));

  return common::Error();
}

common::Error SerialInfo::DoDeSerialize(json_object* serialized) {
  SerialInfo result;
  json_object* jsid = nullptr;
  json_bool jsid_exists = json_object_object_get_ex(serialized, ID_FIELD, &jsid);
  if (!jsid_exists) {
    return common::make_error_inval();
  }
  result.sid_ = json_object_get_string(jsid);

  json_object* jname = nullptr;
  json_bool jname_exists = json_object_object_get_ex(serialized, NAME_FIELD, &jname);
  if (!jname_exists) {
    result.name_ = json_object_get_string(jname);
  }

  json_object* jicon = nullptr;
  json_bool jicon_exists = json_object_object_get_ex(serialized, ICON_FIELD, &jicon);
  if (!jicon_exists) {
    result.icon_ = common::uri::GURL(json_object_get_string(jicon));
  }

  json_object* jgroup = nullptr;
  json_bool jgroup_exists = json_object_object_get_ex(serialized, GROUPS_FIELD, &jgroup);
  if (jgroup_exists) {
    size_t len = json_object_array_length(jgroup);
    for (size_t i = 0; i < len; ++i) {
      json_object* jpart = json_object_array_get_idx(jgroup, i);
      result.groups_.push_back(json_object_get_string(jpart));
    }
  }

  json_object* jdescription = nullptr;
  json_bool jdescription_exists = json_object_object_get_ex(serialized, DESCRIPTION_FIELD, &jdescription);
  if (!jdescription_exists) {
    result.description_ = json_object_get_boolean(jdescription);
  }

  json_object* jseason = nullptr;
  json_bool jseason_exists = json_object_object_get_ex(serialized, SEASON_FIELD, &jseason);
  if (!jseason_exists) {
    result.season_ = json_object_get_int64(jseason);
  }

  json_object* jparts = nullptr;
  json_bool jparts_exists = json_object_object_get_ex(serialized, EPISODES_FIELD, &jparts);
  if (jparts_exists) {
    size_t len = json_object_array_length(jparts);
    for (size_t i = 0; i < len; ++i) {
      json_object* jpart = json_object_array_get_idx(jparts, i);
      result.episodes_.push_back(json_object_get_string(jpart));
    }
  }

  json_object* jview = nullptr;
  json_bool jview_exists = json_object_object_get_ex(serialized, VIEW_COUNT_FIELD, &jview);
  if (jview_exists) {
    result.view_count_ = json_object_get_int(jview);
  }

  if (!result.IsValid()) {
    return common::make_error_inval();
  }

  *this = result;
  return common::Error();
}

bool SerialInfo::Equals(const SerialInfo& url) const {
  return sid_ == url.sid_ && name_ == url.name_ && icon_ == url.icon_ && groups_ == url.groups_ &&
         description_ == url.description_ && season_ == url.season_ && episodes_ == url.episodes_;
}

}  // namespace commands_info
}  // namespace fastotv

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

#include <fastotv/commands_info/epg_info.h>

/*
<channel id="id">
  <display-name lang="ru"></display-name>
  <url>http://www.example.com</url>
  <icon src="http://example.com/x.png"/>
</channel>
*/

#define ID_FIELD "id"
#define URLS_FIELD "urls"
#define NAME_FIELD "display_name"
#define ICON_FIELD "icon"
#define PROGRAMS_FIELD "programs"

namespace fastotv {
namespace commands_info {

EpgInfo::EpgInfo() : tvg_id_(), uri_(), display_name_(), icon_src_(), programs_() {}

EpgInfo::EpgInfo(const tvg_id_t& id, const urls_t& uri, const std::string& name)
    : tvg_id_(id), uri_(uri), display_name_(name), icon_src_(), programs_() {}

bool EpgInfo::IsValid() const {
  return !uri_.empty() && !display_name_.empty();
}

bool EpgInfo::FindProgrammeByTime(timestamp_t time, ProgrammeInfo* inf) const {
  if (!inf || !IsValid()) {
    return false;
  }

  for (size_t i = 0; i < programs_.size(); ++i) {
    ProgrammeInfo pr = programs_[i];
    if (time >= pr.GetStart() && time <= pr.GetStop()) {
      *inf = pr;
      return true;
    }
  }

  return false;
}

void EpgInfo::SetUrls(const urls_t& url) {
  uri_ = url;
}

EpgInfo::urls_t EpgInfo::GetUrls() const {
  return uri_;
}

void EpgInfo::SetDisplayName(const std::string& name) {
  display_name_ = name;
}

std::string EpgInfo::GetDisplayName() const {
  return display_name_;
}

void EpgInfo::SetTvgID(const tvg_id_t& ch) {
  tvg_id_ = ch;
}

EpgInfo::tvg_id_t EpgInfo::GetTvgID() const {
  return tvg_id_;
}

void EpgInfo::SetIconUrl(const url_t& url) {
  icon_src_ = url;
}

void EpgInfo::SetPrograms(const programs_t& progs) {
  programs_ = progs;
}

EpgInfo::programs_t EpgInfo::GetPrograms() const {
  return programs_;
}

void EpgInfo::ClearPrograms() {
  programs_.clear();
}

EpgInfo::url_t EpgInfo::GetIconUrl() const {
  return icon_src_;
}

common::Error EpgInfo::SerializeFields(json_object* deserialized) const {
  if (!IsValid()) {
    return common::make_error_inval();
  }

  ignore_result(SetStringField(deserialized, ID_FIELD, tvg_id_));
  ignore_result(SetStringField(deserialized, NAME_FIELD, display_name_));
  const std::string icon_url_str = icon_src_.spec();
  ignore_result(SetStringField(deserialized, ICON_FIELD, icon_url_str));

  json_object* jurls = json_object_new_array();
  for (const auto url : uri_) {
    std::string url_str = url.spec();
    json_object* jurl = json_object_new_string(url_str.c_str());
    json_object_array_add(jurls, jurl);
  }
  ignore_result(SetArrayField(deserialized, URLS_FIELD, jurls));

  json_object* jprograms = json_object_new_array();
  for (ProgrammeInfo prog : programs_) {
    json_object* jprog = nullptr;
    common::Error err = prog.Serialize(&jprog);
    if (err) {
      continue;
    }
    json_object_array_add(jprograms, jprog);
  }
  ignore_result(SetArrayField(deserialized, PROGRAMS_FIELD, jprograms));
  return common::Error();
}

common::Error EpgInfo::DoDeSerialize(json_object* serialized) {
  stream_id_t id;
  ignore_result(GetStringField(serialized, ID_FIELD, &id));

  json_object* jurls = nullptr;
  urls_t urls;
  size_t len;
  common::Error err = GetArrayField(serialized, URLS_FIELD, &jurls, &len);
  if (!err) {
    for (size_t i = 0; i < len; ++i) {
      json_object* jurl = json_object_array_get_idx(jurls, i);
      const std::string url_str = json_object_get_string(jurl);
      url_t url(url_str);
      if (url.is_valid()) {
        urls.push_back(url);
      }
    }
  }

  std::string name;
  err = GetStringField(serialized, NAME_FIELD, &name);
  if (err) {
    return common::make_error_inval();
  }

  if (name.empty()) {
    return common::make_error_inval();
  }

  EpgInfo url(id, urls, name);
  if (!url.IsValid()) {
    return common::make_error_inval();
  }

  std::string url_icon;
  err = GetStringField(serialized, ICON_FIELD, &url_icon);
  if (!err) {
    url.icon_src_ = url_t(url_icon);
  }

  json_object* jprogs;
  err = GetArrayField(serialized, PROGRAMS_FIELD, &jprogs, &len);
  if (!err) {
    programs_t progs;
    for (size_t i = 0; i < len; ++i) {
      json_object* jprog = json_object_array_get_idx(jprogs, i);
      ProgrammeInfo prog;
      err = prog.DeSerialize(jprog);
      if (err) {
        continue;
      }
      progs.push_back(prog);
    }
    url.programs_ = progs;
  }

  *this = url;
  return common::Error();
}

bool EpgInfo::Equals(const EpgInfo& url) const {
  return tvg_id_ == url.tvg_id_ && uri_ == url.uri_ && display_name_ == url.display_name_;
}

}  // namespace commands_info
}  // namespace fastotv

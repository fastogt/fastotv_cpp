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

#include <fastotv/commands_info/stream_base_info.h>

#define ID_FIELD "id"
#define GROUPS_FIELD "groups"
#define IARC_FIELD "iarc"
#define VIDEO_ENABLE_FIELD "video"
#define AUDIO_ENABLE_FIELD "audio"
#define FAVORITE_FIELD "favorite"
#define RECENT_FIELD "recent"
#define INTERRUPT_TIME_FIELD "interrupt_time"
#define PARTS_FIELD "parts"
#define VIEW_COUNT_FIELD "view_count"
#define LOCKED_FIELD "locked"
#define META_FIELD "meta"
#define CREATED_DATE "created_date"

namespace fastotv {
namespace commands_info {

StreamBaseInfo::StreamBaseInfo()
    : stream_id_(kInvalidStreamId),
      groups_(),
      iarc_(DEFAULT_IARC),
      view_count_(0),
      favorite_(false),
      recent_(0),
      interruption_time_(0),
      enable_audio_(true),
      enable_video_(true),
      parts_(),
      locked_(false),
      meta_urls_(),
      created_date_(0) {}

StreamBaseInfo::StreamBaseInfo(const stream_id_t& sid,
                               const groups_t& groups,
                               iarc_t iarc,
                               bool favorite,
                               timestamp_t recent,
                               timestamp_t interruption_time,
                               bool enable_audio,
                               bool enable_video,
                               const parts_t& parts,
                               view_count_t view,
                               bool locked,
                               const meta_urls_t& urls,
                               timestamp_t created_date)
    : stream_id_(sid),
      groups_(groups),
      iarc_(iarc),
      view_count_(view),
      favorite_(favorite),
      recent_(recent),
      interruption_time_(interruption_time),
      enable_audio_(enable_audio),
      enable_video_(enable_video),
      parts_(parts),
      locked_(locked),
      meta_urls_(urls),
      created_date_(created_date) {}

bool StreamBaseInfo::IsValid() const {
  return stream_id_ != kInvalidStreamId;
}

void StreamBaseInfo::SetCreatedDate(timestamp_t date) {
  created_date_ = date;
}

timestamp_t StreamBaseInfo::GetCreatedDate() const {
  return created_date_;
}

stream_id_t StreamBaseInfo::GetStreamID() const {
  return stream_id_;
}

void StreamBaseInfo::SetStreamID(const stream_id_t& sid) {
  stream_id_ = sid;
}

StreamBaseInfo::groups_t StreamBaseInfo::GetGroups() const {
  return groups_;
}

void StreamBaseInfo::SetGroups(const groups_t& groups) {
  groups_ = groups;
}

StreamBaseInfo::iarc_t StreamBaseInfo::GetIARC() const {
  return iarc_;
}

void StreamBaseInfo::SetIARC(iarc_t iarc) {
  iarc_ = iarc;
}

StreamBaseInfo::view_count_t StreamBaseInfo::GetViewCount() const {
  return view_count_;
}

void StreamBaseInfo::SetViewCount(view_count_t view) {
  view_count_ = view;
}

fastotv::timestamp_t StreamBaseInfo::GetRecent() const {
  return recent_;
}

void StreamBaseInfo::SetRecent(fastotv::timestamp_t rec) {
  recent_ = rec;
}

bool StreamBaseInfo::GetFavorite() const {
  return favorite_;
}

void StreamBaseInfo::SetFavorite(bool fav) {
  favorite_ = fav;
}

timestamp_t StreamBaseInfo::GetInterruptionTime() const {
  return interruption_time_;
}

void StreamBaseInfo::SetInterruptionTime(timestamp_t interruption_time) {
  interruption_time_ = interruption_time;
}

bool StreamBaseInfo::IsEnableAudio() const {
  return enable_audio_;
}

bool StreamBaseInfo::IsEnableVideo() const {
  return enable_video_;
}

StreamBaseInfo::parts_t StreamBaseInfo::GetParts() const {
  return parts_;
}

void StreamBaseInfo::SetParts(const parts_t& parts) {
  parts_ = parts;
}

bool StreamBaseInfo::GetLocked() const {
  return locked_;
}

void StreamBaseInfo::SetLocked(bool locked) {
  locked_ = locked;
}

StreamBaseInfo::meta_urls_t StreamBaseInfo::GetMetaUrls() const {
  return meta_urls_;
}

void StreamBaseInfo::SetMetaUrls(const meta_urls_t& urls) {
  meta_urls_ = urls;
}

common::Error StreamBaseInfo::SerializeFields(json_object* deserialized) const {
  if (!IsValid()) {
    return common::make_error_inval();
  }

  json_object* jgroups = json_object_new_array();
  for (const auto group : groups_) {
    json_object* jgroup = json_object_new_string(group.c_str());
    json_object_array_add(jgroups, jgroup);
  }

  ignore_result(SetStringField(deserialized, ID_FIELD, stream_id_));
  ignore_result(SetArrayField(deserialized, GROUPS_FIELD, jgroups));
  ignore_result(SetIntField(deserialized, IARC_FIELD, iarc_));
  ignore_result(SetBoolField(deserialized, FAVORITE_FIELD, favorite_));
  ignore_result(SetInt64Field(deserialized, RECENT_FIELD, recent_));
  ignore_result(SetInt64Field(deserialized, INTERRUPT_TIME_FIELD, interruption_time_));
  ignore_result(SetBoolField(deserialized, AUDIO_ENABLE_FIELD, enable_audio_));
  ignore_result(SetBoolField(deserialized, VIDEO_ENABLE_FIELD, enable_video_));
  ignore_result(SetIntField(deserialized, VIEW_COUNT_FIELD, view_count_));
  ignore_result(SetBoolField(deserialized, LOCKED_FIELD, locked_));

  json_object* jparts = json_object_new_array();
  for (const auto part : parts_) {
    json_object* jpart = json_object_new_string(part.c_str());
    json_object_array_add(jparts, jpart);
  }
  ignore_result(SetArrayField(deserialized, PARTS_FIELD, jparts));

  json_object* jmeta = nullptr;
  common::Error err = meta_urls_.Serialize(&jmeta);
  if (!err) {
    ignore_result(SetObjectField(deserialized, META_FIELD, jmeta));
  }

  ignore_result(SetInt64Field(deserialized, CREATED_DATE, created_date_));
  return common::Error();
}

common::Error StreamBaseInfo::DoDeSerialize(json_object* serialized) {
  stream_id_t sid;
  common::Error err = GetStringField(serialized, ID_FIELD, &sid);
  if (err) {
    return common::make_error_inval();
  }

  // optional
  int iart = DEFAULT_IARC;
  ignore_result(GetIntField(serialized, IARC_FIELD, &iart));

  bool favorite = false;
  ignore_result(GetBoolField(serialized, FAVORITE_FIELD, &favorite));

  timestamp_t recent = 0;
  ignore_result(GetInt64Field(serialized, RECENT_FIELD, &recent));

  timestamp_t interruption_time = 0;
  ignore_result(GetInt64Field(serialized, INTERRUPT_TIME_FIELD, &interruption_time));

  bool enable_audio = true;
  ignore_result(GetBoolField(serialized, AUDIO_ENABLE_FIELD, &enable_audio));

  bool enable_video = true;
  ignore_result(GetBoolField(serialized, VIDEO_ENABLE_FIELD, &enable_video));

  int view = 0;
  ignore_result(GetIntField(serialized, VIEW_COUNT_FIELD, &view));

  bool locked = false;
  ignore_result(GetBoolField(serialized, LOCKED_FIELD, &locked));

  groups_t groups;
  size_t len;
  json_object* jgroup;
  err = GetArrayField(serialized, GROUPS_FIELD, &jgroup, &len);
  if (!err) {
    for (size_t i = 0; i < len; ++i) {
      json_object* jpart = json_object_array_get_idx(jgroup, i);
      groups.push_back(json_object_get_string(jpart));
    }
  }

  parts_t parts;
  json_object* jparts = nullptr;
  err = GetArrayField(serialized, PARTS_FIELD, &jparts, &len);
  if (!err) {
    for (size_t i = 0; i < len; ++i) {
      json_object* jpart = json_object_array_get_idx(jparts, i);
      parts.push_back(json_object_get_string(jpart));
    }
  }

  meta_urls_t meta;
  json_object* jmeta = nullptr;
  err = GetArrayField(serialized, META_FIELD, &jmeta, &len);
  if (!err) {
    ignore_result(meta.DeSerialize(jmeta));
  }

  timestamp_t created_date = 0;
  ignore_result(GetInt64Field(serialized, CREATED_DATE, &created_date));

  *this = StreamBaseInfo(sid, groups, iart, favorite, recent, interruption_time, enable_audio, enable_video, parts,
                         view, locked, meta, created_date);
  return common::Error();
}

bool StreamBaseInfo::Equals(const StreamBaseInfo& url) const {
  return stream_id_ == url.stream_id_ && groups_ == url.groups_ && iarc_ == url.iarc_ &&
         view_count_ == url.view_count_ && favorite_ == url.favorite_ && recent_ == url.recent_ &&
         interruption_time_ == url.interruption_time_ && enable_audio_ == url.enable_audio_ &&
         enable_video_ == url.enable_video_ && parts_ == url.parts_ && locked_ == url.locked_ &&
         meta_urls_ == url.meta_urls_;
}

}  // namespace commands_info
}  // namespace fastotv

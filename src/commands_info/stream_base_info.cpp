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

#include <fastotv/commands_info/stream_base_info.h>

#define CHANNEL_INFO_ID_FIELD "id"
#define CHANNEL_INFO_GROUP_FIELD "group"
#define CHANNEL_INFO_IARC_FIELD "iarc"
#define CHANNEL_INFO_VIDEO_ENABLE_FIELD "video"
#define CHANNEL_INFO_AUDIO_ENABLE_FIELD "audio"
#define CHANNEL_INFO_FAVORITE_FIELD "favorite"
#define CHANNEL_INFO_RECENT_FIELD "recent"
#define CHANNEL_INFO_INTERRUPT_TIME_FIELD "interrupt_time"
#define CHANNEL_INFO_PARTS_FIELD "parts"
#define CHANNEL_INFO_VIEW_COUNT_FIELD "view_count"

namespace fastotv {
namespace commands_info {

StreamBaseInfo::StreamBaseInfo()
    : stream_id_(invalid_stream_id),
      group_(),
      iarc_(DEFAULT_IARC),
      favorite_(false),
      recent_(0),
      interruption_time_(0),
      enable_audio_(true),
      enable_video_(true),
      parts_(),
      view_count_(0) {}

StreamBaseInfo::StreamBaseInfo(stream_id_t sid,
                               const std::string& group,
                               fastotv::commands_info::StreamBaseInfo::iarc_t iarc,
                               bool favorite,
                               timestamp_t recent,
                               timestamp_t interruption_time,
                               bool enable_audio,
                               bool enable_video,
                               const parts_t& parts,
                               fastotv::commands_info::StreamBaseInfo::view_count_t view)
    : stream_id_(sid),
      group_(group),
      iarc_(iarc),
      favorite_(favorite),
      recent_(recent),
      interruption_time_(interruption_time),
      enable_audio_(enable_audio),
      enable_video_(enable_video),
      parts_(parts),
      view_count_(view) {}

bool StreamBaseInfo::IsValid() const {
  return stream_id_ != invalid_stream_id;
}

stream_id_t StreamBaseInfo::GetStreamID() const {
  return stream_id_;
}

void StreamBaseInfo::SetStreamID(const stream_id_t sid) {
  stream_id_ = sid;
}

std::string StreamBaseInfo::GetGroup() const {
  return group_;
}

void StreamBaseInfo::SetGroup(const std::string& group) {
  group_ = group;
}

StreamBaseInfo::iarc_t StreamBaseInfo::GetIARC() const {
  return iarc_;
}

void StreamBaseInfo::SetIARC(iarc_t iarc) {
  iarc_ = iarc;
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

common::Error StreamBaseInfo::SerializeFields(json_object* deserialized) const {
  if (!IsValid()) {
    return common::make_error_inval();
  }

  json_object_object_add(deserialized, CHANNEL_INFO_ID_FIELD, json_object_new_string(stream_id_.c_str()));
  json_object_object_add(deserialized, CHANNEL_INFO_GROUP_FIELD, json_object_new_string(group_.c_str()));
  json_object_object_add(deserialized, CHANNEL_INFO_IARC_FIELD, json_object_new_int(iarc_));
  json_object_object_add(deserialized, CHANNEL_INFO_FAVORITE_FIELD, json_object_new_boolean(favorite_));
  json_object_object_add(deserialized, CHANNEL_INFO_RECENT_FIELD, json_object_new_int64(recent_));
  json_object_object_add(deserialized, CHANNEL_INFO_INTERRUPT_TIME_FIELD, json_object_new_int64(interruption_time_));
  json_object_object_add(deserialized, CHANNEL_INFO_AUDIO_ENABLE_FIELD, json_object_new_boolean(enable_audio_));
  json_object_object_add(deserialized, CHANNEL_INFO_VIDEO_ENABLE_FIELD, json_object_new_boolean(enable_video_));
  json_object_object_add(deserialized, CHANNEL_INFO_VIEW_COUNT_FIELD, json_object_new_int(view_count_));

  json_object* jparts = json_object_new_array();
  for (const auto part : parts_) {
    json_object* jpart = json_object_new_string(part.c_str());
    json_object_array_add(jparts, jpart);
  }
  json_object_object_add(deserialized, CHANNEL_INFO_PARTS_FIELD, jparts);
  return common::Error();
}

common::Error StreamBaseInfo::DoDeSerialize(json_object* serialized) {
  stream_id_t sid;
  json_object* jsid = nullptr;
  json_bool jsid_exists = json_object_object_get_ex(serialized, CHANNEL_INFO_ID_FIELD, &jsid);
  if (!jsid_exists) {
    return common::make_error_inval();
  }
  sid = json_object_get_string(jsid);

  std::string group;
  json_object* jgroup = nullptr;
  json_bool jgroup_exists = json_object_object_get_ex(serialized, CHANNEL_INFO_GROUP_FIELD, &jgroup);
  if (jgroup_exists) {
    group = json_object_get_string(jgroup);
  }

  iarc_t iart = DEFAULT_IARC;
  json_object* jiart = nullptr;
  json_bool jiart_exists = json_object_object_get_ex(serialized, CHANNEL_INFO_IARC_FIELD, &jgroup);
  if (jiart_exists) {
    iart = json_object_get_int(jiart);
  }

  bool favorite = false;
  json_object* jfavorite = nullptr;
  json_bool jfavorite_exists = json_object_object_get_ex(serialized, CHANNEL_INFO_AUDIO_ENABLE_FIELD, &jfavorite);
  if (jfavorite_exists) {
    favorite = json_object_get_boolean(jfavorite);
  }

  timestamp_t recent = false;
  json_object* jrecent = nullptr;
  json_bool jrecent_exists = json_object_object_get_ex(serialized, CHANNEL_INFO_RECENT_FIELD, &jrecent);
  if (jrecent_exists) {
    recent = json_object_get_int64(jrecent);
  }

  timestamp_t interruption_time = 0;
  json_object* jinterruption_time = nullptr;
  json_bool jinterruption_time_exists =
      json_object_object_get_ex(serialized, CHANNEL_INFO_INTERRUPT_TIME_FIELD, &jinterruption_time);
  if (jinterruption_time_exists) {
    interruption_time = json_object_get_int64(jinterruption_time);
  }

  bool enable_audio = true;
  json_object* jenable_audio = nullptr;
  json_bool jenable_audio_exists =
      json_object_object_get_ex(serialized, CHANNEL_INFO_AUDIO_ENABLE_FIELD, &jenable_audio);
  if (jenable_audio_exists) {
    enable_audio = json_object_get_boolean(jenable_audio);
  }

  bool enable_video = true;
  json_object* jdisable_video = nullptr;
  json_bool jdisable_video_exists =
      json_object_object_get_ex(serialized, CHANNEL_INFO_VIDEO_ENABLE_FIELD, &jdisable_video);
  if (jdisable_video_exists) {
    enable_video = json_object_get_boolean(jdisable_video);
  }

  parts_t parts;
  json_object* jparts = nullptr;
  json_bool jparts_exists = json_object_object_get_ex(serialized, CHANNEL_INFO_PARTS_FIELD, &jparts);
  if (jparts_exists) {
    size_t len = json_object_array_length(jparts);
    for (size_t i = 0; i < len; ++i) {
      json_object* jpart = json_object_array_get_idx(jparts, i);
      parts.push_back(json_object_get_string(jpart));
    }
  }

  view_count_t view;
  json_object* jview = nullptr;
  json_bool jview_exists = json_object_object_get_ex(serialized, CHANNEL_INFO_VIEW_COUNT_FIELD, &jview);
  if (jview_exists) {
    view = json_object_get_int(jview);
  }

  StreamBaseInfo url(sid, group, iart, favorite, recent, interruption_time, enable_audio, enable_video, parts, view);
  if (!url.IsValid()) {
    return common::make_error_inval();
  }

  *this = url;
  return common::Error();
}

bool StreamBaseInfo::Equals(const StreamBaseInfo& url) const {
  return stream_id_ == url.stream_id_ && enable_audio_ == url.enable_audio_ && enable_video_ == url.enable_video_;
}

}  // namespace commands_info
}  // namespace fastotv

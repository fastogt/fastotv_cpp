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

#include <fastotv/commands_info/recent_stream_time_info.h>

#define ID_FIELD "id"
#define TIME_FIELD "time"

namespace fastotv {
namespace commands_info {

RecentStreamTimeInfo::RecentStreamTimeInfo() : id_(invalid_stream_id), timestamp_utc_(0) {}

RecentStreamTimeInfo::RecentStreamTimeInfo(const stream_id_t& channel, timestamp_t time)
    : id_(channel), timestamp_utc_(time) {}

bool RecentStreamTimeInfo::IsValid() const {
  return id_ != invalid_stream_id;
}

common::Error RecentStreamTimeInfo::SerializeFields(json_object* deserialized) const {
  if (!IsValid()) {
    return common::make_error_inval();
  }

  json_object_object_add(deserialized, ID_FIELD, json_object_new_string(id_.c_str()));
  json_object_object_add(deserialized, TIME_FIELD, json_object_new_boolean(timestamp_utc_));
  return common::Error();
}

common::Error RecentStreamTimeInfo::DoDeSerialize(json_object* serialized) {
  json_object* jchannel = nullptr;
  json_bool jchannel_exists = json_object_object_get_ex(serialized, ID_FIELD, &jchannel);
  if (!jchannel_exists) {
    return common::make_error_inval();
  }

  json_object* jtime = nullptr;
  json_bool jtime_exists = json_object_object_get_ex(serialized, TIME_FIELD, &jtime);
  if (!jtime_exists) {
    return common::make_error_inval();
  }

  RecentStreamTimeInfo prog(json_object_get_string(jchannel), json_object_get_int64(jtime));
  *this = prog;
  return common::Error();
}

void RecentStreamTimeInfo::SetChannel(const stream_id_t& channel) {
  id_ = channel;
}

stream_id_t RecentStreamTimeInfo::GetChannel() const {
  return id_;
}

void RecentStreamTimeInfo::SetTimestamp(timestamp_t time) {
  timestamp_utc_ = time;
}

timestamp_t RecentStreamTimeInfo::GetTimestamp() const {
  return timestamp_utc_;
}

bool RecentStreamTimeInfo::Equals(const RecentStreamTimeInfo& prog) const {
  return id_ == prog.id_ && timestamp_utc_ == prog.timestamp_utc_;
}

}  // namespace commands_info
}  // namespace fastotv

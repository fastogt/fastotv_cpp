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

#include <fastotv/commands_info/interrupt_stream_time_info.h>

#define INTERRUPT_STREAM_TIME_INFO_ID_FIELD "id"
#define INTERRUPT_STREAM_TIME_INFO_TIME_FIELD "time"

namespace fastotv {
namespace commands_info {

InterruptStreamTimeInfo::InterruptStreamTimeInfo() : id_(invalid_stream_id), time_(0) {}

InterruptStreamTimeInfo::InterruptStreamTimeInfo(stream_id_t channel, timestamp_t time) : id_(channel), time_(time) {}

bool InterruptStreamTimeInfo::IsValid() const {
  return id_ != invalid_stream_id;
}

common::Error InterruptStreamTimeInfo::SerializeFields(json_object* deserialized) const {
  if (!IsValid()) {
    return common::make_error_inval();
  }

  json_object_object_add(deserialized, INTERRUPT_STREAM_TIME_INFO_ID_FIELD, json_object_new_string(id_.c_str()));
  json_object_object_add(deserialized, INTERRUPT_STREAM_TIME_INFO_TIME_FIELD, json_object_new_boolean(time_));
  return common::Error();
}

common::Error InterruptStreamTimeInfo::DoDeSerialize(json_object* serialized) {
  json_object* jchannel = nullptr;
  json_bool jchannel_exists = json_object_object_get_ex(serialized, INTERRUPT_STREAM_TIME_INFO_ID_FIELD, &jchannel);
  if (!jchannel_exists) {
    return common::make_error_inval();
  }

  json_object* jtime = nullptr;
  json_bool jtime_exists = json_object_object_get_ex(serialized, INTERRUPT_STREAM_TIME_INFO_TIME_FIELD, &jtime);
  if (!jtime_exists) {
    return common::make_error_inval();
  }

  InterruptStreamTimeInfo prog(json_object_get_string(jchannel), json_object_get_int64(jtime));
  *this = prog;
  return common::Error();
}

void InterruptStreamTimeInfo::SetChannel(stream_id_t channel) {
  id_ = channel;
}

stream_id_t InterruptStreamTimeInfo::GetChannel() const {
  return id_;
}

void InterruptStreamTimeInfo::SetTime(timestamp_t time) {
  time_ = time;
}

timestamp_t InterruptStreamTimeInfo::GetTime() const {
  return time_;
}

bool InterruptStreamTimeInfo::Equals(const InterruptStreamTimeInfo& prog) const {
  return id_ == prog.id_ && time_ == prog.time_;
}

}  // namespace commands_info
}  // namespace fastotv

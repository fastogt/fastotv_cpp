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

#include <fastotv/commands_info/interrupt_stream_time_info.h>

#define ID_FIELD "id"
#define TIME_FIELD "time"

namespace fastotv {
namespace commands_info {

InterruptStreamTimeInfo::InterruptStreamTimeInfo() : id_(kInvalidStreamId), time_(0) {}

InterruptStreamTimeInfo::InterruptStreamTimeInfo(const stream_id_t& channel, timestamp_t time)
    : id_(channel), time_(time) {}

bool InterruptStreamTimeInfo::IsValid() const {
  return id_ != kInvalidStreamId;
}

common::Error InterruptStreamTimeInfo::SerializeFields(json_object* deserialized) const {
  if (!IsValid()) {
    return common::make_error_inval();
  }

  ignore_result(SetStringField(deserialized, ID_FIELD, id_));
  ignore_result(SetInt64Field(deserialized, TIME_FIELD, time_));
  return common::Error();
}

common::Error InterruptStreamTimeInfo::DoDeSerialize(json_object* serialized) {
  stream_id_t channel;
  common::Error err = GetStringField(serialized, ID_FIELD, &channel);
  if (err) {
    return err;
  }

  int64_t time;
  err = GetInt64Field(serialized, TIME_FIELD, &time);
  if (err) {
    return err;
  }

  *this = InterruptStreamTimeInfo(channel, time);
  return common::Error();
}

void InterruptStreamTimeInfo::SetChannel(const stream_id_t& channel) {
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

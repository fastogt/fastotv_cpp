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

#include <fastotv/commands_info/catchup_info.h>

#define CATCHUP_INFO_START_FIELD "start"
#define CATCHUP_INFO_STOP_FIELD "stop"

namespace fastotv {
namespace commands_info {

CatchupInfo::CatchupInfo() : base_class(), start_(0), stop_(0) {}

CatchupInfo::CatchupInfo(stream_id_t sid,
                         const std::string& group,
                         iarc_t iarc,
                         bool favorite,
                         timestamp_t recent,
                         timestamp_t interruption_time,
                         const EpgInfo& epg,
                         bool enable_audio,
                         bool enable_video,
                         const parts_t& parts,
                         timestamp_t start,
                         timestamp_t stop)
    : base_class(sid, group, iarc, favorite, recent, interruption_time, epg, enable_audio, enable_video, parts),
      start_(start),
      stop_(stop) {}

void CatchupInfo::SetStart(timestamp_t start) {
  start_ = start;
}

timestamp_t CatchupInfo::GetStart() const {
  return start_;
}

void CatchupInfo::SetStop(timestamp_t stop) {
  stop_ = stop;
}

timestamp_t CatchupInfo::GetStop() const {
  return stop_;
}

bool CatchupInfo::IsValid() const {
  return base_class::IsValid() && start_ != 0 && stop_ != 0;
}

common::Error CatchupInfo::SerializeFields(json_object* deserialized) const {
  if (!IsValid()) {
    return common::make_error_inval();
  }

  common::Error err = base_class::SerializeFields(deserialized);
  if (err) {
    return err;
  }

  json_object_object_add(deserialized, CATCHUP_INFO_START_FIELD, json_object_new_int64(start_));
  json_object_object_add(deserialized, CATCHUP_INFO_STOP_FIELD, json_object_new_int64(stop_));
  return common::Error();
}

common::Error CatchupInfo::DoDeSerialize(json_object* serialized) {
  CatchupInfo inf;
  common::Error err = inf.base_class::DoDeSerialize(serialized);
  if (err) {
    return err;
  }

  json_object* jstart = nullptr;
  json_bool jstart_exists = json_object_object_get_ex(serialized, CATCHUP_INFO_START_FIELD, &jstart);
  if (!jstart_exists) {
    return common::make_error_inval();
  }
  inf.start_ = json_object_get_int64(jstart);

  json_object* jstop = nullptr;
  json_bool jstop_exists = json_object_object_get_ex(serialized, CATCHUP_INFO_STOP_FIELD, &jstop);
  if (!jstop_exists) {
    return common::make_error_inval();
  }
  inf.stop_ = json_object_get_int64(jstop);

  *this = inf;
  return common::Error();
}

bool CatchupInfo::Equals(const CatchupInfo& info) const {
  return base_class::Equals(info) && start_ == info.start_ && stop_ == info.stop_;
}

}  // namespace commands_info
}  // namespace fastotv

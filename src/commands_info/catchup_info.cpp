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

#include <fastotv/commands_info/catchup_info.h>

#define START_FIELD "start"
#define STOP_FIELD "stop"

namespace fastotv {
namespace commands_info {

CatchupInfo::CatchupInfo() : base_class(), start_(0), stop_(0) {}

CatchupInfo::CatchupInfo(const stream_id_t& sid,
                         const groups_t& groups,
                         iarc_t iarc,
                         bool favorite,
                         timestamp_t recent,
                         timestamp_t interruption_time,
                         const EpgInfo& epg,
                         bool enable_audio,
                         bool enable_video,
                         const parts_t& parts,
                         view_count_t view,
                         bool locked,
                         const meta_urls_t& urls,
                         fastotv::timestamp_t created_date,
                         timestamp_t start,
                         timestamp_t stop)
    : base_class(sid,
                 groups,
                 iarc,
                 favorite,
                 recent,
                 interruption_time,
                 epg,
                 enable_audio,
                 enable_video,
                 parts,
                 view,
                 locked,
                 urls,
                 created_date,
                 false),
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

  ignore_result(SetInt64Field(deserialized, START_FIELD, start_));
  ignore_result(SetInt64Field(deserialized, STOP_FIELD, stop_));
  return common::Error();
}

common::Error CatchupInfo::DoDeSerialize(json_object* serialized) {
  CatchupInfo inf;
  common::Error err = inf.base_class::DoDeSerialize(serialized);
  if (err) {
    return err;
  }

  int64_t start;
  err = GetInt64Field(serialized, START_FIELD, &start);
  if (err) {
    return err;
  }
  inf.start_ = start;

  int64_t stop;
  err = GetInt64Field(serialized, STOP_FIELD, &stop);
  if (err) {
    return err;
  }
  inf.stop_ = stop;

  *this = inf;
  return common::Error();
}

bool CatchupInfo::Equals(const CatchupInfo& info) const {
  return base_class::Equals(info) && start_ == info.start_ && stop_ == info.stop_;
}

}  // namespace commands_info
}  // namespace fastotv

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

#include <fastotv/commands_info/catchup_generate_info.h>

#define ID_FIELD "id"
#define TITLE_FIELD "title"
#define START_FIELD "start"
#define STOP_FIELD "stop"

#define CATCHUP_FIELD "catchup"

namespace fastotv {
namespace commands_info {

CatchupGenerateInfo::CatchupGenerateInfo() : sid_(kInvalidStreamId), title_(), start_time_(0), stop_time_(0) {}

CatchupGenerateInfo::CatchupGenerateInfo(const stream_id_t& sid,
                                         const std::string& title,
                                         timestamp_t start_time,
                                         timestamp_t stop_time)
    : sid_(sid), title_(title), start_time_(start_time), stop_time_(stop_time) {}

CatchupGenerateInfo::~CatchupGenerateInfo() {}

bool CatchupGenerateInfo::IsValid() const {
  return sid_ != kInvalidStreamId && start_time_ != 0 && stop_time_ != 0;
}

void CatchupGenerateInfo::SetStreamID(const stream_id_t& sid) {
  sid_ = sid;
}

stream_id_t CatchupGenerateInfo::GetStreamID() const {
  return sid_;
}

void CatchupGenerateInfo::SetStart(timestamp_t start) {
  start_time_ = start;
}

timestamp_t CatchupGenerateInfo::GetStart() const {
  return start_time_;
}

void CatchupGenerateInfo::SetStop(timestamp_t stop) {
  stop_time_ = stop;
}

timestamp_t CatchupGenerateInfo::GetStop() const {
  return stop_time_;
}

void CatchupGenerateInfo::SetTitle(const std::string& title) {
  title_ = title;
}

std::string CatchupGenerateInfo::GetTitle() const {
  return title_;
}

bool CatchupGenerateInfo::Equals(const CatchupGenerateInfo& inf) const {
  return sid_ == inf.sid_ && start_time_ == inf.start_time_ && stop_time_ == inf.stop_time_ && title_ == inf.title_;
}

common::Error CatchupGenerateInfo::DoDeSerialize(json_object* serialized) {
  stream_id_t cid;
  common::Error err = GetStringField(serialized, ID_FIELD, &cid);
  if (err) {
    return err;
  }

  if (cid == kInvalidStreamId) {
    return common::make_error_inval();
  }

  std::string title;
  err = GetStringField(serialized, TITLE_FIELD, &title);
  if (err) {
    return err;
  }

  int64_t start;
  err = GetInt64Field(serialized, START_FIELD, &start);
  if (err) {
    return err;
  }

  int64_t stop;
  err = GetInt64Field(serialized, STOP_FIELD, &stop);
  if (err) {
    return err;
  }

  *this = CatchupGenerateInfo(cid, title, start, stop);
  return common::Error();
}

common::Error CatchupGenerateInfo::SerializeFields(json_object* deserialized) const {
  if (!IsValid()) {
    return common::make_error_inval();
  }

  ignore_result(SetStringField(deserialized, ID_FIELD, sid_));
  ignore_result(SetStringField(deserialized, TITLE_FIELD, title_));
  ignore_result(SetInt64Field(deserialized, START_FIELD, start_time_));
  ignore_result(SetInt64Field(deserialized, STOP_FIELD, stop_time_));
  return common::Error();
}

CatchupQueueInfo::CatchupQueueInfo() : cinf_() {}

CatchupQueueInfo::CatchupQueueInfo(const CatchupInfo& info) : cinf_(info) {}

CatchupQueueInfo::~CatchupQueueInfo() {}

bool CatchupQueueInfo::IsValid() const {
  return cinf_.IsValid();
}

void CatchupQueueInfo::SetCatchup(const CatchupInfo& info) {
  cinf_ = info;
}

CatchupInfo CatchupQueueInfo::GetCatchup() const {
  return cinf_;
}

bool CatchupQueueInfo::Equals(const CatchupQueueInfo& inf) const {
  return cinf_ == inf.cinf_;
}

common::Error CatchupQueueInfo::DoDeSerialize(json_object* serialized) {
  json_object* jcid = nullptr;
  common::Error err = GetObjectField(serialized, CATCHUP_FIELD, &jcid);
  if (err) {
    return err;
  }

  CatchupInfo cid;
  err = cid.DeSerialize(jcid);
  if (err) {
    return err;
  }

  *this = CatchupQueueInfo(cid);
  return common::Error();
}

common::Error CatchupQueueInfo::SerializeFields(json_object* deserialized) const {
  if (!IsValid()) {
    return common::make_error_inval();
  }

  json_object* jobj = nullptr;
  common::Error err = cinf_.Serialize(&jobj);
  if (err) {
    return err;
  }

  ignore_result(SetObjectField(deserialized, CATCHUP_FIELD, jobj));
  return common::Error();
}

}  // namespace commands_info
}  // namespace fastotv

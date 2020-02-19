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

#include <fastotv/commands_info/catchup_generate_info.h>

#define CATCHUP_REQUEST_INFO_ID_FIELD "id"
#define CATCHUP_REQUEST_INFO_TITLE_FIELD "title"
#define CATCHUP_REQUEST_INFO_START_FIELD "start"
#define CATCHUP_REQUEST_INFO_STOP_FIELD "stop"

#define CATCHUP_RESPONSE_INFO_CATCHUP_FIELD "catchup"

namespace fastotv {
namespace commands_info {

CatchupGenerateInfo::CatchupGenerateInfo() : sid_(invalid_stream_id), title_(), start_time_(0), stop_time_(0) {}

CatchupGenerateInfo::CatchupGenerateInfo(stream_id_t sid,
                                         const std::string& title,
                                         timestamp_t start_time,
                                         timestamp_t stop_time)
    : sid_(sid), title_(title), start_time_(start_time), stop_time_(stop_time) {}

CatchupGenerateInfo::~CatchupGenerateInfo() {}

bool CatchupGenerateInfo::IsValid() const {
  return sid_ != invalid_stream_id && start_time_ != 0 && stop_time_ != 0;
}

void CatchupGenerateInfo::SetStreamID(stream_id_t sid) {
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
  return sid_ == inf.sid_ && start_time_ == inf.start_time_ && stop_time_ == inf.stop_time_;
}

common::Error CatchupGenerateInfo::DoDeSerialize(json_object* serialized) {
  CatchupGenerateInfo inf;
  json_object* jcid = nullptr;
  json_bool jcid_exists = json_object_object_get_ex(serialized, CATCHUP_REQUEST_INFO_ID_FIELD, &jcid);
  if (!jcid_exists) {
    return common::make_error_inval();
  }

  stream_id_t cid = json_object_get_string(jcid);
  if (cid == invalid_stream_id) {
    return common::make_error_inval();
  }
  inf.sid_ = cid;

  json_object* jtitle = nullptr;
  json_bool jtitle_exists = json_object_object_get_ex(serialized, CATCHUP_REQUEST_INFO_TITLE_FIELD, &jtitle);
  if (!jtitle_exists) {
    return common::make_error_inval();
  }
  inf.title_ = json_object_get_string(jtitle);

  json_object* jstart = nullptr;
  json_bool jstart_exists = json_object_object_get_ex(serialized, CATCHUP_REQUEST_INFO_START_FIELD, &jstart);
  if (!jstart_exists) {
    return common::make_error_inval();
  }
  inf.start_time_ = json_object_get_int64(jstart);

  json_object* jstop = nullptr;
  json_bool jstop_exists = json_object_object_get_ex(serialized, CATCHUP_REQUEST_INFO_STOP_FIELD, &jstop);
  if (!jstop_exists) {
    return common::make_error_inval();
  }
  inf.stop_time_ = json_object_get_int64(jstop);

  *this = inf;
  return common::Error();
}

common::Error CatchupGenerateInfo::SerializeFields(json_object* deserialized) const {
  if (!IsValid()) {
    return common::make_error_inval();
  }

  json_object_object_add(deserialized, CATCHUP_REQUEST_INFO_ID_FIELD, json_object_new_string(sid_.c_str()));
  json_object_object_add(deserialized, CATCHUP_REQUEST_INFO_TITLE_FIELD, json_object_new_string(title_.c_str()));
  json_object_object_add(deserialized, CATCHUP_REQUEST_INFO_START_FIELD, json_object_new_int64(start_time_));
  json_object_object_add(deserialized, CATCHUP_REQUEST_INFO_STOP_FIELD, json_object_new_int64(stop_time_));
  return common::Error();
}

CatchupQueueInfo::CatchupQueueInfo() : cinf_() {}

CatchupQueueInfo::CatchupQueueInfo(const fastotv::commands_info::CatchupInfo& info) : cinf_(info) {}

CatchupQueueInfo::~CatchupQueueInfo() {}

bool CatchupQueueInfo::IsValid() const {
  return cinf_.IsValid();
}

void CatchupQueueInfo::SetCatchup(const fastotv::commands_info::CatchupInfo& info) {
  cinf_ = info;
}

fastotv::commands_info::CatchupInfo CatchupQueueInfo::GetCatchup() const {
  return cinf_;
}

bool CatchupQueueInfo::Equals(const CatchupQueueInfo& inf) const {
  return cinf_ == inf.cinf_;
}

common::Error CatchupQueueInfo::DoDeSerialize(json_object* serialized) {
  CatchupQueueInfo inf;
  json_object* jcid = nullptr;
  json_bool jcid_exists = json_object_object_get_ex(serialized, CATCHUP_RESPONSE_INFO_CATCHUP_FIELD, &jcid);
  if (!jcid_exists) {
    return common::make_error_inval();
  }

  fastotv::commands_info::CatchupInfo cid;
  common::Error err = cid.DeSerialize(jcid);
  if (err) {
    return err;
  }
  inf.cinf_ = cid;

  *this = inf;
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

  json_object_object_add(deserialized, CATCHUP_RESPONSE_INFO_CATCHUP_FIELD, jobj);
  return common::Error();
}

}  // namespace commands_info
}  // namespace fastotv

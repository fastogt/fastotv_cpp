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

#include <fastotv/commands_info/runtime_channel_info.h>

#define STREAM_ID_FIELD "id"
#define WATCHERS_FIELD "watchers"

namespace fastotv {
namespace commands_info {

RuntimeChannelLiteInfo::RuntimeChannelLiteInfo() : RuntimeChannelLiteInfo(kInvalidStreamId) {}

RuntimeChannelLiteInfo::RuntimeChannelLiteInfo(const fastotv::stream_id_t& sid) : sid_(sid) {}

RuntimeChannelLiteInfo::~RuntimeChannelLiteInfo() {}

bool RuntimeChannelLiteInfo::IsValid() const {
  return sid_ != kInvalidStreamId;
}

void RuntimeChannelLiteInfo::SetStreamID(const fastotv::stream_id_t& sid) {
  sid_ = sid;
}

stream_id_t RuntimeChannelLiteInfo::GetStreamID() const {
  return sid_;
}

bool RuntimeChannelLiteInfo::Equals(const RuntimeChannelLiteInfo& inf) const {
  return sid_ == inf.sid_;
}

common::Error RuntimeChannelLiteInfo::DoDeSerialize(json_object* serialized) {
  RuntimeChannelLiteInfo inf;
  json_object* jcid = nullptr;
  json_bool jcid_exists = json_object_object_get_ex(serialized, STREAM_ID_FIELD, &jcid);
  if (!jcid_exists) {
    return common::make_error_inval();
  }

  stream_id_t cid = json_object_get_string(jcid);
  if (cid == kInvalidStreamId) {
    return common::make_error_inval();
  }
  inf.sid_ = cid;

  *this = inf;
  return common::Error();
}

common::Error RuntimeChannelLiteInfo::SerializeFields(json_object* deserialized) const {
  if (!IsValid()) {
    return common::make_error_inval();
  }

  ignore_result(SetStringField(deserialized, STREAM_ID_FIELD, sid_));
  return common::Error();
}

RuntimeChannelInfo::RuntimeChannelInfo() : base_class(), watchers_(0) {}

RuntimeChannelInfo::RuntimeChannelInfo(const stream_id_t& channel_id, size_t watchers)
    : base_class(channel_id), watchers_(watchers) {}

RuntimeChannelInfo::~RuntimeChannelInfo() {}

void RuntimeChannelInfo::SetWatchersCount(size_t count) {
  watchers_ = count;
}

size_t RuntimeChannelInfo::GetWatchersCount() const {
  return watchers_;
}

common::Error RuntimeChannelInfo::SerializeFields(json_object* deserialized) const {
  common::Error err = base_class::SerializeFields(deserialized);
  if (err) {
    return err;
  }

  ignore_result(SetInt64Field(deserialized, WATCHERS_FIELD, watchers_));
  return common::Error();
}

common::Error RuntimeChannelInfo::DoDeSerialize(json_object* serialized) {
  RuntimeChannelInfo inf;
  common::Error err = inf.base_class::DoDeSerialize(serialized);
  if (err) {
    return err;
  }

  int64_t watchers;
  err = GetInt64Field(serialized, WATCHERS_FIELD, &watchers);
  if (!err) {
    inf.watchers_ = watchers;
  }

  *this = inf;
  return common::Error();
}

bool RuntimeChannelInfo::Equals(const RuntimeChannelInfo& inf) const {
  return base_class::Equals(inf) && watchers_ == inf.watchers_;
}

}  // namespace commands_info
}  // namespace fastotv

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

#include <fastotv/commands_info/channel_info.h>

#define EPG_FIELD "epg"

namespace fastotv {
namespace commands_info {

ChannelInfo::ChannelInfo() : base_class(), epg_() {}

ChannelInfo::ChannelInfo(const stream_id_t& sid,
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
                         const meta_urls_t& urls)
    : base_class(sid,
                 groups,
                 iarc,
                 favorite,
                 recent,
                 interruption_time,
                 enable_audio,
                 enable_video,
                 parts,
                 view,
                 locked,
                 urls),
      epg_(epg) {}

bool ChannelInfo::IsValid() const {
  return base_class::IsValid() && epg_.IsValid();
}

EpgInfo ChannelInfo::GetEpg() const {
  return epg_;
}

void ChannelInfo::SetEpg(const EpgInfo& epg) {
  epg_ = epg;
}

common::Error ChannelInfo::SerializeFields(json_object* deserialized) const {
  if (!IsValid()) {
    return common::make_error_inval();
  }

  common::Error err = base_class::SerializeFields(deserialized);
  if (err) {
    return err;
  }

  json_object* jepg = nullptr;
  err = epg_.Serialize(&jepg);
  if (err) {
    return err;
  }

  ignore_result(SetObjectField(deserialized, EPG_FIELD, jepg));
  return common::Error();
}

common::Error ChannelInfo::DoDeSerialize(json_object* serialized) {
  ChannelInfo inf;
  common::Error err = inf.base_class::DoDeSerialize(serialized);
  if (err) {
    return err;
  }

  json_object* jepg = nullptr;
  err = GetObjectField(serialized, EPG_FIELD, &jepg);
  if (err) {
    return err;
  }

  EpgInfo epg;
  err = epg.DeSerialize(jepg);
  if (err) {
    return err;
  }

  inf.epg_ = epg;
  *this = inf;
  return common::Error();
}

bool ChannelInfo::Equals(const ChannelInfo& info) const {
  return base_class::Equals(info) && epg_ == info.epg_;
}

}  // namespace commands_info
}  // namespace fastotv

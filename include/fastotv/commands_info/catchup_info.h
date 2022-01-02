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

#pragma once

#include <string>

#include <fastotv/commands_info/channel_info.h>

namespace fastotv {
namespace commands_info {

class CatchupInfo : public ChannelInfo {
 public:
  typedef ChannelInfo base_class;

  CatchupInfo();
  CatchupInfo(const stream_id_t& sid,
              const groups_t& group,
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
              timestamp_t stop);

  void SetStart(timestamp_t start);
  timestamp_t GetStart() const;

  void SetStop(timestamp_t stop);
  timestamp_t GetStop() const;

  bool IsValid() const;

  bool Equals(const CatchupInfo& info) const;

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* deserialized) const override;

 private:
  timestamp_t start_;  // utc time
  timestamp_t stop_;   // utc time
};

inline bool operator==(const CatchupInfo& left, const CatchupInfo& right) {
  return left.Equals(right);
}

inline bool operator!=(const CatchupInfo& x, const CatchupInfo& y) {
  return !(x == y);
}

}  // namespace commands_info
}  // namespace fastotv

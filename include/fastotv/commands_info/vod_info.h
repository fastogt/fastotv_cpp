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

#pragma once

#include <fastotv/commands_info/movie_info.h>
#include <fastotv/commands_info/stream_base_info.h>

#include <string>

namespace fastotv {
namespace commands_info {

class VodInfo : public StreamBaseInfo {
 public:
  typedef StreamBaseInfo base_class;

  VodInfo();
  VodInfo(const stream_id_t& sid,
          const groups_t& group,
          iarc_t iarc,
          bool favorite,
          timestamp_t recent,
          timestamp_t interruption_time,
          const MovieInfo& movie,
          bool enable_audio,
          bool enable_video,
          const parts_t& parts,
          view_count_t view,
          bool locked,
          const meta_urls_t& urls,
          fastotv::timestamp_t created_date);

  bool IsValid() const;

  bool IsSerial() const;

  MovieInfo GetMovieInfo() const;
  void SetMovieInfo(const MovieInfo& movie);

  bool Equals(const VodInfo& url) const;

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* deserialized) const override;

 private:
  MovieInfo movie_;
};

inline bool operator==(const VodInfo& left, const VodInfo& right) {
  return left.Equals(right);
}

inline bool operator!=(const VodInfo& x, const VodInfo& y) {
  return !(x == y);
}

}  // namespace commands_info
}  // namespace fastotv

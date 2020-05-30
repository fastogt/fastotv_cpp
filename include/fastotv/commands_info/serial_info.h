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

#pragma once

#include <string>
#include <vector>

#include <common/serializer/json_serializer.h>

#include <fastotv/types.h>
#include <fastotv/types/meta_url.h>

namespace fastotv {
namespace commands_info {

class SerialInfo : public common::serializer::JsonSerializer<SerialInfo> {
 public:
  typedef unsigned int view_count_t;
  typedef std::vector<stream_id_t> episodes_t;
  typedef std::vector<std::string> groups_t;

  SerialInfo();
  SerialInfo(serial_id_t sid,
             const std::string& name,
             const common::uri::GURL& icon,
             groups_t groups,
             const std::string& description,
             size_t season,
             episodes_t episodes,
             view_count_t view);

  bool IsValid() const;

  serial_id_t GetSerialID() const;
  void SetSerialID(serial_id_t sid);

  std::string GetName() const;
  void SetName(const std::string& name);

  common::uri::GURL GetIcon() const;
  void SetIcon(const common::uri::GURL& icon);

  groups_t GetGroups() const;
  void SetGroups(groups_t groups);

  bool GetVisible() const;
  void SetVisible(bool visible);

  view_count_t GetViewCount() const;
  void SetViewCount(view_count_t view);

  std::string GetDescription() const;
  void SetDescription(const std::string& description);

  size_t GetSeason() const;
  void SetSeason(size_t season);

  episodes_t GetEpisodes() const;
  void SetEpisodes(episodes_t episodes);

  bool Equals(const SerialInfo& url) const;

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* deserialized) const override;

 private:
  serial_id_t sid_;
  std::string name_;
  common::uri::GURL icon_;
  groups_t groups_;
  std::string description_;
  size_t season_;
  episodes_t episodes_;
  view_count_t view_count_;
};

inline bool operator==(const SerialInfo& left, const SerialInfo& right) {
  return left.Equals(right);
}

inline bool operator!=(const SerialInfo& x, const SerialInfo& y) {
  return !(x == y);
}

}  // namespace commands_info
}  // namespace fastotv

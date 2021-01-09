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

#pragma once

#include <string>
#include <vector>

#include <common/uri/gurl.h>  // for Uri

#include <fastotv/commands_info/programme_info.h>
#include <fastotv/types.h>

namespace fastotv {
namespace commands_info {

class EpgInfo : public common::serializer::JsonSerializer<EpgInfo> {
 public:
  typedef std::vector<ProgrammeInfo> programs_t;
  typedef std::string tvg_id_t;
  typedef common::uri::GURL url_t;
  typedef std::vector<url_t> urls_t;

  EpgInfo();
  EpgInfo(const tvg_id_t& id, const urls_t& uri, const std::string& name);  // required args

  bool IsValid() const;
  bool FindProgrammeByTime(timestamp_t time, ProgrammeInfo* inf) const;

  void SetUrls(const urls_t& url);
  urls_t GetUrls() const;

  void SetDisplayName(const std::string& name);
  std::string GetDisplayName() const;

  void SetTvgID(const tvg_id_t& ch);
  tvg_id_t GetTvgID() const;

  void SetIconUrl(const url_t& url);
  url_t GetIconUrl() const;

  void SetPrograms(const programs_t& progs);
  programs_t GetPrograms() const;
  void ClearPrograms();

  bool Equals(const EpgInfo& url) const;

  static const url_t& GetUnknownIconUrl();
  static bool IsUnknownIconUrl(const url_t& url);

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* deserialized) const override;

 private:
  tvg_id_t tvg_id_;
  urls_t uri_;
  std::string display_name_;
  url_t icon_src_;
  programs_t programs_;
};

inline bool operator==(const EpgInfo& left, const EpgInfo& right) {
  return left.Equals(right);
}

inline bool operator!=(const EpgInfo& x, const EpgInfo& y) {
  return !(x == y);
}

}  // namespace commands_info
}  // namespace fastotv

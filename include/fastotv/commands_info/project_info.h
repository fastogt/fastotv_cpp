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

#include <common/serializer/json_serializer.h>

#include <fastotv/types.h>

#include <string>

namespace fastotv {
namespace commands_info {

class ProjectInfo : public common::serializer::JsonSerializer<ProjectInfo> {
 public:
  typedef common::serializer::JsonSerializer<ProjectInfo> base_class;

  ProjectInfo();
  ProjectInfo(const std::string& project, const std::string& version);

  bool IsValid() const;

  std::string GetProject() const;
  void SetProject(const std::string& project);

  std::string GetVersion() const;
  void SetVersion(const std::string& version);

  bool Equals(const ProjectInfo& proj) const;

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* deserialized) const override;

 private:
  std::string project_;
  std::string version_;
};

inline bool operator==(const ProjectInfo& lhs, const ProjectInfo& rhs) {
  return lhs.Equals(rhs);
}

inline bool operator!=(const ProjectInfo& x, const ProjectInfo& y) {
  return !(x == y);
}

class LicenseProjectInfo : public ProjectInfo {
 public:
  typedef ProjectInfo base_class;

  LicenseProjectInfo();
  LicenseProjectInfo(const base_class& project, timestamp_t exp);

  bool IsValid() const;

  timestamp_t GetExp() const;
  void SetExp(timestamp_t exp);

  bool Equals(const LicenseProjectInfo& proj) const;

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* deserialized) const override;

 private:
  timestamp_t exp_;
};

}  // namespace commands_info
}  // namespace fastotv

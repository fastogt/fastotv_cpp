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

#include <fastotv/commands_info/project_info.h>

#define NAME_FIELD "project"
#define VERSION_FIELD "version"
#define EXP_TIME "expiration_time"

namespace fastotv {
namespace commands_info {

ProjectInfo::ProjectInfo() : base_class() {}

ProjectInfo::ProjectInfo(const std::string& project, const std::string& version)
    : base_class(), project_(project), version_(version) {}

bool ProjectInfo::IsValid() const {
  return !project_.empty() && !version_.empty();
}

common::Error ProjectInfo::SerializeFields(json_object* deserialized) const {
  if (!IsValid()) {
    return common::make_error_inval();
  }

  ignore_result(SetStringField(deserialized, NAME_FIELD, project_));
  ignore_result(SetStringField(deserialized, VERSION_FIELD, version_));
  return common::Error();
}

common::Error ProjectInfo::DoDeSerialize(json_object* serialized) {
  std::string name;
  common::Error err = GetStringField(serialized, NAME_FIELD, &name);
  if (err) {
    return err;
  }

  std::string version;
  err = GetStringField(serialized, VERSION_FIELD, &version);
  if (err) {
    return err;
  }

  *this = ProjectInfo(name, version);
  return common::Error();
}

std::string ProjectInfo::GetProject() const {
  return project_;
}

void ProjectInfo::SetProject(const std::string& project) {
  project_ = project;
}

std::string ProjectInfo::GetVersion() const {
  return version_;
}

void ProjectInfo::SetVersion(const std::string& version) {
  version_ = version;
}

bool ProjectInfo::Equals(const ProjectInfo& proj) const {
  return project_ == proj.project_ && version_ == proj.version_;
}

LicenseProjectInfo::LicenseProjectInfo() : base_class() {}

LicenseProjectInfo::LicenseProjectInfo(const base_class& project, timestamp_t exp) : base_class(project), exp_(exp) {}

bool LicenseProjectInfo::IsValid() const {
  return base_class::IsValid();
}

timestamp_t LicenseProjectInfo::GetExp() const {
  return exp_;
}

void LicenseProjectInfo::SetExp(timestamp_t exp) {
  exp_ = exp;
}

bool LicenseProjectInfo::Equals(const LicenseProjectInfo& proj) const {
  return base_class::Equals(proj) && proj.exp_ == exp_;
}

common::Error LicenseProjectInfo::DoDeSerialize(json_object* serialized) {
  base_class proj;
  common::Error err = proj.DeSerialize(serialized);
  if (err) {
    return err;
  }

  timestamp_t exp;
  err = GetInt64Field(serialized, EXP_TIME, &exp);
  if (err) {
    return err;
  }

  *this = LicenseProjectInfo(proj, exp);
  return common::Error();
}

common::Error LicenseProjectInfo::SerializeFields(json_object* deserialized) const {
  if (!IsValid()) {
    return common::make_error_inval();
  }

  ignore_result(SetInt64Field(deserialized, EXP_TIME, exp_));
  return base_class::SerializeFields(deserialized);
}

}  // namespace commands_info
}  // namespace fastotv

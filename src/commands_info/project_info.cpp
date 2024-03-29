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

#define NAME_FIELD "name"
#define VERSION_FIELD "version"

namespace fastotv {
namespace commands_info {

ProjectInfo::ProjectInfo() : base_class() {}

ProjectInfo::ProjectInfo(const std::string& name, const std::string& version)
    : base_class(), name_(name), version_(version) {}

bool ProjectInfo::IsValid() const {
  return !name_.empty() && !version_.empty();
}

common::Error ProjectInfo::SerializeFields(json_object* deserialized) const {
  if (!IsValid()) {
    return common::make_error_inval();
  }

  ignore_result(SetStringField(deserialized, NAME_FIELD, name_));
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

std::string ProjectInfo::GetName() const {
  return name_;
}

void ProjectInfo::SetName(const std::string& name) {
  name_ = name;
}

std::string ProjectInfo::GetVersion() const {
  return version_;
}

void ProjectInfo::SetVersion(const std::string& version) {
  version_ = version;
}

bool ProjectInfo::Equals(const ProjectInfo& proj) const {
  return name_ == proj.name_ && version_ == proj.version_;
}

}  // namespace commands_info
}  // namespace fastotv

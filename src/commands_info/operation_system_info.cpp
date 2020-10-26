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

#include <fastotv/commands_info/operation_system_info.h>

#include <common/system_info/system_info.h>

#define NAME_FIELD "name"
#define VERSION_FIELD "version"
#define ARCH_FIELD "arch"
#define RAM_TOTAL_FIELD "ram_total"
#define RAM_FREE_FIELD "ram_free"

namespace fastotv {
namespace commands_info {

OperationSystemInfo::OperationSystemInfo() : OperationSystemInfo(std::string(), std::string(), std::string(), 0, 0) {}

OperationSystemInfo::OperationSystemInfo(const std::string& name,
                                         const std::string& version,
                                         const std::string& arch,
                                         size_t ram_total,
                                         size_t ram_free)
    : name_(name), version_(version), arch_(arch), ram_bytes_total_(ram_total), ram_bytes_free_(ram_free) {}

std::string OperationSystemInfo::GetName() const {
  return name_;
}

void OperationSystemInfo::SetName(const std::string& name) {
  name_ = name;
}

std::string OperationSystemInfo::GetVersion() const {
  return version_;
}

void OperationSystemInfo::SetVersion(const std::string& version) {
  version_ = version;
}

std::string OperationSystemInfo::GetArch() const {
  return arch_;
}

void OperationSystemInfo::SetArch(const std::string& arch) {
  arch_ = arch;
}

size_t OperationSystemInfo::GetRamBytesTotal() const {
  return ram_bytes_total_;
}

void OperationSystemInfo::SetRamBytesTotal(size_t ram) {
  ram_bytes_total_ = ram;
}

size_t OperationSystemInfo::GetRamBytesFree() const {
  return ram_bytes_free_;
}

void OperationSystemInfo::SetRamBytesFree(size_t size) {
  ram_bytes_total_ = size;
}

OperationSystemInfo OperationSystemInfo::MakeOSSnapshot() {
  static const std::string name = common::system_info::OperatingSystemName();
  static const std::string version = common::system_info::OperatingSystemVersion();
  static const std::string arch = common::system_info::OperatingSystemArchitecture();
  const auto total = common::system_info::AmountOfPhysicalMemory();
  const auto avail = common::system_info::AmountOfAvailablePhysicalMemory();
  return OperationSystemInfo(name, version, arch, total ? *total : 0, avail ? *avail : 0);
}

bool OperationSystemInfo::IsValid() const {
  return !name_.empty() && !version_.empty() && !arch_.empty();
}

common::Error OperationSystemInfo::SerializeFields(json_object* deserialized) const {
  if (!IsValid()) {
    return common::make_error_inval();
  }

  json_object_object_add(deserialized, NAME_FIELD, json_object_new_string(name_.c_str()));
  json_object_object_add(deserialized, VERSION_FIELD, json_object_new_string(version_.c_str()));
  json_object_object_add(deserialized, ARCH_FIELD, json_object_new_string(arch_.c_str()));
  json_object_object_add(deserialized, RAM_TOTAL_FIELD, json_object_new_int64(ram_bytes_total_));
  json_object_object_add(deserialized, RAM_FREE_FIELD, json_object_new_int64(ram_bytes_free_));
  return common::Error();
}

common::Error OperationSystemInfo::DoDeSerialize(json_object* serialized) {
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

  std::string arch;
  err = GetStringField(serialized, ARCH_FIELD, &arch);
  if (err) {
    return err;
  }

  // optional
  int64_t ram_total = 0;
  ignore_result(GetInt64Field(serialized, RAM_TOTAL_FIELD, &ram_total));

  int64_t ram_free = 0;
  ignore_result(GetInt64Field(serialized, RAM_FREE_FIELD, &ram_free));

  *this = OperationSystemInfo(name, version, arch, ram_total, ram_free);
  return common::Error();
}

bool OperationSystemInfo::Equals(const OperationSystemInfo& os) const {
  return name_ == os.name_ && version_ == os.version_ && arch_ == os.arch_ && ram_bytes_free_ == os.ram_bytes_free_ &&
         ram_bytes_total_ == os.ram_bytes_total_;
}

}  // namespace commands_info
}  // namespace fastotv

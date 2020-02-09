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

#define OPERATION_SYSTEM_NAME "name"
#define OPERATION_SYSTEM_VERSION "version"
#define OPERATION_SYSTEM_ARCH "arch"
#define OPERATION_SYSTEM_RAM_TOTAL "ram_total"
#define OPERATION_SYSTEM_RAM_FREE "ram_free"

namespace fastotv {
namespace commands_info {

OperationSystemInfo::OperationSystemInfo() : OperationSystemInfo(std::string(), std::string(), std::string(), 0, 0) {}

OperationSystemInfo::OperationSystemInfo(const std::string& name,
                                         const std::string& version,
                                         const std::string& arch,
                                         size_t ram_total,
                                         size_t ram_free)
    : name_(name), version_(version), arch_(arch), ram_total_(ram_total), ram_free_(ram_free) {}

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

size_t OperationSystemInfo::GetRamTotal() const {
  return ram_total_;
}

void OperationSystemInfo::SetRamTotal(size_t ram) {
  ram_total_ = ram;
}

size_t OperationSystemInfo::GetRamFree() const {
  return ram_free_;
}

void OperationSystemInfo::SetRamFree(size_t size) {
  ram_total_ = size;
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

  json_object_object_add(deserialized, OPERATION_SYSTEM_NAME, json_object_new_string(name_.c_str()));
  json_object_object_add(deserialized, OPERATION_SYSTEM_VERSION, json_object_new_string(version_.c_str()));
  json_object_object_add(deserialized, OPERATION_SYSTEM_ARCH, json_object_new_string(arch_.c_str()));
  json_object_object_add(deserialized, OPERATION_SYSTEM_RAM_TOTAL, json_object_new_int64(ram_total_));
  json_object_object_add(deserialized, OPERATION_SYSTEM_RAM_FREE, json_object_new_int64(ram_free_));
  return common::Error();
}

common::Error OperationSystemInfo::DoDeSerialize(json_object* serialized) {
  OperationSystemInfo inf;
  json_object* jname = nullptr;
  json_bool jname_exists = json_object_object_get_ex(serialized, OPERATION_SYSTEM_NAME, &jname);
  if (!jname_exists) {
    return common::make_error_inval();
  }
  inf.name_ = json_object_get_string(jname);

  json_object* jversion = nullptr;
  json_bool jversion_exists = json_object_object_get_ex(serialized, OPERATION_SYSTEM_VERSION, &jversion);
  if (!jversion_exists) {
    return common::make_error_inval();
  }
  inf.version_ = json_object_get_string(jversion);

  json_object* jarch = nullptr;
  json_bool jarch_exists = json_object_object_get_ex(serialized, OPERATION_SYSTEM_ARCH, &jarch);
  if (!jarch_exists) {
    return common::make_error_inval();
  }
  inf.arch_ = json_object_get_string(jarch);

  json_object* jram_total = nullptr;
  json_bool jram_total_exists = json_object_object_get_ex(serialized, OPERATION_SYSTEM_RAM_TOTAL, &jram_total);
  if (jram_total_exists) {
    inf.ram_total_ = json_object_get_int64(jram_total);
  }

  json_object* jram_free = nullptr;
  json_bool jram_free_exists = json_object_object_get_ex(serialized, OPERATION_SYSTEM_RAM_FREE, &jram_free);
  if (jram_free_exists) {
    inf.ram_free_ = json_object_get_int64(jram_free);
  }
  *this = inf;
  return common::Error();
}

bool OperationSystemInfo::Equals(const OperationSystemInfo& os) const {
  return name_ == os.name_ && version_ == os.version_ && arch_ == os.arch_ && ram_free_ == os.ram_free_ &&
         ram_total_ == os.ram_total_;
}

}  // namespace commands_info
}  // namespace fastotv

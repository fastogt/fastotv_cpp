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

#include <common/serializer/json_serializer.h>

namespace fastotv {
namespace commands_info {

class OperationSystemInfo : public common::serializer::JsonSerializer<OperationSystemInfo> {
 public:
  OperationSystemInfo();
  OperationSystemInfo(const std::string& name,
                      const std::string& version,
                      const std::string& arch,
                      size_t ram_total,
                      size_t ram_free);

  bool IsValid() const;

  std::string GetName() const;
  void SetName(const std::string& name);

  std::string GetVersion() const;
  void SetVersion(const std::string& version);

  std::string GetArch() const;
  void SetArch(const std::string& arch);

  size_t GetRamTotal() const;
  void SetRamTotal(size_t ram);

  size_t GetRamFree() const;
  void SetRamFree(size_t size);

  static OperationSystemInfo MakeOSSnapshot();

  bool Equals(const OperationSystemInfo& os) const;

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* deserialized) const override;

 private:
  std::string name_;
  std::string version_;
  std::string arch_;

  size_t ram_total_;
  size_t ram_free_;
};

inline bool operator==(const OperationSystemInfo& left, const OperationSystemInfo& right) {
  return left.Equals(right);
}

inline bool operator!=(const OperationSystemInfo& x, const OperationSystemInfo& y) {
  return !(x == y);
}

}  // namespace commands_info
}  // namespace fastotv

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

#include <fastotv/commands_info/operation_system_info.h>
#include <fastotv/commands_info/project_info.h>

#include <fastotv/types.h>

namespace fastotv {
namespace commands_info {

class ClientInfo : public common::serializer::JsonSerializer<ClientInfo> {
 public:
  ClientInfo();
  ClientInfo(const login_t& login,
             const device_id_t& device_id,
             const ProjectInfo& proj,
             const OperationSystemInfo& os,
             const std::string& cpu_brand);

  bool IsValid() const;

  login_t GetLogin() const;
  void SetLogin(const login_t& login);

  ProjectInfo GetProject() const;
  void SetProject(const ProjectInfo& proj);

  OperationSystemInfo GetOs() const;
  void SetOs(const OperationSystemInfo& os);

  std::string GetCpuBrand() const;
  void SetCpuBrand(const std::string& brand);

  bool Equals(const ClientInfo& info) const;

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* deserialized) const override;

 private:
  login_t login_;
  device_id_t device_id_;
  ProjectInfo proj_;
  OperationSystemInfo os_;
  std::string cpu_brand_;
};

inline bool operator==(const ClientInfo& left, const ClientInfo& right) {
  return left.Equals(right);
}

inline bool operator!=(const ClientInfo& x, const ClientInfo& y) {
  return !(x == y);
}

}  // namespace commands_info
}  // namespace fastotv

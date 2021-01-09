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

#include <fastotv/commands_info/client_info.h>

#define LOGIN_FIELD "login"
#define DEVICE_ID_FIELD "device_id"
#define PROJECT_FIELD "project"
#define OS_FIELD "os"
#define CPU_FIELD "cpu_brand"

namespace fastotv {
namespace commands_info {

ClientInfo::ClientInfo() : login_(), device_id_(), proj_(), os_(), cpu_brand_() {}

ClientInfo::ClientInfo(const login_t& login,
                       const device_id_t& device_id,
                       const ProjectInfo& proj,
                       const OperationSystemInfo& os,
                       const std::string& cpu_brand)
    : login_(login), device_id_(device_id), proj_(proj), os_(os), cpu_brand_(cpu_brand) {}

bool ClientInfo::IsValid() const {
  return !login_.empty();
}

common::Error ClientInfo::SerializeFields(json_object* deserialized) const {
  if (!IsValid()) {
    return common::make_error_inval();
  }

  json_object* proj = nullptr;
  common::Error err = proj_.Serialize(&proj);
  if (err) {
    return err;
  }

  json_object* os = nullptr;
  err = os_.Serialize(&os);
  if (err) {
    return err;
  }

  ignore_result(SetStringField(deserialized, LOGIN_FIELD, login_));
  ignore_result(SetStringField(deserialized, DEVICE_ID_FIELD, device_id_));
  ignore_result(SetObjectField(deserialized, PROJECT_FIELD, proj));
  ignore_result(SetObjectField(deserialized, OS_FIELD, os));
  ignore_result(SetStringField(deserialized, CPU_FIELD, cpu_brand_));
  return common::Error();
}

common::Error ClientInfo::DoDeSerialize(json_object* serialized) {
  ClientInfo inf;
  std::string login;
  common::Error err = GetStringField(serialized, LOGIN_FIELD, &login);
  if (err) {
    return err;
  }

  if (login.empty()) {
    return common::make_error_inval();
  }
  inf.login_ = login;

  device_id_t dev;
  err = GetStringField(serialized, DEVICE_ID_FIELD, &dev);
  if (err) {
    return err;
  }
  inf.device_id_ = dev;

  json_object* jproj;
  err = GetObjectField(serialized, PROJECT_FIELD, &jproj);
  if (err) {
    return err;
  }

  ProjectInfo proj;
  err = proj.DeSerialize(jproj);
  if (err) {
    return err;
  }
  inf.proj_ = proj;

  json_object* jos;
  err = GetObjectField(serialized, OS_FIELD, &jos);
  if (err) {
    return err;
  }

  OperationSystemInfo os;
  err = os.DeSerialize(jos);
  if (err) {
    return err;
  }
  inf.os_ = os;

  std::string brand;
  err = GetStringField(serialized, CPU_FIELD, &brand);
  if (err) {
    return err;
  }
  inf.cpu_brand_ = brand;

  *this = inf;
  return common::Error();
}

login_t ClientInfo::GetLogin() const {
  return login_;
}

void ClientInfo::SetLogin(const login_t& login) {
  login_ = login;
}

ProjectInfo ClientInfo::GetProject() const {
  return proj_;
}

void ClientInfo::SetProject(const ProjectInfo& proj) {
  proj_ = proj;
}

OperationSystemInfo ClientInfo::GetOs() const {
  return os_;
}

void ClientInfo::SetOs(const OperationSystemInfo& os) {
  os_ = os;
}

std::string ClientInfo::GetCpuBrand() const {
  return cpu_brand_;
}

void ClientInfo::SetCpuBrand(const std::string& brand) {
  cpu_brand_ = brand;
}

bool ClientInfo::Equals(const ClientInfo& info) const {
  return login_ == info.login_ && os_ == info.os_ && cpu_brand_ == info.cpu_brand_;
}

}  // namespace commands_info
}  // namespace fastotv

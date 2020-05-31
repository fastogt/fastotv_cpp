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

#include <fastotv/commands_info/client_info.h>

#define LOGIN_FIELD "login"
#define DEVICE_ID_FIELD "device_id"
#define PROJECT_FIELD "project"
#define OS_FIELD "os"
#define CPU_FIELD "cpu"

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

  json_object_object_add(deserialized, LOGIN_FIELD, json_object_new_string(login_.c_str()));
  json_object_object_add(deserialized, DEVICE_ID_FIELD, json_object_new_string(device_id_.c_str()));
  json_object_object_add(deserialized, PROJECT_FIELD, proj);
  json_object_object_add(deserialized, OS_FIELD, os);
  json_object_object_add(deserialized, CPU_FIELD, json_object_new_string(cpu_brand_.c_str()));
  return common::Error();
}

common::Error ClientInfo::DoDeSerialize(json_object* serialized) {
  ClientInfo inf;
  json_object* jlogin = nullptr;
  json_bool jlogin_exists = json_object_object_get_ex(serialized, LOGIN_FIELD, &jlogin);
  if (!jlogin_exists) {
    return common::make_error_inval();
  }

  std::string login = json_object_get_string(jlogin);
  if (login.empty()) {
    return common::make_error_inval();
  }
  inf.login_ = login;

  json_object* jdevice_id = nullptr;
  json_bool jdevice_id_exists = json_object_object_get_ex(serialized, DEVICE_ID_FIELD, &jdevice_id);
  if (!jdevice_id_exists) {
    return common::make_error_inval();
  }
  inf.device_id_ = json_object_get_string(jdevice_id);

  json_object* jproj = nullptr;
  json_bool jproj_exists = json_object_object_get_ex(serialized, PROJECT_FIELD, &jproj);
  if (!jproj_exists) {
    return common::make_error_inval();
  }

  ProjectInfo proj;
  common::Error err = proj.DeSerialize(jproj);
  if (err) {
    return err;
  }
  inf.proj_ = proj;

  json_object* jos = nullptr;
  json_bool jos_exists = json_object_object_get_ex(serialized, OS_FIELD, &jos);
  if (!jos_exists) {
    return common::make_error_inval();
  }

  OperationSystemInfo os;
  err = os.DeSerialize(jos);
  if (err) {
    return err;
  }
  inf.os_ = os;

  json_object* jcpu = nullptr;
  json_bool jcpu_exists = json_object_object_get_ex(serialized, CPU_FIELD, &jcpu);
  if (jcpu_exists) {
    inf.cpu_brand_ = json_object_get_string(jcpu);
  }

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

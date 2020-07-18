/*  Copyright (C) 2014-2020 FastoGT. All right reserved.
    This file is part of fastocloud.
    fastocloud is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    fastocloud is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with fastocloud.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <fastotv/commands_info/machine_info.h>

#define STATISTIC_SERVICE_INFO_UPTIME_FIELD "uptime"
#define STATISTIC_SERVICE_INFO_TIMESTAMP_FIELD "timestamp"
#define STATISTIC_SERVICE_INFO_CPU_FIELD "cpu"
#define STATISTIC_SERVICE_INFO_GPU_FIELD "gpu"
#define STATISTIC_SERVICE_INFO_MEMORY_TOTAL_FIELD "memory_total"
#define STATISTIC_SERVICE_INFO_MEMORY_FREE_FIELD "memory_free"

#define STATISTIC_SERVICE_INFO_HDD_TOTAL_FIELD "hdd_total"
#define STATISTIC_SERVICE_INFO_HDD_FREE_FIELD "hdd_free"

#define STATISTIC_SERVICE_INFO_LOAD_AVERAGE_FIELD "load_average"

#define STATISTIC_SERVICE_INFO_BANDWIDTH_IN_FIELD "bandwidth_in"
#define STATISTIC_SERVICE_INFO_BANDWIDTH_OUT_FIELD "bandwidth_out"

namespace fastotv {
namespace commands_info {

MachineInfo::MachineInfo()
    : base_class(),
      cpu_load_(),
      gpu_load_(),
      load_average_(),
      ram_bytes_total_(),
      ram_bytes_free_(),
      hdd_bytes_total_(),
      hdd_bytes_free_(),
      net_bytes_recv_(),
      net_bytes_send_(),
      current_ts_(),
      uptime_() {}

MachineInfo::MachineInfo(cpu_load_t cpu_load,
                         gpu_load_t gpu_load,
                         const std::string& load_average,
                         size_t ram_bytes_total,
                         size_t ram_bytes_free,
                         size_t hdd_bytes_total,
                         size_t hdd_bytes_free,
                         fastotv::bandwidth_t net_bytes_recv,
                         fastotv::bandwidth_t net_bytes_send,
                         time_t uptime,
                         fastotv::timestamp_t timestamp)
    : base_class(),
      cpu_load_(cpu_load),
      gpu_load_(gpu_load),
      load_average_(load_average),
      ram_bytes_total_(ram_bytes_total),
      ram_bytes_free_(ram_bytes_free),
      hdd_bytes_total_(hdd_bytes_total),
      hdd_bytes_free_(hdd_bytes_free),
      net_bytes_recv_(net_bytes_recv),
      net_bytes_send_(net_bytes_send),
      current_ts_(timestamp),
      uptime_(uptime) {}

common::Error MachineInfo::SerializeFields(json_object* out) const {
  json_object_object_add(out, STATISTIC_SERVICE_INFO_CPU_FIELD, json_object_new_double(cpu_load_));
  json_object_object_add(out, STATISTIC_SERVICE_INFO_GPU_FIELD, json_object_new_double(gpu_load_));
  json_object_object_add(out, STATISTIC_SERVICE_INFO_LOAD_AVERAGE_FIELD, json_object_new_string(load_average_.c_str()));
  json_object_object_add(out, STATISTIC_SERVICE_INFO_MEMORY_TOTAL_FIELD, json_object_new_int64(ram_bytes_total_));
  json_object_object_add(out, STATISTIC_SERVICE_INFO_MEMORY_FREE_FIELD, json_object_new_int64(ram_bytes_free_));
  json_object_object_add(out, STATISTIC_SERVICE_INFO_HDD_TOTAL_FIELD, json_object_new_int64(hdd_bytes_total_));
  json_object_object_add(out, STATISTIC_SERVICE_INFO_HDD_FREE_FIELD, json_object_new_int64(hdd_bytes_free_));
  json_object_object_add(out, STATISTIC_SERVICE_INFO_BANDWIDTH_IN_FIELD, json_object_new_int64(net_bytes_recv_));
  json_object_object_add(out, STATISTIC_SERVICE_INFO_BANDWIDTH_OUT_FIELD, json_object_new_int64(net_bytes_send_));
  json_object_object_add(out, STATISTIC_SERVICE_INFO_UPTIME_FIELD, json_object_new_int64(uptime_));
  json_object_object_add(out, STATISTIC_SERVICE_INFO_TIMESTAMP_FIELD, json_object_new_int64(current_ts_));
  return common::Error();
}

common::Error MachineInfo::DoDeSerialize(json_object* serialized) {
  MachineInfo inf;

  json_object* jcpu_load = nullptr;
  json_bool jcpu_load_exists = json_object_object_get_ex(serialized, STATISTIC_SERVICE_INFO_CPU_FIELD, &jcpu_load);
  if (jcpu_load_exists) {
    inf.cpu_load_ = json_object_get_double(jcpu_load);
  }

  json_object* jgpu_load = nullptr;
  json_bool jgpu_load_exists = json_object_object_get_ex(serialized, STATISTIC_SERVICE_INFO_GPU_FIELD, &jgpu_load);
  if (jgpu_load_exists) {
    inf.gpu_load_ = json_object_get_double(jgpu_load);
  }

  json_object* juptime = nullptr;
  json_bool juptime_exists = json_object_object_get_ex(serialized, STATISTIC_SERVICE_INFO_LOAD_AVERAGE_FIELD, &juptime);
  if (juptime_exists) {
    inf.load_average_ = json_object_get_string(juptime);
  }

  json_object* jmemory_total = nullptr;
  json_bool jmemory_total_exists =
      json_object_object_get_ex(serialized, STATISTIC_SERVICE_INFO_MEMORY_TOTAL_FIELD, &jmemory_total);
  if (jmemory_total_exists) {
    inf.ram_bytes_total_ = json_object_get_int64(jmemory_total);
  }

  json_object* jmemory_avail = nullptr;
  json_bool jmemory_avail_exists =
      json_object_object_get_ex(serialized, STATISTIC_SERVICE_INFO_MEMORY_FREE_FIELD, &jmemory_avail);
  if (jmemory_avail_exists) {
    inf.ram_bytes_free_ = json_object_get_int64(jmemory_avail);
  }

  json_object* jhdd_total = nullptr;
  json_bool jhdd_total_exists =
      json_object_object_get_ex(serialized, STATISTIC_SERVICE_INFO_HDD_TOTAL_FIELD, &jhdd_total);
  if (jhdd_total_exists) {
    inf.hdd_bytes_total_ = json_object_get_int64(jhdd_total);
  }

  json_object* jhdd_free = nullptr;
  json_bool jhdd_free_exists = json_object_object_get_ex(serialized, STATISTIC_SERVICE_INFO_HDD_FREE_FIELD, &jhdd_free);
  if (jhdd_free_exists) {
    inf.hdd_bytes_free_ = json_object_get_int64(jhdd_free);
  }

  json_object* jnet_bytes_recv = nullptr;
  json_bool jnet_bytes_recv_exists =
      json_object_object_get_ex(serialized, STATISTIC_SERVICE_INFO_BANDWIDTH_IN_FIELD, &jnet_bytes_recv);
  if (jnet_bytes_recv_exists) {
    inf.net_bytes_recv_ = json_object_get_int64(jnet_bytes_recv);
  }

  json_object* jnet_bytes_send = nullptr;
  json_bool jnet_bytes_send_exists =
      json_object_object_get_ex(serialized, STATISTIC_SERVICE_INFO_BANDWIDTH_OUT_FIELD, &jnet_bytes_send);
  if (jnet_bytes_send_exists) {
    inf.net_bytes_send_ = json_object_get_int64(jnet_bytes_send);
  }

  json_object* jsys_stamp = nullptr;
  json_bool jsys_stamp_exists = json_object_object_get_ex(serialized, STATISTIC_SERVICE_INFO_UPTIME_FIELD, &jsys_stamp);
  if (jsys_stamp_exists) {
    inf.uptime_ = json_object_get_int64(jsys_stamp);
  }

  json_object* jcur_ts = nullptr;
  json_bool jcur_ts_exists = json_object_object_get_ex(serialized, STATISTIC_SERVICE_INFO_TIMESTAMP_FIELD, &jcur_ts);
  if (jcur_ts_exists) {
    inf.current_ts_ = json_object_get_int64(jcur_ts);
  }

  *this = inf;
  return common::Error();
}

MachineInfo::cpu_load_t MachineInfo::GetCpuLoad() const {
  return cpu_load_;
}

MachineInfo::gpu_load_t MachineInfo::GetGpuLoad() const {
  return gpu_load_;
}

std::string MachineInfo::GetLoadAverage() const {
  return load_average_;
}

fastotv::bandwidth_t MachineInfo::GetNetBytesRecv() const {
  return net_bytes_recv_;
}

fastotv::bandwidth_t MachineInfo::GetNetBytesSend() const {
  return net_bytes_send_;
}

fastotv::timestamp_t MachineInfo::GetTimestamp() const {
  return current_ts_;
}

}  // namespace commands_info
}  // namespace fastotv

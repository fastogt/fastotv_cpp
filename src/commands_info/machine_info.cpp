/*  Copyright (C) 2014-2021 FastoGT. All right reserved.
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

#define UPTIME_FIELD "uptime"
#define TIMESTAMP_FIELD "timestamp"
#define CPU_FIELD "cpu"
#define GPU_FIELD "gpu"
#define MEMORY_TOTAL_FIELD "memory_total"
#define MEMORY_FREE_FIELD "memory_free"

#define HDD_TOTAL_FIELD "hdd_total"
#define HDD_FREE_FIELD "hdd_free"

#define LOAD_AVERAGE_FIELD "load_average"

#define BANDWIDTH_IN_FIELD "bandwidth_in"
#define BANDWIDTH_OUT_FIELD "bandwidth_out"

#define TOTAL_BYTES_IN_FIELD "total_bytes_in"
#define TOTAL_BYTES_OUT_FIELD "total_bytes_out"

namespace fastotv {
namespace commands_info {

MachineInfo::MachineInfo()
    : base_class(),
      cpu_load_(0),
      gpu_load_(0),
      load_average_(),
      ram_bytes_total_(0),
      ram_bytes_free_(0),
      hdd_bytes_total_(0),
      hdd_bytes_free_(0),
      net_bytes_recv_(0),
      net_bytes_send_(0),
      current_ts_(0),
      uptime_(0),
      net_total_bytes_recv_(0),
      net_total_bytes_send_(0) {}

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
                         fastotv::timestamp_t timestamp,
                         size_t net_total_bytes_recv,
                         size_t net_total_bytes_send)
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
      uptime_(uptime),
      net_total_bytes_recv_(net_total_bytes_recv),
      net_total_bytes_send_(net_total_bytes_send) {}

common::Error MachineInfo::SerializeFields(json_object* out) const {
  ignore_result(SetDoubleField(out, CPU_FIELD, cpu_load_));
  ignore_result(SetDoubleField(out, GPU_FIELD, gpu_load_));
  ignore_result(SetStringField(out, LOAD_AVERAGE_FIELD, load_average_));
  ignore_result(SetUInt64Field(out, MEMORY_TOTAL_FIELD, ram_bytes_total_));
  ignore_result(SetUInt64Field(out, MEMORY_FREE_FIELD, ram_bytes_free_));
  ignore_result(SetUInt64Field(out, HDD_TOTAL_FIELD, hdd_bytes_total_));
  ignore_result(SetUInt64Field(out, HDD_FREE_FIELD, hdd_bytes_free_));
  ignore_result(SetUInt64Field(out, BANDWIDTH_IN_FIELD, net_bytes_recv_));
  ignore_result(SetUInt64Field(out, BANDWIDTH_OUT_FIELD, net_bytes_send_));
  ignore_result(SetInt64Field(out, UPTIME_FIELD, uptime_));
  ignore_result(SetInt64Field(out, TIMESTAMP_FIELD, current_ts_));
  ignore_result(SetUInt64Field(out, TOTAL_BYTES_IN_FIELD, net_total_bytes_recv_));
  ignore_result(SetUInt64Field(out, TOTAL_BYTES_OUT_FIELD, net_total_bytes_send_));
  return common::Error();
}

common::Error MachineInfo::DoDeSerialize(json_object* serialized) {
  cpu_load_t cpu_load = 0;
  ignore_result(GetDoubleField(serialized, CPU_FIELD, &cpu_load));

  gpu_load_t gpu_load = 0;
  ignore_result(GetDoubleField(serialized, GPU_FIELD, &gpu_load));

  std::string load_average;
  ignore_result(GetStringField(serialized, LOAD_AVERAGE_FIELD, &load_average));

  size_t ram_bytes_total = 0;
  ignore_result(GetUint64Field(serialized, MEMORY_TOTAL_FIELD, &ram_bytes_total));

  size_t ram_bytes_free = 0;
  ignore_result(GetUint64Field(serialized, MEMORY_FREE_FIELD, &ram_bytes_free));

  size_t hdd_bytes_total = 0;
  ignore_result(GetUint64Field(serialized, HDD_TOTAL_FIELD, &hdd_bytes_total));

  size_t hdd_bytes_free = 0;
  ignore_result(GetUint64Field(serialized, HDD_FREE_FIELD, &hdd_bytes_free));

  fastotv::bandwidth_t net_bytes_recv = 0;
  ignore_result(GetUint64Field(serialized, BANDWIDTH_IN_FIELD, &net_bytes_recv));

  fastotv::bandwidth_t net_bytes_send = 0;
  ignore_result(GetUint64Field(serialized, BANDWIDTH_OUT_FIELD, &net_bytes_send));

  fastotv::timestamp_t current_ts = 0;
  ignore_result(GetInt64Field(serialized, TIMESTAMP_FIELD, &current_ts));

  time_t uptime = 0;
  ignore_result(GetInt64Field(serialized, UPTIME_FIELD, &uptime));

  size_t net_total_bytes_recv = 0;
  ignore_result(GetUint64Field(serialized, TOTAL_BYTES_IN_FIELD, &net_total_bytes_recv));

  size_t net_total_bytes_send = 0;
  ignore_result(GetUint64Field(serialized, TOTAL_BYTES_OUT_FIELD, &net_total_bytes_send));

  *this =
      MachineInfo(cpu_load, gpu_load, load_average, ram_bytes_total, ram_bytes_free, hdd_bytes_total, hdd_bytes_free,
                  net_bytes_recv, net_bytes_send, uptime, current_ts, net_total_bytes_recv, net_total_bytes_send);
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

size_t MachineInfo::GetRamBytesTotal() const {
  return ram_bytes_total_;
}

size_t MachineInfo::GetRamBytesFree() const {
  return ram_bytes_free_;
}

size_t MachineInfo::GetHddBytesTotal() const {
  return hdd_bytes_total_;
}

size_t MachineInfo::GetHddBytesFree() const {
  return hdd_bytes_free_;
}

fastotv::bandwidth_t MachineInfo::GetNetBytesRecv() const {
  return net_bytes_recv_;
}

fastotv::bandwidth_t MachineInfo::GetNetBytesSend() const {
  return net_bytes_send_;
}

time_t MachineInfo::GetUptime() {
  return uptime_;
}

fastotv::timestamp_t MachineInfo::GetTimestamp() const {
  return current_ts_;
}

size_t MachineInfo::GetNetTotalBytesRecv() const {
  return net_total_bytes_recv_;
}

size_t MachineInfo::GetNetTotalBytesSend() const {
  return net_total_bytes_send_;
}

bool MachineInfo::Equals(const MachineInfo& mach) const {
  return mach.cpu_load_ == cpu_load_ && mach.gpu_load_ == gpu_load_ && mach.load_average_ == load_average_ &&
         mach.ram_bytes_total_ == ram_bytes_total_ && mach.ram_bytes_free_ == ram_bytes_free_ &&
         mach.hdd_bytes_total_ == hdd_bytes_total_ && mach.hdd_bytes_free_ == hdd_bytes_free_ &&
         mach.net_bytes_recv_ == net_bytes_recv_ && mach.net_bytes_send_ == net_bytes_send_ &&
         mach.uptime_ == uptime_ && mach.current_ts_ == current_ts_ &&
         mach.net_total_bytes_recv_ == net_total_bytes_recv_ && mach.net_total_bytes_send_ == net_total_bytes_send_;
}

}  // namespace commands_info
}  // namespace fastotv

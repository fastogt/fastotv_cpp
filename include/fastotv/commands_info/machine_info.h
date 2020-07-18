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

#pragma once

#include <string>

#include <common/net/types.h>
#include <common/serializer/json_serializer.h>

#include <fastotv/commands_info/operation_system_info.h>
#include <fastotv/types.h>

namespace fastotv {
namespace commands_info {

class MachineInfo : public common::serializer::JsonSerializer<MachineInfo> {
 public:
  typedef JsonSerializer<MachineInfo> base_class;
  typedef double cpu_load_t;
  typedef double gpu_load_t;
  MachineInfo();
  MachineInfo(cpu_load_t cpu_load,
              gpu_load_t gpu_load,
              const std::string& load_average,
              size_t ram_bytes_total,
              size_t ram_bytes_free,
              size_t hdd_bytes_total,
              size_t hdd_bytes_free,
              fastotv::bandwidth_t net_bytes_recv,
              fastotv::bandwidth_t net_bytes_send,
              time_t uptime,
              fastotv::timestamp_t timestamp);

  cpu_load_t GetCpuLoad() const;
  gpu_load_t GetGpuLoad() const;
  std::string GetLoadAverage() const;
  fastotv::bandwidth_t GetNetBytesRecv() const;
  fastotv::bandwidth_t GetNetBytesSend() const;
  fastotv::timestamp_t GetTimestamp() const;

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* out) const override;

 private:
  cpu_load_t cpu_load_;
  gpu_load_t gpu_load_;
  std::string load_average_;
  size_t ram_bytes_total_;
  size_t ram_bytes_free_;
  size_t hdd_bytes_total_;
  size_t hdd_bytes_free_;
  fastotv::bandwidth_t net_bytes_recv_;
  fastotv::bandwidth_t net_bytes_send_;
  fastotv::timestamp_t current_ts_;
  time_t uptime_;
};

}  // namespace commands_info
}  // namespace fastotv

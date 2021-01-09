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

#include <fastotv/client/client.h>

#include <common/system_info/cpu_info.h>  // for CurrentCpuInfo

#include <fastotv/client/commands_factory.h>

namespace fastotv {
namespace client {

Client::Client(common::libev::IoLoop* server, const common::net::socket_info& info, compressor_t compressor)
    : base_class(server, info, compressor) {}

common::ErrnoError Client::Ping() {
  common::daemon::commands::ServerPingInfo serv_ping;
  return Ping(serv_ping);
}

common::ErrnoError Client::Ping(const common::daemon::commands::ServerPingInfo& ping) {
  protocol::request_t ping_request;
  common::Error err_ser = PingRequest(NextRequestID(), ping, &ping_request);
  if (err_ser) {
    return common::make_errno_error(err_ser->GetDescription(), EINVAL);
  }

  return WriteRequest(ping_request);
}

common::ErrnoError Client::NotificationTextOK(protocol::sequance_id_t id) {
  protocol::response_t resp;
  common::Error err_ser = NotificationTextSuccess(id, &resp);
  if (err_ser) {
    const std::string err_str = err_ser->GetDescription();
    return common::make_errno_error(err_str, EINVAL);
  }

  return WriteResponse(resp);
}

common::ErrnoError Client::Pong(protocol::sequance_id_t id) {
  common::daemon::commands::ClientPingInfo client_pong;
  return Pong(id, client_pong);
}

common::ErrnoError Client::Pong(protocol::sequance_id_t id, const common::daemon::commands::ClientPingInfo& pong) {
  protocol::response_t resp;
  common::Error err_ser = PingResponseSuccess(id, pong, &resp);
  if (err_ser) {
    const std::string err_str = err_ser->GetDescription();
    return common::make_errno_error(err_str, EINVAL);
  }

  return WriteResponse(resp);
}

common::ErrnoError Client::SystemInfo(protocol::sequance_id_t id,
                                      const login_t& login,
                                      const device_id_t& dev,
                                      const commands_info::ProjectInfo& proj) {
  common::system_info::CPU c1;
  commands_info::ClientInfo info(login, dev, proj, commands_info::OperationSystemInfo::MakeOSSnapshot(),
                                 c1.vendor_name());
  return SystemInfo(id, info);
}

common::ErrnoError Client::SystemInfo(protocol::sequance_id_t id, const commands_info::ClientInfo& info) {
  protocol::response_t resp;
  common::Error err_ser = SystemInfoResponseSuccess(id, info, &resp);
  if (err_ser) {
    return common::make_errno_error(err_ser->GetDescription(), EINVAL);
  }

  return WriteResponse(resp);
}

common::ErrnoError Client::ActivateDevice(const commands_info::LoginInfo& login) {
  protocol::request_t login_request;
  common::Error err_ser = ActivateDeviceRequest(NextRequestID(), login, &login_request);
  if (err_ser) {
    DNOTREACHED();
    return common::make_errno_error(err_ser->GetDescription(), EINVAL);
  }

  return WriteRequest(login_request);
}

common::ErrnoError Client::Login(const commands_info::AuthInfo& auth) {
  protocol::request_t auth_request;
  common::Error err_ser = LoginRequest(NextRequestID(), auth, &auth_request);
  if (err_ser) {
    DNOTREACHED();
    return common::make_errno_error(err_ser->GetDescription(), EINVAL);
  }

  return WriteRequest(auth_request);
}

common::ErrnoError Client::GetServerInfo() {
  protocol::request_t server_info_request;
  common::Error err_ser = GetServerInfoRequest(NextRequestID(), &server_info_request);
  if (err_ser) {
    return common::make_errno_error(err_ser->GetDescription(), EINVAL);
  }

  return WriteRequest(server_info_request);
}

common::ErrnoError Client::GetChannels() {
  protocol::request_t server_info_request;
  common::Error err_ser = GetChannelsRequest(NextRequestID(), &server_info_request);
  if (err_ser) {
    return common::make_errno_error(err_ser->GetDescription(), EINVAL);
  }

  return WriteRequest(server_info_request);
}

common::ErrnoError Client::GetRuntimeChannelInfo(stream_id_t sid) {
  protocol::request_t run_channels_request;
  commands_info::RuntimeChannelLiteInfo run(sid);
  common::Error err_ser = GetRuntimeChannelInfoRequest(NextRequestID(), run, &run_channels_request);
  if (err_ser) {
    return common::make_errno_error(err_ser->GetDescription(), EINVAL);
  }

  return WriteRequest(run_channels_request);
}

}  // namespace client
}  // namespace fastotv

/*  Copyright (C) 2014-2022 FastoGT. All right reserved.

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

#include <string>  // for string

#include <common/daemon/commands/ping_info.h>

#include <fastotv/protocol/types.h>

#include <fastotv/commands_info/auth_info.h>
#include <fastotv/commands_info/catchup_generate_info.h>
#include <fastotv/commands_info/catchup_undo_info.h>
#include <fastotv/commands_info/client_info.h>
#include <fastotv/commands_info/runtime_channel_info.h>

namespace fastotv {
namespace client {

// requests
common::Error ActivateDeviceRequest(protocol::sequance_id_t id,
                                    const commands_info::LoginInfo& params,
                                    protocol::request_t* req);
common::Error LoginRequest(protocol::sequance_id_t id, const commands_info::AuthInfo& params, protocol::request_t* req);
common::Error PingRequest(protocol::sequance_id_t id,
                          const common::daemon::commands::ServerPingInfo& params,
                          protocol::request_t* req);
common::Error GetServerInfoRequest(protocol::sequance_id_t id, protocol::request_t* req);
common::Error GetChannelsRequest(protocol::sequance_id_t id, protocol::request_t* req);
common::Error GetRuntimeChannelInfoRequest(protocol::sequance_id_t id,
                                           const commands_info::RuntimeChannelLiteInfo& params,
                                           protocol::request_t* req);
common::Error CatchupRequest(protocol::sequance_id_t id,
                             const commands_info::CatchupGenerateInfo& params,
                             protocol::request_t* req);
common::Error CatchupUndoRequest(protocol::sequance_id_t id,
                                 const commands_info::CatchupUndoInfo& params,
                                 protocol::request_t* req);

// response
common::Error PingResponseSuccess(protocol::sequance_id_t id,
                                  const common::daemon::commands::ClientPingInfo& params,
                                  protocol::response_t* resp);
common::Error SystemInfoResponseSuccess(protocol::sequance_id_t id,
                                        const commands_info::ClientInfo& params,
                                        protocol::response_t* resp);
common::Error NotificationTextSuccess(protocol::sequance_id_t id, protocol::response_t* resp);

}  // namespace client
}  // namespace fastotv

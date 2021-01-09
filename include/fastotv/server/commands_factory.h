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

#include <string>  // for string

#include <common/daemon/commands/ping_info.h>

#include <fastotv/protocol/types.h>

#include <fastotv/commands_info/auth_info.h>
#include <fastotv/commands_info/catchup_generate_info.h>
#include <fastotv/commands_info/catchups_info.h>
#include <fastotv/commands_info/channels_info.h>
#include <fastotv/commands_info/content_requests_info.h>
#include <fastotv/commands_info/devices_info.h>
#include <fastotv/commands_info/runtime_channel_info.h>
#include <fastotv/commands_info/series_info.h>
#include <fastotv/commands_info/server_info.h>
#include <fastotv/commands_info/vods_info.h>

namespace fastotv {
namespace server {

// requests
common::Error PingRequest(protocol::sequance_id_t id,
                          const common::daemon::commands::ClientPingInfo& params,
                          protocol::request_t* req);

common::Error GetClientInfoRequest(protocol::sequance_id_t id, protocol::request_t* req);

// responses
common::Error ActivateDeviceResponseSuccess(protocol::sequance_id_t id,
                                            const commands_info::DevicesInfo& params,
                                            protocol::response_t* resp);
common::Error ActivateDeviceResponseFail(protocol::sequance_id_t id,
                                         const std::string& error_text,
                                         protocol::response_t* resp);

common::Error LoginResponseSuccess(protocol::sequance_id_t id,
                                   const commands_info::ServerAuthInfo& params,
                                   protocol::response_t* resp);
common::Error LoginResponseFail(protocol::sequance_id_t id, const std::string& error_text, protocol::response_t* resp);

// client ping
common::Error PingResponseSuccess(protocol::sequance_id_t id,
                                  const common::daemon::commands::ServerPingInfo& params,
                                  protocol::response_t* resp);

// server info
common::Error GetServerInfoResponseSuccess(protocol::sequance_id_t id,
                                           const commands_info::ServerInfo& params,
                                           protocol::response_t* resp);
common::Error GetServerInfoResponseFail(protocol::sequance_id_t id,
                                        const std::string& error_text,
                                        protocol::response_t* resp);

// channels
common::Error GetChannelsResponseSuccess(protocol::sequance_id_t id,
                                         const commands_info::ChannelsInfo& channels,
                                         const commands_info::VodsInfo& vods,
                                         const commands_info::ChannelsInfo& private_channels,
                                         const commands_info::VodsInfo& private_vods,
                                         const commands_info::CatchupsInfo& catchups,
                                         const commands_info::SeriesInfo& series,
                                         const commands_info::ContentRequestsInfo& requests,
                                         protocol::response_t* resp);
common::Error GetChannelsResponseFail(protocol::sequance_id_t id,
                                      const std::string& error_text,
                                      protocol::response_t* resp);

// runtimeChannel
common::Error GetRuntimeChannelInfoResponseSuccess(protocol::sequance_id_t id,
                                                   const commands_info::RuntimeChannelInfo& params,
                                                   protocol::response_t* resp);

// catchups info
common::Error CatchupGenerateResponseSuccess(protocol::sequance_id_t id,
                                             const commands_info::CatchupQueueInfo& params,
                                             protocol::response_t* resp);
common::Error CatchupGenerateResponseFail(protocol::sequance_id_t id,
                                          const std::string& error_text,
                                          protocol::response_t* resp);

// catchups undo info
common::Error CatchupUndoResponseSuccess(protocol::sequance_id_t id, protocol::response_t* resp);
common::Error CatchupUndoResponseFail(protocol::sequance_id_t id,
                                      const std::string& error_text,
                                      protocol::response_t* resp);

// content request
common::Error ContentRequestResponseSuccess(protocol::sequance_id_t id, protocol::response_t* resp);
common::Error ContentRequestResponseFail(protocol::sequance_id_t id,
                                         const std::string& error_text,
                                         protocol::response_t* resp);

common::Error FavoriteSuccess(protocol::sequance_id_t id, protocol::response_t* resp);
common::Error RecentSuccess(protocol::sequance_id_t id, protocol::response_t* resp);
common::Error InterruptStreamTimeSuccess(protocol::sequance_id_t id, protocol::response_t* resp);

}  // namespace server
}  // namespace fastotv

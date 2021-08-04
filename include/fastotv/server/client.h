/*  Copyright (C) 2014-2021 FastoGT. All right reserved.
    This file is part of iptv_cloud.
    iptv_cloud is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    iptv_cloud is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with iptv_cloud.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <memory>

#include <common/daemon/commands/ping_info.h>
#include <common/net/types.h>

#include <fastotv/client.h>
#include <fastotv/commands_info/auth_info.h>
#include <fastotv/commands_info/catchup_generate_info.h>
#include <fastotv/commands_info/catchups_info.h>
#include <fastotv/commands_info/channels_info.h>
#include <fastotv/commands_info/devices_info.h>
#include <fastotv/commands_info/runtime_channel_info.h>
#include <fastotv/commands_info/series_info.h>
#include <fastotv/commands_info/server_info.h>
#include <fastotv/commands_info/vods_info.h>
#include <fastotv/protocol/types.h>

namespace fastotv {
namespace server {

class Client : public ProtocoledClient {
 public:
  typedef ProtocoledClient base_class;
  Client(common::libev::IoLoop* server,
         const common::net::socket_info& info,
         compressor_t compressor = std::make_shared<protocol::FastoTVCompressor>());

  // requests
  common::ErrnoError Ping() WARN_UNUSED_RESULT;
  common::ErrnoError Ping(const common::daemon::commands::ClientPingInfo& ping) WARN_UNUSED_RESULT;

  common::ErrnoError GetClientInfo() WARN_UNUSED_RESULT;

  // responses
  common::ErrnoError CheckLoginFail(protocol::sequance_id_t id, common::Error err) WARN_UNUSED_RESULT;

  common::ErrnoError ActivateDeviceFail(protocol::sequance_id_t id, common::Error err) WARN_UNUSED_RESULT;
  common::ErrnoError ActivateDeviceSuccess(protocol::sequance_id_t id,
                                           const commands_info::DevicesInfo& devices) WARN_UNUSED_RESULT;

  common::ErrnoError LoginFail(protocol::sequance_id_t id, common::Error err) WARN_UNUSED_RESULT;
  common::ErrnoError LoginSuccess(protocol::sequance_id_t id,
                                  const commands_info::ServerAuthInfo& auth) WARN_UNUSED_RESULT;

  common::ErrnoError Pong(protocol::sequance_id_t id) WARN_UNUSED_RESULT;
  common::ErrnoError Pong(protocol::sequance_id_t id,
                          const common::daemon::commands::ServerPingInfo& pong) WARN_UNUSED_RESULT;

  common::ErrnoError GetServerInfoFail(protocol::sequance_id_t id, common::Error err) WARN_UNUSED_RESULT;
  common::ErrnoError GetServerInfoSuccess(protocol::sequance_id_t id,
                                          const commands_info::ServerInfo& serv) WARN_UNUSED_RESULT;

  common::ErrnoError GetChannelsFail(protocol::sequance_id_t id, common::Error err) WARN_UNUSED_RESULT;
  common::ErrnoError GetChannelsSuccess(protocol::sequance_id_t id,
                                        const commands_info::ChannelsInfo& channels,
                                        const commands_info::VodsInfo& vods,
                                        const commands_info::ChannelsInfo& private_channels,
                                        const commands_info::VodsInfo& private_vods,
                                        const commands_info::CatchupsInfo& catchups,
                                        const commands_info::SeriesInfo& series) WARN_UNUSED_RESULT;

  common::ErrnoError GetRuntimeChannelInfoSuccess(protocol::sequance_id_t id,
                                                  stream_id_t sid,
                                                  size_t watchers) WARN_UNUSED_RESULT;
  common::ErrnoError GetRuntimeChannelInfoSuccess(protocol::sequance_id_t id,
                                                  const commands_info::RuntimeChannelInfo& channel) WARN_UNUSED_RESULT;
  common::ErrnoError GetRuntimeChannelInfoFail(protocol::sequance_id_t id, common::Error err) WARN_UNUSED_RESULT;

  common::ErrnoError SetFavoriteInfoSuccess(protocol::sequance_id_t id) WARN_UNUSED_RESULT;
  common::ErrnoError SetFavoriteInfoFail(protocol::sequance_id_t id, common::Error err) WARN_UNUSED_RESULT;

  common::ErrnoError SetRecentInfoSuccess(protocol::sequance_id_t id) WARN_UNUSED_RESULT;
  common::ErrnoError SetRecentInfoFail(protocol::sequance_id_t id, common::Error err) WARN_UNUSED_RESULT;

  common::ErrnoError SetInterruptStreamTimeInfoSuccess(protocol::sequance_id_t id) WARN_UNUSED_RESULT;
  common::ErrnoError SetInterruptStreamTimeInfoFail(protocol::sequance_id_t id, common::Error err) WARN_UNUSED_RESULT;

  common::ErrnoError CatchupGenerateFail(protocol::sequance_id_t id, common::Error err) WARN_UNUSED_RESULT;
  common::ErrnoError CatchupGenerateSuccess(protocol::sequance_id_t id,
                                            const commands_info::CatchupQueueInfo& info) WARN_UNUSED_RESULT;

  common::ErrnoError CatchupUndoFail(protocol::sequance_id_t id, common::Error err) WARN_UNUSED_RESULT;
  common::ErrnoError CatchupUndoSuccess(protocol::sequance_id_t id) WARN_UNUSED_RESULT;

  common::ErrnoError ContentRequestFail(protocol::sequance_id_t id, common::Error err) WARN_UNUSED_RESULT;
  common::ErrnoError ContentRequestSuccess(protocol::sequance_id_t id) WARN_UNUSED_RESULT;
};

}  // namespace server
}  // namespace fastotv

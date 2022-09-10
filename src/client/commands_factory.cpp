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

#include <fastotv/client/commands_factory.h>
#include <fastotv/commands/commands.h>

namespace fastotv {
namespace client {

common::Error ActivateDeviceRequest(protocol::sequance_id_t id,
                                    const commands_info::LoginInfo& params,
                                    protocol::request_t* req) {
  if (!req) {
    return common::make_error_inval();
  }

  std::string login_str;
  common::Error err_ser = params.SerializeToString(&login_str);
  if (err_ser) {
    return err_ser;
  }

  protocol::request_t lreq;
  lreq.id = id;
  lreq.method = CLIENT_ACTIVATE_DEVICE;
  lreq.params = login_str;
  *req = lreq;
  return common::Error();
}

common::Error LoginRequest(protocol::sequance_id_t id,
                           const commands_info::AuthInfo& params,
                           protocol::request_t* req) {
  if (!req) {
    return common::make_error_inval();
  }

  std::string auth_str;
  common::Error err_ser = params.SerializeToString(&auth_str);
  if (err_ser) {
    return err_ser;
  }

  protocol::request_t lreq;
  lreq.id = id;
  lreq.method = CLIENT_LOGIN;
  lreq.params = auth_str;
  *req = lreq;
  return common::Error();
}

common::Error PingRequest(protocol::sequance_id_t id,
                          const common::daemon::commands::ServerPingInfo& params,
                          protocol::request_t* req) {
  if (!req) {
    return common::make_error_inval();
  }

  std::string ping_server_json;
  common::Error err_ser = params.SerializeToString(&ping_server_json);
  if (err_ser) {
    return err_ser;
  }

  protocol::request_t lreq;
  lreq.id = id;
  lreq.method = CLIENT_PING;
  lreq.params = ping_server_json;
  *req = lreq;
  return common::Error();
}

common::Error GetServerInfoRequest(protocol::sequance_id_t id, protocol::request_t* req) {
  if (!req) {
    return common::make_error_inval();
  }

  protocol::request_t lreq;
  lreq.id = id;
  lreq.method = CLIENT_GET_SERVER_INFO;
  *req = lreq;
  return common::Error();
}

common::Error GetChannelsRequest(protocol::sequance_id_t id, protocol::request_t* req) {
  if (!req) {
    return common::make_error_inval();
  }

  protocol::request_t lreq;
  lreq.id = id;
  lreq.method = CLIENT_GET_CHANNELS;
  *req = lreq;
  return common::Error();
}

common::Error GetRuntimeChannelInfoRequest(protocol::sequance_id_t id,
                                           const commands_info::RuntimeChannelLiteInfo& params,
                                           protocol::request_t* req) {
  if (!req) {
    return common::make_error_inval();
  }

  std::string run_json;
  common::Error err_ser = params.SerializeToString(&run_json);
  if (err_ser) {
    return err_ser;
  }

  protocol::request_t lreq;
  lreq.id = id;
  lreq.method = CLIENT_GET_RUNTIME_CHANNEL_INFO;
  lreq.params = run_json;
  *req = lreq;
  return common::Error();
}

common::Error CatchupRequest(protocol::sequance_id_t id,
                             const commands_info::CatchupGenerateInfo& params,
                             protocol::request_t* req) {
  if (!req) {
    return common::make_error_inval();
  }

  std::string run_json;
  common::Error err_ser = params.SerializeToString(&run_json);
  if (err_ser) {
    return err_ser;
  }

  protocol::request_t lreq;
  lreq.id = id;
  lreq.method = CLIENT_REQUEST_CATCHUP;
  lreq.params = run_json;
  *req = lreq;
  return common::Error();
}

common::Error CatchupUndoRequest(protocol::sequance_id_t id,
                                 const commands_info::CatchupUndoInfo& params,
                                 protocol::request_t* req) {
  if (!req) {
    return common::make_error_inval();
  }

  std::string run_json;
  common::Error err_ser = params.SerializeToString(&run_json);
  if (err_ser) {
    return err_ser;
  }

  protocol::request_t lreq;
  lreq.id = id;
  lreq.method = CLIENT_REQUEST_UNDO_CATCHUP;
  lreq.params = run_json;
  *req = lreq;
  return common::Error();
}

common::Error PingResponseSuccess(protocol::sequance_id_t id,
                                  const common::daemon::commands::ClientPingInfo& params,
                                  protocol::response_t* resp) {
  if (!resp) {
    return common::make_error_inval();
  }

  std::string ping_str;
  common::Error err_ser = params.SerializeToString(&ping_str);
  if (err_ser) {
    return err_ser;
  }

  *resp =
      protocol::response_t::MakeMessage(id, common::protocols::json_rpc::JsonRPCMessage::MakeSuccessMessage(ping_str));
  return common::Error();
}

common::Error SystemInfoResponseSuccess(protocol::sequance_id_t id,
                                        const commands_info::ClientInfo& params,
                                        protocol::response_t* resp) {
  if (!resp) {
    return common::make_error_inval();
  }

  std::string info_json;
  common::Error err_ser = params.SerializeToString(&info_json);
  if (err_ser) {
    return err_ser;
  }

  *resp =
      protocol::response_t::MakeMessage(id, common::protocols::json_rpc::JsonRPCMessage::MakeSuccessMessage(info_json));
  return common::Error();
}

common::Error NotificationTextSuccess(protocol::sequance_id_t id, protocol::response_t* resp) {
  if (!resp) {
    return common::make_error_inval();
  }

  *resp = protocol::response_t::MakeMessage(id, common::protocols::json_rpc::JsonRPCMessage::MakeSuccessMessage());
  return common::Error();
}

}  // namespace client
}  // namespace fastotv

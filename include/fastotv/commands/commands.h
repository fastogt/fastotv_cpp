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

#pragma once

// client commands
#define CLIENT_ACTIVATE_DEVICE "client_activate_device"
#define CLIENT_LOGIN "client_login"
#define CLIENT_PING "client_ping"  // ping server
#define CLIENT_GET_SERVER_INFO "get_server_info"
#define CLIENT_GET_CHANNELS "get_channels"
#define CLIENT_GET_RUNTIME_CHANNEL_INFO "get_runtime_channel_info"
#define CLIENT_REQUEST_CATCHUP "request_catchup"
#define CLIENT_REQUEST_UNDO_CATCHUP "undo_catchup"
#define CLIENT_SET_FAVORITE "set_favorite"
#define CLIENT_SET_RECENT "set_recent"
#define CLIENT_INTERRUPT_STREAM_TIME "interrupt_time"

// server commands
#define SERVER_PING "server_ping"  // ping client
#define SERVER_GET_CLIENT_INFO "get_client_info"
#define SERVER_TEXT_NOTIFICATION "send_message"

// request
// {"jsonrpc": "2.0", "method": "activate_request", "id": 11, "params": {"license_key":"%s"}}

// response
// {"jsonrpc": "2.0", "result": 11, "id": 11}

/*  Copyright (C) 2014-2023 FastoGT. All right reserved.

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

#include <fastotv/client.h>

namespace fastotv {

Client::Client(common::libev::IoLoop* server, const common::net::socket_info& info)
    : common::libev::tcp::TcpClient(server, info) {}

Client::~Client() {}

const char* Client::ClassName() const {
  return "Client";
}

ProtocoledClient::ProtocoledClient(common::libev::IoLoop* server,
                                   const common::net::socket_info& info,
                                   compressor_t compressor)
    : base_class(compressor, server, info) {}

}  // namespace fastotv

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

#include <string>

#include <common/types.h>  // for time64_t

namespace fastotv {

typedef std::string stream_id_t;  // must be unique
static const stream_id_t kInvalidStreamId = stream_id_t();
typedef uint32_t channel_id_t;

typedef std::string content_request_id_t;
typedef std::string serial_id_t;
typedef std::string login_t;           // unique, user email now
typedef std::string device_id_t;       // unique, mongodb id, registered by user
typedef std::string user_id_t;         // mongodb id in json
typedef size_t bandwidth_t;            // bytes/s
typedef common::time64_t timestamp_t;  // millisecond

enum StreamType : unsigned {
  PROXY = 0,
  VOD_PROXY = 1,
  RELAY = 2,
  ENCODE = 3,
  TIMESHIFT_PLAYER = 4,
  TIMESHIFT_RECORDER = 5,
  CATCHUP = 6,
  TEST_LIFE = 7,
  VOD_RELAY = 8,
  VOD_ENCODE = 9,
  COD_RELAY = 10,
  COD_ENCODE = 11,
  EVENT = 12,
  CV_DATA = 13,
  CHANGER_RELAY = 14,
  CHANGER_ENCODE = 15
};

}  // namespace fastotv

/*  Copyright (C) 2014-2019 FastoGT. All right reserved.
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

#include "gtest/gtest.h"

#include <common/macros.h>
#include <fastotv/types/output_uri.h>

#define RTMP_OUTPUT "rtmp://4.31.30.153:1935/devapp/tokengenffmpeg1"
#define HTTP_OUTPUT "/home/sasha/123/"

TEST(OutputUri, ConvertFromString) {
  const std::string invalid_uri_json = "{ \"id\": 0, \"uri\": \"\", \"http_root\": \"\", \"hls_type\": 0 }";
  fastotv::OutputUri invalid_uri;
  ASSERT_EQ(invalid_uri.GetID(), 0);
  ASSERT_EQ(invalid_uri.GetUrl(), common::uri::GURL());
  ASSERT_EQ(invalid_uri.GetHttpRoot(), fastotv::OutputUri::http_root_t());
  std::string conv;
  common::Error err = invalid_uri.SerializeToString(&conv);
  ASSERT_TRUE(err);

  const std::string uri_json = "{ \"id\": 1, \"uri\": \"" RTMP_OUTPUT "\", \"http_root\": \"" HTTP_OUTPUT
                               "\", \"size\": \"0x0\", \"video_bitrate\": 0, \"audio_bitrate\": 0 }";
  fastotv::OutputUri uri;
  err = uri.DeSerializeFromString(uri_json);
  ASSERT_FALSE(err);
  ASSERT_EQ(uri.GetID(), 1);
  common::uri::GURL ro(RTMP_OUTPUT);
  ASSERT_EQ(uri.GetUrl(), ro);
  ASSERT_EQ(uri.GetHttpRoot(), common::file_system::ascii_directory_string_path(HTTP_OUTPUT));

  err = uri.SerializeToString(&conv);
  ASSERT_FALSE(err);
}

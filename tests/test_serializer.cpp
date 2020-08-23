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

#include <gtest/gtest.h>

#include <fastotv/commands_info/auth_info.h>
#include <fastotv/commands_info/catchup_generate_info.h>
#include <fastotv/commands_info/catchup_info.h>
#include <fastotv/commands_info/catchup_undo_info.h>
#include <fastotv/commands_info/channel_info.h>
#include <fastotv/commands_info/channels_info.h>
#include <fastotv/commands_info/client_info.h>
#include <fastotv/commands_info/content_request_info.h>
#include <fastotv/commands_info/device_info.h>
#include <fastotv/commands_info/epg_info.h>
#include <fastotv/commands_info/favorite_info.h>
#include <fastotv/commands_info/interrupt_stream_time_info.h>
#include <fastotv/commands_info/machine_info.h>
#include <fastotv/commands_info/movie_info.h>
#include <fastotv/commands_info/notification_text_info.h>
#include <fastotv/commands_info/operation_system_info.h>
#include <fastotv/commands_info/programme_info.h>
#include <fastotv/commands_info/runtime_channel_info.h>
#include <fastotv/commands_info/serial_info.h>
#include <fastotv/commands_info/server_info.h>

typedef fastotv::commands_info::AuthInfo::serialize_type serialize_t;

TEST(ChannelInfo, serialize_deserialize) {
  const std::string name = "alex";
  const fastotv::stream_id_t stream_id = "123";
  const common::uri::GURL url("http://localhost:8080/hls/69_avformat_test_alex_2/play.m3u8");
  const bool enable_video = false;
  const bool enable_audio = true;

  fastotv::commands_info::EpgInfo::urls_t urls = {url};
  fastotv::commands_info::EpgInfo epg_info(stream_id, urls, name);
  ASSERT_EQ(epg_info.GetDisplayName(), name);
  ASSERT_EQ(epg_info.GetTvgID(), stream_id);
  ASSERT_EQ(epg_info.GetUrls(), urls);

  serialize_t user;
  common::Error err = epg_info.Serialize(&user);
  ASSERT_TRUE(!err);
  fastotv::commands_info::EpgInfo depg;
  err = depg.DeSerialize(user);
  ASSERT_TRUE(!err);

  ASSERT_EQ(epg_info, depg);

  fastotv::commands_info::ChannelInfo http_uri(stream_id, {}, 0, false, false, 0, epg_info, enable_audio, enable_video,
                                               {}, 0, false, {});
  ASSERT_EQ(http_uri.GetStreamID(), stream_id);
  ASSERT_EQ(http_uri.IsEnableAudio(), enable_audio);
  ASSERT_EQ(http_uri.IsEnableVideo(), enable_video);

  serialize_t ser;
  err = http_uri.Serialize(&ser);
  ASSERT_TRUE(!err);
  fastotv::commands_info::ChannelInfo dhttp_uri;
  err = dhttp_uri.DeSerialize(ser);
  ASSERT_TRUE(!err);

  ASSERT_EQ(http_uri, dhttp_uri);

  const std::string channel_inf_json =
      R""({"audio": true, "video": true, "id": "5d0db38335c23f2dd95e803d", "epg": {"icon": "https://upload.wikimedia.org/wikipedia/commons/thumb/0/0c/Channel_NewsAsia_logo_%28shape_only%29.svg/220px-Channel_NewsAsia_logo_%28shape_only%29.svg.png", "urls": ["https://drsh196ivjwe8.cloudfront.net/hls/cnai/03.m3u8?fluxustv.m3u8"], "display_name": "Channel NewsAsia (Opt-1)", "id": "", "programs": []}})"";
  fastotv::commands_info::ChannelInfo chan;
  err = chan.DeSerializeFromString(channel_inf_json);
  ASSERT_TRUE(!err);
}

TEST(ServerInfo, serialize_deserialize) {
  const common::uri::GURL url("http://localhost/index.html");
  fastotv::commands_info::ServerInfo serv_info(url, "");

  serialize_t ser;
  common::Error err = serv_info.Serialize(&ser);
  ASSERT_FALSE(err);
  fastotv::commands_info::ServerInfo dser;
  err = dser.DeSerialize(ser);
  ASSERT_FALSE(err);
  std::string out;
  err = dser.SerializeToString(&out);
  ASSERT_FALSE(err);
}

TEST(EpgInfo, serialize_deserialize) {
  const fastotv::commands_info::EpgInfo::tvg_id_t id = "tid";
  const common::uri::GURL uri("http://fasotgt.com:8080/master.m3u8");
  const std::string name = "test";

  fastotv::commands_info::EpgInfo::urls_t urls = {uri};
  fastotv::commands_info::EpgInfo epg(id, urls, name);
  ASSERT_TRUE(epg.IsValid());
  serialize_t ser;
  common::Error err = epg.Serialize(&ser);
  ASSERT_TRUE(!err);

  fastotv::commands_info::EpgInfo dser;
  ASSERT_TRUE(!dser.IsValid());
  err = dser.DeSerialize(ser);
  ASSERT_TRUE(!err);
  ASSERT_TRUE(dser.IsValid());

  ASSERT_EQ(epg.GetTvgID(), dser.GetTvgID());
  ASSERT_EQ(epg.GetUrls(), dser.GetUrls());
  ASSERT_EQ(epg.GetDisplayName(), dser.GetDisplayName());
  ASSERT_EQ(epg, dser);
}

TEST(ProgrammeInfo, serialize_deserialize) {
  const fastotv::stream_id_t id = "1234";
  const fastotv::timestamp_t start_time = 1;
  const fastotv::timestamp_t stop_time = 123;
  const std::string title = "tit";

  fastotv::commands_info::ProgrammeInfo prog(id, start_time, stop_time, title, std::string(), std::string());
  ASSERT_TRUE(prog.IsValid());
  ASSERT_EQ(prog.GetChannel(), id);
  ASSERT_EQ(prog.GetStart(), start_time);
  ASSERT_EQ(prog.GetStop(), stop_time);
  ASSERT_EQ(prog.GetTitle(), title);

  serialize_t ser;
  common::Error err = prog.Serialize(&ser);
  ASSERT_TRUE(!err);

  fastotv::commands_info::ProgrammeInfo dser;
  ASSERT_TRUE(!dser.IsValid());
  err = dser.DeSerialize(ser);
  ASSERT_TRUE(!err);

  ASSERT_EQ(prog.GetChannel(), dser.GetChannel());
  ASSERT_EQ(prog.GetStart(), dser.GetStart());
  ASSERT_EQ(prog.GetStop(), dser.GetStop());
  ASSERT_EQ(prog.GetTitle(), dser.GetTitle());
  ASSERT_EQ(prog, dser);
}

TEST(ClientInfo, serialize_deserialize) {
  const fastotv::login_t login = "Alex";
  const fastotv::device_id_t deva = "12345";
  const std::string os = "Os";
  const std::string os_version = "123";
  const std::string cpu_brand = "brand";
  const std::string arch = "x64";
  const int64_t ram_total = 1;
  const int64_t ram_free = 2;

  fastotv::commands_info::OperationSystemInfo ops(os, os_version, arch, ram_total, ram_free);
  ASSERT_EQ(ops.GetRamBytesTotal(), ram_total);
  ASSERT_EQ(ops.GetRamBytesFree(), ram_free);

  fastotv::commands_info::ProjectInfo proj("fastocloud", "1.2.3");

  fastotv::commands_info::ClientInfo cinf(login, deva, proj, ops, cpu_brand);
  ASSERT_EQ(cinf.GetLogin(), login);
  ASSERT_EQ(cinf.GetOs(), ops);
  ASSERT_EQ(cinf.GetCpuBrand(), cpu_brand);

  serialize_t ser;
  common::Error err = cinf.Serialize(&ser);
  ASSERT_TRUE(!err);
  fastotv::commands_info::ClientInfo dcinf;
  err = dcinf.DeSerialize(ser);
  ASSERT_TRUE(!err);

  ASSERT_EQ(cinf.GetLogin(), dcinf.GetLogin());
  ASSERT_EQ(cinf.GetOs(), dcinf.GetOs());
  ASSERT_EQ(cinf.GetCpuBrand(), dcinf.GetCpuBrand());

  ASSERT_EQ(cinf, dcinf);
}

TEST(channels_t, serialize_deserialize) {
  const std::string name = "alex";
  const fastotv::stream_id_t stream_id = "123";
  const common::uri::GURL url("http://localhost:8080/hls/69_avformat_test_alex_2/play.m3u8");
  const bool enable_video = false;
  const bool enable_audio = true;

  fastotv::commands_info::EpgInfo::urls_t urls = {url};
  fastotv::commands_info::ChannelsInfo channels;
  fastotv::commands_info::EpgInfo epg_info(stream_id, urls, name);
  channels.Add(fastotv::commands_info::ChannelInfo(stream_id, {}, 0, true, false, 0, epg_info, enable_audio,
                                                   enable_video, {}, 0, 0, {}));
  ASSERT_EQ(channels.Get().size(), 1);

  serialize_t ser;
  common::Error err = channels.Serialize(&ser);
  ASSERT_TRUE(!err);
  fastotv::commands_info::ChannelsInfo dchannels;
  err = dchannels.DeSerialize(ser);
  ASSERT_TRUE(!err);

  ASSERT_EQ(channels, dchannels);
}

TEST(AuthInfo, serialize_deserialize) {
  const std::string login = "palec";
  const std::string password = "ff";
  const std::string device = "dev";
  fastotv::commands_info::LoginInfo log(login, password);
  fastotv::commands_info::AuthInfo auth_info(log, device);
  ASSERT_EQ(auth_info.GetLogin(), login);
  ASSERT_EQ(auth_info.GetPassword(), password);
  ASSERT_EQ(auth_info.GetDeviceID(), device);
  serialize_t ser;
  common::Error err = auth_info.Serialize(&ser);
  ASSERT_TRUE(!err);
  fastotv::commands_info::AuthInfo dser;
  err = dser.DeSerialize(ser);
  ASSERT_TRUE(!err);

  ASSERT_EQ(auth_info, dser);
}

TEST(RuntimeChannelInfo, serialize_deserialize) {
  const std::string channel_id = "1234";
  const size_t watchers = 7;
  fastotv::commands_info::RuntimeChannelInfo rinf_info(channel_id, watchers);
  ASSERT_EQ(rinf_info.GetStreamID(), channel_id);
  ASSERT_EQ(rinf_info.GetWatchersCount(), watchers);
  serialize_t ser;
  common::Error err = rinf_info.Serialize(&ser);
  ASSERT_TRUE(!err);
  fastotv::commands_info::RuntimeChannelInfo dser;
  err = dser.DeSerialize(ser);
  ASSERT_TRUE(!err);

  ASSERT_EQ(rinf_info, dser);
}

TEST(DeviceInfo, serialize_deserialize) {
  const std::string did = "1234";
  const std::string name = "Android";
  fastotv::commands_info::DeviceInfo devi_info(did, name);
  ASSERT_EQ(devi_info.GetDeviceID(), did);
  ASSERT_EQ(devi_info.GetName(), name);
  serialize_t ser;
  common::Error err = devi_info.Serialize(&ser);
  ASSERT_TRUE(!err);
  fastotv::commands_info::DeviceInfo dser;
  err = dser.DeSerialize(ser);
  ASSERT_TRUE(!err);

  ASSERT_EQ(devi_info, dser);
}

TEST(SerialInfo, serialize_deserialize) {
  const std::string sid = "1234";
  const std::string name = "Termiantor";
  const common::uri::GURL icon("http://localhost:8080/hls/69_avformat_test_alex_2/play.png");
  const fastotv::commands_info::SerialInfo::groups_t groups = {"Movie"};
  const std::string descr = "Description";
  const size_t season = 3;
  const fastotv::commands_info::SerialInfo::episodes_t epis = {"1234", "4543"};
  const size_t views = 11;
  fastotv::commands_info::SerialInfo serial(sid, name, icon, groups, descr, season, epis, views);
  ASSERT_EQ(serial.GetSerialID(), sid);
  ASSERT_EQ(serial.GetIcon(), icon);
  ASSERT_EQ(serial.GetGroups(), groups);
  ASSERT_EQ(serial.GetDescription(), descr);
  ASSERT_EQ(serial.GetSeason(), season);
  ASSERT_EQ(serial.GetEpisodes(), epis);
  ASSERT_EQ(serial.GetViewCount(), views);

  serialize_t ser;
  common::Error err = serial.Serialize(&ser);
  ASSERT_TRUE(!err);
  fastotv::commands_info::SerialInfo dser;
  err = dser.DeSerialize(ser);
  ASSERT_TRUE(!err);

  ASSERT_EQ(serial, dser);
}

TEST(CatchupGenerateInfo, serialize_deserialize) {
  fastotv::stream_id_t sid = "3211";
  std::string title = "some";
  fastotv::timestamp_t start_time = 1444;
  fastotv::timestamp_t stop_time = 6664;
  fastotv::commands_info::CatchupGenerateInfo cat_info(sid, title, start_time, stop_time);
  ASSERT_EQ(cat_info.GetStreamID(), sid);
  ASSERT_EQ(cat_info.GetTitle(), title);
  ASSERT_EQ(cat_info.GetStart(), start_time);
  ASSERT_EQ(cat_info.GetStop(), stop_time);
  serialize_t ser;
  common::Error err = cat_info.Serialize(&ser);
  ASSERT_TRUE(!err);
  fastotv::commands_info::CatchupGenerateInfo dser;
  err = dser.DeSerialize(ser);
  ASSERT_TRUE(!err);

  ASSERT_EQ(cat_info, dser);
}

TEST(CatchupInfo, serialize_deserialize) {
  const std::string sid = "1234";
  const std::string name = "Termiantor";
  const fastotv::commands_info::CatchupInfo::iarc_t iarc = 11;
  const fastotv::commands_info::CatchupInfo::groups_t groups = {"Movie"};
  const bool favorite = false;
  const fastotv::timestamp_t recent = 1234;
  const fastotv::timestamp_t interruption_time = 3333;
  const fastotv::stream_id_t stream_id = "123";
  const common::uri::GURL url("http://localhost:8080/hls/69_avformat_test_alex_2/play.m3u8");
  fastotv::commands_info::EpgInfo epg_info(stream_id, {url}, name);
  bool enable_audio = false;
  bool enable_video = true;
  const fastotv::commands_info::CatchupInfo::parts_t parts;
  const size_t views = 11;
  bool locked = false;
  fastotv::commands_info::CatchupInfo::meta_urls_t urls;
  urls.Add(fastotv::MetaUrl("Some", common::uri::GURL("http://localhost:8080/hls/69_avformat_test_alex_2/play.png")));
  const fastotv::timestamp_t start = 111;
  const fastotv::timestamp_t stop = 333;

  fastotv::commands_info::CatchupInfo cat_info(sid, groups, iarc, favorite, recent, interruption_time, epg_info,
                                               enable_audio, enable_video, parts, views, locked, urls, start, stop);
  ASSERT_EQ(cat_info.GetStreamID(), sid);
  ASSERT_EQ(cat_info.GetGroups(), groups);
  ASSERT_EQ(cat_info.GetIARC(), iarc);
  ASSERT_EQ(cat_info.GetFavorite(), favorite);
  ASSERT_EQ(cat_info.GetRecent(), recent);
  ASSERT_EQ(cat_info.GetInterruptionTime(), interruption_time);
  ASSERT_EQ(cat_info.GetEpg(), epg_info);
  ASSERT_EQ(cat_info.GetParts(), parts);
  ASSERT_EQ(cat_info.GetViewCount(), views);
  ASSERT_EQ(cat_info.GetLocked(), locked);
  ASSERT_EQ(cat_info.GetMetaUrls(), urls);
  ASSERT_EQ(cat_info.GetStart(), start);
  ASSERT_EQ(cat_info.GetStop(), stop);

  serialize_t ser;
  common::Error err = cat_info.Serialize(&ser);
  ASSERT_TRUE(!err);
  fastotv::commands_info::CatchupInfo dser;
  err = dser.DeSerialize(ser);
  ASSERT_TRUE(!err);

  ASSERT_EQ(cat_info, dser);
}

TEST(CatchupUndoInfo, serialize_deserialize) {
  const fastotv::stream_id_t channel_id = "1234";
  fastotv::commands_info::CatchupUndoInfo rinf_info(channel_id);
  ASSERT_EQ(rinf_info.GetStreamID(), channel_id);
  serialize_t ser;
  common::Error err = rinf_info.Serialize(&ser);
  ASSERT_TRUE(!err);
  fastotv::commands_info::CatchupUndoInfo dser;
  err = dser.DeSerialize(ser);
  ASSERT_TRUE(!err);

  ASSERT_EQ(rinf_info, dser);
}

TEST(CreateContentRequestInfo, serialize_deserialize) {
  const std::string text = "Test";
  const fastotv::commands_info::CreateContentRequestInfo::ContentType cont =
      fastotv::commands_info::CreateContentRequestInfo::VODS;
  const fastotv::commands_info::CreateContentRequestInfo::RequestStatus res =
      fastotv::commands_info::CreateContentRequestInfo::DONE;

  fastotv::commands_info::CreateContentRequestInfo rinf_info(text, cont, res);
  ASSERT_EQ(rinf_info.GetText(), text);
  ASSERT_EQ(rinf_info.GetType(), cont);
  ASSERT_EQ(rinf_info.GetStatus(), res);
  serialize_t ser;
  common::Error err = rinf_info.Serialize(&ser);
  ASSERT_TRUE(!err);
  fastotv::commands_info::CreateContentRequestInfo dser;
  err = dser.DeSerialize(ser);
  ASSERT_TRUE(!err);

  ASSERT_EQ(rinf_info, dser);
}

TEST(FavoriteInfo, serialize_deserialize) {
  const fastotv::stream_id_t channel_id = "1234";
  const bool fav = false;
  fastotv::commands_info::FavoriteInfo rinf_info(channel_id, fav);
  ASSERT_EQ(rinf_info.GetChannel(), channel_id);
  ASSERT_EQ(rinf_info.GetFavorite(), fav);
  serialize_t ser;
  common::Error err = rinf_info.Serialize(&ser);
  ASSERT_TRUE(!err);
  fastotv::commands_info::FavoriteInfo dser;
  err = dser.DeSerialize(ser);
  ASSERT_TRUE(!err);

  ASSERT_EQ(rinf_info, dser);
}

TEST(InterruptStreamTimeInfo, serialize_deserialize) {
  const fastotv::stream_id_t channel_id = "1234";
  const fastotv::timestamp_t ts = 1234;
  fastotv::commands_info::InterruptStreamTimeInfo rinf_info(channel_id, ts);
  ASSERT_EQ(rinf_info.GetChannel(), channel_id);
  ASSERT_EQ(rinf_info.GetTime(), ts);
  serialize_t ser;
  common::Error err = rinf_info.Serialize(&ser);
  ASSERT_TRUE(!err);
  fastotv::commands_info::InterruptStreamTimeInfo dser;
  err = dser.DeSerialize(ser);
  ASSERT_TRUE(!err);

  ASSERT_EQ(rinf_info, dser);
}

TEST(MachineInfo, serialize_deserialize) {
  fastotv::commands_info::MachineInfo::cpu_load_t cpu_load = 0.1;
  fastotv::commands_info::MachineInfo::gpu_load_t gpu_load = 3.33;
  const std::string load_average = "123 333 555";
  size_t ram_bytes_total = 100;
  size_t ram_bytes_free = 223;
  size_t hdd_bytes_total = 555;
  size_t hdd_bytes_free = 45;
  fastotv::bandwidth_t net_bytes_recv = 11;
  fastotv::bandwidth_t net_bytes_send = 53;
  time_t uptime = 2334;
  fastotv::timestamp_t timestamp = 122355;
  size_t net_total_bytes_recv = 54431;
  size_t net_total_bytes_send = 324;
  fastotv::commands_info::MachineInfo rinf_info(cpu_load, gpu_load, load_average, ram_bytes_total, ram_bytes_free,
                                                hdd_bytes_total, hdd_bytes_free, net_bytes_recv, net_bytes_send, uptime,
                                                timestamp, net_total_bytes_recv, net_total_bytes_send);
  ASSERT_EQ(rinf_info.GetCpuLoad(), cpu_load);
  ASSERT_EQ(rinf_info.GetGpuLoad(), gpu_load);
  ASSERT_EQ(rinf_info.GetLoadAverage(), load_average);
  ASSERT_EQ(rinf_info.GetRamBytesTotal(), ram_bytes_total);
  ASSERT_EQ(rinf_info.GetRamBytesFree(), ram_bytes_free);
  ASSERT_EQ(rinf_info.GetHddBytesTotal(), hdd_bytes_total);
  ASSERT_EQ(rinf_info.GetHddBytesFree(), hdd_bytes_free);
  ASSERT_EQ(rinf_info.GetNetBytesRecv(), net_bytes_recv);
  ASSERT_EQ(rinf_info.GetNetBytesSend(), net_bytes_send);
  ASSERT_EQ(rinf_info.GetUptime(), uptime);
  ASSERT_EQ(rinf_info.GetTimestamp(), timestamp);
  ASSERT_EQ(rinf_info.GetNetTotalBytesRecv(), net_total_bytes_recv);
  ASSERT_EQ(rinf_info.GetNetTotalBytesSend(), net_total_bytes_send);

  serialize_t ser;
  common::Error err = rinf_info.Serialize(&ser);
  ASSERT_TRUE(!err);
  fastotv::commands_info::MachineInfo dser;
  err = dser.DeSerialize(ser);
  ASSERT_TRUE(!err);

  ASSERT_EQ(rinf_info, dser);
}

TEST(MovieInfo, serialize_deserialize) {
  const std::string name = "Some";
  const fastotv::commands_info::MovieInfo::urls_t urls = {
      common::uri::GURL("http://localhost:8080/hls/69_avformat_test_alex_2/play.png")};
  const std::string description = "Desc";
  const fastotv::commands_info::MovieInfo::url_t preview_icon =
      common::uri::GURL("http://localhost:8080/hls/69_avformat_test_alex_2/play1.png");
  const fastotv::commands_info::MovieInfo::url_t trailer_url =
      common::uri::GURL("http://localhost:8080/hls/69_avformat_test_alex_2/play2.png");
  double user_score = 12.33;
  fastotv::timestamp_t prime_date = 1234;
  const std::string country = "USA";
  fastotv::timestamp_t duration = 442;
  fastotv::commands_info::MovieInfo::Type type = fastotv::commands_info::MovieInfo::SERIES;

  fastotv::commands_info::MovieInfo rinf_info(name, urls, description, preview_icon, trailer_url, user_score,
                                              prime_date, country, duration, type);
  ASSERT_EQ(rinf_info.GetName(), name);
  ASSERT_EQ(rinf_info.GetUrls(), urls);
  ASSERT_EQ(rinf_info.GetDescription(), description);
  ASSERT_EQ(rinf_info.GetPreviewIcon(), preview_icon);
  ASSERT_EQ(rinf_info.GetTrailerUrl(), trailer_url);
  ASSERT_EQ(rinf_info.GetUserScore(), user_score);
  ASSERT_EQ(rinf_info.GetPrimeDate(), prime_date);
  ASSERT_EQ(rinf_info.GetCountry(), country);
  ASSERT_EQ(rinf_info.GetDuration(), duration);
  ASSERT_EQ(rinf_info.GetType(), type);
  serialize_t ser;
  common::Error err = rinf_info.Serialize(&ser);
  ASSERT_TRUE(!err);
  fastotv::commands_info::MovieInfo dser;
  err = dser.DeSerialize(ser);
  ASSERT_TRUE(!err);

  ASSERT_EQ(rinf_info, dser);
}

TEST(NotificationTextInfo, serialize_deserialize) {
  const std::string msg = "1234";
  const fastotv::commands_info::NotificationTextInfo::MessageType mt =
      fastotv::commands_info::NotificationTextInfo::HYPERLINK;
  const common::time64_t sh = 1000;
  fastotv::commands_info::NotificationTextInfo rinf_info(msg, mt, sh);
  ASSERT_EQ(rinf_info.GetText(), msg);
  ASSERT_EQ(rinf_info.GetType(), mt);
  ASSERT_EQ(rinf_info.GetShowTime(), sh);
  serialize_t ser;
  common::Error err = rinf_info.Serialize(&ser);
  ASSERT_TRUE(!err);
  fastotv::commands_info::NotificationTextInfo dser;
  err = dser.DeSerialize(ser);
  ASSERT_TRUE(!err);

  ASSERT_EQ(rinf_info, dser);
}

TEST(OperationSystemInfo, serialize_deserialize) {
  const std::string name = "Windows";
  const std::string version = "4.3";
  const std::string arch = "arm";
  size_t ram_total = 12354;
  size_t ram_free = 3244;

  fastotv::commands_info::OperationSystemInfo rinf_info(name, version, arch, ram_total, ram_free);
  ASSERT_EQ(rinf_info.GetName(), name);
  ASSERT_EQ(rinf_info.GetVersion(), version);
  ASSERT_EQ(rinf_info.GetArch(), arch);
  ASSERT_EQ(rinf_info.GetRamBytesTotal(), ram_total);
  ASSERT_EQ(rinf_info.GetRamBytesFree(), ram_free);
  serialize_t ser;
  common::Error err = rinf_info.Serialize(&ser);
  ASSERT_TRUE(!err);
  fastotv::commands_info::OperationSystemInfo dser;
  err = dser.DeSerialize(ser);
  ASSERT_TRUE(!err);

  ASSERT_EQ(rinf_info, dser);
}

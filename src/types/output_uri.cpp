/*  Copyright (C) 2014-2023 FastoGT. All right reserved.
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

#include <fastotv/types/output_uri.h>

#define HLSSINK_TYPE_FIELD "hlssink_type"
#define HTTP_ROOT_FIELD "http_root"
#define HLS_TYPE_FIELD "hls_type"
#define HTTP_HEADERS_FIELD "http_headers"
#define WHIP_FIELD "whip"
#define CHUNK_DURATION_FIELD "chunk_duration"
#define PLAYLIST_ROOT_FIELD "playlist_root"
#define SRT_MODE_FIELD "srt_mode"
#define SRT_KEY_FIELD "srt_key"
#define RTMPSINK_TYPE_FILED "rtmpsink_type"
#define KVS_FIELD "kvs"
#define AWS_FIELD "aws"
#define AZURE_FIELD "azure"
#define NDI_FIELD "ndi"
#define GOOGLE_FIELD "google"
#define WEBRTC_FIELD "webrtc"
#define MULTICAST_IFACE_FIELD "multicast_iface"

namespace fastotv {

OutputUri::OutputUri() : OutputUri(0, url_t()) {}

OutputUri::OutputUri(uri_id_t id, const url_t& url)
    : base_class(id, url),
      hlssink_type_(),
      http_root_(),
      hls_type_(),
      chunk_duration_(),
      playlist_root_(),
      whip_(),
      http_headers_(),
      srt_mode_(),
      srt_key_(),
      rtmpsink_type_(),
      kvs_(),
      aws_(),
      azure_(),
      ndi_(),
      google_(),
      webrtc_() {}

bool OutputUri::IsValid() const {
  return base_class::IsValid();
}

bool OutputUri::IsHls() const {
  DCHECK(IsValid());
  const auto url = GetUrl();
  if (!url.SchemeIsHTTPOrHTTPS()) {
    return false;
  }

  if (GetWhip()) {
    return false;
  }

  if (GetHlsSinkType() && GetHttpRoot() && GetHlsType()) {
    return true;
  }

  return false;
}

OutputUri::rtmp_type_t OutputUri::GetRtmpSinkType() const {
  return rtmpsink_type_;
}

void OutputUri::SetRtmpSinkType(rtmp_type_t rtmpsink) {
  rtmpsink_type_ = rtmpsink;
}

OutputUri::hlssink_type_t OutputUri::GetHlsSinkType() const {
  return hlssink_type_;
}

void OutputUri::SetHlsSinkType(hlssink_type_t hlssink) {
  hlssink_type_ = hlssink;
}

OutputUri::http_headers_t OutputUri::GetHttpHeaders() const {
  return http_headers_;
}

void OutputUri::SetHttpHeaders(const http_headers_t& head) {
  http_headers_ = head;
}

OutputUri::http_root_t OutputUri::GetHttpRoot() const {
  return http_root_;
}

void OutputUri::SetHttpRoot(const http_root_t& root) {
  http_root_ = root;
}

OutputUri::chunk_duration_t OutputUri::GetChunkDuration() const {
  return chunk_duration_;
}

void OutputUri::SetChunkDuration(chunk_duration_t duration) {
  chunk_duration_ = duration;
}

OutputUri::hls_t OutputUri::GetHlsType() const {
  return hls_type_;
}

void OutputUri::SetHlsType(hls_t type) {
  hls_type_ = type;
}

OutputUri::whip_t OutputUri::GetWhip() const {
  return whip_;
}

void OutputUri::SetWhip(whip_t whip) {
  whip_ = whip;
}

OutputUri::srt_mode_t OutputUri::GetSrtMode() const {
  return srt_mode_;
}

void OutputUri::SetSrtMode(srt_mode_t mode) {
  srt_mode_ = mode;
}

OutputUri::srt_key_t OutputUri::GetSrtKey() const {
  return srt_key_;
}

void OutputUri::SetSrtKey(const srt_key_t& pass) {
  srt_key_ = pass;
}

OutputUri::playlist_root_t OutputUri::GetPlaylistRoot() const {
  return playlist_root_;
}

void OutputUri::SetPlaylistRoot(const OutputUri::playlist_root_t& playlist) {
  playlist_root_ = playlist;
}

OutputUri::kvs_t OutputUri::GetKVS() const {
  return kvs_;
}

void OutputUri::SetKVS(const kvs_t& kvs) {
  kvs_ = kvs;
}

OutputUri::aws_t OutputUri::GetAWS() const {
  return aws_;
}

void OutputUri::SetAWS(const aws_t& aws) {
  aws_ = aws;
}

OutputUri::ndi_t OutputUri::GetNDI() const {
  return ndi_;
}

void OutputUri::SetNDI(const ndi_t& ndi) {
  ndi_ = ndi;
}

OutputUri::azure_t OutputUri::GetAzure() const {
  return azure_;
}

void OutputUri::SetAzure(const OutputUri::azure_t& azure) {
  azure_ = azure;
}

OutputUri::google_t OutputUri::GetGoogle() const {
  return google_;
}

void OutputUri::SetGoogle(const google_t& google) {
  google_ = google;
}

OutputUri::webrtc_t OutputUri::GetWebRTC() const {
  return webrtc_;
}

void OutputUri::SetWebRTC(const webrtc_t& web) {
  webrtc_ = web;
}

OutputUri::multicast_iface_t OutputUri::GetMulticastIface() const {
  return iface_;
}

void OutputUri::SetMulticastIface(multicast_iface_t iface) {
  iface_ = iface;
}

bool OutputUri::Equals(const OutputUri& url) const {
  return base_class::Equals(url) && hlssink_type_ == url.hlssink_type_ && http_root_ == url.http_root_ &&
         hls_type_ == url.hls_type_ && chunk_duration_ == url.chunk_duration_ && playlist_root_ == url.playlist_root_ &&
         whip_ == url.whip_ && http_headers_ == url.http_headers_ && srt_key_ == url.srt_key_ &&
         srt_mode_ == url.srt_mode_ && kvs_ == url.kvs_ && aws_ == url.aws_ && azure_ == url.azure_ &&
         ndi_ == url.ndi_ && google_ == url.google_ && webrtc_ == url.webrtc_;
}

common::Optional<OutputUri> OutputUri::Make(common::HashValue* hash) {
  if (!hash) {
    return common::Optional<OutputUri>();
  }

  common::Optional<OutputUrl> base = base_class::Make(hash);
  if (!base) {
    return common::Optional<OutputUri>();
  }

  OutputUri url(base->GetID(), base->GetUrl());
  int64_t hlssink2;
  common::Value* hlssink2_field = hash->Find(HLSSINK_TYPE_FIELD);
  if (hlssink2_field && hlssink2_field->GetAsInteger64(&hlssink2)) {
    url.SetHlsSinkType(static_cast<HlsSinkType>(hlssink2));
  }

  std::string http_root_str;
  common::Value* http_root_str_field = hash->Find(HTTP_ROOT_FIELD);
  if (http_root_str_field && http_root_str_field->GetAsBasicString(&http_root_str)) {
    const common::file_system::ascii_directory_string_path http_root(http_root_str);
    url.SetHttpRoot(http_root);
  }

  int64_t hls_type;
  common::Value* hls_type_field = hash->Find(HLS_TYPE_FIELD);
  if (hls_type_field && hls_type_field->GetAsInteger64(&hls_type)) {
    url.SetHlsType(static_cast<HlsType>(hls_type));
  }

  int64_t chunk_duration;
  common::Value* chunk_duration_field = hash->Find(CHUNK_DURATION_FIELD);
  if (chunk_duration_field && chunk_duration_field->GetAsInteger64(&chunk_duration)) {
    url.SetChunkDuration(chunk_duration);
  }

  std::string playlist_root;
  common::Value* playlist_field = hash->Find(PLAYLIST_ROOT_FIELD);
  if (playlist_field && playlist_field->GetAsBasicString(&playlist_root)) {
    url.SetPlaylistRoot(common::uri::GURL(playlist_root));
  }

  common::HashValue* whip;
  common::Value* whip_field = hash->Find(WHIP_FIELD);
  if (whip_field && whip_field->GetAsHash(&whip)) {
    url.SetWhip(WhipProp::Make(whip));
  }

  common::Value* headers_field = hash->Find(HTTP_HEADERS_FIELD);
  common::ArrayValue* headers_array = nullptr;
  if (headers_field && headers_field->GetAsList(&headers_array)) {
    http_headers_t::value_type headers;
    for (size_t i = 0; i < headers_array->GetSize(); ++i) {
      common::Value* head = nullptr;
      common::HashValue* head_item = nullptr;
      if (headers_array->Get(i, &head) && head->GetAsHash(&head_item)) {
        const auto murl = HttpHeader::Make(head_item);
        if (murl) {
          headers.Add(*murl);
        }
      }
    }
    url.SetHttpHeaders(headers);
  }

  int64_t srt_mode;
  common::Value* srt_mode_field = hash->Find(SRT_MODE_FIELD);
  if (srt_mode_field && srt_mode_field->GetAsInteger64(&srt_mode)) {
    url.SetSrtMode(static_cast<SrtMode>(srt_mode));
  }

  common::HashValue* srt_key;
  common::Value* srt_key_field = hash->Find(SRT_KEY_FIELD);
  if (srt_key_field && srt_key_field->GetAsHash(&srt_key)) {
    url.SetSrtKey(SrtKey::Make(srt_key));
  }

  int64_t rtmpsink;
  common::Value* rtmpsink_field = hash->Find(RTMPSINK_TYPE_FILED);
  if (rtmpsink_field && rtmpsink_field->GetAsInteger64(&rtmpsink)) {
    url.SetRtmpSinkType(static_cast<RtmpSinkType>(rtmpsink));
  }

  common::HashValue* kvs;
  common::Value* kvs_field = hash->Find(KVS_FIELD);
  if (kvs_field && kvs_field->GetAsHash(&kvs)) {
    url.SetKVS(KVSProp::Make(kvs));
  }

  common::HashValue* aws;
  common::Value* aws_field = hash->Find(AWS_FIELD);
  if (aws_field && aws_field->GetAsHash(&aws)) {
    url.SetAWS(S3Prop::Make(aws));
  }

  common::HashValue* azure;
  common::Value* azure_field = hash->Find(AZURE_FIELD);
  if (azure_field && azure_field->GetAsHash(&azure)) {
    url.SetAzure(AzureProp::Make(azure));
  }

  common::HashValue* ndi;
  common::Value* ndi_field = hash->Find(NDI_FIELD);
  if (ndi_field && ndi_field->GetAsHash(&ndi)) {
    url.SetNDI(NDIProp::Make(ndi));
  }

  common::HashValue* google;
  common::Value* google_field = hash->Find(GOOGLE_FIELD);
  if (google_field && google_field->GetAsHash(&google)) {
    url.SetGoogle(GoogleProp::Make(google));
  }

  common::HashValue* webrtc;
  common::Value* webrtc_field = hash->Find(WEBRTC_FIELD);
  if (webrtc_field && webrtc_field->GetAsHash(&webrtc)) {
    url.SetWebRTC(WebRTCProp::Make(webrtc));
  }

  common::Value* iface_field = hash->Find(MULTICAST_IFACE_FIELD);
  std::string iface;
  if (iface_field && iface_field->GetAsBasicString(&iface)) {
    url.SetMulticastIface(iface);
  }

  return common::Optional<OutputUri>(url);
}

common::Error OutputUri::DoDeSerialize(json_object* serialized) {
  OutputUri res;
  common::Error err = res.base_class::DoDeSerialize(serialized);
  if (err) {
    return err;
  }

  HlsSinkType hlssink2;
  err = GetEnumField(serialized, HLSSINK_TYPE_FIELD, &hlssink2);
  if (!err) {
    res.SetHlsSinkType(hlssink2);
  }

  std::string http_root;
  err = GetStringField(serialized, HTTP_ROOT_FIELD, &http_root);
  if (!err) {
    res.SetHttpRoot(common::file_system::ascii_directory_string_path(http_root));
  }

  HlsType hls_type;
  err = GetEnumField(serialized, HLS_TYPE_FIELD, &hls_type);
  if (!err) {
    res.SetHlsType(hls_type);
  }

  int chunk_duration;
  err = GetIntField(serialized, CHUNK_DURATION_FIELD, &chunk_duration);
  if (!err) {
    res.SetChunkDuration(chunk_duration);
  }

  std::string play_list;
  err = GetStringField(serialized, PLAYLIST_ROOT_FIELD, &play_list);
  if (!err) {
    res.SetPlaylistRoot(common::uri::GURL(play_list));
  }

  json_object* jwhip = nullptr;
  err = GetObjectField(serialized, WHIP_FIELD, &jwhip);
  if (!err) {
    WhipProp key;
    err = key.DeSerialize(jwhip);
    if (!err) {
      res.SetWhip(key);
    }
  }

  size_t hlen;
  json_object* jhead;
  err = GetArrayField(serialized, HTTP_HEADERS_FIELD, &jhead, &hlen);
  if (!err) {
    HttpHeaders headers;
    err = headers.DeSerialize(jhead);
    if (!err) {
      res.SetHttpHeaders(headers);
    }
  }

  SrtMode srt_mode;
  err = GetEnumField(serialized, SRT_MODE_FIELD, &srt_mode);
  if (!err) {
    res.SetSrtMode(srt_mode);
  }

  json_object* jsrt_key = nullptr;
  err = GetObjectField(serialized, SRT_KEY_FIELD, &jsrt_key);
  if (!err) {
    SrtKey key;
    err = key.DeSerialize(jsrt_key);
    if (!err) {
      res.SetSrtKey(key);
    }
  }

  RtmpSinkType rtmpsink;
  err = GetEnumField(serialized, RTMPSINK_TYPE_FILED, &rtmpsink);
  if (!err) {
    res.SetRtmpSinkType(rtmpsink);
  }

  json_object* jaws = nullptr;
  err = GetObjectField(serialized, AWS_FIELD, &jaws);
  if (!err) {
    S3Prop prop;
    err = prop.DeSerialize(jaws);
    if (!err) {
      res.SetAWS(prop);
    }
  }

  json_object* jkvs = nullptr;
  err = GetObjectField(serialized, KVS_FIELD, &jkvs);
  if (!err) {
    KVSProp prop;
    err = prop.DeSerialize(jkvs);
    if (!err) {
      res.SetKVS(prop);
    }
  }

  json_object* jazure = nullptr;
  err = GetObjectField(serialized, AZURE_FIELD, &jazure);
  if (!err) {
    AzureProp prop;
    err = prop.DeSerialize(jazure);
    if (!err) {
      res.SetAzure(prop);
    }
  }

  json_object* jndi = nullptr;
  err = GetObjectField(serialized, NDI_FIELD, &jndi);
  if (!err) {
    NDIProp prop;
    err = prop.DeSerialize(jndi);
    if (!err) {
      res.SetNDI(prop);
    }
  }

  json_object* jgoogle = nullptr;
  err = GetObjectField(serialized, GOOGLE_FIELD, &jgoogle);
  if (!err) {
    GoogleProp prop;
    err = prop.DeSerialize(jgoogle);
    if (!err) {
      res.SetGoogle(prop);
    }
  }

  json_object* jweb = nullptr;
  err = GetObjectField(serialized, WEBRTC_FIELD, &jweb);
  if (!err) {
    WebRTCProp prop;
    err = prop.DeSerialize(jweb);
    if (!err) {
      res.SetWebRTC(prop);
    }
  }

  std::string iface;
  err = GetStringField(serialized, MULTICAST_IFACE_FIELD, &iface);
  if (!err) {
    res.SetMulticastIface(iface);
  }

  *this = res;
  return common::Error();
}

common::Error OutputUri::SerializeFields(json_object* deserialized) const {
  if (!IsValid()) {
    return common::make_error_inval();
  }

  common::Error err = base_class::SerializeFields(deserialized);
  if (err) {
    return err;
  }

  if (hlssink_type_) {
    ignore_result(SetIntField(deserialized, HLSSINK_TYPE_FIELD, *hlssink_type_));
  }
  auto ps = GetHttpRoot();
  if (ps) {
    const std::string http_root_str = ps->GetPath();
    ignore_result(SetStringField(deserialized, HTTP_ROOT_FIELD, http_root_str));
  }
  if (hls_type_) {
    ignore_result(SetEnumField(deserialized, HLS_TYPE_FIELD, *hls_type_));
  }
  if (chunk_duration_) {
    ignore_result(SetIntField(deserialized, CHUNK_DURATION_FIELD, *chunk_duration_));
  }
  if (playlist_root_) {
    const std::string root = playlist_root_->spec();
    ignore_result(SetStringField(deserialized, PLAYLIST_ROOT_FIELD, root));
  }
  if (whip_) {
    json_object* jwhip = nullptr;
    err = whip_->Serialize(&jwhip);
    if (!err) {
      ignore_result(SetObjectField(deserialized, WHIP_FIELD, jwhip));
    }
  }
  if (srt_mode_) {
    ignore_result(SetEnumField(deserialized, SRT_MODE_FIELD, *srt_mode_));
  }
  if (srt_key_) {
    json_object* jkey = nullptr;
    err = srt_key_->Serialize(&jkey);
    if (!err) {
      ignore_result(SetObjectField(deserialized, SRT_KEY_FIELD, jkey));
    }
  }
  if (rtmpsink_type_) {
    ignore_result(SetEnumField(deserialized, RTMPSINK_TYPE_FILED, *rtmpsink_type_));
  }
  if (kvs_) {
    json_object* jkvs = nullptr;
    err = kvs_->Serialize(&jkvs);
    if (!err) {
      ignore_result(SetObjectField(deserialized, KVS_FIELD, jkvs));
    }
  }
  if (aws_) {
    json_object* jaws = nullptr;
    err = aws_->Serialize(&jaws);
    if (!err) {
      ignore_result(SetObjectField(deserialized, AWS_FIELD, jaws));
    }
  }
  if (azure_) {
    json_object* jazure = nullptr;
    err = azure_->Serialize(&jazure);
    if (!err) {
      ignore_result(SetObjectField(deserialized, AZURE_FIELD, jazure));
    }
  }
  if (ndi_) {
    json_object* jndi = nullptr;
    err = ndi_->Serialize(&jndi);
    if (!err) {
      ignore_result(SetObjectField(deserialized, NDI_FIELD, jndi));
    }
  }
  if (google_) {
    json_object* jgoogle = nullptr;
    err = google_->Serialize(&jgoogle);
    if (!err) {
      ignore_result(SetObjectField(deserialized, GOOGLE_FIELD, jgoogle));
    }
  }
  if (webrtc_) {
    json_object* jweb = nullptr;
    err = webrtc_->Serialize(&jweb);
    if (!err) {
      ignore_result(SetObjectField(deserialized, WEBRTC_FIELD, jweb));
    }
  }
  const auto iface = GetMulticastIface();
  if (iface) {
    const std::string iface_str = *iface;
    ignore_result(SetStringField(deserialized, MULTICAST_IFACE_FIELD, iface_str));
  }
  return common::Error();
}

}  // namespace fastotv

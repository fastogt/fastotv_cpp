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

#include <fastotv/types/input_uri.h>

#define USER_AGENT_FIELD "user_agent"
#define PYFASTOSTREAM_URL_FIELD "stream_link"
#define PROXY_FIELD "proxy"
#define WPE_FIELD "wpe"
#define CEF_FIELD "cef"
#define WHEP_FIELD "whep"
#define HTTP_HEADERS_FIELD "http_headers"
#define PROGRAM_NUMBER_FIELD "program_number"
#define MULTICAST_IFACE_FIELD "multicast_iface"
#define SRT_KEY_FIELD "srt_key"
#define SRT_MODE_FIELD "srt_mode"
#define RTMPSRC_TYPE_FILED "rtmpsrc_type"
#define WEBRTC_FIELD "webrtc"
#define NDI_FIELD "ndi"
#define AWS_FIELD "aws"
#define KEYS_FIELD "keys"

namespace fastotv {

InputUri::InputUri() : InputUri(0, url_t()) {}

InputUri::InputUri(uri_id_t id, const url_t& input)
    : base_class(id, input),
      user_agent_(),
      stream_url_(),
      http_proxy_url_(),
      keys_(),
      wpe_(),
      cef_(),
      whep_(),
      http_headers_(),
      program_number_(),
      iface_(),
      srt_mode_(),
      srt_key_(),
      rtmpsrc_type_(),
      webrtc_(),
      ndi_(),
      aws_() {}

bool InputUri::IsValid() const {
  return base_class::IsValid();
}

InputUri::user_agent_t InputUri::GetUserAgent() const {
  return user_agent_;
}

void InputUri::SetUserAgent(user_agent_t agent) {
  user_agent_ = agent;
}

InputUri::stream_url_t InputUri::GetPyFastoStream() const {
  return stream_url_;
}

void InputUri::SetPyFastoStream(fastotv::InputUri::stream_url_t stream) {
  stream_url_ = stream;
}

InputUri::keys_t InputUri::GetKeys() const {
  return keys_;
}

void InputUri::SetKeys(keys_t keys) {
  keys_ = keys;
}

InputUri::whep_t InputUri::GetWhep() const {
  return whep_;
}

void InputUri::SetWhep(whep_t whep) {
  whep_ = whep;
}

InputUri::http_proxy_url_t InputUri::GetHttpProxyUrl() const {
  return http_proxy_url_;
}

void InputUri::SetHttpProxyUrl(const http_proxy_url_t& url) {
  http_proxy_url_ = url;
}

InputUri::wpe_t InputUri::GetWPE() const {
  return wpe_;
}

void InputUri::SetWPE(const wpe_t& wpe) {
  wpe_ = wpe;
}

InputUri::cef_t InputUri::GetCef() const {
  return cef_;
}

void InputUri::SetCef(const cef_t& cef) {
  cef_ = cef;
}

InputUri::http_headers_t InputUri::GetHttpHeaders() const {
  return http_headers_;
}

void InputUri::SetHttpHeaders(const http_headers_t& head) {
  http_headers_ = head;
}

InputUri::program_number_t InputUri::GetProgramNumber() const {
  return program_number_;
}

void InputUri::SetProgramNumber(fastotv::InputUri::program_number_t pid) {
  program_number_ = pid;
}

InputUri::multicast_iface_t InputUri::GetMulticastIface() const {
  return iface_;
}

void InputUri::SetMulticastIface(multicast_iface_t iface) {
  iface_ = iface;
}

InputUri::srt_key_t InputUri::GetSrtKey() const {
  return srt_key_;
}

void InputUri::SetSrtKey(const srt_key_t& pass) {
  srt_key_ = pass;
}

InputUri::rtmpsrc_type_t InputUri::GetRtmpSrcType() const {
  return rtmpsrc_type_;
}

void InputUri::SetRtmpSrcType(const rtmpsrc_type_t& type) {
  rtmpsrc_type_ = type;
}

InputUri::srt_mode_t InputUri::GetSrtMode() const {
  return srt_mode_;
}

void InputUri::SetSrtMode(srt_mode_t mode) {
  srt_mode_ = mode;
}

InputUri::webrtc_t InputUri::GetWebRTC() const {
  return webrtc_;
}

void InputUri::SetWebRTC(const webrtc_t& web) {
  webrtc_ = web;
}

InputUri::ndi_t InputUri::GetNDI() const {
  return ndi_;
}

void InputUri::SetNDI(const ndi_t& ndi) {
  ndi_ = ndi;
}

InputUri::aws_t InputUri::GetAWS() const {
  return aws_;
}

void InputUri::SetAWS(const aws_t& aws) {
  aws_ = aws;
}

bool InputUri::Equals(const InputUri& url) const {
  return base_class::Equals(url) && url.user_agent_ == user_agent_ && stream_url_ == url.stream_url_ &&
         http_proxy_url_ == url.http_proxy_url_ && keys_ == url.keys_ && wpe_ == url.wpe_ && cef_ == url.cef_ &&
         whep_ == url.whep_ && http_headers_ == url.http_headers_ && program_number_ == url.program_number_ &&
         iface_ == url.iface_ && srt_key_ == url.srt_key_ && srt_mode_ == url.srt_mode_ &&
         rtmpsrc_type_ == url.rtmpsrc_type_ && webrtc_ == url.webrtc_ && ndi_ == url.ndi_ && aws_ == url.aws_;
}

common::Optional<InputUri> InputUri::Make(common::HashValue* hash) {
  if (!hash) {
    return common::Optional<InputUri>();
  }

  common::Optional<InputUrl> base = base_class::Make(hash);
  if (!base) {
    return common::Optional<InputUri>();
  }

  InputUri url(base->GetID(), base->GetUrl());
  int64_t agent;
  common::Value* agent_field = hash->Find(USER_AGENT_FIELD);
  if (agent_field && agent_field->GetAsInteger64(&agent)) {
    url.SetUserAgent(static_cast<UserAgent>(agent));
  }

  common::HashValue* pyfastostream_url;
  common::Value* pyfastostream_url_field = hash->Find(PYFASTOSTREAM_URL_FIELD);
  if (pyfastostream_url_field && pyfastostream_url_field->GetAsHash(&pyfastostream_url)) {
    url.SetPyFastoStream(PyFastoStream::Make(pyfastostream_url));
  }

  std::string http_url_str;
  common::Value* http_proxy_field = hash->Find(PROXY_FIELD);
  if (http_proxy_field && http_proxy_field->GetAsBasicString(&http_url_str)) {
    url.SetHttpProxyUrl(url_t(http_url_str));
  }

  common::Value* keys_field = hash->Find(KEYS_FIELD);
  common::ArrayValue* keys_array = nullptr;
  if (keys_field && keys_field->GetAsList(&keys_array)) {
    keys_t::value_type keys;
    for (size_t i = 0; i < keys_array->GetSize(); ++i) {
      common::Value* key = nullptr;
      common::HashValue* key_hash = nullptr;
      if (keys_array->Get(i, &key) && key->GetAsHash(&key_hash)) {
        const auto murl = DrmKey::Make(key_hash);
        if (murl) {
          keys.Add(*murl);
        }
      }
    }
    url.SetKeys(keys);
  }

  common::HashValue* wpe;
  common::Value* wpe_field = hash->Find(WPE_FIELD);
  if (wpe_field && wpe_field->GetAsHash(&wpe)) {
    auto wp = Wpe::Make(wpe);
    url.SetWPE(wp);
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

  common::HashValue* cef;
  common::Value* cef_field = hash->Find(CEF_FIELD);
  if (cef_field && cef_field->GetAsHash(&cef)) {
    auto wp = Cef::Make(cef);
    url.SetCef(wp);
  }

  common::HashValue* whep;
  common::Value* whep_field = hash->Find(WHEP_FIELD);
  if (whep_field && whep_field->GetAsHash(&whep)) {
    url.SetWhep(WhepProp::Make(whep));
  }

  common::Value* pid_field = hash->Find(PROGRAM_NUMBER_FIELD);
  int64_t pid;
  if (pid_field && pid_field->GetAsInteger64(&pid)) {
    url.SetProgramNumber(pid);
  }

  common::Value* iface_field = hash->Find(MULTICAST_IFACE_FIELD);
  std::string iface;
  if (iface_field && iface_field->GetAsBasicString(&iface)) {
    url.SetMulticastIface(iface);
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

  int64_t rtmpsrc;
  common::Value* rtmpsrc_field = hash->Find(RTMPSRC_TYPE_FILED);
  if (rtmpsrc_field && rtmpsrc_field->GetAsInteger64(&rtmpsrc)) {
    url.SetRtmpSrcType(static_cast<RtmpSrcType>(rtmpsrc));
  }

  common::HashValue* webrtc;
  common::Value* webrtc_field = hash->Find(WEBRTC_FIELD);
  if (webrtc_field && webrtc_field->GetAsHash(&webrtc)) {
    url.SetWebRTC(WebRTCProp::Make(webrtc));
  }

  common::HashValue* ndi;
  common::Value* ndi_field = hash->Find(NDI_FIELD);
  if (ndi_field && ndi_field->GetAsHash(&ndi)) {
    url.SetNDI(NDIProp::Make(ndi));
  }
  common::HashValue* aws;
  common::Value* aws_field = hash->Find(AWS_FIELD);
  if (aws_field && aws_field->GetAsHash(&aws)) {
    url.SetAWS(S3Prop::Make(aws));
  }
  return common::Optional<InputUri>(url);
}

common::Error InputUri::DoDeSerialize(json_object* serialized) {
  InputUri res;
  common::Error err = res.base_class::DoDeSerialize(serialized);
  if (err) {
    return err;
  }

  UserAgent agent;
  err = GetEnumField(serialized, USER_AGENT_FIELD, &agent);
  if (!err) {
    res.SetUserAgent(agent);
  }

  json_object* jstream_url = nullptr;
  err = GetObjectField(serialized, PYFASTOSTREAM_URL_FIELD, &jstream_url);
  if (!err) {
    PyFastoStream link;
    err = link.DeSerialize(jstream_url);
    if (!err) {
      res.SetPyFastoStream(link);
    }
  }

  json_object* jwhep = nullptr;
  err = GetObjectField(serialized, WHEP_FIELD, &jwhep);
  if (!err) {
    WhepProp key;
    err = key.DeSerialize(jwhep);
    if (!err) {
      res.SetWhep(key);
    }
  }

  int pid;
  err = GetIntField(serialized, PROGRAM_NUMBER_FIELD, &pid);
  if (!err) {
    res.SetProgramNumber(pid);
  }

  std::string iface;
  err = GetStringField(serialized, MULTICAST_IFACE_FIELD, &iface);
  if (!err) {
    res.SetMulticastIface(iface);
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

  SrtMode srt_mode;
  err = GetEnumField(serialized, SRT_MODE_FIELD, &srt_mode);
  if (!err) {
    res.SetSrtMode(srt_mode);
  }

  std::string http_proxy;
  err = GetStringField(serialized, PROXY_FIELD, &http_proxy);
  if (!err) {
    res.SetHttpProxyUrl(url_t(http_proxy));
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

  size_t len;
  json_object* jkeys;
  err = GetArrayField(serialized, KEYS_FIELD, &jkeys, &len);
  if (!err) {
    DrmKeys keys;
    err = keys.DeSerialize(jkeys);
    if (!err) {
      res.SetKeys(keys);
    }
  }

  json_object* jwpe = nullptr;
  err = GetObjectField(serialized, WPE_FIELD, &jwpe);
  if (!err) {
    Wpe wp;
    err = wp.DeSerialize(jwpe);
    if (!err) {
      res.SetWPE(wp);
    }
  }

  json_object* jcef = nullptr;
  err = GetObjectField(serialized, CEF_FIELD, &jcef);
  if (!err) {
    Cef cef;
    err = cef.DeSerialize(jcef);
    if (!err) {
      res.SetCef(cef);
    }
  }

  RtmpSrcType rtmpsrc;
  err = GetEnumField(serialized, RTMPSRC_TYPE_FILED, &rtmpsrc);
  if (!err) {
    res.SetRtmpSrcType(rtmpsrc);
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

  json_object* jndi = nullptr;
  err = GetObjectField(serialized, NDI_FIELD, &jndi);
  if (!err) {
    NDIProp prop;
    err = prop.DeSerialize(jndi);
    if (!err) {
      res.SetNDI(prop);
    }
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

  *this = res;
  return common::Error();
}

common::Error InputUri::SerializeFields(json_object* deserialized) const {
  if (!IsValid()) {
    return common::make_error_inval();
  }

  common::Error err = base_class::SerializeFields(deserialized);
  if (err) {
    return err;
  }

  if (user_agent_) {
    ignore_result(SetIntField(deserialized, USER_AGENT_FIELD, *user_agent_));
  }

  if (stream_url_) {
    json_object* jlink = nullptr;
    err = stream_url_->Serialize(&jlink);
    if (!err) {
      ignore_result(SetObjectField(deserialized, PYFASTOSTREAM_URL_FIELD, jlink));
    }
  }

  if (whep_) {
    json_object* jwhep = nullptr;
    err = whep_->Serialize(&jwhep);
    if (!err) {
      ignore_result(SetObjectField(deserialized, WHEP_FIELD, jwhep));
    }
  }

  const auto pid = GetProgramNumber();
  if (pid) {
    ignore_result(SetIntField(deserialized, PROGRAM_NUMBER_FIELD, *pid));
  }

  const auto iface = GetMulticastIface();
  if (iface) {
    const std::string iface_str = *iface;
    ignore_result(SetStringField(deserialized, MULTICAST_IFACE_FIELD, iface_str));
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

  const auto hurl = GetHttpProxyUrl();
  if (hurl) {
    const std::string proxy = hurl->spec();
    ignore_result(SetStringField(deserialized, PROXY_FIELD, proxy));
  }

  const auto keys = GetKeys();
  if (keys) {
    json_object* jkeys = nullptr;
    err = keys->Serialize(&jkeys);
    if (!err) {
      ignore_result(SetObjectField(deserialized, KEYS_FIELD, jkeys));
    }
  }

  const auto wpe = GetWPE();
  if (wpe) {
    json_object* jwpe = nullptr;
    err = wpe->Serialize(&jwpe);
    if (!err) {
      ignore_result(SetObjectField(deserialized, WPE_FIELD, jwpe));
    }
  }

  const auto cef = GetCef();
  if (cef) {
    json_object* jcef = nullptr;
    err = cef->Serialize(&jcef);
    if (!err) {
      ignore_result(SetObjectField(deserialized, CEF_FIELD, jcef));
    }
  }

  if (rtmpsrc_type_) {
    ignore_result(SetEnumField(deserialized, RTMPSRC_TYPE_FILED, *rtmpsrc_type_));
  }
  if (webrtc_) {
    json_object* jweb = nullptr;
    err = webrtc_->Serialize(&jweb);
    if (!err) {
      ignore_result(SetObjectField(deserialized, WEBRTC_FIELD, jweb));
    }
  }
  if (ndi_) {
    json_object* jndi = nullptr;
    err = ndi_->Serialize(&jndi);
    if (!err) {
      ignore_result(SetObjectField(deserialized, NDI_FIELD, jndi));
    }
  }
  if (aws_) {
    json_object* jaws = nullptr;
    err = aws_->Serialize(&jaws);
    if (!err) {
      ignore_result(SetObjectField(deserialized, AWS_FIELD, jaws));
    }
  }
  return common::Error();
}

}  // namespace fastotv

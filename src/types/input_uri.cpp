/*  Copyright (C) 2014-2020 FastoGT. All right reserved.
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

#include <string>

#include <json-c/json_object.h>
#include <json-c/json_tokener.h>

#define ID_FIELD "id"
#define URI_FIELD "uri"
#define USER_AGENT_FIELD "user_agent"
#define STREAMLINK_URL_FIELD "stream_link"
#define PROXY_FIELD "proxy"
#define PROGRAM_NUMBER_FIELD "program_number"
#define MULTICAST_IFACE "multicast_iface"

namespace fastotv {

InputUri::InputUri() : InputUri(0, url_t()) {}

InputUri::InputUri(uri_id_t id, const url_t& input)
    : base_class(),
      id_(id),
      input_(input),
      user_agent_(),
      stream_url_(),
      http_proxy_url_(),
      program_number_(),
      iface_() {}

bool InputUri::IsValid() const {
  return input_.is_valid();
}

InputUri::uri_id_t InputUri::GetID() const {
  return id_;
}

void InputUri::SetID(uri_id_t id) {
  id_ = id;
}

InputUri::url_t InputUri::GetInput() const {
  return input_;
}

void InputUri::SetInput(const url_t& uri) {
  input_ = uri;
}

InputUri::user_agent_t InputUri::GetUserAgent() const {
  return user_agent_;
}

void InputUri::SetUserAgent(user_agent_t agent) {
  user_agent_ = agent;
}

InputUri::stream_url_t InputUri::GetStreamLink() const {
  return stream_url_;
}

void InputUri::SetStreamLink(fastotv::InputUri::stream_url_t stream) {
  stream_url_ = stream;
}

InputUri::http_proxy_url_t InputUri::GetHttpProxyUrl() const {
  return http_proxy_url_;
}

void InputUri::SetHttpProxyUrl(const http_proxy_url_t& url) {
  http_proxy_url_ = url;
}

fastotv::InputUri::program_number_t InputUri::GetProgramNumber() const {
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

bool InputUri::Equals(const InputUri& inf) const {
  return id_ == inf.id_ && input_ == inf.input_;
}

common::Optional<InputUri> InputUri::Make(common::HashValue* hash) {
  if (!hash) {
    return common::Optional<InputUri>();
  }

  std::string url_str;
  common::Value* url_str_field = hash->Find(URI_FIELD);
  if (!url_str_field || !url_str_field->GetAsBasicString(&url_str)) {
    return common::Optional<InputUri>();
  }

  url_t uri(url_str);
  if (!uri.is_valid()) {
    return common::Optional<InputUri>();
  }

  common::Value* input_id_field = hash->Find(ID_FIELD);
  int uid;
  if (!input_id_field || !input_id_field->GetAsInteger(&uid)) {
    return common::Optional<InputUri>();
  }

  InputUri url;
  url.SetInput(uri);
  url.SetID(uid);

  int agent;
  common::Value* agent_field = hash->Find(USER_AGENT_FIELD);
  if (agent_field && agent_field->GetAsInteger(&agent)) {
    url.SetUserAgent(static_cast<UserAgent>(agent));
  }

  common::HashValue* streamlink_url;
  common::Value* streamlink_url_field = hash->Find(STREAMLINK_URL_FIELD);
  if (streamlink_url_field && streamlink_url_field->GetAsHash(&streamlink_url)) {
    url.SetStreamLink(StreamLink::Make(streamlink_url));
  }

  std::string http_url_str;
  common::Value* http_proxy_field = hash->Find(PROXY_FIELD);
  if (http_proxy_field && http_proxy_field->GetAsBasicString(&http_url_str)) {
    url.SetHttpProxyUrl(url_t(http_url_str));
  }

  common::Value* pid_field = hash->Find(PROGRAM_NUMBER_FIELD);
  int pid;
  if (pid_field && pid_field->GetAsInteger(&pid)) {
    url.SetProgramNumber(pid);
  }

  common::Value* iface_field = hash->Find(MULTICAST_IFACE);
  std::string iface;
  if (iface_field && iface_field->GetAsBasicString(&iface)) {
    url.SetMulticastIface(iface);
  }
  return url;
}

common::Error InputUri::DoDeSerialize(json_object* serialized) {
  json_object* juri = nullptr;
  json_bool juri_exists = json_object_object_get_ex(serialized, URI_FIELD, &juri);
  if (!juri_exists) {
    return common::make_error_inval();
  }

  json_object* jid = nullptr;
  json_bool jid_exists = json_object_object_get_ex(serialized, ID_FIELD, &jid);
  if (!jid_exists || !json_object_is_type(jid, json_type_int)) {
    return common::make_error_inval();
  }

  InputUri res;
  url_t url(json_object_get_string(juri));
  res.SetInput(url);
  res.SetID(json_object_get_int(jid));

  json_object* juser_agent = nullptr;
  json_bool juser_agent_exists = json_object_object_get_ex(serialized, USER_AGENT_FIELD, &juser_agent);
  if (juser_agent_exists) {
    user_agent_t agent = static_cast<UserAgent>(json_object_get_int(juser_agent));
    res.SetUserAgent(agent);
  }

  json_object* jstream_url = nullptr;
  json_bool jstream_url_exists = json_object_object_get_ex(serialized, STREAMLINK_URL_FIELD, &jstream_url);
  if (jstream_url_exists) {
    StreamLink link;
    common::Error err = link.DeSerialize(jstream_url);
    if (!err) {
      res.SetStreamLink(link);
    }
  }

  json_object* jpid = nullptr;
  json_bool jpid_exists = json_object_object_get_ex(serialized, PROGRAM_NUMBER_FIELD, &jpid);
  if (jpid_exists) {
    res.SetProgramNumber(json_object_get_int(jpid));
  }

  json_object* jiface = nullptr;
  json_bool jiface_exists = json_object_object_get_ex(serialized, MULTICAST_IFACE, &jiface);
  if (jiface_exists) {
    std::string iface = json_object_get_string(jiface);
    res.SetMulticastIface(iface);
  }

  json_object* jhttp_proxy = nullptr;
  json_bool jhttp_proxy_exists = json_object_object_get_ex(serialized, PROXY_FIELD, &jhttp_proxy);
  if (jhttp_proxy_exists) {
    res.SetHttpProxyUrl(url_t(json_object_get_string(jhttp_proxy)));
  }

  *this = res;
  return common::Error();
}

common::Error InputUri::SerializeFields(json_object* out) const {
  if (!IsValid()) {
    return common::make_error_inval();
  }

  json_object_object_add(out, ID_FIELD, json_object_new_int(GetID()));
  const std::string url_str = input_.spec();
  json_object_object_add(out, URI_FIELD, json_object_new_string(url_str.c_str()));
  if (user_agent_) {
    json_object_object_add(out, USER_AGENT_FIELD, json_object_new_int(*user_agent_));
  }
  if (stream_url_) {
    json_object* jlink = nullptr;
    common::Error err = stream_url_->Serialize(&jlink);
    if (!err) {
      json_object_object_add(out, STREAMLINK_URL_FIELD, jlink);
    }
  }
  const auto pid = GetProgramNumber();
  if (pid) {
    json_object_object_add(out, PROGRAM_NUMBER_FIELD, json_object_new_int(*pid));
  }
  const auto iface = GetMulticastIface();
  if (iface) {
    const std::string iface_str = *iface;
    json_object_object_add(out, MULTICAST_IFACE, json_object_new_string(iface_str.c_str()));
  }
  const auto hurl = GetHttpProxyUrl();
  if (hurl) {
    const std::string proxy = hurl->spec();
    json_object_object_add(out, PROXY_FIELD, json_object_new_string(proxy.c_str()));
  }

  return common::Error();
}

}  // namespace fastotv

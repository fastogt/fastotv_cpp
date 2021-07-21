/*  Copyright (C) 2014-2021 FastoGT. All right reserved.
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

#include <fastotv/types/pyfastostream.h>

#define HTTP_FIELD "http_proxy"
#define HTTPS_FIELD "https_proxy"
#define PREFER_FIELD "prefer"

namespace fastotv {

PyFastoStream::PyFastoStream() : http_proxy_(), https_proxy_(), prefer_(QP_BOTH) {}

PyFastoStream::PyFastoStream(const http_proxy_t& http, const http_proxy_t& https, fastotv::QualityPrefer prefer)
    : http_proxy_(http), https_proxy_(https), prefer_(prefer) {}

bool PyFastoStream::IsValid() const {
  return true;
}

PyFastoStream::http_proxy_t PyFastoStream::GetHttp() const {
  return http_proxy_;
}

void PyFastoStream::SetHttp(const http_proxy_t& url) {
  http_proxy_ = url;
}

PyFastoStream::https_proxy_t PyFastoStream::GetHttps() const {
  return https_proxy_;
}

void PyFastoStream::SetHttps(const https_proxy_t& url) {
  https_proxy_ = url;
}

QualityPrefer PyFastoStream::GetPrefer() const {
  return prefer_;
}

void PyFastoStream::SetPrefer(QualityPrefer prefer) {
  prefer_ = prefer;
}

bool PyFastoStream::Equals(const PyFastoStream& url) const {
  return http_proxy_ == url.http_proxy_ && https_proxy_ == url.https_proxy_;
}

common::Optional<PyFastoStream> PyFastoStream::Make(common::HashValue* json) {
  if (!json) {
    return common::Optional<PyFastoStream>();
  }

  PyFastoStream res;
  common::Value* http_field = json->Find(HTTP_FIELD);
  std::string url_str;
  if (http_field && http_field->GetAsBasicString(&url_str)) {
    res.http_proxy_ = http_proxy_t(url_str);
  }

  common::Value* https_field = json->Find(HTTPS_FIELD);
  if (https_field && https_field->GetAsBasicString(&url_str)) {
    res.https_proxy_ = https_proxy_t(url_str);
  }

  int64_t prefer;
  common::Value* prefer_field = json->Find(PREFER_FIELD);
  if (prefer_field && prefer_field->GetAsInteger64(&prefer)) {
    res.prefer_ = static_cast<QualityPrefer>(prefer);
  }
  return res;
}

common::Error PyFastoStream::DoDeSerialize(json_object* serialized) {
  PyFastoStream res;
  QualityPrefer prefer = QualityPrefer::QP_BOTH;
  common::Error err = GetEnumField(serialized, PREFER_FIELD, &prefer);
  if (err) {
    return err;
  }
  res.SetPrefer(prefer);

  std::string http;
  err = GetStringField(serialized, HTTP_FIELD, &http);
  if (!err) {
    res.SetHttp(http_proxy_t(http));
  }

  std::string https;
  err = GetStringField(serialized, HTTPS_FIELD, &https);
  if (!err) {
    res.SetHttps(https_proxy_t(https));
  }

  *this = res;
  return common::Error();
}

common::Error PyFastoStream::SerializeFields(json_object* out) const {
  if (http_proxy_) {
    const std::string url_path = http_proxy_->spec();
    ignore_result(SetStringField(out, HTTP_FIELD, url_path));
  }
  if (https_proxy_) {
    const std::string url_path = https_proxy_->spec();
    ignore_result(SetStringField(out, HTTPS_FIELD, url_path));
  }
  ignore_result(SetEnumField(out, PREFER_FIELD, prefer_));
  return common::Error();
}

}  // namespace fastotv

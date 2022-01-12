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

#include <fastotv/types/stream_overlay.h>

#define URL_FIELD "url"
#define WPE_FIELD "wpe"
#define BACKGROUND_FIELD "background"
#define METHOD_FIELD "method"

namespace fastotv {

StreamOverlay::StreamOverlay(const url_t& url, bool wpe, const background_color_t& color, const alpha_method_t& method)
    : url_(url), wpe_(wpe), background_color_(color), method_(method) {}

bool StreamOverlay::Equals(const StreamOverlay& back) const {
  return back.url_ == url_ && back.wpe_ == wpe_;
}

StreamOverlay::url_t StreamOverlay::GetUrl() const {
  return url_;
}

void StreamOverlay::SetUrl(const url_t& url) {
  url_ = url;
}

const StreamOverlay::background_color_t& StreamOverlay::GetBackgroundColor() const {
  return background_color_;
}

void StreamOverlay::SetBackgroundColor(background_color_t color) {
  background_color_ = color;
}

const StreamOverlay::alpha_method_t& StreamOverlay::GetAlphaMethod() const {
  return method_;
}

void StreamOverlay::SetAlphaMethod(alpha_method_t method) {
  method_ = method;
}

void StreamOverlay::SetWPE(bool wpe) {
  wpe_ = wpe;
}

bool StreamOverlay::GetWPE() const {
  return wpe_;
}

common::Optional<StreamOverlay> StreamOverlay::Make(common::HashValue* hash) {
  if (!hash) {
    return common::Optional<StreamOverlay>();
  }

  common::Value* url_field = hash->Find(URL_FIELD);
  std::string url;
  if (!url_field || !url_field->GetAsBasicString(&url)) {
    return common::Optional<StreamOverlay>();
  }

  common::Value* wpe_field = hash->Find(WPE_FIELD);
  bool wpe;
  if (!wpe_field || !wpe_field->GetAsBoolean(&wpe)) {
    return common::Optional<StreamOverlay>();
  }

  StreamOverlay stream = StreamOverlay(url_t(url), wpe);
  int64_t color;
  common::Value* back_field = hash->Find(BACKGROUND_FIELD);
  if (back_field && back_field->GetAsInteger64(&color)) {
    stream.SetBackgroundColor(static_cast<BackgroundColor>(color));
  }

  common::HashValue* method;
  common::Value* method_field = hash->Find(METHOD_FIELD);
  if (method_field && method_field->GetAsHash(&method)) {
    stream.SetAlphaMethod(AlphaMethod::Make(method));
  }

  return stream;
}

common::Error StreamOverlay::DoDeSerialize(json_object* serialized) {
  std::string url;
  common::Error err = GetStringField(serialized, URL_FIELD, &url);
  if (err) {
    return err;
  }

  bool wpe;
  err = GetEnumField(serialized, WPE_FIELD, &wpe);
  if (err) {
    return err;
  }

  StreamOverlay stream = StreamOverlay(url_t(url), wpe);
  BackgroundColor back;
  err = GetEnumField(serialized, BACKGROUND_FIELD, &back);
  if (!err) {
    stream.SetBackgroundColor(back);
  }

  json_object* jmethod = nullptr;
  err = GetObjectField(serialized, METHOD_FIELD, &jmethod);
  if (!err) {
    AlphaMethod prop = AlphaMethod::MakeBlue();
    err = prop.DeSerialize(jmethod);
    if (!err) {
      stream.SetAlphaMethod(prop);
    }
  }

  *this = stream;
  return common::Error();
}

common::Error StreamOverlay::SerializeFields(json_object* out) const {
  ignore_result(SetStringField(out, URL_FIELD, url_.spec()));
  ignore_result(SetBoolField(out, WPE_FIELD, wpe_));
  if (background_color_) {
    ignore_result(SetEnumField(out, BACKGROUND_FIELD, *background_color_));
  }
  if (method_) {
    json_object* jmethod = nullptr;
    common::Error err = method_->Serialize(&jmethod);
    if (!err) {
      ignore_result(SetObjectField(out, METHOD_FIELD, jmethod));
    }
  }
  return common::Error();
}

}  // namespace fastotv

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
#define BACKGROUND_FIELD "background"
#define ALPHA_FIELD "alpha"

namespace fastotv {

StreamOverlay::StreamOverlay(const url_t& url, const background_color_t& color, alpha_t alpha)
    : url_(url), background_color_(color), alpha_(alpha) {}

bool StreamOverlay::Equals(const StreamOverlay& back) const {
  return back.url_ == url_;
}

StreamOverlay::url_t StreamOverlay::GetUrl() const {
  return url_;
}

void StreamOverlay::SetUrl(const url_t& url) {
  url_ = url;
}

StreamOverlay::alpha_t StreamOverlay::GetAlpha() const {
  return alpha_;
}

void StreamOverlay::SetAlpha(alpha_t alpha) {
  alpha_ = alpha;
}

const StreamOverlay::background_color_t& StreamOverlay::GetBackgroundColor() const {
  return background_color_;
}

void StreamOverlay::SetBackgroundColor(background_color_t color) {
  background_color_ = color;
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

  StreamOverlay stream = StreamOverlay(url_t(url));
  int64_t color;
  common::Value* back_field = hash->Find(BACKGROUND_FIELD);
  if (back_field && back_field->GetAsInteger64(&color)) {
    stream.SetBackgroundColor(static_cast<BackgroundColor>(color));
  }

  double alpha;
  common::Value* alpha_field = hash->Find(ALPHA_FIELD);
  if (alpha_field && alpha_field->GetAsDouble(&alpha)) {
    stream.SetAlpha(alpha);
  }

  return stream;
}

common::Error StreamOverlay::DoDeSerialize(json_object* serialized) {
  std::string url;
  common::Error err = GetStringField(serialized, URL_FIELD, &url);
  if (err) {
    return err;
  }

  StreamOverlay stream = StreamOverlay(url_t(url));
  BackgroundColor back;
  err = GetEnumField(serialized, BACKGROUND_FIELD, &back);
  if (!err) {
    stream.SetBackgroundColor(back);
  }
  double alpha;
  err = GetDoubleField(serialized, ALPHA_FIELD, &alpha);
  if (!err) {
    stream.SetAlpha(alpha);
  }

  *this = stream;
  return common::Error();
}

common::Error StreamOverlay::SerializeFields(json_object* out) const {
  ignore_result(SetStringField(out, URL_FIELD, url_.spec()));
  if (background_color_) {
    ignore_result(SetEnumField(out, BACKGROUND_FIELD, *background_color_));
  }
  if (alpha_) {
    ignore_result(SetEnumField(out, ALPHA_FIELD, *alpha_));
  }
  return common::Error();
}

}  // namespace fastotv

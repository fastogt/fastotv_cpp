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

#pragma once

#include <string>

#include <common/uri/gurl.h>
#include <common/value.h>

#include <common/serializer/json_serializer.h>

namespace fastotv {

class StreamOverlay : public common::serializer::JsonSerializer<StreamOverlay> {
 public:
  typedef common::serializer::JsonSerializer<StreamOverlay> base_class;
  enum BackgroundColor { CHECKER = 0, BLACK, WHITE, TRANSPARENT };
  typedef common::uri::GURL url_t;
  typedef common::Optional<BackgroundColor> background_color_t;

  StreamOverlay(const url_t& url, const background_color_t& color = background_color_t());

  bool Equals(const StreamOverlay& back) const;

  url_t GetUrl() const;
  void SetUrl(const url_t& url);

  const background_color_t& GetBackgroundColor() const;
  void SetBackgroundColor(background_color_t color);

  static common::Optional<StreamOverlay> Make(common::HashValue* hash);

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* out) const override;

 private:
  url_t url_;
  background_color_t background_color_;
};

inline bool operator==(const StreamOverlay& left, const StreamOverlay& right) {
  return left.Equals(right);
}

inline bool operator!=(const StreamOverlay& x, const StreamOverlay& y) {
  return !(x == y);
}

}  // namespace fastotv

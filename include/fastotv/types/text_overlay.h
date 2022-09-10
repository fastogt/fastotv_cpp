/*  Copyright (C) 2014-2022 FastoGT. All right reserved.
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

#include <fastotv/types/font.h>

#include <string>

namespace fastotv {

class TextOverlay : public common::serializer::JsonSerializer<TextOverlay> {
 public:
  typedef common::serializer::JsonSerializer<TextOverlay> base_class;
  typedef std::string text_t;
  typedef double absolute_t;
  typedef common::Optional<Font> font_t;

  TextOverlay(const text_t& text, absolute_t x, absolute_t y, const font_t& font = font_t());

  bool Equals(const TextOverlay& back) const;

  text_t GetText() const;
  void SetText(const text_t& text);

  font_t GetFont() const;
  void SetFont(const font_t& font);

  absolute_t GetXAbsolute() const;
  void SetXAbsolute(absolute_t absolute);

  absolute_t GetYAbsolute() const;
  void SetYAbsolute(absolute_t absolute_t);

  static common::Optional<TextOverlay> Make(common::HashValue* hash);

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* out) const override;

 private:
  text_t text_;
  absolute_t x_absolute_;
  absolute_t y_absolute_;

  font_t font_;
};

inline bool operator==(const TextOverlay& left, const TextOverlay& right) {
  return left.Equals(right);
}

inline bool operator!=(const TextOverlay& x, const TextOverlay& y) {
  return !(x == y);
}

}  // namespace fastotv

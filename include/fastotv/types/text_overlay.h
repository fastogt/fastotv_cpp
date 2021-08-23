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

#include <common/serializer/json_serializer.h>
#include <common/value.h>

namespace fastotv {

class TextOverlay : public common::serializer::JsonSerializer<TextOverlay> {
 public:
  typedef common::serializer::JsonSerializer<TextOverlay> base_class;
  typedef std::string text_t;
  typedef common::Optional<std::string> font_t;

  TextOverlay(const text_t& text, const font_t& font = font_t());

  bool Equals(const TextOverlay& back) const;

  static common::Optional<TextOverlay> Make(common::HashValue* hash);

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* out) const override;

 private:
  text_t text_;
  font_t font_;
};

}  // namespace fastotv

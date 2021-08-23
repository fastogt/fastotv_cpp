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

#include <fastotv/types/text_overlay.h>

#include <common/sprintf.h>

#define TEXT_FIELD "text"
#define FONT_FIELD "font"

namespace fastotv {

TextOverlay::TextOverlay(const text_t& text, const font_t& font) : text_(text), font_(font) {}

bool TextOverlay::Equals(const TextOverlay& back) const {
  return back.text_ == text_ && back.font_ == font_;
}

TextOverlay::text_t TextOverlay::GetText() {
  return text_;
}

void TextOverlay::SetText(const TextOverlay::text_t& text) {
  text_ = text;
}

TextOverlay::font_t TextOverlay::GetFont() {
  return font_;
}

void TextOverlay::SetFont(const TextOverlay::font_t& font) {
  font_ = font;
}

common::Optional<TextOverlay> TextOverlay::Make(common::HashValue* hash) {
  if (!hash) {
    return common::Optional<TextOverlay>();
  }

  common::Value* text_field = hash->Find(TEXT_FIELD);
  text_t text;
  if (!text_field || !text_field->GetAsBasicString(&text)) {
    return common::Optional<TextOverlay>();
  }

  std::string font;
  common::Value* font_field = hash->Find(FONT_FIELD);
  if (font_field && font_field->GetAsBasicString(&font)) {
    return TextOverlay(text, font);
  }

  return TextOverlay(text);
}

common::Error TextOverlay::DoDeSerialize(json_object* serialized) {
  text_t text;
  common::Error err = GetStringField(serialized, TEXT_FIELD, &text);
  if (err) {
    return err;
  }

  std::string font;
  err = GetStringField(serialized, FONT_FIELD, &font);
  if (err) {
    *this = TextOverlay(text);
    return common::Error();
  }

  *this = TextOverlay(text, font);
  return common::Error();
}

common::Error TextOverlay::SerializeFields(json_object* out) const {
  ignore_result(SetStringField(out, TEXT_FIELD, text_));
  if (font_) {
    ignore_result(SetStringField(out, FONT_FIELD, *font_));
  }
  return common::Error();
}

}  // namespace fastotv

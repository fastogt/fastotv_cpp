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
#define X_ABSOLUTE_FIELD "x_absolute"
#define Y_ABSOLUTE_FIELD "y_absolute"

#define FONT_FIELD "font"

#define FONT_FAMILY "family"
#define FONT_SIZE "size"

namespace fastotv {

Font::Font() : family_(), size_(0) {}

Font::Font(const family_t& family, int size) : family_(family), size_(size) {}

bool Font::IsValid() const {
  return !family_.empty() && size_ != 0;
}

bool Font::Equals(const Font& back) const {
  return back.family_ == family_ && back.size_ == size_;
}

common::Optional<Font> Font::Make(common::HashValue* json) {
  if (!json) {
    return common::Optional<Font>();
  }

  Font res;
  common::Value* pass_field = json->Find(FONT_FAMILY);
  std::string pass;
  if (!pass_field || !pass_field->GetAsBasicString(&pass)) {
    return common::Optional<Font>();
  }
  res.family_ = pass;

  int64_t kl;
  common::Value* kl_field = json->Find(FONT_SIZE);
  if (!kl_field || !kl_field->GetAsInteger64(&kl)) {
    return common::Optional<Font>();
  }
  res.size_ = kl;
  return res;
}

common::Error Font::DoDeSerialize(json_object* serialized) {
  family_t text;
  common::Error err = GetStringField(serialized, FONT_FAMILY, &text);
  if (err) {
    return err;
  }

  int64_t size;
  err = GetInt64Field(serialized, FONT_SIZE, &size);
  if (err) {
    return err;
  }

  *this = Font(text, size);
  return common::Error();
}

common::Error Font::SerializeFields(json_object* out) const {
  ignore_result(SetStringField(out, FONT_FAMILY, family_));
  ignore_result(SetInt64Field(out, X_ABSOLUTE_FIELD, size_));
  return common::Error();
}

TextOverlay::TextOverlay(const text_t& text,
                         fastotv::TextOverlay::absolute_t x,
                         fastotv::TextOverlay::absolute_t y,
                         const font_t& font)
    : text_(text), x_absolute_(x), y_absolute_(y), font_(font) {}

bool TextOverlay::Equals(const TextOverlay& back) const {
  return back.text_ == text_ && back.font_ == font_;
}

TextOverlay::text_t TextOverlay::GetText() const {
  return text_;
}

void TextOverlay::SetText(const TextOverlay::text_t& text) {
  text_ = text;
}

TextOverlay::font_t TextOverlay::GetFont() const {
  return font_;
}

void TextOverlay::SetFont(const TextOverlay::font_t& font) {
  font_ = font;
}

TextOverlay::absolute_t TextOverlay::GetXAbsolute() const {
  return x_absolute_;
}

void TextOverlay::SetXAbsolute(absolute_t absolute) {
  x_absolute_ = absolute;
}

TextOverlay::absolute_t TextOverlay::GetYAbsolute() const {
  return y_absolute_;
}

void TextOverlay::SetYAbsolute(absolute_t absolute) {
  y_absolute_ = absolute;
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

  common::Value* xabs_field = hash->Find(X_ABSOLUTE_FIELD);
  absolute_t xabs;
  if (!xabs_field || !xabs_field->GetAsDouble(&xabs)) {
    return common::Optional<TextOverlay>();
  }

  common::Value* yabs_field = hash->Find(Y_ABSOLUTE_FIELD);
  absolute_t yabs;
  if (!yabs_field || !yabs_field->GetAsDouble(&yabs)) {
    return common::Optional<TextOverlay>();
  }

  std::string font;
  common::Value* font_field = hash->Find(FONT_FIELD);
  common::HashValue* font_hash = nullptr;
  if (font_field && font_field->GetAsHash(&font_hash)) {
    return TextOverlay(text, xabs, yabs, Font::Make(font_hash));
  }

  return TextOverlay(text, xabs, yabs);
}

common::Error TextOverlay::DoDeSerialize(json_object* serialized) {
  text_t text;
  common::Error err = GetStringField(serialized, TEXT_FIELD, &text);
  if (err) {
    return err;
  }

  absolute_t xabs;
  err = GetDoubleField(serialized, X_ABSOLUTE_FIELD, &xabs);
  if (err) {
    return err;
  }

  absolute_t yabs;
  err = GetDoubleField(serialized, Y_ABSOLUTE_FIELD, &yabs);
  if (err) {
    return err;
  }

  json_object* jfont;
  err = GetObjectField(serialized, FONT_FIELD, &jfont);
  if (err) {
    *this = TextOverlay(text, xabs, yabs);
    return common::Error();
  }

  Font font;
  err = font.DeSerialize(jfont);
  if (err) {
    return err;
  }

  *this = TextOverlay(text, xabs, yabs, font);
  return common::Error();
}

common::Error TextOverlay::SerializeFields(json_object* out) const {
  ignore_result(SetStringField(out, TEXT_FIELD, text_));
  ignore_result(SetDoubleField(out, X_ABSOLUTE_FIELD, x_absolute_));
  ignore_result(SetDoubleField(out, Y_ABSOLUTE_FIELD, y_absolute_));
  if (font_) {
    json_object* jkey = nullptr;
    common::Error err = font_->Serialize(&jkey);
    if (!err) {
      ignore_result(SetObjectField(out, FONT_FAMILY, jkey));
    }
  }
  return common::Error();
}

}  // namespace fastotv

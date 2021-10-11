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

#include <fastotv/types/font.h>

#define FONT_FAMILY "family"
#define FONT_SIZE "size"

namespace fastotv {

Font::Font() : family_(), size_(0) {}

Font::Font(const family_t& family, int size) : family_(family), size_(size) {}

Font::family_t Font::GetFamily() const {
  return family_;
}

size_t Font::GetSize() const {
  return size_;
}

void Font::SetFamily(const family_t& family) {
  family_ = family;
}

void Font::SetSize(size_t size) {
  size_ = size;
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
  ignore_result(SetInt64Field(out, FONT_SIZE, size_));
  return common::Error();
}

}  // namespace fastotv

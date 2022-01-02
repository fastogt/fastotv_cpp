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

#include <string>

#include <common/serializer/json_serializer.h>
#include <common/value.h>

namespace fastotv {

class Font : public common::serializer::JsonSerializer<Font> {
 public:
  typedef common::serializer::JsonSerializer<Font> base_class;
  typedef std::string family_t;

  Font();
  Font(const family_t& family, int size);

  bool Equals(const Font& back) const;

  family_t GetFamily() const;
  void SetFamily(const family_t& family);

  size_t GetSize() const;
  void SetSize(size_t size);

  static common::Optional<Font> Make(common::HashValue* json);

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* out) const override;

 private:
  family_t family_;
  size_t size_;
};

inline bool operator==(const Font& left, const Font& right) {
  return left.Equals(right);
}

inline bool operator!=(const Font& x, const Font& y) {
  return !(x == y);
}

}  // namespace fastotv

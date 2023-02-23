/*  Copyright (C) 2014-2023 FastoGT. All right reserved.
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

#include <common/serializer/json_serializer.h>
#include <common/value.h>

#include <string>

namespace fastotv {

class Wpe : public common::serializer::JsonSerializer<Wpe> {
 public:
  typedef JsonSerializer<Wpe> base_class;
  typedef bool gl_t;

  Wpe();
  explicit Wpe(gl_t gl);

  void SetGL(gl_t gl);
  gl_t GetGL() const;

  bool Equals(const Wpe& inf) const;

  static common::Optional<Wpe> Make(common::HashValue* hash);

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* out) const override;

 private:
  gl_t gl_;
};

inline bool operator==(const Wpe& left, const Wpe& right) {
  return left.Equals(right);
}

inline bool operator!=(const Wpe& x, const Wpe& y) {
  return !(x == y);
}

}  // namespace fastotv

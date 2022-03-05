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

class Cef : public common::serializer::JsonSerializer<Cef> {
 public:
  typedef JsonSerializer<Cef> base_class;
  typedef bool gpu_t;

  Cef();
  explicit Cef(gpu_t gpu);

  void SetGL(gpu_t gpu);
  gpu_t GetGPU() const;

  bool Equals(const Cef& inf) const;
  static common::Optional<Cef> Make(common::HashValue* hash);

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* out) const override;

 private:
  gpu_t gpu_;
};

inline bool operator==(const Cef& left, const Cef& right) {
  return left.Equals(right);
}

inline bool operator!=(const Cef& x, const Cef& y) {
  return !(x == y);
}

}  // namespace fastotv

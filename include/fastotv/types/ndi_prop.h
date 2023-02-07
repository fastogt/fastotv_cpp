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

#include <common/serializer/json_serializer.h>
#include <common/value.h>

#include <string>

namespace fastotv {

class NDIProp : public common::serializer::JsonSerializer<NDIProp> {
 public:
  typedef JsonSerializer<NDIProp> base_class;
  typedef std::string ndi_name_t;

  NDIProp();
  explicit NDIProp(const ndi_name_t& name);

  bool IsValid() const;

  ndi_name_t GetName() const;
  void SetName(const ndi_name_t& name);

  bool Equals(const NDIProp& key) const;

  static common::Optional<NDIProp> Make(common::HashValue* json);

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* out) const override;

 private:
  ndi_name_t ndi_name_;
};

inline bool operator==(const NDIProp& left, const NDIProp& right) {
  return left.Equals(right);
}

inline bool operator!=(const NDIProp& x, const NDIProp& y) {
  return !(x == y);
}

}  // namespace fastotv

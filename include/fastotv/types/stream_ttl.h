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

class StreamTTL : public common::serializer::JsonSerializer<StreamTTL> {
 public:
  typedef JsonSerializer<StreamTTL> base_class;
  typedef common::utctime_t ttl_t;

  StreamTTL();
  explicit StreamTTL(const ttl_t& ttl, bool phoenix);

  bool IsValid() const;

  ttl_t GetTTL() const;
  void SetTTL(const ttl_t& ttl);

  void SetPhoenix(bool phoenix);
  bool GetPhoenix() const;

  bool Equals(const StreamTTL& key) const;

  static common::Optional<StreamTTL> Make(common::HashValue* json);

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* out) const override;

 private:
  ttl_t ttl_;
  bool phoenix_;
};

inline bool operator==(const StreamTTL& left, const StreamTTL& right) {
  return left.Equals(right);
}

inline bool operator!=(const StreamTTL& x, const StreamTTL& y) {
  return !(x == y);
}

}  // namespace fastotv

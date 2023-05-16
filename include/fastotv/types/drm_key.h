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

class DrmKey : public common::serializer::JsonSerializer<DrmKey> {
 public:
  typedef JsonSerializer<DrmKey> base_class;
  typedef std::string hexed_kid_t;
  typedef std::string hexed_key_t;

  DrmKey();
  explicit DrmKey(const hexed_kid_t& kid, const hexed_kid_t& key);

  bool IsValid() const;

  common::Optional<common::char_buffer_t> GetKey() const;
  hexed_kid_t GetHexedKid() const;
  void SetHexedKid(const hexed_kid_t& kid);

  hexed_kid_t GetHexedKey() const;
  void SetHexedKey(const hexed_key_t& key);

  bool Equals(const DrmKey& key) const;

  static common::Optional<DrmKey> Make(common::HashValue* json);

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* out) const override;

 private:
  hexed_kid_t kid_;
  hexed_key_t key_;
};

inline bool operator==(const DrmKey& left, const DrmKey& right) {
  return left.Equals(right);
}

inline bool operator!=(const DrmKey& x, const DrmKey& y) {
  return !(x == y);
}

typedef common::serializer::JsonSerializerArray<DrmKey> DrmKeys;

}  // namespace fastotv

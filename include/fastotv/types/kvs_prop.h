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

class KVSProp : public common::serializer::JsonSerializer<KVSProp> {
 public:
  typedef JsonSerializer<KVSProp> base_class;
  typedef std::string stream_name_t;

  KVSProp();
  explicit KVSProp(const stream_name_t& name);

  bool IsValid() const;

  stream_name_t GetStreamName() const;
  void SetStreamName(const stream_name_t& name);

  bool Equals(const KVSProp& key) const;

  static common::Optional<KVSProp> Make(common::HashValue* json);

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* out) const override;

 private:
  stream_name_t stream_name_;
};

inline bool operator==(const KVSProp& left, const KVSProp& right) {
  return left.Equals(right);
}

inline bool operator!=(const KVSProp& x, const KVSProp& y) {
  return !(x == y);
}

}  // namespace fastotv

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

class KVSProp : public common::serializer::JsonSerializer<KVSProp> {
 public:
  typedef JsonSerializer<KVSProp> base_class;
  typedef std::string stream_name_t;
  typedef uint32_t storage_size_t;
  typedef std::string access_key_t;
  typedef std::string secret_key_t;
  typedef std::string aws_region_t;

  KVSProp();
  explicit KVSProp(const stream_name_t& name,
                   const access_key_t& access_key,
                   const secret_key_t& secret_key,
                   const aws_region_t& aws_region,
                   storage_size_t storage = 512);

  bool IsValid() const;

  stream_name_t GetStreamName() const;
  void SetStreamName(const stream_name_t& name);

  access_key_t GetAccessKey() const;
  void SetAccessKey(const access_key_t& key);

  secret_key_t GetSecretKey() const;
  void SetSecretKey(const secret_key_t& key);

  aws_region_t GetAwsRegion() const;
  void SetAwsRegion(const aws_region_t& region);

  storage_size_t GetStorageSize() const;
  void SetStorageSize(storage_size_t size);

  bool Equals(const KVSProp& key) const;

  static common::Optional<KVSProp> Make(common::HashValue* json);

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* out) const override;

 private:
  stream_name_t stream_name_;
  access_key_t access_key_;
  secret_key_t secret_key_;
  aws_region_t aws_region_;
  storage_size_t storage_size_;
};

inline bool operator==(const KVSProp& left, const KVSProp& right) {
  return left.Equals(right);
}

inline bool operator!=(const KVSProp& x, const KVSProp& y) {
  return !(x == y);
}

}  // namespace fastotv

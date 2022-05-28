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

class AzureProp : public common::serializer::JsonSerializer<AzureProp> {
 public:
  typedef JsonSerializer<AzureProp> base_class;
  typedef std::string account_name_t;
  typedef std::string account_key_t;
  typedef std::string location_t;

  AzureProp();
  explicit AzureProp(const account_name_t& name, const account_key_t& account_key, const location_t& location);

  bool IsValid() const;

  account_name_t GetAccountName() const;
  void SetAccountName(const account_name_t& name);

  account_key_t GetAccountKey() const;
  void SetAccountKey(const account_key_t& key);

  location_t GetLocation() const;
  void SetLocation(const location_t& location);

  bool Equals(const AzureProp& key) const;

  static common::Optional<AzureProp> Make(common::HashValue* json);

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* out) const override;

 private:
  account_name_t account_name_;
  account_key_t account_key_;
  location_t location_;
};

inline bool operator==(const AzureProp& left, const AzureProp& right) {
  return left.Equals(right);
}

inline bool operator!=(const AzureProp& x, const AzureProp& y) {
  return !(x == y);
}

}  // namespace fastotv

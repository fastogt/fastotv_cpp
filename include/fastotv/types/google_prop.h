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

class GoogleProp : public common::serializer::JsonSerializer<GoogleProp> {
 public:
  typedef JsonSerializer<GoogleProp> base_class;
  typedef std::string account_creds_t;

  GoogleProp();
  explicit GoogleProp(const account_creds_t& creds);

  bool IsValid() const;

  account_creds_t GetAccountCreds() const;
  void SetAccountCreds(const account_creds_t& creds);

  bool Equals(const GoogleProp& key) const;

  static common::Optional<GoogleProp> Make(common::HashValue* json);

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* out) const override;

 private:
  account_creds_t account_creds_;
};

inline bool operator==(const GoogleProp& left, const GoogleProp& right) {
  return left.Equals(right);
}

inline bool operator!=(const GoogleProp& x, const GoogleProp& y) {
  return !(x == y);
}

}  // namespace fastotv

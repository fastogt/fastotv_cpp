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

class WhepProp : public common::serializer::JsonSerializer<WhepProp> {
 public:
  typedef JsonSerializer<WhepProp> base_class;
  typedef common::Optional<std::string> auth_token_t;

  WhepProp();
  explicit WhepProp(const auth_token_t& auth);

  bool IsValid() const;

  auth_token_t GetAuthToken() const;
  void SetAuthToken(const auth_token_t& token);

  bool Equals(const WhepProp& key) const;

  static common::Optional<WhepProp> Make(common::HashValue* json);

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* out) const override;

 private:
  auth_token_t auth_token_;
};

inline bool operator==(const WhepProp& left, const WhepProp& right) {
  return left.Equals(right);
}

inline bool operator!=(const WhepProp& x, const WhepProp& y) {
  return !(x == y);
}

}  // namespace fastotv

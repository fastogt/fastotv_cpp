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

class WebRTCProp : public common::serializer::JsonSerializer<WebRTCProp> {
 public:
  typedef JsonSerializer<WebRTCProp> base_class;
  typedef std::string stun_t;
  typedef std::string turn_t;

  WebRTCProp();
  explicit WebRTCProp(const stun_t& stun, const turn_t& turn);

  bool IsValid() const;

  stun_t GetStun() const;
  void SetStun(const stun_t& stun);

  turn_t GetTurn() const;
  void SetTurn(const turn_t& stun);

  bool Equals(const WebRTCProp& key) const;

  static common::Optional<WebRTCProp> Make(common::HashValue* json);

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* out) const override;

 private:
  stun_t stun_;
  turn_t turn_;
};

inline bool operator==(const WebRTCProp& left, const WebRTCProp& right) {
  return left.Equals(right);
}

inline bool operator!=(const WebRTCProp& x, const WebRTCProp& y) {
  return !(x == y);
}

}  // namespace fastotv

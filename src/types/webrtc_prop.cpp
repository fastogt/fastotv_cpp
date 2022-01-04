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

#include <fastotv/types/webrtc_prop.h>

#define STUN_FIELD "stun"
#define TURN_FIELD "turn"

namespace fastotv {

WebRTCProp::WebRTCProp() : stun_(), turn_() {}

WebRTCProp::WebRTCProp(const stun_t& stun, const turn_t& turn) : stun_(stun), turn_(turn) {}

bool WebRTCProp::IsValid() const {
  return !stun_.empty() && !turn_.empty();
}

WebRTCProp::stun_t WebRTCProp::GetStun() const {
  return stun_;
}

void WebRTCProp::SetStun(const stun_t& stun) {
  stun_ = stun;
}

WebRTCProp::turn_t WebRTCProp::GetTurn() const {
  return turn_;
}

void WebRTCProp::SetTurn(const turn_t& stun) {
  turn_ = stun;
}

bool WebRTCProp::Equals(const WebRTCProp& key) const {
  return stun_ == key.stun_ && turn_ == key.turn_;
}

common::Optional<WebRTCProp> WebRTCProp::Make(common::HashValue* json) {
  if (!json) {
    return common::Optional<WebRTCProp>();
  }

  WebRTCProp res;
  common::Value* stun_field = json->Find(STUN_FIELD);
  stun_t stun;
  if (!stun_field || !stun_field->GetAsBasicString(&stun)) {
    return common::Optional<WebRTCProp>();
  }
  res.stun_ = stun;

  common::Value* turn_field = json->Find(TURN_FIELD);
  turn_t turn;
  if (!turn_field || !turn_field->GetAsBasicString(&turn)) {
    return common::Optional<WebRTCProp>();
  }
  res.turn_ = turn;
  return res;
}

common::Error WebRTCProp::DoDeSerialize(json_object* serialized) {
  WebRTCProp res;
  stun_t stun;
  common::Error err = GetStringField(serialized, STUN_FIELD, &stun);
  if (err) {
    return err;
  }
  res.stun_ = stun;

  turn_t turn;
  err = GetStringField(serialized, TURN_FIELD, &turn);
  if (err) {
    return err;
  }
  res.turn_ = turn;
  *this = res;
  return common::Error();
}

common::Error WebRTCProp::SerializeFields(json_object* out) const {
  if (!IsValid()) {
    return common::make_error_inval();
  }

  ignore_result(SetStringField(out, STUN_FIELD, stun_));
  ignore_result(SetStringField(out, TURN_FIELD, turn_));
  return common::Error();
}

}  // namespace fastotv

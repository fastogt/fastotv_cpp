/*  Copyright (C) 2014-2020 FastoGT. All right reserved.

    This file is part of FastoTV.

    FastoTV is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    FastoTV is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FastoTV. If not, see <http://www.gnu.org/licenses/>.
*/

#include <fastotv/commands_info/notification_text_info.h>

#include <string>  // for string

#define TEXT_FIELD "message"
#define TEXT_TYPE_FIELD "type"
#define SHOW_TIME_FIELD "show_time"

namespace fastotv {
namespace commands_info {

NotificationTextInfo::NotificationTextInfo() : text_(), show_time_(0) {}

NotificationTextInfo::NotificationTextInfo(const std::string& text, MessageType type, common::time64_t show_time)
    : text_(text), type_(type), show_time_(show_time) {}

common::Error NotificationTextInfo::SerializeFields(json_object* deserialized) const {
  ignore_result(SetStringField(deserialized, TEXT_FIELD, text_));
  ignore_result(SetIntField(deserialized, TEXT_TYPE_FIELD, type_));
  ignore_result(SetInt64Field(deserialized, SHOW_TIME_FIELD, show_time_));
  return common::Error();
}

common::Error NotificationTextInfo::DoDeSerialize(json_object* serialized) {
  std::string text;
  common::Error err = GetStringField(serialized, TEXT_FIELD, &text);
  if (err) {
    return err;
  }

  MessageType type;
  err = GetEnumField<MessageType>(serialized, TEXT_TYPE_FIELD, &type);
  if (err) {
    return err;
  }

  int64_t show_time;
  err = GetInt64Field(serialized, SHOW_TIME_FIELD, &show_time);
  if (err) {
    return err;
  }

  *this = NotificationTextInfo(text, type, show_time);
  return common::Error();
}

std::string NotificationTextInfo::GetText() const {
  return text_;
}

void NotificationTextInfo::SetText(const std::string& text) {
  text_ = text;
}

common::time64_t NotificationTextInfo::GetShowTime() const {
  return show_time_;
}

void NotificationTextInfo::SetShowTime(common::time64_t time) {
  show_time_ = time;
}

NotificationTextInfo::MessageType NotificationTextInfo::GetType() const {
  return type_;
}

void NotificationTextInfo::SetType(MessageType type) {
  type_ = type;
}

bool NotificationTextInfo::Equals(const NotificationTextInfo& auth) const {
  return text_ == auth.text_ && show_time_ == auth.show_time_ && type_ == auth.type_;
}

}  // namespace commands_info
}  // namespace fastotv

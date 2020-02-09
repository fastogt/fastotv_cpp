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

#define NOTIFICATION_TEXT_INFO_TEXT_FIELD "message"
#define NOTIFICATION_TEXT_INFO_TEXT_TYPE_FIELD "type"
#define NOTIFICATION_TEXT_INFO_SHOW_TIME_FIELD "show_time"

namespace fastotv {
namespace commands_info {

NotificationTextInfo::NotificationTextInfo() : text_(), show_time_(0) {}

NotificationTextInfo::NotificationTextInfo(const std::string& text, MessageType type, common::time64_t show_time)
    : text_(text), type_(type), show_time_(show_time) {}

common::Error NotificationTextInfo::SerializeFields(json_object* deserialized) const {
  json_object_object_add(deserialized, NOTIFICATION_TEXT_INFO_TEXT_FIELD, json_object_new_string(text_.c_str()));
  json_object_object_add(deserialized, NOTIFICATION_TEXT_INFO_TEXT_TYPE_FIELD, json_object_new_int(type_));
  json_object_object_add(deserialized, NOTIFICATION_TEXT_INFO_SHOW_TIME_FIELD, json_object_new_int64(show_time_));
  return common::Error();
}

common::Error NotificationTextInfo::DoDeSerialize(json_object* serialized) {
  json_object* jtext = nullptr;
  json_bool jtext_exists = json_object_object_get_ex(serialized, NOTIFICATION_TEXT_INFO_TEXT_FIELD, &jtext);
  if (!jtext_exists) {
    return common::make_error_inval();
  }

  MessageType type = TEXT;
  json_object* jtype = nullptr;
  json_bool jtype_exists = json_object_object_get_ex(serialized, NOTIFICATION_TEXT_INFO_TEXT_TYPE_FIELD, &jtype);
  if (jtype_exists) {
    type = static_cast<MessageType>(json_object_get_int(jtype));
  }

  json_object* jshow_time = nullptr;
  json_bool jshow_time_exists =
      json_object_object_get_ex(serialized, NOTIFICATION_TEXT_INFO_SHOW_TIME_FIELD, &jshow_time);
  if (!jshow_time_exists) {
    return common::make_error_inval();
  }

  NotificationTextInfo ainf(json_object_get_string(jtext), type, json_object_get_int64(jshow_time));
  *this = ainf;
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

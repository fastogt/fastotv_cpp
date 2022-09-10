/*  Copyright (C) 2014-2022 FastoGT. All right reserved.

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

#pragma once

#include <common/serializer/json_serializer.h>
#include <common/time.h>

#include <string>

namespace fastotv {
namespace commands_info {

class NotificationTextInfo : public common::serializer::JsonSerializer<NotificationTextInfo> {
 public:
  enum MessageType { TEXT = 0, HYPERLINK = 1 };

  NotificationTextInfo();
  NotificationTextInfo(const std::string& text, MessageType message, common::time64_t show_time);

  std::string GetText() const;
  void SetText(const std::string& text);

  common::time64_t GetShowTime() const;
  void SetShowTime(common::time64_t time);

  MessageType GetType() const;
  void SetType(MessageType type);

  bool Equals(const NotificationTextInfo& auth) const;

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* deserialized) const override;

 private:
  std::string text_;
  MessageType type_;
  common::time64_t show_time_;
};

inline bool operator==(const NotificationTextInfo& lhs, const NotificationTextInfo& rhs) {
  return lhs.Equals(rhs);
}

inline bool operator!=(const NotificationTextInfo& x, const NotificationTextInfo& y) {
  return !(x == y);
}

}  // namespace commands_info
}  // namespace fastotv

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

#pragma once

#include <string>

#include <common/serializer/json_serializer.h>
#include <common/time.h>

namespace fastotv {
namespace commands_info {

class ContentRequestInfo : public common::serializer::JsonSerializer<ContentRequestInfo> {
 public:
  enum ContentType { LIVE = 0, VODS = 1, SERIAL = 2 };

  ContentRequestInfo();
  ContentRequestInfo(const std::string& text, ContentType type);

  std::string GetText() const;
  void SetText(const std::string& text);

  common::time64_t GetShowTime() const;
  void SetShowTime(common::time64_t time);

  ContentType GetType() const;
  void SetType(ContentType type);

  bool Equals(const ContentRequestInfo& auth) const;

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* deserialized) const override;

 private:
  std::string text_;
  ContentType type_;
};

inline bool operator==(const ContentRequestInfo& lhs, const ContentRequestInfo& rhs) {
  return lhs.Equals(rhs);
}

inline bool operator!=(const ContentRequestInfo& x, const ContentRequestInfo& y) {
  return !(x == y);
}

}  // namespace commands_info
}  // namespace fastotv

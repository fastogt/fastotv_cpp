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

#include <fastotv/types.h>

namespace fastotv {
namespace commands_info {

class CreateContentRequestInfo : public common::serializer::JsonSerializer<CreateContentRequestInfo> {
 public:
  enum ContentType { LIVE = 0, VODS = 1, SERIAL = 2 };
  enum RequestStatus { NEW = 0, IN_PROGRESS = 1, DONE = 2 };

  CreateContentRequestInfo();
  CreateContentRequestInfo(const std::string& text, ContentType type, RequestStatus status);

  std::string GetText() const;
  void SetText(const std::string& text);

  common::time64_t GetShowTime() const;
  void SetShowTime(common::time64_t time);

  ContentType GetType() const;
  void SetType(ContentType type);

  RequestStatus GetStatus() const;
  void SetStatus(RequestStatus status);

  bool Equals(const CreateContentRequestInfo& auth) const;

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* deserialized) const override;

 private:
  std::string text_;
  ContentType type_;
  RequestStatus status_;
};

class ContentRequestInfo : public CreateContentRequestInfo {
 public:
  typedef CreateContentRequestInfo base_class;

  ContentRequestInfo();
  ContentRequestInfo(const content_request_id_t& rid, const std::string& text, ContentType type, RequestStatus status);

  bool IsValid() const;

  bool Equals(const ContentRequestInfo& auth) const;

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* deserialized) const override;

 private:
  content_request_id_t rid_;
};

inline bool operator==(const CreateContentRequestInfo& lhs, const CreateContentRequestInfo& rhs) {
  return lhs.Equals(rhs);
}

inline bool operator!=(const CreateContentRequestInfo& x, const CreateContentRequestInfo& y) {
  return !(x == y);
}

inline bool operator==(const ContentRequestInfo& lhs, const ContentRequestInfo& rhs) {
  return lhs.Equals(rhs);
}

inline bool operator!=(const ContentRequestInfo& x, const ContentRequestInfo& y) {
  return !(x == y);
}

}  // namespace commands_info
}  // namespace fastotv

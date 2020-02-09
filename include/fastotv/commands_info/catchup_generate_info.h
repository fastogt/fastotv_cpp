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

#include <vector>

#include <common/serializer/json_serializer.h>

#include <fastotv/commands_info/catchup_info.h>

namespace fastotv {
namespace commands_info {

class CatchupGenerateInfo : public common::serializer::JsonSerializer<CatchupGenerateInfo> {
 public:
  CatchupGenerateInfo();
  explicit CatchupGenerateInfo(stream_id_t sid,
                               const std::string& title,
                               timestamp_t start_time,
                               timestamp_t stop_time);
  ~CatchupGenerateInfo();

  bool IsValid() const;

  void SetStreamID(stream_id_t sid);
  stream_id_t GetStreamID() const;

  void SetStart(timestamp_t start);  // UTC
  timestamp_t GetStart() const;

  void SetStop(timestamp_t stop);  // UTC
  timestamp_t GetStop() const;

  void SetTitle(const std::string& title);
  std::string GetTitle() const;

  bool Equals(const CatchupGenerateInfo& inf) const;

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* deserialized) const override;

 private:
  stream_id_t sid_;
  std::string title_;
  timestamp_t start_time_;  // utc time
  timestamp_t stop_time_;   // utc time
};

inline bool operator==(const CatchupGenerateInfo& left, const CatchupGenerateInfo& right) {
  return left.Equals(right);
}

inline bool operator!=(const CatchupGenerateInfo& x, const CatchupGenerateInfo& y) {
  return !(x == y);
}

class CatchupQueueInfo : public common::serializer::JsonSerializer<CatchupQueueInfo> {
 public:
  CatchupQueueInfo();
  explicit CatchupQueueInfo(const CatchupInfo& info);
  ~CatchupQueueInfo();

  bool IsValid() const;

  void SetCatchup(const CatchupInfo& cinf);
  CatchupInfo GetCatchup() const;

  bool Equals(const CatchupQueueInfo& inf) const;

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* deserialized) const override;

 private:
  CatchupInfo cinf_;
};

inline bool operator==(const CatchupQueueInfo& left, const CatchupQueueInfo& right) {
  return left.Equals(right);
}

inline bool operator!=(const CatchupQueueInfo& x, const CatchupQueueInfo& y) {
  return !(x == y);
}

}  // namespace commands_info
}  // namespace fastotv

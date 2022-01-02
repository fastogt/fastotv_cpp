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

#include <string>

#include <common/serializer/json_serializer.h>
#include <common/value.h>

#include <fastotv/types.h>

namespace fastotv {

class Programme : public common::serializer::JsonSerializer<Programme> {
 public:
  typedef common::Optional<std::string> category_t;
  typedef common::Optional<std::string> description_t;

  Programme();
  Programme(const stream_id_t& id,
            timestamp_t start_time,
            timestamp_t stop_time,
            const std::string& title,
            const category_t& category,
            const description_t& descr);

  bool IsValid() const;

  void SetChannel(const stream_id_t& channel);
  stream_id_t GetChannel() const;

  void SetStart(timestamp_t start);  // UTC
  timestamp_t GetStart() const;

  void SetStop(timestamp_t stop);  // UTC
  timestamp_t GetStop() const;

  void SetTitle(const std::string& title);
  std::string GetTitle() const;

  void SetCategory(const category_t& category);
  category_t GetCategory() const;

  void SetDescription(const description_t& description);
  description_t GetDescription() const;

  bool Equals(const Programme& prog) const;

  static common::Optional<Programme> Make(common::HashValue* json);

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* deserialized) const override;

 private:
  stream_id_t channel_;
  timestamp_t start_time_;  // utc time
  timestamp_t stop_time_;   // utc time
  std::string title_;
  category_t category_;
  description_t description_;
};

inline bool operator==(const Programme& lhs, const Programme& rhs) {
  return lhs.Equals(rhs);
}

inline bool operator!=(const Programme& x, const Programme& y) {
  return !(x == y);
}

}  // namespace fastotv

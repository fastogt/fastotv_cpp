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

#include <fastotv/types.h>

namespace fastotv {
namespace commands_info {

class CatchupUndoInfo : public common::serializer::JsonSerializer<CatchupUndoInfo> {
 public:
  CatchupUndoInfo();
  explicit CatchupUndoInfo(const stream_id_t& sid);
  ~CatchupUndoInfo();

  bool IsValid() const;

  void SetStreamID(const stream_id_t& sid);
  stream_id_t GetStreamID() const;

  bool Equals(const CatchupUndoInfo& inf) const;

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* deserialized) const override;

 private:
  stream_id_t sid_;
};

inline bool operator==(const CatchupUndoInfo& left, const CatchupUndoInfo& right) {
  return left.Equals(right);
}

inline bool operator!=(const CatchupUndoInfo& x, const CatchupUndoInfo& y) {
  return !(x == y);
}

}  // namespace commands_info
}  // namespace fastotv

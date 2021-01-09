/*  Copyright (C) 2014-2021 FastoGT. All right reserved.

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
#include <vector>

#include <common/serializer/json_serializer.h>

#include <fastotv/commands_info/ml/types.h>
#include <fastotv/types.h>

namespace fastotv {
namespace commands_info {
namespace ml {

class NotificationInfo : public common::serializer::JsonSerializer<NotificationInfo> {
 public:
  typedef std::vector<ImageBox> images_t;

  NotificationInfo();
  explicit NotificationInfo(const stream_id_t& sid, const images_t& images);

  fastotv::stream_id_t GetStreamID() const;
  void SetStreamID(const fastotv::stream_id_t& sid);

  images_t GetImages() const;
  void SetImages(const images_t& images);

  void AddImage(const ImageBox& image);
  void ClearImages();

  bool Equals(const NotificationInfo& norification) const;

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* deserialized) const override;

 private:
  fastotv::stream_id_t sid_;
  images_t images_;
};

inline bool operator==(const NotificationInfo& lhs, const NotificationInfo& rhs) {
  return lhs.Equals(rhs);
}

inline bool operator!=(const NotificationInfo& x, const NotificationInfo& y) {
  return !(x == y);
}

}  // namespace ml
}  // namespace commands_info
}  // namespace fastotv

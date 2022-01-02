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

#include <fastotv/commands_info/ml/types.h>

namespace fastotv {
namespace commands_info {
namespace ml {

ImageBox::ImageBox() : unique_component_id(0), class_id(0), object_id(0), confidence(0), rect() {}

ImageBox::ImageBox(int32_t unique_component_id,
                   int32_t class_id,
                   uint64_t object_id,
                   float confidence,
                   const common::draw::Rect& rect)
    : unique_component_id(unique_component_id),
      class_id(class_id),
      object_id(object_id),
      confidence(confidence),
      rect(rect) {}

bool ImageBox::Equals(const ImageBox& box) const {
  return class_id == box.class_id && confidence == box.confidence && unique_component_id == box.unique_component_id &&
         object_id == box.object_id && rect == box.rect;
}

std::ostream& operator<<(std::ostream& out, const ImageBox& box) {
  return out << "Class id: " << box.class_id << ", Confidence: " << box.confidence
             << ", Unique component id: " << box.unique_component_id << ", Object id: " << box.object_id
             << ", Rect: " << box.rect.ToString();
}

}  // namespace ml
}  // namespace commands_info
}  // namespace fastotv

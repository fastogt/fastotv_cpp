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

#include <common/draw/rect.h>

#include <vector>

namespace fastotv {
namespace commands_info {
namespace ml {

enum InferDataType { FLOAT = 0, HALF = 1, INT8 = 2, INT32 = 3 };

struct InferLayer {
  std::string name;
  InferDataType type;
  size_t size;
  void* data;

  InferLayer();

  bool Equals(const InferLayer& layer) const;
};

inline bool operator==(const InferLayer& lhs, const InferLayer& rhs) {
  return lhs.Equals(rhs);
}

inline bool operator!=(const InferLayer& x, const InferLayer& y) {
  return !(x == y);
}

std::ostream& operator<<(std::ostream& out, const InferLayer& box);

struct ImageBox {
  std::string sender;
  int32_t unique_component_id;
  int32_t class_id;
  uint64_t object_id;
  float confidence;
  common::draw::Rect rect;
  std::vector<InferLayer> layers;

  ImageBox();
  ImageBox(const std::string& sender,
           int32_t unique_component_id,
           int32_t class_id,
           uint64_t object_id,
           float confidence,
           const common::draw::Rect& rect,
           const std::vector<InferLayer>& layers);

  bool Equals(const ImageBox& box) const;
};

inline bool operator==(const ImageBox& lhs, const ImageBox& rhs) {
  return lhs.Equals(rhs);
}

inline bool operator!=(const ImageBox& x, const ImageBox& y) {
  return !(x == y);
}

std::ostream& operator<<(std::ostream& out, const ImageBox& box);

}  // namespace ml
}  // namespace commands_info
}  // namespace fastotv

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
#include <common/optional.h>
#include <fastotv/types.h>
#include <memory>
#include <vector>

namespace fastotv {
namespace commands_info {
namespace ml {

enum InferDataType { FLOAT = 0, HALF = 1, INT8 = 2, INT32 = 3 };

struct InferLayer {
  typedef float_t fp32_t;
  typedef float_t fp16_t;
  typedef int8_t i8_t;
  typedef int32_t i32_t;

  std::string name;
  InferDataType type;
  uint64_t size;
  std::shared_ptr<fp32_t[]> data;

  InferLayer();

  static common::Optional<InferLayer> MakeInferLayer(const std::string& name,
                                                     InferDataType type,
                                                     void* data,
                                                     uint64_t size);
  static std::shared_ptr<fp32_t[]> AllocateData(uint64_t size);

  bool Equals(const InferLayer& layer) const;
};

inline bool operator==(const InferLayer& lhs, const InferLayer& rhs) {
  return lhs.Equals(rhs);
}

inline bool operator!=(const InferLayer& x, const InferLayer& y) {
  return !(x == y);
}

std::ostream& operator<<(std::ostream& out, const InferLayer& box);

struct LabelInfo {
  std::string label;
  uint32_t label_id;
  uint32_t class_id;
  float probability;

  LabelInfo();

  bool Equals(const LabelInfo& lb) const;
};

inline bool operator==(const LabelInfo& lhs, const LabelInfo& rhs) {
  return lhs.Equals(rhs);
}

inline bool operator!=(const LabelInfo& x, const LabelInfo& y) {
  return !(x == y);
}

std::ostream& operator<<(std::ostream& out, const LabelInfo& box);

struct ImageBox {
  std::string sender;
  int32_t unique_component_id;
  int32_t class_id;
  uint64_t object_id;
  float confidence;
  timestamp_t timestamp;
  common::draw::Rect rect;
  std::vector<InferLayer> layers;
  std::vector<LabelInfo> labels;

  ImageBox();
  ImageBox(const std::string& sender,
           int32_t unique_component_id,
           int32_t class_id,
           uint64_t object_id,
           float confidence,
           timestamp_t ts,
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

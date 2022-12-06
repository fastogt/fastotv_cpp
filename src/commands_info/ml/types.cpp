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

#include <memory.h>

namespace fastotv {
namespace commands_info {
namespace ml {

InferLayer::InferLayer() : name(), type(FLOAT), size(0), data() {}

common::Optional<InferLayer> InferLayer::MakeInferLayer(const std::string& name,
                                                        InferDataType type,
                                                        void* data,
                                                        uint64_t size) {
  if (!data) {
    return common::Optional<InferLayer>();
  }

  InferLayer layer;
  layer.name = name;
  layer.type = type;
  layer.size = size;
  if (size != 0) {
    layer.data = AllocateData(size);
    for (uint64_t i = 0; i < size; ++i) {
      if (layer.type == FLOAT) {
        auto place = static_cast<fp32_t*>(data) + i;
        layer.data[i] = *place;
      } else if (layer.type == HALF) {
        auto place = static_cast<fp16_t*>(data) + i;
        layer.data[i] = *place;
      } else if (layer.type == INT8) {
        auto place = static_cast<i8_t*>(data) + i;
        layer.data[i] = *place;
      } else {
        auto place = static_cast<i32_t*>(data) + i;
        layer.data[i] = *place;
      }
    }
  }
  return layer;
}

std::shared_ptr<InferLayer::fp32_t[]> InferLayer::AllocateData(uint64_t size) {
  return std::shared_ptr<fp32_t[]>(new fp32_t[size]());
}

bool InferLayer::Equals(const InferLayer& layer) const {
  return name == layer.name && type == layer.type && size == layer.size && data == layer.data;
}

std::ostream& operator<<(std::ostream& out, const InferLayer& layer) {
  InferLayer::fp32_t* data = static_cast<InferLayer::fp32_t*>(layer.data.get());
  std::stringstream str;
  if (data) {
    for (uint64_t i = 0; i < layer.size; ++i) {
      auto place = data + i;
      if (layer.type == FLOAT) {
        str << static_cast<InferLayer::fp32_t>(*place);
      } else if (layer.type == HALF) {
        str << static_cast<InferLayer::fp16_t>(*place);
      } else if (layer.type == INT8) {
        str << static_cast<InferLayer::i8_t>(*place);
      } else {
        str << static_cast<InferLayer::i32_t>(*place);
      }

      if (i + 1 < layer.size) {
        str << ", ";
      }
    }
  }
  return out << "Name: " << layer.name << ", size: " << layer.size << ", type: " << layer.type << ", data: "
             << "[" << str.str() << "]";
}

ImageBox::ImageBox() : sender(), unique_component_id(0), class_id(0), object_id(0), confidence(0), rect(), layers() {}

ImageBox::ImageBox(const std::string& sender,
                   int32_t unique_component_id,
                   int32_t class_id,
                   uint64_t object_id,
                   float confidence,
                   const common::draw::Rect& rect,
                   const std::vector<InferLayer>& layers)
    : sender(sender),
      unique_component_id(unique_component_id),
      class_id(class_id),
      object_id(object_id),
      confidence(confidence),
      rect(rect),
      layers(layers) {}

bool ImageBox::Equals(const ImageBox& box) const {
  return sender == box.sender && class_id == box.class_id && confidence == box.confidence &&
         unique_component_id == box.unique_component_id && object_id == box.object_id && rect == box.rect;
}

std::ostream& operator<<(std::ostream& out, const ImageBox& box) {
  std::stringstream str;
  for (size_t i = 0; i < box.layers.size(); ++i) {
    str << "[" << i << "] " << box.layers[i];
    if (i + 1 < box.layers.size()) {
      str << ", ";
    }
  }
  return out << "Sender: " << box.sender << ", Class id: " << box.class_id << ", Confidence: " << box.confidence
             << ", Unique component id: " << box.unique_component_id << ", Object id: " << box.object_id
             << ", Rect: " << box.rect.ToString() << ", Layers: " << str.str();
}

}  // namespace ml
}  // namespace commands_info
}  // namespace fastotv

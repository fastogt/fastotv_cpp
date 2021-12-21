/*  Copyright (C) 2014-2019 FastoGT. All right reserved.
    This file is part of fastocloud.
    fastocloud is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    fastocloud is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with fastocloud.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <fastotv/types/ml/audio_stabilization.h>

#define TYPE_FIELD "type"
#define GPU_MODEL_FIELD "gpu_model"

namespace fastotv {
namespace ml {

AudioStabilization::AudioStabilization(AudioEffectType type, GpuModel model) : type_(type), gpu_(model) {}

bool AudioStabilization::Equals(const AudioStabilization& back) const {
  return back.type_ == type_;
}

AudioEffectType AudioStabilization::GetType() const {
  return type_;
}

GpuModel AudioStabilization::GetGpuModel() const {
  return gpu_;
}

common::Optional<AudioStabilization> AudioStabilization::Make(common::HashValue* hash) {
  if (!hash) {
    return common::Optional<AudioStabilization>();
  }

  common::Value* type_field = hash->Find(TYPE_FIELD);
  int64_t type;
  if (!type_field || !type_field->GetAsInteger64(&type)) {
    return common::Optional<AudioStabilization>();
  }

  GpuModel model = NVIDIA_T4;
  common::Value* model_field = hash->Find(GPU_MODEL_FIELD);
  int64_t md;
  if (model_field && model_field->GetAsInteger64(&md)) {
    model = static_cast<GpuModel>(md);
  }

  return AudioStabilization(static_cast<AudioEffectType>(type), model);
}

common::Error AudioStabilization::DoDeSerialize(json_object* serialized) {
  AudioEffectType type;
  common::Error err = GetEnumField(serialized, TYPE_FIELD, &type);
  if (err) {
    return err;
  }

  GpuModel model = NVIDIA_T4;
  ignore_result(GetEnumField(serialized, GPU_MODEL_FIELD, &model));

  *this = AudioStabilization(type, model);
  return common::Error();
}

common::Error AudioStabilization::SerializeFields(json_object* out) const {
  ignore_result(SetIntField(out, TYPE_FIELD, type_));
  ignore_result(SetIntField(out, GPU_MODEL_FIELD, gpu_));
  return common::Error();
}

}  // namespace ml
}  // namespace fastotv

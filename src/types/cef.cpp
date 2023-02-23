/*  Copyright (C) 2014-2023 FastoGT. All right reserved.
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

#include <fastotv/types/cef.h>

#define GPU_FIELD "gpu"

namespace fastotv {

Cef::Cef() : gpu_() {}

Cef::Cef(gpu_t gpu) : gpu_(gpu) {}

void Cef::SetGL(gpu_t gpu) {
  gpu_ = gpu;
}

Cef::gpu_t Cef::GetGPU() const {
  return gpu_;
}

bool Cef::Equals(const Cef& inf) const {
  return gpu_ == inf.gpu_;
}

common::Optional<Cef> Cef::Make(common::HashValue* hash) {
  if (!hash) {
    return common::Optional<Cef>();
  }

  common::Value* gpu_field = hash->Find(GPU_FIELD);
  bool gpu;
  if (!gpu_field || !gpu_field->GetAsBoolean(&gpu)) {
    return common::Optional<Cef>();
  }
  return Cef(gpu);
}

common::Error Cef::DoDeSerialize(json_object* serialized) {
  bool gpu;
  common::Error err = GetBoolField(serialized, GPU_FIELD, &gpu);
  if (err) {
    return err;
  }

  *this = Cef(gpu);
  return common::Error();
}

common::Error Cef::SerializeFields(json_object* out) const {
  ignore_result(SetBoolField(out, GPU_FIELD, gpu_));
  return common::Error();
}

}  // namespace fastotv

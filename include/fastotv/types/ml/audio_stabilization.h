/*  Copyright (C) 2014-2021 FastoGT. All right reserved.
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

#pragma once

#include <string>

#include <common/serializer/json_serializer.h>
#include <common/uri/gurl.h>
#include <common/value.h>

namespace fastotv {
namespace ml {

enum AudioEffectType { DENOISER, DEREVERB, DEREVERB_DENOISER };
enum GpuModel { NVIDIA_A100, NVIDIA_A10, NVIDIA_T4, NVIDIA_V100 };

class AudioStabilization : public common::serializer::JsonSerializer<AudioStabilization> {
 public:
  typedef common::serializer::JsonSerializer<AudioStabilization> base_class;

  AudioStabilization(AudioEffectType type, GpuModel model);

  bool Equals(const AudioStabilization& back) const;

  AudioEffectType GetType() const;

  static common::Optional<AudioStabilization> Make(common::HashValue* hash);

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* out) const override;

 private:
  AudioEffectType type_;
  GpuModel gpu_;
};

}  // namespace ml
}  // namespace fastotv

/*  Copyright (C) 2014-2022 FastoGT. All right reserved.
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

#include <common/file_system/path.h>
#include <common/serializer/json_serializer.h>
#include <common/uri/gurl.h>
#include <common/value.h>

#include <string>
#include <vector>

namespace fastotv {
namespace ml {

enum SupportedBackends { NVIDIA = 0 };

class Model : public common::serializer::JsonSerializer<Model> {
 public:
  typedef common::file_system::ascii_file_string_path model_path_t;

  Model();
  explicit Model(const model_path_t& path);

  model_path_t GetModelPath() const;
  void SetModelPath(const model_path_t& path);

  bool Equals(const Model& model) const;

  static common::Optional<Model> MakeMachineLearning(common::HashValue* hash);

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* out) const override;

 private:
  model_path_t path_;
};

inline bool operator==(const Model& lhs, const Model& rhs) {
  return lhs.Equals(rhs);
}

typedef common::serializer::JsonSerializerArray<Model> ModelsInfo;

class MachineLearning : public common::serializer::JsonSerializer<MachineLearning> {
 public:
  MachineLearning();
  MachineLearning(SupportedBackends backend, const ModelsInfo& models);

  bool Equals(const MachineLearning& learn) const;

  SupportedBackends GetBackend() const;
  void SetBackend(SupportedBackends backend);

  ModelsInfo GetModels() const;
  void SetModels(const ModelsInfo& path);

  bool GetNeedTracking() const;
  void SetNeedTracking(bool tracking);

  bool GetNeedOverlay() const;
  void SetNeedOverlay(bool overlay);

  static common::Optional<MachineLearning> MakeMachineLearning(common::HashValue* hash);

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* out) const override;

 private:
  SupportedBackends backend_;
  ModelsInfo models_;
  bool tracking_;
  bool overlay_;
};

}  // namespace ml
}  // namespace fastotv

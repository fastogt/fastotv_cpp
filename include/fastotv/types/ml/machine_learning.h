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
#include <vector>

#include <common/serializer/json_serializer.h>
#include <common/uri/gurl.h>
#include <common/value.h>

namespace fastotv {
namespace ml {

enum SupportedBackends { NVIDIA = 0 };

class MachineLearning : public common::serializer::JsonSerializer<MachineLearning> {
 public:
  typedef common::uri::GURL model_path_t;

  MachineLearning();
  MachineLearning(SupportedBackends backend, const model_path_t& model_path);

  bool Equals(const MachineLearning& learn) const;

  SupportedBackends GetBackend() const;
  void SetBackend(SupportedBackends backend);

  model_path_t GetModelPath() const;
  void SetModelPath(const model_path_t& path);

  bool GetNeedTracking() const;
  void SetNeedTracking(bool tracking);

  bool GetNeedDump() const;
  void SetNeedDump(bool dump);

  bool GetNeedOverlay() const;
  void SetNeedOverlay(bool overlay);

  int GetClassID() const;
  void SetClassID(int cid);

  static common::Optional<MachineLearning> MakeMachineLearning(common::HashValue* hash);

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* out) const override;

 private:
  SupportedBackends backend_;
  model_path_t model_path_;
  bool tracking_;
  bool dump_;
  int class_id_;
  bool overlay_;
};

}  // namespace ml
}  // namespace fastotv

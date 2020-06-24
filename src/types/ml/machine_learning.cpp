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

#include <fastotv/types/ml/machine_learning.h>

#include <json-c/json_object.h>
#include <json-c/json_tokener.h>
#include <json-c/linkhash.h>

#include <common/sprintf.h>

#define DEEP_LEARNING_BACKEND_FIELD "backend"
#define DEEP_LEARNING_MODEL_PATH_FIELD "model_url"
#define DEEP_LEARNING_OVERLAY_FIELD "overlay"

namespace fastotv {
namespace ml {

MachineLearning::MachineLearning() : backend_(NVIDIA), model_path_(), overlay_(false) {}

MachineLearning::MachineLearning(SupportedBackends backend, const model_path_t& model_path)
    : backend_(backend), model_path_(model_path), overlay_() {}

MachineLearning::model_path_t MachineLearning::GetModelPath() const {
  return model_path_;
}

void MachineLearning::SetModelPath(const model_path_t& path) {
  model_path_ = path;
}

bool MachineLearning::GetNeedOverlay() const {
  return overlay_;
}

void MachineLearning::SetNeedOverlay(bool overlay) {
  overlay_ = overlay;
}

SupportedBackends MachineLearning::GetBackend() const {
  return backend_;
}

void MachineLearning::SetBackend(SupportedBackends backend) {
  backend_ = backend;
}

bool MachineLearning::Equals(const MachineLearning& learn) const {
  return learn.backend_ == backend_ && learn.model_path_ == model_path_ && learn.overlay_ == overlay_;
}

common::Optional<MachineLearning> MachineLearning::MakeMachineLearning(common::HashValue* hash) {
  if (!hash) {
    return common::Optional<MachineLearning>();
  }

  MachineLearning res;
  common::Value* learning_backend_field = hash->Find(DEEP_LEARNING_BACKEND_FIELD);
  int backend;
  if (!learning_backend_field || !learning_backend_field->GetAsInteger(&backend)) {
    return common::Optional<MachineLearning>();
  }
  res.SetBackend(static_cast<SupportedBackends>(backend));

  std::string model_path_str;
  common::Value* model_path_field = hash->Find(DEEP_LEARNING_MODEL_PATH_FIELD);
  if (!model_path_field || !model_path_field->GetAsBasicString(&model_path_str)) {
    return common::Optional<MachineLearning>();
  }
  res.SetModelPath(common::uri::GURL(model_path_str));

  bool overlay;
  common::Value* overlay_field = hash->Find(DEEP_LEARNING_OVERLAY_FIELD);
  if (!overlay_field || !overlay_field->GetAsBoolean(&overlay)) {
    return common::Optional<MachineLearning>();
  }
  res.SetNeedOverlay(overlay);
  return res;
}

common::Error MachineLearning::DoDeSerialize(json_object* serialized) {
  MachineLearning res;
  json_object* jbackend = nullptr;
  json_bool jbackend_exists = json_object_object_get_ex(serialized, DEEP_LEARNING_BACKEND_FIELD, &jbackend);
  if (!jbackend_exists) {
    return common::make_error_inval();
  }
  res.SetBackend(static_cast<SupportedBackends>(json_object_get_int(jbackend)));

  json_object* jmodel_path = nullptr;
  json_bool jmodel_path_exists = json_object_object_get_ex(serialized, DEEP_LEARNING_MODEL_PATH_FIELD, &jmodel_path);
  if (!jmodel_path_exists) {
    return common::make_error_inval();
  }
  res.SetModelPath(common::uri::GURL(json_object_get_string(jmodel_path)));
  *this = res;
  return common::Error();
}

common::Error MachineLearning::SerializeFields(json_object* out) const {
  json_object_object_add(out, DEEP_LEARNING_BACKEND_FIELD, json_object_new_int64(backend_));
  const std::string model_path_str = model_path_.spec();
  json_object_object_add(out, DEEP_LEARNING_MODEL_PATH_FIELD, json_object_new_string(model_path_str.c_str()));
  json_object_object_add(out, DEEP_LEARNING_OVERLAY_FIELD, json_object_new_boolean(overlay_));
  return common::Error();
}

}  // namespace ml
}  // namespace fastotv

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

#define PATH_FIELD "path"

#define BACKEND_FIELD "backend"
#define MODELS_FIELD "models"
#define TRACKING_FIELD "tracking"
#define OVERLAY_FIELD "overlay"

namespace fastotv {
namespace ml {

Model::Model() : path_() {}

Model::Model(const model_path_t& path) : path_(path) {}

Model::model_path_t Model::GetModelPath() const {
  return path_;
}

void Model::SetModelPath(const Model::model_path_t& path) {
  path_ = path;
}

bool Model::Equals(const Model& model) const {
  return model.path_ == path_;
}

common::Optional<Model> Model::MakeMachineLearning(common::HashValue* hash) {
  if (!hash) {
    return common::Optional<Model>();
  }

  std::string model_path;
  common::Value* model_path_field = hash->Find(PATH_FIELD);
  if (!model_path_field || !model_path_field->GetAsBasicString(&model_path)) {
    return common::Optional<Model>();
  }

  Model res = Model(model_path_t(model_path));
  return res;
}

common::Error Model::DoDeSerialize(json_object* serialized) {
  std::string model_path;
  common::Error err = GetStringField(serialized, PATH_FIELD, &model_path);
  if (err) {
    return err;
  }

  *this = Model(model_path_t(model_path));
  return common::Error();
}

common::Error Model::SerializeFields(json_object* out) const {
  const std::string model_path_str = path_.GetPath();
  ignore_result(SetStringField(out, PATH_FIELD, model_path_str));
  return common::Error();
}

MachineLearning::MachineLearning() : backend_(NVIDIA), models_(), tracking_(false), overlay_(false) {}

MachineLearning::MachineLearning(SupportedBackends backend, const ModelsInfo& models)
    : backend_(backend), models_(models), overlay_(false) {}

ModelsInfo MachineLearning::GetModels() const {
  return models_;
}

void MachineLearning::SetModels(const ModelsInfo& path) {
  models_ = path;
}

bool MachineLearning::GetNeedTracking() const {
  return tracking_;
}

void MachineLearning::SetNeedTracking(bool tracking) {
  tracking_ = tracking;
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
  return learn.backend_ == backend_ && learn.models_ == models_ && learn.overlay_ == overlay_;
}

common::Optional<MachineLearning> MachineLearning::MakeMachineLearning(common::HashValue* hash) {
  if (!hash) {
    return common::Optional<MachineLearning>();
  }

  MachineLearning res;
  common::Value* learning_backend_field = hash->Find(BACKEND_FIELD);
  int64_t backend;
  if (!learning_backend_field || !learning_backend_field->GetAsInteger64(&backend)) {
    return common::Optional<MachineLearning>();
  }
  res.SetBackend(static_cast<SupportedBackends>(backend));

  std::string models_str;
  common::Value* model_path_field = hash->Find(MODELS_FIELD);
  if (!model_path_field || !model_path_field->GetAsBasicString(&models_str)) {
    return common::Optional<MachineLearning>();
  }

  ModelsInfo models;
  common::Error err = models.DeSerializeFromString(models_str);
  if (err) {
    return common::Optional<MachineLearning>();
  }

  if (models.Empty()) {
    return common::Optional<MachineLearning>();
  }

  res.SetModels(models);

  bool tracking;
  common::Value* tracking_field = hash->Find(TRACKING_FIELD);
  if (!tracking_field || !tracking_field->GetAsBoolean(&tracking)) {
    return common::Optional<MachineLearning>();
  }
  res.SetNeedTracking(tracking);

  bool overlay;
  common::Value* overlay_field = hash->Find(OVERLAY_FIELD);
  if (!overlay_field || !overlay_field->GetAsBoolean(&overlay)) {
    return common::Optional<MachineLearning>();
  }
  res.SetNeedOverlay(overlay);
  return res;
}

common::Error MachineLearning::DoDeSerialize(json_object* serialized) {
  SupportedBackends backend;
  common::Error err = GetEnumField(serialized, BACKEND_FIELD, &backend);
  if (err) {
    return err;
  }

  size_t len;
  json_object* jmodels;
  err = GetArrayField(serialized, MODELS_FIELD, &jmodels, &len);
  if (err) {
    return err;
  }

  ModelsInfo models;
  err = models.DeSerialize(jmodels);
  if (err) {
    return err;
  }

  if (models.Empty()) {
    return common::make_error_inval();
  }

  MachineLearning lresult(backend, models);
  bool tracking;
  err = GetBoolField(serialized, TRACKING_FIELD, &tracking);
  if (err) {
    return err;
  }
  lresult.SetNeedTracking(tracking);

  bool overlay;
  err = GetBoolField(serialized, OVERLAY_FIELD, &overlay);
  if (err) {
    return err;
  }
  lresult.SetNeedOverlay(overlay);

  *this = lresult;
  return common::Error();
}

common::Error MachineLearning::SerializeFields(json_object* out) const {
  ignore_result(SetInt64Field(out, BACKEND_FIELD, backend_));
  json_object* jobj = nullptr;
  common::Error err = models_.Serialize(&jobj);
  if (err) {
    return err;
  }

  ignore_result(SetArrayField(out, MODELS_FIELD, jobj));
  ignore_result(SetBoolField(out, TRACKING_FIELD, tracking_));
  ignore_result(SetBoolField(out, OVERLAY_FIELD, overlay_));
  return common::Error();
}

}  // namespace ml
}  // namespace fastotv

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

#define BACKEND_FIELD "backend"
#define MODEL_PATH_FIELD "model_url"
#define TRACKING_FIELD "tracking"
#define CLASS_ID_FIELD "class_id"
#define OVERLAY_FIELD "overlay"
#define DUMP_FIELD "dump"

namespace fastotv {
namespace ml {

MachineLearning::MachineLearning()
    : backend_(NVIDIA), model_path_(), tracking_(false), dump_(false), class_id_(0), overlay_(false) {}

MachineLearning::MachineLearning(SupportedBackends backend, const model_path_t& model_path)
    : backend_(backend), model_path_(model_path), class_id_(0), overlay_(false) {}

MachineLearning::model_path_t MachineLearning::GetModelPath() const {
  return model_path_;
}

void MachineLearning::SetModelPath(const model_path_t& path) {
  model_path_ = path;
}

bool MachineLearning::GetNeedTracking() const {
  return tracking_;
}

void MachineLearning::SetNeedTracking(bool tracking) {
  tracking_ = tracking;
}

bool MachineLearning::GetNeedDump() const {
  return dump_;
}

void MachineLearning::SetNeedDump(bool dump) {
  dump_ = dump;
}

bool MachineLearning::GetNeedOverlay() const {
  return overlay_;
}

void MachineLearning::SetNeedOverlay(bool overlay) {
  overlay_ = overlay;
}

int MachineLearning::GetClassID() const {
  return class_id_;
}

void MachineLearning::SetClassID(int cid) {
  class_id_ = cid;
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
  common::Value* learning_backend_field = hash->Find(BACKEND_FIELD);
  int64_t backend;
  if (!learning_backend_field || !learning_backend_field->GetAsLongInteger(&backend)) {
    return common::Optional<MachineLearning>();
  }
  res.SetBackend(static_cast<SupportedBackends>(backend));

  std::string model_path_str;
  common::Value* model_path_field = hash->Find(MODEL_PATH_FIELD);
  if (!model_path_field || !model_path_field->GetAsBasicString(&model_path_str)) {
    return common::Optional<MachineLearning>();
  }
  res.SetModelPath(common::uri::GURL(model_path_str));

  bool tracking;
  common::Value* tracking_field = hash->Find(TRACKING_FIELD);
  if (!tracking_field || !tracking_field->GetAsBoolean(&tracking)) {
    return common::Optional<MachineLearning>();
  }
  res.SetNeedTracking(tracking);

  bool dump;
  common::Value* dump_field = hash->Find(DUMP_FIELD);
  if (!dump_field || !dump_field->GetAsBoolean(&dump)) {
    return common::Optional<MachineLearning>();
  }
  res.SetNeedDump(dump);

  int64_t clid;
  common::Value* clid_field = hash->Find(CLASS_ID_FIELD);
  if (!clid_field || !clid_field->GetAsLongInteger(&clid)) {
    return common::Optional<MachineLearning>();
  }
  res.SetClassID(clid);

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

  std::string model_path;
  err = GetStringField(serialized, MODEL_PATH_FIELD, &model_path);
  if (err) {
    return err;
  }

  MachineLearning lresult(backend, common::uri::GURL(model_path));
  bool tracking;
  err = GetBoolField(serialized, TRACKING_FIELD, &tracking);
  if (err) {
    return err;
  }
  lresult.SetNeedTracking(tracking);

  bool dump;
  err = GetBoolField(serialized, DUMP_FIELD, &dump);
  if (err) {
    return err;
  }
  lresult.SetNeedDump(dump);

  int clid;
  err = GetIntField(serialized, CLASS_ID_FIELD, &clid);
  if (err) {
    return err;
  }
  lresult.SetClassID(clid);

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
  const std::string model_path_str = model_path_.spec();
  ignore_result(SetStringField(out, MODEL_PATH_FIELD, model_path_str));
  ignore_result(SetBoolField(out, TRACKING_FIELD, tracking_));
  ignore_result(SetBoolField(out, DUMP_FIELD, dump_));
  ignore_result(SetIntField(out, CLASS_ID_FIELD, class_id_));
  ignore_result(SetBoolField(out, OVERLAY_FIELD, overlay_));
  return common::Error();
}

}  // namespace ml
}  // namespace fastotv

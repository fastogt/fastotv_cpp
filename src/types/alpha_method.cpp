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

#include <common/sprintf.h>
#include <fastotv/types/alpha_method.h>

#define METHOD_FIELD "method"
#define COLOR_FIELD "color"
#define ALPHA_FIELD "alpha"

namespace fastotv {

AlphaMethod::AlphaMethod(method_t method) : method_(method), alpha_(), color_() {}

AlphaMethod AlphaMethod::MakeBlue() {
  auto result = AlphaMethod(BLUE);
  return result;
}

AlphaMethod AlphaMethod::MakeGreen() {
  auto result = AlphaMethod(GREEN);
  return result;
}

AlphaMethod AlphaMethod::MakeCustom(const color_t& color) {
  auto result = AlphaMethod(CUSTOM);
  result.color_ = color;
  return result;
}

bool AlphaMethod::Equals(const AlphaMethod& back) const {
  return back.method_ == method_ && color_ == color_;
}

AlphaMehodType AlphaMethod::GetMethod() const {
  return method_;
}

const AlphaMethod::color_t& AlphaMethod::GetColor() const {
  return color_;
}

const AlphaMethod::alpha_t& AlphaMethod::GetAlpha() const {
  return alpha_;
}

void AlphaMethod::SetAlpha(const alpha_t& alpha) {
  alpha_ = alpha;
}

common::Optional<AlphaMethod> AlphaMethod::Make(common::HashValue* hash) {
  if (!hash) {
    return common::Optional<AlphaMethod>();
  }

  common::Value* method_field = hash->Find(METHOD_FIELD);
  int64_t method;
  if (!method_field || !method_field->GetAsInteger64(&method)) {
    return common::Optional<AlphaMethod>();
  }

  alpha_t alpha;
  double alp;
  common::Value* alpha_field = hash->Find(ALPHA_FIELD);
  if (alpha_field && alpha_field->GetAsDouble(&alp)) {
    alpha = alp;
  }

  if (method == CUSTOM) {
    int64_t color;
    common::Value* color_field = hash->Find(COLOR_FIELD);
    if (!color_field || !color_field->GetAsInteger64(&color)) {
      return common::Optional<AlphaMethod>();
    }
    auto res = MakeCustom(color);
    res.SetAlpha(alpha);
    return res;
  }
  auto res = AlphaMethod(static_cast<method_t>(method));
  res.SetAlpha(alpha);
  return res;
}

common::Error AlphaMethod::DoDeSerialize(json_object* serialized) {
  method_t method;
  common::Error err = GetEnumField(serialized, METHOD_FIELD, &method);
  if (err) {
    return err;
  }

  alpha_t alpha;
  double alp;
  err = GetDoubleField(serialized, ALPHA_FIELD, &alp);
  if (!err) {
    alpha = alp;
  }

  if (method == CUSTOM) {
    int64_t color;
    err = GetInt64Field(serialized, COLOR_FIELD, &color);
    if (err) {
      return err;
    }
    auto res = MakeCustom(color);
    res.SetAlpha(alpha);
    *this = res;
    return common::Error();
  }

  auto res = AlphaMethod(static_cast<method_t>(method));
  res.SetAlpha(alpha);
  *this = res;
  return common::Error();
}

common::Error AlphaMethod::SerializeFields(json_object* out) const {
  ignore_result(SetIntField(out, METHOD_FIELD, method_));
  if (color_) {
    ignore_result(SetInt64Field(out, COLOR_FIELD, *color_));
  }
  if (alpha_) {
    ignore_result(SetEnumField(out, ALPHA_FIELD, *alpha_));
  }
  return common::Error();
}

}  // namespace fastotv

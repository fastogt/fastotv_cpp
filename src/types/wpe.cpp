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

#include <fastotv/types/overlay_url.h>

#define GL_FIELD "gl"

namespace fastotv {

Wpe::Wpe() : gl_() {}

Wpe::Wpe(gl_t gl) : gl_(gl) {}

void Wpe::SetGL(gl_t gl) {
  gl_ = gl;
}

Wpe::gl_t Wpe::GetGL() const {
  return gl_;
}

bool Wpe::Equals(const Wpe& inf) const {
  return gl_ == inf.gl_;
}

common::Optional<Wpe> Wpe::Make(common::HashValue* hash) {
  if (!hash) {
    return common::Optional<Wpe>();
  }

  common::Value* gl_field = hash->Find(GL_FIELD);
  bool gl;
  if (!gl_field || !gl_field->GetAsBoolean(&gl)) {
    return common::Optional<Wpe>();
  }
  return Wpe(gl);
}

common::Error Wpe::DoDeSerialize(json_object* serialized) {
  bool gl;
  common::Error err = GetBoolField(serialized, GL_FIELD, &gl);
  if (err) {
    return err;
  }

  *this = Wpe(gl);
  return common::Error();
}

common::Error Wpe::SerializeFields(json_object* out) const {
  ignore_result(SetBoolField(out, GL_FIELD, gl_));
  return common::Error();
}

}  // namespace fastotv

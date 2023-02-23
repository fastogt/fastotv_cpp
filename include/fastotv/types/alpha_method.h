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

#pragma once

#include <common/serializer/json_serializer.h>
#include <common/value.h>

#include <string>

namespace fastotv {

enum AlphaMehodType { SET = 0, GREEN, BLUE, CUSTOM };

class AlphaMethod : public common::serializer::JsonSerializer<AlphaMethod> {
 public:
  typedef common::serializer::JsonSerializer<AlphaMethod> base_class;
  typedef AlphaMehodType method_t;
  typedef common::Optional<unsigned int> color_t;
  typedef common::Optional<double> alpha_t;

  static AlphaMethod MakeBlue();
  static AlphaMethod MakeGreen();
  static AlphaMethod MakeCustom(const color_t& color);

  bool Equals(const AlphaMethod& meth) const;

  method_t GetMethod() const;
  const color_t& GetColor() const;
  const alpha_t& GetAlpha() const;
  void SetAlpha(const alpha_t& alpha);

  static common::Optional<AlphaMethod> Make(common::HashValue* hash);

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* out) const override;

 private:
  explicit AlphaMethod(method_t type);

  method_t method_;
  alpha_t alpha_;
  color_t color_;
};

}  // namespace fastotv

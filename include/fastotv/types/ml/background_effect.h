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
#include <common/value.h>

namespace fastotv {
namespace ml {

enum BackgroundEffectType { BLUR = 0, IMAGE, COLOR };

class BackgroundEffect : public common::serializer::JsonSerializer<BackgroundEffect> {
 public:
  typedef common::serializer::JsonSerializer<BackgroundEffect> base_class;
  typedef common::Optional<double> blur_strength_t;
  typedef common::Optional<std::string> image_path_t;
  typedef common::Optional<int> color_t;

  static BackgroundEffect MakeBlurEffect(blur_strength_t blur);        // for blur type
  static BackgroundEffect MakeImageEffect(const image_path_t& image);  // for image type
  static BackgroundEffect MakeColorEffect(const color_t& color);       // for color type

  ~BackgroundEffect() override;

  bool Equals(const BackgroundEffect& back) const;

  BackgroundEffectType GetType() const;
  blur_strength_t GetBlurStrength() const;
  image_path_t GetImagePath() const;
  color_t GetColor() const;

  static common::Optional<BackgroundEffect> Make(common::HashValue* hash);

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* out) const override;

 private:
  BackgroundEffect(BackgroundEffectType type);

  BackgroundEffectType type_;

  // should be union but not trivial types
  blur_strength_t blur_;
  image_path_t image_;
  color_t color_;
};

}  // namespace ml
}  // namespace fastotv

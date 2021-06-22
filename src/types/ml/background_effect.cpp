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

#include <fastotv/types/ml/background_effect.h>

#include <common/sprintf.h>

#define TYPE_FIELD "type"
#define STRENGTH_FIELD "strength"
#define IMAGE_FIELD "image"
#define COLOR_FIELD "color"

namespace fastotv {
namespace ml {

BackgroundEffect::BackgroundEffect(BackgroundEffectType type) : type_(type), blur_(), image_(), color_() {}

BackgroundEffect BackgroundEffect::MakeBlurEffect(blur_strength_t blur) {
  auto result = BackgroundEffect(BLUR);
  result.blur_ = blur;
  return result;
}

BackgroundEffect BackgroundEffect::MakeImageEffect(const image_path_t& image) {
  auto result = BackgroundEffect(IMAGE);
  result.image_ = image;
  return result;
}

BackgroundEffect BackgroundEffect::MakeColorEffect(const color_t& color) {
  auto result = BackgroundEffect(COLOR);
  result.color_ = color;
  return result;
}

bool BackgroundEffect::Equals(const BackgroundEffect& back) const {
  return back.type_ == type_;
}

BackgroundEffectType BackgroundEffect::GetType() const {
  return type_;
}

BackgroundEffect::blur_strength_t BackgroundEffect::GetBlurStrength() const {
  return blur_;
}

BackgroundEffect::image_path_t BackgroundEffect::GetImagePath() const {
  return image_;
}

BackgroundEffect::color_t BackgroundEffect::GetColor() const {
  return color_;
}

common::Optional<BackgroundEffect> BackgroundEffect::Make(common::HashValue* hash) {
  if (!hash) {
    return common::Optional<BackgroundEffect>();
  }

  common::Value* type_field = hash->Find(TYPE_FIELD);
  int type;
  if (!type_field || !type_field->GetAsInteger(&type)) {
    return common::Optional<BackgroundEffect>();
  }

  if (type == BLUR) {
    double blur;
    common::Value* strength_field = hash->Find(STRENGTH_FIELD);
    if (!strength_field || !strength_field->GetAsDouble(&blur)) {
      return common::Optional<BackgroundEffect>();
    }
    return MakeBlurEffect(blur);
  } else if (type == IMAGE) {
    std::string path;
    common::Value* path_field = hash->Find(IMAGE_FIELD);
    if (!path_field || !path_field->GetAsBasicString(&path)) {
      return common::Optional<BackgroundEffect>();
    }
    return MakeImageEffect(path);
  } else if (type == COLOR) {
    int color;
    common::Value* color_field = hash->Find(COLOR_FIELD);
    if (!color_field || !color_field->GetAsInteger(&color)) {
      return common::Optional<BackgroundEffect>();
    }
    return MakeColorEffect(color);
  }
  return common::Optional<BackgroundEffect>();
}

common::Error BackgroundEffect::DoDeSerialize(json_object* serialized) {
  BackgroundEffectType type;
  common::Error err = GetEnumField(serialized, TYPE_FIELD, &type);
  if (err) {
    return err;
  }

  if (type == BLUR) {
    double blur;
    err = GetDoubleField(serialized, STRENGTH_FIELD, &blur);
    if (err) {
      return err;
    }
    *this = MakeBlurEffect(blur);
    return common::Error();
  } else if (type == IMAGE) {
    std::string image;
    err = GetStringField(serialized, IMAGE_FIELD, &image);
    if (err) {
      return err;
    }
    *this = MakeImageEffect(image);
    return common::Error();
  } else if (type == COLOR) {
    int color;
    err = GetIntField(serialized, COLOR_FIELD, &color);
    if (err) {
      return err;
    }
    *this = MakeColorEffect(color);
    return common::Error();
  }

  return common::make_error(common::MemSPrintf("unknown type: %d", type));
}

common::Error BackgroundEffect::SerializeFields(json_object* out) const {
  ignore_result(SetIntField(out, TYPE_FIELD, type_));
  if (blur_) {
    ignore_result(SetDoubleField(out, STRENGTH_FIELD, *blur_));
  }
  if (image_) {
    ignore_result(SetStringField(out, IMAGE_FIELD, *image_));
  }
  if (color_) {
    ignore_result(SetIntField(out, COLOR_FIELD, *color_));
  }
  return common::Error();
}

}  // namespace ml
}  // namespace fastotv

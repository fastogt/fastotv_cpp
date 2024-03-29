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

#include <common/serializer/json_serializer.h>
#include <fastotv/types/utils.h>

#define WIDTH_FIELD "width"
#define HEIGHT_FIELD "height"

#define POSITION_X_FIELD "x"
#define POSITION_Y_FIELD "y"

#define NUM_FIELD "num"
#define DEN_FIELD "den"

namespace fastotv {

json_object* MakeJson(const common::draw::Size& size) {
  json_object* result = json_object_new_object();
  json_object_object_add(result, WIDTH_FIELD, json_object_new_int(size.width()));
  json_object_object_add(result, HEIGHT_FIELD, json_object_new_int(size.height()));
  return result;
}

json_object* MakeJson(const common::draw::Point& point) {
  json_object* result = json_object_new_object();
  json_object_object_add(result, POSITION_X_FIELD, json_object_new_int(point.x()));
  json_object_object_add(result, POSITION_Y_FIELD, json_object_new_int(point.y()));
  return result;
}

json_object* MakeJson(const common::media::Rational& rat) {
  json_object* result = json_object_new_object();
  json_object_object_add(result, NUM_FIELD, json_object_new_int(rat.num));
  json_object_object_add(result, DEN_FIELD, json_object_new_int(rat.den));
  return result;
}

common::Optional<common::draw::Size> MakeSize(common::HashValue* value) {
  if (!value) {
    return common::Optional<common::draw::Size>();
  }

  common::Value* width_field = value->Find(WIDTH_FIELD);
  common::Value* height_field = value->Find(HEIGHT_FIELD);
  int64_t width = 0;
  int64_t height = 0;
  if (width_field && width_field->GetAsInteger64(&width) && height_field && height_field->GetAsInteger64(&height)) {
    return common::draw::Size(width, height);
  }

  return common::Optional<common::draw::Size>();
}

common::Optional<common::draw::Point> MakePoint(common::HashValue* value) {
  if (!value) {
    return common::Optional<common::draw::Point>();
  }

  common::Value* x_field = value->Find(POSITION_X_FIELD);
  common::Value* y_field = value->Find(POSITION_Y_FIELD);
  int64_t x = 0;
  int64_t y = 0;
  if (x_field && x_field->GetAsInteger64(&x) && y_field && y_field->GetAsInteger64(&y)) {
    return common::draw::Point(x, y);
  }

  return common::Optional<common::draw::Point>();
}

common::Optional<common::media::Rational> MakeRational(common::HashValue* value) {
  if (!value) {
    return common::Optional<common::media::Rational>();
  }

  common::Value* num_field = value->Find(NUM_FIELD);
  common::Value* den_field = value->Find(DEN_FIELD);
  int64_t num = 0;
  int64_t den = 0;
  if (num_field && num_field->GetAsInteger64(&num) && den_field && den_field->GetAsInteger64(&den)) {
    return common::media::Rational{static_cast<int>(num), static_cast<int>(den)};
  }

  return common::Optional<common::media::Rational>();
}

common::Optional<common::draw::Size> MakeSize(json_object* serialized) {
  if (!serialized) {
    return common::Optional<common::draw::Size>();
  }

  int width;
  common::Error err = common::serializer::json_get_int(serialized, WIDTH_FIELD, &width);
  if (err) {
    return common::Optional<common::draw::Size>();
  }

  int height;
  err = common::serializer::json_get_int(serialized, HEIGHT_FIELD, &height);
  if (err) {
    return common::Optional<common::draw::Size>();
  }

  return common::draw::Size(width, height);
}

common::Optional<common::draw::Point> MakePoint(json_object* serialized) {
  if (!serialized) {
    return common::Optional<common::draw::Point>();
  }

  int x;
  common::Error err = common::serializer::json_get_int(serialized, POSITION_X_FIELD, &x);
  if (err) {
    return common::Optional<common::draw::Point>();
  }

  int y;
  err = common::serializer::json_get_int(serialized, POSITION_Y_FIELD, &y);
  if (err) {
    return common::Optional<common::draw::Point>();
  }

  return common::draw::Point(x, y);
}

common::Optional<common::media::Rational> MakeRational(json_object* serialized) {
  if (!serialized) {
    return common::Optional<common::media::Rational>();
  }

  int num;
  common::Error err = common::serializer::json_get_int(serialized, NUM_FIELD, &num);
  if (err) {
    return common::Optional<common::media::Rational>();
  }

  int den;
  err = common::serializer::json_get_int(serialized, DEN_FIELD, &den);
  if (err) {
    return common::Optional<common::media::Rational>();
  }

  return common::media::Rational{static_cast<int>(num), static_cast<int>(den)};
}

}  // namespace fastotv

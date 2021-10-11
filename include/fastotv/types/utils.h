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

#include <common/draw/point.h>
#include <common/draw/size.h>
#include <common/optional.h>
#include <common/value.h>

struct json_object;

namespace fastotv {

json_object* MakeJson(const common::draw::Size& size);
json_object* MakeJson(const common::draw::Point& point);

common::Optional<common::draw::Size> MakeSize(common::HashValue* value);
common::Optional<common::draw::Point> MakePoint(common::HashValue* value);

common::Optional<common::draw::Size> MakeSize(json_object* serialized);
common::Optional<common::draw::Point> MakePoint(json_object* serialized);

}  // namespace fastotv

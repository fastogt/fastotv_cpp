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

#include <common/draw/point.h>
#include <common/draw/size.h>
#include <common/serializer/json_serializer.h>
#include <common/uri/gurl.h>
#include <common/value.h>

#include <string>

namespace fastotv {

class Logo : public common::serializer::JsonSerializer<Logo> {
 public:
  typedef double alpha_t;
  typedef common::uri::GURL url_t;
  typedef common::Optional<common::draw::Size> image_size_t;

  Logo();
  Logo(const url_t& path, const common::draw::Point& position, alpha_t alpha);

  bool Equals(const Logo& logo) const;

  url_t GetPath() const;
  void SetPath(const url_t& path);

  common::draw::Point GetPosition() const;
  void SetPosition(const common::draw::Point& position);

  image_size_t GetSize() const;
  void SetSize(const image_size_t& size);

  alpha_t GetAlpha() const;
  void SetAlpha(alpha_t alpha);

  static common::Optional<Logo> Make(common::HashValue* value);

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* out) const override;

 private:
  url_t path_;
  common::draw::Point position_;
  image_size_t size_;
  alpha_t alpha_;
};

}  // namespace fastotv

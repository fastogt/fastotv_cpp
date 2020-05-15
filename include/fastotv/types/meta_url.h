/*  Copyright (C) 2014-2020 FastoGT. All right reserved.
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
#include <common/uri/gurl.h>

namespace fastotv {

class MetaUrl : public common::serializer::JsonSerializer<MetaUrl> {
 public:
  typedef JsonSerializer<MetaUrl> base_class;
  typedef std::string name_t;
  typedef common::uri::GURL url_t;

  MetaUrl();
  explicit MetaUrl(const name_t& name, const url_t& url);

  bool IsValid() const;

  name_t GetName() const;
  void SetName(const name_t& name);

  url_t GetUrl() const;
  void SetUrl(const url_t& uri);

  bool Equals(const MetaUrl& inf) const;

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* out) const override;

 private:
  // required
  name_t name_;
  url_t url_;
};

typedef common::serializer::JsonSerializerArray<MetaUrl> MetaUrls;

}  // namespace fastotv

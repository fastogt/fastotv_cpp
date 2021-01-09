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

#include <fastotv/types/meta_url.h>

#define NAME_FIELD "name"
#define URL_FIELD "url"

namespace fastotv {

MetaUrl::MetaUrl() : MetaUrl(name_t(), url_t()) {}

MetaUrl::MetaUrl(const name_t& name, const url_t& url) : base_class(), name_(name), url_(url) {}

bool MetaUrl::IsValid() const {
  return url_.is_valid() && !name_.empty();
}

MetaUrl::name_t MetaUrl::GetName() const {
  return name_;
}

void MetaUrl::SetName(const name_t& name) {
  name_ = name;
}

MetaUrl::url_t MetaUrl::GetUrl() const {
  return url_;
}

void MetaUrl::SetUrl(const url_t& uri) {
  url_ = uri;
}

bool MetaUrl::Equals(const MetaUrl& inf) const {
  return name_ == inf.name_ && url_ == inf.url_;
}

common::Error MetaUrl::DoDeSerialize(json_object* serialized) {
  std::string uri;
  common::Error err = GetStringField(serialized, URL_FIELD, &uri);
  if (err) {
    return err;
  }

  std::string name;
  err = GetStringField(serialized, NAME_FIELD, &name);
  if (err) {
    return err;
  }

  *this = MetaUrl(name, url_t(uri));
  return common::Error();
}

common::Error MetaUrl::SerializeFields(json_object* out) const {
  if (!IsValid()) {
    return common::make_error_inval();
  }

  ignore_result(SetStringField(out, NAME_FIELD, name_));
  const std::string url_str = url_.spec();
  ignore_result(SetStringField(out, URL_FIELD, url_str));
  return common::Error();
}

}  // namespace fastotv

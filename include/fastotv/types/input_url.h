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

#pragma once

#include <string>

#include <common/serializer/json_serializer.h>
#include <common/uri/gurl.h>
#include <common/value.h>

#include <fastotv/types.h>

namespace fastotv {

class InputUrl : public common::serializer::JsonSerializer<InputUrl> {
 public:
  typedef JsonSerializer<InputUrl> base_class;
  typedef fastotv::channel_id_t uri_id_t;
  typedef common::uri::GURL url_t;

  InputUrl();
  explicit InputUrl(uri_id_t id, const url_t& input);

  bool IsValid() const;

  uri_id_t GetID() const;
  void SetID(uri_id_t id);

  url_t GetUrl() const;
  void SetUrl(const url_t& uri);

  bool Equals(const InputUrl& inf) const;

  static common::Optional<InputUrl> Make(common::HashValue* hash);

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* out) const override;

 private:
  // required
  uri_id_t id_;
  url_t url_;
};

inline bool operator==(const InputUrl& left, const InputUrl& right) {
  return left.Equals(right);
}

inline bool operator!=(const InputUrl& x, const InputUrl& y) {
  return !(x == y);
}

}  // namespace fastotv

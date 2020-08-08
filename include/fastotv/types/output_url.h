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

#include <common/serializer/json_serializer.h>
#include <common/uri/gurl.h>
#include <common/value.h>

#include <fastotv/types.h>

namespace fastotv {

class OutputUrl : public common::serializer::JsonSerializer<OutputUrl> {
 public:
  typedef JsonSerializer<OutputUrl> base_class;
  typedef fastotv::channel_id_t uri_id_t;
  typedef common::uri::GURL url_t;

  OutputUrl();
  explicit OutputUrl(uri_id_t id, const url_t& url);

  bool IsValid() const;

  uri_id_t GetID() const;
  void SetID(uri_id_t id);

  url_t GetUrl() const;
  void SetUrl(const url_t& uri);

  bool Equals(const OutputUrl& inf) const;

  static common::Optional<OutputUrl> Make(common::HashValue* hash);

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* out) const override;

 private:
  // required
  uri_id_t id_;
  url_t url_;
};

}  // namespace fastotv

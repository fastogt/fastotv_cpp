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
#include <fastotv/types/cef.h>
#include <fastotv/types/wpe.h>

namespace fastotv {

enum OverlayUrlType { URL, WPE, CEF };

class OverlayUrl : public common::serializer::JsonSerializer<OverlayUrl> {
 public:
  typedef JsonSerializer<OverlayUrl> base_class;
  typedef common::uri::GURL url_t;
  typedef common::Optional<Wpe> wpe_t;
  typedef common::Optional<Cef> cef_t;

  OverlayUrl();

  bool IsValid() const;

  url_t GetUrl() const;
  void SetUrl(const url_t& uri);

  wpe_t GetWPE() const;
  cef_t GetCEF() const;
  OverlayUrlType GetType() const;

  bool Equals(const OverlayUrl& inf) const;

  static OverlayUrl MakeOverlayUrl(const url_t& url);
  static OverlayUrl MakeWpeOverlayUrl(const url_t& url, const Wpe& wpe);
  static OverlayUrl MakeCefOverlayUrl(const url_t& url, const Cef& cef);

  static common::Optional<OverlayUrl> Make(common::HashValue* hash);

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* out) const override;

 private:
  OverlayUrl(const url_t& url, OverlayUrlType type);

  // required
  url_t url_;
  OverlayUrlType type_;

  wpe_t wpe_;
  cef_t cef_;
};

inline bool operator==(const OverlayUrl& left, const OverlayUrl& right) {
  return left.Equals(right);
}

inline bool operator!=(const OverlayUrl& x, const OverlayUrl& y) {
  return !(x == y);
}

}  // namespace fastotv

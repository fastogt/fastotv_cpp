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

#include <fastotv/types/overlay_url.h>

#include <common/sprintf.h>

#define GPU_FIELD "gpu"
//
#define TYPE_FIELD "type"
#define URL_FIELD "url"
#define WPE_FIELD "wpe"
#define CEF_FIELD "cef"

namespace fastotv {

Cef::Cef() : gpu_() {}

Cef::Cef(gpu_t gpu) : gpu_(gpu) {}

void Cef::SetGL(gpu_t gpu) {
  gpu_ = gpu;
}

Cef::gpu_t Cef::GetGPU() const {
  return gpu_;
}

common::Optional<Cef> Cef::Make(common::HashValue* hash) {
  if (!hash) {
    return common::Optional<Cef>();
  }

  common::Value* gpu_field = hash->Find(GPU_FIELD);
  bool gpu;
  if (!gpu_field || !gpu_field->GetAsBoolean(&gpu)) {
    return common::Optional<Cef>();
  }
  return Cef(gpu);
}

common::Error Cef::DoDeSerialize(json_object* serialized) {
  bool gpu;
  common::Error err = GetBoolField(serialized, GPU_FIELD, &gpu);
  if (err) {
    return err;
  }

  *this = Cef(gpu);
  return common::Error();
}

common::Error Cef::SerializeFields(json_object* out) const {
  ignore_result(SetBoolField(out, GPU_FIELD, gpu_));
  return common::Error();
}

OverlayUrl::OverlayUrl(const url_t& input, OverlayUrlType type) : base_class(), url_(input), type_(type) {}

OverlayUrl::OverlayUrl() {}

bool OverlayUrl::IsValid() const {
  return url_.is_valid();
}

OverlayUrl::url_t OverlayUrl::GetUrl() const {
  return url_;
}

void OverlayUrl::SetUrl(const url_t& uri) {
  url_ = uri;
}

bool OverlayUrl::Equals(const OverlayUrl& inf) const {
  return url_ == inf.url_;
}

OverlayUrl OverlayUrl::MakeOverlayUrl(const url_t& url) {
  return OverlayUrl(url, URL);
}

OverlayUrl::wpe_t OverlayUrl::GetWPE() const {
  return wpe_;
}

OverlayUrl::cef_t OverlayUrl::GetCEF() const {
  return cef_;
}

OverlayUrlType OverlayUrl::GetType() const {
  return type_;
}

OverlayUrl OverlayUrl::MakeWpeOverlayUrl(const url_t& url, const Wpe& wpe) {
  auto result = OverlayUrl(url, WPE);
  result.wpe_ = wpe;
  return result;
}

OverlayUrl OverlayUrl::MakeCefOverlayUrl(const url_t& url, const Cef& cef) {
  auto result = OverlayUrl(url, CEF);
  result.cef_ = cef;
  return result;
}

common::Optional<OverlayUrl> OverlayUrl::Make(common::HashValue* hash) {
  if (!hash) {
    return common::Optional<OverlayUrl>();
  }

  common::Value* type_field = hash->Find(TYPE_FIELD);
  int64_t type;
  if (!type_field || !type_field->GetAsInteger64(&type)) {
    return common::Optional<OverlayUrl>();
  }

  std::string url_str;
  common::Value* url_str_field = hash->Find(URL_FIELD);
  if (!url_str_field || !url_str_field->GetAsBasicString(&url_str)) {
    return common::Optional<OverlayUrl>();
  }

  url_t uri(url_str);
  if (!uri.is_valid()) {
    return common::Optional<OverlayUrl>();
  }

  if (type == URL) {
    return MakeOverlayUrl(uri);
  } else if (type == WPE) {
    common::HashValue* wpe;
    common::Value* wpe_field = hash->Find(WPE_FIELD);
    if (wpe_field && wpe_field->GetAsHash(&wpe)) {
      auto wp = Wpe::Make(wpe);
      if (wp) {
        return MakeWpeOverlayUrl(uri, *wp);
      }
    }

    return common::Optional<OverlayUrl>();
  } else if (type == CEF) {
    common::HashValue* cef;
    common::Value* cef_field = hash->Find(CEF_FIELD);
    if (cef_field && cef_field->GetAsHash(&cef)) {
      auto cf = Cef::Make(cef);
      if (cf) {
        return MakeCefOverlayUrl(uri, *cf);
      }
    }

    return common::Optional<OverlayUrl>();
  }

  return common::Optional<OverlayUrl>();
}

common::Error OverlayUrl::DoDeSerialize(json_object* serialized) {
  std::string url_str;
  common::Error err = GetStringField(serialized, URL_FIELD, &url_str);
  if (err) {
    return err;
  }

  OverlayUrlType type;
  err = GetEnumField(serialized, TYPE_FIELD, &type);
  if (err) {
    return err;
  }

  url_t uri(url_str);
  if (!uri.is_valid()) {
    return common::make_error_inval();
  }

  if (type == URL) {
    *this = MakeOverlayUrl(uri);
    return common::Error();
  } else if (type == WPE) {
    json_object* wpe = nullptr;
    err = GetObjectField(serialized, WPE_FIELD, &wpe);
    if (err) {
      return err;
    }

    Wpe wp;
    err = wp.DeSerialize(wpe);
    if (err) {
      return err;
    }
    *this = MakeWpeOverlayUrl(uri, wp);
    return common::Error();
  } else if (type == CEF) {
    json_object* cef = nullptr;
    err = GetObjectField(serialized, CEF_FIELD, &cef);
    if (err) {
      return err;
    }

    Cef wp;
    err = wp.DeSerialize(cef);
    if (err) {
      return err;
    }
    *this = MakeCefOverlayUrl(uri, wp);
    return common::Error();
  }

  return common::make_error(common::MemSPrintf("unknown type: %d", type));
}

common::Error OverlayUrl::SerializeFields(json_object* out) const {
  if (!IsValid()) {
    return common::make_error_inval();
  }

  const std::string url_str = url_.spec();
  ignore_result(SetStringField(out, URL_FIELD, url_str));
  NOTREACHED() << "Not implemented";
  return common::Error();
}

}  // namespace fastotv

/*  Copyright (C) 2014-2021 FastoGT. All right reserved.

    This file is part of FastoTV.

    FastoTV is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    FastoTV is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FastoTV. If not, see <http://www.gnu.org/licenses/>.
*/

#include <fastotv/commands_info/movie_info.h>

#define URLS_FIELD "urls"
#define DESCRIPTION_FIELD "description"
#define PREVIEW_ICON_FIELD "preview_icon"
#define BACKGROUND_URL_FIELD "backgorund_url"
#define NAME_FIELD "display_name"
#define TRAILER_URL_FIELD "trailer_url"
#define USER_SCORE_FIELD "user_score"
#define PRIME_DATE_FIELD "prime_date"
#define COUNTRY_FIELD "country"
#define DURATION_FIELD "duration"
#define TYPE_FIELD "type"

namespace fastotv {
namespace commands_info {

MovieInfo::MovieInfo()
    : display_name_(),
      urls_(),
      description_(),
      preview_icon_(),
      background_url_(),
      trailer_url_(),
      user_score_(),
      prime_date_(),
      country_(),
      duration_(),
      type_(VODS) {}

MovieInfo::MovieInfo(const std::string& name,
                     const urls_t& urls,
                     const std::string& description,
                     const url_t& preview_icon,
                     const optional_url_t& background_url,
                     const optional_url_t& trailer_url,
                     double user_score,
                     timestamp_t prime_date,
                     const std::string& country,
                     timestamp_t duration,
                     Type type)
    : display_name_(name),
      urls_(urls),
      description_(description),
      preview_icon_(preview_icon),
      background_url_(background_url),
      trailer_url_(trailer_url),
      user_score_(user_score),
      prime_date_(prime_date),
      country_(country),
      duration_(duration),
      type_(type) {}

bool MovieInfo::IsValid() const {
  return !urls_.empty() && !display_name_.empty();
}

bool MovieInfo::IsSerial() const {
  return type_ == SERIES;
}

void MovieInfo::SetUrls(const urls_t& urls) {
  urls_ = urls;
}

MovieInfo::urls_t MovieInfo::GetUrls() const {
  return urls_;
}

void MovieInfo::SetName(const std::string& name) {
  display_name_ = name;
}

std::string MovieInfo::GetName() const {
  return display_name_;
}

void MovieInfo::SetDescription(const std::string& descr) {
  description_ = descr;
}

std::string MovieInfo::GetDescription() const {
  return description_;
}

void MovieInfo::SetPreviewIcon(const url_t& url) {
  preview_icon_ = url;
}

fastotv::commands_info::MovieInfo::url_t MovieInfo::GetPreviewIcon() const {
  return preview_icon_;
}

void MovieInfo::SetBackgroundUrl(const optional_url_t& url) {
  background_url_ = url;
}

MovieInfo::optional_url_t MovieInfo::GetBackgroundUrl() const {
  return background_url_;
}

void MovieInfo::SetTrailerUrl(const fastotv::commands_info::MovieInfo::optional_url_t& url) {
  trailer_url_ = url;
}

fastotv::commands_info::MovieInfo::optional_url_t MovieInfo::GetTrailerUrl() const {
  return trailer_url_;
}

void MovieInfo::SetUserScore(double score) {
  user_score_ = score;
}

double MovieInfo::GetUserScore() const {
  return user_score_;
}

void MovieInfo::SetPrimeDate(timestamp_t date) {
  prime_date_ = date;
}

timestamp_t MovieInfo::GetPrimeDate() const {
  return prime_date_;
}

void MovieInfo::SetCountry(const std::string& country) {
  country_ = country;
}

const std::string& MovieInfo::GetCountry() const {
  return country_;
}

void MovieInfo::SetDuration(timestamp_t dur) {
  duration_ = dur;
}

timestamp_t MovieInfo::GetDuration() const {
  return duration_;
}

MovieInfo::Type MovieInfo::GetType() const {
  return type_;
}

void MovieInfo::SetType(Type type) {
  type_ = type;
}

common::Error MovieInfo::SerializeFields(json_object* deserialized) const {
  if (!IsValid()) {
    return common::make_error_inval();
  }

  ignore_result(SetStringField(deserialized, NAME_FIELD, display_name_));
  ignore_result(SetStringField(deserialized, DESCRIPTION_FIELD, description_));
  const std::string icon_url_str = preview_icon_.spec();
  ignore_result(SetStringField(deserialized, PREVIEW_ICON_FIELD, icon_url_str));

  if (background_url_) {
    const std::string back_icon_url_str = background_url_->spec();
    ignore_result(SetStringField(deserialized, BACKGROUND_URL_FIELD, back_icon_url_str));
  }

  if (trailer_url_) {
    const std::string trailer_url_str = trailer_url_->spec();
    ignore_result(SetStringField(deserialized, TRAILER_URL_FIELD, trailer_url_str));
  }
  ignore_result(SetDoubleField(deserialized, USER_SCORE_FIELD, user_score_));
  ignore_result(SetInt64Field(deserialized, PRIME_DATE_FIELD, prime_date_));
  ignore_result(SetStringField(deserialized, COUNTRY_FIELD, country_));
  ignore_result(SetInt64Field(deserialized, DURATION_FIELD, duration_));

  json_object* jurls = json_object_new_array();
  for (auto url : urls_) {
    std::string url_str = url.spec();
    json_object* jurl = json_object_new_string(url_str.c_str());
    json_object_array_add(jurls, jurl);
  }
  ignore_result(SetArrayField(deserialized, URLS_FIELD, jurls));
  ignore_result(SetEnumField(deserialized, TYPE_FIELD, type_));
  return common::Error();
}

common::Error MovieInfo::DoDeSerialize(json_object* serialized) {
  json_object* jurls;
  size_t len;
  common::Error err = GetArrayField(serialized, URLS_FIELD, &jurls, &len);
  if (err) {
    return err;
  }

  MovieInfo res;
  urls_t urls;
  for (size_t i = 0; i < len; ++i) {
    json_object* jurl = json_object_array_get_idx(jurls, i);
    const std::string url_str = json_object_get_string(jurl);
    urls.push_back(url_t(url_str));
  }
  res.SetUrls(urls);

  std::string name;
  err = GetStringField(serialized, NAME_FIELD, &name);
  if (err) {
    return err;
  }
  res.SetName(name);

  // optional
  std::string description;
  if (GetStringField(serialized, DESCRIPTION_FIELD, &description)) {
    res.SetDescription(description);
  }

  std::string preview_icon;
  if (GetStringField(serialized, PREVIEW_ICON_FIELD, &preview_icon)) {
    res.SetPreviewIcon(url_t(preview_icon));
  }

  std::string back_url;
  if (GetStringField(serialized, BACKGROUND_URL_FIELD, &back_url)) {
    res.SetBackgroundUrl(url_t(back_url));
  }

  std::string trailer_url;
  if (GetStringField(serialized, TRAILER_URL_FIELD, &trailer_url)) {
    res.SetTrailerUrl(url_t(trailer_url));
  }

  double user_score = 0;
  if (GetDoubleField(serialized, USER_SCORE_FIELD, &user_score)) {
    res.SetUserScore(user_score);
  }

  timestamp_t prime_date = 0;
  if (GetInt64Field(serialized, PRIME_DATE_FIELD, &prime_date)) {
    res.SetPrimeDate(prime_date);
  }

  std::string country;
  if (GetStringField(serialized, COUNTRY_FIELD, &country)) {
    res.SetCountry(country);
  }

  timestamp_t duration = 0;
  if (GetInt64Field(serialized, DURATION_FIELD, &prime_date)) {
    res.SetDuration(duration);
  }

  Type type = VODS;
  if (GetEnumField(serialized, TYPE_FIELD, &type)) {
    res.SetType(type);
  }

  *this = res;
  return common::Error();
}

bool MovieInfo::Equals(const MovieInfo& url) const {
  return urls_ == url.urls_ && description_ == url.description_ && preview_icon_ == url.preview_icon_ &&
         background_url_ == url.background_url_ && type_ == url.type_;
}

}  // namespace commands_info
}  // namespace fastotv

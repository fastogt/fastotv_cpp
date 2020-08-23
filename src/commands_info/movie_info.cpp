/*  Copyright (C) 2014-2020 FastoGT. All right reserved.

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
                     const url_t& trailer_url,
                     double user_score,
                     timestamp_t prime_date,
                     const std::string& country,
                     timestamp_t duration,
                     Type type)
    : display_name_(name),
      urls_(urls),
      description_(description),
      preview_icon_(preview_icon),
      trailer_url_(trailer_url),
      user_score_(user_score),
      prime_date_(prime_date),
      country_(country),
      duration_(duration),
      type_(type) {}

bool MovieInfo::IsValid() const {
  return !urls_.empty();
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

void MovieInfo::SetTrailerUrl(const url_t& url) {
  trailer_url_ = url;
}

MovieInfo::url_t MovieInfo::GetTrailerUrl() const {
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

  json_object_object_add(deserialized, NAME_FIELD, json_object_new_string(display_name_.c_str()));
  json_object_object_add(deserialized, DESCRIPTION_FIELD, json_object_new_string(description_.c_str()));
  const std::string icon_url_str = preview_icon_.spec();
  json_object_object_add(deserialized, PREVIEW_ICON_FIELD, json_object_new_string(icon_url_str.c_str()));

  const std::string trailer_url_str = trailer_url_.spec();
  json_object_object_add(deserialized, TRAILER_URL_FIELD, json_object_new_string(trailer_url_str.c_str()));
  json_object_object_add(deserialized, USER_SCORE_FIELD, json_object_new_double(user_score_));
  json_object_object_add(deserialized, PRIME_DATE_FIELD, json_object_new_int64(prime_date_));
  json_object_object_add(deserialized, COUNTRY_FIELD, json_object_new_string(country_.c_str()));
  json_object_object_add(deserialized, DURATION_FIELD, json_object_new_int64(duration_));

  json_object* jurls = json_object_new_array();
  for (const auto url : urls_) {
    std::string url_str = url.spec();
    json_object* jurl = json_object_new_string(url_str.c_str());
    json_object_array_add(jurls, jurl);
  }
  json_object_object_add(deserialized, URLS_FIELD, jurls);
  json_object_object_add(deserialized, TYPE_FIELD, json_object_new_int(type_));
  return common::Error();
}

common::Error MovieInfo::DoDeSerialize(json_object* serialized) {
  json_object* jurls = nullptr;
  json_bool jurls_exists = json_object_object_get_ex(serialized, URLS_FIELD, &jurls);
  if (!jurls_exists) {
    return common::make_error_inval();
  }

  urls_t urls;
  size_t len = json_object_array_length(jurls);
  for (size_t i = 0; i < len; ++i) {
    json_object* jurl = json_object_array_get_idx(jurls, i);
    const std::string url_str = json_object_get_string(jurl);
    url_t url(url_str);
    if (url.is_valid()) {
      urls.push_back(url);
    }
  }

  std::string description;
  json_object* jdescription = nullptr;
  json_bool jdescription_exists = json_object_object_get_ex(serialized, DESCRIPTION_FIELD, &jdescription);
  if (jdescription_exists) {
    description = json_object_get_string(jdescription);
  }

  std::string name;
  json_object* jname = nullptr;
  json_bool jname_exists = json_object_object_get_ex(serialized, NAME_FIELD, &jname);
  if (jname_exists) {
    name = json_object_get_string(jname);
  }

  url_t preview_icon;
  json_object* jpreview_icon = nullptr;
  json_bool jpreview_icon_exists = json_object_object_get_ex(serialized, PREVIEW_ICON_FIELD, &jpreview_icon);
  if (jpreview_icon_exists) {
    preview_icon = url_t(json_object_get_string(jpreview_icon));
  }

  url_t trailer_url;
  json_object* jtrailer_url = nullptr;
  json_bool jtrailer_url_exists = json_object_object_get_ex(serialized, TRAILER_URL_FIELD, &jtrailer_url);
  if (jtrailer_url_exists) {
    trailer_url = url_t(json_object_get_string(jtrailer_url));
  }

  double user_score = 0;
  json_object* juser_score = nullptr;
  json_bool juser_score_exists = json_object_object_get_ex(serialized, USER_SCORE_FIELD, &juser_score);
  if (juser_score_exists) {
    user_score = json_object_get_double(juser_score);
  }

  timestamp_t prime_date = 0;
  json_object* jprime_date = nullptr;
  json_bool jprime_date_exists = json_object_object_get_ex(serialized, PRIME_DATE_FIELD, &jprime_date);
  if (jprime_date_exists) {
    prime_date = json_object_get_int64(jprime_date);
  }

  std::string country;
  json_object* jcountry = nullptr;
  json_bool jcountry_exists = json_object_object_get_ex(serialized, COUNTRY_FIELD, &jcountry);
  if (jcountry_exists) {
    country = json_object_get_string(jcountry);
  }

  json_object* jduration = nullptr;
  timestamp_t duration = 0;
  json_bool jduration_exists = json_object_object_get_ex(serialized, DURATION_FIELD, &jduration);
  if (jduration_exists) {
    duration = json_object_get_int64(jduration);
  }

  Type type = VODS;
  json_object* jtype = nullptr;
  json_bool jtype_exists = json_object_object_get_ex(serialized, TYPE_FIELD, &jtype);
  if (jtype_exists) {
    type = static_cast<Type>(json_object_get_int(jtype));
  }

  MovieInfo url(name, urls, description, preview_icon, trailer_url, user_score, prime_date, country, duration, type);
  *this = url;
  return common::Error();
}

bool MovieInfo::Equals(const MovieInfo& url) const {
  return urls_ == url.urls_ && description_ == url.description_ && preview_icon_ == url.preview_icon_ &&
         type_ == url.type_;
}

const MovieInfo::url_t& MovieInfo::GetUnknownIconUrl() {
  static const url_t url("https://fastocloud.com/images/unknown_channel.png");
  return url;
}

bool MovieInfo::IsUnknownIconUrl(const url_t& url) {
  return url == GetUnknownIconUrl();
}

}  // namespace commands_info
}  // namespace fastotv

/*  Copyright (C) 2014-2022 FastoGT. All right reserved.

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

#include <fastotv/types/programme.h>

/*
<programme start="20170613010000 +0000" stop="20170613020000 +0000" channel="FoxNews.us">
  <title lang="en">The Five</title>
  <desc lang="en">The Five covers the hot topics that have everyone talking, and the viewpoints of five voices that will
have everyone listening!</desc>
  <category lang="en">Talk</category>
  <category lang="en">Current Affairs</category>
  <star-rating>
    <value>8.8</value>
  </star-rating>
</programme>
*/

#define CHANNEL_FIELD "channel"
#define START_FIELD "start"
#define STOP_FIELD "stop"
#define TITLE_FIELD "title"
#define CATEGORY_FIELD "category"
#define DESCRIPTION_FIELD "desc"

namespace fastotv {

Programme::Programme()
    : channel_(kInvalidStreamId), start_time_(0), stop_time_(0), title_(), category_(), description_() {}

Programme::Programme(const stream_id_t& channel,
                     timestamp_t start,
                     timestamp_t stop,
                     const std::string& title,
                     const category_t& category,
                     const description_t& descr)
    : channel_(channel),
      start_time_(start),
      stop_time_(stop),
      title_(title),
      category_(category),
      description_(descr) {}

bool Programme::IsValid() const {
  return channel_ != kInvalidStreamId && !title_.empty();
}

common::Error Programme::SerializeFields(json_object* deserialized) const {
  if (!IsValid()) {
    return common::make_error_inval();
  }

  ignore_result(SetStringField(deserialized, CHANNEL_FIELD, channel_));
  ignore_result(SetInt64Field(deserialized, START_FIELD, start_time_));
  ignore_result(SetInt64Field(deserialized, STOP_FIELD, stop_time_));
  ignore_result(SetStringField(deserialized, TITLE_FIELD, title_));
  if (category_) {
    ignore_result(SetStringField(deserialized, CATEGORY_FIELD, *category_));
  }
  if (description_) {
    ignore_result(SetStringField(deserialized, DESCRIPTION_FIELD, *description_));
  }
  return common::Error();
}

common::Error Programme::DoDeSerialize(json_object* serialized) {
  std::string channel;
  common::Error err = GetStringField(serialized, CHANNEL_FIELD, &channel);
  if (err) {
    return err;
  }

  timestamp_t start;
  err = GetInt64Field(serialized, START_FIELD, &start);
  if (err) {
    return err;
  }

  timestamp_t stop;
  err = GetInt64Field(serialized, STOP_FIELD, &stop);
  if (err) {
    return err;
  }

  std::string title;
  err = GetStringField(serialized, TITLE_FIELD, &title);
  if (err) {
    return err;
  }

  json_object* jcategory = nullptr;
  category_t category;
  json_bool jcategory_exists = json_object_object_get_ex(serialized, CATEGORY_FIELD, &jcategory);
  if (jcategory_exists) {
    category = std::string(json_object_get_string(jcategory));
  }

  json_object* jdescr = nullptr;
  description_t descr;
  json_bool jdescr_exists = json_object_object_get_ex(serialized, DESCRIPTION_FIELD, &jdescr);
  if (jdescr_exists) {
    descr = std::string(json_object_get_string(jdescr));
  }

  *this = Programme(channel, start, stop, title, category, descr);
  return common::Error();
}

void Programme::SetChannel(const stream_id_t& channel) {
  channel_ = channel;
}

stream_id_t Programme::GetChannel() const {
  return channel_;
}

void Programme::SetStart(timestamp_t start) {
  start_time_ = start;
}

timestamp_t Programme::GetStart() const {
  return start_time_;
}

void Programme::SetStop(timestamp_t stop) {
  stop_time_ = stop;
}

timestamp_t Programme::GetStop() const {
  return stop_time_;
}

void Programme::SetTitle(const std::string& title) {
  title_ = title;
}

std::string Programme::GetTitle() const {
  return title_;
}

void Programme::SetCategory(const category_t& category) {
  category_ = category;
}

Programme::category_t Programme::GetCategory() const {
  return category_;
}

void Programme::SetDescription(const description_t& description) {
  description_ = description;
}

Programme::description_t Programme::GetDescription() const {
  return description_;
}

common::Optional<Programme> Programme::Make(common::HashValue* json) {
  if (!json) {
    return common::Optional<Programme>();
  }

  Programme res;
  common::Value* channel_field = json->Find(CHANNEL_FIELD);
  std::string channel;
  if (!channel_field || !channel_field->GetAsBasicString(&channel)) {
    return common::Optional<Programme>();
  }
  res.channel_ = channel;

  common::Value* start_field = json->Find(START_FIELD);
  timestamp_t start;
  if (!start_field || !start_field->GetAsInteger64(&start)) {
    return common::Optional<Programme>();
  }
  res.start_time_ = start;

  common::Value* stop_field = json->Find(STOP_FIELD);
  timestamp_t stop;
  if (!stop_field || !start_field->GetAsInteger64(&stop)) {
    return common::Optional<Programme>();
  }
  res.stop_time_ = stop;

  common::Value* title_field = json->Find(TITLE_FIELD);
  std::string title;
  if (!title_field || !title_field->GetAsBasicString(&title)) {
    return common::Optional<Programme>();
  }
  res.title_ = title;

  common::Value* category_field = json->Find(CATEGORY_FIELD);
  std::string category;
  if (category_field && category_field->GetAsBasicString(&category)) {
    res.category_ = category;
  }

  common::Value* desc_field = json->Find(DESCRIPTION_FIELD);
  std::string desc;
  if (desc_field && desc_field->GetAsBasicString(&desc)) {
    res.description_ = desc;
  }

  return res;
}

bool Programme::Equals(const Programme& prog) const {
  return channel_ == prog.channel_ && start_time_ == prog.start_time_ && stop_time_ == prog.stop_time_ &&
         title_ == prog.title_ && description_ == prog.description_;
}

}  // namespace fastotv

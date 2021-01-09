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

#include <fastotv/commands_info/programme_info.h>

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
namespace commands_info {

ProgrammeInfo::ProgrammeInfo()
    : channel_(invalid_stream_id), start_time_(0), stop_time_(0), title_(), category_(), description_() {}

ProgrammeInfo::ProgrammeInfo(const stream_id_t& channel,
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

bool ProgrammeInfo::IsValid() const {
  return channel_ != invalid_stream_id && !title_.empty();
}

common::Error ProgrammeInfo::SerializeFields(json_object* deserialized) const {
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

common::Error ProgrammeInfo::DoDeSerialize(json_object* serialized) {
  std::string channel;
  common::Error err = GetStringField(serialized, CHANNEL_FIELD, &channel);
  if (err) {
    return err;
  }

  int64_t start;
  err = GetInt64Field(serialized, START_FIELD, &start);
  if (err) {
    return err;
  }

  int64_t stop;
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

  *this = ProgrammeInfo(channel, start, stop, title, category, descr);
  return common::Error();
}

void ProgrammeInfo::SetChannel(const stream_id_t& channel) {
  channel_ = channel;
}

stream_id_t ProgrammeInfo::GetChannel() const {
  return channel_;
}

void ProgrammeInfo::SetStart(timestamp_t start) {
  start_time_ = start;
}

timestamp_t ProgrammeInfo::GetStart() const {
  return start_time_;
}

void ProgrammeInfo::SetStop(timestamp_t stop) {
  stop_time_ = stop;
}

timestamp_t ProgrammeInfo::GetStop() const {
  return stop_time_;
}

void ProgrammeInfo::SetTitle(const std::string& title) {
  title_ = title;
}

std::string ProgrammeInfo::GetTitle() const {
  return title_;
}

void ProgrammeInfo::SetCategory(const category_t& category) {
  category_ = category;
}

ProgrammeInfo::category_t ProgrammeInfo::GetCategory() const {
  return category_;
}

void ProgrammeInfo::SetDescription(const description_t& description) {
  description_ = description;
}

ProgrammeInfo::description_t ProgrammeInfo::GetDescription() const {
  return description_;
}

bool ProgrammeInfo::Equals(const ProgrammeInfo& prog) const {
  return channel_ == prog.channel_ && start_time_ == prog.start_time_ && stop_time_ == prog.stop_time_ &&
         title_ == prog.title_ && description_ == prog.description_;
}

}  // namespace commands_info
}  // namespace fastotv

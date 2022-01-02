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

#include <fastotv/commands_info/favorite_info.h>

#define ID_FIELD "id"
#define FAVORITE_FIELD "favorite"

namespace fastotv {
namespace commands_info {

FavoriteInfo::FavoriteInfo() : id_(kInvalidStreamId), favorite_(false) {}

FavoriteInfo::FavoriteInfo(const stream_id_t& channel, bool favorite) : id_(channel), favorite_(favorite) {}

bool FavoriteInfo::IsValid() const {
  return id_ != kInvalidStreamId;
}

common::Error FavoriteInfo::SerializeFields(json_object* deserialized) const {
  if (!IsValid()) {
    return common::make_error_inval();
  }

  ignore_result(SetStringField(deserialized, ID_FIELD, id_));
  ignore_result(SetBoolField(deserialized, FAVORITE_FIELD, favorite_));
  return common::Error();
}

common::Error FavoriteInfo::DoDeSerialize(json_object* serialized) {
  std::string channel;
  common::Error err = GetStringField(serialized, ID_FIELD, &channel);
  if (err) {
    return err;
  }

  bool favorite;
  err = GetBoolField(serialized, FAVORITE_FIELD, &favorite);
  if (err) {
    return err;
  }

  *this = FavoriteInfo(channel, favorite);
  return common::Error();
}

void FavoriteInfo::SetChannel(const stream_id_t& channel) {
  id_ = channel;
}

stream_id_t FavoriteInfo::GetChannel() const {
  return id_;
}

void FavoriteInfo::SetFavorite(bool favorite) {
  favorite_ = favorite;
}

bool FavoriteInfo::GetFavorite() const {
  return favorite_;
}

bool FavoriteInfo::Equals(const FavoriteInfo& prog) const {
  return id_ == prog.id_ && favorite_ == prog.favorite_;
}

}  // namespace commands_info
}  // namespace fastotv

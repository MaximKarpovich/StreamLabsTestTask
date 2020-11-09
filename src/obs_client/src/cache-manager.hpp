/******************************************************************************
    Copyright (C) 2016-2019 by Streamlabs (General Workings Inc)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

******************************************************************************/

#include "utility-v8.hpp"


struct SourceDataInfo
{
	std::string obs_sourceId = "";
	std::string name         = "";
	uint64_t    id           = UINT64_MAX;

	bool isMuted      = false;
	bool mutedChanged = true;

	std::string setting         = "";
	bool        settingsChanged = true;

	uint32_t audioMixers        = UINT32_MAX;
	bool     audioMixersChanged = true;

	std::vector<uint64_t>* filters             = new std::vector<uint64_t>();
	bool                   filtersOrderChanged = true;
};

template<class T>
class CacheManager
{
	public:
	static CacheManager& getInstance()
	{
		static CacheManager instance;
		return instance;
	}

	private:
	CacheManager(){};

	public:
	CacheManager(CacheManager const&) = delete;
	void operator=(CacheManager const&) = delete;

	private:
	std::map<std::string, SourceDataInfo*> sourcesByName;
	std::map<uint64_t, SourceDataInfo*>    sourcesById;


	public:
	void Store(uint64_t id, std::string name, SourceDataInfo* sdi) {
		sdi->name = name;
		sourcesByName.erase(name);
		sourcesById.erase(id);
		sourcesByName.emplace(name, sdi);
		sourcesById.emplace(id, sdi);
	}
	
	T Retrieve(uint64_t id) {
		if (id != UINT64_MAX) {
			if (typeid(T) == typeid(SourceDataInfo*)) {
				auto it = sourcesById.find(id);
				if (it != sourcesById.end()) {
					return (T)it->second;
				}
			}
		}
		return nullptr;
	}
	T Retrieve(std::string name) {
		if (name.size() > 0) {
			if (typeid(T) == typeid(SourceDataInfo*)) {
				auto it = sourcesByName.find(name);
				if (it != sourcesByName.end()) {
					return (T)it->second;
				}
			}
		}
		return nullptr;
	}
	void Remove(uint64_t id) {
		if (id != UINT64_MAX) {
			if (typeid(T) == typeid(SourceDataInfo*)) {
				auto it = sourcesById.find(id);
				if (it != sourcesById.end()) {
					sourcesByName.erase(it->second->name);
					sourcesById.erase(id);
				}
			} 
		} 
	}
};
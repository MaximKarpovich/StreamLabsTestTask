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

#if defined(_WIN32)
#include "Shlobj.h"
#endif

#include <fstream>
#include <string>
#include "controller.hpp"
#include "global.hpp"
#include "input.hpp"
#include "module.hpp"
#include "nodeobs_api.hpp"
#include "video.hpp"
#include "nodeobs_settings.hpp"
#include "nodeobs_service.hpp"
#include "nodeobs_autoconfig.hpp"
#include "callback-manager.hpp"

int main(int, char ** , char **){}

Napi::Object main_node(Napi::Env env, Napi::Object exports) {

	Controller::Init(env, exports);
	api::Init(env, exports);
	osn::Input::Init(env, exports);
	osn::Global::Init(env, exports);
	osn::Module::Init(env, exports);
	osn::Video::Init(env, exports);
	settings::Init(env, exports);
	service::Init(env, exports);
	autoConfig::Init(env, exports);
	sourceCallback::Init(env, exports);
	return exports;
};

NODE_API_MODULE(obs_studio_node, main_node);

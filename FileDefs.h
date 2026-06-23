#pragma once

#include <filesystem>
#include <string_view>

namespace TimberFiles
{
using namespace std::literals;

static const std::string_view backGroundName = "graphics/background.png"sv;
static const std::string_view treeName       = "graphics/tree.png"sv;
static const std::string_view beeName		 = "graphics/bee.png"sv;
static const std::string_view cloudName		 = "graphics/cloud.png"sv;
static const std::string_view branchName	 = "graphics/branch.png"sv;
static const std::string_view playerName	 = "graphics/player.png"sv;
static const std::string_view graveName		 = "graphics/rip.png"sv;
static const std::string_view axeName		 = "graphics/axe.png"sv;
static const std::string_view logName		 = "graphics/log.png"sv;

static const std::string_view fontName		 = "fonts/KOMIKABG.ttf"sv;

const std::filesystem::path path_chop_sound		   = "sound/chop.wav";
const std::filesystem::path path_death_sound	   = "sound/death.wav";
const std::filesystem::path path_out_of_time_sound = "sound/out_of_time.wav";

}
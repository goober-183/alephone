/*

	Copyright (C) 1991-2001 and beyond by Bungie Studios, Inc.
	and the "Aleph One" developers.
 
	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	This license is contained in the file "COPYING",
	which is included with this source code; it is available online at
	http://www.gnu.org/licenses/gpl.html

	Creator of root of XML-Parser Tree
	by Loren Petrich,
	April 16, 2000

	This is for setting up the absolute root element; this element has as its children
	the possible root elements of the Marathon XML files, which is here only "marathon"
*/

#include "cseries.h"
#include "XML_ParseTreeRoot.h"
#include "TextStrings.h"
#include "interface.h"
#include "game_window.h"
#include "PlayerName.h"
#include "motion_sensor.h"
#include "world.h"
#include "overhead_map.h"
#include "dynamic_limits.h"
#include "AnimatedTextures.h"
#include "player.h"
#include "items.h"
#include "media.h"
#include "map.h"
#include "platforms.h"
#include "scenery.h"
#include "fades.h"
#include "ViewControl.h"
#include "weapons.h"
#include "OGL_Setup.h"
#include "shell.h"
#include "SoundManager.h"
#include "vbl.h"
#include "monsters.h"
#include "Logging.h"
#include "Scenario.h"
#include "SW_Texture_Extras.h"
#include "Console.h"
#include "XML_LevelScript.h"
#include "InfoTree.h"

// The absolute root element is a global, of course
XML_ElementParser RootParser("");

// This is the canonical root element in the XML setup files:
XML_ElementParser MarathonParser("marathon");


void SetupParseTree()
{
	// Add the only recognized XML-document-root object here
	RootParser.AddChild(&MarathonParser);

	return;
	
	// Add all its subobjects
	MarathonParser.AddChild(TS_GetParser());		// Text strings
	MarathonParser.AddChild(Interface_GetParser());
	MarathonParser.AddChild(PlayerName_GetParser());
	MarathonParser.AddChild(Infravision_GetParser());
	MarathonParser.AddChild(MotionSensor_GetParser());
	MarathonParser.AddChild(OverheadMap_GetParser());
	MarathonParser.AddChild(DynamicLimits_GetParser());
	MarathonParser.AddChild(AnimatedTextures_GetParser());
	MarathonParser.AddChild(Player_GetParser());
	MarathonParser.AddChild(Items_GetParser());
	MarathonParser.AddChild(ControlPanels_GetParser());
	MarathonParser.AddChild(Liquids_GetParser());
	MarathonParser.AddChild(Sounds_GetParser());
	MarathonParser.AddChild(Platforms_GetParser());
	MarathonParser.AddChild(Scenery_GetParser());
	MarathonParser.AddChild(Faders_GetParser());
	MarathonParser.AddChild(View_GetParser());
	MarathonParser.AddChild(Landscapes_GetParser());
	MarathonParser.AddChild(Weapons_GetParser());
	MarathonParser.AddChild(OpenGL_GetParser());
	MarathonParser.AddChild(Cheats_GetParser());
	MarathonParser.AddChild(TextureLoading_GetParser());
	MarathonParser.AddChild(Keyboard_GetParser());
	MarathonParser.AddChild(DamageKicks_GetParser());
	MarathonParser.AddChild(Monsters_GetParser());
	MarathonParser.AddChild(Logging_GetParser());
	MarathonParser.AddChild(Scenario_GetParser());
	MarathonParser.AddChild(SW_Texture_Extras_GetParser());
	MarathonParser.AddChild(Console_GetParser());
	MarathonParser.AddChild(ExternalDefaultLevelScript_GetParser());
}

// This will reset all values changed by MML scripts which implement ResetValues() method
// and are part of the master MarathonParser tree.
void ResetAllMMLValues()
{
//  MarathonParser.ResetChildrenValues();
	reset_mml_stringset();
	reset_mml_interface();
	reset_mml_motion_sensor();
	reset_mml_overhead_map();
	reset_mml_infravision();
	reset_mml_animated_textures();
	reset_mml_control_panels();
	reset_mml_platforms();
	reset_mml_liquids();
	reset_mml_sounds();
	reset_mml_faders();
	reset_mml_player();
	reset_mml_view();
	reset_mml_weapons();
	reset_mml_items();
	reset_mml_damage_kicks();
	reset_mml_monsters();
	reset_mml_scenery();
	reset_mml_landscapes();
	reset_mml_texture_loading();
	reset_mml_opengl();
	reset_mml_software();
	reset_mml_dynamic_limits();
	reset_mml_player_name();
	reset_mml_scenario();
	reset_mml_keyboard();
	reset_mml_cheats();
	reset_mml_logging();
	reset_mml_console();
	reset_mml_default_levels();
}

void _ParseAllMML(const InfoTree& fileroot)
{
	BOOST_FOREACH(InfoTree root, fileroot.children_named("marathon"))
	{
		BOOST_FOREACH(InfoTree child, root.children_named("stringset"))
			parse_mml_stringset(child);
		BOOST_FOREACH(InfoTree child, root.children_named("interface"))
			parse_mml_interface(child);
		BOOST_FOREACH(InfoTree child, root.children_named("motion_sensor"))
			parse_mml_motion_sensor(child);
		BOOST_FOREACH(InfoTree child, root.children_named("overhead_map"))
			parse_mml_overhead_map(child);
		BOOST_FOREACH(InfoTree child, root.children_named("infravision"))
			parse_mml_infravision(child);
		BOOST_FOREACH(InfoTree child, root.children_named("animated_textures"))
			parse_mml_animated_textures(child);
		BOOST_FOREACH(InfoTree child, root.children_named("control_panels"))
			parse_mml_control_panels(child);
		BOOST_FOREACH(InfoTree child, root.children_named("platforms"))
			parse_mml_platforms(child);
		BOOST_FOREACH(InfoTree child, root.children_named("liquids"))
			parse_mml_liquids(child);
		BOOST_FOREACH(InfoTree child, root.children_named("sounds"))
			parse_mml_sounds(child);
		BOOST_FOREACH(InfoTree child, root.children_named("faders"))
			parse_mml_faders(child);
		BOOST_FOREACH(InfoTree child, root.children_named("player"))
			parse_mml_player(child);
		BOOST_FOREACH(InfoTree child, root.children_named("view"))
			parse_mml_view(child);
		BOOST_FOREACH(InfoTree child, root.children_named("weapons"))
			parse_mml_weapons(child);
		BOOST_FOREACH(InfoTree child, root.children_named("items"))
			parse_mml_items(child);
		BOOST_FOREACH(InfoTree child, root.children_named("damage_kicks"))
			parse_mml_damage_kicks(child);
		BOOST_FOREACH(InfoTree child, root.children_named("monsters"))
			parse_mml_monsters(child);
		BOOST_FOREACH(InfoTree child, root.children_named("scenery"))
			parse_mml_scenery(child);
		BOOST_FOREACH(InfoTree child, root.children_named("landscapes"))
			parse_mml_landscapes(child);
		BOOST_FOREACH(InfoTree child, root.children_named("texture_loading"))
			parse_mml_texture_loading(child);
		BOOST_FOREACH(InfoTree child, root.children_named("opengl"))
			parse_mml_opengl(child);
		BOOST_FOREACH(InfoTree child, root.children_named("software"))
			parse_mml_software(child);
		BOOST_FOREACH(InfoTree child, root.children_named("dynamic_limits"))
			parse_mml_dynamic_limits(child);
		BOOST_FOREACH(InfoTree child, root.children_named("player_name"))
			parse_mml_player_name(child);
		BOOST_FOREACH(InfoTree child, root.children_named("scenario"))
			parse_mml_scenario(child);
		BOOST_FOREACH(InfoTree child, root.children_named("keyboard"))
			parse_mml_keyboard(child);
		BOOST_FOREACH(InfoTree child, root.children_named("cheats"))
			parse_mml_cheats(child);
		BOOST_FOREACH(InfoTree child, root.children_named("logging"))
			parse_mml_logging(child);
		BOOST_FOREACH(InfoTree child, root.children_named("console"))
			parse_mml_console(child);
		BOOST_FOREACH(InfoTree child, root.children_named("default_levels"))
			parse_mml_default_levels(child);
	}
}

bool ParseMMLFromFile(const FileSpecifier& FileSpec)
{
	bool parse_error = false;
	try {
		InfoTree fileroot = InfoTree::load_xml(FileSpec);
		_ParseAllMML(fileroot);
	} catch (InfoTree::parse_error ex) {
		logError2("Error parsing MML file (%s): %s", FileSpec.GetPath(), ex.what());
		parse_error = true;
	} catch (InfoTree::path_error ep) {
		logError2("Path error parsing MML file (%s): %s", FileSpec.GetPath(), ep.what());
		parse_error = true;
	} catch (InfoTree::data_error ed) {
		logError2("Data error parsing MML file (%s): %s", FileSpec.GetPath(), ed.what());
		parse_error = true;
	} catch (InfoTree::unexpected_error ee) {
		logError2("Unexpected error parsing MML file (%s): %s", FileSpec.GetPath(), ee.what());
		parse_error = true;
	}
	return !parse_error;
}

bool ParseMMLFromData(const char *buffer, size_t buflen)
{
	bool parse_error = false;
	try {
		std::istringstream strm(std::string(buffer, buflen));
		InfoTree fileroot = InfoTree::load_xml(strm);
		_ParseAllMML(fileroot);
	} catch (InfoTree::parse_error ex) {
		logError1("Error parsing MML data: %s", ex.what());
		parse_error = true;
	} catch (InfoTree::path_error ep) {
		logError1("Path error parsing MML data: %s", ep.what());
		parse_error = true;
	} catch (InfoTree::data_error ed) {
		logError1("Data error parsing MML data: %s", ed.what());
		parse_error = true;
	} catch (InfoTree::unexpected_error ee) {
		logError1("Unexpected error parsing MML data: %s", ee.what());
		parse_error = true;
	}
	return !parse_error;
}


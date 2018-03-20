#include "scr_vm.h"
#include "g_public_mp.h"

extern "C" void __cdecl GScr_LoadConsts()
{
  scr_const.emptystring = GScr_AllocString("");
  scr_const.active = GScr_AllocString("active");
  scr_const.j_spine4 = GScr_AllocString("j_spine4");
  scr_const.j_helmet = GScr_AllocString("j_helmet");
  scr_const.j_head = GScr_AllocString("j_head");
  scr_const.all = GScr_AllocString("all");
  scr_const.allies = GScr_AllocString("allies");
  scr_const.axis = GScr_AllocString("axis");
  scr_const.bad_path = GScr_AllocString("bad_path");
  scr_const.begin_firing = GScr_AllocString("begin_firing");
  scr_const.cancel_location = GScr_AllocString("cancel_location");
  scr_const.confirm_location = GScr_AllocString("confirm_location");
  scr_const.crouch = GScr_AllocString("crouch");
  scr_const.current = GScr_AllocString("current");
  scr_const.damage = GScr_AllocString("damage");
  scr_const.dead = GScr_AllocString("dead");
  scr_const.death = GScr_AllocString("death");
  scr_const.detonate = GScr_AllocString("detonate");
  scr_const.direct = GScr_AllocString("direct");
  scr_const.dlight = GScr_AllocString("dlight");
  scr_const.done = GScr_AllocString("done");
  scr_const.empty = GScr_AllocString("empty");
  scr_const.end_firing = GScr_AllocString("end_firing");
  scr_const.entity = GScr_AllocString("entity");
  scr_const.explode = GScr_AllocString("explode");
  scr_const.failed = GScr_AllocString("failed");
  scr_const.fraction = GScr_AllocString("fraction");
  scr_const.free = GScr_AllocString("free");
  scr_const.goal = GScr_AllocString("goal");
  scr_const.goal_changed = GScr_AllocString("goal_changed");
  scr_const.goal_yaw = GScr_AllocString("goal_yaw");
  scr_const.grenade = GScr_AllocString("grenade");
  scr_const.grenade_danger = GScr_AllocString("grenade danger");
  scr_const.grenade_fire = GScr_AllocString("grenade_fire");
  scr_const.grenade_pullback = GScr_AllocString("grenade_pullback");
  scr_const.info_notnull = GScr_AllocString("info_notnull");
  scr_const.invisible = GScr_AllocString("invisible");
  scr_const.key1 = GScr_AllocString("key1");
  scr_const.key2 = GScr_AllocString("key2");
  scr_const.killanimscript = GScr_AllocString("killanimscript");
  scr_const.left = GScr_AllocString("left");
  scr_const.light = GScr_AllocString("light");
  scr_const.movedone = GScr_AllocString("movedone");
  scr_const.noclass = GScr_AllocString("noclass");
  scr_const.none = GScr_AllocString("none");
  scr_const.normal = GScr_AllocString("normal");
  scr_const.player = GScr_AllocString("player");
  scr_const.position = GScr_AllocString("position");
  scr_const.projectile_impact = GScr_AllocString("projectile_impact");
  scr_const.prone = GScr_AllocString("prone");
  scr_const.right = GScr_AllocString("right");
  scr_const.reload = GScr_AllocString("reload");
  scr_const.reload_start = GScr_AllocString("reload_start");
  scr_const.rocket = GScr_AllocString("rocket");
  scr_const.rotatedone = GScr_AllocString("rotatedone");
  scr_const.script_brushmodel = GScr_AllocString("script_brushmodel");
  scr_const.script_model = GScr_AllocString("script_model");
  scr_const.script_origin = GScr_AllocString("script_origin");
  scr_const.snd_enveffectsprio_level = GScr_AllocString("snd_enveffectsprio_level");
  scr_const.snd_enveffectsprio_shellshock = GScr_AllocString("snd_enveffectsprio_shellshock");
  scr_const.snd_channelvolprio_holdbreath = GScr_AllocString("snd_channelvolprio_holdbreath");
  scr_const.snd_channelvolprio_pain = GScr_AllocString("snd_channelvolprio_pain");
  scr_const.snd_channelvolprio_shellshock = GScr_AllocString("snd_channelvolprio_shellshock");
  scr_const.stand = GScr_AllocString("stand");
  scr_const.suppression = GScr_AllocString("suppression");
  scr_const.suppression_end = GScr_AllocString("suppression_end");
  scr_const.surfacetype = GScr_AllocString("surfacetype");
  scr_const.tag_aim = GScr_AllocString("tag_aim");
  scr_const.tag_aim_animated = GScr_AllocString("tag_aim_animated");
  scr_const.tag_brass = GScr_AllocString("tag_brass");
  scr_const.tag_butt = GScr_AllocString("tag_butt");
  scr_const.tag_clip = GScr_AllocString("tag_clip");
  scr_const.tag_flash = GScr_AllocString("tag_flash");
  scr_const.tag_flash_11 = GScr_AllocString("tag_flash_11");
  scr_const.tag_flash_2 = GScr_AllocString("tag_flash_2");
  scr_const.tag_flash_22 = GScr_AllocString("tag_flash_22");
  scr_const.tag_flash_3 = GScr_AllocString("tag_flash_3");
  scr_const.tag_fx = GScr_AllocString("tag_fx");
  scr_const.tag_inhand = GScr_AllocString("tag_inhand");
  scr_const.tag_knife_attach = GScr_AllocString("tag_knife_attach");
  scr_const.tag_knife_fx = GScr_AllocString("tag_knife_fx");
  scr_const.tag_laser = GScr_AllocString("tag_laser");
  scr_const.tag_origin = GScr_AllocString("tag_origin");
  scr_const.tag_weapon = GScr_AllocString("tag_weapon");
  scr_const.tag_player = GScr_AllocString("tag_player");
  scr_const.tag_camera = GScr_AllocString("tag_camera");
  scr_const.tag_weapon_right = GScr_AllocString("tag_weapon_right");
  scr_const.tag_gasmask = GScr_AllocString("tag_gasmask");
  scr_const.tag_gasmask2 = GScr_AllocString("tag_gasmask2");
  scr_const.tag_sync = GScr_AllocString("tag_sync");
  scr_const.target_script_trigger = GScr_AllocString("target_script_trigger");
  scr_const.tempEntity = GScr_AllocString("tempEntity");
  scr_const.top = GScr_AllocString("top");
  scr_const.touch = GScr_AllocString("touch");
  scr_const.trigger = GScr_AllocString("trigger");
  scr_const.trigger_use = GScr_AllocString("trigger_use");
  scr_const.trigger_use_touch = GScr_AllocString("trigger_use_touch");
  scr_const.trigger_damage = GScr_AllocString("trigger_damage");
  scr_const.trigger_lookat = GScr_AllocString("trigger_lookat");
  scr_const.truck_cam = GScr_AllocString("truck_cam");
  scr_const.weapon_change = GScr_AllocString("weapon_change");
  scr_const.weapon_fired = GScr_AllocString("weapon_fired");
  scr_const.worldspawn = GScr_AllocString("worldspawn");
  scr_const.flashbang = GScr_AllocString("flashbang");
  scr_const.flash = GScr_AllocString("flash");
  scr_const.smoke = GScr_AllocString("smoke");
  scr_const.night_vision_on = GScr_AllocString("night_vision_on");
  scr_const.night_vision_off = GScr_AllocString("night_vision_off");
  scr_const.MOD_UNKNOWN = GScr_AllocString("MOD_UNKNOWN");
  scr_const.MOD_PISTOL_BULLET = GScr_AllocString("MOD_PISTOL_BULLET");
  scr_const.MOD_RIFLE_BULLET = GScr_AllocString("MOD_RIFLE_BULLET");
  scr_const.MOD_GRENADE = GScr_AllocString("MOD_GRENADE");
  scr_const.MOD_GRENADE_SPLASH = GScr_AllocString("MOD_GRENADE_SPLASH");
  scr_const.MOD_PROJECTILE = GScr_AllocString("MOD_PROJECTILE");
  scr_const.MOD_PROJECTILE_SPLASH = GScr_AllocString("MOD_PROJECTILE_SPLASH");
  scr_const.MOD_MELEE = GScr_AllocString("MOD_MELEE");
  scr_const.MOD_HEAD_SHOT = GScr_AllocString("MOD_HEAD_SHOT");
  scr_const.MOD_CRUSH = GScr_AllocString("MOD_CRUSH");
  scr_const.MOD_TELEFRAG = GScr_AllocString("MOD_TELEFRAG");
  scr_const.MOD_FALLING = GScr_AllocString("MOD_FALLING");
  scr_const.MOD_SUICIDE = GScr_AllocString("MOD_SUICIDE");
  scr_const.MOD_TRIGGER_HURT = GScr_AllocString("MOD_TRIGGER_HURT");
  scr_const.MOD_EXPLOSIVE = GScr_AllocString("MOD_EXPLOSIVE");
  scr_const.MOD_IMPACT = GScr_AllocString("MOD_IMPACT");
  scr_const.script_vehicle = GScr_AllocString("script_vehicle");
  scr_const.script_vehicle_collision = GScr_AllocString("script_vehicle_collision");
  scr_const.script_vehicle_collmap = GScr_AllocString("script_vehicle_collmap");
  scr_const.script_vehicle_corpse = GScr_AllocString("script_vehicle_corpse");
  scr_const.turret_fire = GScr_AllocString("turret_fire");
  scr_const.turret_on_target = GScr_AllocString("turret_on_target");
  scr_const.turret_not_on_target = GScr_AllocString("turret_not_on_target");
  scr_const.turret_on_vistarget = GScr_AllocString("turret_on_vistarget");
  scr_const.turret_no_vis = GScr_AllocString("turret_no_vis");
  scr_const.turret_rotate_stopped = GScr_AllocString("turret_rotate_stopped");
  scr_const.turret_deactivate = GScr_AllocString("turret_deactivate");
  scr_const.turretstatechange = GScr_AllocString("turretstatechange");
  scr_const.turretownerchange = GScr_AllocString("turretownerchange");
  scr_const.reached_end_node = GScr_AllocString("reached_end_node");
  scr_const.reached_wait_node = GScr_AllocString("reached_wait_node");
  scr_const.reached_wait_speed = GScr_AllocString("reached_wait_speed");
  scr_const.near_goal = GScr_AllocString("near_goal");
  scr_const.veh_collision = GScr_AllocString("veh_collision");
  scr_const.veh_predictedcollision = GScr_AllocString("veh_predictedcollision");
  scr_const.auto_change = GScr_AllocString("auto_change");
  scr_const.back_low = GScr_AllocString("back_low");
  scr_const.back_mid = GScr_AllocString("back_mid");
  scr_const.back_up = GScr_AllocString("back_up");
  scr_const.begin = GScr_AllocString("begin");
  scr_const.call_vote = GScr_AllocString("call_vote");
  scr_const.freelook = GScr_AllocString("freelook");
  scr_const.head = GScr_AllocString("head");
  scr_const.intermission = GScr_AllocString("intermission");
  scr_const.j_head_dup = GScr_AllocString("j_head");
  scr_const.manual_change = GScr_AllocString("manual_change");
  scr_const.menuresponse = GScr_AllocString("menuresponse");
  scr_const.neck = GScr_AllocString("neck");
  scr_const.pelvis = GScr_AllocString("pelvis");
  scr_const.pistol = GScr_AllocString("pistol");
  scr_const.plane_waypoint = GScr_AllocString("plane_waypoint");
  scr_const.playing = GScr_AllocString("playing");
  scr_const.spectator = GScr_AllocString("spectator");
  scr_const.vote = GScr_AllocString("vote");
  scr_const.sprint_begin = GScr_AllocString("sprint_begin");
  scr_const.sprint_end = GScr_AllocString("sprint_end");
  scr_const.tag_driver = GScr_AllocString("tag_driver");
  scr_const.tag_passenger = GScr_AllocString("tag_passenger");
  scr_const.tag_gunner = GScr_AllocString("tag_gunner");
  scr_const.tag_wheel_front_left = GScr_AllocString("tag_wheel_front_left");
  scr_const.tag_wheel_front_right = GScr_AllocString("tag_wheel_front_right");
  scr_const.tag_wheel_back_left = GScr_AllocString("tag_wheel_back_left");
  scr_const.tag_wheel_back_right = GScr_AllocString("tag_wheel_back_right");
  scr_const.tag_wheel_middle_left = GScr_AllocString("tag_wheel_middle_left");
  scr_const.tag_wheel_middle_right = GScr_AllocString("tag_wheel_middle_right");
  scr_const.script_vehicle_collision = GScr_AllocString("script_vehicle_collision");
  scr_const.script_vehicle_collmap = GScr_AllocString("script_vehicle_collmap");
  scr_const.script_vehicle_corpse = GScr_AllocString("script_vehicle_corpse");
  scr_const.tag_detach = GScr_AllocString("tag_detach");
  scr_const.tag_popout = GScr_AllocString("tag_popout");
  scr_const.tag_body = GScr_AllocString("tag_body");
  scr_const.tag_turret = GScr_AllocString("tag_turret");
  scr_const.tag_turret_base = GScr_AllocString("tag_turret_base");
  scr_const.tag_barrel = GScr_AllocString("tag_barrel");
  scr_const.tag_engine_left = GScr_AllocString("tag_engine_left");
  scr_const.tag_engine_right = GScr_AllocString("tag_engine_right");
  scr_const.front_left = GScr_AllocString("front_left");
  scr_const.front_right = GScr_AllocString("front_right");
  scr_const.back_left = GScr_AllocString("back_left");
  scr_const.back_right = GScr_AllocString("back_right");
  scr_const.tag_gunner_pov = GScr_AllocString("tag_gunner_pov");
}
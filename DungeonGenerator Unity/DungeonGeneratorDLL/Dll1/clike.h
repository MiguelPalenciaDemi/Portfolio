#pragma once
#include "ProcGen.h"

extern "C" __declspec(dllexport)
ProcGen* create_ProcGen() {
	return new ProcGen();
}

extern "C" __declspec(dllexport)
void destroy_ProcGen(ProcGen* pc) {
	delete pc;
}

extern "C" __declspec(dllexport)
void generate_dungeon(ProcGen* pc) {
	pc->generate();
}

extern "C" __declspec(dllexport)
void set_width(ProcGen* pc, int width) {
	pc->set_width(width);
}

extern "C" __declspec(dllexport)
void set_height(ProcGen* pc, int height) {
	pc->set_height(height);
}

extern "C" __declspec(dllexport)
void set_room_min_size(ProcGen* pc, int min) {
	pc->set_room_min_size(min);
}


extern "C" __declspec(dllexport)
void set_room_max_size(ProcGen* pc, int max) {
	pc->set_room_max_size(max);
}

extern "C" __declspec(dllexport)
void set_min_rooms(ProcGen* pc, int min) {
	pc->set_min_rooms(min);
}


extern "C" __declspec(dllexport)
void set_max_rooms(ProcGen* pc, int max) {
	pc->set_max_rooms(max);
}

extern "C" __declspec(dllexport)
int get_width(ProcGen* pc) {
	return pc->get_width();
}

extern "C" __declspec(dllexport)
int get_height(ProcGen* pc) {
	return pc->get_height();
}

extern "C" __declspec(dllexport)
int get_room_min_size(ProcGen* pc) {
	return pc->get_room_min_size();
}

extern "C" __declspec(dllexport)
int get_room_max_size(ProcGen* pc) {
	return pc->get_room_max_size();
}

extern "C" __declspec(dllexport)
int get_min_rooms(ProcGen* pc) {
	return pc->get_min_rooms();
}

extern "C" __declspec(dllexport)
int get_max_rooms(ProcGen* pc) {
	return pc->get_max_rooms();
}

extern "C" __declspec(dllexport)
char* get_dungeon(ProcGen* pc) {
	return pc->get_dungeon();
}










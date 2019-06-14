#pragma once
#include <stdlib.h>
#include <string>

class ProcGen
{
private:
	int width = 20;
	int height = 20;
	int roomMinSize = 3;
	int roomMaxSize = 4;
	int minRooms = 3;
	int maxRooms = 5;
	char* cells = NULL;

	const char WALL_CELL = 'X';
	const char FLOOR_CELL = ' ';

	void reset_cells();

public:
	ProcGen();
	~ProcGen();
	void set_width(int width);
	void set_height(int height);
	void set_room_min_size(int min);
	void set_room_max_size(int max);
	void set_min_rooms(int min);
	void set_max_rooms(int max);

	int get_width() { return width; }
	int get_height() { return height; }
	int get_room_min_size() { return roomMinSize; }
	int get_room_max_size() { return roomMaxSize; }
	int get_min_rooms() { return minRooms; }
	int get_max_rooms() { return maxRooms; }	
	char* get_dungeon() { return cells; }

	void generate();
};


#include <iostream>
#include <fstream>
#include <string>
#include "logic.h"

using std::cout, std::endl, std::ifstream, std::string;

/**
 * TODO: Student implement this function
 * Load representation of the dungeon level from file into the 2D map.
 * Calls createMap to allocate the 2D array.
 * @param   fileName    File name of dungeon level.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object by reference to set starting position.
 * @return  pointer to 2D dynamic array representation of dungeon map with player's location., or nullptr if loading fails for any reason
 * @updates  maxRow, maxCol, player
 */
char** loadLevel(const string& fileName, int& maxRow, int& maxCol, Player& player) {
    int rows_0 = 0;
    int col_0 = 0;
    int row_0_player = 0;
    int col_0_player = 0;
    bool exit = false;
    ifstream green(fileName);
    if(!green.is_open())
    {
        return nullptr;
    }
    else{
        green >> rows_0;
        if(green.fail() || rows_0 < 1)
        {
            cout << "35" << endl;
            return nullptr;
        }
        maxRow = rows_0;
        green >> col_0;
        if(green.fail() || col_0 < 1 || (rows_0*col_0) < 0)
        {
            cout << "43" << endl;
            return nullptr;
        }
        maxCol = col_0;
        green >> row_0_player;
        if (green.fail() || row_0_player < 0 || row_0_player >= maxRow)
        {
            cout << "51" << endl;
            return nullptr;
        }
        player.row = row_0_player;
        green >> col_0_player;
        if(green.fail() || col_0_player < 0 || col_0_player >= maxCol)
        {
            cout << "59" << endl;
            return nullptr;
        }
        player.col = col_0_player;
        char** Level =createMap(maxRow, maxCol);

        if (Level == nullptr){
            return nullptr;
        }
    
    char symbol = '/';
        for(int i = 0; i<maxRow;i++){
            for(int k = 0; k<maxCol;k++){
                green >> symbol;
                if(green.fail()){
                    cout << "76" << endl;
                    deleteMap(Level, maxRow);
                    maxCol = 0;
                    return nullptr;
                }
                if(symbol != TILE_OPEN && symbol != TILE_AMULET && symbol != TILE_DOOR && symbol != TILE_EXIT && symbol != TILE_MONSTER && symbol != TILE_PILLAR && symbol != TILE_PLAYER && symbol != TILE_TREASURE && symbol){
                    cout << "84" << endl;
                    deleteMap(Level, maxRow);
                    maxCol = 0;
                    return nullptr;
                }
                if(symbol == '!' || symbol == '?'){
                    exit = true;
                }
                Level[i][k] = symbol;
            }
        }
        if(Level[row_0_player][col_0_player] == '-'){
            Level[row_0_player][col_0_player] = 'o';
        }
        if(!exit){
            cout << "97" << endl;
            deleteMap(Level, maxRow);
            maxCol = 0;
            return nullptr;
        }
        symbol = 'z';
        green >> symbol;
        if(!green.fail()){
            cout << "106" << endl;
            deleteMap(Level, maxRow);
            maxCol = 0;
            return nullptr;
        }
        return Level;
    }
}

/**
 * TODO: Student implement this function
 * Translate the character direction input by the user into row or column change.
 * That is, updates the nextRow or nextCol according to the player's movement direction.
 * @param   input       Character input by the user which translates to a direction.
 * @param   nextRow     Player's next row on the dungeon map (up/down).
 * @param   nextCol     Player's next column on dungeon map (left/right).
 * @updates  nextRow, nextCol
 */
void getDirection(char input, int& nextRow, int& nextCol) {
    switch(input){
        case MOVE_UP:
        nextRow--;
        break;
        case MOVE_DOWN:
        nextRow++;
        break;
        case MOVE_LEFT:
        nextCol--;
        break;
        case MOVE_RIGHT:
        nextCol++;
        break;
    }
}

/**
 * TODO: [suggested] Student implement this function
 * Allocate the 2D map array.
 * Initialize each cell to TILE_OPEN.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @return  2D map array for the dungeon level, holds char type.
 */
char** createMap(int maxRow, int maxCol) {
    char** map = new char*[maxRow];
    for (int i = 0; i < maxRow; i++){
        map[i] = new char[maxCol];
        for (int k = 0; k < maxCol; k++){
            map[i][k] = TILE_OPEN;
        }
    }
    return map;
}

/**
 * TODO: Student implement this function
 * Deallocates the 2D map array.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @return None
 * @update map, maxRow
 */
void deleteMap(char**& map, int& maxRow) {
    if (map != nullptr) {
        for(int i = 0;  i < maxRow; i++){
            delete[] map[i];
        }
        delete[] map;
        map = nullptr;
    }
    maxRow = 0;
}

/**
 * TODO: Student implement this function
 * Resize the 2D map by doubling both dimensions.
 * Copy the current map contents to the right, diagonal down, and below.
 * Do not duplicate the player, and remember to avoid memory leaks!
 * You can use the STATUS constants defined in logic.h to help!
 * @param   map         Dungeon map. 
 * @param   maxRow      Number of rows in the dungeon table (aka height), to be doubled.
 * @param   maxCol      Number of columns in the dungeon table (aka width), to be doubled.
 * @return  pointer to a dynamically-allocated 2D array (map) that has twice as many columns and rows in size.
 * @update maxRow, maxCol
 */
char** resizeMap(char** map, int& maxRow, int& maxCol) {
    if(maxRow <= 0 || maxCol <= 0 || map == nullptr){
        return nullptr;
    }
    int max_Row2 = maxRow * 2;
    int max_Col2 = maxCol * 2;
    char** new_array = createMap(max_Row2, max_Col2);
    for (int i = 0; i<maxRow; i++){
        for(int k = 0; k < maxCol; k++){
            new_array[i][k] = map[i][k];
            if(map[i][k] == 'o'){
                map[i][k] = TILE_OPEN;
            }
        }
    }
    for (int i = 0; i<maxRow; i++){
        for(int k = 0; k < maxCol; k++){
            new_array[i][maxCol + k] = map[i][k];
        }
    }
    for (int i = 0; i<maxRow; i++){
        for(int k = 0; k < maxCol; k++){
                new_array[maxRow + i][k] = map[i][k];
        }
    }
    for (int i = 0; i<maxRow; i++){
        for(int k = 0; k < maxCol; k++){
                new_array[maxRow + i][maxCol + k] = map[i][k];
        }
    }
    deleteMap(map, maxRow);
    maxRow = max_Row2;
    maxCol = max_Col2;
    return new_array;
}

/**
 * TODO: Student implement this function
 * Checks if the player can move in the specified direction and performs the move if so.
 * Cannot move out of bounds or onto TILE_PILLAR or TILE_MONSTER.
 * Cannot move onto TILE_EXIT without at least one treasure. 
 * If TILE_TREASURE, increment treasure by 1.
 * Remember to update the map tile that the player moves onto and return the appropriate status.
 * You can use the STATUS constants defined in logic.h to help!
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object to by reference to see current location.
 * @param   nextRow     Player's next row on the dungeon map (up/down).
 * @param   nextCol     Player's next column on dungeon map (left/right).
 * @return  Player's movement status after updating player's position.
 * @update map contents, player
 */
int doPlayerMove(char** map, int maxRow, int maxCol, Player& player, int nextRow, int nextCol) {
    if (nextCol >= maxCol || nextCol < 0){
        nextRow = player.row;
        nextCol = player.col;
        return 0;
    }
    if (nextRow >= maxRow || nextRow < 0){
        nextRow = player.row;
        nextCol = player.col;
        return 0;
    }
    if(map[nextRow][nextCol] == TILE_PILLAR || map[nextRow][nextCol] == TILE_MONSTER){
        nextRow = player.row;
        nextCol = player.col;
        return 0;
    }
    if(map[nextRow][nextCol] == TILE_TREASURE){
        player.treasure ++;
        map[player.row][player.col] = TILE_OPEN;
        map[nextRow][nextCol] = TILE_PLAYER;

        player.row = nextRow;
        player.col = nextCol;
        
        return 2;
    }
    if(map[nextRow][nextCol] == TILE_AMULET){
        map[player.row][player.col] = TILE_OPEN;
        map[nextRow][nextCol] = TILE_PLAYER;

        player.row = nextRow;
        player.col = nextCol;
        
        return 3;
    }
    if(map[nextRow][nextCol] == TILE_DOOR){
        map[player.row][player.col] = TILE_OPEN;
        map[nextRow][nextCol] = TILE_PLAYER;

        player.row = nextRow;
        player.col = nextCol;
        
        return 4;
    }
    if(map[nextRow][nextCol] == TILE_EXIT){
        if(player.treasure >= 1){
            map[player.row][player.col] = TILE_OPEN;
            map[nextRow][nextCol] = TILE_PLAYER;
            player.row = nextRow;
            player.col = nextCol;
            return 5;
        }
        nextRow = player.row;
        nextCol = player.col;
        return 0;
    }

    map[player.row][player.col] = TILE_OPEN;
    map[nextRow][nextCol] = TILE_PLAYER;
    player.row = nextRow;
    player.col = nextCol;
    return 1;
}

/**
 * TODO: Student implement this function
 * Update monster locations:
 * We check up, down, left, right from the current player position.
 * If we see an obstacle, there is no line of sight in that direction, and the monster does not move.
 * If we see a monster before an obstacle, the monster moves one tile toward the player.
 * We should update the map as the monster moves.
 * At the end, we check if a monster has moved onto the player's tile.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object by reference for current location.
 * @return  Boolean value indicating player status: true if monster reaches the player, false if not.
 * @update map contents
 */
bool doMonsterAttack(char** map, int maxRow, int maxCol, const Player& player) {
    bool dead_player = false;
    for(int i = player.row-1; i>= 0; i--){
        if(map[i][player.col] == TILE_PILLAR){
            break;
        }
        if(map[i][player.col] == TILE_MONSTER){
            if (map[i+1][player.col] == TILE_PLAYER){
                map[i][player.col] = TILE_OPEN;
                map[i+1][player.col] = TILE_MONSTER;
                dead_player = true;
            }
            map[i][player.col] = TILE_OPEN;
            map[i+1][player.col] = TILE_MONSTER;
        }
    }
    for(int i = player.row+1; i<maxRow; i++){
        if(map[i][player.col] == TILE_PILLAR){
            break;
        }
        if(map[i][player.col] == TILE_MONSTER){
            if (map[i-1][player.col] == TILE_PLAYER){
                map[i][player.col] = TILE_OPEN;
                map[i-1][player.col] = TILE_MONSTER;
                dead_player = true;
            }
            map[i][player.col] = TILE_OPEN;
            map[i-1][player.col] = TILE_MONSTER;
        }
    }
    for(int i = player.col-1; i>= 0; i--){
        if(map[player.row][i] == TILE_PILLAR){
            break;
        }
        if(map[player.row][i] == TILE_MONSTER){
            if (map[player.row][i+1] == TILE_PLAYER){
                map[player.row][i] = TILE_OPEN;
                map[player.row][i+1] = TILE_MONSTER;
                dead_player = true;
            }
            map[player.row][i] = TILE_OPEN;
            map[player.row][i+1]=TILE_MONSTER;
        }
    }
    for(int i = player.col+1; i<maxCol; i++){
        if(map[player.row][i] == TILE_PILLAR){
            break;
        }
        if(map[player.row][i] == TILE_MONSTER){
            if (map[player.row][i-1] == TILE_PLAYER){
                map[player.row][i] = TILE_OPEN;
                map[player.row][i-1] = TILE_MONSTER;
                dead_player = true;
            }
            map[player.row][i] = TILE_OPEN;
            map[player.row][i-1] = TILE_MONSTER;
        }
    }
    
    return dead_player;
}

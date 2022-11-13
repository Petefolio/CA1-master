#include "raylib.h"
struct Player { //struct for player
    Rectangle rect;
    Vector2 speed;
    Color color;
};

int main() {
const int windowWidth{500};
const int windowHeight{500};
int player_posX = 250;
int player_posY = 250;
InitWindow(800, 500, "Game");
InitAudioDevice();
SetTargetFPS(60);

Player player;
player.rect.height= 35;
player.rect.width = 35;
player.color = BLUE;
player.rect.x = windowWidth/2;
player.rect.y = windowHeight-player.rect.height;
player.speed.x = 10;
player.speed.y = 0;

Music music = LoadMusicStream("resources/bg_music.wav"); 
Sound sound = LoadSound("resources/collect.wav");
PlayMusicStream(music);

Rectangle enemy = { 10, GetScreenHeight()/2.0f - 50, 200, 100 }; 
int enemySpeedX = 4; //Credit to: https://www.raylib.com/examples.html "collision area"
//End of credit

Rectangle obstacleA = { 100, GetScreenHeight()/4.0f - 100, 50, 50 };
int boxBSpeedY = 4;

Rectangle obstacleB = { 650, GetScreenHeight()/4.0f - 100, 50, 50 };
int boxCSpeedY = 4;

Rectangle obstacleC = { 600, GetScreenHeight()/1.1f - 100, 50, 50 };
int boxDSpeedY = 4;

Rectangle obstacleD = { 150, GetScreenHeight()/1.1f - 100, 50, 50 };
int boxESpeedY = 4;

Rectangle pit = { 360, GetScreenHeight()/2.5f - 100, 80, 80 };

Rectangle key = { 500, GetScreenHeight()/2.5f - 100, 30, 30 };

Rectangle door = {GetScreenWidth()/2.0f, GetScreenHeight()- 500, 60, 10 };

bool collision{}; //collision bool
bool have_key{}; //bool for having key
bool game_end{false}; //bool to end game


while(!WindowShouldClose()){

UpdateMusicStream(music); 

if(CheckCollisionRecs(player.rect,enemy)){ //collision detection for enemies and obstacles
		collision = true;
	}
if(CheckCollisionRecs(player.rect,obstacleA)){
		collision = true;
	}
if(CheckCollisionRecs(player.rect,obstacleB)){
		collision = true;
	}
if(CheckCollisionRecs(player.rect,obstacleC)){
		collision = true;
	}
if(CheckCollisionRecs(player.rect,obstacleD)){
		collision = true;
	}
if(CheckCollisionRecs(player.rect,pit)){
		collision = true;
	}
if(CheckCollisionRecs(player.rect,key)){ //check to see if the player has picked up the key
        PlaySound(sound);
        have_key = true;
}

if(CheckCollisionRecs(player.rect,pit)){
		collision = true;
}
if(CheckCollisionRecs(player.rect, door) && have_key){
    game_end = true; //end the game if the player passes through the door carrying the
}

if (((enemy.x + enemy.width) >= GetScreenWidth()) || (enemy.x <= 0)) enemySpeedX *= -1;
//Enemy movement. Credit to: https://www.raylib.com/examples.html "collision area". End of credit.

if (IsKeyDown(KEY_D))
{
    player.rect.x = player.rect.x+10;
}
if (IsKeyDown(KEY_A))
{
    player.rect.x = player.rect.x-10;
}
if (IsKeyDown(KEY_S))
{
    player.rect.y = player.rect.y+10;
}
if (IsKeyDown(KEY_W))
{
    player.rect.y = player.rect.y-10;
}
BeginDrawing();

enemy.x += enemySpeedX; //Enemy movement. Credit to: https://www.raylib.com/examples.html "collision area". End of credit
ClearBackground(WHITE);
if (collision) {
 DrawText("Game Over!",GetScreenHeight()/2.0f, GetScreenHeight()/2.0f, 50, PURPLE); //game over screen
}
else if (game_end){ //else if statement to allow for both the game over and game win scenarios occur without error
   DrawText("You win!",GetScreenHeight()/2.0f, GetScreenHeight()/2.0f, 50, PURPLE); //game win screen.
}
else{

DrawRectangleRec(player.rect,player.color); //draw the sprites if the game is not over
DrawRectangleRec(enemy, GOLD);
DrawRectangleRec(obstacleA, RED);
DrawRectangleRec(obstacleB, RED);
DrawRectangleRec(obstacleC, RED);
DrawRectangleRec(obstacleD, RED);
DrawRectangleRec(pit, PURPLE);
DrawRectangleRec(door, GREEN);
DrawText("Collect the yellow key and", 20, 80, 20, BLACK);
DrawText("escape through the green door!", 20, 100, 20, BLACK);
}

if (!have_key) {
DrawRectangleRec(key, YELLOW); //have the key disappear if the player picks it up, and be drawn if they have not.
}

EndDrawing();
}
CloseAudioDevice(); 
CloseWindow();
}
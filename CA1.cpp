#include "raylib.h"
struct Player { //struct for player
    Rectangle rect;
    Vector2 speed;
    Color color;
};

struct Bullets{ //struct for bullets. Credit to https://github.com/naoisecollins/scarfyJump/blob/master/scarfyJump.cpp.
	Rectangle rect;
	Vector2 speed; 
	Color color;
	bool active;
};
//End of credit.

int main() {
const int windowWidth{500};
const int windowHeight{500};
int player_posX = 250;
int player_posY = 250;
int life_counter = 3;
int num_bullets{50};

InitWindow(800, 500, "Game");
SetTargetFPS(60);

Player player;
player.rect.height= 35;
player.rect.width = 35;
player.color = BLUE;
player.rect.x = windowWidth/2;
player.rect.y = windowHeight-player.rect.height;
player.speed.x = 10;
player.speed.y = 0;

Bullets bullet[num_bullets];
for (int i = 0; i<num_bullets; i++){
bullet[i].rect.height= 10;
bullet[i].rect.width = 10;
bullet[i].color = BLACK; //changed the color of the bullets from green to black 
bullet[i].rect.x = (windowWidth/2)+(player.rect.width/2)-(bullet[i].rect.width/2);
bullet[i].rect.y = (windowHeight-player.rect.height)-(bullet[i].rect.height);
bullet[i].speed.x = 50;
bullet[i].speed.y = -10;
bullet[i].active = false;}
int shootRate = 0;

Music music = LoadMusicStream("resources/bg_music.wav"); 
Sound sound = LoadSound("resources/pistol.wav");
PlayMusicStream(music);

Rectangle boxA = { 10, GetScreenHeight()/2.0f - 50, 200, 100 }; //rectangle enemy placeholders
int boxASpeedX = 4; //Credit to: https://www.raylib.com/examples.html "collision area"
//End of credit

Rectangle boxB = { 100, GetScreenHeight()/4.0f - 100, 50, 50 };
int boxBSpeedY = 4;

Rectangle boxC = { 650, GetScreenHeight()/4.0f - 100, 50, 50 };
int boxCSpeedY = 4;

Rectangle boxD = { 600, GetScreenHeight()/1.1f - 100, 50, 50 };
int boxDSpeedY = 4;

Rectangle boxE = { 150, GetScreenHeight()/1.1f - 100, 50, 50 };
int boxESpeedY = 4;

Rectangle pit = { 360, GetScreenHeight()/2.5f - 100, 80, 80 };

Rectangle key = { 500, GetScreenHeight()/2.5f - 100, 30, 30 };

Rectangle door = {GetScreenWidth()/2.0f, GetScreenHeight()- 500, 60, 10 };

bool collision{}; //collision bool
bool have_key{}; //bool for having key
bool game_end{false}; //bool to end game
bool dead_enemy{false}; //bool to kill enemies

while(!WindowShouldClose()){

if(CheckCollisionRecs(player.rect,boxA)){ //collision detection for enemies and obstacles
		collision = true;
	}
if(CheckCollisionRecs(player.rect,boxB)){
		collision = true;
	}
if(CheckCollisionRecs(player.rect,boxC)){
		collision = true;
	}
if(CheckCollisionRecs(player.rect,boxD)){
		collision = true;
	}
if(CheckCollisionRecs(player.rect,boxE)){
		collision = true;
	}
if(CheckCollisionRecs(player.rect,pit)){
		collision = true;
	}
if(CheckCollisionRecs(player.rect,key)){ //check to see if the player has picked up the key
        have_key = true;
}

if(CheckCollisionRecs(player.rect,pit)){
		collision = true;
}
if(CheckCollisionRecs(player.rect, door) && have_key){
    game_end = true; //end the game if the player passes through the door carrying the
}

for (int i = 0; i < num_bullets; i++) //Shoot code. Credit to https://github.com/naoisecollins/scarfyJump/blob/master/scarfyJump.cpp.
    {
        if (bullet[i].active)
            DrawRectangleRec(bullet[i].rect, bullet[i].color);
    }

    if (IsKeyDown(KEY_SPACE))
    {
        shootRate += 5;
        for (int i = 0; i <num_bullets; i++)
        {
            if (!bullet[i].active && shootRate % 40 == 0)
            {
				PlaySound(sound);
                bullet[i].rect.x = player.rect.x;
                bullet[i].rect.y = player.rect.y + player.rect.height / 4;
                bullet[i].active = true;
				break;
            }
        }
    }


    for (int i = 0; i < num_bullets; i++)
    {
        if (bullet[i].active)
        {
           
            bullet[i].rect.x += bullet[i].speed.y; //Change made: added speed to the X position of the bullet instead of the Y.

            if (bullet[i].rect.y <= 0) 
            {
                bullet[i].active = false;
                shootRate = 0;
            }
        }
    }
     for (int i = 0; i < num_bullets; i++)
    {
        if (bullet[i].active)
        { 
        if(CheckCollisionRecs(bullet[i].rect,boxA)){ //collision detection for enemies and obstacles
		dead_enemy = true;}} //attempt at getting the enemies to die when bullets collide with them
//End of credit.

if (((boxA.x + boxA.width) >= GetScreenWidth()) || (boxA.x <= 0)) boxASpeedX *= -1;
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

boxA.x += boxASpeedX; //Enemy movement. Credit to: https://www.raylib.com/examples.html "collision area". End of credit
ClearBackground(WHITE);
if (collision) {
 DrawText("Game Over",GetScreenHeight()/2.0f, GetScreenHeight()/2.0f, 50, PURPLE); //game over screen
}
else if (game_end){ //else if statement to allow for both the game over and game win scenarios occur without error
   DrawText("You win!",GetScreenHeight()/2.0f, GetScreenHeight()/2.0f, 50, PURPLE); //game win screen.
}
else{

DrawRectangleRec(player.rect,player.color); //draw the sprites if the game is not over
DrawRectangleRec(boxB, RED);
DrawRectangleRec(boxC, RED);
DrawRectangleRec(boxD, RED);
DrawRectangleRec(boxE, RED);
DrawRectangleRec(pit, PURPLE);
DrawRectangleRec(door, GREEN);
}

if (!have_key) {
DrawRectangleRec(key, YELLOW); //have the key disappear if the player picks it up, and have it be drawn if they have not.
}

if(!dead_enemy) {
DrawRectangleRec(boxA, GOLD);   
}

EndDrawing();
}
CloseAudioDevice(); 
CloseWindow();
}}
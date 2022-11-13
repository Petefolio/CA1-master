#include "raylib.h" //include the raylib library.
//Credit to https://github.com/naoisecollins/Lecture7/blob/master/lecture7.cpp.
struct Player { //A player structure which stores the variables for the player's rectangle, speed, and colour.
    Rectangle rect;
    Vector2 speed;
    Color color;
};
//End of Credit.

int main() {
const int windowWidth{800}; //setd the constant integer value for the width of the window.
const int windowHeight{500}; //sets the constant integer value for the height of the window.
InitWindow(windowWidth, windowHeight, "CA1"); //initializes the window and setting its name.
InitAudioDevice(); //initializes the audio device to allow for audio device management functions throughout the project.
SetTargetFPS(60); //sets the frame rate at which the game will aim to run.

Player player; //Player structure which stores all of the players meta data for the player's main variables inside.
player.rect.height= 35; //height of the rectangle.
player.rect.width = 35; //width of the rectangle.
player.color = BLUE; //colour of the rectangle.
player.rect.x = windowWidth/2; //the player's x position is halfway through the width of the whole window.
player.rect.y = windowHeight-player.rect.height; //the player's y position is he height of the window minus the player's height, meaning they are at the bottom of the window.
player.speed.x = 10; //the speed the player travels at along the x axis.
player.speed.y = 10; //the speed the player travels at along the y axis.

Music music = LoadMusicStream("resources/bg_music.wav"); //loads in the background music from the resources folder to be used later.
Sound sound = LoadSound("resources/collect.wav"); //loads in a pick up sound effect from the resources folder to be used later.
PlayMusicStream(music); //starts the music playing.

//Credit to: https://www.raylib.com/examples.html "collision area"
Rectangle enemy = { 10, GetScreenHeight()/2.0f - 50, 200, 100 }; //stores the x position, y position(slightly over halfway up the screen height), hight, and width of the enemy.
//Name  changed from "boxA" to "enemy".
int enemySpeedX = 4; //defines the speed at which the enemy moves.
//Name changed from "boxASpeedX" to "enemySpeedX".
//End of credit.

Rectangle obstacleA = { 100, GetScreenHeight()/4.0f - 100, 50, 50 }; //stores the x position, y position(slightly over halfway up the screen height), hight, and width of the obstacle.

Rectangle obstacleB = { 650, GetScreenHeight()/4.0f - 100, 50, 50 }; //stores the x position, y position(slightly over halfway up the screen height), hight, and width of the obstacle.

Rectangle obstacleC = { 600, GetScreenHeight()/1.1f - 100, 50, 50 }; //stores the x position, y position(slightly over halfway up the screen height), hight, and width of the obstacle.

Rectangle obstacleD = { 150, GetScreenHeight()/1.1f - 100, 50, 50 }; //stores the x position, y position(slightly over halfway up the screen height), hight, and width of the obstacle.

Rectangle pit = { 360, GetScreenHeight()/2.5f - 100, 80, 80 }; //stores the x position, y position(slightly over halfway up the screen height), hight, and width of the pit.

Rectangle key = { 500, GetScreenHeight()/2.5f - 100, 30, 30 }; //stores the x position, y position(slightly over halfway up the screen height), hight, and width of the key.

Rectangle door = {GetScreenWidth()/2.0f, GetScreenHeight()- 500, 60, 10 }; //stores the x position, y position(slightly over halfway up the screen height), hight, and width of the door.

bool collision{}; // boolean variable to detect whether or not a collision has occurred.
bool have_key{}; //a boolean variable to detect whether or not the player has picked up the key.
bool game_end{false}; //a boolean variable to detect whether or not the end of the game has been reached.


while(!WindowShouldClose()){ //everything within this while loop will occur while the window is open.

UpdateMusicStream(music); //updating the music stream allows for the music to play continuously while the game is open.

if(CheckCollisionRecs(player.rect,enemy)){ //if the player's rectangle comes into contact with the enemy's, the collision boolean is true.
		collision = true;
	}
if(CheckCollisionRecs(player.rect,obstacleA)){ //if the player's reectangle comes into contact with the obstacle's, the collision boolean is true.
		collision = true;
	}
if(CheckCollisionRecs(player.rect,obstacleB)){ //if the player's rectangle comes into contact with the obstacle's, the collision boolean is true.
		collision = true;
	}
if(CheckCollisionRecs(player.rect,obstacleC)){ //if the player's rectangle comes into contact with the obstacle's, the collision boolean is true.
		collision = true;
	}
if(CheckCollisionRecs(player.rect,obstacleD)){//if the player's rectangle comes into contact with the obstacle's, the collision boolean is true.
		collision = true;
	}
if(CheckCollisionRecs(player.rect,pit)){//if the player's rectangle comes into contact with the pit's, the collision boolean is true.
		collision = true;
	}
if(CheckCollisionRecs(player.rect,key)){ //if the player's rectangle comes into contact with the key's, they have picked up the key.
        PlaySound(sound); //a sound will play when the player's rectangle comes into contact with the key's.
        have_key = true; //the state of having the key is true.
}
if(CheckCollisionRecs(player.rect, door) && have_key){ 
    game_end = true; //if the player passes through the door after making the have_key boolean true by picking the key up, the game_end boolean will be true and the game will end.
}

//Credit to: https://www.raylib.com/examples.html "collision area".
if (((enemy.x + enemy.width) >= GetScreenWidth()) || (enemy.x <= 0)) enemySpeedX *= -1; //if the enemy comes into contact with the edge of the screen it will be sent back the other way and will do the same on the other side, causing it to move back and forth.
//End of Credit.

if (IsKeyDown(KEY_D)) //if the D key is held down, the player's x speed will be added to the player's x value and they will move right.
{
    player.rect.x = player.rect.x + player.speed.x;
}
if (IsKeyDown(KEY_A)) //if the A key is held down, the player's x speed will be taken from the player's x value and they will move left.
{
    player.rect.x = player.rect.x - player.speed.x;
}
if (IsKeyDown(KEY_S))//if the S key is held down, the player's y speed will be added to the player's y value and they will move down.
{
    player.rect.y = player.rect.y + player.speed.y;
}
if (IsKeyDown(KEY_W)) //if the W key is held down, the player's y speed will be taken to the player's y value and they will move up.
{
    player.rect.y = player.rect.y - player.speed.y;
}

BeginDrawing(); //initializes sprites to be drawn.

enemy.x += enemySpeedX; //the enemy's movement speed is added to the enemy's x value.
ClearBackground(WHITE); //sets the background colour.
if (collision) { //if the collision boolean is true then a game over screen will appear and the game will end.
 DrawText("Game Over!",GetScreenHeight()/2.0f, GetScreenHeight()/2.0f, 50, PURPLE); 
}
else if (game_end){ //else if statement to say that if the game_end boolean is true a game win screen will appear and the game will end.
   DrawText("You win!",GetScreenHeight()/2.0f, GetScreenHeight()/2.0f, 50, PURPLE); 
}
else{ //if these booleans are not true then the following will be drawn.

DrawRectangleRec(player.rect,player.color); //setting the measurements and colour of the player using the previously established variables from the player struct.
DrawRectangleRec(enemy, GOLD);
DrawRectangleRec(obstacleA, RED);
DrawRectangleRec(obstacleB, RED); //setting the measurements of the obstacles and enemy using the previously established variables from their Rectangle structs. Also setting their colours.
DrawRectangleRec(obstacleC, RED);
DrawRectangleRec(obstacleD, RED);
DrawRectangleRec(pit, PURPLE);
DrawRectangleRec(door, GREEN);
DrawText("Collect the yellow key and", 20, 80, 20, BLACK); //instructional text to be displayer in the upper left hand area of the window.
DrawText("escape through the green door!", 20, 100, 20, BLACK);//the bottom half of the instructional text to be displayer in the upper left hand area of the window.
}

if (!have_key) {
DrawRectangleRec(key, YELLOW); //have the key disappear if the player picks it up, and be drawn if they have not.
}

EndDrawing(); //stop drawing objects and text.
}
CloseAudioDevice(); //if what is contained within the above while loop stops, then close the audio device.
CloseWindow();//if what is contained within the above while loop stops, then close the window.
}
//
// Player
#define PLAYER_1_NAME "Player 1"
#define PLAYER_2_NAME "Player 2"

//
// Color theme
//
#define TRON_DARK \
    (Color) { .r = 0x23, .g = 0x21, .b = 0x1B, .a = 0xFF }
#define TRON_LIGHT_BLUE \
    (Color) { .r = 0xAC, .g = 0xE6, .b = 0xFE, .a = 0xFF }
#define TRON_BLUE \
    (Color) { .r = 0x6F, .g = 0xC3, .b = 0xDF, .a = 0xFF }
#define TRON_YELLOW \
    (Color) { .r = 0xFF, .g = 0xE6, .b = 0x4D, .a = 0xFF }
#define TRON_ORANGE \
    (Color) { .r = 0xFF, .g = 0x9F, .b = 0x1C, .a = 0xFF }
#define TRON_RED \
    (Color) { .r = 0xF4, .g = 0x47, .b = 0x47, .a = 0xFF }

//
// Game misc settings
//
#define GAME_FPS 60

//
// Game UI settings
//
#define GAME_UI_INIT_SCREEN_WIDTH 1024
#define GAME_UI_INIT_SCREEN_HEIGHT 768
#define GAME_UI_PADDING 10.0f
#define GAME_UI_BACKGROUND_COLOR TRON_DARK
#define GAME_UI_BORDER_COLOR TRON_LIGHT_BLUE
#define GAME_UI_RACKET_COLOR TRON_ORANGE

//
// Scoreboard UI settings
//
#define SCOREBOARD_UI_PADDING GAME_UI_PADDING
#define SCOREBOARD_UI_BORDER_COLOR TRON_LIGHT_BLUE
#define SCOREBOARD_UI_BORDER_HEIGHT_PERCENT 10
#define SCOREBOARD_UI_BORDER_THICKNESS 2.0f
#define SCOREBOARD_UI_VS_FONT_SIZE 30.f
#define SCOREBOARD_UI_VS_FONT_SPACE 10.0f
#define SCOREBOARD_UI_PLAYER_FONT_SPACE 5.0f
#define SCOREBOARD_UI_PLAYER_NAME_FONT_SIZE 30.f
#define SCOREBOARD_UI_PLAYER_SCORE_FONT_SIZE 50.f
#define SCOREBOARD_UI_SPACE_BETWEEN_NAME_AND_BORDER 50.f
#define SCOREBOARD_UI_SPACE_BETWEEN_NAME_AND_SCORE 50.f

//
// Table UI settings
//
#define TABLE_UI_MARGIN GAME_UI_PADDING
#define TABLE_UI_BORDER_COLOR TRON_LIGHT_BLUE
#define TABLE_UI_BORDER_THICKNESS 2.0f
#define TABLE_UI_START_PROMPT_BORDER_COLOR TRON_ORANGE
#define TABLE_UI_START_PROMPT_TEXT_COLOR TRON_ORANGE
#define TABLE_UI_START_PROMPT_TEXT "Press 'Space' to start the game"
#define TABLE_UI_START_PROMPT_FONT_SIZE 40.0f
#define TABLE_UI_START_PROMPT_FONT_SPACE 5.0f
#define TABLE_UI_START_PROMPT_CONTAINER_HORIZONTAL_PADDING 20.0f
#define TABLE_UI_START_PROMPT_CONTAINER_VERTICAL_PADDING 10.0f

//
// Ball UI settings
//
#define BALL_UI_BALL_COLOR TRON_LIGHT_BLUE
#define BALL_UI_FIREBALL_COLOR TRON_ORANGE
#define BALL_UI_BALL_RADIUS 30.f  // 20.0f
#define BALL_UI_BALL_VELOCITY_X 400.0f
#define BALL_UI_BALL_VELOCITY_Y 400.0f
// How many hits before increasing the ball velocity
#define BALL_UI_HITS_BEFORE_INCREASE_VELOCITY 2
// How many velocities increase to enable a fireball
#define BALL_UI_VELOCITIES_INCREASE_TO_ENABLE_FIREBALL 4
// Velocity acceleration
#define BALL_UI_VELOCITY_ACCELERATION 100
#define BALL_UI_LIGHTING_TAIL_PARTICLE_COUNT 50
// Init `alpha` value, it affects how light the particle at the beginning
#define BALL_UI_LIGHTING_TAIL_PRATICLE_INIT_ALPHA 0.8f
// It affects how big the particle will be: how many percentage of the ball
// size: 0.0 ~ 1.0 (0 ~ 100%)
#define BALL_UI_LIGHTING_TAIL_PRATICLE_SIZE 0.5f

//
// Racket UI settings
//
#define RACKET_UI_MAX_RACKETS_PER_PLAYER 5
#define RACKET_UI_MARGIN 20.f
#define RACKET_UI_WIDTH 40.f
#define RACKET_UI_HEIGHT 200.f
#define RACKET_UI_COLOR TRON_LIGHT_BLUE
#define RACKET_UI_VELOCITY 600.f
#define RACKET_UI_DRAW_DEBUG_BOUNDARY false

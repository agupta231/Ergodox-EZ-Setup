#include QMK_KEYBOARD_H
#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"

#include "keymap_german.h"
#include "keymap_nordic.h"

// Layers
enum layers {
	BASE = 0,
	NAV,
	SYMB,
	MATH,
	VIM,
	MAC,
	TMUX,
	GAME,
	GIT, 
	C_IDE,
	MINECRAFT
};

enum custom_keycodes {
	PLACEHOLDER = SAFE_RANGE, // can always be here
	EPRM,
	VRSN,
	RGB_SLD,
	VIM_MOVE_LEFT,
	VIM_MOVE_RIGHT,
	VIM_MOVE_UP,
	VIM_MOVE_DOWN,
	VIM_COPY,
	VIM_PASTE,
	VIM_SPELL,
	TMUX_SELECT_PANE_LEFT,
	TMUX_SELECT_PANE_RIGHT,
	TMUX_SELECT_PANE_UP,
	TMUX_SELECT_PANE_DOWN,
	TMUX_MOVE_PANE_LEFT,
	TMUX_MOVE_PANE_RIGHT,
	TMUX_MOVE_PANE_UP,
	TMUX_MOVE_PANE_DOWN,
	TMUX_EXPAND_PANE_LEFT,
	TMUX_EXPAND_PANE_RIGHT,
	TMUX_EXPAND_PANE_UP,
	TMUX_EXPAND_PANE_DOWN,
	TMUX_SPLIT_HORIZONTAL,
	TMUX_SPLIT_VERTICAL,
	TMUX_FOCUS_PANE,
	TMUX_PAUSE_TERM_OUTPUT,
	TMUX_DETACH,
	GIT_STATUS,
	GIT_ADD,
	GIT_COMMIT,
	C_CLOSE,
	C_SWITCH_FILE,
	C_TOGGLE_FULLSCREEN,
	C_GOTO_DEF,
	C_EXPAND_SNIPPET,
	C_PANE_LEFT,
	C_PANE_RIGHT,
	C_MOVE_LINE_UP,
	C_MOVE_LINE_DOWN,
	C_IMPORT_SYMBOL,
	C_COMMAND_PALLETTE,
	C_FORMAT_FILE,
	C_COMMENT,
	C_AUTOCOMPLETE,
	MC_SCROLL_NEXT
};

/**
 * ******************** LEGEND *******************
 *
 * There will be a lot of non standard abbrevaiations in this program. For anybody new, (or me,
 * after like, 2 days) these abbrebivations will make 0 sense. Over here, you can find out what
 * everything means. 
 *
 * If something still doesn't make sense, please open up an issue on my github. If you figure out
 * what the cyptic abbreviation means, by all means, open up a PR editing this legend.
 *
 *
 *
 * ************ Note about key layouts *********** 
 * All the keys are their standard keys, and work as if they are on a normal keyboard (shift works).
 * If something is different, it will be explicitly stated.
 *
 *
 *
 * ************ Legend ***************************
 * BUP = LED brightness up
 * BDOWN = LED brightness down
 * HOLD(<key>) = Outputs <key> if held, otherwise, outputs the other key
 * TG = Toggle Layer
 * MO = Only toggle selected layer when this key is held down
 * TT = Act as MO. If the key is just tapped, than toggle layer
 * ANIME = I swear this isn't what you think it is! Animates the LEDs on the keyboard.
 * H UP = Raise the hue of the LEDS
 * H DOWN = Lower the hue of the LEDS
 * V UP = Volume up
 * V DOWN = Volume down
 */


/* Keymap Blank Template
 * 
 * ,------------------------------------------------------.						,------------------------------------------------------.
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * |-----------+------+------+------+------+--------------|						|-------+------+------+------+------+------+-----------|
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * |-----------+------+------+------+------+------|				|						|				|------+------+------+------+------+-----------|
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * |					 |			|			 |			|			 |			|-------|						|-------|			 |			|			 |			|			 |					 |
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * |-----------+------+------+------+------+------|				|						|				|------+------+------+------+------+-----------|
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * `-----------+------+------+------+------+--------------'						` -------------+------+------+------+------+-----------'
 *			|			 |			|			 |			|			 |																				 |			|			 |			|			 |			|
 *			|			 |			|			 |			|			 |																				 |			|			 |			|			 |			|
 *			|			 |			|			 |			|			 |																				 |			|			 |			|			 |			|
 *			`----------------------------------'																				 `----------------------------------'
 *																				 ,-------------.					 ,-------------.
 *																				 |			|			 |					 |			|			 |
 *																				 |			|			 |					 |			|			 |
 *																				 |			|			 |					 |			|			 |
 *																	,------|------|------|					 |------+------+------.
 *																	|			 |			|			 |					 |			|			 |			|
 *																	|			 |			|			 |					 |			|			 |			|
 *																	|			 |			|			 |					 |			|			 |			|
 *																	|			 |			|------|					 |------|			 |			|
 *																	|			 |			|			 |					 |			|			 |			|
 *																	|			 |			|			 |					 |			|			 |			|
 *																	|			 |			|			 |					 |			|			 |			|
 *																	`--------------------'					 `--------------------'
 */

/* Keymap Blank Template
 
	[TMUX] = LAYOUT_ergodox(
			// Left hand
			KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,
			KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,
			KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,
			KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,
			KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,
			
																																				//Left thumb cluster
																																				KC_TRANSPARENT,					 KC_TRANSPARENT,
																																																 KC_TRANSPARENT,
																																				KC_TRANSPARENT,					 KC_TRANSPARENT,
																																				KC_TRANSPARENT,
			
							//Right hand
							KC_TRANSPARENT,					 KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,
							KC_TRANSPARENT,					 KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,
																			 KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,
							KC_TRANSPARENT,					 KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,
											KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,
		
							// Right thumb cluster
							KC_TRANSPARENT,					KC_TRANSPARENT,
							KC_TRANSPARENT,
							KC_TRANSPARENT,					KC_TRANSPARENT,  KC_TRANSPARENT),

*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Keymap 0: Base
 *
 * ,------------------------------------------------------.						,------------------------------------------------------.
 * |		 `		 |	1		|  2	 |	3		|		4  |	5		|  BUP	|						| BDOWN |		6  | 7		|  8	 |	9		|  0	 | CAPS LCK  |
 * |-----------+------+------+------+------+--------------|						|-------+------+------+------+------+------+-----------|
 * |		TAB		 |	Q		|  W	 |	E		|  R	 |	T		|		-		|						|		~		|  Y	 |	U		|  I	 |	O		|  P	 |		\			 |
 * |					 |			|			 |			|			 | HOLD |				|						|				|			 |			|			 |			|			 |					 |
 * |					 |			|			 |			|			 | TMUX |				|						|				|			 |			|			 |			|			 |					 |
 * |-----------+------+------+------+------+------|				|						|				|------+------+------+------+------+-----------|
 * |		ESC		 |	A		|  S	 |	D		|  F	 |	G		|-------|						|-------|  H	 |	J		|  K	 |	L		|  ;	 |		'			 |
 * | HOLD(CMD) |			|			 |			|			 | HOLD	|		*		|						|		`		|			 |			|			 |			|			 |					 |
 * |	         |			|			 |			|			 | GIT  |		 		|						|		 		|			 |			|			 |			|			 |					 |
 * |-----------+------+------+------+------+------| HOLD( |						| HOLD( |------+------+------+------+------+-----------|
 * |	 SHIFT	 |	Z		|  X	 |	C		|  V	 |	B		| LALT) |						| RALT) |  N	 |	M		|  ,	 |	.		|  /	 |	SHIFT		 |
 * |					 |			|			 | HOLD | HOLD |			|				|						|				|			 |			|			 |			|			 |					 |
 * |					 |			|			 | C-IDE|(VIM) |			|				|						|				|			 |			|			 |			|			 |					 |
 * `-----------+------+------+------+------+--------------'						` -------------+------+------+------+------+-----------'
 *			| MINE | SYMB | NAV  |	MAC | GAME |																	     | DOWN |  UP  | SYMB | <-	 |	->	|
 *			|  TG  |	MO	|  TT  |	MO	|	 TG	 |																			 | ARROW| ARROW| MO		|			 |			|
 *			`----------------------------------'																			 `----------------------------------'
 *																				 ,-------------.					 ,-------------.
 *																				 |ANIME | H UP |					 | V UP | MUTE |
 *																	,------|------|------|					 |------+------+------.
 *																	|BACK  |	D		|H DOWN|					 |V DOWN| ENTER|			|
 *																	|SPACE |	E		|------|					 |------|			 | SPACE|
 *																	|			 |	L		| CTRL |					 | CMD	|			 |			|
 *																	`--------------------'					 `--------------------'
 */

	[BASE] = LAYOUT_ergodox(
			// Left Hand
			KC_GRAVE,					 KC_1,	    KC_2,	    KC_3,	           KC_4,						  KC_5,		         RGB_VAD,
			KC_TAB,						 KC_Q,	    KC_W,	    KC_E,	           KC_R,						  LT(TMUX, KC_T),	 KC_MINUS,
			GUI_T(KC_ESCAPE),  KC_A,	    KC_S,	    KC_D,	           KC_F,						  LT(GIT, KC_G),
			KC_LSHIFT,				 KC_Z,	    KC_X,	    LT(C_IDE, KC_C), LT(VIM, KC_V),			KC_B,			       ALT_T(KC_KP_ASTERISK),
			TO(MINECRAFT),		 MO(SYMB),	TT(NAV),	MO(MAC),	       TO(GAME),
			
																																				// Left hand cluster
																																				RGB_MOD,					RGB_HUI,
																																													RGB_HUD,
																																				KC_BSPACE,				KC_DELETE,
																																				KC_LCTL,
		
							// Right hand
							RGB_VAI,					KC_6,		KC_7,		KC_8,			 KC_9,			 KC_0,							KC_CAPSLOCK,
							KC_TILD,					KC_Y,		KC_U,		KC_I,			 KC_O,			 KC_P,							KC_BSLASH,
											KC_H,			KC_J,		KC_K,		KC_L,			 KC_SCOLON,  RCTL_T(KC_QUOTE),
							ALT_T(KC_GRAVE),		 KC_N,	 KC_M,	 KC_COMMA,	KC_DOT,			KC_SLASH,					 KC_RSHIFT,
											KC_DOWN,	KC_UP,	MO(SYMB),  KC_LEFT,		KC_RIGHT,
			
							// Right thumb cluster
							KC_AUDIO_VOL_UP,				KC_AUDIO_MUTE,
							KC_AUDIO_VOL_DOWN,
							KC_LGUI,								KC_ENTER,				KC_SPACE),

/* Keymap 1: Navigation
 * 
 * ,------------------------------------------------------.						,------------------------------------------------------.
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * |-----------+------+------+------+------+--------------|						|-------+------+------+------+------+------+-----------|
 * |					 |			|			 |			|			 |			|				|						|				|mouse |mouse |mouse |mouse |			 |					 |
 * |					 |			|			 |			|			 |			|				|						|page		|wheel |wheel |wheel |wheel |			 |					 |
 * |					 |			|			 |			|			 |			|				|						|up			|left  |up		|down  |right |			 |					 |
 * |-----------+------+------+------+------+------|				|						|				|------+------+------+------+------+-----------|
 * |					 |			|			 |PAUSE |PREV  |NEXT  |				|						|				|mouse |mouse |mouse |mouse |			 |					 |
 * |					 |			|			 |MUSIC |TRACK |TRACK |-------|						|-------|left  | down |up		 |right |			 |					 |
 * |					 |			|			 |      |			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * |-----------+------+------+------+------+------|				|						|page		|------+------+------+------+------+-----------|
 * |					 |			|			 |Accel |Accel |Accel |				|						|down		|			 |down	|  ^	 |			|			 |					 |
 * |					 |			|			 | 0		| 2		 | 1		|				|						|				| <-	 |arrow |  |	 | ->		|			 |					 |
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * `-----------+------+------+------+------+--------------'						` -------------+------+------+------+------+-----------'
 *			|			 |			|			 |			|			 |																				 |			|			 |			|			 |			|
 *			|			 |			|			 |			|			 |																				 |			|			 |			|			 |			|
 *			|			 |			|			 |			|			 |																				 |			|			 |			|			 |			|
 *			`----------------------------------'																				 `----------------------------------'
 *																				 ,-------------.					 ,-------------.
 *																				 |			|			 |					 |			|			 |
 *																				 |			|			 |					 |			|			 |
 *																				 |			|			 |					 |			|			 |
 *																	,------|------|------|					 |------+------+------.
 *																	|			 |			|			 |					 |			|			 |			|
 *																	|right |			|			 |					 |			|			 |left	|
 *																	|mouse |			|			 |					 |			|			 |mouse |
 *																	|click |			|------|					 |------|			 |click |
 *																	|			 |			|			 |					 |			|			 |			|
 *																	|			 |			|			 |					 |			|			 |			|
 *																	|			 |			|			 |					 |			|			 |			|
 *																	`--------------------'					 `--------------------'
 */
	[NAV] = LAYOUT_ergodox(
			// Left hand
			KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,
			KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,
			KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,  KC_MEDIA_PLAY_PAUSE,	KC_MEDIA_REWIND, KC_MEDIA_FAST_FORWARD,
			KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,  KC_MS_ACCEL0,		KC_MS_ACCEL2,		 KC_MS_ACCEL1,		KC_TRANSPARENT,
			KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,
			
																																				//Left thumb cluster
																																				KC_TRANSPARENT,					 KC_TRANSPARENT,
																																																 KC_TRANSPARENT,
																																				KC_MS_BTN2,							 KC_TRANSPARENT,
																																				KC_TRANSPARENT,
			
							//Right hand
							KC_TRANSPARENT,					 KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,
							KC_PGUP,								 KC_MS_WH_LEFT,		KC_MS_WH_UP,		 KC_MS_WH_DOWN,		KC_MS_WH_RIGHT,  KC_TRANSPARENT,	KC_TRANSPARENT,
											KC_MS_LEFT,			 KC_MS_DOWN,			KC_MS_UP,				 KC_MS_RIGHT,			KC_TRANSPARENT,  KC_TRANSPARENT,
							KC_PGDOWN,							 KC_LEFT,					KC_DOWN,				 KC_UP,						KC_RIGHT,				 KC_TRANSPARENT,	KC_TRANSPARENT,
											KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,
		
							// Right thumb cluster
							KC_TRANSPARENT,					KC_TRANSPARENT,
							KC_TRANSPARENT,
							KC_TRANSPARENT,					KC_TRANSPARENT,  KC_MS_BTN1),



/* Keymap 2: Symbols
 * 
 * ,------------------------------------------------------.						,------------------------------------------------------.
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * |					 | f16	| f15  | f14	|  f13 |			|				|						|				|			 |			|			 |			|			 |					 |
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * |-----------+------+------+------+------+--------------|						|-------+------+------+------+------+------+-----------|
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * |					 | f12	| f11  | f10	| f9	 |			|				|						|				|  #	 |	[		|  ]	 |	&		|  |	 |	  ^			 |
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * |-----------+------+------+------+------+------|				|						|				|------+------+------+------+------+-----------|
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * |					 | f8		| f7	 | f6		| f5	 |			|-------|						|-------|  @	 |	(		|  )	 |	!		|  =	 |	  %			 |
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * |-----------+------+------+------+------+------|				|						|				|------+------+------+------+------+-----------|
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * |					 | f4		| f3	 | f2		| f1	 |			|				|						|				|  $	 |	{		|  }	 |	+		|  -	 |	    		 |
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * `-----------+------+------+------+------+--------------'						` -------------+------+------+------+------+-----------'
 *			|			 |			|			 |			|			 |																				 |			|			 |			|			 |			|
 *			|			 |			|			 |			|			 |																				 |			|			 |			|			 |			|
 *			|			 |			|			 |			|			 |																				 |			|			 |			|			 |			|
 *			`----------------------------------'																				 `----------------------------------'
 *																				 ,-------------.					 ,-------------.
 *																				 |			|			 |					 |			|			 |
 *																				 |			|			 |					 |			|			 |
 *																				 |			|			 |					 |			|			 |
 *																	,------|------|------|					 |------+------+------.
 *																	|			 |			|			 |					 |			|			 |			|
 *																	|			 |			|			 |					 |			|			 |			|
 *																	|			 |			|			 |					 |			|			 |			|
 *																	|			 |			|------|					 |------|			 |			|
 *																	|			 |			|			 |					 |			|			 |			|
 *																	|			 |			|			 |					 |			|			 |			|
 *																	|			 |			|			 |					 |			|			 |			|
 *																	`--------------------'					 `--------------------'
 */

	[SYMB] = LAYOUT_ergodox(
			//Left hand
			KC_TRANSPARENT,  KC_F16,					KC_F15,					 KC_F14,					KC_F13,					 KC_TRANSPARENT,	KC_TRANSPARENT,
			KC_TRANSPARENT,  KC_F12,					KC_F11,					 KC_F10,					KC_F9,					 KC_TRANSPARENT,	KC_TRANSPARENT,
			KC_TRANSPARENT,  KC_F8,						KC_F7,					 KC_F6,						KC_F5,					 KC_TRANSPARENT,
			KC_TRANSPARENT,  KC_F4,						KC_F3,					 KC_F2,						KC_F1,					 KC_TRANSPARENT,	KC_TRANSPARENT,
			KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,

																																				// Left thumb cluster
																																				KC_TRANSPARENT,					 KC_TRANSPARENT,
																																								KC_TRANSPARENT,
																																				KC_TRANSPARENT,					 KC_TRANSPARENT,
																																				KC_TRANSPARENT,

							// Right hand
							KC_TRANSPARENT,					 KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,
							KC_TRANSPARENT,					 KC_HASH,					KC_LBRACKET,		 KC_RBRACKET,			KC_AMPR,				 KC_PIPE,					KC_CIRCUMFLEX,
											KC_AT,					 KC_LPRN,					KC_RPRN,				 KC_EXLM,					KC_EQUAL,				 KC_PERCENT,
							KC_TRANSPARENT,					 KC_DLR,					KC_LCBR,				 KC_RCBR,					KC_PLUS,				 KC_MINUS,				KC_TRANSPARENT,
											KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,
			
							// Right thumb cluster
							KC_TRANSPARENT,  KC_TRANSPARENT,
							KC_TRANSPARENT,
							KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT),

/* Keymap 3: Math
 * 
 * ,------------------------------------------------------.						,------------------------------------------------------.
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * |-----------+------+------+------+------+--------------|						|-------+------+------+------+------+------+-----------|
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * |					 |			|  -	 |	(		|  )	 |			|				|						|				|			 |	7		|  8	 |	9		|			 |					 |
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * |-----------+------+------+------+------+------|				|						|				|------+------+------+------+------+-----------|
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * |					 |	/		|  *	 |	-		|  +	 |			|-------|						|-------|			 |	4		|  5	 |	6		|			 |					 |
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * |-----------+------+------+------+------+------|				|						|				|------+------+------+------+------+-----------|
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * |					 |			|			 |			|			 |			|				|						|				|			 |	1		|  2	 |	3		|			 |					 |
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * `-----------+------+------+------+------+--------------'						` -------------+------+------+------+------+-----------'
 *			|			 |			|			 |			|			 |																				 |			|			 |			|			 |			|
 *			|			 |			|			 |			|			 |																				 |	.		|  0	 |	$		|			 |			|
 *			|			 |			|			 |			|			 |																				 |			|			 |			|			 |			|
 *			`----------------------------------'																				 `----------------------------------'
 *																				 ,-------------.					 ,-------------.
 *																				 |			|			 |					 |			|			 |
 *																				 |			|			 |					 |			|			 |
 *																				 |			|			 |					 |			|			 |
 *																	,------|------|------|					 |------+------+------.
 *																	|			 |			|			 |					 |			|			 |			|
 *																	|			 |			|			 |					 |			|			 |			|
 *																	|back  | DEL	|			 |					 |			|			 |			|
 *																	|space |			|------|					 |------| enter| tab	|
 *																	|			 |			|			 |					 |			|			 |			|
 *																	|			 |			|			 |					 |			|			 |			|
 *																	|			 |			|			 |					 |			|			 |			|
 *																	`--------------------'					 `--------------------'
 */
	[MATH] = LAYOUT_ergodox(
			//Left hand
			KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,
			KC_TRANSPARENT,  KC_TRANSPARENT,	KC_KP_MINUS,		 KC_LPRN,					KC_RPRN,				 KC_TRANSPARENT,	KC_TRANSPARENT,
			KC_TRANSPARENT,  KC_KP_SLASH,			KC_KP_ASTERISK,  KC_KP_MINUS,			KC_KP_PLUS,			 KC_TRANSPARENT,
			KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,
			KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,
			
																																				// Left thumb cluster
																																				KC_TRANSPARENT,					 KC_TRANSPARENT,
																																								KC_TRANSPARENT,
																																				KC_BSPACE,							 KC_DELETE,
																																				KC_TRANSPARENT,
			
							// Right hand
							KC_TRANSPARENT,					 KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,
							KC_TRANSPARENT,					 KC_TRANSPARENT,	KC_7,						 KC_8,						KC_9,						 KC_TRANSPARENT,	KC_TRANSPARENT,
											KC_TRANSPARENT,  KC_4,						KC_5,						 KC_6,						KC_TRANSPARENT,  KC_TRANSPARENT,
							KC_TRANSPARENT,					 KC_TRANSPARENT,	KC_1,						 KC_2,						KC_3,						 KC_TRANSPARENT,	KC_TRANSPARENT,
											KC_DOT,					 KC_0,						KC_DLR,					 KC_TRANSPARENT,	KC_TRANSPARENT,
											
							// Right thumb cluster
							KC_TRANSPARENT,  KC_TRANSPARENT,
							KC_TRANSPARENT,
							KC_TRANSPARENT,  KC_KP_ENTER,			KC_TAB),

/* Keymap 4: VIM
 * 
 * ,------------------------------------------------------.						,------------------------------------------------------.
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * |-----------+------+------+------+------+--------------|						|-------+------+------+------+------+------+-----------|
 * |					 |			|			 |			|			 |			|				|						|				|MOVE  |MOVE	|MOVE  |MOVE	|PASTE |					 |
 * |					 |			|			 |			|			 |			|				|						|				|PANE  |PANE	|PANE  |PANE	| FROM |					 |
 * |					 |			|			 |			|			 |			|				|						|				|LEFT  |DOWN	|UP		 |RIGHT |CLIPBD|					 |
 * |-----------+------+------+------+------+------|				|						|				|------+------+------+------+------+-----------|
 * |					 |			|SPELL |			|			 |			|				|						|				| CNTl | CNTl | CNTl | CNTl |			 |					 |
 * |					 |			|CHECK |			|			 |			|-------|						|-------|			 |			|			 |			|			 |					 |
 * |					 |			|WORD  |			|			 |			|				|						|				|  h	 |	j		|  k	 |	l		|			 |					 |
 * |-----------+------+------+------+------+------|				|						|				|------+------+------+------+------+-----------|
 * |					 |			|			 |COPY	|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * |					 |			|			 | TO		|			 |			|				|						|				|  f9  |	f8	|  f7  |	f10 |			 |					 |
 * |					 |			|			 |CLIPBD|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * `-----------+------+------+------+------+--------------'						` -------------+------+------+------+------+-----------'
 *			|			 |			|			 |			|			 |																				 |			|			 |			|			 |			|
 *			|			 |			|			 |			|			 |																				 |			|			 |			|			 |			|
 *			|			 |			|			 |			|			 |																				 |			|			 |			|			 |			|
 *			`----------------------------------'																				 `----------------------------------'
 *																				 ,-------------.					 ,-------------.
 *																				 |			|			 |					 |			|			 |
 *																				 |			|			 |					 |			|			 |
 *																				 |			|			 |					 |			|			 |
 *																	,------|------|------|					 |------+------+------.
 *																	|			 |			|			 |					 |			|			 |			|
 *																	|			 |			|			 |					 |			|			 |			|
 *																	|			 |			|			 |					 |			|			 |			|
 *																	|			 |			|------|					 |------|			 |			|
 *																	|			 |			|			 |					 |			|			 |			|
 *																	|			 |			|			 |					 |			|			 |			|
 *																	|			 |			|			 |					 |			|			 |			|
 *																	`--------------------'					 `--------------------'
 */
	[VIM] = LAYOUT_ergodox(
			//Left hand
			KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,
			KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,
			KC_TRANSPARENT,  KC_TRANSPARENT,	VIM_SPELL,       KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,
			KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,  VIM_COPY,				KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,
			KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,
			
																																				// Left thumb cluster
																																				KC_TRANSPARENT,					 KC_TRANSPARENT,
																																								KC_TRANSPARENT,
																																				KC_TRANSPARENT,					 KC_TRANSPARENT,
																																				KC_TRANSPARENT,

							// Right hand
							KC_TRANSPARENT,		KC_TRANSPARENT,			KC_TRANSPARENT,			KC_TRANSPARENT,			KC_TRANSPARENT,			KC_TRANSPARENT,		KC_TRANSPARENT,
							KC_TRANSPARENT,		VIM_MOVE_LEFT,			VIM_MOVE_DOWN,			 VIM_MOVE_UP,				 VIM_MOVE_RIGHT,		VIM_PASTE,	 KC_TRANSPARENT,
																LCTL(KC_H),					LCTL(KC_J),					LCTL(KC_K),					LCTL(KC_L),					KC_TRANSPARENT,			KC_TRANSPARENT,
							KC_TRANSPARENT,		KC_F9,							KC_F8,							KC_F7,							KC_F10,							KC_TRANSPARENT,		KC_TRANSPARENT,
																KC_TRANSPARENT,		KC_TRANSPARENT,			KC_TRANSPARENT,			KC_TRANSPARENT,			KC_TRANSPARENT,
											
							// Right thumb cluster
							KC_TRANSPARENT,  KC_TRANSPARENT,
							KC_TRANSPARENT,
							KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT),

/* Keymap 5: MacOS + Magnet App integration
 * 
 * ,------------------------------------------------------.						,------------------------------------------------------.
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * |-----------+------+------+------+------+--------------|						|-------+------+------+------+------+------+-----------|
 * |					 |			|			 |			|			 |			|				|						|				|top	 |left	|right |top		|			 |					 |
 * |					 |			|			 |			|			 |			|				|						|				|left  |third |third |right |			 | revert		 |
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * |-----------+------+------+------+------+------|				|						|				|------+------+------+------+------+-----------|
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * |					 |			|			 |			|			 |			|-------|						|-------|left  | down |  up  | right|center|maximize	 |
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * |-----------+------+------+------+------+------|				|						|				|------+------+------+------+------+-----------|
 * |					 |			|			 |			|			 |			|				|						|				|bottom| left |right |bottom|			 |					 |
 * |					 |			|			 |			|			 |			|				|						|				|left  | two	|two	 |right |			 |					 |
 * |					 |			|			 |			|			 |			|				|						|				|			 |thirds|thirds|			|			 |					 |
 * `-----------+------+------+------+------+--------------'						` -------------+------+------+------+------+-----------'
 *			|			 |			|			 |			|			 |																				 |prev	|next  |space |space |			|
 *			|			 |			|			 |			|			 |																				 |disply|disp  |left	|right |			|
 *			|			 |			|			 |			|			 |																				 |			|			 |			|			 |			|
 *			`----------------------------------'																				 `----------------------------------'
 *																				 ,-------------.					 ,-------------.
 *																				 |			|			 |					 |			|			 |
 *																				 |			|			 |					 |			|			 |
 *																				 |			|			 |					 |			|			 |
 *																	,------|------|------|					 |------+------+------.
 *																	|			 |			|			 |					 |			|			 |			|
 *																	|			 |			|			 |					 |			|			 |			|
 *																	|			 |			|			 |					 |			|			 |			|
 *																	|			 |			|------|					 |------|			 |			|
 *																	|			 |			|			 |					 |			|			 |			|
 *																	|			 |			|			 |					 |			|			 |			|
 *																	|			 |			|			 |					 |			|			 |			|
 *																	`--------------------'					 `--------------------'
 */
	[MAC] = LAYOUT_ergodox(
			//Left hand
			KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,
			KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,
			KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,
			KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,
			KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,
			
			// Left thumb cluster
			KC_TRANSPARENT,KC_TRANSPARENT,
							KC_TRANSPARENT,
			KC_TRANSPARENT,KC_TRANSPARENT,
			KC_TRANSPARENT,
			
			// Right hand
			KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,
			KC_TRANSPARENT,  LALT(LCTL(KC_U)),LALT(LCTL(KC_D)),LALT(LCTL(KC_G)),LALT(LCTL(KC_I)),LCTL(KC_UP),LALT(LCTL(KC_BSPACE)),
							LALT(LCTL(KC_LEFT)),LALT(LCTL(KC_DOWN)),LALT(LCTL(KC_UP)),LALT(LCTL(KC_RIGHT)),LALT(LCTL(KC_C)),LALT(LCTL(KC_ENTER)),
			KC_TRANSPARENT,		LALT(LCTL(KC_J)),LALT(LCTL(KC_E)),LALT(LCTL(KC_T)),LALT(LCTL(KC_K)),LCTL(KC_DOWN),KC_TRANSPARENT,
							LALT(LCTL(LGUI(KC_LEFT))),LALT(LCTL(LGUI(KC_RIGHT))),LCTL(KC_LEFT),LCTL(KC_RIGHT),KC_TRANSPARENT,
							
			// Right thumb cluster
			KC_TRANSPARENT,KC_TRANSPARENT,
			KC_TRANSPARENT,
			KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT),

/* Keymap 6: TMUX
 * 
 * ,------------------------------------------------------.						,------------------------------------------------------.
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * |-----------+------+------+------+------+--------------|						|-------+------+------+------+------+------+-----------|
 * |					 |			|			 |			|			 |			|				|						|				|MOVE  |MOVE	|MOVE  |MOVE	|PAUSE |					 |
 * |					 |			|			 |			|			 |			|				|						| SPLIT |PANE  |PANE	|PANE  |PANE	|TERM  |					 |
 * |					 |			|			 |			|			 |			|				|						| VERT	|LEFT  |DOWN	|UP		 |RIGHT |OUTPUT|					 |
 * |-----------+------+------+------+------+------|				|						|				|------+------+------+------+------+-----------|
 * |					 |			|			 | TMUX |			 |			|				|						|				|SELECT|SELECT|SELECT|SELECT|			 | SPLIT		 |
 * |					 |			|			 |			|			 |			|-------|						|-------|PANE  | PANE | PANE | PANE |			 | HORIZONTAL|
 * |					 |			|			 |DETACH|			 |			|				|						|				|LEFT  | DOWN |  UP  | RIGHT|			 |					 |
 * |-----------+------+------+------+------+------|				|						| FOCUS |------+------+------+------+------+-----------|
 * |					 |			|			 |			|			 |			|				|						| PANE	|EXPAND|EXPAND|EXPAND|EXPAND|			 |					 |
 * |					 |			|			 |			|			 |			|				|						|				|PANE  | PANE | PANE | PANE |			 |					 |
 * |					 |			|			 |			|			 |			|				|						|				|LEFT  | DOWN |  UP  | RIGHT|			 |					 |
 * `-----------+------+------+------+------+--------------'						` -------------+------+------+------+------+-----------'
 *			|			 |			|			 |			|			 |																				 |			|			 |			|			 |			|
 *			|			 |			|			 |			|			 |																				 |			|			 |			|			 |			|
 *			|			 |			|			 |			|			 |																				 |			|			 |			|			 |			|
 *			`----------------------------------'																				 `----------------------------------'
 *																				 ,-------------.					 ,-------------.
 *																				 |			|			 |					 |			|			 |
 *																				 |			|			 |					 |			|			 |
 *																				 |			|			 |					 |			|			 |
 *																	,------|------|------|					 |------+------+------.
 *																	|			 |			|			 |					 |			|			 |			|
 *																	|			 |			|			 |					 |			|			 |			|
 *																	|			 |			|			 |					 |			|			 |			|
 *																	|			 |			|------|					 |------|			 |			|
 *																	|			 |			|			 |					 |			|			 |			|
 *																	|			 |			|			 |					 |			|			 |			|
 *																	|			 |			|			 |					 |			|			 |			|
 *																	`--------------------'					 `--------------------'
 */

	[TMUX] = LAYOUT_ergodox(
			// Left hand
			KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,
			KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,
			KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,  TMUX_DETACH,			KC_TRANSPARENT,  KC_TRANSPARENT,
			KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,
			KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,
			
																																				//Left thumb cluster
																																				KC_TRANSPARENT,					 KC_TRANSPARENT,
																																																 KC_TRANSPARENT,
																																				KC_TRANSPARENT,					 KC_TRANSPARENT,
																																				KC_TRANSPARENT,
			
							//Right hand
							KC_TRANSPARENT,					 KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,
							TMUX_SPLIT_VERTICAL,		 TMUX_MOVE_PANE_LEFT,  TMUX_MOVE_PANE_DOWN,  TMUX_MOVE_PANE_UP,  TMUX_MOVE_PANE_RIGHT,	TMUX_PAUSE_TERM_OUTPUT,  KC_TRANSPARENT,
																			 TMUX_SELECT_PANE_LEFT,  TMUX_SELECT_PANE_DOWN,  TMUX_SELECT_PANE_UP,  TMUX_SELECT_PANE_RIGHT,	KC_TRANSPARENT,  TMUX_SPLIT_HORIZONTAL,
							TMUX_FOCUS_PANE,				 TMUX_EXPAND_PANE_LEFT,  TMUX_EXPAND_PANE_DOWN,  TMUX_EXPAND_PANE_UP,  TMUX_EXPAND_PANE_RIGHT,	KC_TRANSPARENT,  KC_TRANSPARENT,
											KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,
		
							// Right thumb cluster
							KC_TRANSPARENT,					KC_TRANSPARENT,
							KC_TRANSPARENT,
							KC_TRANSPARENT,					KC_TRANSPARENT,  KC_TRANSPARENT),


/* Keymap 7: GAME
 * 
 * ,------------------------------------------------------.						,------------------------------------------------------.
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * |					 |  1		|	 2	 |	3 	|	 4	 |	5 	|				|						|				|			 |			|			 |			|			 |					 |
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * |-----------+------+------+------+------+--------------|						|-------+------+------+------+------+------+-----------|
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * | TAB  		 |  Q		|	 W	 |	E 	|	 R   |	T 	|				|						|				|			 |			|			 |			|			 |					 |
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * |-----------+------+------+------+------+------|				|						|				|------+------+------+------+------+-----------|
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * | L ALT		 |  A		|	 S	 |	D 	|	 F	 |	G 	|-------|						|-------|			 |			|			 |			|			 |					 |
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * |-----------+------+------+------+------+------|				|						|				|------+------+------+------+------+-----------|
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * | L SHIFT	 |	Z 	|	 X	 |	C 	|	 V	 |	B 	|				|						|				|			 |			|			 |			|			 |					 |
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * `-----------+------+------+------+------+--------------'						` -------------+------+------+------+------+-----------'
 *			| BASE |			|			 |			|			 |																				 |			|			 |			|			 |			|
 *			|	T0	 | F1		|	 F2	 |	F3	|	 F4	 |																				 |			|			 |			|			 |			|
 *			|			 |			|			 |			|			 |																				 |			|			 |			|			 |			|
 *			`----------------------------------'																				 `----------------------------------'
 *																				 ,-------------.					 ,-------------.
 *																				 |			|			 |					 |			|			 |
 *																				 |			|			 |					 |			|			 |
 *																				 |			|			 |					 |			|			 |
 *																	,------|------|------|					 |------+------+------.
 *																	|			 |			|			 |					 |			|			 |			|
 *																	|	 S	 |			|			 |					 |			|			 |			|
 *																	|	 P	 |  C		|			 |					 |			|			 |			|
 *																	|	 A	 |  N		|------|					 |------|			 |			|
 *																	|	 C	 |  T		|			 |					 |			|			 |			|
 *																	|	 E	 |  L		|			 |					 |			|			 |			|
 *																	|			 |			|			 |					 |			|			 |			|
 *																	`--------------------'					 `--------------------'
 */

	[GAME] = LAYOUT_ergodox(
			// Left Hand
			KC_TRANSPARENT,		 KC_1,	 KC_2,	 KC_3,	 KC_4,						KC_5,		KC_TRANSPARENT,
			KC_TAB,						 KC_Q,	 KC_W,	 KC_E,	 KC_R,						KC_T,		KC_TRANSPARENT,
			KC_LALT,           KC_A,	 KC_S,	 KC_D,	 KC_F,						KC_G,
			KC_LSHIFT,				 KC_Z,	 KC_X,	 KC_C,	 KC_V,			      KC_B,		KC_TRANSPARENT,	
			TO(BASE),					 KC_F1,	 KC_F2,	 KC_F3,	 KC_F4,
			
																																				// Left hand cluster
																																				KC_TRANSPARENT,	  KC_TRANSPARENT,
																																													KC_TRANSPARENT,
																																				KC_SPACE,				  KC_LCTRL,
																																				KC_TRANSPARENT,
							//Right hand
							KC_TRANSPARENT,					 KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,
							KC_TRANSPARENT,					 KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,
																			 KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,
							KC_TRANSPARENT,					 KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,
											KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,
		
							// Right thumb cluster
							KC_TRANSPARENT,					KC_TRANSPARENT,
							KC_TRANSPARENT,
							KC_TRANSPARENT,					KC_TRANSPARENT,  KC_TRANSPARENT),

/* Git Keymap
 * 
 * ,------------------------------------------------------.						,------------------------------------------------------.
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * |-----------+------+------+------+------+--------------|						|-------+------+------+------+------+------+-----------|
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * |-----------+------+------+------+------+------|				|						|				|------+------+------+------+------+-----------|
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * |					 | ADD  |STATUS|			|			 |			|-------|						|-------|			 |			|			 |			|			 |					 |
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * |-----------+------+------+------+------+------|				|						|				|------+------+------+------+------+-----------|
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * |					 |			|			 |COMMIT|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * `-----------+------+------+------+------+--------------'						` -------------+------+------+------+------+-----------'
 *			|			 |			|			 |			|			 |																				 |			|			 |			|			 |			|
 *			|			 |			|			 |			|			 |																				 |			|			 |			|			 |			|
 *			|			 |			|			 |			|			 |																				 |			|			 |			|			 |			|
 *			`----------------------------------'																				 `----------------------------------'
 *																				 ,-------------.					 ,-------------.
 *																				 |			|			 |					 |			|			 |
 *																				 |			|			 |					 |			|			 |
 *																				 |			|			 |					 |			|			 |
 *																	,------|------|------|					 |------+------+------.
 *																	|			 |			|			 |					 |			|			 |			|
 *																	|			 |			|			 |					 |			|			 |			|
 *																	|			 |			|			 |					 |			|			 |			|
 *																	|			 |			|------|					 |------|			 |			|
 *																	|			 |			|			 |					 |			|			 |			|
 *																	|			 |			|			 |					 |			|			 |			|
 *																	|			 |			|			 |					 |			|			 |			|
 *																	`--------------------'					 `--------------------'
 */
	
	[GIT] = LAYOUT_ergodox(
			//Left hand
			KC_TRANSPARENT,	KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,KC_TRANSPARENT,
			KC_TRANSPARENT,	KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,KC_TRANSPARENT,
			KC_TRANSPARENT,	GIT_ADD       , GIT_STATUS    , KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
			KC_TRANSPARENT,	KC_TRANSPARENT, KC_TRANSPARENT, GIT_COMMIT    , KC_TRANSPARENT, KC_TRANSPARENT,KC_TRANSPARENT,
			KC_TRANSPARENT,	KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
			
			// Left thumb cluster
			KC_TRANSPARENT,KC_TRANSPARENT,
							KC_TRANSPARENT,
			KC_TRANSPARENT,KC_TRANSPARENT,
			KC_TRANSPARENT,

			//Right hand
			KC_TRANSPARENT,					 KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,
			KC_TRANSPARENT,					 KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,
															 KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,
			KC_TRANSPARENT,					 KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,
							KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,
		
			// Right thumb cluster
			KC_TRANSPARENT,					KC_TRANSPARENT,
			KC_TRANSPARENT,
			KC_TRANSPARENT,					KC_TRANSPARENT,  KC_TRANSPARENT),

/* C-IDE Keymap
 * 
 * ,------------------------------------------------------.						,------------------------------------------------------.
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * |-----------+------+------+------+------+--------------|						|-------+------+------+------+------+------+-----------|
 * |					 |			|CLOSE |			|			 |			|				|						|				|			 |			|IMPORT|			| CMD  |					 |
 * |					 |			| FILE |			|			 |			|				|						|				|			 |			|SYMBOL|			|PALLET|					 |
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * |-----------+------+------+------+------+------|				|						|				|------+------+------+------+------+-----------|
 * |					 |			|SWITCH|			|TOGGLE|			|				|						|				| PANE | MOVE | MOVE | PANE |			 |  FORMAT   |
 * |					 |			| FILE |			| FULL |			|-------|						|-------|			 | LINE |	LINE |			|			 |	FILE   	 |
 * |					 |			|			 |			|SCREEN|			|				|						|				| LEFT | DOWN |  UP  |RIGHT |			 |					 |
 * |-----------+------+------+------+------+------|				|						|				|------+------+------+------+------+-----------|
 * |					 |			|			 |			|			 | OPEN |				|						|				|			 |			|			 |			|COMENT|					 |
 * |					 |			|			 |			|			 |  DEF |				|						|				|			 |			|			 |			|SELECT|					 |
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|	     |					 |
 * `-----------+------+------+------+------+--------------'						` -------------+------+------+------+------+-----------'
 *			|			 |			|			 |			|			 |																				 |			|			 |			|			 |			|
 *			|			 |			|			 |			|			 |																				 |			|			 |			|			 |			|
 *			|			 |			|			 |			|			 |																				 |			|			 |			|			 |			|
 *			`----------------------------------'																				 `----------------------------------'
 *																				 ,-------------.					 ,-------------.
 *																				 |			|			 |					 |			|			 |
 *																				 |			|			 |					 |			|			 |
 *																				 |			|			 |					 |			|			 |
 *																	,------|------|------|					 |------+------+------.
 *																	|E		S|			|			 |					 |			|      | A		|
 *																	|X		N|			|			 |					 |			|      | U C	|
 *																	|P		I|			|			 |					 |			|      | T O	|
 *																	|A		P|			|------|					 |------|      | O M	|
 *																	|N		P|			|			 |					 |			|      |	 P	|
 *																	|D		E|			|			 |					 |			|      |	  	|
 *																	|			T|			|			 |					 |			|      |			|
 *																	`--------------------'					 `--------------------'
 */
 
	[C_IDE] = LAYOUT_ergodox(
			// Left hand
			KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,       KC_TRANSPARENT,	KC_TRANSPARENT,
			KC_TRANSPARENT,  KC_TRANSPARENT,	C_CLOSE,         KC_TRANSPARENT,	KC_TRANSPARENT,       KC_TRANSPARENT,	KC_TRANSPARENT,
			KC_TRANSPARENT,  KC_TRANSPARENT,	C_SWITCH_FILE,   KC_TRANSPARENT,	C_TOGGLE_FULLSCREEN,  KC_TRANSPARENT,
			KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,       C_GOTO_DEF,	    KC_TRANSPARENT,
			KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,
			
																																				//Left thumb cluster
																																				KC_TRANSPARENT,					 KC_TRANSPARENT,
																																																 KC_TRANSPARENT,
																																				C_EXPAND_SNIPPET,				 KC_TRANSPARENT,
																																				                         KC_TRANSPARENT,
			
							//Right hand
							KC_TRANSPARENT,					 KC_TRANSPARENT,	KC_TRANSPARENT,    KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	    KC_TRANSPARENT,
							KC_TRANSPARENT,					 KC_TRANSPARENT,	KC_TRANSPARENT,    C_IMPORT_SYMBOL,	KC_TRANSPARENT,  C_COMMAND_PALLETTE,	KC_TRANSPARENT,
																			 C_PANE_LEFT,	    C_MOVE_LINE_DOWN,  C_MOVE_LINE_UP,	C_PANE_RIGHT,    KC_TRANSPARENT,	    C_FORMAT_FILE,
							KC_TRANSPARENT,					 KC_TRANSPARENT,	KC_TRANSPARENT,    KC_TRANSPARENT,	KC_TRANSPARENT,  C_COMMENT,	          KC_TRANSPARENT,
											KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,    KC_TRANSPARENT,	KC_TRANSPARENT,
		
							// Right thumb cluster
							KC_TRANSPARENT,					KC_TRANSPARENT,
							KC_TRANSPARENT,
							KC_TRANSPARENT,					KC_TRANSPARENT,   C_AUTOCOMPLETE),

/* Minecraft
 * 
 * ,------------------------------------------------------.						,------------------------------------------------------.
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * |  esc      |	1		|		2	 |	3		|		4	 |	5		|		6		|						|				|			 |			|			 |			|			 |					 |
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * |-----------+------+------+------+------+--------------|						|-------+------+------+------+------+------+-----------|
 * |					 |			|			 |			| MC   |			|				|						|				|			 |			|			 |			|			 |					 |
 * |	tab			 |	q		|		w	 |	e		|scroll|			|				|						|				|			 |			|			 |			|			 |					 |
 * |					 |			|			 |			|	next |			|				|						|				|			 |			|			 |			|			 |					 |
 * |-----------+------+------+------+------+------|				|						|				|------+------+------+------+------+-----------|
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * | left 		 |	a		|		s	 |	d 	| 	f  |			|-------|						|-------|			 |			|			 |			|			 |					 |
 * |	cntrl	   |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * |-----------+------+------+------+------+------|				|						|				|------+------+------+------+------+-----------|
 * |					 |			|			 |			|			 |			|	 f5 	|						|				|			 |			|			 |			|			 |					 |
 * |	l shift	 |			|			 |	c 	|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * |					 |			|			 |			|			 |			|				|						|				|			 |			|			 |			|			 |					 |
 * `-----------+------+------+------+------+--------------'						` -------------+------+------+------+------+-----------'
 *			|	     |			|			 |			|			 |																				 |			|			 |			|			 |			|
 *			|  6   |	f2	|	 f3	 |	f11	|	base |																				 |			|			 |			|			 |			|
 *			|      |			|			 |			|			 |																				 |			|			 |			|			 |			|
 *			`----------------------------------'																				 `----------------------------------'
 *																				 ,-------------.					 ,-------------.
 *																				 |			|			 |					 |			|			 |
 *																				 |pg up	|pg dwn|					 |			|			 |
 *																				 |			|			 |					 |			|			 |
 *																	,------|------|------|					 |------+------+------.
 *																	|	s		 |			|			 |					 |			|			 |			|
 *																	|	p		 |			|	 end |					 |			|			 |			|
 *																	|	a		 |			|			 |					 |			|			 |			|
 *																	|	c		 |	7 	|------|					 |------|			 |			|
 *																	|	e		 |			|			 |					 |			|			 |			|
 *																	|			 |			|	home |					 |			|			 |			|
 *																	|			 |			|			 |					 |			|			 |			|
 *																	`--------------------'					 `--------------------
 */
	[MINECRAFT] = LAYOUT_ergodox(
			// Left hand
			KC_ESCAPE,       KC_1, 	          KC_2,            KC_3,	          KC_4,                   KC_5,	          KC_6,
			KC_TAB,          KC_Q,	          KC_W,            KC_E,	          MC_SCROLL_NEXT,         KC_TRANSPARENT,	KC_TRANSPARENT,
			KC_LCTRL,        KC_A,	          KC_S,            KC_D,	          KC_F,                   KC_TRANSPARENT,
			KC_LSHIFT,       KC_TRANSPARENT,	KC_TRANSPARENT,  KC_C,	          KC_TRANSPARENT,         KC_TRANSPARENT,	KC_F5,
			KC_6,            KC_F2,	          KC_F3,           KC_F11,	        TO(BASE),
			
																																				//Left thumb cluster
																																				KC_PGUP,					       KC_PGDN,
																																																 KC_END,
																																				KC_SPACE,                KC_7,
																																				KC_HOME,
			
							//Right hand
							KC_TRANSPARENT,					 KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,
							KC_TRANSPARENT,					 KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,
																			 KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,
							KC_TRANSPARENT,					 KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,
											KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,  KC_TRANSPARENT,	KC_TRANSPARENT,
		
							// Right thumb cluster
							KC_TRANSPARENT,					KC_TRANSPARENT,
							KC_TRANSPARENT,
							KC_TRANSPARENT,					KC_TRANSPARENT,  KC_TRANSPARENT),

};

const uint16_t PROGMEM fn_actions[] = {
	[1] = ACTION_LAYER_TAP_TOGGLE(1)
};

// leaving this in place for compatibilty with old keymaps cloned and re-compiled.
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
			switch(id) {
				case 0:
				if (record->event.pressed) {
					SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
				}
				break;
			}
		return MACRO_NONE;
};

void matrix_init_user(void) {
#ifdef RGBLIGHT_COLOR_LAYER_0
	rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
#endif
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
		// dynamically generate these.
		case EPRM:
			if (record->event.pressed) {
				eeconfig_init();
			}
			return false;
			break;
		case VRSN:
			if (record->event.pressed) {
				SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
			}
			return false;
			break;
		case RGB_SLD:
			if (record->event.pressed) {
				rgblight_mode(1);
			}
			return false;
			break;
		case VIM_MOVE_LEFT:
			if (record->event.pressed) {
				SEND_STRING(SS_LCTRL("W")"H");
			}
			return false;
			break;
		case VIM_MOVE_RIGHT:
			if (record->event.pressed) {
				SEND_STRING(SS_LCTRL("W")"L");
			}
			return false;
			break;
		case VIM_MOVE_UP:
			if (record->event.pressed) {
				SEND_STRING(SS_LCTRL("W")"K");
			}
			return false;
			break;
		case VIM_MOVE_DOWN:
			if (record->event.pressed) {
				SEND_STRING(SS_LCTRL("W")"J");
			}
			return false;
			break;
		case VIM_COPY:
			if (record->event.pressed) {
				SEND_STRING("\"+y");
			}
			return false;
			break;
		case VIM_PASTE:
			if (record->event.pressed) {
				SEND_STRING("\"+p");
			}
			return false;
			break;
		case VIM_SPELL:
			if (record->event.pressed) {
				SEND_STRING("z=");
			}
			return false;
			break;
		case TMUX_SELECT_PANE_LEFT:
			if (record->event.pressed) {
				SEND_STRING(SS_LCTRL("b")SS_TAP(X_LEFT));
			}
			return false;
			break;
		case TMUX_SELECT_PANE_RIGHT:
			if (record->event.pressed) {
				SEND_STRING(SS_LCTRL("b")SS_TAP(X_RIGHT));
			}
			return false;
			break;
		case TMUX_SELECT_PANE_UP:
			if (record->event.pressed) {
				SEND_STRING(SS_LCTRL("b")SS_TAP(X_UP));
			}
			return false;
			break;
		case TMUX_SELECT_PANE_DOWN:
			if (record->event.pressed) {
				SEND_STRING(SS_LCTRL("b")SS_TAP(X_DOWN));
			}
			return false;
			break;
		case TMUX_MOVE_PANE_LEFT:
			if (record->event.pressed) {
				SEND_STRING(SS_LCTRL("b")"H");
			}
			return false;
			break;
		case TMUX_MOVE_PANE_RIGHT:
			if (record->event.pressed) {
				SEND_STRING(SS_LCTRL("b")"L");
			}
			return false;
			break;
		case TMUX_MOVE_PANE_UP:
			if (record->event.pressed) {
				SEND_STRING(SS_LCTRL("b")"K");
			}
			return false;
			break;
		case TMUX_MOVE_PANE_DOWN:
			if (record->event.pressed) {
				SEND_STRING(SS_LCTRL("b")"J");
			}
			return false;
			break;
		case TMUX_EXPAND_PANE_LEFT:
			if (record->event.pressed) {
				SEND_STRING(SS_LCTRL("b")SS_TAP(X_F9));
			}
			return false;
			break;
		case TMUX_EXPAND_PANE_RIGHT:
			if (record->event.pressed) {
				SEND_STRING(SS_LCTRL("b")SS_TAP(X_F10));
			}
			return false;
			break;
		case TMUX_EXPAND_PANE_UP:
			if (record->event.pressed) {
				SEND_STRING(SS_LCTRL("b")SS_TAP(X_F7));
			}
			return false;
			break;
		case TMUX_EXPAND_PANE_DOWN:
			if (record->event.pressed) {
				SEND_STRING(SS_LCTRL("b")SS_TAP(X_F8));
			}
			return false;
			break;
		case TMUX_SPLIT_HORIZONTAL:
			if (record->event.pressed) {
				SEND_STRING(SS_LCTRL("b")"-");
			}
			return false;
			break;
		case TMUX_SPLIT_VERTICAL:
			if (record->event.pressed) {
				SEND_STRING(SS_LCTRL("b")"|");
			}
			return false;
			break;
		case TMUX_DETACH:
			if (record->event.pressed) {
				SEND_STRING(SS_LCTRL("b")":detach"SS_TAP(X_ENTER));
			}
			return false;
			break;
		case TMUX_PAUSE_TERM_OUTPUT:
			if (record->event.pressed) {
				SEND_STRING(SS_LCTRL("b")"[");
			}
			return false;
			break;
		case TMUX_FOCUS_PANE:
			if (record->event.pressed) {
				SEND_STRING(SS_LCTRL("b")"z");
			}
			return false;
			break;
		case GIT_ADD:
			if (record->event.pressed) {
				SEND_STRING("git add ."SS_TAP(X_ENTER));
			}
			return false;
			break;
		case GIT_STATUS:
			if (record->event.pressed) {
				SEND_STRING("git status"SS_TAP(X_ENTER));
			}
			return false;
			break;
		case GIT_COMMIT:
			if (record->event.pressed) {
				SEND_STRING("git commit -m \"");
			}
			return false;
			break;
		case C_CLOSE:
			if (record->event.pressed) {
				SEND_STRING(SS_LCTRL("/")"w");
			}
			return false;
			break;
		case C_SWITCH_FILE:
			if (record->event.pressed) {
				SEND_STRING(SS_LCTRL("P")"switch file"SS_TAP(X_ENTER));
			}
			return false;
			break;
		case C_TOGGLE_FULLSCREEN:
			if (record->event.pressed) {
				SEND_STRING(SS_LCTRL("/")"vf");
			}
			return false;
			break;
		case C_GOTO_DEF:
			if (record->event.pressed) {
				SEND_STRING(SS_TAP(X_F3));
			}
			return false;
			break;
		case C_EXPAND_SNIPPET:
			if (record->event.pressed) {
				SEND_STRING(SS_LCTRL("b"));
			}
			return false;
			break;
		case C_PANE_LEFT:
			if (record->event.pressed) {
				SEND_STRING(SS_LCTRL("h"));
			}
			return false;
			break;
		case C_PANE_RIGHT:
			if (record->event.pressed) {
				SEND_STRING(SS_LCTRL("l"));
			}
			return false;
			break;
		case C_MOVE_LINE_UP:
			if (record->event.pressed) {
				SEND_STRING(SS_LALT(SS_TAP(X_UP)));
			}
			return false;
			break;
		case C_MOVE_LINE_DOWN:
			if (record->event.pressed) {
				SEND_STRING(SS_LALT(SS_TAP(X_DOWN)));
			}
			return false;
			break;
		case C_IMPORT_SYMBOL:
			if (record->event.pressed) {
				SEND_STRING(SS_LCTRL("/")"i");
			}
			return false;
			break;
		case C_COMMAND_PALLETTE:
			if (record->event.pressed) {
				SEND_STRING(SS_LCTRL("P"));
			}
			return false;
			break;
		case C_FORMAT_FILE:
			if (record->event.pressed) {
				SEND_STRING(SS_LCTRL("P")"format current file"SS_TAP(X_ENTER));
			}
			return false;
			break;
		case C_COMMENT:
			if (record->event.pressed) {
				SEND_STRING(SS_LCTRL("/")"/");
			}
			return false;
			break;
		case C_AUTOCOMPLETE:
			if (record->event.pressed) {
				SEND_STRING(SS_LCTRL(" "));
			}
			return false;
			break;
		case MC_SCROLL_NEXT:
			if (record->event.pressed) {
				register_code(KC_WH_D);
				SEND_STRING(SS_DELAY(100));
				unregister_code(KC_WH_D);
			}
			return false;
			break;
	}
	return true;
}

uint32_t layer_state_set_user(uint32_t state) {


		uint8_t layer = biton32(state);

		ergodox_board_led_off();
		ergodox_right_led_1_off();
		ergodox_right_led_2_off();
		ergodox_right_led_3_off();
		switch (layer) {
			case 0:
				#ifdef RGBLIGHT_COLOR_LAYER_0
					rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
				#endif
				break;
			case 1:
				ergodox_right_led_1_on();
				#ifdef RGBLIGHT_COLOR_LAYER_1
					rgblight_setrgb(RGBLIGHT_COLOR_LAYER_1);
				#endif
				break;
			case 2:
				ergodox_right_led_2_on();
				#ifdef RGBLIGHT_COLOR_LAYER_2
					rgblight_setrgb(RGBLIGHT_COLOR_LAYER_2);
				#endif
				break;
			case 3:
				ergodox_right_led_3_on();
				#ifdef RGBLIGHT_COLOR_LAYER_3
					rgblight_setrgb(RGBLIGHT_COLOR_LAYER_3);
				#endif
				break;
			case 4:
				ergodox_right_led_1_on();
				ergodox_right_led_2_on();
				#ifdef RGBLIGHT_COLOR_LAYER_4
					rgblight_setrgb(RGBLIGHT_COLOR_LAYER_4);
				#endif
				break;
			case 5:
				ergodox_right_led_1_on();
				ergodox_right_led_3_on();
				#ifdef RGBLIGHT_COLOR_LAYER_5
					rgblight_setrgb(RGBLIGHT_COLOR_LAYER_5);
				#endif
				break;
			case 6:
				ergodox_right_led_2_on();
				ergodox_right_led_3_on();
				#ifdef RGBLIGHT_COLOR_LAYER_6
					rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
				#endif
				break;
			case 7:
				ergodox_right_led_1_on();
				ergodox_right_led_2_on();
				ergodox_right_led_3_on();
				#ifdef RGBLIGHT_COLOR_LAYER_7
					rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
				#endif
				break;
			default:
				break;
		}
		return state;
};

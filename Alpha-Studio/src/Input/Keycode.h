#pragma once

namespace Alpha {
	using Keycode = unsigned int;

	class Keycodes {
	public:
		inline static const Keycode KEY_SPACE         =     32 ;
		inline static const Keycode KEY_APOSTROPHE    =     39 ; /* ' */
		inline static const Keycode KEY_COMMA         =     44 ; /* , */
		inline static const Keycode KEY_MINUS         =     45 ; /* - */
		inline static const Keycode KEY_PERIOD        =     46 ; /* . */
		inline static const Keycode KEY_SLASH         =     47 ; /* / */
		inline static const Keycode KEY_0             =     48	;
		inline static const Keycode KEY_1             =     49	;
		inline static const Keycode KEY_2             =     50	;
		inline static const Keycode KEY_3             =     51	;
		inline static const Keycode KEY_4             =     52	;
		inline static const Keycode KEY_5             =     53	;
		inline static const Keycode KEY_6             =     54	;
		inline static const Keycode KEY_7             =     55	;
		inline static const Keycode KEY_8             =     56	;
		inline static const Keycode KEY_9             =     57	;
		inline static const Keycode KEY_SEMICOLON     =     59 ; /* ; */
		inline static const Keycode KEY_EQUAL         =     61 ; /* = */
		inline static const Keycode KEY_A             =     65	;
		inline static const Keycode KEY_B             =     66	;
		inline static const Keycode KEY_C             =     67	;
		inline static const Keycode KEY_D             =     68	;
		inline static const Keycode KEY_E             =     69	;
		inline static const Keycode KEY_F             =     70	;
		inline static const Keycode KEY_G             =     71	;
		inline static const Keycode KEY_H             =     72	;
		inline static const Keycode KEY_I             =     73	;
		inline static const Keycode KEY_J             =     74	;
		inline static const Keycode KEY_K             =     75	;
		inline static const Keycode KEY_L             =     76	;
		inline static const Keycode KEY_M             =     77	;
		inline static const Keycode KEY_N             =     78	;
		inline static const Keycode KEY_O             =     79	;
		inline static const Keycode KEY_P             =     80	;
		inline static const Keycode KEY_Q             =     81	;
		inline static const Keycode KEY_R             =     82	;
		inline static const Keycode KEY_S             =     83	;
		inline static const Keycode KEY_T             =     84	;
		inline static const Keycode KEY_U             =     85	;
		inline static const Keycode KEY_V             =     86	;
		inline static const Keycode KEY_W             =     87	;
		inline static const Keycode KEY_X             =     88	;
		inline static const Keycode KEY_Y             =     89	;
		inline static const Keycode KEY_Z             =     90	;
		inline static const Keycode KEY_LEFT_BRACKET  =     91 ; /* [ */
		inline static const Keycode KEY_BACKSLASH     =     92 ; /* \ */
		inline static const Keycode KEY_RIGHT_BRACKET =     93 ; /* ] */
		inline static const Keycode KEY_GRAVE_ACCENT  =     96 ; /* ` */
		inline static const Keycode KEY_WORLD_1       =     161; /* non-US #1 */
		inline static const Keycode KEY_WORLD_2       =     162; /* non-US #2 */
																;
																;
		inline static const Keycode KEY_ESCAPE        =     256;
		inline static const Keycode KEY_ENTER         =     257;
		inline static const Keycode KEY_TAB           =     258;
		inline static const Keycode KEY_BACKSPACE     =     259;
		inline static const Keycode KEY_INSERT        =     260;
		inline static const Keycode KEY_DELETE        =     261;
		inline static const Keycode KEY_RIGHT         =     262;
		inline static const Keycode KEY_LEFT          =     263;
		inline static const Keycode KEY_DOWN          =     264;
		inline static const Keycode KEY_UP            =     265;
		inline static const Keycode KEY_PAGE_UP       =     266;
		inline static const Keycode KEY_PAGE_DOWN     =     267;
		inline static const Keycode KEY_HOME          =     268;
		inline static const Keycode KEY_END           =     269;
		inline static const Keycode KEY_CAPS_LOCK     =     280;
		inline static const Keycode KEY_SCROLL_LOCK   =     281;
		inline static const Keycode KEY_NUM_LOCK      =     282;
		inline static const Keycode KEY_PRINT_SCREEN  =     283;
		inline static const Keycode KEY_PAUSE         =     284;
		inline static const Keycode KEY_F1            =     290;
		inline static const Keycode KEY_F2            =     291;
		inline static const Keycode KEY_F3            =     292;
		inline static const Keycode KEY_F4            =     293;
		inline static const Keycode KEY_F5            =     294;
		inline static const Keycode KEY_F6            =     295;
		inline static const Keycode KEY_F7            =     296;
		inline static const Keycode KEY_F8            =     297;
		inline static const Keycode KEY_F9            =     298;
		inline static const Keycode KEY_F10           =     299;
		inline static const Keycode KEY_F11           =     300;
		inline static const Keycode KEY_F12           =     301;
		inline static const Keycode KEY_F13           =     302;
		inline static const Keycode KEY_F14           =     303;
		inline static const Keycode KEY_F15           =     304;
		inline static const Keycode KEY_F16           =     305;
		inline static const Keycode KEY_F17           =     306;
		inline static const Keycode KEY_F18           =     307;
		inline static const Keycode KEY_F19           =     308;
		inline static const Keycode KEY_F20           =     309;
		inline static const Keycode KEY_F21           =     310;
		inline static const Keycode KEY_F22           =     311;
		inline static const Keycode KEY_F23           =     312;
		inline static const Keycode KEY_F24           =     313;
		inline static const Keycode KEY_F25           =     314;
		inline static const Keycode KEY_NP_0          =     320;
		inline static const Keycode KEY_NP_1          =     321;
		inline static const Keycode KEY_NP_2          =     322;
		inline static const Keycode KEY_NP_3          =     323;
		inline static const Keycode KEY_NP_4          =     324;
		inline static const Keycode KEY_NP_5          =     325;
		inline static const Keycode KEY_NP_6          =     326;
		inline static const Keycode KEY_NP_7          =     327;
		inline static const Keycode KEY_NP_8          =     328;
		inline static const Keycode KEY_NP_9          =     329;
		inline static const Keycode KEY_NP_DECIMAL    =     330;
		inline static const Keycode KEY_NP_DIVIDE     =     331;
		inline static const Keycode KEY_NP_MULTIPLY   =     332;
		inline static const Keycode KEY_NP_SUBTRACT   =     333;
		inline static const Keycode KEY_NP_ADD        =     334;
		inline static const Keycode KEY_NP_ENTER      =     335;
		inline static const Keycode KEY_NP_EQUAL      =     336;
		inline static const Keycode KEY_LEFT_SHIFT    =     340;
		inline static const Keycode KEY_LEFT_CONTROL  =     341;
		inline static const Keycode KEY_LEFT_ALT      =     342;
		inline static const Keycode KEY_LEFT_SUPER    =     343;
		inline static const Keycode KEY_RIGHT_SHIFT   =     344;
		inline static const Keycode KEY_RIGHT_CONTROL =     345;
		inline static const Keycode KEY_RIGHT_ALT     =     346;
		inline static const Keycode KEY_RIGHT_SUPER   =     347;
		inline static const Keycode KEY_MENU          =     348;
	};

	using MouseButton = unsigned int;

	class MouseButtons {
	public:
		inline static const MouseButton FIRST = 0;
		inline static const MouseButton SECOND = 1;
		inline static const MouseButton THIRD = 2;
		inline static const MouseButton FOURTH = 3;
		inline static const MouseButton FIFTH = 4;
		inline static const MouseButton SIXTH = 5;
		inline static const MouseButton SEVENTH = 6;
		inline static const MouseButton EIGHTH = 7;
		inline static const MouseButton LEFT = MouseButtons::FIRST;
		inline static const MouseButton RIGHT = MouseButtons::SECOND;
		inline static const MouseButton MIDDLE = MouseButtons::THIRD;
	};
}
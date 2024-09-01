#pragma once
// Copy-pasted from GLFWs keys and restructured to make it more API-friendly

namespace Rutan::IO 
{

namespace KeyStatus
{
enum Status : u8
{
	Unknown = 0,
	Release = 1,
	Press   = 2,
	Repeat  = 3
};
}

namespace Mouse
{
enum Buttons : u8
{
	Button1      = 0,
	Button2      = 1,
	Button3      = 2,
	ButtonLeft   = Button1,
	ButtonRight  = Button2,
	ButtonMiddle = Button3,
	Button4      = 3,
	Button5      = 4,
	Button6      = 5,
	Button7      = 6,
	Button8      = 7,

	FIRST        = Button1,
	LAST         = Button8
};
}

namespace Joystick
{
enum Buttons : u8
{
	Button1    = 0,
	Button2    = 1,
	Button3    = 2,
	Button4    = 3,
	Button5    = 4,
	Button6    = 5,
	Button7    = 6,
	Button8    = 7,
	Button9    = 8,
	Button10   = 9,
	Button11   = 10,
	Button12   = 11,
	Button13   = 12,
	Button14   = 13,
	Button15   = 14,
	Button16   = 15,
	
	FIRST      = Button1,
	LAST       = Button16
};
}

namespace Gamepad
{
enum Buttons : u8
{
	ButtonA                = 0,
	ButtonB                = 1,
	ButtonX                = 2,
	ButtonY                = 3,
	ButtonCross            = ButtonA,
	ButtonCircle           = ButtonB,
	ButtonSquare           = ButtonX,
	ButtonTriangle         = ButtonY,
	ButtonLeftBumper       = 4,
	ButtonRightBumper      = 5,
	ButtonBack             = 6, 
	ButtonStart            = 7,
	ButtonGuide            = 8,
	ButtonLeftThumb        = 9,
	ButtonRightThumb       = 10, 
	ButtonDpadUp           = 11,
	ButtonDpadRight        = 12,
	ButtonDpadDown         = 13, 
	ButtonDpadLeft         = 14,  

	FIRSTBUTTON            = ButtonA,
	LASTBUTTON             = ButtonDpadLeft,

	ButtonAxisLeftX        = 0,
	ButtonAxisLeftY        = 1,
	ButtonAxisRightX       = 2,
	ButtonAxisRightY       = 3,
	ButtonAxisLeftTrigger  = 4,
	ButtonAxisRightTrigger = 5,

	FIRSTAXIS = ButtonAxisLeftX,
	LASTAXIS  = ButtonAxisRightTrigger
};
}

namespace Keyboard
{
enum Buttons : u16
{
	Space          = 32,
	Apostrophe     = 39,
	Comma          = 44,
	Minus          = 45,
	Period         = 46,
	Slash          = 47,
	Key0           = 48,
	Key1           = 49,
	Key2           = 50,
	Key3           = 51,
	Key4           = 52,
	Key5           = 53,
	Key6           = 54,
	Key7           = 55,
	Key8           = 56,
	Key9           = 57,
	Semicolon      = 59,
	Equal          = 61,
	A              = 65,
	B              = 66,
	C              = 67,
	D              = 68,
	E              = 69,
	F              = 70,
	G              = 71,
	H              = 72,
	I              = 73,
	J              = 74,
	K              = 75,
	L              = 76,
	M              = 77,
	N              = 78,
	O              = 79,
	P              = 80,
	Q              = 81,
	R              = 82,
	S              = 83,
	T              = 84,
	U              = 85,
	V              = 86,
	W              = 87,
	X              = 88,
	Y              = 89,
	Z              = 90,
	LeftBracket    = 91,
	Backslash      = 92,
	RightBracket   = 93,
	GraveAccent    = 96,
	World1         = 161,
	World2         = 162,
	Escape         = 256,
	Enter          = 257,
	Tab            = 258,
	Backspace      = 259,
	Insert         = 260,
	Delete         = 261,
	Right          = 262,
	Left           = 263,
	Down           = 264,
	Up             = 265,
	PageUp         = 266,
	PageDown       = 267,
	Home           = 268,
	End            = 269,
	CapsLock       = 280,
	ScrollLock     = 281,
	NumLock        = 282,
	PrintScreen    = 283,
	Pause          = 284,
	F1             = 290,
	F2             = 291,
	F3             = 292,
	F4             = 293,
	F5             = 294,
	F6             = 295,
	F7             = 296,
	F8             = 297,
	F9             = 298,
	F10            = 299,
	F11            = 300,
	F12            = 301,
	F13            = 302,
	F14            = 303,
	F15            = 304,
	F16            = 305,
	F17            = 306,
	F18            = 307,
	F19            = 308,
	F20            = 309,
	F21            = 310,
	F22            = 311,
	F23            = 312,
	F24            = 313,
	F25            = 314,
	NumPad0        = 320,
	NumPad1        = 321,
	NumPad2        = 322,
	NumPad3        = 323,
	NumPad4        = 324,
	NumPad5        = 325,
	NumPad6        = 326,
	NumPad7        = 327,
	NumPad8        = 328,
	NumPad9        = 329,
	NumPadDecimal  = 330,
	NumPadDivide   = 331,
	NumPadMultiply = 332,
	NumPadSubtract = 333,
	NumPadAdd      = 334,
	NumPadEnter    = 335,
	NumPadEqual    = 336,
	ShiftLeft      = 340,
	ControlLeft    = 341,
	AltLeft        = 342,
	SuperLeft      = 343,
	ShiftRight     = 344,
	ControlRight   = 345,
	AltRight       = 346,
	SuperRight     = 347,
	Menu           = 348,

	FIRST          = Space,
	LAST           = Menu,

	UNKNOWN        = 0xFFFF
};
}

}

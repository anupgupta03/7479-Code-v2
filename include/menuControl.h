/**
* @Date:   2016-11-30T10:50:51+11:00
* @Last modified time: 2016-12-01T20:09:41+11:00
*/

#ifndef H_MENUCONTROL_INCLUDED
#define H_MENUCONTROL_INCLUDED

// Different types of menus
#define MENUTYPE_VALUE 0
#define MENUTYPE_CHOICE 1
#define MENUTYPE_SUB 2
#define MENUTYPE_EXIT 99

// Default for LCD line 2 display
#define DEFAULT_LINE2 "<<            >>"
#define SUBMENU_SELECT_TEXT "<<   SELECT   >>"
#define EXIT_MENU_SELECT "<<     OK     >>"

#define MAX_MEN_LISTS 4
#define MAX_MENUS 10
#define MAX_CHOICES 10

// A menu list
// holds a double linked list of menus
typedef struct _menuList {
  // number of menus in this list
  int num;
  // pointer to first menu
  struct _menu* first;
  // pointer to last menu
  struct _menu* last;
  // pointer to current menu
  struct _menu* current;
} menuList;

// A menu structure
typedef struct _menu {
  // lcd display text
  char lcd_line_1[20];
  char lcd_line_2[20];

  // pointes to next and previous menus
  struct _menu* next;
  struct _menu* prev;

  // the type of this menu
  int menu_type;

  // value (used as index for choice menus)
  int value;
  // maximum value of a "value" menu
  int max_value;

  // list of choices
  int cnum;
  struct _clist* cfirst;
  struct _clist* cend;

  // pointer to a menu list - a sub menu
  menuList* list;
} menu;

// A choice structure
typedef struct _clist {
  // name of choice
  char name[20];
  // pointer to next choice
  struct _clist* next;
  // pointer to previous choice
  struct _clist* prev;
} clist;

// Enums for button pushes in the menu state machine
typedef enum _userControl {
  initializeButton = 0,
  noButton,
  leftButtonDown,
  rightButtonDown,
  centerButtonDown
} userControl;

#endif  // H_MENUCONTROL_INCLUDED

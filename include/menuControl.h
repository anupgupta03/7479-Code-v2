/**
* @Date:   2016-11-30T10:50:51+11:00
* @Last modified time: 2016-12-02T22:04:51+11:00
*/

#ifndef H_MENUCONTROL_INCLUDED
#define H_MENUCONTROL_INCLUDED

// Different types of menus
#define MENUTYPE_VALUE 0
#define MENUTYPE_CHOICE 1
#define MENUTYPE_SUB 2
#define MENUTYPE_FUNCTION 3
#define MENUTYPE_EXIT 99

// Default for LCD line 2 display
#define DEFAULT_LINE2 "<<            >>"
#define SUBMENU_SELECT_TEXT "<<   SELECT   >>"
#define EXIT_MENU_SELECT    "<<     OK     >>"
#define FUNCTION_MENU_TEXT  "<<   SELECT   >>"

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
  unsigned func;

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

/**
 * Create a new menu list
 * @return menuList object that has been initialized
 */
menuList* menuListInit();
/**
 * Add a menu to a menu list
 * @param  list menuList to append
 * @param  m    menu object to append to the menuList
 * @return      Returns an int as a success code
 */
int menuListAddMenu(menuList* list, menu* m);
/**
 * Initialize a menu and link into the menu list
 * @param  list menuList object to append
 * @param  name name of menu
 * @param  type type of menu
 * @param  max  max value of the menu
 * @return      returns initialized menu object
 */
menu* menuInit(menuList* list, const char* name, int type, int max, unsigned func);
/**
 * Add one choice to a menu
 * @param  m    menu object
 * @param  name Name of the choice
 * @return      List object
 */
clist* MenuAddChoice(menu* m, const char* name);
/**
 * Update the LCD display with the menu information
 * @param m Menu to display
 */
int menuLcdUpdate(menu* m);
/**
 * Create a value display for the LCD line 2
 * @param m Menu object to read from
 */
int menuCreateValueDisplay(menu* m);
/**
 * Create a choice display for the LCD line 2
 * @param m menu object
 */
int menuCreateChoiceDisplay(menu* m);
/**
 * Update the text for the LCD line 2 based on the menu type
 * @param m menu object
 */
int menuCreateDisplay(menu* m);
/**
 * Run a menu list
 * @param  list list object
 * @return      Status code
 */
int menuRun(menuList* list);
/**
 * Main init function for primary menu display
 */
void mainMenuInit();

#endif  // H_MENUCONTROL_INCLUDED
